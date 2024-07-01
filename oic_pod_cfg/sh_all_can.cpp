//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "sh_all_can.h"
#include "chan_form.h"
#include "admin.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TShowChannelForm *ShowChannelForm;
//---------------------------------------------------------------------------
__fastcall TShowChannelForm::TShowChannelForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TShowChannelForm::RefreshRow(TObject *Sender,TChannel *ch,int rr)
{
        StringGrid->Cells[0][rr] = IntToStr(ch->ChannelID);
        StringGrid->Cells[1][rr] = ch->ChannelCaption;

        StringGrid->Cells[2][rr] = ChannelForm->TypeEdit->Items->Strings[ch->ChannelType];
        StringGrid->Cells[3][rr] = ChannelForm->DimensionEdit->Items->Strings[ch->Dimension];
        StringGrid->Cells[4][rr] = ChannelForm->KindDimEdit->Items->Strings[ch->DimensionKind];

        StringGrid->Cells[5][rr] = FloatToStr(ch->MIN_DIM);
        StringGrid->Cells[6][rr] = FloatToStr(ch->MAX_DIM);

        StringGrid->Cells[7][rr] = ch->col;

        StringGrid->Cells[8][rr] = IntToStr(ch->NFPGA);
        StringGrid->Cells[9][rr] = IntToStr(ch->n_channel);

        StringGrid->Cells[10][rr] = FloatToStrF(ch->a,ffFixed,8,2);
        StringGrid->Cells[11][rr] = FloatToStrF(ch->b,ffFixed,8,2);
        StringGrid->Cells[12][rr] = FloatToStrF(ch->k,ffFixed,8,2);
        StringGrid->Cells[13][rr] = FloatToStr(ch->imp);

        StringGrid->Cells[14][rr] = FloatToStrF(ch->k_trans,ffFixed,8,2);                
}

void __fastcall TShowChannelForm::GetChannelParamFromForm(TObject *Sender,TChannel *ch)
{
        ch->ChannelID = ChannelForm->IDEdit->Value;
        strcpy(ch->ChannelCaption,ChannelForm->CaptionEdit->Text.c_str());
        ch->ChannelType = TChannelType(ChannelForm->TypeEdit->ItemIndex);
        ch->Dimension = TDimensionType(ChannelForm->DimensionEdit->ItemIndex);
        ch->DimensionKind = TDimensionKind(ChannelForm->KindDimEdit->ItemIndex);
        ch->MIN_DIM = StrToFloat(ChannelForm->MINDimEdit->Text);
        ch->MAX_DIM = StrToFloat(ChannelForm->MAXDimEdit->Text);
        ch->col = ChannelForm->ActColorEdit->Selected;
        ch->col_nact = ChannelForm->NActColorEdit->Selected;
        ch->NFPGA = ChannelForm->FPGAEdit->Value;
        ch->n_channel = ChannelForm->NChannelEdit->Value;

        ch->a = StrToFloat(ChannelForm->aEdit->Text);
        ch->b = StrToFloat(ChannelForm->bEdit->Text);
        ch->k = StrToFloat(ChannelForm->kEdit->Text);
        ch->imp = StrToFloat(ChannelForm->impEdit->Text);

        ch->k_trans = StrToFloat(ChannelForm->KTransEdit->Text);
}

void __fastcall TShowChannelForm::AddButtonClick(TObject *Sender)
{
        int c = AdminForm->ChannelList->GetLastID();
        ChannelForm->IDEdit->Value = c+1;

        if (ChannelForm->ShowModal() == mrOk)
        {

                TChannel *ch = new TChannel;

                AdminForm->ChannelList->Add(ch);

                ch->ChannelID = c+1;

                int k = AdminForm->ChannelList->count;

                GetChannelParamFromForm(Sender,ch);

                RefreshRow(Sender,ch,k);
        }
}
//---------------------------------------------------------------------------

void __fastcall TShowChannelForm::FormCreate(TObject *Sender)
{
        StringGrid->Cells[0][0] = "ID";
        StringGrid->Cells[1][0] = "Наименование";
        StringGrid->Cells[2][0] = "Тип канала";
        StringGrid->Cells[3][0] = "Измерение";
        StringGrid->Cells[4][0] = "Ед.изм.";
        StringGrid->Cells[5][0] = "MIN";
        StringGrid->Cells[6][0] = "MAX";
        StringGrid->Cells[7][0] = "Цвет";
        StringGrid->Cells[8][0] = "FPGA";
        StringGrid->Cells[9][0] = "№ конт.";
        StringGrid->Cells[10][0] = "a";
        StringGrid->Cells[11][0] = "b";
        StringGrid->Cells[12][0] = "k";
        StringGrid->Cells[13][0] = "Имп.";
        StringGrid->Cells[14][0] = "Транс.";
}
//---------------------------------------------------------------------------

void __fastcall TShowChannelForm::SaveButtonClick(TObject *Sender)
{
        AnsiString f_name;
        f_name = AdminForm->sys_param->SysDir;
        f_name += "\\channels.dat";
        AdminForm->ChannelList->WriteToFile(f_name);
}
//---------------------------------------------------------------------------


void __fastcall TShowChannelForm::StringGridDblClick(TObject *Sender)
{
    int r = StringGrid->Row;

    if (AdminForm->ChannelList->count >= r)
    {
        TChannel *ch = (*AdminForm->ChannelList)[r-1];
        if (ch->ChannelType == tchtANALOG)
        {
                ChannelForm->AnalogBox->Visible = true;
                ChannelForm->CounterBox->Visible = false;
                ChannelForm->TransBox->Visible = true;
        }
        else
        if (ch->ChannelType == tchtCOUNTER)
        {
                ChannelForm->AnalogBox->Visible = false;
                ChannelForm->CounterBox->Visible = true;
                ChannelForm->TransBox->Visible = false;
        }
        else
        {
                ChannelForm->AnalogBox->Visible = false;
                ChannelForm->CounterBox->Visible = false;
                ChannelForm->TransBox->Visible = false;
        }

        ChannelForm->RefreshEdits(Sender,(*AdminForm->ChannelList)[r-1]);

        if (ChannelForm->ShowModal() == mrOk)
        {
                TChannel *ch = (*AdminForm->ChannelList)[r-1];

                GetChannelParamFromForm(Sender,ch);

                RefreshRow(Sender,ch,r);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TShowChannelForm::FormShow(TObject *Sender)
{
        ClearStringGrid(Sender);

        AdminForm->ChannelList->DestroyList();
        delete AdminForm->ChannelList;

        AdminForm->ChannelList = new TVariantList <TChannel>;
        AnsiString f_name;
        f_name = AdminForm->sys_param->SysDir;
        f_name += "\\channels.dat";
        AdminForm->ChannelList->ReadFromFile(f_name);

        for (int i=0; i < AdminForm->ChannelList->count; i++)
        {
                TChannel *ch = (*AdminForm->ChannelList)[i];
                RefreshRow(Sender,ch,i+1);
        }
}
//---------------------------------------------------------------------------

void __fastcall TShowChannelForm::ClearStringGrid(TObject *Sender)
{
        for (int j=1; j<100; j++)
             StringGrid->Rows[j]->Clear();
}

void __fastcall TShowChannelForm::DelButtonClick(TObject *Sender)
{
   if (AdminForm->ChannelList->count != 0)
   {
        if (MessageDlg("Удалить канал?",
               mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
        {
                int r = StringGrid->Row;

                if (r <= AdminForm->ChannelList->count)
                {
                        AdminForm->ChannelList->Del(r-1);

                        // пересчет ID
                        ClearStringGrid(Sender);
                        for (int i=0; i<AdminForm->ChannelList->count; i++)
                        {
                                TChannel *ch = (*AdminForm->ChannelList)[i];
                                ch->ChannelID = i;
                                RefreshRow(Sender,ch,i+1);
                        }
                }
        }
   }
}
//---------------------------------------------------------------------------

void __fastcall TShowChannelForm::CloseButtonClick(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

// пересчет id
void __fastcall TShowChannelForm::Button1Click(TObject *Sender)
{
        ClearStringGrid(Sender);
        for (int i=0; i<AdminForm->ChannelList->count; i++)
        {
                TChannel *ch = (*AdminForm->ChannelList)[i];
                ch->ChannelID = i;
                RefreshRow(Sender,ch,i+1);
        }
}
//---------------------------------------------------------------------------


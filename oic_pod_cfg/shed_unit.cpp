//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "admin.h"
#include "shed_unit.h"
#include "add_shed.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdPort"
#pragma link "AdTapi"
#pragma link "ADTrmEmu"
#pragma link "AdTStat"
#pragma link "OoMisc"
#pragma link "AdProtcl"
#pragma link "AdPStat"
#pragma link "AdPacket"
#pragma resource "*.dfm"
TShedForm *ShedForm;
//---------------------------------------------------------------------------
__fastcall TShedForm::TShedForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TShedForm::ClearRows()
{
        for (int i = 1; i < StringGrid->RowCount; i++)
                StringGrid->Rows[i]->Clear();
}

void TShedForm::RefreshRow(TShedRecord *rec,int rr)
{
        StringGrid->Cells[0][rr] = TimeToStr(rec->time);
        StringGrid->Cells[1][rr] = rec->StvolName;
        StringGrid->Cells[2][rr] = rec->Phone;

        AnsiString temp;
        switch (rec->action)
        {
                case tsaGET_ACTUAL :
                        temp = "получение актуального архива смены";
                        break;
                case tsaGET_ACTUAL_STAT :
                        temp = "получение актуальной статистики";
                        break;
                case tsaGET_NOT_DOWNLOADED :
                        temp = "получение <забытых> архивов";
                        break;
        }
        StringGrid->Cells[3][rr] = temp;

        if (rec->state) temp = "заблокировано";
        else temp = "активно";
        StringGrid->Cells[4][rr] = temp;
}

void __fastcall TShedForm::FormCreate(TObject *Sender)
{
        StringGrid->Cells[0][0] = "Время";
        StringGrid->Cells[1][0] = "Ствол";
        StringGrid->Cells[2][0] = "Телефон";
        StringGrid->Cells[3][0] = "Действие";
        StringGrid->Cells[4][0] = "Состояние";
}
//---------------------------------------------------------------------------
//save
void __fastcall TShedForm::BitBtn3Click(TObject *Sender)
{
        AdminForm->sheduler->Save();
}
//---------------------------------------------------------------------------
// delete
void __fastcall TShedForm::BitBtn2Click(TObject *Sender)
{
   if (AdminForm->sheduler->list->count != 0)
   {
        if (MessageDlg("Удалить запись?",
               mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
        {
                int r = StringGrid->Row;

                if (r <= AdminForm->sheduler->list->count)
                {
                        AdminForm->sheduler->list->Del(r-1);

                        ClearRows();

                        StringGrid->RowCount = 2;

                        for (int i=0; i<AdminForm->sheduler->list->count; i++)
                        {
                                RefreshRow((*AdminForm->sheduler->list)[i],i+1);
                                StringGrid->RowCount++;
                        }
                }
        }
   }
}
//---------------------------------------------------------------------------
void __fastcall TShedForm::FormShow(TObject *Sender)
{
        AdminForm->sheduler->list->DestroyList();
        AdminForm->sheduler->Load();

        ClearRows();

        StringGrid->RowCount = 2;

        for (int i=0; i<AdminForm->sheduler->list->count; i++)
        {
                RefreshRow((*AdminForm->sheduler->list)[i],i+1);
                StringGrid->RowCount++;
        }
}
//---------------------------------------------------------------------------
//close
void __fastcall TShedForm::BitBtn4Click(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------
// add shedul
void __fastcall TShedForm::BitBtn1Click(TObject *Sender)
{
        AddShedForm->Caption = "Добавление действия";
        AddShedForm->TimeEdit->Text = "";
        AddShedForm->StvolEdit->ItemIndex = -1;
        AddShedForm->StvolEdit->Text = "";
        AddShedForm->PhoneEdit->Text = "";
        AddShedForm->ActionEdit->ItemIndex = -1;
        AddShedForm->ActionEdit->Text = "";
        AddShedForm->BlockCheckBox->Checked = false;

        if (AddShedForm->ShowModal() == mrOk)
        {
                TShedRecord *rec = new TShedRecord();
                rec->time = StrToTime(AddShedForm->TimeEdit->Text);
                strcpy(rec->StvolName,AddShedForm->StvolEdit->Text.c_str());
                strcpy(rec->Phone,AddShedForm->PhoneEdit->Text.c_str());
                rec->action = AddShedForm->ActionEdit->ItemIndex;
                rec->state = AddShedForm->BlockCheckBox->Checked;
                AdminForm->sheduler->list->Add(rec);

                short rr = StringGrid->RowCount-1;
                StringGrid->RowCount++;
                RefreshRow(rec,rr);
        }
}
//---------------------------------------------------------------------------
void __fastcall TShedForm::StringGridDblClick(TObject *Sender)
{
        AddShedForm->Caption = "Редактирование";

        int r = StringGrid->Row;

        if (AdminForm->sheduler->list->count >= r)
        {
                TShedRecord *rec = (*AdminForm->sheduler->list)[r-1];

                AddShedForm->TimeEdit->Text = TimeToStr(rec->time);
                AddShedForm->StvolEdit->Text = rec->StvolName;
                AddShedForm->PhoneEdit->Text = rec->Phone;

                AnsiString temp;
                switch (rec->action)
                {
                        case tsaGET_ACTUAL :
                                temp = "получение актуального архива смены";
                                break;
                        case tsaGET_ACTUAL_STAT :
                                temp = "получение актуальной статистики";
                                break;
                        case tsaGET_NOT_DOWNLOADED :
                                temp = "получение <забытых> архивов";
                                break;
                }
                AddShedForm->ActionEdit->ItemIndex = rec->action;
                AddShedForm->ActionEdit->Text = temp;

                AddShedForm->BlockCheckBox->Checked = rec->state;

                if (AddShedForm->ShowModal() == mrOk)
                {
                        rec->time = StrToTime(AddShedForm->TimeEdit->Text);
                        strcpy(rec->StvolName,AddShedForm->StvolEdit->Text.c_str());
                        strcpy(rec->Phone,AddShedForm->PhoneEdit->Text.c_str());
                        rec->action = AddShedForm->ActionEdit->ItemIndex;
                        rec->state = AddShedForm->BlockCheckBox->Checked;

                        RefreshRow(rec,r);
                }
        }
}







//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "chan_form.h"
#include "sh_all_can.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TChannelForm *ChannelForm;
//---------------------------------------------------------------------------
__fastcall TChannelForm::TChannelForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TChannelForm::RefreshEdits(TObject *Sender,TChannel *ch)
{
        IDEdit->Value = ch->ChannelID;
        CaptionEdit->Text = ch->ChannelCaption;
        TypeEdit->ItemIndex = ch->ChannelType;
        DimensionEdit->ItemIndex = ch->Dimension;
        KindDimEdit->ItemIndex = ch->DimensionKind;
        MINDimEdit->Text = FloatToStr(ch->MIN_DIM);
        MAXDimEdit->Text = FloatToStr(ch->MAX_DIM);
        ActColorEdit->Selected = ch->col;
        NActColorEdit->Selected = ch->col_nact;        
        FPGAEdit->Value = ch->NFPGA;
        NChannelEdit->Value = ch->n_channel;

        aEdit->Text = FloatToStr(ch->a);
        bEdit->Text = FloatToStr(ch->b);
        kEdit->Text = FloatToStr(ch->k);
        impEdit->Text = FloatToStr(ch->imp);
        KTransEdit->Text = FloatToStr(ch->k_trans);
}

void __fastcall TChannelForm::OkButtonClick(TObject *Sender)
{
        if (MINDimEdit->Text == "") MINDimEdit->Text = "0";
        if (MAXDimEdit->Text == "") MAXDimEdit->Text = "0";

        if (aEdit->Text == "") aEdit->Text = "0";
        if (bEdit->Text == "") bEdit->Text = "0";
        if (kEdit->Text == "") kEdit->Text = "0";
        if (impEdit->Text == "") impEdit->Text = "0";

        // если аналоговый
        if (TypeEdit->ItemIndex == 1)
        {
                impEdit->Text = "0";
        }
        else // если счетчик
        if (TypeEdit->ItemIndex == 2)
        {
                aEdit->Text = "0";
                bEdit->Text = "0";
                kEdit->Text = "0";
        }
        else
        {
                aEdit->Text = "0";
                bEdit->Text = "0";
                kEdit->Text = "0";
                impEdit->Text = "0";
        }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "gist.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGistForm *GistForm;
//---------------------------------------------------------------------------
__fastcall TGistForm::TGistForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TGistForm::FormClose(TObject *Sender, TCloseAction &Action)
{
        VagonChart->Series[0]->DataSource = NULL;
        VagonChart->Series[0]->XLabelsSource = "";
        VagonChart->Series[0]->YValues->ValueSource = "";

        RTPChart->Series[0]->DataSource = NULL;
        RTPChart->Series[0]->XLabelsSource = "";
        RTPChart->Series[0]->YValues->ValueSource = "";

        CPChart->Series[0]->DataSource = NULL;
        CPChart->Series[0]->XLabelsSource = "";
        CPChart->Series[0]->YValues->ValueSource = "";

        PChart->Series[0]->DataSource = NULL;
        PChart->Series[0]->XLabelsSource = "";
        PChart->Series[0]->YValues->ValueSource = "";

        MHChart->Series[0]->DataSource = NULL;
        MHChart->Series[0]->XLabelsSource = "";
        MHChart->Series[0]->YValues->ValueSource = "";

        LChart->Series[0]->DataSource = NULL;
        LChart->Series[0]->XLabelsSource = "";
        LChart->Series[0]->YValues->ValueSource = "";
}
//---------------------------------------------------------------------------

void __fastcall TGistForm::CloseButtonClick(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------


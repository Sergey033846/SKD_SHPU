//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "add_shed.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAddShedForm *AddShedForm;
//---------------------------------------------------------------------------
__fastcall TAddShedForm::TAddShedForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAddShedForm::FormShow(TObject *Sender)
{
        TimeEdit->SetFocus();        
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "add_node.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAddNodeForm *AddNodeForm;
//---------------------------------------------------------------------------
__fastcall TAddNodeForm::TAddNodeForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAddNodeForm::FormShow(TObject *Sender)
{
        XEdit->SetFocus();        
}
//---------------------------------------------------------------------------

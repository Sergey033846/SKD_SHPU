//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "add_user.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAddUserForm *AddUserForm;
//---------------------------------------------------------------------------
__fastcall TAddUserForm::TAddUserForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAddUserForm::FormShow(TObject *Sender)
{
        NameEdit->SetFocus();        
}
//---------------------------------------------------------------------------




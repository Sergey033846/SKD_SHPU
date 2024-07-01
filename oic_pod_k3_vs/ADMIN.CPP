//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "admin.h"
#include "main_unit.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAdminForm *AdminForm;
//---------------------------------------------------------------------------
__fastcall TAdminForm::TAdminForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
 
void __fastcall TAdminForm::Button1Click(TObject *Sender)
{
        MainForm->Show();
}
//---------------------------------------------------------------------------



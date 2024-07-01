//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "comm_conf.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCommConfigForm *CommConfigForm;
//---------------------------------------------------------------------------
__fastcall TCommConfigForm::TCommConfigForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

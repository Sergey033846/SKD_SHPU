//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "prg_unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TProgressForm *ProgressForm;
//---------------------------------------------------------------------------
__fastcall TProgressForm::TProgressForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

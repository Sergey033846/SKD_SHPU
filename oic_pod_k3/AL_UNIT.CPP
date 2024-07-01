//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "al_unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAlarmForm *AlarmForm;
//---------------------------------------------------------------------------
__fastcall TAlarmForm::TAlarmForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

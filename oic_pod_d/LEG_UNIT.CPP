//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "leg_unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLegendForm *LegendForm;
//---------------------------------------------------------------------------
__fastcall TLegendForm::TLegendForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TLegendForm::BitBtn1Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "warn_unit.h"
#include "leg_unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TWarningForm *WarningForm;
//---------------------------------------------------------------------------
__fastcall TWarningForm::TWarningForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TWarningForm::BitBtn2Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------
void __fastcall TWarningForm::FormCreate(TObject *Sender)
{
        StringGrid->Cells[0][0] = "№";
        StringGrid->Cells[1][0] = "Время";
        StringGrid->Cells[2][0] = "Событие";
}
//---------------------------------------------------------------------------
void __fastcall TWarningForm::BitBtn1Click(TObject *Sender)
{
        LegendForm->ShowModal();        
}
//---------------------------------------------------------------------------


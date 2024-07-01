//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "rep_unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TReportForm *ReportForm;
//---------------------------------------------------------------------------
__fastcall TReportForm::TReportForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "test_unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTestForm *TestForm;
//---------------------------------------------------------------------------
__fastcall TTestForm::TTestForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TTestForm::CheckBox13Click(TObject *Sender)
{
        if (CheckBox13->Checked) CheckBox14->Checked = false;
        else CheckBox14->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TTestForm::CheckBox14Click(TObject *Sender)
{
        if (CheckBox14->Checked) CheckBox13->Checked = false;
        else CheckBox13->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TTestForm::CheckBox15Click(TObject *Sender)
{
        if (CheckBox15->Checked) CheckBox16->Checked = false;
        else CheckBox16->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TTestForm::CheckBox16Click(TObject *Sender)
{
        if (CheckBox16->Checked) CheckBox15->Checked = false;
        else CheckBox15->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TTestForm::CheckBox27Click(TObject *Sender)
{
        if (CheckBox27->Checked) CheckBox28->Checked = false;
        else CheckBox28->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TTestForm::CheckBox28Click(TObject *Sender)
{
        if (CheckBox28->Checked) CheckBox27->Checked = false;
        else CheckBox27->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TTestForm::CheckBox25Click(TObject *Sender)
{
        if (CheckBox25->Checked) CheckBox26->Checked = false;
        else CheckBox26->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TTestForm::CheckBox26Click(TObject *Sender)
{
        if (CheckBox26->Checked) CheckBox25->Checked = false;
        else CheckBox25->Checked = true;
}
//---------------------------------------------------------------------------


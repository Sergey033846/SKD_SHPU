//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "hard_test.h"
#include "main_unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
THardTestForm *HardTestForm;
//---------------------------------------------------------------------------
__fastcall THardTestForm::THardTestForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall THardTestForm::Button1Click(TObject *Sender)
{
        MainForm->LSB = StrToFloat(Edit1->Text) / 1000000.0;
        MainForm->G = StrToInt(Edit2->Text);

        Memo1->Lines->Clear();
        Memo2->Lines->Clear();
        Memo3->Lines->Clear();
        Memo4->Lines->Clear();

        Close();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "pause.h"
#include "main_unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPauseForm *PauseForm;
//---------------------------------------------------------------------------
__fastcall TPauseForm::TPauseForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPauseForm::BitBtn1Click(TObject *Sender)
{
        TWarning *war = new TWarning;
        war->warning_id = 0;
        war->date_time = Date()+Time();

        if (CheckBox1->Checked) war->warning_id += 0x01;
        if (CheckBox2->Checked) war->warning_id += 0x02;
        if (CheckBox3->Checked) war->warning_id += 0x04;
        if (CheckBox4->Checked) war->warning_id += 0x08;
        if (CheckBox5->Checked) war->warning_id += 0x10;
        if (CheckBox6->Checked) war->warning_id += 0x20;
        if (CheckBox7->Checked) war->warning_id += 0x40;

        if (war->warning_id != 0) MainForm->war_list->Add(war);

        Close();        
}
//---------------------------------------------------------------------------
void __fastcall TPauseForm::BitBtn2Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------
void __fastcall TPauseForm::FormShow(TObject *Sender)
{
        CheckBox1->Checked = false;
        CheckBox2->Checked = false;
        CheckBox3->Checked = false;
        CheckBox4->Checked = false;
        CheckBox5->Checked = false;
        CheckBox6->Checked = false;
        CheckBox7->Checked = false;
}
//---------------------------------------------------------------------------

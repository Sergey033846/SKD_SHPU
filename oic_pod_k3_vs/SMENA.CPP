//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "smena.h"
#include "main_unit.h"
#include "passw.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSmenaForm *SmenaForm;
//---------------------------------------------------------------------------
__fastcall TSmenaForm::TSmenaForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSmenaForm::Button1Click(TObject *Sender)
{
        MainForm->name_mash = ComboBox1->Text;
        MainForm->name_master = ComboBox2->Text;

        bool p_mash,p_mast;
        p_mash = p_mast = false;

        // проверка пароля машиниста
        for (int i=0; i<MainForm->users->count; i++)
        {
                if (strcmp((*MainForm->users)[i]->name,MainForm->name_mash.c_str()) == 0 &&
                    strcmp((*MainForm->users)[i]->tab_order,Edit1->Text.c_str()) == 0)
                {
                        p_mash = true;
                        break;
                }
        }
        // проверка пароля мастера
        for (int i=0; i<MainForm->users->count; i++)
        {
                if (strcmp((*MainForm->users)[i]->name,MainForm->name_master.c_str()) == 0 &&
                    strcmp((*MainForm->users)[i]->tab_order,Edit2->Text.c_str()) == 0)
                {
                        p_mast = true;
                        break;
                }
        }
        //-------------------------

        if (p_mash && p_mast) // login succesfully
        {
                ModalResult = mrOk;
        }
        else // login fail
        {
                MessageDlg("Неправильное имя или пароль!",
                        mtWarning, TMsgDlgButtons() << mbCancel, 0);
                ModalResult = mrCancel;
        }
}
//---------------------------------------------------------------------------
void __fastcall TSmenaForm::FormShow(TObject *Sender)
{
        ComboBox1->Clear();
        ComboBox2->Clear();

        for (int i=0; i<MainForm->users->count; i++)
        {
                if (strcmp((*MainForm->users)[i]->group,"машинист") == 0)
                {
                        ComboBox1->Items->Add((*MainForm->users)[i]->name);
                }
                else
                if (strcmp((*MainForm->users)[i]->group,"мастер") == 0)
                {
                        ComboBox2->Items->Add((*MainForm->users)[i]->name);
                }
        }

        ComboBox1->ItemIndex = -1; ComboBox1->Text = "";
        ComboBox2->ItemIndex = -1; ComboBox2->Text = "";

        Edit1->Text = "";        Edit2->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TSmenaForm::SpeedButton1Click(TObject *Sender)
{
        if (PasswForm->ShowModal() == mrOk)
        {
                Edit1->Text = PasswForm->Edit1->Text;
        }
}
//---------------------------------------------------------------------------

void __fastcall TSmenaForm::SpeedButton2Click(TObject *Sender)
{
        if (PasswForm->ShowModal() == mrOk)
        {
                Edit2->Text = PasswForm->Edit1->Text;
        }
}
//---------------------------------------------------------------------------


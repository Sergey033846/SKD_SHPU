//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "smena.h"
#include "main_unit.h"
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
void __fastcall TSmenaForm::Button2Click(TObject *Sender)
{
//        Close();
}
//---------------------------------------------------------------------------
void __fastcall TSmenaForm::Button1Click(TObject *Sender)
{
/*        AnsiString sys_dir;
        sys_dir = MainForm->sys_param->SysDir;

        AnsiString name_mash,name_master;

        name_mash = ComboBox1->Text;
        name_master = ComboBox2->Text;

        if (ComboBox1->ItemIndex == -1)
        {
                if (name_mash != "")
                {
                        ComboBox1->Items->Add(name_mash);
                        ComboBox1->Items->SaveToFile(sys_dir+"\\mashinist.txt");
                }
        }
        if (ComboBox2->ItemIndex == -1)
        {
                if (name_master != "")
                {
                        ComboBox2->Items->Add(name_master);
                        ComboBox2->Items->SaveToFile(sys_dir+"\\master.txt");
                }
        }

        strcpy(MainForm->archive->MashinistName,name_mash.c_str());
        strcpy(MainForm->archive->MasterName,name_master.c_str());*/
}
//---------------------------------------------------------------------------
void __fastcall TSmenaForm::FormShow(TObject *Sender)
{
        AnsiString sys_dir;
        sys_dir = MainForm->sys_param->SysDir;
        ComboBox1->Items->LoadFromFile(sys_dir+"\\mashinist.txt");
        ComboBox2->Items->LoadFromFile(sys_dir+"\\master.txt");

        ComboBox1->ItemIndex = -1; ComboBox1->Text = "";
        ComboBox2->ItemIndex = -1; ComboBox2->Text = "";
}
//---------------------------------------------------------------------------


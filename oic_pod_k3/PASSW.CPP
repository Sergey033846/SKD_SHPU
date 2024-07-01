//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "passw.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPasswForm *PasswForm;
//---------------------------------------------------------------------------
__fastcall TPasswForm::TPasswForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPasswForm::FormShow(TObject *Sender)
{
        Edit1->Text = "";        
}
//---------------------------------------------------------------------------
void __fastcall TPasswForm::Button1Click(TObject *Sender)
{
        Edit1->Text = Edit1->Text+"1";       
}
//---------------------------------------------------------------------------
void __fastcall TPasswForm::Button2Click(TObject *Sender)
{
        Edit1->Text = Edit1->Text+"2";
}
//---------------------------------------------------------------------------
void __fastcall TPasswForm::Button3Click(TObject *Sender)
{
        Edit1->Text = Edit1->Text+"3";
}
//---------------------------------------------------------------------------
void __fastcall TPasswForm::Button4Click(TObject *Sender)
{
        Edit1->Text = Edit1->Text+"4";
}
//---------------------------------------------------------------------------
void __fastcall TPasswForm::Button7Click(TObject *Sender)
{
        Edit1->Text = Edit1->Text+"7";
}
//---------------------------------------------------------------------------
void __fastcall TPasswForm::Button5Click(TObject *Sender)
{
        Edit1->Text = Edit1->Text+"5";
}
//---------------------------------------------------------------------------
void __fastcall TPasswForm::Button6Click(TObject *Sender)
{
        Edit1->Text = Edit1->Text+"6";
}
//---------------------------------------------------------------------------
void __fastcall TPasswForm::Button8Click(TObject *Sender)
{
        Edit1->Text = Edit1->Text+"8";
}
//---------------------------------------------------------------------------
void __fastcall TPasswForm::Button9Click(TObject *Sender)
{
        Edit1->Text = Edit1->Text+"9";
}
//---------------------------------------------------------------------------
void __fastcall TPasswForm::Button10Click(TObject *Sender)
{
        Edit1->Text = Edit1->Text+"0";
}
//---------------------------------------------------------------------------
void __fastcall TPasswForm::SpeedButton1Click(TObject *Sender)
{
        Edit1->Text = "";        
}
//---------------------------------------------------------------------------

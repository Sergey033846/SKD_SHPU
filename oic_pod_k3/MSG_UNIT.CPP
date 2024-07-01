//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "msg_unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMsgForm *MsgForm;
//---------------------------------------------------------------------------
__fastcall TMsgForm::TMsgForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMsgForm::BitBtn1Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------


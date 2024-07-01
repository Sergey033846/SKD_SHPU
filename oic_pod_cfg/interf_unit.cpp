//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "interf_unit.h"
#include "admin.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TInterfForm *InterfForm;
//---------------------------------------------------------------------------
__fastcall TInterfForm::TInterfForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TInterfForm::FormShow(TObject *Sender)
{
        AdminForm->sys_param->Load();

        ColorBox1->Selected = AdminForm->sys_param->repRGcol;
        ComboBox1->ItemIndex = AdminForm->sys_param->repRGlinestyle;

        ColorBox2->Selected = AdminForm->sys_param->repRLcol;
        ComboBox2->ItemIndex = AdminForm->sys_param->repRLlinestyle;

        ColorBox3->Selected = AdminForm->sys_param->repRRcol;
        ComboBox3->ItemIndex = AdminForm->sys_param->repRRlinestyle;

        ColorBox4->Selected = AdminForm->sys_param->repROcol;
        ComboBox4->ItemIndex = AdminForm->sys_param->repROlinestyle;

        ColorBox6->Selected = AdminForm->sys_param->repPCcol;
        ComboBox5->ItemIndex = AdminForm->sys_param->repPClinestyle;

        ColorBox5->Selected = AdminForm->sys_param->repDIAGcol;

        WColorBox->Selected = AdminForm->sys_param->wcolor;
        SColorBox->Selected = AdminForm->sys_param->scolor;
        ZColorBox->Selected = AdminForm->sys_param->zcolor;
        FColorBox->Selected = AdminForm->sys_param->fcolor;
        BkColorBox->Selected = AdminForm->sys_param->bkcolor;
}
//---------------------------------------------------------------------------





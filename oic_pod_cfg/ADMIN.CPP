//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "set_date.h"

#include "admin.h"
#include "shed_unit.h"
#include "koef_unit.h"
#include "chan_form.h"
#include "sh_all_can.h"

#include "param_unit.h"
#include "etalon.h"

#include "interf_unit.h"
#include "reg_form.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAdminForm *AdminForm;
//---------------------------------------------------------------------------
__fastcall TAdminForm::TAdminForm(TComponent* Owner)
        : TForm(Owner)
{
        sys_dir = ExtractFilePath(Application->ExeName);

        ChannelList = new TVariantList <TChannel>;
        ChannelList->ReadFromFile(sys_dir+"channels.dat");

        sys_koef = new TSysKoef;
        sys_koef->Load();

        sys_param = new TSysParams(sys_dir+"options.ini");
        sys_param->Load();

        users = new TLogRecList();
        sheduler = new TSheduler(sys_dir+"shedule.dat");
}
//---------------------------------------------------------------------------
void __fastcall TAdminForm::N9Click(TObject *Sender)
{
        ShedForm->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TAdminForm::BitBtn4Click(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

void __fastcall TAdminForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        delete users;
        delete sys_param;
        delete sheduler;

        delete ChannelList;
        delete sys_koef;
}
//---------------------------------------------------------------------------

void __fastcall TAdminForm::BitBtn1Click(TObject *Sender)
{
        UserForm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TAdminForm::BitBtn2Click(TObject *Sender)
{
        ShedForm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TAdminForm::BitBtn3Click(TObject *Sender)
{
        if (InterfForm->ShowModal() == mrOk)
        {
                sys_param->repRGcol = InterfForm->ColorBox1->Selected;
                sys_param->repRGlinestyle = InterfForm->ComboBox1->ItemIndex;

                sys_param->repRLcol = InterfForm->ColorBox2->Selected;
                sys_param->repRLlinestyle = InterfForm->ComboBox2->ItemIndex;

                sys_param->repRRcol = InterfForm->ColorBox3->Selected;
                sys_param->repRRlinestyle = InterfForm->ComboBox3->ItemIndex;

                sys_param->repROcol = InterfForm->ColorBox4->Selected;
                sys_param->repROlinestyle = InterfForm->ComboBox4->ItemIndex;

                sys_param->repPCcol = InterfForm->ColorBox6->Selected;
                sys_param->repPClinestyle = InterfForm->ComboBox5->ItemIndex;

                sys_param->repDIAGcol = InterfForm->ColorBox5->Selected;

                sys_param->wcolor = InterfForm->WColorBox->Selected;
                sys_param->scolor = InterfForm->SColorBox->Selected;
                sys_param->zcolor = InterfForm->ZColorBox->Selected;
                sys_param->fcolor = InterfForm->FColorBox->Selected;
                sys_param->bkcolor = InterfForm->BkColorBox->Selected;                                

                sys_param->Save();
        }        
}
//---------------------------------------------------------------------------

void __fastcall TAdminForm::BitBtn5Click(TObject *Sender)
{
        ParamForm->ShowModal();        
}
//---------------------------------------------------------------------------

void __fastcall TAdminForm::BitBtn6Click(TObject *Sender)
{
        EtalonForm->ShowModal();        
}
//---------------------------------------------------------------------------

void __fastcall TAdminForm::BitBtn7Click(TObject *Sender)
{
        KoefForm->ShowModal();        
}
//---------------------------------------------------------------------------


void __fastcall TAdminForm::BitBtn8Click(TObject *Sender)
{
        ShowChannelForm->ShowModal();        
}
//---------------------------------------------------------------------------

void __fastcall TAdminForm::BitBtn9Click(TObject *Sender)
{
        SetDateTimeForm->ShowModal();        
}
//---------------------------------------------------------------------------


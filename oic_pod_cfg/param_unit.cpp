//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "param_unit.h"
#include "admin.h"
#include "dir_unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TParamForm *ParamForm;
//---------------------------------------------------------------------------
__fastcall TParamForm::TParamForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TParamForm::OkButtonClick(TObject *Sender)
{
        AdminForm->sys_param->RudNameIndex = RudNameEdit->ItemIndex;
        AdminForm->sys_param->StvolNameIndex = StvolNameEdit->ItemIndex;
//        strcpy(MainForm->sys_param->RudName,RudNameEdit->Text.c_str());
//        strcpy(MainForm->sys_param->StvolName,StvolNameEdit->Text.c_str());

        AdminForm->sys_param->RefrTime = RefrTimeEdit->Value;
        AdminForm->sys_param->ArcTime = ArcTimeEdit->Value;

        AdminForm->sys_param->DayTime1 = DayTime1->Value;
        AdminForm->sys_param->DayTime2 = DayTime2->Value;
        AdminForm->sys_param->NightTime1 = NightTime1->Value;
        AdminForm->sys_param->NightTime2 = NightTime2->Value;

        strcpy(AdminForm->sys_param->ArcDir,ArcDirEdit->Text.c_str());
        strcpy(AdminForm->sys_param->SysDir,SysDirEdit->Text.c_str());
        strcpy(AdminForm->sys_param->MediaDir,MediaDirEdit->Text.c_str());

        AdminForm->sys_param->comm.COM_PORT_ID = COMRadioGroup->ItemIndex;
        AdminForm->sys_param->comm.DIAL_MODE = DIALRadioGroup->ItemIndex;

        AdminForm->sys_param->dt_peresm = StrToInt(dtPeresmEdit->Text);

        strcpy(AdminForm->sys_param->RARArcDir,RARDirEdit->Text.c_str());
        strcpy(AdminForm->sys_param->FlashDir,FlashDirEdit->Text.c_str());        

        AdminForm->sys_param->Save();
}
//---------------------------------------------------------------------------
void __fastcall TParamForm::FormShow(TObject *Sender)
{
        AdminForm->sys_param->Load();

        RudNameEdit->ItemIndex = AdminForm->sys_param->RudNameIndex;
        StvolNameEdit->ItemIndex = AdminForm->sys_param->StvolNameIndex;

        RefrTimeEdit->Value = AdminForm->sys_param->RefrTime;
        ArcTimeEdit->Value = AdminForm->sys_param->ArcTime;

        DayTime1->Value = AdminForm->sys_param->DayTime1;
        DayTime2->Value = AdminForm->sys_param->DayTime2;
        NightTime1->Value = AdminForm->sys_param->NightTime1;
        NightTime2->Value = AdminForm->sys_param->NightTime2;

        ArcDirEdit->Text = AdminForm->sys_param->ArcDir;
        SysDirEdit->Text = AdminForm->sys_param->SysDir;
        MediaDirEdit->Text = AdminForm->sys_param->MediaDir;

        COMRadioGroup->ItemIndex = AdminForm->sys_param->comm.COM_PORT_ID;
        DIALRadioGroup->ItemIndex = AdminForm->sys_param->comm.DIAL_MODE;

        dtPeresmEdit->Text = IntToStr(AdminForm->sys_param->dt_peresm);

        RARDirEdit->Text = AdminForm->sys_param->RARArcDir;
        FlashDirEdit->Text = AdminForm->sys_param->FlashDir;        
}
//---------------------------------------------------------------------------
// установка архивного каталога
void __fastcall TParamForm::SpeedButton1Click(TObject *Sender)
{
        if (DirForm->ShowModal() == mrOk)
        {
                ArcDirEdit->Text = DirForm->DirectoryListBox1->Directory;
        }
}
//---------------------------------------------------------------------------
// установка системного каталога
void __fastcall TParamForm::SpeedButton2Click(TObject *Sender)
{
        if (DirForm->ShowModal() == mrOk)
        {
                SysDirEdit->Text = DirForm->DirectoryListBox1->Directory;
        }
}
//---------------------------------------------------------------------------
// установка мультимедийного каталога
void __fastcall TParamForm::SpeedButton3Click(TObject *Sender)
{
        if (DirForm->ShowModal() == mrOk)
        {
                MediaDirEdit->Text = DirForm->DirectoryListBox1->Directory;
        }
}
//---------------------------------------------------------------------------

void __fastcall TParamForm::SpeedButton4Click(TObject *Sender)
{
        if (DirForm->ShowModal() == mrOk)
        {
                RARDirEdit->Text = DirForm->DirectoryListBox1->Directory;
        }
}
//---------------------------------------------------------------------------

void __fastcall TParamForm::SpeedButton5Click(TObject *Sender)
{
        if (DirForm->ShowModal() == mrOk)
        {
                FlashDirEdit->Text = DirForm->DirectoryListBox1->Directory;
        }
}
//---------------------------------------------------------------------------


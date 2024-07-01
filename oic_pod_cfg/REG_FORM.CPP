//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "reg_form.h"
#include "admin.h"
#include "add_user.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TUserForm *UserForm;
//---------------------------------------------------------------------------
__fastcall TUserForm::TUserForm(TComponent* Owner)
        : TForm(Owner)
{
}

void TUserForm::ClearRows()
{
        for (int i = 1; i < StringGrid->RowCount; i++)
                StringGrid->Rows[i]->Clear();
}

//---------------------------------------------------------------------------
void __fastcall TUserForm::FormCreate(TObject *Sender)
{
        StringGrid->Cells[0][0] = "ID";
        StringGrid->Cells[1][0] = "Имя";
        StringGrid->Cells[2][0] = "Категория";
        StringGrid->Cells[3][0] = "Пароль";
}
//---------------------------------------------------------------------------
// save
void __fastcall TUserForm::BitBtn3Click(TObject *Sender)
{
        AdminForm->users->WriteToFile(AdminForm->sys_dir+"users.dat");
}
//---------------------------------------------------------------------------
// delete
void __fastcall TUserForm::BitBtn2Click(TObject *Sender)
{
   if (AdminForm->users->count != 0)
   {
        if (MessageDlg("Удалить запись?",
               mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
        {
                int r = StringGrid->Row;

                if (r <= AdminForm->users->count)
                {
                        AdminForm->users->Del(r-1);

                        ClearRows();

                        StringGrid->RowCount = 2;

                        for (int i=0; i<AdminForm->users->count; i++)
                        {
                                RefreshRow((*AdminForm->users)[i],i+1);
                                StringGrid->RowCount++;
                        }
                }
        }
   }
}
//---------------------------------------------------------------------------
// close
void __fastcall TUserForm::BitBtn4Click(TObject *Sender)
{
        Close();
}

void TUserForm::RefreshRow(TLoginRecord *rec,int rr)
{
        StringGrid->Cells[0][rr] = IntToStr(rr);
        StringGrid->Cells[1][rr] = rec->name;
        StringGrid->Cells[2][rr] = rec->group;
        StringGrid->Cells[3][rr] = rec->tab_order;                        
}

//---------------------------------------------------------------------------
// add user
void __fastcall TUserForm::BitBtn1Click(TObject *Sender)
{
        AddUserForm->Caption = "Добавление пользователя";
        AddUserForm->NameEdit->Text = "";
        AddUserForm->GroupEdit->ItemIndex = -1;
        AddUserForm->GroupEdit->Text = "";
        AddUserForm->PasswordEdit->Text = "";

        if (AddUserForm->ShowModal() == mrOk)
        {
                TLoginRecord *rec = new TLoginRecord();
                strcpy(rec->name,AddUserForm->NameEdit->Text.c_str());
                strcpy(rec->group,AddUserForm->GroupEdit->Text.c_str());
                strcpy(rec->tab_order,AddUserForm->PasswordEdit->Text.c_str());
                AdminForm->users->Add(rec);

                short rr = StringGrid->RowCount-1;
                StringGrid->RowCount++;
                RefreshRow(rec,rr);
        }
}
//---------------------------------------------------------------------------
void __fastcall TUserForm::FormShow(TObject *Sender)
{
        AdminForm->users->DestroyList();
        AdminForm->users->ReadFromFile(AdminForm->sys_dir+"users.dat");

        ClearRows();

        StringGrid->RowCount = 2;

        for (int i=0; i<AdminForm->users->count; i++)
        {
                RefreshRow((*AdminForm->users)[i],i+1);
                StringGrid->RowCount++;
        }
}
//---------------------------------------------------------------------------
void __fastcall TUserForm::StringGridDblClick(TObject *Sender)
{
        AddUserForm->Caption = "Редактирование";

        int r = StringGrid->Row;

        if (AdminForm->users->count >= r)
        {
                TLoginRecord *rec = (*AdminForm->users)[r-1];
                AddUserForm->NameEdit->Text = rec->name;
                AddUserForm->GroupEdit->Text = rec->group;
                AddUserForm->PasswordEdit->Text = rec->tab_order;

                if (AddUserForm->ShowModal() == mrOk)
                {
                        strcpy(rec->name,AddUserForm->NameEdit->Text.c_str());
                        strcpy(rec->group,AddUserForm->GroupEdit->Text.c_str());
                        strcpy(rec->tab_order,AddUserForm->PasswordEdit->Text.c_str());

                        RefreshRow(rec,r);
                }
        }
}
//---------------------------------------------------------------------------

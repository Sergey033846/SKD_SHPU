//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "etalon.h"
#include "edit_etalon.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEtalonForm *EtalonForm;
//---------------------------------------------------------------------------
__fastcall TEtalonForm::TEtalonForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
// загрузка выбранной диаграммы
void __fastcall TEtalonForm::Button9Click(TObject *Sender)
{
        // РГ
        if (RadioGroup2->ItemIndex == 0)
        {
                EditEtalonForm->Caption = "Редактирование диаграммы РГ ";
                EditEtalonForm->mode_id = 0;
                EditEtalonForm->f_name = "d_rg_";
        }
        // РЛ
        if (RadioGroup2->ItemIndex == 1)
        {
                EditEtalonForm->Caption = "Редактирование диаграммы РЛ ";
                EditEtalonForm->mode_id = 1;
                EditEtalonForm->f_name = "d_rl_";
        }
        // РР
        if (RadioGroup2->ItemIndex == 2)
        {
                EditEtalonForm->Caption = "Редактирование диаграммы РР ";
                EditEtalonForm->mode_id = 2;
                EditEtalonForm->f_name = "d_rr_";
        }
        // РО
        if (RadioGroup2->ItemIndex == 3)
        {
                EditEtalonForm->Caption = "Редактирование диаграммы РО ";
                EditEtalonForm->mode_id = 3;
                EditEtalonForm->f_name = "d_ro_";                
        }

        // разгон
        if (RadioGroup1->ItemIndex == 0)
        {
                EditEtalonForm->Caption = EditEtalonForm->Caption+"(разгон)";
                EditEtalonForm->speed_id = 0;
                EditEtalonForm->f_name = EditEtalonForm->f_name+"r.dia";
        }
        // торможение
        if (RadioGroup1->ItemIndex == 1)
        {
                EditEtalonForm->speed_id = 1;
                EditEtalonForm->Caption = EditEtalonForm->Caption+"(торможение)";
                EditEtalonForm->f_name = EditEtalonForm->f_name+"t.dia";                
        }

        EditEtalonForm->ShowModal();
}
//---------------------------------------------------------------------------
// закрыть
void __fastcall TEtalonForm::Button10Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------


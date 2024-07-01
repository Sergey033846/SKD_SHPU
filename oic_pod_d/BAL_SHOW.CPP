//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "bal_show.h"
#include "bal_par.h"
#include "gist.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TBalRepForm *BalRepForm;
//---------------------------------------------------------------------------
__fastcall TBalRepForm::TBalRepForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TBalRepForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        Query1->Active = false;
}
//---------------------------------------------------------------------------
// гистограммы
void __fastcall TBalRepForm::GistButtonClick(TObject *Sender)
{
        bool by_smena,by_day,by_month,by_quarter,by_halfyear,by_year,by_stvol,by_rudnik;
        bool by_vagon,by_mh,by_tp,by_l,by_p,by_cp;

        by_vagon = BalParForm->CheckBox1->Checked;
        by_mh = BalParForm->CheckBox2->Checked;
        by_tp = BalParForm->CheckBox3->Checked;
        by_l = BalParForm->CheckBox4->Checked;
        by_p = BalParForm->CheckBox5->Checked;
        by_cp = BalParForm->CheckBox6->Checked;
        //------------------------------------------------------
        by_smena = BalParForm->CheckBox7->Checked;
        by_day = BalParForm->CheckBox8->Checked;
        by_month = BalParForm->CheckBox9->Checked;
        by_quarter = BalParForm->CheckBox10->Checked;
        by_halfyear = BalParForm->CheckBox11->Checked;
        by_year = BalParForm->CheckBox12->Checked;
        by_stvol = BalParForm->CheckBox13->Checked;
        by_rudnik = BalParForm->CheckBox14->Checked;
//---------------------------------------------------------
        GistForm->VagonChart->Visible = by_vagon;
        GistForm->RTPChart->Visible = by_tp;
        GistForm->CPChart->Visible = by_cp;
        GistForm->PChart->Visible = by_p;
        GistForm->MHChart->Visible = by_mh;
        GistForm->LChart->Visible = by_l;

        AnsiString XFieldName = "";
        AnsiString BName = "Гистограммы баланса [";

        if (by_rudnik) XFieldName = "Rudnik";
        if (by_stvol) XFieldName = "Stvol";
        if (by_year) XFieldName = "Year111";
        if (by_halfyear) XFieldName = "HalfYear111";
        if (by_quarter) XFieldName = "Quarter111";
        if (by_month) XFieldName = "Month111";
        if (by_day) XFieldName = "Day111";
        if (by_smena) XFieldName = "Smena111";

        if (by_rudnik) BName += " Рудник";
        if (by_stvol) BName += " Ствол";
        if (by_year) BName += " Год";
        if (by_halfyear) BName += " Полугодие";
        if (by_quarter) BName += " Квартал";
        if (by_month) BName += " Месяц";
        if (by_day) BName += " День";
        if (by_smena) BName += " Смена";

        BName += " ]";

        if (by_vagon)
        {
                GistForm->VagonChart->Series[0]->DataSource = Query1;
                GistForm->VagonChart->Series[0]->XLabelsSource = XFieldName;
                GistForm->VagonChart->Series[0]->YValues->ValueSource = "SUM OF Vagon";
        }
        if (by_tp)
        {
                GistForm->RTPChart->Series[0]->DataSource = Query1;
                GistForm->RTPChart->Series[0]->XLabelsSource = XFieldName;
                GistForm->RTPChart->Series[0]->YValues->ValueSource = "SUM OF RTP";
        }
        if (by_cp)
        {
                GistForm->CPChart->Series[0]->DataSource = Query1;
                GistForm->CPChart->Series[0]->XLabelsSource = XFieldName;
                GistForm->CPChart->Series[0]->YValues->ValueSource = "SUM OF CP";
        }
        if (by_p)
        {
                GistForm->PChart->Series[0]->DataSource = Query1;
                GistForm->PChart->Series[0]->XLabelsSource = XFieldName;
                GistForm->PChart->Series[0]->YValues->ValueSource = "SUM OF P";
        }
        if (by_mh)
        {
                GistForm->MHChart->Series[0]->DataSource = Query1;
                GistForm->MHChart->Series[0]->XLabelsSource = XFieldName;
                GistForm->MHChart->Series[0]->YValues->ValueSource = "SUM OF MH";
        }
        if (by_l)
        {
                GistForm->LChart->Series[0]->DataSource = Query1;
                GistForm->LChart->Series[0]->XLabelsSource = XFieldName;
                GistForm->LChart->Series[0]->YValues->ValueSource = "SUM OF L";
        }
//---------------------------------------------------------
        GistForm->Caption = BName;
        GistForm->ShowModal();
//---------------------------------------------------------
}

short TBalRepForm::GetVisibleColumn(short n)
{
        short res = -1;
        for (int i=0; i<DBGrid2->Columns->Count; i++)
        {
                if (DBGrid2->Columns->Items[i]->Visible) res++;
                if (res == n) break;
        }
        return res;
}

//---------------------------------------------------------------------------
// Excel
void __fastcall TBalRepForm::BitBtn1Click(TObject *Sender)
{
        Variant App,Sh,vCell;

        // если Excel запущен - подключиться к нему
        try
        {
                App = Variant::GetActiveObject("Excel.Application");
        } catch(...)
        {
                // Excel не запущен - запустить его
                try { App = Variant::CreateObject("Excel.Application"); } catch (...)
                        {
                              Application->MessageBox("Невозможно открыть Microsoft Excel!"
                                        "Возможно Excel не установлен на компьютере.","Ошибка",MB_OK+MB_ICONERROR);
                        }
        }

        App.OlePropertyGet("WorkBooks").OleProcedure("add");
        Sh = App.OlePropertyGet("WorkSheets",1);

        short x=1,y=1,n;
        AnsiString fcapt;
        for (int i=0; i<Query1->FieldCount; i++)
        {
                vCell = Sh.OlePropertyGet("Cells").OlePropertyGet("Item",y,x+i);
                vCell.OlePropertyGet("Font").OlePropertySet("Name","Arial");
                vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
                vCell.OlePropertySet("HorizontalAlignment",-4108);
                vCell.OlePropertySet("VerticalAlignment",-4108);

                if (Query1->Fields->Fields[i]->FieldName == "Rudnik") fcapt = "Рудник";
                else
                if (Query1->Fields->Fields[i]->FieldName == "Stvol") fcapt = "Ствол";
                else
                if (Query1->Fields->Fields[i]->FieldName == "Year111") fcapt = "Год";
                else
                if (Query1->Fields->Fields[i]->FieldName == "HalfYear111") fcapt = "Полугодие";
                else
                if (Query1->Fields->Fields[i]->FieldName == "Quarter111") fcapt = "Квартал";
                else
                if (Query1->Fields->Fields[i]->FieldName == "Month111") fcapt = "Месяц";
                else
                if (Query1->Fields->Fields[i]->FieldName == "Day111") fcapt = "День";
                else
                if (Query1->Fields->Fields[i]->FieldName == "Smena111") fcapt = "Смена";
                else
                if (Query1->Fields->Fields[i]->FieldName == "SUM OF Vagon") fcapt = "Выдано";
                else
                if (Query1->Fields->Fields[i]->FieldName == "SUM OF RTP") fcapt = "РТП";
                else
                if (Query1->Fields->Fields[i]->FieldName == "SUM OF CP") fcapt = "Циклов";
                else
                if (Query1->Fields->Fields[i]->FieldName == "SUM OF P") fcapt = "Эл.энергия";
                else
                if (Query1->Fields->Fields[i]->FieldName == "SUM OF MH") fcapt = "Моточасы";
                else
                if (Query1->Fields->Fields[i]->FieldName == "SUM OF L") fcapt = "Путь";

                vCell.OlePropertySet("Value",fcapt.c_str());
        }

        DBGrid2->Hide();
        Query1->First();
        y = 2;
        for (int i=0; i<Query1->RecordCount; i++)
        {
                for (int j=0; j<Query1->FieldCount; j++)
                {
                   switch (Query1->Fields->Fields[j]->DataType)
                   {
                      case ftInteger :
                                       vCell = Sh.OlePropertyGet("Cells").OlePropertyGet("Item",y+i,x+j);
                                       vCell.OlePropertySet("Value",Query1->Fields->Fields[j]->AsInteger);
                                       break;
                      case ftFloat:
                                       vCell = Sh.OlePropertyGet("Cells").OlePropertyGet("Item",y+i,x+j);
                                       vCell.OlePropertySet("Value",Query1->Fields->Fields[j]->AsFloat);
                                       break;
                      case ftString:
                                       vCell = Sh.OlePropertyGet("Cells").OlePropertyGet("Item",y+i,x+j);
                                       vCell.OlePropertySet("Value",Query1->Fields->Fields[j]->AsString.c_str());
                                       break;
                   }
                   vCell.OlePropertySet("HorizontalAlignment",-4108);
                   vCell.OlePropertySet("VerticalAlignment",-4108);
                   if (Query1->Fields->Fields[j]->FieldName == "Rudnik" ||
                         Query1->Fields->Fields[j]->FieldName == "Stvol")
                   {
                        vCell.OlePropertySet("ColumnWidth",20);
                   }
                }

                Query1->Next();
        }
        DBGrid2->Show();
        //-----------------------------------------
        if (!App.IsEmpty()) App.OlePropertySet("Visible",true);

        Sh.Clear();
        App.Clear();
}
//---------------------------------------------------------------------------


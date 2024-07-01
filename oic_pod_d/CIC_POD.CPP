//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "cic_pod.h"
#include "arc_unit.h"
#include "sm_rep.h"
#include "rep_unit2.h"
#include "objects.cpp"
#include "rep_i_unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSmCiklForm *SmCiklForm;
//---------------------------------------------------------------------------
__fastcall TSmCiklForm::TSmCiklForm(TComponent* Owner)
        : TForm(Owner)
{
        cikl = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TSmCiklForm::FormCreate(TObject *Sender)
{
        StringGrid->Cells[0][0] = "№";
        StringGrid->Cells[1][0] = "Направление";
        StringGrid->Cells[2][0] = "Начало";
        StringGrid->Cells[3][0] = "Длительность";
        StringGrid->Cells[4][0] = "Пауза";
        StringGrid->Cells[5][0] = "Режим";
        StringGrid->Cells[6][0] = "Вагон";
        StringGrid->Cells[7][0] = "Эл.энергия";
        StringGrid->Cells[8][0] = "L,м";
}
//---------------------------------------------------------------------------
void __fastcall TSmCiklForm::FormShow(TObject *Sender)
{
        RepButton1->Enabled = false;
        RepButton2->Enabled = false;
        RepButton3->Enabled = false;
        RepButton4->Enabled = false;
        RepButton5->Enabled = false;
//        RepButton4->Enabled = false;
  //      RepButton5->Enabled = false;

        is_cikl_loaded = false;
        cikl = new TArcRecList();
        cikl1 = new TArcRecList();

        if (SmRepForm->cikl_list->count > 0)
        {
                LoadButon->Enabled = true;
                StringGrid->RowCount = SmRepForm->cikl_list->count+1;
        }
        else
        {
                LoadButon->Enabled = false;
                StringGrid->RowCount = 2;
        }

        TCiklPod *tc;
        Word hour,min,sec,msec;
        for (int i=0; i<SmRepForm->cikl_list->count; i++)
        {
                tc = (*SmRepForm->cikl_list)[i];

                StringGrid->Cells[0][i+1] = IntToStr(i+1);
                if (tc->vector == 1) StringGrid->Cells[1][i+1] = "подъем";
                if (tc->vector == -1) StringGrid->Cells[1][i+1] = "спуск";

                DecodeTime(tc->fbeg,hour,min,sec,msec);
                StringGrid->Cells[2][i+1] = IntToStr(hour)+":"+IntToStr(min)+":"+IntToStr(sec);

                StringGrid->Cells[3][i+1] = IntToStr(tc->rhour)+":"+IntToStr(tc->rmin)+":"+IntToStr(tc->rsec);

                StringGrid->Cells[4][i+1] = IntToStr(tc->phour)+":"+IntToStr(tc->pmin)+":"+IntToStr(tc->psec);

                if (tc->mode == 0) StringGrid->Cells[5][i+1] = "Груз";
                else
                if (tc->mode == 1) StringGrid->Cells[5][i+1] = "Люди";
                else
                if (tc->mode == 2) StringGrid->Cells[5][i+1] = "Ревизия";
                else
                if (tc->mode == 3) StringGrid->Cells[5][i+1] = "Оборудование";

                if (tc->vagon) StringGrid->Cells[6][i+1] = "1";
                else StringGrid->Cells[6][i+1] = "0";

                StringGrid->Cells[7][i+1] = FloatToStrF(tc->P,ffFixed,8,2);

                StringGrid->Cells[8][i+1] = FloatToStrF(tc->L,ffFixed,8,2);
        }
}
//---------------------------------------------------------------------------
// Закрыть
void __fastcall TSmCiklForm::BitBtn5Click(TObject *Sender)
{
        StringGrid->RowCount = 2;
        for (int i=0; i<StringGrid->ColCount; i++) StringGrid->Cells[i][1] = "";

        is_cikl_loaded = false;
        cikl->DestroyList();
        delete cikl;
        cikl1->DestroyList();
        delete cikl1;
}
//---------------------------------------------------------------------------
// загрузка цикла подъема
void __fastcall TSmCiklForm::LoadButonClick(TObject *Sender)
{
   // если цикл уже загружен
   if (is_cikl_loaded)
   {
        cikl->DestroyList();
        cikl1->DestroyList();
        is_cikl_loaded = false;
   }

   if (is_cikl_loaded == false)
   {
        short cikl_id =  StringGrid->Row-1;

//        short ch_id_cp = GetChannelByNameAndDimension(ArcForm->ChannelList,"ЦП",tdtNONE)->ChannelID;
  //      short ch_n_cp = GetChannelByNameAndDimension(ArcForm->ChannelList,"N_CP",tdtNONE)->ChannelID;

        TArchiveRecord *rec,*rec1;

        // загрузка данных
/*        for (int i=0; i<arh->count_arch_rec; i++)
        {
                rec = arh->LoadItem(ArcForm->ChannelList,i);

                if ( (*rec->ChannelDataList)[ch_id_cp]->analog == cikl_id &&
                                (*rec->ChannelDataList)[ch_n_cp]->analog == 1.0 )
                {
                        cikl->Add(rec);
                }
        }*/

        int cbeg = 0; int cend = 0;

/*        // поиск начальной метки
        for (int i=1; i<arh->count_arch_rec; i++)
        {
                rec = arh->LoadItem(ArcForm->ChannelList,i);

                if ( (*rec->ChannelDataList)[ch_id_cp]->analog == cikl_id &&
                        (*rec->ChannelDataList)[ch_n_cp]->analog == 1.0 )
                {
                        cbeg = i-1;
                        break;
                }
        }
        for (int i=cbeg-1; i>=0; i--)
        {
                rec = arh->LoadItem(ArcForm->ChannelList,i);

                if ( (*rec->ChannelDataList)[ArcForm->idIst]->analog == 0.0 )
                {
                        cbeg = i;
                        break;
                }
        }
        //---------------------------------------

        // поиск метки завершения цикла
        for (int i=arh->count_arch_rec-1; i>cbeg; i--)
        {
                rec = arh->LoadItem(ArcForm->ChannelList,i);

                if ( (*rec->ChannelDataList)[ch_id_cp]->analog == cikl_id &&
                        (*rec->ChannelDataList)[ch_n_cp]->analog == 1.0 )
                {
                        cend = i;
                        break;
                }
        }
        for (int i=cend+1; i<arh->count_arch_rec; i++)
        {
                rec = arh->LoadItem(ArcForm->ChannelList,i);

                if ( (*rec->ChannelDataList)[ArcForm->idIst]->analog == 0.0 )
                {
                        cend = i;
                        break;
                }
        }
        //---------------------------------------
*/
        // формирование цикла
        cbeg = (*SmRepForm->cikl_list)[cikl_id]->begr;
        cend = (*SmRepForm->cikl_list)[cikl_id]->endr;
        for (int i=cbeg; i<=cend; i++)
        {
                rec = arh->LoadItem(ArcForm->ChannelList,i);
                cikl->Add(rec);
        }

        if (cikl_id != SmRepForm->cikl_list->count-1)
        {
                cbeg = (*SmRepForm->cikl_list)[cikl_id+1]->begr;
                cend = (*SmRepForm->cikl_list)[cikl_id+1]->endr;
                for (int i=cbeg; i<=cend; i++)
                {
                        rec = arh->LoadItem(ArcForm->ChannelList,i);
                        cikl1->Add(rec);
                }
        }

        is_cikl_loaded = true;
        StatusBar1->Panels->Items[0]->Text = "Загружен №:"+IntToStr(cikl_id+1);
        RepButton1->Enabled = true;
        RepButton2->Enabled = true;
        RepButton3->Enabled = true;
        RepButton4->Enabled = true;
        RepButton5->Enabled = true;                
//        RepButton4->Enabled = true;
  //      RepButton5->Enabled = true;
   }
}
//---------------------------------------------------------------------------
// Отчет по Iст
void __fastcall TSmCiklForm::RepButton1Click(TObject *Sender)
{
        RepIstIdtForm->Caption = "Токовая диаграмма цикла подъема (Iст)";
        ReportForm2->QRLabel1->Caption = "Токовая диаграмма цикла подъема";
        ReportForm2->QuickRep1->ReportTitle = ReportForm2->QRLabel1->Caption;

        //--------
        RepIstIdtForm->diag_rect1 = RepIstIdtForm->Image1->ClientRect;

        TPoint pk;
        pk.x = 5;
        pk.y = RepIstIdtForm->Image1->ClientHeight-5;
        int log_x = 1;   // минута
        int log_y = 100; // Ампер
        RepIstIdtForm->ks1 = new TKoordSystem(RepIstIdtForm->Image1,RepIstIdtForm->diag_rect1,pk,log_x,log_y);
        RepIstIdtForm->ks1->bk_col = clWhite;
        RepIstIdtForm->ks1->log_koord.x = 0;
        RepIstIdtForm->ks1->log_koord.y = 0;
        RepIstIdtForm->ks1->koef.kx = 512;
        RepIstIdtForm->ks1->koef.ky = 90;
        RepIstIdtForm->ks1->col = clGreen;
        RepIstIdtForm->ks1->text_col = clBlack;
        RepIstIdtForm->ks1->draw_setka = RepIstIdtForm->SetkaCheckBox->Checked;
        RepIstIdtForm->ks1->draw_numbers_y = RepIstIdtForm->YCheckBox->Checked;
        RepIstIdtForm->ks1->draw_numbers_x = RepIstIdtForm->XCheckBox->Checked;        
        RepIstIdtForm->ks1->draw_kslines = true;
        RepIstIdtForm->diag1 = new TDiagram(RepIstIdtForm->ks1,ArcForm->ChannelList);
        RepIstIdtForm->diag1->col = ArcForm->sys_param->repDIAGcol;

        short ch_Ist_id = GetChannelByNameAndDimension(ArcForm->ChannelList,"Iст",tdtI)->ChannelID;

        int st_msec;
        Word hour,min,sec,msec;
        for (int i=0; i<cikl->count; i++)
        {
                if (i==0)
                {
                        DecodeTime((*cikl)[0]->date_time,hour,min,sec,msec);
                        st_msec = hour*3600*1000+min*60*1000+sec*1000+msec;
                }

                TLogPoint *lp = new TLogPoint;

                DecodeTime((*cikl)[i]->date_time,hour,min,sec,msec);
                int x_msec = hour*3600*1000+min*60*1000+sec*1000+msec;

                lp->x = (x_msec-st_msec)/(60*1000.0);
                lp->y = (*(*cikl)[i]->ChannelDataList)[ch_Ist_id]->analog;
                RepIstIdtForm->diag1->lp_list->Add(lp);
        }

        RepIstIdtForm->ks1->DrawKoordSystem();
        RepIstIdtForm->diag1->RedrawWithOutNodes();
        RepIstIdtForm->diag1->Redraw();

        //--------
        RepIstIdtForm->freq_id = 1;        

        RepIstIdtForm->ShowModal();
}
//---------------------------------------------------------------------------
// Iдт
void __fastcall TSmCiklForm::RepButton2Click(TObject *Sender)
{
        RepIstIdtForm->Caption = "Токовая диаграмма динамического торможения (Iдт)";
        ReportForm2->QRLabel1->Caption = "Токовая диаграмма динамического торможения";
        ReportForm2->QuickRep1->ReportTitle = ReportForm2->QRLabel1->Caption;        
        //--------
        
        RepIstIdtForm->diag_rect1 = RepIstIdtForm->Image1->ClientRect;

        TPoint pk;
        pk.x = 5;
        pk.y = RepIstIdtForm->Image1->ClientHeight-5;
        int log_x = 1;   // минута
        int log_y = 100; // Ампер
        RepIstIdtForm->ks1 = new TKoordSystem(RepIstIdtForm->Image1,RepIstIdtForm->diag_rect1,pk,log_x,log_y);
        RepIstIdtForm->ks1->bk_col = clWhite;
        RepIstIdtForm->ks1->log_koord.x = 0;
        RepIstIdtForm->ks1->log_koord.y = 0;
        RepIstIdtForm->ks1->koef.kx = 512;
        RepIstIdtForm->ks1->koef.ky = 90;
        RepIstIdtForm->ks1->col = clGreen;
        RepIstIdtForm->ks1->text_col = clBlack;
        RepIstIdtForm->ks1->draw_setka = RepIstIdtForm->SetkaCheckBox->Checked;
        RepIstIdtForm->ks1->draw_numbers_y = RepIstIdtForm->YCheckBox->Checked;
        RepIstIdtForm->ks1->draw_numbers_x = RepIstIdtForm->XCheckBox->Checked;
        RepIstIdtForm->ks1->draw_kslines = true;
        RepIstIdtForm->diag1 = new TDiagram(RepIstIdtForm->ks1,ArcForm->ChannelList);
        RepIstIdtForm->diag1->col = ArcForm->sys_param->repDIAGcol;

        short ch_Idt_id = GetChannelByNameAndDimension(ArcForm->ChannelList,"Iдт",tdtI)->ChannelID;

        int st_msec;
        Word hour,min,sec,msec;
        for (int i=0; i<cikl->count; i++)
        {
                if (i==0)
                {
                        DecodeTime((*cikl)[0]->date_time,hour,min,sec,msec);
                        st_msec = hour*3600*1000+min*60*1000+sec*1000+msec;
                }

                TLogPoint *lp = new TLogPoint;

                DecodeTime((*cikl)[i]->date_time,hour,min,sec,msec);
                int x_msec = hour*3600*1000+min*60*1000+sec*1000+msec;

                lp->x = (x_msec-st_msec)/(60*1000.0);
                lp->y = (*(*cikl)[i]->ChannelDataList)[ch_Idt_id]->analog;
                RepIstIdtForm->diag1->lp_list->Add(lp);
        }

        RepIstIdtForm->ks1->DrawKoordSystem();
        RepIstIdtForm->diag1->RedrawWithOutNodes();
        RepIstIdtForm->diag1->Redraw();
        //--------

        RepIstIdtForm->freq_id = 1;

        RepIstIdtForm->ShowModal();        
}
//---------------------------------------------------------------------------
void __fastcall TSmCiklForm::RepButton3Click(TObject *Sender)
{
        RepIstIdtForm->Caption = "Диаграмма цикла подъема по напряжению (Uтг)";
        ReportForm2->QRLabel1->Caption = "Диаграмма цикла подъема по напряжению";
        ReportForm2->QuickRep1->ReportTitle = ReportForm2->QRLabel1->Caption;

        //--------
        RepIstIdtForm->diag_rect1 = RepIstIdtForm->Image1->ClientRect;

        TPoint pk;
        pk.x = 5;
        pk.y = RepIstIdtForm->Image1->ClientHeight/2-5;
        int log_x = 1;   // минута
        int log_y = 30; // Вольт
        RepIstIdtForm->ks1 = new TKoordSystem(RepIstIdtForm->Image1,RepIstIdtForm->diag_rect1,pk,log_x,log_y);
        RepIstIdtForm->ks1->bk_col = clWhite;
        RepIstIdtForm->ks1->log_koord.x = 0;
        RepIstIdtForm->ks1->log_koord.y = 0;
        RepIstIdtForm->ks1->koef.kx = 512;
        RepIstIdtForm->ks1->koef.ky = 90;
        RepIstIdtForm->ks1->col = clGreen;
        RepIstIdtForm->ks1->text_col = clBlack;
        RepIstIdtForm->ks1->draw_setka = RepIstIdtForm->SetkaCheckBox->Checked;
        RepIstIdtForm->ks1->draw_numbers_y = RepIstIdtForm->YCheckBox->Checked;
        RepIstIdtForm->ks1->draw_numbers_x = RepIstIdtForm->XCheckBox->Checked;
        RepIstIdtForm->ks1->draw_kslines = true;
        RepIstIdtForm->diag1 = new TDiagram(RepIstIdtForm->ks1,ArcForm->ChannelList);
        RepIstIdtForm->diag1->col = ArcForm->sys_param->repDIAGcol;

        short ch_Utg_id = GetChannelByNameAndDimension(ArcForm->ChannelList,"Uтг",tdtU)->ChannelID;

        int st_msec;
        Word hour,min,sec,msec;
        for (int i=0; i<cikl->count; i++)
        {
                if (i==0)
                {
                        DecodeTime((*cikl)[0]->date_time,hour,min,sec,msec);
                        st_msec = hour*3600*1000+min*60*1000+sec*1000+msec;
                }

                TLogPoint *lp = new TLogPoint;

                DecodeTime((*cikl)[i]->date_time,hour,min,sec,msec);
                int x_msec = hour*3600*1000+min*60*1000+sec*1000+msec;

                lp->x = (x_msec-st_msec)/(60*1000.0);
                lp->y = (*(*cikl)[i]->ChannelDataList)[ch_Utg_id]->analog;
                RepIstIdtForm->diag1->lp_list->Add(lp);
        }

        RepIstIdtForm->ks1->DrawKoordSystem();
        RepIstIdtForm->diag1->RedrawWithOutNodes();
        RepIstIdtForm->diag1->Redraw();

        //--------

        RepIstIdtForm->freq_id = 1;

        RepIstIdtForm->ShowModal();
}
//---------------------------------------------------------------------------
// Uтг+РКЗ
void __fastcall TSmCiklForm::RepButton4Click(TObject *Sender)
{
        RepIstIdtForm->Caption = "Диаграмма состояния предохранительных дверей и стопоров в клети";
        ReportForm2->QRLabel1->Caption = "Диаграмма состояния предохранительных дверей и стопоров в клети";
        ReportForm2->QuickRep1->ReportTitle = ReportForm2->QRLabel1->Caption;

        //--------
        TRect r = RepIstIdtForm->Image1->ClientRect;
        r.Bottom -= 50;
        RepIstIdtForm->diag_rect1 = r;

        TRect r2;
        r2.Left = r.Left;
        r2.Right = r.Right;
        r2.Top = r.Bottom+5;
        r2.Bottom = r.Bottom+50;

        TPoint pk;
        pk.x = 5;
        pk.y = RepIstIdtForm->Image1->ClientHeight/2-5;
        int log_x = 1;   // час
        int log_y = 50; // Вольт
        RepIstIdtForm->ks1 = new TKoordSystem(RepIstIdtForm->Image1,RepIstIdtForm->diag_rect1,pk,log_x,log_y);
        RepIstIdtForm->ks1->bk_col = clWhite;
        RepIstIdtForm->ks1->log_koord.x = 0;
        RepIstIdtForm->ks1->log_koord.y = 0;
        RepIstIdtForm->ks1->koef.kx = 512;
        RepIstIdtForm->ks1->koef.ky = 90;
        RepIstIdtForm->ks1->col = clGreen;
        RepIstIdtForm->ks1->text_col = clBlack;
        RepIstIdtForm->ks1->draw_setka = RepIstIdtForm->SetkaCheckBox->Checked;
        RepIstIdtForm->ks1->draw_numbers_y = RepIstIdtForm->YCheckBox->Checked;
        RepIstIdtForm->ks1->draw_numbers_x = RepIstIdtForm->XCheckBox->Checked;
        RepIstIdtForm->ks1->draw_kslines = true;
        RepIstIdtForm->diag1 = new TDiagram(RepIstIdtForm->ks1,ArcForm->ChannelList);
        RepIstIdtForm->diag1->col = ArcForm->sys_param->repDIAGcol;

        TPoint pk2;
        pk2.x = 5;
        pk2.y = 40;
        int log_x2 = 1;   // час
        int log_y2 = 1;
        RepIstIdtForm->ks2 = new TKoordSystem(RepIstIdtForm->Image1,r2,pk2,log_x2,log_y2);
        RepIstIdtForm->ks2->bk_col = clWhite;
        RepIstIdtForm->ks2->log_koord.x = 0;
        RepIstIdtForm->ks2->log_koord.y = 0;
        RepIstIdtForm->ks2->koef.kx = 512;
        RepIstIdtForm->ks2->koef.ky = 30;
        RepIstIdtForm->ks2->col = clGreen;
        RepIstIdtForm->ks2->text_col = clBlack;
        RepIstIdtForm->ks2->draw_setka = RepIstIdtForm->SetkaCheckBox->Checked;
        RepIstIdtForm->ks2->draw_numbers_y = false;
        RepIstIdtForm->ks2->draw_numbers_x = RepIstIdtForm->XCheckBox->Checked;
        RepIstIdtForm->ks2->draw_kslines = true;
        RepIstIdtForm->diag2 = new TDiagram(RepIstIdtForm->ks2,ArcForm->ChannelList);
        RepIstIdtForm->diag2->col = clBlack;

        int st_msec;
        Word hour,min,sec,msec;
        for (int i=0; i<cikl->count; i++)
        {
                if (i==0)
                {
                        DecodeTime((*cikl)[0]->date_time,hour,min,sec,msec);
                        st_msec = hour*3600*1000+min*60*1000+sec*1000+msec;
                }

                TLogPoint *lp = new TLogPoint;

                DecodeTime((*cikl)[i]->date_time,hour,min,sec,msec);
                int x_msec = hour*3600*1000+min*60*1000+sec*1000+msec;

                lp->x = (x_msec-st_msec)/(60*1000.0);
                lp->y = (*(*cikl)[i]->ChannelDataList)[ArcForm->idUtg]->analog;
                RepIstIdtForm->diag1->lp_list->Add(lp);

                TLogPoint *lp2 = new TLogPoint;
                lp2->x = lp->x;
                lp2->y = (*(*cikl)[i]->ChannelDataList)[ArcForm->idRKZon]->diskret;
                RepIstIdtForm->diag2->lp_list->Add(lp2);
        }
        for (int i=0; i<cikl1->count; i++)
        {
                TLogPoint *lp = new TLogPoint;

                DecodeTime((*cikl1)[i]->date_time,hour,min,sec,msec);
                int x_msec = hour*3600*1000+min*60*1000+sec*1000+msec;

                lp->x = (x_msec-st_msec)/(60*1000.0);
                lp->y = (*(*cikl1)[i]->ChannelDataList)[ArcForm->idUtg]->analog;
                RepIstIdtForm->diag1->lp_list->Add(lp);

                TLogPoint *lp2 = new TLogPoint;
                lp2->x = lp->x;
                lp2->y = (*(*cikl1)[i]->ChannelDataList)[ArcForm->idRKZon]->diskret;
                RepIstIdtForm->diag2->lp_list->Add(lp2);
        }

        RepIstIdtForm->ks1->DrawKoordSystem();
        RepIstIdtForm->diag1->RedrawWithOutNodes();
        RepIstIdtForm->diag1->Redraw();

        RepIstIdtForm->ks2->DrawKoordSystem();
        RepIstIdtForm->diag2->RedrawWithOutNodes();
        RepIstIdtForm->diag2->Redraw();        

        //--------

        RepIstIdtForm->freq_id = 1;

        RepIstIdtForm->ShowModal();
}
//---------------------------------------------------------------------------
// Uтг+Iст+Iдт
void __fastcall TSmCiklForm::RepButton5Click(TObject *Sender)
{
        RepIstIdtForm->Caption = "Сводная диаграмма цикла подъема";
        ReportForm2->QRLabel1->Caption = "Сводная диаграмма цикла подъема";
        ReportForm2->QuickRep1->ReportTitle = ReportForm2->QRLabel1->Caption;

        //--------
        RepIstIdtForm->diag_rect1 = RepIstIdtForm->Image1->ClientRect;

        TPoint pk;
        pk.x = 5;
        pk.y = RepIstIdtForm->Image1->ClientHeight/2-5;
        int log_x = 1;   // минута
        int log_y = 30; // Вольт
        RepIstIdtForm->ks1 = new TKoordSystem(RepIstIdtForm->Image1,RepIstIdtForm->diag_rect1,pk,log_x,log_y);
        RepIstIdtForm->ks1->bk_col = clWhite;
        RepIstIdtForm->ks1->log_koord.x = 0;
        RepIstIdtForm->ks1->log_koord.y = 0;
        RepIstIdtForm->ks1->koef.kx = 512;
        RepIstIdtForm->ks1->koef.ky = 90;
        RepIstIdtForm->ks1->col = clGreen;
        RepIstIdtForm->ks1->text_col = clBlack;
        RepIstIdtForm->ks1->draw_setka = RepIstIdtForm->SetkaCheckBox->Checked;
        RepIstIdtForm->ks1->draw_numbers_y = RepIstIdtForm->YCheckBox->Checked;
        RepIstIdtForm->ks1->draw_numbers_x = RepIstIdtForm->XCheckBox->Checked;
        RepIstIdtForm->ks1->draw_kslines = true;
        RepIstIdtForm->diag1 = new TDiagram(RepIstIdtForm->ks1,ArcForm->ChannelList);
        RepIstIdtForm->diag1->col = clGreen;
        RepIstIdtForm->diag2 = new TDiagram(RepIstIdtForm->ks1,ArcForm->ChannelList);
        RepIstIdtForm->diag2->col = clRed;
        RepIstIdtForm->diag3 = new TDiagram(RepIstIdtForm->ks1,ArcForm->ChannelList);
        RepIstIdtForm->diag3->col = clBlue;

        int st_msec;
        Word hour,min,sec,msec;
        for (int i=0; i<cikl->count; i++)
        {
                if (i==0)
                {
                        DecodeTime((*cikl)[0]->date_time,hour,min,sec,msec);
                        st_msec = hour*3600*1000+min*60*1000+sec*1000+msec;
                }

                TLogPoint *lp = new TLogPoint;

                DecodeTime((*cikl)[i]->date_time,hour,min,sec,msec);
                int x_msec = hour*3600*1000+min*60*1000+sec*1000+msec;

                lp->x = (x_msec-st_msec)/(60*1000.0);
                lp->y = (*(*cikl)[i]->ChannelDataList)[ArcForm->idUtg]->analog;
                RepIstIdtForm->diag1->lp_list->Add(lp);

                TLogPoint *lp2 = new TLogPoint;
                lp2->x = lp->x;
                lp2->y = (*(*cikl)[i]->ChannelDataList)[ArcForm->idIst]->analog;
                RepIstIdtForm->diag2->lp_list->Add(lp2);

                TLogPoint *lp3 = new TLogPoint;
                lp3->x = lp->x;
                lp3->y = (*(*cikl)[i]->ChannelDataList)[ArcForm->idIdt]->analog;
                RepIstIdtForm->diag3->lp_list->Add(lp3);
        }

        RepIstIdtForm->ks1->DrawKoordSystem();
        RepIstIdtForm->diag1->RedrawWithOutNodes();
        RepIstIdtForm->diag1->Redraw();
        RepIstIdtForm->diag2->RedrawWithOutNodes();
        RepIstIdtForm->diag2->Redraw();
        RepIstIdtForm->diag3->RedrawWithOutNodes();
        RepIstIdtForm->diag3->Redraw();

        //--------

        RepIstIdtForm->freq_id = 1;

        RepIstIdtForm->ShowModal();
}
//---------------------------------------------------------------------------


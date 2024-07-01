//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "arc_unit.h"
#include "warn_unit.h"
#include "sm_rep.h"
#include "rep_unit.h"
#include "rep_unit2.h"
#include "rep_i_unit.h"
#include "cic_pod.h"
#include "diag_rtp.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSmRepForm *SmRepForm;
//---------------------------------------------------------------------------
__fastcall TSmRepForm::TSmRepForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSmRepForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        delete diag1;
        delete diag2;
        delete ks1;
        delete ks2;

        cikl_list->DestroyList();
        delete cikl_list;

        RTP_cikl_list->DestroyList(); //???
        delete RTP_cikl_list;

        war_list->DestroyList();
        delete war_list;
}
//---------------------------------------------------------------------------

void __fastcall TSmRepForm::PrintButtonClick(TObject *Sender)
{
        //------------------------------------------
        ReportForm->DateL->Caption = this->DateL->Caption;
        ReportForm->SmenaL->Caption = this->SmenaL->Caption;
        ReportForm->MashL->Caption = this->MashL->Caption;
        ReportForm->MasterL->Caption = this->MasterL->Caption;
        ReportForm->StvolL->Caption = this->StvolL->Caption;

        ReportForm->VagonL->Caption = this->VagonL->Caption;
        ReportForm->Gor3L->Caption = this->Gor3L->Caption;
        ReportForm->Gor5L->Caption = this->Gor5L->Caption;

        ReportForm->MHL->Caption = this->MHL->Caption;
        ReportForm->TotalL->Caption = this->TotalLL->Caption;
        ReportForm->PL->Caption = this->PL->Caption;

        ReportForm->RTPL->Caption = this->TPL->Caption;
        ReportForm->CPL->Caption = this->CPL->Caption;
        //------------------------------------------

/*        ReportForm->QRImage1->Canvas->CopyRect(ReportForm->QRImage1->ClientRect,
                                                               SmRepForm->Image1->Canvas,
                                                               SmRepForm->Image1->ClientRect);
  */
        SmRepForm->Image1->Picture->SaveToFile("temp.bmp");
        ReportForm->QRImage1->Picture->LoadFromFile("temp.bmp");
        ReportForm->QRImage1->Update();
//        DeleteFile("temp.bmp");
        ReportForm->QuickRep1->Update();

//        ReportForm->QuickRep1->Prepare();
        ReportForm->QuickRep1->PreviewModal();
}
//---------------------------------------------------------------------------

void __fastcall TSmRepForm::CloseButtonClick(TObject *Sender)
{
        DeleteFile(ArcForm->file2del+".arc");
        DeleteFile(ArcForm->file2del+".war");        
        Close();
}
//---------------------------------------------------------------------------

// циклы подъема
void __fastcall TSmRepForm::Button1Click(TObject *Sender)
{
        SmCiklForm->StatusBar1->Panels->Items[0]->Text = "Нет активного цикла";
        SmCiklForm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TSmRepForm::DiagRTPButtonClick(TObject *Sender)
{
        DiagRTPForm->ShowModal();
}
//---------------------------------------------------------------------------
// Uтг
void __fastcall TSmRepForm::Button2Click(TObject *Sender)
{
        RepIstIdtForm->Caption = "Диаграмма работы подъема за смену по напряжению (Uтг)";
        ReportForm2->QRLabel1->Caption = "Диаграмма работы подъема за смену по напряжению";
        ReportForm2->QuickRep1->ReportTitle = ReportForm2->QRLabel1->Caption;

        //--------
        RepIstIdtForm->diag_rect1 = RepIstIdtForm->Image1->ClientRect;

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

        short ch_Utg_id = GetChannelByNameAndDimension(ArcForm->ChannelList,"Uтг",tdtU)->ChannelID;

        int st_msec;
        Word hour,min,sec,msec;
        for (int i=0; i<arh->count_arch_rec; i++)
        {
                TArchiveRecord *rec = arh->LoadItem(ArcForm->ChannelList,i);

                DecodeTime(rec->date_time,hour,min,sec,msec);

                //-----------
                float hour2 = hour + min/60.0;
                float dtper = ArcForm->sys_param->dt_peresm/60.0;

                if (arc_stat->smena_id==0)
                 if (hour2>=ArcForm->sys_param->DayTime1-dtper && hour2 <= ArcForm->sys_param->DayTime1+dtper)
                 {
                 }
                 else
                 {
                        hour = ArcForm->sys_param->DayTime1;
                        min = 0;
                        sec = 0;
                        msec = 0;
                 }
                else
                if (arc_stat->smena_id==1)
                 if (hour2>=ArcForm->sys_param->NightTime1-dtper && hour2 <= ArcForm->sys_param->NightTime1+dtper)
                 {
                 }
                 else
                 {
                        hour = ArcForm->sys_param->NightTime1;
                        min = 0;
                        sec = 0;
                        msec = 0;
                 }
                //-----------
                st_msec = hour*3600*1000+min*60*1000+sec*1000+msec;

                TLogPoint *lp = new TLogPoint;

                DecodeTime(rec->date_time,hour,min,sec,msec);
                if (hour>=0 && hour<=ArcForm->sys_param->NightTime2+1) hour += 24;// после 24:00
                int x_msec = hour*3600*1000+min*60*1000+sec*1000+msec;

                lp->x = (x_msec-st_msec)/(60*60*1000.0);
                lp->y = (*rec->ChannelDataList)[ch_Utg_id]->analog;
                RepIstIdtForm->diag1->lp_list->Add(lp);
        }

        RepIstIdtForm->ks1->DrawKoordSystem();
        RepIstIdtForm->diag1->RedrawWithOutNodes(freq_id);
        RepIstIdtForm->diag1->Redraw();

        //--------

        RepIstIdtForm->freq_id = SmRepForm->freq_id;

        RepIstIdtForm->ShowModal();
}
//---------------------------------------------------------------------------
// Iст
void __fastcall TSmRepForm::Button3Click(TObject *Sender)
{
        RepIstIdtForm->Caption = "Диаграмма работы подъема за смену по току статора (Iст)";
        ReportForm2->QRLabel1->Caption = "Диаграмма работы подъема за смену по току статора";
        ReportForm2->QuickRep1->ReportTitle = ReportForm2->QRLabel1->Caption;

        //--------
        RepIstIdtForm->diag_rect1 = RepIstIdtForm->Image1->ClientRect;

        TPoint pk;
        pk.x = 5;
        pk.y = RepIstIdtForm->Image1->ClientHeight-5;
        int log_x = 1;   // час
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

        int st_msec;
        Word hour,min,sec,msec;
        for (int i=0; i<arh->count_arch_rec; i++)
        {
                TArchiveRecord *rec = arh->LoadItem(ArcForm->ChannelList,i);

                DecodeTime(rec->date_time,hour,min,sec,msec);

                //-----------
                float hour2 = hour + min/60.0;
                float dtper = ArcForm->sys_param->dt_peresm/60.0;

                if (arc_stat->smena_id==0)
                 if (hour2>=ArcForm->sys_param->DayTime1-dtper && hour2 <= ArcForm->sys_param->DayTime1+dtper)
                 {
                 }
                 else
                 {
                        hour = ArcForm->sys_param->DayTime1;
                        min = 0;
                        sec = 0;
                        msec = 0;
                 }
                else
                if (arc_stat->smena_id==1)
                 if (hour2>=ArcForm->sys_param->NightTime1-dtper && hour2 <= ArcForm->sys_param->NightTime1+dtper)
                 {
                 }
                 else
                 {
                        hour = ArcForm->sys_param->NightTime1;
                        min = 0;
                        sec = 0;
                        msec = 0;
                 }
                //-----------
                st_msec = hour*3600*1000+min*60*1000+sec*1000+msec;

                TLogPoint *lp = new TLogPoint;

                DecodeTime(rec->date_time,hour,min,sec,msec);
                if (hour>=0 && hour<=ArcForm->sys_param->NightTime2+1) hour += 24;// после 24:00
                int x_msec = hour*3600*1000+min*60*1000+sec*1000+msec;

                lp->x = (x_msec-st_msec)/(60*60*1000.0);
                lp->y = (*rec->ChannelDataList)[ArcForm->idIst]->analog;
                RepIstIdtForm->diag1->lp_list->Add(lp);
        }

        RepIstIdtForm->ks1->DrawKoordSystem();
        RepIstIdtForm->diag1->RedrawWithOutNodes(freq_id);
        RepIstIdtForm->diag1->Redraw();

        //--------

        RepIstIdtForm->freq_id = SmRepForm->freq_id;

        RepIstIdtForm->ShowModal();
}
//---------------------------------------------------------------------------
// Uтг+РКЗ
void __fastcall TSmRepForm::Button4Click(TObject *Sender)
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
        for (int i=0; i<arh->count_arch_rec; i++)
        {
                TArchiveRecord *rec = arh->LoadItem(ArcForm->ChannelList,i);

                DecodeTime(rec->date_time,hour,min,sec,msec);

                //-----------
                float hour2 = hour + min/60.0;
                float dtper = ArcForm->sys_param->dt_peresm/60.0;

                if (arc_stat->smena_id==0)
                 if (hour2>=ArcForm->sys_param->DayTime1-dtper && hour2 <= ArcForm->sys_param->DayTime1+dtper)
                 {
                 }
                 else
                 {
                        hour = ArcForm->sys_param->DayTime1;
                        min = 0;
                        sec = 0;
                        msec = 0;
                 }
                else
                if (arc_stat->smena_id==1)
                 if (hour2>=ArcForm->sys_param->NightTime1-dtper && hour2 <= ArcForm->sys_param->NightTime1+dtper)
                 {
                 }
                 else
                 {
                        hour = ArcForm->sys_param->NightTime1;
                        min = 0;
                        sec = 0;
                        msec = 0;
                 }
                //-----------
                st_msec = hour*3600*1000+min*60*1000+sec*1000+msec;

                TLogPoint *lp = new TLogPoint;

                DecodeTime(rec->date_time,hour,min,sec,msec);
                if (hour>=0 && hour<=ArcForm->sys_param->NightTime2+1) hour += 24;// после 24:00
                int x_msec = hour*3600*1000+min*60*1000+sec*1000+msec;

                lp->x = (x_msec-st_msec)/(60*60*1000.0);
                lp->y = (*rec->ChannelDataList)[ArcForm->idUtg]->analog;
                RepIstIdtForm->diag1->lp_list->Add(lp);
                //-----------
                TLogPoint *lp2 = new TLogPoint;
                lp2->x = lp->x;
                lp2->y = (*rec->ChannelDataList)[ArcForm->idRKZon]->diskret;
                RepIstIdtForm->diag2->lp_list->Add(lp2);
        }

        RepIstIdtForm->ks1->DrawKoordSystem();
        RepIstIdtForm->diag1->RedrawWithOutNodes(freq_id);
        RepIstIdtForm->diag1->Redraw();

        RepIstIdtForm->ks2->DrawKoordSystem();
        RepIstIdtForm->diag2->RedrawWithOutNodes(freq_id);
        RepIstIdtForm->diag2->Redraw();
        //--------

        RepIstIdtForm->freq_id = SmRepForm->freq_id;

        RepIstIdtForm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TSmRepForm::Button5Click(TObject *Sender)
{
        WarningForm->StringGrid->RowCount = 2;
        for (int i=0; i<WarningForm->StringGrid->ColCount; i++) WarningForm->StringGrid->Cells[i][1] = "";

        TWarning *tc;
        Word hour,min,sec,msec;
        AnsiString warstr;
        for (int i=0; i<war_list->count; i++)
        {
                tc = (*SmRepForm->war_list)[i];

                WarningForm->StringGrid->Cells[0][i+1] = IntToStr(i+1);
                DecodeTime(tc->date_time,hour,min,sec,msec);
                WarningForm->StringGrid->Cells[1][i+1] = IntToStr(hour)+":"+IntToStr(min)+":"+IntToStr(sec);

                warstr = "";
                if (tc->warning_id & 0x01) warstr += "1, ";
                if (tc->warning_id & 0x02) warstr += "2, ";
                if (tc->warning_id & 0x04) warstr += "3, ";
                if (tc->warning_id & 0x08) warstr += "4, ";
                if (tc->warning_id & 0x10) warstr += "5, ";
                if (tc->warning_id & 0x20) warstr += "6, ";
                if (tc->warning_id & 0x40) warstr += "7, ";

                WarningForm->StringGrid->Cells[2][i+1] = warstr;

                WarningForm->StringGrid->RowCount++;
        }

        WarningForm->ShowModal();
}
//---------------------------------------------------------------------------


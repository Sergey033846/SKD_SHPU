//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "diag_rtp.h"
#include "sm_rep.h"
#include "rep_unit2.h"
#include "rep_i_unit.h"
#include "objects.cpp"

#include "arc_unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDiagRTPForm *DiagRTPForm;
//---------------------------------------------------------------------------
__fastcall TDiagRTPForm::TDiagRTPForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDiagRTPForm::FormCreate(TObject *Sender)
{
        StringGrid->Cells[0][0] = "№";
        StringGrid->Cells[1][0] = "Направление";
        StringGrid->Cells[2][0] = "Начало";
        StringGrid->Cells[3][0] = "Длина цикла";
        StringGrid->Cells[4][0] = "Длительность";
        StringGrid->Cells[5][0] = "Режим";
        StringGrid->Cells[6][0] = "Причина";
        StringGrid->Cells[7][0] = "Вагон";
        StringGrid->Cells[8][0] = "a_тп";
        StringGrid->Cells[9][0] = "L_тп";
        StringGrid->Cells[10][0] = "V_тп";
}
//---------------------------------------------------------------------------
void __fastcall TDiagRTPForm::FormShow(TObject *Sender)
{
        if (SmRepForm->RTP_cikl_list->count > 0)
        {
                RepUtgButton->Enabled = true;
                RepIstButton->Enabled = true;
                StringGrid->RowCount = SmRepForm->RTP_cikl_list->count+1;
        }
        else
        {
                RepUtgButton->Enabled = false;
                RepIstButton->Enabled = false;
                StringGrid->RowCount = 2;
        }

        TCiklPod *tc,*tc2;

        TArchiveRecord *rec1,*rec2,*rec;
        float Utg;
        long st_msec,end_msec,totalmsec;
        Word hour,min,sec,msec;
        short mode_id;
        short curr_cikl;
        for (int i=0; i<SmRepForm->RTP_cikl_list->count; i++)
        {
                tc = (*SmRepForm->RTP_cikl_list)[i];
                rec1 = arh->LoadItem(ArcForm->ChannelList,tc->begr);
                rec2 = arh->LoadItem(ArcForm->ChannelList,tc->endr);

                for (int j=tc->begr; j<=tc->endr; j++)
                {
                        rec = arh->LoadItem(ArcForm->ChannelList,j);
                        Utg = (*rec->ChannelDataList)[ArcForm->idUtg]->analog;
                        if (Utg != 0.0) break;
                }

                // направление
                if (Utg < 0.0) tc->vector = -1; // подъем левой клети
                if (Utg > 0.0) tc->vector = 1; // подъем правой клети
                //----------------------

                // время начала цикла
                tc->fbeg = rec1->date_time;
                //----------------------

                //----------------------
                curr_cikl = -1;
                DecodeTime(tc->fbeg,hour,min,sec,msec);
                if (hour>=0 && hour<=ArcForm->sys_param->NightTime2+1) hour += 24;// после 24:00
                totalmsec = hour*3600*1000+min*60*1000+sec*1000+msec;
                for (int j = 0; j<SmRepForm->cikl_list->count; j++)
                {
                        TArchiveRecord *rec5,*rec6;
                        rec5 = arh->LoadItem(ArcForm->ChannelList,(*SmRepForm->cikl_list)[j]->begr);
                        rec6 = arh->LoadItem(ArcForm->ChannelList,(*SmRepForm->cikl_list)[j]->endr);
                        Word hour5,min5,sec5,msec5;
                        Word hour6,min6,sec6,msec6;
                        long totalmsec5,totalmsec6;
                        DecodeTime(rec5->date_time,hour5,min5,sec5,msec5);
                        if (hour5>=0 && hour5<=ArcForm->sys_param->NightTime2+1) hour5 += 24;// после 24:00
                        DecodeTime(rec6->date_time,hour6,min6,sec6,msec6);
                        if (hour6>=0 && hour6<=ArcForm->sys_param->NightTime2+1) hour6 += 24;// после 24:00                        
                        totalmsec5 = hour5*3600*1000+min5*60*1000+sec5*1000+msec5;
                        totalmsec6 = hour6*3600*1000+min6*60*1000+sec6*1000+msec6;

                        if (totalmsec >= totalmsec5 && totalmsec <= totalmsec6)
                        {
                                curr_cikl = j;
                                break;
                        }
                }
                // n Tдв вагон
                if (curr_cikl != -1)
                {
                        tc->n = curr_cikl+1;
                        tc->rhour = (*SmRepForm->cikl_list)[curr_cikl]->rhour;
                        tc->rmin = (*SmRepForm->cikl_list)[curr_cikl]->rmin;
                        tc->rsec = (*SmRepForm->cikl_list)[curr_cikl]->rsec;
                        tc->vagon = (*SmRepForm->cikl_list)[curr_cikl]->vagon;
                }
                //----------------------

                // Tтп
                DecodeTime(tc->fbeg,hour,min,sec,msec);
                if (hour>=0 && hour<=ArcForm->sys_param->NightTime2+1) hour += 24;// после 24:00
                st_msec = hour*3600*1000+min*60*1000+sec*1000+msec;

                DecodeTime(rec2->date_time,hour,min,sec,msec);
                if (hour>=0 && hour<=ArcForm->sys_param->NightTime2+1) hour += 24;// после 24:00
                end_msec = hour*3600*1000+min*60*1000+sec*1000+msec;

                tc->tphour = (end_msec-st_msec)/3600000;
                tc->tpmin = (end_msec-st_msec)/60000-tc->tphour*60;
                tc->tpsec = (end_msec-st_msec)/1000-tc->tphour*3600-tc->tpmin*60;
                //----------------------

                // режим
                if ((*rec1->ChannelDataList)[ArcForm->idRG]->diskret) mode_id = 0;
                if ((*rec1->ChannelDataList)[ArcForm->idRL]->diskret) mode_id = 1;
                if ((*rec1->ChannelDataList)[ArcForm->idRR]->diskret) mode_id = 2;
                if ((*rec1->ChannelDataList)[ArcForm->idRO]->diskret) mode_id = 3;
                tc->mode = mode_id;
                //----------------------

                // причина
                bool is_AV1_on = (*rec->ChannelDataList)[ArcForm->idAV1]->diskret;
                bool is_RVPU_on = (*rec->ChannelDataList)[ArcForm->idRVPU]->diskret;
                bool is_EV21_on = (*rec->ChannelDataList)[ArcForm->idEV21]->diskret;
                bool is_ROKp_on = (*rec->ChannelDataList)[ArcForm->idROKp]->diskret;
                bool is_EV1_on = (*rec->ChannelDataList)[ArcForm->idEV1]->diskret;
                bool is_Y4_on = (*rec->ChannelDataList)[ArcForm->idY4]->diskret;
                bool is_RKT_on = (*rec->ChannelDataList)[ArcForm->idRKT]->diskret;

                if (!is_AV1_on) tc->reason = 1;
                else
                if (!is_RVPU_on) tc->reason = 2;
                else
                if (!is_EV21_on) tc->reason = 3;
                else
                if (!is_ROKp_on) tc->reason = 4;
                else
                if (!is_EV1_on) tc->reason = 5;
                else
                if (!is_Y4_on) tc->reason = 6;
                else
                if (!is_RKT_on) tc->reason = 7;
                //----------------------

                // Vтп
                tc->Vtp = (*rec1->ChannelDataList)[ArcForm->idV]->analog;
                //----------------------

                // Lтп,м
                tc->Ltp = (*rec2->ChannelDataList)[ArcForm->idL]->analog -
                                        (*rec1->ChannelDataList)[ArcForm->idL]->analog;
                //----------------------

                // a тп
                tc->atp = (tc->Vtp*tc->Vtp)/(2*(tc->Ltp-0.3*tc->Vtp));
                //----------------------
        }

        for (int i=0; i<SmRepForm->RTP_cikl_list->count; i++)
        {
                tc = (*SmRepForm->RTP_cikl_list)[i];

                StringGrid->Cells[0][i+1] = tc->n;
                if (tc->vector == 1) StringGrid->Cells[1][i+1] = "подъем";
                if (tc->vector == -1) StringGrid->Cells[1][i+1] = "спуск";

                DecodeTime(tc->fbeg,hour,min,sec,msec);
                StringGrid->Cells[2][i+1] = IntToStr(hour)+":"+IntToStr(min)+":"+IntToStr(sec);

                StringGrid->Cells[3][i+1] = IntToStr(tc->rhour)+":"+IntToStr(tc->rmin)+":"+IntToStr(tc->rsec);

                StringGrid->Cells[4][i+1] = IntToStr(tc->tphour)+":"+IntToStr(tc->tpmin)+":"+IntToStr(tc->tpsec);

                if (tc->mode == 0) StringGrid->Cells[5][i+1] = "Груз";
                else
                if (tc->mode == 1) StringGrid->Cells[5][i+1] = "Люди";
                else
                if (tc->mode == 2) StringGrid->Cells[5][i+1] = "Ревизия";
                else
                if (tc->mode == 3) StringGrid->Cells[5][i+1] = "Оборудование";

                StringGrid->Cells[6][i+1] = IntToStr(tc->reason);

                if (tc->vagon) StringGrid->Cells[7][i+1] = "1";
                else StringGrid->Cells[7][i+1] = "0";

                StringGrid->Cells[8][i+1] = FloatToStrF(tc->atp,ffFixed,8,2);

                StringGrid->Cells[9][i+1] = FloatToStrF(tc->Ltp,ffFixed,8,2);

                StringGrid->Cells[10][i+1] = FloatToStrF(tc->Vtp,ffFixed,8,2);
        }
}
//---------------------------------------------------------------------------
void __fastcall TDiagRTPForm::CloseButtonClick(TObject *Sender)
{
        StringGrid->RowCount = 2;
        for (int i=0; i<StringGrid->ColCount; i++) StringGrid->Cells[i][1] = "";
}
//---------------------------------------------------------------------------
void __fastcall TDiagRTPForm::RepIstButtonClick(TObject *Sender)
{
        curr_diag = StringGrid->Row-1;

        RepIstIdtForm->Caption = "Диаграмма предохранительного торможения по току (Iст)";
        ReportForm2->QRLabel1->Caption = "Токовая диаграмма предохранительного торможения по току";
        ReportForm2->QuickRep1->ReportTitle = ReportForm2->QRLabel1->Caption;

        //--------
        RepIstIdtForm->diag_rect1 = RepIstIdtForm->Image1->ClientRect;

        TPoint pk;
        pk.x = 5;
        pk.y = RepIstIdtForm->Image1->ClientHeight-5;
        int log_x = 1;   // секунда
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

        short ch_Ist_id = ArcForm->idIst;

        int st_msec;
        Word hour,min,sec,msec;

        TCiklPod *curr_RTP = (*SmRepForm->RTP_cikl_list)[curr_diag];

        TArchiveRecord *rec;

        for (int i=curr_RTP->begr; i<=curr_RTP->endr; i++)
        {
                rec = arh->LoadItem(ArcForm->ChannelList,i);

                if (i==curr_RTP->begr)
                {
                        DecodeTime(rec->date_time,hour,min,sec,msec);
                        st_msec = hour*3600*1000+min*60*1000+sec*1000+msec;
                }

                TLogPoint *lp = new TLogPoint;

                DecodeTime(rec->date_time,hour,min,sec,msec);
                int x_msec = hour*3600*1000+min*60*1000+sec*1000+msec;

                lp->x = (x_msec-st_msec)/(1000.0);
                lp->y = (*rec->ChannelDataList)[ch_Ist_id]->analog;
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

void __fastcall TDiagRTPForm::RepUtgButtonClick(TObject *Sender)
{
        curr_diag = StringGrid->Row-1;

        RepIstIdtForm->Caption = "Диаграмма предохранительного торможения по скорости (Uтг)";
        ReportForm2->QRLabel1->Caption = "Диаграмма предохранительного торможения по скорости";
        ReportForm2->QuickRep1->ReportTitle = ReportForm2->QRLabel1->Caption;
        //--------
        RepIstIdtForm->diag_rect1 = RepIstIdtForm->Image1->ClientRect;

        TPoint pk;
        pk.x = 5;
        pk.y = RepIstIdtForm->Image1->ClientHeight/2-5;
        int log_x = 1;   // секунда
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

        short ch_V_id = ArcForm->idUtg;

        int st_msec;
        Word hour,min,sec,msec;

        TCiklPod *curr_RTP = (*SmRepForm->RTP_cikl_list)[curr_diag];

        TArchiveRecord *rec;

        for (int i=curr_RTP->begr; i<=curr_RTP->endr; i++)
        {
                rec = arh->LoadItem(ArcForm->ChannelList,i);

                if (i==curr_RTP->begr)
                {
                        DecodeTime(rec->date_time,hour,min,sec,msec);
                        st_msec = hour*3600*1000+min*60*1000+sec*1000+msec;
                }

                TLogPoint *lp = new TLogPoint;

                DecodeTime(rec->date_time,hour,min,sec,msec);
                int x_msec = hour*3600*1000+min*60*1000+sec*1000+msec;

                lp->x = (x_msec-st_msec)/(1000.0);
                lp->y = (*rec->ChannelDataList)[ch_V_id]->analog;
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


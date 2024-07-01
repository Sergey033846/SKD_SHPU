//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "arc_unit.h"
#include "freq_unit.h"
#include "cic_pod.h"
#include "sm_rep.h"
#include "rep_unit.h"
#include "prg_unit.h"
#include "diag_rtp.h"
#include "bal_par.h"
#include "bal_show.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdPacket"
#pragma link "AdPort"
#pragma link "AdProtcl"
#pragma link "AdPStat"
#pragma link "AdTapi"
#pragma link "ADTrmEmu"
#pragma link "AdTStat"
#pragma link "OoMisc"
#pragma resource "*.dfm"
TArcForm *ArcForm;
//---------------------------------------------------------------------------
__fastcall TArcForm::TArcForm(TComponent* Owner)
        : TForm(Owner)
{
        sys_dir = ExtractFilePath(Application->ExeName);

        sys_param = new TSysParams(sys_dir+"options.ini");
        sys_param->Load();

        users = new TLogRecList();
        sheduler = new TSheduler(sys_dir+"shedule.dat");
        sheduler->Load();

        ChannelList = new TVariantList <TChannel>;
        ChannelList->ReadFromFile(sys_dir+"channels.dat");

        idRG = GetChannelByNameAndDimension(ChannelList,"РГ",tdtON)->ChannelID;
        idRL = GetChannelByNameAndDimension(ChannelList,"РЛ",tdtON)->ChannelID;
        idRR = GetChannelByNameAndDimension(ChannelList,"РР",tdtON)->ChannelID;
        idRO = GetChannelByNameAndDimension(ChannelList,"РО",tdtON)->ChannelID;

        idRPMon = GetChannelByNameAndDimension(ChannelList,"РПМ",tdtON)->ChannelID;
        idRPMoff = GetChannelByNameAndDimension(ChannelList,"РПМ",tdtOFF)->ChannelID;
        idRKZon = GetChannelByNameAndDimension(ChannelList,"РКЗ",tdtON)->ChannelID;
        idRKZoff = GetChannelByNameAndDimension(ChannelList,"РКЗ",tdtOFF)->ChannelID;
        idRDZon = GetChannelByNameAndDimension(ChannelList,"РДЗ",tdtON)->ChannelID;
        idRDZoff = GetChannelByNameAndDimension(ChannelList,"РДЗ",tdtOFF)->ChannelID;

        idUtg = GetChannelByNameAndDimension(ChannelList,"Uтг",tdtU)->ChannelID;
        idIst = GetChannelByNameAndDimension(ChannelList,"Iст",tdtI)->ChannelID;
        idIdt = GetChannelByNameAndDimension(ChannelList,"Iдт",tdtI)->ChannelID;
        idV = GetChannelByNameAndDimension(ChannelList,"V",tdtSPEED)->ChannelID;
        idP = GetChannelByNameAndDimension(ChannelList,"P",tdtP)->ChannelID;
        idL = GetChannelByNameAndDimension(ChannelList,"L",tdtNONE)->ChannelID;

        idAV1 = GetChannelByNameAndDimension(ChannelList,"АВ-1",tdtON)->ChannelID;
        idRVPU = GetChannelByNameAndDimension(ChannelList,"РВПУ",tdtON)->ChannelID;
        idEV21 = GetChannelByNameAndDimension(ChannelList,"ЭВ-21",tdtON)->ChannelID;
        idROKp = GetChannelByNameAndDimension(ChannelList,"РОКп",tdtON)->ChannelID;
        idEV1 = GetChannelByNameAndDimension(ChannelList,"ЭВ-1",tdtON)->ChannelID;
        idY4 = GetChannelByNameAndDimension(ChannelList,"У-4",tdtON)->ChannelID;
        idRKT = GetChannelByNameAndDimension(ChannelList,"РК-Т",tdtON)->ChannelID;

        idG3 = GetChannelByNameAndDimension(ChannelList,"ГР3",tdtNONE)->ChannelID;
        idG5 = GetChannelByNameAndDimension(ChannelList,"ГР5",tdtNONE)->ChannelID;

        is_busy = false;
}
//---------------------------------------------------------------------------
// имя файла без расширения
short TArcForm::UnpackArc(AnsiString f_name)
{
   char t[50];
   strcpy(t,f_name.c_str());
   strcat(t,".rar");
   AnsiString file_name = t;

   if (FileExists(file_name))
   {
        STARTUPINFO startin;
        PROCESS_INFORMATION pinfo;

        startin.cb = sizeof(STARTUPINFO);
        startin.lpReserved = NULL;
        startin.lpDesktop = NULL;
        startin.lpTitle = NULL;
        startin.dwFlags = STARTF_USESHOWWINDOW;
        startin.cbReserved2 = 0;
        startin.lpReserved2 = NULL;
        startin.wShowWindow = SW_SHOWMINIMIZED;

        AnsiString ArcDir = sys_param->ArcDir;

        AnsiString cmdLine = sys_param->RARArcDir;
        cmdLine += "\\WinRAR.exe e -o+ ";
        cmdLine += file_name;
        cmdLine += " ";
        cmdLine += ArcDir+"\\";

        CreateProcess(NULL,cmdLine.c_str(),
                      NULL,NULL,FALSE,0,
                      NULL,NULL,&startin,
                      &pinfo);

        char d[50];
        strcpy(d,f_name.c_str());
//        strcat(d,".arc");
        file2del = d;

        return 0;
   }
}

void __fastcall TArcForm::CloseButtonClick(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------
// delete
void __fastcall TArcForm::BitBtn1Click(TObject *Sender)
{
        int r = ListView->ItemIndex;

        if (r != -1)
        {
                if (MessageDlg("Удалить архив?", mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
                {
                        TArchive *arc = (*arc_list)[r];
                        DeleteFile(arc->f_name);
                        arc_list->Del(r);

                        FormShow(Sender);
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TArcForm::FormClose(TObject *Sender, TCloseAction &Action)
{
//-----------------------------
        arc_list->DestroyList();
        delete arc_list;

        arc_stat_list->DestroyList();
        delete arc_stat_list;
//---------------------------
        users->DestroyList();
        delete users;

        delete sys_param;

        sheduler->list->DestroyList();
        delete sheduler;

        ChannelList->DestroyList();
        delete ChannelList;

        ApdTapiDevice1->CancelCall();        
}
//---------------------------------------------------------------------------
void __fastcall TArcForm::RefreshArhs()
{
        arc_list = new TArchiveList;

        arc_stat_list = new TArcStatList();

        ListView->Clear();
        AnsiString dir_name;
        dir_name = sys_param->ArcDir;
        dir_name += "\\";
        FileListBox->Directory = dir_name;
        FileListBox->Update();

        for (int j=0; j<FileListBox->Count; j++)
        {
                TArcStat *arc_stat = new TArcStat();

                AnsiString s_name = sys_param->ArcDir;
                s_name += "\\"+FileListBox->Items->Strings[j];
                FILE *f = fopen(s_name.c_str(),"rb");
                if (f != NULL) fread(arc_stat,sizeof(TArcStat),1,f);
                fclose(f);
                arc_stat_list->Add(arc_stat);

                AnsiString arc_name = s_name;
                char *p = StrPos(arc_name.c_str(),".sta");
                if (p == NULL) p = StrPos(arc_name.c_str(),".STA");
                p[0] = 0;

   char t[50];
   strcpy(t,arc_name.c_str());
   AnsiString file_name = t;

                TArchive *arc = new TArchive(sys_param,ChannelList,file_name,1);
                arc_list->Add(arc);

                //------------------------------------
                TListItem *ListItem;
                ListItem = ListView->Items->Add();
                ListItem->Caption = IntToStr(j+1);

                if (arc_stat->RudNameIndex == 0) ListItem->SubItems->Add("Холбинский");
                else ListItem->SubItems->Add("???");

                if (arc_stat->StvolNameIndex == 0) ListItem->SubItems->Add("Вспомогательный");
                else
                if (arc_stat->StvolNameIndex == 1) ListItem->SubItems->Add("Главный");
                else ListItem->SubItems->Add("???");

                ListItem->SubItems->Add(DateToStr(arc_stat->date_time));

                if (arc_stat->smena_id == 0) ListItem->SubItems->Add("I");
                else
                if (arc_stat->smena_id == 1) ListItem->SubItems->Add("II");
                else ListItem->SubItems->Add("???");

                //-----------
                ListItem->SubItems->Add(IntToStr(arc_stat->Gruz3+arc_stat->Gruz5)); // выдано
                ListItem->SubItems->Add(FloatToStrF(arc_stat->P,ffFixed,8,2));   // Р
                ListItem->SubItems->Add(IntToStr(arc_stat->RTP_count)); // РТП
                ListItem->SubItems->Add(IntToStr(arc_stat->RPM_count)); // РПМ                
                ListItem->SubItems->Add(FloatToStrF(arc_stat->mh,ffFixed,8,2)); // Моточасы
                ListItem->SubItems->Add(FloatToStrF(arc_stat->Total_L_count/1000.0,ffFixed,8,2));

                ListItem->SubItems->Add(IntToStr(arc_stat->CP_count)); // ЦП
                ListItem->SubItems->Add(arc_stat->MashinistName); // машинист
                ListItem->SubItems->Add(arc_stat->MasterName); // мастер                                
                //-----------
        }
}

void __fastcall TArcForm::FormShow(TObject *Sender)
{
        RefreshArhs();
        Memo1->Lines->Add("FormShow");
}
//---------------------------------------------------------------------------

void __fastcall TArcForm::RefreshButtonClick(TObject *Sender)
{
        FormShow(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TArcForm::ListViewDblClick(TObject *Sender)
{
   int r = ListView->ItemIndex;

   // если архив выбран
   if (r != -1 && FreqForm->ShowModal()==mrOk)
   {
        short freq_id;
        switch (FreqForm->RadioGroup1->ItemIndex)
        {
                case 0: freq_id = 1;
                        break;
                case 1: freq_id = 50;
                        break;
                case 2: freq_id = 100;
                        break;
                case 3: freq_id = 200;
                        break;
        }
        SmRepForm->freq_id = freq_id;
        //---------------------------------------

        SmRepForm->cikl_list = new TCiklPodList;

        TCiklPod *curr_RTP;
        SmRepForm->RTP_cikl_list = new TCiklPodList;

//        ProgressForm->ProgressBar1->Position = 0;

//        StatusBar1->Panels->Items[0]->Text = "Загрузка данных, подождите, пожалуйста...";

//        ProgressForm->Caption = "Загрузка данных...";
  //      ProgressForm->Label1->Caption = "Подождите, пожалуйста...";

// формирование отчета за смену
//------------------------------------------------------------------
        SmRepForm->Image1->Canvas->Brush->Color = clWhite;
        SmRepForm->Image1->Canvas->FillRect(SmRepForm->Image1->ClientRect);

        SmRepForm->diag_rect1 = Rect(0,0,1024,261);
        SmRepForm->diag_rect2 = Rect(0,261+5+30,1024,562-5);
        SmRepForm->hour_rect = Rect(0,261+5,1024,261+5+30);
        SmRepForm->_7_rect = Rect(970,30,970+52,30+129);

        TPoint pk;
        pk.x = 0;
        pk.y = 261/2;
        int log_x = 1; // час
        int log_y = 30; // ???
        SmRepForm->ks1 = new TKoordSystem(SmRepForm->Image1,SmRepForm->diag_rect1,pk,log_x,log_y);
        SmRepForm->ks1->bk_col = clWhite;
        SmRepForm->ks1->log_koord.x = 0;
        SmRepForm->ks1->log_koord.y = 0;
        SmRepForm->ks1->koef.kx = log_x*(SmRepForm->Image1->Width)/6.0; //???
//        SmRepForm->ks1->koef.kx =200;
        SmRepForm->ks1->koef.ky = 30;
        SmRepForm->ks1->col = clGreen;
        SmRepForm->ks1->draw_setka = false;
        SmRepForm->ks1->draw_numbers_y = false;
        SmRepForm->ks1->draw_numbers_x = false;
        SmRepForm->ks1->draw_kslines = false;
        SmRepForm->diag1 = new TDiagram(SmRepForm->ks1,ChannelList);
        SmRepForm->diag1->col = sys_param->repDIAGcol;

        SmRepForm->ks2 = new TKoordSystem(SmRepForm->Image1,SmRepForm->diag_rect2,pk,log_x,log_y);
        SmRepForm->ks2->bk_col = clWhite;
        SmRepForm->ks2->log_koord.x = 6;
        SmRepForm->ks2->log_koord.y = 0;
        SmRepForm->ks2->koef.kx = log_x*(SmRepForm->Image1->Width)/6.0; //???
//        SmRepForm->ks2->koef.kx = 200;
        SmRepForm->ks2->koef.ky = 30;
        SmRepForm->ks2->col = clGreen;
        SmRepForm->ks2->draw_setka = false;
        SmRepForm->ks2->draw_numbers_y = false;
        SmRepForm->ks2->draw_numbers_x = false;
        SmRepForm->ks2->draw_kslines = false;
        SmRepForm->diag2 = new TDiagram(SmRepForm->ks2,ChannelList);
        SmRepForm->diag2->col = sys_param->repDIAGcol;

        // ось времени (часы)
        Graphics::TBitmap *btmp;
        btmp = new Graphics::TBitmap;
        btmp->Width = SmRepForm->Image2->Width;
        btmp->Height = SmRepForm->Image2->Height;
        TRect RectS;
        RectS = Rect(0,0,btmp->Width,btmp->Height);
        btmp->Canvas->CopyRect(RectS,SmRepForm->Image2->Canvas,RectS);
        SmRepForm->Image1->Canvas->CopyRect(SmRepForm->hour_rect,btmp->Canvas,RectS);
        delete btmp;

        //-------------------
        // распаковка

        TArchive *arh = (*arc_list)[r];
 if (FileExists(arh->f_name+".rar"))
 {
    //    ProgressForm->Show();

        SmRepForm->arh = arh;
        TArcStat *arc_stat = SmRepForm->arc_stat = (*arc_stat_list)[r];
        TArchiveRecord *rec;

        UnpackArc(arh->f_name);

        Sleep(3000);///???

        arh->ReadHeader(ChannelList);

        SmRepForm->war_list = new TWarningList();
        arh->ReadWarnings(SmRepForm->war_list);
        //-------------------------

        SmCiklForm->arh = arh;
        DiagRTPForm->arh = arh;

        short ch_Utg_id;
        ch_Utg_id = GetChannelByNameAndDimension(ChannelList,"Uтг",tdtU)->ChannelID;

        short ch_RTPon_id = GetChannelByNameAndDimension(ChannelList,"РТП",tdtON)->ChannelID;
        short ch_RTPoff_id = GetChannelByNameAndDimension(ChannelList,"РТП",tdtOFF)->ChannelID;
        short ch_V_id = GetChannelByNameAndDimension(ChannelList,"V",tdtSPEED)->ChannelID;

        bool mrg,mrl,mrr,mro;
        signed char mode_tek = -1;
        TLogPoint stp;
        stp.x = 0;
        stp.y = 261+1;

        bool RTP_cikl_begin = false;
        bool AV1beg,RVPUbeg,EV21beg,ROKpbeg,EV1beg,Y4beg,RKTbeg,RPMbeg;
        AV1beg = RVPUbeg = EV21beg = ROKpbeg = EV1beg = Y4beg = RKTbeg = RPMbeg = false;
        T7List *_7list = new T7List;

        Word phour;

        int st_msec,prev_x_msec;//,st_n_cp;
        int st_c_msec; // начало цикла
        short ch_id_p;//,ch_n_cp;
//        short ch_id_cp;
//        int cikl_tek;
        TCiklPod cikl_tek_rec;
        float Ist,prevIst;
//        float Utg,prevUtg;

        if (arh->count_arch_rec > 0)
        {
                rec = arh->LoadItem(ChannelList,0);
                mrg = (*rec->ChannelDataList)[idRG]->diskret;
                mrl = (*rec->ChannelDataList)[idRL]->diskret;
                mrr = (*rec->ChannelDataList)[idRR]->diskret;
                mro = (*rec->ChannelDataList)[idRO]->diskret;
                if (mrg) mode_tek = 0;
                if (mrl) mode_tek = 1;
                if (mrr) mode_tek = 2;
                if (mro) mode_tek = 3;

                TLogPoint *vp = new TLogPoint();
                vp->x = 0;
                vp->y = (*rec->ChannelDataList)[ch_Utg_id]->analog;
                SmRepForm->diag1->lp_list->Add(vp);

                Word hour,min,sec,msec;
                DecodeTime(rec->date_time,hour,min,sec,msec);
                phour = hour;
                //-----------
                float hour2 = hour + min/60.0;
                float dtper = sys_param->dt_peresm/60.0;

                if (arc_stat->smena_id==0)
                 if (hour2>=sys_param->DayTime1-dtper && hour2 <= sys_param->DayTime1+dtper)
                 {
                 }
                 else
                 {
                        hour = sys_param->DayTime1;
                        min = 0;
                        sec = 0;
                        msec = 0;
                 }
                else
                if (arc_stat->smena_id==1)
                 if (hour2>=sys_param->NightTime1-dtper && hour2 <= sys_param->NightTime1+dtper)
                 {
                 }
                 else
                 {
                        hour = sys_param->NightTime1;
                        min = 0;
                        sec = 0;
                        msec = 0;
                 }
                //-----------
/*                if (hour>=0 && hour<=sys_param->NightTime2+1) // после 24:00
                {
                        hour += 24;
                }*/
                prev_x_msec = st_msec = hour*3600*1000+min*60*1000+sec*1000+msec;


//                ProgressForm->ProgressBar1->Max = arh->count_arch_rec-1;

                SmRepForm->DateL->Caption = DateToStr(rec->date_time);

                //--------start cicle values
//                ch_n_cp = GetChannelByNameAndDimension(ChannelList,"N_CP",tdtNONE)->ChannelID; //???
                ch_id_p = GetChannelByNameAndDimension(ChannelList,"P",tdtP)->ChannelID;
                cikl_tek_rec.mode = mode_tek;
//                cikl_tek_rec.p = (*rec->ChannelDataList)[ch_id_p]->analog;
//                cikl_tek_rec.total_msec = st_msec;
//                st_n_cp = (*rec->ChannelDataList)[ch_n_cp]->analog;
                //---------------------

                prevIst = (*rec->ChannelDataList)[idIst]->analog;
//                prevUtg = (*rec->ChannelDataList)[idUtg]->analog;

                DiagRTPForm->smena_beg_time = rec->date_time;
        }
        else
        {
//                ProgressForm->ProgressBar1->Max = 0;
        }

        int begr=0,endr=0;
        for (int i=1; i<arh->count_arch_rec; i++)
        {
                rec = arh->LoadItem(ChannelList,i);

                float V = (*rec->ChannelDataList)[ch_V_id]->analog;

                //--------------------

                TLogPoint *vp = new TLogPoint();

                Word hour,min,sec,msec;
                DecodeTime(rec->date_time,hour,min,sec,msec);

                if (phour > hour) hour += 24;
//                if (hour>=0 && hour<=sys_param->NightTime2+1) hour += 24;// после 24:00

                int x_msec = hour*3600*1000+min*60*1000+sec*1000+msec;
                vp->x = (x_msec-st_msec)/(3600.0*1000.0);
                vp->y = (*rec->ChannelDataList)[ch_Utg_id]->analog;

                phour = hour;

                // определение зависания PC (dt = 5мин) ------
                if ( (x_msec-prev_x_msec) >= 5000*60 )
                {
                        mode_tek = 4;
                }        
                //------------------------------------------

                // чтение режима
                signed char mode_next = -1;
                mrg = (*rec->ChannelDataList)[idRG]->diskret;
                mrl = (*rec->ChannelDataList)[idRL]->diskret;
                mrr = (*rec->ChannelDataList)[idRR]->diskret;
                mro = (*rec->ChannelDataList)[idRO]->diskret;
                if (mrg) mode_next = 0;
                if (mrl) mode_next = 1;
                if (mrr) mode_next = 2;
                if (mro) mode_next = 3;

                //--- формирование 7 РТП и РПМ
                bool is_RKT_on = (*rec->ChannelDataList)[idRKT]->diskret;
                if (is_RKT_on && RKTbeg) RKTbeg = false;
                if (!is_RKT_on && !RKTbeg && mode_tek!=4 && V!=0.0)
                {
                        RKTbeg = true;

                        T7Record *_7rec = new T7Record;
                        _7rec->n = '7';
                        _7rec->lp.x = vp->x;
                        _7rec->lp.y = vp->y;
                        _7list->Add(_7rec);
                }

                bool is_Y4_on = (*rec->ChannelDataList)[idY4]->diskret;
                if (is_Y4_on && Y4beg) Y4beg = false;
                if (!is_Y4_on && !Y4beg && mode_tek!=4)
                {
                        Y4beg = true;

                        T7Record *_7rec = new T7Record;
                        _7rec->n = '6';
                        _7rec->lp.x = vp->x;
                        _7rec->lp.y = vp->y;
                        _7list->Add(_7rec);
                }

                bool is_EV1_on = (*rec->ChannelDataList)[idEV1]->diskret;
                if (is_EV1_on && EV1beg) EV1beg = false;
                if (!is_EV1_on && !EV1beg && mode_tek!=4)
                {
                        EV1beg = true;

                        T7Record *_7rec = new T7Record;
                        _7rec->n = '5';
                        _7rec->lp.x = vp->x;
                        _7rec->lp.y = vp->y;
                        _7list->Add(_7rec);
                }

                bool is_ROKp_on = (*rec->ChannelDataList)[idROKp]->diskret;
                if (is_ROKp_on && ROKpbeg) ROKpbeg = false;
                if (!is_ROKp_on && !ROKpbeg && mode_tek!=4)
                {
                        ROKpbeg = true;

                        T7Record *_7rec = new T7Record;
                        _7rec->n = '4';
                        _7rec->lp.x = vp->x;
                        _7rec->lp.y = vp->y;
                        _7list->Add(_7rec);
                }

                bool is_EV21_on = (*rec->ChannelDataList)[idEV21]->diskret;
                if (is_EV21_on && EV21beg) EV21beg = false;
                if (!is_EV21_on && !EV21beg && mode_tek!=4)
                {
                        EV21beg = true;

                        T7Record *_7rec = new T7Record;
                        _7rec->n = '3';
                        _7rec->lp.x = vp->x;
                        _7rec->lp.y = vp->y;
                        _7list->Add(_7rec);
                }

                bool is_RVPU_on = (*rec->ChannelDataList)[idRVPU]->diskret;
                if (is_RVPU_on && RVPUbeg) RVPUbeg = false;
                if (!is_RVPU_on && !RVPUbeg && mode_tek!=4)
                {
                        RVPUbeg = true;

                        T7Record *_7rec = new T7Record;
                        _7rec->n = '2';
                        _7rec->lp.x = vp->x;
                        _7rec->lp.y = vp->y;
                        _7list->Add(_7rec);
                }

                bool is_AV1_on = (*rec->ChannelDataList)[idAV1]->diskret;
                if (is_AV1_on && AV1beg) AV1beg = false;
                if (!is_AV1_on && !AV1beg && mode_tek!=4)
                {
                        AV1beg = true;

                        T7Record *_7rec = new T7Record;
                        _7rec->n = '1';
                        _7rec->lp.x = vp->x;
                        _7rec->lp.y = vp->y;
                        _7list->Add(_7rec);
                }
                //------------------------
                bool is_RPM_on = (*rec->ChannelDataList)[idRPMon]->diskret;
                if (!is_RPM_on && RPMbeg) RPMbeg = false;
                if (is_RPM_on && !RPMbeg && mode_tek!=4)
                {
                        RPMbeg = true;

                        T7Record *_7rec = new T7Record;
                        _7rec->n = 'п';
                        _7rec->lp.x = vp->x;
                        _7rec->lp.y = vp->y;
                        _7list->Add(_7rec);
                }
                //----------------------------

                // Формирование диаграмм RTP
                bool is_RTP_on = (*rec->ChannelDataList)[ch_RTPon_id]->diskret;
                bool is_RTP_off = (*rec->ChannelDataList)[ch_RTPoff_id]->diskret;

                if (is_RTP_off && !RTP_cikl_begin && V!=0.0)
                {
                        RTP_cikl_begin = true;
                        curr_RTP = new TCiklPod();
                        curr_RTP->begr = i;
                }

                if ( (!is_RTP_off && RTP_cikl_begin) || (RTP_cikl_begin && V==0.0) )
                {
                        RTP_cikl_begin = false;
                        curr_RTP->endr = i;
                        SmRepForm->RTP_cikl_list->Add(curr_RTP);
                }

                //--------------------------

                //------------ формирование циклов подъема

                Ist = (*rec->ChannelDataList)[idIst]->analog;
                if (prevIst == 0.0 && Ist != 0.0) // начало цикла
                {
                        begr = i-1;
                }
                else
                if (prevIst != 0.0 && Ist == 0.0) // завершение цикла
                {
                        TCiklPod *cikl = new TCiklPod;

                        endr = i;

                        cikl->begr = begr;
                        cikl->endr = endr;

                        SmRepForm->cikl_list->Add(cikl);
                }
                prevIst = Ist;
/*                Utg = (*rec->ChannelDataList)[idUtg]->analog;
                if (prevUtg == 0.0 && Utg != 0.0) // начало цикла
                {
                        begr = i-1;
                }
                else
                if (prevUtg != 0.0 && Utg == 0.0) // завершение цикла
                {
                        TCiklPod *cikl = new TCiklPod;

                        endr = i;

                        cikl->begr = begr;
                        cikl->endr = endr;

                        SmRepForm->cikl_list->Add(cikl);
                }
                prevUtg = Utg;*/

                //------------

                if (vp->x <= 6.0)
                {
                        SmRepForm->diag1->lp_list->Add(vp);
                }
                else
                {
                        SmRepForm->diag2->lp_list->Add(vp);
                }

                if (mode_tek == mode_next && i != arh->count_arch_rec-1)
                {
                }
                else
                {
                        SmRepForm->Image1->Canvas->Pen->Width = 1;
                        if (mode_tek == 0)
                        {
                                SmRepForm->Image1->Canvas->Pen->Style = (TPenStyle)sys_param->repRGlinestyle;
                                SmRepForm->Image1->Canvas->Pen->Color = sys_param->repRGcol;
                        }
                        else if (mode_tek == 1)
                        {
                                SmRepForm->Image1->Canvas->Pen->Style = (TPenStyle)sys_param->repRLlinestyle;
                                SmRepForm->Image1->Canvas->Pen->Color = sys_param->repRLcol;
                        }
                        else if (mode_tek == 2)
                        {
                                SmRepForm->Image1->Canvas->Pen->Style = (TPenStyle)sys_param->repRRlinestyle;
                                SmRepForm->Image1->Canvas->Pen->Color = sys_param->repRRcol;
                        }
                        else if (mode_tek == 3)
                        {
                                SmRepForm->Image1->Canvas->Pen->Style = (TPenStyle)sys_param->repROlinestyle;
                                SmRepForm->Image1->Canvas->Pen->Color = sys_param->repROcol;
                        }
                        else if (mode_tek == 4 || mode_tek == -1) // "зависание" PC
                        {
                                SmRepForm->Image1->Canvas->Pen->Style = (TPenStyle)sys_param->repPClinestyle;
                                SmRepForm->Image1->Canvas->Pen->Color = sys_param->repPCcol;
                        }

                        //-------------------------
                        TLogPoint stp2;
                        stp2.x = vp->x;
                        stp2.y = vp->y;

                        // деление на части
                        short gx,gx2,gy,gy2;
                        short tx,ty,tx2,ty2;
                        if (stp.x <= 6.0 && stp2.x >= 6.0)
                        {
                                gx = (stp.x-SmRepForm->ks1->log_koord.x) / SmRepForm->ks1->log_x
                                                                                * SmRepForm->ks1->koef.kx;
                                gy = 261+1+1;
                                gx2 = (stp2.x-SmRepForm->ks2->log_koord.x) / SmRepForm->ks2->log_x
                                                                                * SmRepForm->ks2->koef.kx - 1;
                                gy2 = 261*2+40+1-5;

                                tx = (6.0-SmRepForm->ks1->log_koord.x) / SmRepForm->ks1->log_x
                                                                                * SmRepForm->ks1->koef.kx;
                                ty = gy;
                                tx2 = (6.0-SmRepForm->ks2->log_koord.x) / SmRepForm->ks2->log_x
                                                                                * SmRepForm->ks2->koef.kx - 1;
                                ty2 = gy2;

                                SmRepForm->Image1->Canvas->MoveTo(gx,gy);
                                SmRepForm->Image1->Canvas->LineTo(tx,ty);
                                SmRepForm->Image1->Canvas->MoveTo(tx2,ty2);
                                SmRepForm->Image1->Canvas->LineTo(gx2,gy2);

                                SmRepForm->Image1->Canvas->MoveTo(gx,gy+1);
                                SmRepForm->Image1->Canvas->LineTo(tx,ty+1);
                                SmRepForm->Image1->Canvas->MoveTo(tx2,ty2+1);
                                SmRepForm->Image1->Canvas->LineTo(gx2,gy2+1);

                                SmRepForm->Image1->Canvas->MoveTo(gx,gy+2);
                                SmRepForm->Image1->Canvas->LineTo(tx,ty+2);
                                SmRepForm->Image1->Canvas->MoveTo(tx2,ty2+2);
                                SmRepForm->Image1->Canvas->LineTo(gx2,gy2+2);
                        }
                        else
                        {
                            if (stp2.x < 6.0)
                            {
                                gx = (stp.x-SmRepForm->ks1->log_koord.x) / SmRepForm->ks1->log_x
                                                                                * SmRepForm->ks1->koef.kx;
                                gx2 = (stp2.x-SmRepForm->ks1->log_koord.x) / SmRepForm->ks1->log_x
                                                                                * SmRepForm->ks1->koef.kx;
                                gy = gy2 = 261+1+1;
                            }
                            else
                            if (stp2.x > 6.0)
                            {
                                gx = (stp.x-SmRepForm->ks2->log_koord.x) / SmRepForm->ks2->log_x
                                                                                * SmRepForm->ks2->koef.kx;
                                gx2 = (stp2.x-SmRepForm->ks2->log_koord.x) / SmRepForm->ks2->log_x
                                                                                * SmRepForm->ks2->koef.kx - 1;
                                gy = gy2 = 261*2+40+1-5;
                            }
                            SmRepForm->Image1->Canvas->MoveTo(gx,gy);
                            SmRepForm->Image1->Canvas->LineTo(gx2,gy2);

                            SmRepForm->Image1->Canvas->MoveTo(gx,gy+1);
                            SmRepForm->Image1->Canvas->LineTo(gx2,gy2+1);

                            SmRepForm->Image1->Canvas->MoveTo(gx,gy+2);
                            SmRepForm->Image1->Canvas->LineTo(gx2,gy2+2);
                        }

                        stp.x = stp2.x;
                        stp.y = stp2.y;
                        //-------------------------

                        mode_tek = mode_next;

                        // контроль на превышение длительности смены
                        if (vp->x > 12.0)
                        {
                                break;
                        }
                }
                //--------------

                prev_x_msec = x_msec;

                delete rec;

//                ProgressForm->ProgressBar1->Position++;
        }

//----------------------------формирование отчета (стат.часть)
                        SmRepForm->DateL->Caption = DateToStr(arc_stat->date_time);

                        SmRepForm->TPL->Caption = IntToStr(arc_stat->RTP_count);

                        short gr3,gr5;
                        SmRepForm->Gor3L->Caption = IntToStr(gr3 = arc_stat->Gruz3);
                        SmRepForm->Gor5L->Caption = IntToStr(gr5 = arc_stat->Gruz5);
                        SmRepForm->VagonL->Caption = IntToStr(gr3+gr5);

                        SmRepForm->TotalLL->Caption = FloatToStrF(arc_stat->Total_L_count/1000.0,ffFixed,8,2)+" км";

                        SmRepForm->PL->Caption = FloatToStrF(arc_stat->P,ffFixed,8,2)+" кВт/ч";

                        SmRepForm->MHL->Caption = FloatToStrF(arc_stat->mh,ffFixed,8,2);

                        SmRepForm->CPL->Caption = IntToStr(arc_stat->CP_count);

                        if (arc_stat->smena_id == 0) SmRepForm->SmenaL->Caption = "I";
                        else
                        if (arc_stat->smena_id == 1) SmRepForm->SmenaL->Caption = "II";

                        if (arc_stat->StvolNameIndex == 0) SmRepForm->StvolL->Caption = "Вспомогательный";
                        else
                        if (arc_stat->StvolNameIndex == 1) SmRepForm->StvolL->Caption = "Главный";

                        SmRepForm->MashL->Caption = arc_stat->MashinistName;
                        SmRepForm->MasterL->Caption = arc_stat->MasterName;
//----------------------------

        SmRepForm->ks1->DrawKoordSystem();
        SmRepForm->diag1->RedrawWithOutNodes(freq_id);
        SmRepForm->ks2->DrawKoordSystem();
        SmRepForm->diag2->RedrawWithOutNodes(freq_id);

        for (int i = 0; i<_7list->count; i++)
                if ((*_7list)[i]->lp.x <= 6.0) SmRepForm->diag1->Draw7Point((*_7list)[i],clBlue);
                else SmRepForm->diag2->Draw7Point((*_7list)[i],clBlue);

        SmRepForm->diag1->Redraw();
        SmRepForm->diag2->Redraw();

        // 7 РТП и РПМ
        btmp = new Graphics::TBitmap;
        btmp->Width = SmRepForm->Image3->Width;
        btmp->Height = SmRepForm->Image3->Height;
        RectS = Rect(0,0,btmp->Width,btmp->Height);
        btmp->Canvas->CopyRect(RectS,SmRepForm->Image3->Canvas,RectS);
        SmRepForm->Image1->Canvas->CopyRect(SmRepForm->_7_rect,btmp->Canvas,RectS);
        delete btmp;

        delete _7list;


        //----------------------
        { // формирование циклов подъема
        TCiklPod *tc,*tc2;
        TArchiveRecord *rec1,*rec2,*rec;
        float Utg;
        long st_msec,end_msec;
        Word hour,min,sec,msec;
        short mode_id;
        float vag,prevvag;
        for (int i=0; i<SmRepForm->cikl_list->count; i++)
        {
                tc = (*SmRepForm->cikl_list)[i];
                rec1 = arh->LoadItem(ArcForm->ChannelList,tc->begr);
                rec2 = arh->LoadItem(ArcForm->ChannelList,tc->endr);

                for (int j=tc->begr; j<=tc->endr; j++)
                {
                        rec = arh->LoadItem(ArcForm->ChannelList,j);
                        Utg = (*rec->ChannelDataList)[ArcForm->idUtg]->analog;
                        if (Utg != 0.0) break;
                }

                // направление
                if (Utg > 0.0) tc->vector = -1; // подъем левой клети
                if (Utg < 0.0) tc->vector = 1; // подъем правой клети
                //----------------------

                // время начала цикла
                tc->fbeg = rec1->date_time;
                //----------------------

                // длительность
                DecodeTime(tc->fbeg,hour,min,sec,msec);
                if (hour>=0 && hour<=ArcForm->sys_param->NightTime2+1) hour += 24;// после 24:00
                st_msec = hour*3600*1000+min*60*1000+sec*1000+msec;

                DecodeTime(rec2->date_time,hour,min,sec,msec);
                if (hour>=0 && hour<=ArcForm->sys_param->NightTime2+1) hour += 24;// после 24:00
                end_msec = hour*3600*1000+min*60*1000+sec*1000+msec;

                tc->rhour = (end_msec-st_msec)/3600000;
                tc->rmin = (end_msec-st_msec)/60000-tc->rhour*60;
                tc->rsec = (end_msec-st_msec)/1000-tc->rhour*3600-tc->rmin*60;
                //----------------------

                // пауза
                if (i != SmRepForm->cikl_list->count-1)
                {
                        tc2 = (*SmRepForm->cikl_list)[i+1];
                        rec = arh->LoadItem(ArcForm->ChannelList,tc2->begr);
                        DecodeTime(rec->date_time,hour,min,sec,msec);
                        if (hour>=0 && hour<=ArcForm->sys_param->NightTime2+1) hour += 24;// после 24:00
                        st_msec = hour*3600*1000+min*60*1000+sec*1000+msec;

                        tc->phour = (-end_msec+st_msec)/3600000;
                        tc->pmin = (-end_msec+st_msec)/60000-tc->phour*60;
                        tc->psec = (-end_msec+st_msec)/1000-tc->phour*3600-tc->pmin*60;
                }
                //----------------------

                // режим
                if ((*rec1->ChannelDataList)[ArcForm->idRG]->diskret) mode_id = 0;
                if ((*rec1->ChannelDataList)[ArcForm->idRL]->diskret) mode_id = 1;
                if ((*rec1->ChannelDataList)[ArcForm->idRR]->diskret) mode_id = 2;
                if ((*rec1->ChannelDataList)[ArcForm->idRO]->diskret) mode_id = 3;
                tc->mode = mode_id;
                //----------------------

                // вагон
                prevvag = (*rec1->ChannelDataList)[ArcForm->idG3]->analog +
                              (*rec1->ChannelDataList)[ArcForm->idG5]->analog;
                if (i != SmRepForm->cikl_list->count-1)
                {
                        tc2 = (*SmRepForm->cikl_list)[i+1];
                        rec = arh->LoadItem(ArcForm->ChannelList,tc2->begr);
                        vag = (*rec->ChannelDataList)[ArcForm->idG3]->analog +
                              (*rec->ChannelDataList)[ArcForm->idG5]->analog;
                }
                else
                {
                        rec = arh->LoadItem(ArcForm->ChannelList,arh->count_arch_rec-1);
                        vag = (*rec->ChannelDataList)[ArcForm->idG3]->analog +
                              (*rec->ChannelDataList)[ArcForm->idG5]->analog;
                }
                tc->vagon = vag > prevvag;
                //----------------------

                // эл.энергия
                tc->P = (*rec2->ChannelDataList)[ArcForm->idP]->analog -
                                 (*rec1->ChannelDataList)[ArcForm->idP]->analog;
                //----------------------

                // L,м
                tc->L = (*rec2->ChannelDataList)[ArcForm->idL]->analog -
                                        (*rec1->ChannelDataList)[ArcForm->idL]->analog;
                //----------------------
        }
        }
        //----------------------

//        StatusBar1->Panels->Items[0]->Text = "Загрузка данных завершена...";
//        ProgressForm->Caption = "Загрузка данных завершена...";
//        ProgressForm->Visible = false;
  //      Sleep(2000);

        SmRepForm->ShowModal();
 }
 else
   {
        MessageDlg("Файл архива не найден!", mtError, TMsgDlgButtons() << mbOK, 0);
   }
 }
}
//---------------------------------------------------------------------------
void __fastcall TArcForm::FormCreate(TObject *Sender)
{
        ApdComPort1->ComNumber = sys_param->comm.COM_PORT_ID+1;

        ApdProtocol2->DestinationDirectory = sys_param->ArcDir;
}
//---------------------------------------------------------------------------

void __fastcall TArcForm::DialTimerTimer(TObject *Sender)
{
        for (int i=0; i<sheduler->list->count; i++)
        {
//                ApdComPort1->Open = false;//??
                TShedRecord *rec = (*sheduler->list)[i];

                Word hour,min,sec,msec;
                DecodeTime(Time(),hour,min,sec,msec);
                Word total_min = hour*60+min;

                Word hour2,min2,sec2,msec2;
                DecodeTime(rec->time,hour2,min2,sec2,msec2);
                Word total_min2 = hour2*60+min2;

                // совпадение временной метки с текущим временем и активность записи
                if (rec->state == false && total_min2 == total_min && !is_busy)
                {
                        AnsiString phone;
                        if (sys_param->comm.DIAL_MODE == tdmTONE) phone = "";
                        if (sys_param->comm.DIAL_MODE == tdmPULSE) phone = "P";
                        phone += rec->Phone;
                        command = "c"+IntToStr(rec->action);
                        Memo1->Lines->Add("Dialing...");
//                        ApdComPort1->Open = true;//??
                        is_busy = true;
                        ApdTapiDevice1->Dial(phone);
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TArcForm::ApdTapiDevice1TapiFail(TObject *Sender)
{
        if (!ApdTapiDevice1->Cancelled) ApdTapiDevice1->CancelCall();
        Sleep(3000);
        is_busy = false;
}
//---------------------------------------------------------------------------

void __fastcall TArcForm::ApdTapiDevice1TapiPortOpen(TObject *Sender)
{
        Memo1->Lines->Add("Connected");

        Memo1->Lines->Add("Send command file: ");

        char f_name[60];
        strcpy(f_name,sys_param->SysDir);
        strcat(f_name,"\\cmnd.tmp");

        FILE *f = fopen(f_name,"wt");
        fputs(command.c_str(),f);
        fclose(f);

        Memo1->Lines->Add(command);

        ApdProtocol1->FileMask = f_name;
//        Memo1->Lines->Add("FileName: "+ApdProtocol1->FileMask);
        ApdProtocol1->StartTransmit();
}
//---------------------------------------------------------------------------

void __fastcall TArcForm::ApdProtocol1ProtocolFinish(TObject *CP,
      int ErrorCode)
{
//        Memo1->Lines->Add("Command file was send");
  //      Memo1->Lines->Add("Wait Answer");

        ApdProtocol2->StartReceive();
}
//---------------------------------------------------------------------------

void __fastcall TArcForm::ApdProtocol2ProtocolFinish(TObject *CP,
      int ErrorCode)
{
        //Memo1->Lines->Add("File was downloaded");

        // оборвать связь (закрыть сеанс)
        ApdTapiDevice1->CancelCall();

        // обновить информацию
        RefreshArhs();

        is_busy = false;
}
//---------------------------------------------------------------------------
// составление балансов работы ШПМ
void __fastcall TArcForm::BalansButtonClick(TObject *Sender)
{
if (BalParForm->ShowModal() == mrOk)
{
  bool by_smena,by_day,by_month,by_quarter,by_halfyear,by_year,by_stvol,by_rudnik;
  bool by_vagon,by_mh,by_tp,by_l,by_p,by_cp;

  BalRepForm->by_vagon = by_vagon = BalParForm->CheckBox1->Checked;
  BalRepForm->by_mh = by_mh = BalParForm->CheckBox2->Checked;
  BalRepForm->by_tp = by_tp = BalParForm->CheckBox3->Checked;
  BalRepForm->by_l = by_l = BalParForm->CheckBox4->Checked;
  BalRepForm->by_p = by_p = BalParForm->CheckBox5->Checked;
  BalRepForm->by_cp = by_cp = BalParForm->CheckBox6->Checked;
  //------------------------------------------------------
  BalRepForm->by_smena = by_smena = BalParForm->CheckBox7->Checked;
  BalRepForm->by_day = by_day = BalParForm->CheckBox8->Checked;
  BalRepForm->by_month = by_month = BalParForm->CheckBox9->Checked;
  BalRepForm->by_quarter = by_quarter = BalParForm->CheckBox10->Checked;
  BalRepForm->by_halfyear = by_halfyear = BalParForm->CheckBox11->Checked;
  BalRepForm->by_year = by_year = BalParForm->CheckBox12->Checked;
  BalRepForm->by_stvol = by_stvol = BalParForm->CheckBox13->Checked;
  BalRepForm->by_rudnik = by_rudnik = BalParForm->CheckBox14->Checked;

  bool flag_sum = by_vagon||by_mh||by_tp||by_l||by_p||by_cp;
  bool flag_dim = by_smena||by_day||by_month||by_quarter||by_halfyear||by_year||by_stvol||by_rudnik;

  if (flag_sum && flag_dim)
  {
        //-------------------------------------------
        TTimeStatList *tst_list = new TTimeStatList;
        TArcStat *st; TTimeStat *tst;
        for (int i=0; i<arc_stat_list->count; i++)
        {
                st = (*arc_stat_list)[i];
                tst = new TTimeStat;
                Stat2TimeStat(st,tst);
                tst_list->Add(tst);
        }
        //-------------------------------------------
                  
        BalRepForm->Table1->Active = false;
        BalRepForm->Table1->DatabaseName = sys_param->SysDir;
        BalRepForm->Table1->TableType = ttParadox;
        BalRepForm->Table1->TableName = "balans";

        BalRepForm->Table1->FieldDefs->Clear();

        // создание измерений
        TFieldDef *pNewDef;

        pNewDef = BalRepForm->Table1->FieldDefs->AddFieldDef();
        pNewDef->Name = "Year111";
        pNewDef->DataType = ftString;
        pNewDef->Size = 5;

        pNewDef = BalRepForm->Table1->FieldDefs->AddFieldDef();
        pNewDef->Name = "HalfYear111";
        pNewDef->DataType = ftString;
        pNewDef->Size = 5;

        pNewDef = BalRepForm->Table1->FieldDefs->AddFieldDef();
        pNewDef->Name = "Quarter111";
        pNewDef->DataType = ftString;
        pNewDef->Size = 5;

        pNewDef = BalRepForm->Table1->FieldDefs->AddFieldDef();
        pNewDef->Name = "Month111";
        pNewDef->DataType = ftString;
        pNewDef->Size = 5;

        pNewDef = BalRepForm->Table1->FieldDefs->AddFieldDef();
        pNewDef->Name = "Day111";
        pNewDef->DataType = ftString;
        pNewDef->Size = 5;

        pNewDef = BalRepForm->Table1->FieldDefs->AddFieldDef();
        pNewDef->Name = "Smena111";
        pNewDef->DataType = ftString;
        pNewDef->Size = 5;

        pNewDef = BalRepForm->Table1->FieldDefs->AddFieldDef();
        pNewDef->Name = "Rudnik";
        pNewDef->DataType = ftString;
        pNewDef->Size = 30;

        pNewDef = BalRepForm->Table1->FieldDefs->AddFieldDef();
        pNewDef->Name = "Stvol";
        pNewDef->DataType = ftString;
        pNewDef->Size = 30;
        //-------------------------------

        // создание мер
        pNewDef = BalRepForm->Table1->FieldDefs->AddFieldDef();
        pNewDef->Name = "Vagon";
        pNewDef->DataType = ftInteger;

        pNewDef = BalRepForm->Table1->FieldDefs->AddFieldDef();
        pNewDef->Name = "RTP";
        pNewDef->DataType = ftInteger;

        pNewDef = BalRepForm->Table1->FieldDefs->AddFieldDef();
        pNewDef->Name = "CP";
        pNewDef->DataType = ftInteger;

        pNewDef = BalRepForm->Table1->FieldDefs->AddFieldDef();
        pNewDef->Name = "P";
        pNewDef->DataType = ftFloat;

        pNewDef = BalRepForm->Table1->FieldDefs->AddFieldDef();
        pNewDef->Name = "MH";
        pNewDef->DataType = ftFloat;

        pNewDef = BalRepForm->Table1->FieldDefs->AddFieldDef();
        pNewDef->Name = "L";
        pNewDef->DataType = ftFloat;
        //-------------------------------
        BalRepForm->Table1->IndexDefs->Clear();

        BalRepForm->Table1->CreateTable();
        //-------------------------------
        AnsiString RudName,StvolName;
        TTimeStat *tstrec;

        BalRepForm->Table1->Active = true;

        for (int i=0; i<tst_list->count; i++)
        {
                tstrec = (*tst_list)[i];

                if (tstrec->Rudnik == 0) RudName = "Холбинский";
                else RudName = "???";

                if (tstrec->Stvol == 0) StvolName = "Вспомогательный";
                else
                if (tstrec->Stvol == 1) StvolName = "Главный";
                else StvolName = "???";

                BalRepForm->Table1->InsertRecord(ARRAYOFCONST((                                                           //  i,
                                                               IntToStr(tstrec->Year),
                                                               IntToStr(tstrec->HalfYear),
                                                               IntToStr(tstrec->Quarter),
                                                               IntToStr(tstrec->Month),
                                                               IntToStr(tstrec->Day),
                                                               IntToStr(tstrec->Smena+1),    // ---

                                                               RudName,
                                                               StvolName,

                                                               tstrec->stat->Gruz3+tstrec->stat->Gruz5,
                                                               tstrec->stat->RTP_count,
                                                               tstrec->stat->CP_count,
                                                               tstrec->stat->P,
                                                               tstrec->stat->mh,
                                                               tstrec->stat->Total_L_count)));
        }

                BalRepForm->Table1->Active = false;

                //-----------------------------------
                BalRepForm->Table2->Active = false;
                BalRepForm->Table2->DatabaseName = sys_param->SysDir;
                BalRepForm->Query1->DatabaseName = sys_param->SysDir;
                BalRepForm->Table2->TableType = ttParadox;
                BalRepForm->Table2->TableName = "balans";
                //-----------------------------------

                BalRepForm->DBGrid2->Columns->Items[0]->Visible = by_rudnik;
                BalRepForm->DBGrid2->Columns->Items[1]->Visible = by_stvol;
                BalRepForm->DBGrid2->Columns->Items[2]->Visible = by_year;
                BalRepForm->DBGrid2->Columns->Items[3]->Visible = by_halfyear;
                BalRepForm->DBGrid2->Columns->Items[4]->Visible = by_quarter;
                BalRepForm->DBGrid2->Columns->Items[5]->Visible = by_month;
                BalRepForm->DBGrid2->Columns->Items[6]->Visible = by_day;
                BalRepForm->DBGrid2->Columns->Items[7]->Visible = by_smena;

                BalRepForm->DBGrid2->Columns->Items[8]->Visible = by_vagon;
                BalRepForm->DBGrid2->Columns->Items[9]->Visible = by_tp;
                BalRepForm->DBGrid2->Columns->Items[10]->Visible = by_cp;
                BalRepForm->DBGrid2->Columns->Items[11]->Visible = by_p;
                BalRepForm->DBGrid2->Columns->Items[12]->Visible = by_mh;
                BalRepForm->DBGrid2->Columns->Items[13]->Visible = by_l;

                //-----------------------------------
                BalRepForm->Query1->Active = false;

                BalRepForm->Query1->FieldDefs->Clear();

                AnsiString strSQL1 = "select ";
                AnsiString strSQL2 = " from balans ";
                AnsiString strSQL3 = "group by ";

                char temp1[200],temp3[200];
                strcpy(temp1,"");
                strcpy(temp3,"");

                if (by_rudnik)
                {
                        strcat(temp1,",Rudnik");
                        strcat(temp3,",Rudnik");
                }
                if (by_stvol)
                {
                        strcat(temp1,",Stvol");
                        strcat(temp3,",Stvol");
                }
                if (by_year)
                {
                        strcat(temp1,",Year111");
                        strcat(temp3,",Year111");
                }
                if (by_halfyear)
                {
                        strcat(temp1,",HalfYear111");
                        strcat(temp3,",HalfYear111");
                }
                if (by_quarter)
                {
                        strcat(temp1,",Quarter111");
                        strcat(temp3,",Quarter111");
                }
                if (by_month)
                {
                        strcat(temp1,",Month111");
                        strcat(temp3,",Month111");
                }
                if (by_day)
                {
                        strcat(temp1,",Day111");
                        strcat(temp3,",Day111");
                }
                if (by_smena)
                {
                        strcat(temp1,",Smena111");
                        strcat(temp3,",Smena111");
                }

                if (by_vagon)
                {
                        strcat(temp1,",Sum(Vagon)");
                }
                if (by_tp)
                {
                        strcat(temp1,",Sum(RTP)");
                }
                if (by_cp)
                {
                        strcat(temp1,",Sum(CP)");
                }
                if (by_p)
                {
                        strcat(temp1,",Sum(P)");
                }
                if (by_mh)
                {
                        strcat(temp1,",Sum(MH)");
                }
                if (by_l)
                {
                        strcat(temp1,",Sum(L)");
                }

                temp1[0]=' ';
                temp3[0]=' ';

                strSQL1 += temp1;
                strSQL3 += temp3;

                AnsiString strSQL = strSQL1+strSQL2+strSQL3;

                BalRepForm->Query1->SQL->Clear();
                BalRepForm->Query1->SQL->Add(strSQL);

                BalRepForm->Query1->Active = true;

                if (by_p) ((TFloatField*)BalRepForm->Query1->FieldByName("SUM OF P"))->DisplayFormat = "0.###";
                if (by_mh) ((TFloatField*)BalRepForm->Query1->FieldByName("SUM OF MH"))->DisplayFormat = "0.###";
                if (by_l) ((TFloatField*)BalRepForm->Query1->FieldByName("SUM OF L"))->DisplayFormat = "0.###";

                BalRepForm->ShowModal();

        //-------------------------------

  tst_list->DestroyList();
  delete tst_list;
  }
  else MessageDlg("Нет данных для баланса!", mtWarning, TMsgDlgButtons() << mbYes, 0);
}
}
//---------------------------------------------------------------------------





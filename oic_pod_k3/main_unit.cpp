//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//#include "admin.h"
#include "last_stat.h"
#include "copy_arc.h"
#include "stvol_init.h"
#include "smena.h"
#include "cpu686.h"
#include "main_unit.h"
#include "al_unit.h"
#include "test_unit.h"

#include "threads.h"
#include "hard_test.h"

#include "msg_unit.h"
#include "pause.h"

#include <io.h>
#include <fcntl.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGAUGES"
//#pragma link "AdPacket"
#pragma link "AdPort"
#pragma link "AdProtcl"
#pragma link "AdPStat"
#pragma link "AdTapi"
#pragma link "ADTrmEmu"
#pragma link "AdTStat"
#pragma link "OoMisc"
#pragma resource "*.dfm"
TMainForm *MainForm;
HANDLE hSem;

TGetDataThread *get_data_thread;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
        //--------------------------------------
        LiftRect1 = Rect(932,18,932+24,18+28);
        LiftRect2 = Rect(966,582,966+24,582+28);
        LiftBtmp1 = new Graphics::TBitmap; LiftBtmp1->Width = 24; LiftBtmp1->Height = 28;
        LiftBtmp2 = new Graphics::TBitmap; LiftBtmp2->Width = 24; LiftBtmp2->Height = 28;
        LiftBtmp1->Canvas->CopyRect(Rect(0,0,24,28),Image1->Canvas,LiftRect1);
        LiftBtmp2->Canvas->CopyRect(Rect(0,0,24,28),Image1->Canvas,LiftRect2);
        //--------------------------------------
        GorRect = Rect(916,601,916+8,601+8);
        GorBtmp = new Graphics::TBitmap; GorBtmp->Width = 8; GorBtmp->Height = 8;
        GorBtmp->Canvas->CopyRect(Rect(0,0,8,8),Image1->Canvas,GorRect);
        //--------------------------------------
        H12Rect = Rect(866,75,866+32,75+5);
        H12Btmp = new Graphics::TBitmap; H12Btmp->Width = 32; H12Btmp->Height = 5;
        H12Btmp->Canvas->CopyRect(Rect(0,0,32,5),Image1->Canvas,H12Rect);
        //--------------------------------------

        FileDir = ExtractFilePath(Application->ExeName);

        is_init = false;

        ChannelList = new TVariantList <TChannel>;
        ChannelList->ReadFromFile(FileDir+"channels.dat");

        //---используемые TBI24-0
        UNIO_TBI = new T_UNIO_TBI;
        DISKRET = new T_DISKRET_TBI;

        UNIO_TBI->COUNTERS = 0;
        DISKRET->_1 = DISKRET->_2 = DISKRET->_3 = DISKRET->_4 = false;
        for (int i=0; i<ChannelList->count; i++)
        {
                TChannel *ch = (*ChannelList)[i];
                short FPGA = ch->NFPGA;
                if (ch->ChannelType == tchtDISKRET)
                {
                        if (FPGA == 1) DISKRET->_1 = true;
                        if (FPGA == 2) DISKRET->_2 = true;
                        if (FPGA == 3) DISKRET->_3 = true;
                        if (FPGA == 4) DISKRET->_4 = true;
                }
                else
                if (ch->ChannelType == tchtCOUNTER)
                {
                        UNIO_TBI->COUNTERS = FPGA;
                }
        }

        UNIO_TBI->_1stTBI = UNIO_TBI->_2ndTBI = 0;

        if (DISKRET->_1) UNIO_TBI->_1stTBI = 1;
        else
          if (DISKRET->_2) UNIO_TBI->_1stTBI = 2;
          else
            if (DISKRET->_3) UNIO_TBI->_1stTBI = 3;
            else
              if (DISKRET->_4) UNIO_TBI->_1stTBI = 4;

        if (DISKRET->_4) UNIO_TBI->_2ndTBI = 4;
        else
          if (DISKRET->_3) UNIO_TBI->_2ndTBI = 3;
          else
            if (DISKRET->_2) UNIO_TBI->_2ndTBI = 2;
            else
              if (DISKRET->_1) UNIO_TBI->_2ndTBI = 1;
        //----------------------

        st.current_record = new TArchiveRecord();
        st_prev.current_record = new TArchiveRecord();

        for (int i=0; i<ChannelList->count; i++)
        {
                TChannelData *ch_data = new TChannelData();
                TChannelData *ch_data_prev = new TChannelData();
                ch_data->ChannelID = (*ChannelList)[i]->ChannelID;
                ch_data_prev->ChannelID = (*ChannelList)[i]->ChannelID;
                st.current_record->ChannelDataList->Add(ch_data);
                st_prev.current_record->ChannelDataList->Add(ch_data_prev);
        }

        VisualChannelList = new TVariantList <TVisualisationChannel>;

        sys_koef = new TSysKoef;
        sys_koef->Load();

        sys_param = new TSysParams(FileDir+"options.ini");
        sys_param->Load();

        MainTimer->Interval = sys_param->RefrTime;
        ArcTimer->Interval = sys_param->ArcTime;

        hSem = CreateSemaphore(NULL,1,1,NULL);

        diag_rect = Rect(5,236,5+831,236+403);
        TPoint pk;
        pk.x = 1+1;
        pk.y = diag_rect.Height()-2;
        int log_x = 1;
        int log_y = 1;
        mks = new TKoordSystem(Image1,diag_rect,pk,log_x,log_y);
//        mks->koef.ky = 70+50+50;
  //      mks->koef.kx = 60+100;
//        mks->koef.ky = 30+90;
  //      mks->koef.kx = 30+100;
        mks->koef.ky = 30;
        mks->koef.kx = 30;
        mks->log_koord.x = sys_koef->koef.L_MAX - mks->r.Width()/mks->koef.kx +
                           mks->r.Width()/mks->koef.kx/5;
        mks->log_koord.y = 0;
        mks->bk_col = sys_param->bkcolor;
        if (mks->bk_col == clWhite) mks->text_col = clBlack;

        mks->DrawKoordSystem();
        mks->Redraw();

        diag = new TDiagram(mks,MainForm->ChannelList);
        diag->col = MainForm->sys_param->fcolor;
        diag->line_thickness = 1;
        diag->style = psSolid;

        is_mode_changed = false;
        is_direct_changed = false;
        is_RZT_change_off = false;

        st.mode_id = -1;
        st_prev.DPI = 0;
        st_prev.V = st.V = 0;
        st_prev.tmsec = st.tmsec = 0; 

        diag_low = new TDiagram(mks,MainForm->ChannelList);
        diag_hi = new TDiagram(mks,MainForm->ChannelList);
        diag_work = new TDiagram(mks,MainForm->ChannelList);

        //-------------------
        idRG = GetChannelByNameAndDimension(MainForm->ChannelList,"РГ",tdtON)->ChannelID;
        idRL = GetChannelByNameAndDimension(MainForm->ChannelList,"РЛ",tdtON)->ChannelID;
        idRR = GetChannelByNameAndDimension(MainForm->ChannelList,"РР",tdtON)->ChannelID;
        idRO = GetChannelByNameAndDimension(MainForm->ChannelList,"РО",tdtON)->ChannelID;

        idUtg = GetChannelByNameAndDimension(ChannelList,"Uтг",tdtU)->ChannelID;
        idUtgm = GetChannelByNameAndDimension(MainForm->ChannelList,"Uтг-",tdtU)->ChannelID;
        idUtgp = GetChannelByNameAndDimension(MainForm->ChannelList,"Uтг+",tdtU)->ChannelID;
        idIst = GetChannelByNameAndDimension(ChannelList,"Iст",tdtI)->ChannelID;
        idIdt = GetChannelByNameAndDimension(ChannelList,"Iдт",tdtI)->ChannelID;
        idV = GetChannelByNameAndDimension(ChannelList,"V",tdtSPEED)->ChannelID;

        idRZTon = GetChannelByNameAndDimension(MainForm->ChannelList,"РЗТ",tdtON)->ChannelID;
        idRZToff = GetChannelByNameAndDimension(MainForm->ChannelList,"РЗТ",tdtOFF)->ChannelID;
        idRKZon = GetChannelByNameAndDimension(MainForm->ChannelList,"РКЗ",tdtON)->ChannelID;
        idRKZoff = GetChannelByNameAndDimension(MainForm->ChannelList,"РКЗ",tdtOFF)->ChannelID;
        idRKNon = GetChannelByNameAndDimension(MainForm->ChannelList,"РКН",tdtON)->ChannelID;
        idRKNoff = GetChannelByNameAndDimension(MainForm->ChannelList,"РКН",tdtOFF)->ChannelID;
        idRDZon = GetChannelByNameAndDimension(MainForm->ChannelList,"РДЗ",tdtON)->ChannelID;
        idRDZoff = GetChannelByNameAndDimension(MainForm->ChannelList,"РДЗ",tdtOFF)->ChannelID;
        idRPMon = GetChannelByNameAndDimension(MainForm->ChannelList,"РПМ",tdtON)->ChannelID;
        idRPMoff = GetChannelByNameAndDimension(MainForm->ChannelList,"РПМ",tdtOFF)->ChannelID;
        idRTPon = GetChannelByNameAndDimension(MainForm->ChannelList,"РТП",tdtON)->ChannelID;
        idRTPoff = GetChannelByNameAndDimension(MainForm->ChannelList,"РТП",tdtOFF)->ChannelID;

        id02 = GetChannelByNameAndDimension(MainForm->ChannelList,"0.2",tdtON)->ChannelID;
        id06 = GetChannelByNameAndDimension(MainForm->ChannelList,"0.6",tdtON)->ChannelID;
        id10 = GetChannelByNameAndDimension(MainForm->ChannelList,"1.0",tdtON)->ChannelID;

        idRTPK = GetChannelByNameAndDimension(MainForm->ChannelList,"РТП_К",tdtNONE)->ChannelID;
        idRPMK = GetChannelByNameAndDimension(MainForm->ChannelList,"РПМ_К",tdtNONE)->ChannelID;
        idCP = GetChannelByNameAndDimension(MainForm->ChannelList,"ЦП",tdtNONE)->ChannelID;
        idGR3 = GetChannelByNameAndDimension(MainForm->ChannelList,"ГР3",tdtNONE)->ChannelID;
        idGR5 = GetChannelByNameAndDimension(MainForm->ChannelList,"ГР5",tdtNONE)->ChannelID;
        idP = GetChannelByNameAndDimension(MainForm->ChannelList,"P",tdtP)->ChannelID;
        idL = GetChannelByNameAndDimension(MainForm->ChannelList,"L",tdtNONE)->ChannelID;
        idMH = GetChannelByNameAndDimension(MainForm->ChannelList,"MH",tdtNONE)->ChannelID;
        idALARM = GetChannelByNameAndDimension(MainForm->ChannelList,"ALARM",tdtNONE)->ChannelID;

        idH = GetChannelByNameAndDimension(MainForm->ChannelList,"H",tdtNONE)->ChannelID;
        idDPI = GetChannelByNameAndDimension(MainForm->ChannelList,"ДПИ-1",tdtNONE)->ChannelID;
        //-------------------

//        tf = fopen("test.dat","wt");

        ActGorImage->Canvas->Brush->Color = clRed;
        ActGorImage->Canvas->Pen->Color = clBlack;
        ActGorImage->Canvas->Rectangle(ActGorImage->ClientRect);

        ControlStyle = TControlStyle() << csOpaque;

        alarm_id = 0;

        // инициализация звука
        AnsiString w_name;
        w_name = MainForm->sys_param->MediaDir;
        w_name += "\\ringin.wav";

        HFILE hf = _lopen(w_name.c_str(),OF_READ);
        Word w_size = _llseek(hf,0L,2);
        _llseek(hf,0L,0);
        hWave = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE, w_size);
        waveBuf = (char *)GlobalLock(hWave);
        if (waveBuf != NULL)
        {
                _hread(hf,waveBuf,w_size);
        }
        _lclose(hf);
        //--------------------

        btmp = new Graphics::TBitmap;

        AnsiString media_dir = sys_param->MediaDir;
        Animate1->FileName = media_dir+"\\"+"search.avi";
        Animate1->Active = true;

        _1st_boot = true;

        archive = NULL;

        AnsiString cat_name = sys_param->SysDir;
        cat_name += "\\catalog.dat";
        arc_cat = new TArcCatalog(cat_name,sys_param);
        arc_cat->Load();

        //------------------------------------------
        ApdComPort1->ComNumber = sys_param->comm.COM_PORT_ID+1;

//        Memo2->Lines->Add("Waiting...");

        ApdProtocol1->DestinationDirectory = sys_param->SysDir;

//        ApdTapiDevice1->AutoAnswer();
  //      Memo2->Lines->Add("Listening...&& Cancelling...");
        //------------------------------------------

        RKZ_count_vagon = 1;

        AnsiString sys_dir;
        sys_dir = MainForm->sys_param->SysDir;

        users = new TLogRecList();
        users->ReadFromFile(sys_dir+"\\users.dat");

        pause_time = 0;
        pause_start = true;

        war_list = new TWarningList();

                hpp = 0;

                h0 = MainForm->sys_koef->koef.hpp_0;

                h1 = MainForm->sys_koef->koef.hpp_0+
                     MainForm->sys_koef->koef.h0_1;

                h2 = MainForm->sys_koef->koef.hpp_0+
                     MainForm->sys_koef->koef.h0_1+
                     MainForm->sys_koef->koef.h1_2;

                h3 = MainForm->sys_koef->koef.hpp_0+
                     MainForm->sys_koef->koef.h0_1+
                     MainForm->sys_koef->koef.h1_2+
                     MainForm->sys_koef->koef.h2_3;

                h4 = MainForm->sys_koef->koef.hpp_0+
                     MainForm->sys_koef->koef.h0_1+
                     MainForm->sys_koef->koef.h1_2+
                     MainForm->sys_koef->koef.h2_3+
                     MainForm->sys_koef->koef.h3_4;

                h5 = MainForm->sys_koef->koef.hpp_0+
                     MainForm->sys_koef->koef.h0_1+
                     MainForm->sys_koef->koef.h1_2+
                     MainForm->sys_koef->koef.h2_3+
                     MainForm->sys_koef->koef.h3_4+
                     MainForm->sys_koef->koef.h4_5;

//---------------------------------------------------------------
        sys_koef->koef.L_MAX = sys_koef->koef.hpp_0+
                          sys_koef->koef.h0_1+
                          sys_koef->koef.h1_2+
                          sys_koef->koef.h2_3+
                          sys_koef->koef.h3_4+
                          sys_koef->koef.h4_5;
        gor_act = 5;

        st.Hl = 0;
        st.Hr = sys_koef->koef.L_MAX;
        st.direct = 1;

        GetPeresm();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SetAlarm(short al_id,AnsiString capt)
{
        alarm_id = al_id;
        MemoLog->Lines->Add(capt);
}

void __fastcall TMainForm::Del48files()
{
        AnsiString arcfname,stafname;
        TArcFileState flag;
        TArcStat stat;
        FILE *f;

        int c = arc_cat->list->count;
        for (int i=0; i < c; i++)
        {
                arcfname = (*arc_cat->list)[i]->fname;
                stafname = arcfname;
                flag = (*arc_cat->list)[i]->flag;

                if (flag != tafsCURRENT)// && flag != tafsACTUAL)
                {
//                        arcfname += ".rar";
                        stafname += ".sta";

                        f = fopen(stafname.c_str(),"rb");
                        fread(&stat,sizeof(TArcStat),1,f);
                        fclose(f);

                        Word day1,month1,year1;
                        DecodeDate(stat.date_time,year1,month1,day1);

                        Word day2,month2,year2;
                        DecodeDate(Date(),year2,month2,day2);

                        if ( ((day2-day1) >= 3) ||
                             (month1 != 2 && day2 < day1 && (day1-day2) <= 28) ||
                             (month1 == 2 && day2 < day1 && (day1-day2) <= 25) )
                        {
                                arc_cat->DelFileFromDisk(arcfname);
                                arc_cat->Save();
                                c = arc_cat->list->count;
                                i = 0;
                        }
                }
        }
}

void TMainForm::UpdateKS()
{
        if (diag->lp_list->count == 0)
        {
                mks->log_koord.x = sys_koef->koef.L_MAX - mks->r.Width()/mks->koef.kx +
                                mks->r.Width()/mks->koef.kx/5;
        }
        else
        {
//                mks->log_koord.x = (*diag->lp_list)[diag->lp_list->count-1]->x-4;
                mks->log_koord.x = (*diag->lp_list)[diag->lp_list->count-1]->x-mks->r.Width()/mks->koef.kx+1;
        }
        mks->DrawKoordSystem();
        mks->Redraw();
}

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
        delete UNIO_TBI;
        delete DISKRET;

        ChannelList->DestroyList();
        delete ChannelList;

        VisualChannelList->DestroyList();
        delete VisualChannelList;

        if (archive)
        {
                delete archive;
        }

        delete sys_param;
        delete sys_koef;
        delete st.current_record;
        delete st_prev.current_record;

        CloseHandle(hSem);
        delete this->diag;
        delete this->diag_hi;
        delete this->diag_low;
        delete this->diag_work;
        delete this->mks;

//        fclose(tf);

        GlobalUnlock(waveBuf);
        GlobalFree(waveBuf);

        delete btmp;
        delete LiftBtmp1;
        delete LiftBtmp2;
        delete GorBtmp;
        delete H12Btmp;

        delete arc_cat;

        users->DestroyList();
        delete users;

        war_list->DestroyList();
        delete war_list;
}

// проверка целостности файла-архива
bool TMainForm::CheckCorrectArcSize(AnsiString f_name,TChannelList *ch_list)
{
        long fsize;
        bool flag;

        int handle = open(f_name.c_str(),O_CREAT);
        fsize = filelength(handle);
        close(handle);

        long n_beg = 0;//sizeof(int);
        long nk = sizeof(TDateTime)+2*sizeof(long)+
                  (GetChannelCount(ch_list,tchtANALOG)-2)*sizeof(float)+
                  (GetChannelCount(ch_list,tchtCOUNTER)-1)*sizeof(float)+
                  (GetChannelCount(ch_list,tchtPROGRAM)-5)*sizeof(float);

        if ( (fsize-n_beg)%nk == 0 ) flag = true;
        else flag = false;

        return flag;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::DateTimerTimer(TObject *Sender)
{
        MainStatusBar->Panels->Items[0]->Text =
        " Дата: "+ DateToStr(Date())+ "    Текущее время: "+ TimeToStr(Time());
}
//---------------------------------------------------------------------------
// проверить состояние системы на предмет окончания цикла подъема (спуска)
void TMainForm::CheckUpEnd()
{
        if (st_prev.V > st.V && st.V == 0)
        {
                MemoLog->Lines->Add("Подъем остановлен "+TimeToStr(Time()));
        }
}

void __fastcall TMainForm::MainTimerTimer(TObject *Sender)
{
        if (MemoLog->Lines->Count > 300)
        {
                MemoLog->Lines->Clear();
        }

        //--------------------------

        TDateTime t = Time();
        Word hour,min,sec,msec;
        DecodeTime(t,hour,min,sec,msec);

        float hour2 = hour + min/60.0;

        if ( (hour2 >= sys_param->DayTime2-sys_param->dt_peresm/60.0 &&
              hour2 < sys_param->DayTime2+sys_param->dt_peresm/60.0)
              ||
             (hour2 >= sys_param->DayTime1-sys_param->dt_peresm/60.0 &&
              hour2 < sys_param->DayTime1+sys_param->dt_peresm/60.0) )
        {
                was_avto_peresm = false;

//                if (!was_man_peresm) SmenaButton->Enabled = true;
  //              else;
        }
        else
        {
                if (!was_man_peresm && !was_avto_peresm)
                {

                        GetPeresm();
                        was_avto_peresm = true;
                }

                was_man_peresm = false;
        }

        if (!is_init)
        {
                is_init = true;

                LSB = 9.84 / 1000000;
                G = 0;

//                if (AdminForm->ProgRadioButton->Checked)
  //              {
    //            }
      //          if (AdminForm->HardRadioButton->Checked)
        //        {
                // инициализация "железа"
                    //    init_UNIO();
                      //  init_AI();
          //      }

                TVisualisationChannel* ch;
                // инициализация всех каналов отображения

//------------------------------------------------------------------------------------------------
// новые семь каналов

                ch = new TVisualisationChannel(tchtDISKRET,st.current_record);
                ch->ChannelID_on = GetChannelByNameAndDimension(ChannelList,"АВ-1",tdtON)->ChannelID;
                ch->ChannelID_off = -1;
                ch->ch_id_on_data = (*st.current_record->ChannelDataList)[ch->ChannelID_on];
                ch->ch_id_off_data = NULL;
                ch->col = GetChannelByNameAndDimension(ChannelList,"АВ-1",tdtON)->col;
                ch->coloff = GetChannelByNameAndDimension(ChannelList,"АВ-1",tdtON)->col_nact;
                ch->capt = "АВ-1 РМа РМс РМ";
                ch->r = Rect(422,93,524,107);
                VisualChannelList->Add(ch);    

                ch = new TVisualisationChannel(tchtDISKRET,st.current_record);
                ch->ChannelID_on = GetChannelByNameAndDimension(ChannelList,"РВПУ",tdtON)->ChannelID;
                ch->ChannelID_off = -1;
                ch->ch_id_on_data = (*st.current_record->ChannelDataList)[ch->ChannelID_on];
                ch->ch_id_off_data = NULL;
                ch->col = GetChannelByNameAndDimension(ChannelList,"РВПУ",tdtON)->col;
                ch->coloff = GetChannelByNameAndDimension(ChannelList,"РВПУ",tdtON)->col_nact;
                ch->capt = "РВПУ ЭОС-3 УПА ЛАК";
                ch->r = Rect(531,93,654,107);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtDISKRET,st.current_record);
                ch->ChannelID_on = GetChannelByNameAndDimension(ChannelList,"ЭВ-21",tdtON)->ChannelID;
                ch->ChannelID_off = -1;
                ch->ch_id_on_data = (*st.current_record->ChannelDataList)[ch->ChannelID_on];
                ch->ch_id_off_data = NULL;
                ch->col = GetChannelByNameAndDimension(ChannelList,"ЭВ-21",tdtON)->col;
                ch->coloff = GetChannelByNameAndDimension(ChannelList,"ЭВ-21",tdtON)->col_nact;
                ch->capt = "ЭВ-21 ВП1";
                ch->r = Rect(661,93,720,107);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtDISKRET,st.current_record);
                ch->ChannelID_on = GetChannelByNameAndDimension(ChannelList,"РОКп",tdtON)->ChannelID;
                ch->ChannelID_off = -1;
                ch->ch_id_on_data = (*st.current_record->ChannelDataList)[ch->ChannelID_on];
                ch->ch_id_off_data = NULL;
                ch->col = GetChannelByNameAndDimension(ChannelList,"РОКп",tdtON)->col;
                ch->coloff = GetChannelByNameAndDimension(ChannelList,"РОКп",tdtON)->col_nact;
                ch->capt = "РОКп ВИК1-2 РОК-Л";
                ch->r = Rect(414,114,525,128);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtDISKRET,st.current_record);
                ch->ChannelID_on = GetChannelByNameAndDimension(ChannelList,"ЭВ-1",tdtON)->ChannelID;
                ch->ChannelID_off = -1;
                ch->ch_id_on_data = (*st.current_record->ChannelDataList)[ch->ChannelID_on];
                ch->ch_id_off_data = NULL;
                ch->col = GetChannelByNameAndDimension(ChannelList,"ЭВ-1",tdtON)->col;
                ch->coloff = GetChannelByNameAndDimension(ChannelList,"ЭВ-1",tdtON)->col_nact;
                ch->capt = "ЭВ-1 ВП2";
                ch->r = Rect(532,114,590,128);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtDISKRET,st.current_record);
                ch->ChannelID_on = GetChannelByNameAndDimension(ChannelList,"У-4",tdtON)->ChannelID;
                ch->ChannelID_off = -1;
                ch->ch_id_on_data = (*st.current_record->ChannelDataList)[ch->ChannelID_on];
                ch->ch_id_off_data = NULL;
                ch->col = GetChannelByNameAndDimension(ChannelList,"У-4",tdtON)->col;
                ch->coloff = GetChannelByNameAndDimension(ChannelList,"У-4",tdtON)->col_nact;
                ch->capt = "У-4 У-8 РОС";
                ch->r = Rect(597,114,665,128);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtDISKRET,st.current_record);
                ch->ChannelID_on = GetChannelByNameAndDimension(ChannelList,"РК-Т",tdtON)->ChannelID;
                ch->ChannelID_off = -1;
                ch->ch_id_on_data = (*st.current_record->ChannelDataList)[ch->ChannelID_on];
                ch->ch_id_off_data = NULL;
                ch->col = GetChannelByNameAndDimension(ChannelList,"РК-Т",tdtON)->col;
                ch->coloff = GetChannelByNameAndDimension(ChannelList,"РК-Т",tdtON)->col_nact;
                ch->capt = "РАО РК-Т";
                ch->r = Rect(672,114,728,128);
                VisualChannelList->Add(ch);

//------------------------------------------------------------------------------------------------
                ch = new TVisualisationChannel(tchtDISKRET,st.current_record);
                ch->ChannelID_on = GetChannelByNameAndDimension(ChannelList,"0.2",tdtON)->ChannelID;
                ch->ChannelID_off = -1;
                ch->ch_id_on_data = (*st.current_record->ChannelDataList)[ch->ChannelID_on];
                ch->ch_id_off_data = NULL;
                ch->col = GetChannelByNameAndDimension(ChannelList,"0.2",tdtON)->col;
                ch->coloff = GetChannelByNameAndDimension(ChannelList,"0.2",tdtON)->col_nact;
                ch->capt = "0.2";
                ch->r = Rect(634,62,634+29,62+14);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtDISKRET,st.current_record);
                ch->ChannelID_on = GetChannelByNameAndDimension(ChannelList,"0.6",tdtON)->ChannelID;
                ch->ChannelID_off = -1;
                ch->ch_id_on_data = (*st.current_record->ChannelDataList)[ch->ChannelID_on];
                ch->ch_id_off_data = NULL;
                ch->col = GetChannelByNameAndDimension(ChannelList,"0.6",tdtON)->col;
                ch->coloff = GetChannelByNameAndDimension(ChannelList,"0.6",tdtON)->col_nact;
                ch->capt = "0.6";
                ch->r = Rect(670,62,670+29,62+14);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtDISKRET,st.current_record);
                ch->ChannelID_on = GetChannelByNameAndDimension(ChannelList,"1.0",tdtON)->ChannelID;
                ch->ChannelID_off = -1;
                ch->ch_id_on_data = (*st.current_record->ChannelDataList)[ch->ChannelID_on];
                ch->ch_id_off_data = NULL;
                ch->col = GetChannelByNameAndDimension(ChannelList,"1.0",tdtON)->col;
                ch->coloff = GetChannelByNameAndDimension(ChannelList,"1.0",tdtON)->col_nact;
                ch->capt = "1.0";
                ch->r = Rect(706,62,706+29,62+14);
                VisualChannelList->Add(ch);

//------------------------------------------------------------------------------------------------

                ch = new TVisualisationChannel(tchtDISKRET,st.current_record);
                ch->ChannelID_on = GetChannelByNameAndDimension(ChannelList,"РГ",tdtON)->ChannelID;
                ch->ChannelID_off = -1;
                ch->ch_id_on_data = (*st.current_record->ChannelDataList)[ch->ChannelID_on];
                ch->ch_id_off_data = NULL;
                ch->col = GetChannelByNameAndDimension(ChannelList,"РГ",tdtON)->col;
                ch->coloff = clWhite;
                ch->capt = "РГ";
                ch->r = Rect(408,31,408+27,31+14);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtDISKRET,st.current_record);
                ch->ChannelID_on = GetChannelByNameAndDimension(ChannelList,"РЛ",tdtON)->ChannelID;
                ch->ChannelID_off = -1;
                ch->ch_id_on_data = (*st.current_record->ChannelDataList)[ch->ChannelID_on];
                ch->ch_id_off_data = NULL;
                ch->col = GetChannelByNameAndDimension(ChannelList,"РЛ",tdtON)->col;
                ch->coloff = clWhite;
                ch->capt = "РЛ";
                ch->r = Rect(442,31,442+27,31+14);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtDISKRET,st.current_record);
                ch->ChannelID_on = GetChannelByNameAndDimension(ChannelList,"РР",tdtON)->ChannelID;
                ch->ChannelID_off = -1;
                ch->ch_id_on_data = (*st.current_record->ChannelDataList)[ch->ChannelID_on];
                ch->ch_id_off_data = NULL;
                ch->col = GetChannelByNameAndDimension(ChannelList,"РР",tdtON)->col;
                ch->coloff = clWhite;
                ch->capt = "РР";
                ch->r = Rect(476,31,476+27,31+14);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtDISKRET,st.current_record);
                ch->ChannelID_on = GetChannelByNameAndDimension(ChannelList,"РО",tdtON)->ChannelID;
                ch->ChannelID_off = -1;
                ch->ch_id_on_data = (*st.current_record->ChannelDataList)[ch->ChannelID_on];
                ch->ch_id_off_data = NULL;
                ch->col = GetChannelByNameAndDimension(ChannelList,"РО",tdtON)->col;
                ch->coloff = clWhite;                
                ch->capt = "РО";
                ch->r = Rect(510,31,510+27,31+14);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtDISKRET,st.current_record);
                ch->ChannelID_on = GetChannelByNameAndDimension(ChannelList,"РЗТ",tdtON)->ChannelID;
                ch->ChannelID_off = GetChannelByNameAndDimension(ChannelList,"РЗТ",tdtOFF)->ChannelID;
                ch->ch_id_on_data = (*st.current_record->ChannelDataList)[ch->ChannelID_on];
                ch->ch_id_off_data = (*st.current_record->ChannelDataList)[ch->ChannelID_off];
                ch->col = GetChannelByNameAndDimension(ChannelList,"РЗТ",tdtON)->col;
                ch->coloff = GetChannelByNameAndDimension(ChannelList,"РЗТ",tdtON)->col_nact;
                ch->capt = "РЗТ";
                ch->r = Rect(516,62,516+29,62+14);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtDISKRET,st.current_record);
                ch->ChannelID_on = GetChannelByNameAndDimension(ChannelList,"РПМ",tdtON)->ChannelID;
                ch->ChannelID_off = GetChannelByNameAndDimension(ChannelList,"РПМ",tdtOFF)->ChannelID;
                ch->ch_id_on_data = (*st.current_record->ChannelDataList)[ch->ChannelID_on];
                ch->ch_id_off_data = (*st.current_record->ChannelDataList)[ch->ChannelID_off];
                ch->col = GetChannelByNameAndDimension(ChannelList,"РПМ",tdtON)->col;
                ch->coloff = GetChannelByNameAndDimension(ChannelList,"РПМ",tdtON)->col_nact;
                ch->capt = "РПМ";
                ch->r = Rect(444,62,444+29,62+14);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtDISKRET,st.current_record);
                ch->ChannelID_on = GetChannelByNameAndDimension(ChannelList,"РКН",tdtON)->ChannelID;
                ch->ChannelID_off = GetChannelByNameAndDimension(ChannelList,"РКН",tdtOFF)->ChannelID;
                ch->ch_id_on_data = (*st.current_record->ChannelDataList)[ch->ChannelID_on];
                ch->ch_id_off_data = (*st.current_record->ChannelDataList)[ch->ChannelID_off];
                ch->col = GetChannelByNameAndDimension(ChannelList,"РКН",tdtON)->col;
                ch->coloff = GetChannelByNameAndDimension(ChannelList,"РКН",tdtON)->col_nact;
                ch->capt = "РКН";
                ch->r = Rect(480,62,480+29,62+14);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtDISKRET,st.current_record);
                ch->ChannelID_on = GetChannelByNameAndDimension(ChannelList,"РДЗ",tdtON)->ChannelID;
                ch->ChannelID_off = GetChannelByNameAndDimension(ChannelList,"РДЗ",tdtOFF)->ChannelID;
                ch->ch_id_on_data = (*st.current_record->ChannelDataList)[ch->ChannelID_on];
                ch->ch_id_off_data = (*st.current_record->ChannelDataList)[ch->ChannelID_off];
                ch->col = GetChannelByNameAndDimension(ChannelList,"РДЗ",tdtON)->col;
                ch->coloff = GetChannelByNameAndDimension(ChannelList,"РДЗ",tdtON)->col_nact;
                ch->capt = "РДЗ";
                ch->r = Rect(588,62,588+29,62+14);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtDISKRET,st.current_record);
                ch->ChannelID_on = GetChannelByNameAndDimension(ChannelList,"РКЗ",tdtON)->ChannelID;
                ch->ChannelID_off = GetChannelByNameAndDimension(ChannelList,"РКЗ",tdtOFF)->ChannelID;
                ch->ch_id_on_data = (*st.current_record->ChannelDataList)[ch->ChannelID_on];
                ch->ch_id_off_data = (*st.current_record->ChannelDataList)[ch->ChannelID_off];
                ch->col = GetChannelByNameAndDimension(ChannelList,"РКЗ",tdtON)->col;
                ch->coloff = GetChannelByNameAndDimension(ChannelList,"РКЗ",tdtON)->col_nact;
                ch->capt = "РКЗ";
                ch->r = Rect(552,62,552+29,62+14);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtDISKRET,st.current_record);
                ch->ChannelID_on = GetChannelByNameAndDimension(ChannelList,"РТП",tdtON)->ChannelID;
                ch->ChannelID_off = GetChannelByNameAndDimension(ChannelList,"РТП",tdtOFF)->ChannelID;
                ch->ch_id_on_data = (*st.current_record->ChannelDataList)[ch->ChannelID_on];
                ch->ch_id_off_data = (*st.current_record->ChannelDataList)[ch->ChannelID_off];
                ch->col = GetChannelByNameAndDimension(ChannelList,"РТП",tdtON)->col;
                ch->coloff = GetChannelByNameAndDimension(ChannelList,"РТП",tdtON)->col_nact;                
                ch->capt = "РТП";
                ch->r = Rect(408,62,408+29,62+14);
                VisualChannelList->Add(ch);

                //--------------------------------------------------------------
                ch = new TVisualisationChannel(tchtANALOG,st.current_record);
                ch->ChannelID_analog = GetChannelByNameAndDimension(ChannelList,"Uтг",tdtU)->ChannelID;
                ch->control = this->UtgImage;
                ch->ch_id_analog_data = (*st.current_record->ChannelDataList)[ch->ChannelID_analog];
                ch->capt = "Uтг";
                ch->r = Rect(10,111,194,205);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtANALOG,st.current_record);
                ch->ChannelID_analog = GetChannelByNameAndDimension(ChannelList,"Iст",tdtI)->ChannelID;
                ch->control = this->IstImage;
                ch->ch_id_analog_data = (*st.current_record->ChannelDataList)[ch->ChannelID_analog];
                ch->capt = "Iст";
                ch->r = Rect(204,10,388,104);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtANALOG,st.current_record);
                ch->ChannelID_analog = GetChannelByNameAndDimension(ChannelList,"Iдт",tdtI)->ChannelID;
                ch->capt = "Iдт";
                ch->ch_id_analog_data = (*st.current_record->ChannelDataList)[ch->ChannelID_analog];
                ch->control = this->IdtImage;
                ch->r = Rect(10,10,194,104);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtANALOG,st.current_record);//?
                ch->ChannelID_analog = GetChannelByNameAndDimension(ChannelList,"P",tdtP)->ChannelID;
                ch->capt = "P";
                ch->ch_id_analog_data = (*st.current_record->ChannelDataList)[ch->ChannelID_analog];
                ch->r = Rect(606,170,659,183);
                VisualChannelList->Add(ch);

                //--------------------------------------------------------------
                ch = new TVisualisationChannel(tchtPROGRAM,st.current_record);
                ch->ChannelID_analog = GetChannelByNameAndDimension(ChannelList,"V",tdtSPEED)->ChannelID;
                ch->control = this->VImage;
                ch->ch_id_analog_data = (*st.current_record->ChannelDataList)[ch->ChannelID_analog];
                ch->col = GetChannelByNameAndDimension(ChannelList,"V",tdtSPEED)->col;
                ch->capt = "SPEED";
                ch->r = Rect(204,111,388,205);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtPROGRAM,st.current_record);
                ch->ChannelID_analog = GetChannelByNameAndDimension(ChannelList,"H",tdtNONE)->ChannelID;
                ch->ch_id_analog_data = (*st.current_record->ChannelDataList)[ch->ChannelID_analog];
                ch->capt = "H";
                ch->r = Rect(917,621,917+88,621+17);
                VisualChannelList->Add(ch);
                //--------------------------------------------------------------
                ch = new TVisualisationChannel(tchtPROGRAM,st.current_record);
                ch->ChannelID_analog = GetChannelByNameAndDimension(ChannelList,"РТП_К",tdtNONE)->ChannelID;
                ch->ch_id_analog_data = (*st.current_record->ChannelDataList)[ch->ChannelID_analog];
                ch->capt = "РТП_К";
                ch->r = Rect(802,170,830,183);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtPROGRAM,st.current_record);
                ch->ChannelID_analog = GetChannelByNameAndDimension(ChannelList,"РПМ_К",tdtNONE)->ChannelID;
                ch->ch_id_analog_data = (*st.current_record->ChannelDataList)[ch->ChannelID_analog];
                ch->capt = "РПМ_К";
                ch->r = Rect(802,191,830,204);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtPROGRAM,st.current_record);
                ch->ChannelID_analog = GetChannelByNameAndDimension(ChannelList,"ЦП",tdtNONE)->ChannelID;
                ch->ch_id_analog_data = (*st.current_record->ChannelDataList)[ch->ChannelID_analog];
                ch->capt = "ЦП";
                ch->r = Rect(704,170,757,183);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtPROGRAM,st.current_record);
                ch->ChannelID_analog = GetChannelByNameAndDimension(ChannelList,"L",tdtNONE)->ChannelID;
                ch->ch_id_analog_data = (*st.current_record->ChannelDataList)[ch->ChannelID_analog];
                ch->capt = "L";
                ch->r = Rect(606,191,659,204);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtPROGRAM,st.current_record);
                ch->ChannelID_analog = GetChannelByNameAndDimension(ChannelList,"ГР3",tdtNONE)->ChannelID;
                ch->ch_id_analog_data = (*st.current_record->ChannelDataList)[ch->ChannelID_analog];
                ch->capt = "ГР3";
                ch->r = Rect(543,170,571,183);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtPROGRAM,st.current_record);
                ch->ChannelID_analog = GetChannelByNameAndDimension(ChannelList,"ГР5",tdtNONE)->ChannelID;
                ch->ch_id_analog_data = (*st.current_record->ChannelDataList)[ch->ChannelID_analog];
                ch->capt = "ГР5";
                ch->r = Rect(543,191,571,204);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtPROGRAM,st.current_record);
                ch->ChannelID_analog = GetChannelByNameAndDimension(ChannelList,"MH",tdtNONE)->ChannelID;
                ch->ch_id_analog_data = (*st.current_record->ChannelDataList)[ch->ChannelID_analog];
                ch->capt = "MH";
                ch->r = Rect(704,191,757,204);
                VisualChannelList->Add(ch);

                ch = new TVisualisationChannel(tchtPROGRAM,st.current_record);
                ch->ChannelID_analog = GetChannelByNameAndDimension(ChannelList,"ALARM",tdtNONE)->ChannelID;
                ch->ch_id_analog_data = (*st.current_record->ChannelDataList)[ch->ChannelID_analog];
                ch->capt = "ALARM";
                ch->r = Rect(549,5,677,50);
                VisualChannelList->Add(ch);
                //--------------------------------------------------------------

                GetData();
                st.mode_id = -1;
                        mks->log_koord.x = sys_koef->koef.L_MAX - mks->r.Width()/mks->koef.kx +
                                                mks->r.Width()/mks->koef.kx/5;

//                MainTimer->Enabled = true;
                ArcTimer->Enabled = true;
        }
        else
        {
        }

        DWORD WaitReturn;

        WaitReturn = WaitForSingleObject(hSem,INFINITE);
        if (WaitReturn == WAIT_OBJECT_0)
        {
        GetData();
        GetChannelChanges();
        GetProgramData();

                GetDiagramFromEtalon();

                for (int i=0; i<VisualChannelList->count; i++)
                {
                        (*VisualChannelList)[i]->Repaint();
                }

                //---------------------------

                // горизонт выдачи
                if (gor_act == -1) ActGorImage->Top = 37;
                else
                if (gor_act == 0) ActGorImage->Top = 131;
                else
                if (gor_act == 1) ActGorImage->Top = 225;
                else
                if (gor_act == 2) ActGorImage->Top = 319;
                else
                if (gor_act == 3) ActGorImage->Top = 413;
                else
                if (gor_act == 4) ActGorImage->Top = 507;
                else
                if (gor_act == 5) ActGorImage->Top = 601;

                TRect r = Rect(GorRect.Left,ActGorImage->Top,GorRect.Right,ActGorImage->Top+8);
                Image1->Canvas->CopyRect(GorRect,GorBtmp->Canvas,Rect(0,0,8,8));
                Image1->Canvas->CopyRect(r,ActGorImage->Canvas,Rect(0,0,8,8));
                GorRect = r;
                //----------------

                if (is_RZT_change_off || is_mode_changed)
                {
                        diag->lp_list->DestroyList();
                        delete diag;
                        diag = new TDiagram(mks,MainForm->ChannelList);
                        diag->col = sys_param->fcolor;
                        diag->line_thickness = 1;
                        diag->style = psSolid;                
                }

                // если изменилось направление движения левой клети
                if (this->is_direct_changed || is_RPM_change_off)
                {
                        mks->log_koord.x = sys_koef->koef.L_MAX - mks->r.Width()/mks->koef.kx +
                                                mks->r.Width()/mks->koef.kx/5;
                        mks->DrawKoordSystem();

                        diag->lp_list->DestroyList();
                        delete diag;
                        diag = new TDiagram(mks,MainForm->ChannelList);
                        diag->col = sys_param->fcolor;
                        diag->line_thickness = 1;
                        diag->style = psSolid;
                }

                // scrolling диаграммы----------------------------------
                if (st_prev.sign_Utg != st.sign_Utg)
                {
                        if (st.sign_Utg == -1) mks->log_koord.x = st.Hr-3;
                        else if (st.sign_Utg == 1) mks->log_koord.x = st.Hl-3;
                }

                mks->log_koord.x -= dH;

                float Lraz = sys_koef->koef.L_MAX-
                                        sys_koef->koef.mode_koefs[st.mode_id].L_oth-
                                                sys_koef->koef.mode_koefs[st.mode_id].L_razg;
                float Lzam = sys_koef->koef.mode_koefs[st.mode_id].L_dot+sys_koef->koef.mode_koefs[st.mode_id].L_zam;

                if (st.Hl >= 0 && st.Hl <= sys_koef->koef.mode_koefs[st.mode_id].L_dot+5.0 ||
                        st.Hl >= sys_koef->koef.L_MAX-sys_koef->koef.mode_koefs[st.mode_id].L_oth-5.0 &&
                        st.Hl <= sys_koef->koef.L_MAX)
                {
                        mks->koef.kx = 200;
                        mks->koef.ky = 410;
                }
                else
                {
                        mks->koef.kx = 80;
                        mks->koef.ky = 210;
                }

                float dV = st.V - st_prev.V;

                if (mks->log_koord.y < 0)
                {
                        mks->log_koord.y = 0;
                }

                if (dV > 0 && st.V-mks->log_koord.y > 1.0*mks->log_y)
                {
                        mks->log_koord.y += dV;
                }
                else
                if (dV < 0 && mks->log_koord.y != 0)
                {
                        mks->log_koord.y += dV;
                }

                if (mks->log_koord.x <= 0)
                {
                // выравнивание диаграмм по нулю при приближении к ПП
                // (погрешность длины ствола, канат)
                        if (mks->log_koord.x < 0)
                        {
                                mks->log_koord.x = 0;
                        }
                }

                mks->DrawKoordSystem();
                diag_work->RedrawWithOutNodes();
                diag_hi->RedrawWithOutNodes();
                diag_low->RedrawWithOutNodes();
  
                TLogPoint *vp = new TLogPoint;
                if (st.direct == -1)
                {
                        vp->x = st.Hl;
                }
                if (st.direct == 1)
                {
                        vp->x = sys_koef->koef.L_MAX-st.Hl;
                }
                vp->y = st.V;

            if (!is_RPM_on && is_RPM_off)
            {
                if (diag->lp_list->count <= 1) diag->lp_list->Add(vp);
                if (diag->lp_list->count > 1 && vp->x != (*diag->lp_list)[diag->lp_list->count-2]->x)
                        diag->lp_list->Add(vp);
                diag->DrawPoint(vp);
                diag->RedrawWithOutNodes();

                // установка alarm_id по скорости---------
                float alvw,alvl,alvh;
                alvw = GetVFromList(vp->x,diag_work->lp_list);
                alvl = GetVFromList(vp->x,diag_low->lp_list);
                alvh = GetVFromList(vp->x,diag_hi->lp_list);

                // "нормальный" режим
                if (vp->y <= alvl)
                {
                        alarm_id = 0;
                }
                // "сигнальный" интервал
                if (vp->y > alvl && vp->y < alvh)
                {
                        SetAlarm(1,"ВНИМАНИЕ!!! ПРЕВЫШЕН СИГНАЛЬНЫЙ УРОВЕНЬ СКОРОСТИ");
                }
                // "критический" уровень
                if (vp->y > alvh)
                {
                        SetAlarm(2,"ВНИМАНИЕ!!! ПРЕВЫШЕН КРИТИЧЕСКИЙ УРОВЕНЬ СКОРОСТИ");
                }
                //----------------------------------------
                // по состоянию каналов

                if (is_RTP_on && is_RTP_off) alarm_id = 2;
                if (!is_RTP_on && !is_RTP_off) alarm_id = 2;

                if (is_RPM_on && is_RPM_off) alarm_id = 2;
                if (!is_RPM_on && !is_RPM_off) alarm_id = 2;

                if (is_RKN_on && is_RKN_off) alarm_id = 2;
                if (!is_RKN_on && !is_RKN_off) alarm_id = 2;

                if (is_RZT_on && is_RZT_off) alarm_id = 2;
                if (!is_RZT_on && !is_RZT_off) alarm_id = 2;

                if (is_RKZ_on && is_RKZ_off) alarm_id = 2;
                if (!is_RKZ_on && !is_RKZ_off) alarm_id = 2;

                if (is_RDZ_on && is_RDZ_off) alarm_id = 2;
                if (!is_RDZ_on && !is_RDZ_off) alarm_id = 2;

                if (!is_RDZ_on && is_RDZ_off && MainForm->st.V!=0) // если РДЗ = 0
                {
                        alarm_id = 2;
                        MsgForm->Label1->Caption = "Двери открыты!";
//                        MsgForm->Show();
                }
                if (is_RTP_off)
                {
                        alarm_id = 2;
                        MsgForm->Label1->Caption = "РТП";
//                        MsgForm->Show();
                }
                //----------------------------------------

            }
            mks->Redraw();
                //------------------------------------------------------

                // проверить состояние системы на предмет окончания цикла подъема
                CheckUpEnd();
        }
        ReleaseSemaphore(hSem,1,NULL);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ArcTimerTimer(TObject *Sender)
{
        DWORD WaitReturn;

        WaitReturn = WaitForSingleObject(hSem,INFINITE);
        if (WaitReturn == WAIT_OBJECT_0)
        {
                st.current_record->date_time = Date()+Time();
                archive->AppendToFile(st.current_record,ChannelList);

                // перезапись статистики
                archive->ReadStat(&(archive->arc_stat));
                //------------------------
                archive->arc_stat.RTP_count = RTP_count;
                archive->arc_stat.RPM_count = RPM_count;
                archive->arc_stat.CP_count = CP_count;
                archive->arc_stat.Total_L_count = Total_L_count;
                archive->arc_stat.P = Total_P;
                archive->arc_stat.Gruz3 = Gruz3;
                archive->arc_stat.Gruz5 = Gruz5;
                archive->arc_stat.mh = mh;
                //------------------------
                archive->WriteStat();
                archive->WriteWarnings(war_list);
                war_list->DestroyList();
        }
        ReleaseSemaphore(hSem,1,NULL);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CPU686TimerTimer(TObject *Sender)
{
//        get_data_thread = new TGetDataThread(false);
}
//---------------------------------------------------------------------------

void TMainForm::GetDiagramFromEtalon()
{
        // если произошла смена режима
        // то диаграммы необходимо удалить и создать снова

    if (is_mode_changed || is_RPM_change_off)
    {
        float dx_gor = 0;
        //????
                dx_gor = MainForm->sys_koef->koef.hpp_0+
                         MainForm->sys_koef->koef.h0_1+
                         MainForm->sys_koef->koef.h1_2+
                         MainForm->sys_koef->koef.h2_3+
                         MainForm->sys_koef->koef.h3_4+
                         MainForm->sys_koef->koef.h4_5 - MainForm->sys_koef->koef.L_MAX;
        // ????
/*        if (gor_act == 0)
        {
                dx_gor = MainForm->sys_koef->koef.h0_1+
                         MainForm->sys_koef->koef.h1_2+
                         MainForm->sys_koef->koef.h2_3+
                         MainForm->sys_koef->koef.h3_4+
                         MainForm->sys_koef->koef.h4_5;
        }
        else
        if (gor_act == 1)
        {
                dx_gor = sys_koef->koef.h1_2 + sys_koef->koef.h2_3 + sys_koef->koef.h3_4 + sys_koef->koef.h4_5;
        }
        else
        if (gor_act == 2)
        {
                dx_gor = sys_koef->koef.h2_3 + sys_koef->koef.h3_4 + sys_koef->koef.h4_5;
        }
        else
        if (gor_act == 3)
        {
                dx_gor = sys_koef->koef.h3_4 + sys_koef->koef.h4_5;
        }
        else
        if (gor_act == 4)
        {
                dx_gor = sys_koef->koef.h4_5;
        }
        else
        if (gor_act == 5)
        {
                dx_gor = 0;
        }*/
        //---------------------------------------------------------------------
        diag_low->lp_list->DestroyList();
        delete diag_low;
        diag_hi->lp_list->DestroyList();
        delete diag_hi;
        diag_work->lp_list->DestroyList();        
        delete diag_work;
        //---------------------------------------------------------------------

        diag_low = new TDiagram(mks,MainForm->ChannelList);
        diag_hi = new TDiagram(mks,MainForm->ChannelList);
        diag_work = new TDiagram(mks,MainForm->ChannelList);

        AnsiString f_name_t;
        AnsiString f_name_r;

        if (st.mode_id == 0)
        {
                f_name_t = "d_rg_t.dia";
                f_name_r = "d_rg_r.dia";
        }
        if (st.mode_id == 1)
        {
                f_name_t = "d_rl_t.dia";
                f_name_r = "d_rl_r.dia";
        }
        if (st.mode_id == 2)
        {
                f_name_t = "d_rr_t.dia";
                f_name_r = "d_rr_r.dia";
        }
        if (st.mode_id == 3)
        {
                f_name_t = "d_ro_t.dia";
                f_name_r = "d_ro_r.dia";
        }

        AnsiString dir_name = sys_param->SysDir;
        dir_name += "\\";

        f_name_t = dir_name+f_name_t;
        f_name_r = dir_name+f_name_r;        

        // формирование в списке list1 расчетной диаграммы скорости
        FILE *ft,*fr;
        ft = fopen(f_name_t.c_str(),"rb");
        fr = fopen(f_name_r.c_str(),"rb");

        TVariantList <TLogPoint> *list1 = new TVariantList <TLogPoint>;

        TLogPoint *lp;

        if (ft != NULL)
        {
                fseek(ft,sizeof(TLogPoint)+sizeof(TColor)+sizeof(TKoordKoef)+2*sizeof(int),SEEK_SET);
                fseek(fr,sizeof(TLogPoint)+sizeof(TColor)+sizeof(TKoordKoef)+2*sizeof(int),SEEK_SET);
                list1->ReadFromFile2(fr);

                // корректировка с учетом РПМ
                for (int i=0; i<list1->count; i++)
                {
                        (*list1)[i]->x -= dx_gor;
                }
                //---------------------------
                list1->ReadFromFile2(ft);
                fclose(ft);
                fclose(fr);
        }
        if (list1->count > 0)
        {

        // work calculated diagram
        for (int i=0; i<list1->count; i++)
        {
                lp = new TLogPoint;
                lp->x = (*list1)[i]->x;
                if (st.mode_id == 2) // если "ревизия"
                {
                        float kV = st.V_rev / sys_koef->koef.mode_koefs[st.mode_id].Vmax;
                        lp->y = kV*(*list1)[i]->y;
                }
                else lp->y = (*list1)[i]->y;
                diag_work->lp_list->Add(lp);
        }

        //----------------------------------------------------------------------
        // добавление узлов на р/м участке движения
        float endVrav = sys_koef->koef.L_MAX-
                                sys_koef->koef.mode_koefs[st.mode_id].L_oth-
                                        sys_koef->koef.mode_koefs[st.mode_id].L_razg;
        float begVrav = sys_koef->koef.mode_koefs[st.mode_id].L_dot+sys_koef->koef.mode_koefs[st.mode_id].L_zam;

        for (float l = begVrav+7.0; l < endVrav-7.0; l+=7.0)
        {
                lp = new TLogPoint;
                lp->x = l;
                lp->y = sys_koef->koef.mode_koefs[st.mode_id].Vmax;
                diag_work->lp_list->Add(lp);
        }
        //----------------------------------------------------------------------

        diag_work->SortNodes(1);

        // корректировка разгона и стопорения
        TVariantList <TLogPoint> *list_corr = new TVariantList <TLogPoint>;
        for (int i=0; i<diag_work->lp_list->count; i++)
        {
                if ( (*diag_work->lp_list)[i]->x < sys_koef->koef.L_MAX-sys_koef->koef.mode_koefs[st.mode_id].L_oth &&
                     (*diag_work->lp_list)[i]->x > sys_koef->koef.L_MAX-sys_koef->koef.mode_koefs[st.mode_id].L_oth-
                                                   sys_koef->koef.mode_koefs[st.mode_id].L_razg )
                {
                }
                else
                {
                        lp = new TLogPoint;
                        lp->x = (*diag_work->lp_list)[i]->x;
                        lp->y = (*diag_work->lp_list)[i]->y;
                        list_corr->Add(lp);
                }
        }
        lp = new TLogPoint;

        float dl;
        if (st.mode_id == 2)
        {
                dl = 0;
                lp->y = st.V_rev;
        }
        else
        {
                dl = 2;
                lp->y = sys_koef->koef.mode_koefs[st.mode_id].Vmax;
        }
        lp->x = sys_koef->koef.L_MAX-sys_koef->koef.mode_koefs[st.mode_id].L_oth-dl;
        list_corr->Add(lp);

        // hi level diagram
//        float dp = 50;
        float dp = sys_koef->koef.mode_koefs[st.mode_id].dV_hi;
        for (int i=0; i<list_corr->count; i++)
        {
                lp = new TLogPoint;
                lp->x = (*list_corr)[i]->x;

                if ( (lp->x >= 0 && lp->x <= sys_koef->koef.mode_koefs[st.mode_id].L_dot) ||
                     (lp->x <= sys_koef->koef.L_MAX &&
                         lp->x >= sys_koef->koef.L_MAX-sys_koef->koef.mode_koefs[st.mode_id].L_oth) )
                {
                        lp->y = (*list_corr)[i]->y+dp*(*list_corr)[i]->y/100;
                }
                else
                {
                        lp->y = (*list_corr)[i]->y+sys_koef->koef.mode_koefs[st.mode_id].V_hi*(*list_corr)[i]->y/100;
                }
                diag_hi->lp_list->Add(lp);
        }
        diag_hi->SortNodes(0);
        (*diag_hi->lp_list)[0]->y = (*diag_hi->lp_list)[1]->y; // изменение первого узла (участок стопорения)
        diag_hi->SortNodes(1);

        // low level diagram
        //dp = 20;
        dp = sys_koef->koef.mode_koefs[st.mode_id].dV_low;
        for (int i=0; i<list_corr->count; i++)
        {
                lp = new TLogPoint;
                lp->x = (*list_corr)[i]->x;

                if ( (lp->x >= 0 && lp->x <= sys_koef->koef.mode_koefs[st.mode_id].L_dot) ||
                     (lp->x <= sys_koef->koef.L_MAX &&
                         lp->x >= sys_koef->koef.L_MAX-sys_koef->koef.mode_koefs[st.mode_id].L_oth) )
                {
                        lp->y = (*list_corr)[i]->y+dp*(*list_corr)[i]->y/100;
                }
                else
                {
                        lp->y = (*list_corr)[i]->y+sys_koef->koef.mode_koefs[st.mode_id].V_low*(*list_corr)[i]->y/100;
                }
                diag_low->lp_list->Add(lp);
        }
        diag_low->SortNodes(0);
        (*diag_low->lp_list)[0]->y = (*diag_low->lp_list)[1]->y; // изменение первого узла (участок стопорения)
        diag_low->SortNodes(1);

        delete list1;
        delete list_corr;

                float kRV;
                if (st.mode_id == 2) // если "ревизия"
                {
                        kRV = st.V_rev / sys_koef->koef.mode_koefs[st.mode_id].Vmax;
                }
                else kRV = 1;

        float Vmax = kRV * sys_koef->koef.mode_koefs[st.mode_id].Vmax;
        float grV = Vmax + Vmax*sys_koef->koef.mode_koefs[st.mode_id].V_hi/100.0;

        float dV = grV-round(grV);

        mks->koef.ky = round((mks->r.Height()-10) / grV);

        mks->DrawKoordSystem();

        diag_work->col = sys_param->wcolor;
        diag_work->line_thickness = 2;
        diag_work->RedrawWithOutNodes();

        diag_low->col = sys_param->scolor;
        diag_low->RedrawWithOutNodes();

        diag_hi->col = sys_param->zcolor;
        diag_hi->line_thickness = 2;
        diag_hi->RedrawWithOutNodes();
        }
        else // если эталонная диаграмма не задана
        {
                mks->DrawKoordSystem();
        }
    }
    else // если режим не изменился
    {
    }
}

// программный сброс статистики и аппаратный счетчиков
void __fastcall TMainForm::ClearStat()
{
        // программный сброс статистики
        RTP_count = RPM_count = 0;
        CP_count = 0;
        Total_L_count = 0;
        Total_P = 0;
        Gruz3 = Gruz5 = 0;
        mh = 0;
//        n_cp = 0;
        Ist_cp = 0;
        Idt_cp = 0;
        Utg_cp = 0;

        // аппаратный сброс счетчиков UNIO
//        if (AdminForm->HardRadioButton->Checked)
  //      {
                //Clear_UNIO_Counters(); // надо кроме ДПИ
    //    }

        war_list->DestroyList();   
}

void __fastcall TMainForm::GetPeresm()
{
             int id_smena;

             if (_1st_boot)
             {
                // формирование имени архива
                TDate d = Date();
                Word year,month,day;
                DecodeDate(d,year,month,day);

                Word hour,min,sec,msec;
                DecodeTime(Time(),hour,min,sec,msec);

                float hour2 = hour + min/60.0;
                hour2 += sys_param->dt_peresm/60.0;

                if (hour2 >= 0 && hour2 <= sys_param->NightTime2) d--;
                //--------------------------------------------

                AnsiString dir_name = sys_param->ArcDir;
                AnsiString f_name = DateToStr(d)+"_";
                f_name += IntToStr(sys_param->RudNameIndex);
                f_name += IntToStr(sys_param->StvolNameIndex);
                                    
                if (hour2 >= sys_param->DayTime1 && hour2 < sys_param->DayTime2) id_smena = 0;
                else id_smena = 1;
                f_name += IntToStr(id_smena);
                f_name = dir_name+"\\"+f_name;

                int id_oper;
                if (FileExists(f_name+".arc"))
                {
                        if (CheckCorrectArcSize(f_name+".arc",ChannelList)) id_oper = 2;
                        else // если файл поврежден, то удалить его
                        {
                                arc_cat->DelFileFromDisk(f_name);
                                arc_cat->Save();
                                id_oper = 0;
                        }
                }
                else id_oper = 0;
                archive = new TArchive(sys_param,ChannelList,f_name,id_oper);
                ClearStat();
                if (id_oper == 2)
                {
                        archive->ReadStat(&(archive->arc_stat));
                //------------------------
                        RTP_count = archive->arc_stat.RTP_count;
                        RPM_count = archive->arc_stat.RPM_count;
                        CP_count = archive->arc_stat.CP_count;
                        Total_L_count = archive->arc_stat.Total_L_count;
                        Total_P = archive->arc_stat.P;
                        Gruz3 = archive->arc_stat.Gruz3;
                        Gruz5 = archive->arc_stat.Gruz5;
                        mh = archive->arc_stat.mh;
                }
                //--------------------

                if (id_oper == 0)
                {
                        short actual_id = arc_cat->GetFirstFile(tafsACTUAL);
                        if (actual_id != -1)
                        {
                                (*arc_cat->list)[actual_id]->flag = tafsNOT_DOWNLOADED;
                        }

                        short last_curr_id = arc_cat->GetFirstFile(tafsCURRENT);
                        if (last_curr_id != -1)
                        {
                                (*arc_cat->list)[last_curr_id]->flag = tafsACTUAL;
                                arc_cat->PackArchive((*arc_cat->list)[last_curr_id]->fname);
                        }

                        TArcInfo *arc_info = new TArcInfo();
                        arc_info->flag = tafsCURRENT;
                        strcpy(arc_info->fname,archive->f_name.c_str());
                        arc_info->date_time = Date()+Time();

                        arc_cat->list->Add(arc_info);
                        arc_cat->Save();
                }

                //--------------------

                MemoLog->Lines->Add("Начало смены "+TimeToStr(Time()));

                was_avto_peresm = _1st_boot = false;

                Del48files();

                MainTimer->Enabled = true;
             }
             else
             {
                MainTimer->Enabled = false;
                ArcTimer->Enabled = false;

                // формирование архива
                AnsiString dir_name = sys_param->ArcDir;
                AnsiString f_name = DateToStr(Date())+"_";
                f_name += IntToStr(sys_param->RudNameIndex);
                f_name += IntToStr(sys_param->StvolNameIndex);
                TDateTime t = Time();
                Word hour,min,sec,msec;
                DecodeTime(t,hour,min,sec,msec);

                float hour2 = hour + min/60.0;
                hour2 += sys_param->dt_peresm/60.0;

                if (hour2 >= sys_param->DayTime1 && hour2 < sys_param->DayTime2) id_smena = 0;
                else id_smena = 1;
                f_name += IntToStr(id_smena);
                f_name = dir_name+"\\"+f_name;

                archive->WriteStat();
                delete archive;

                archive = new TArchive(sys_param,ChannelList,f_name,0);
                ClearStat();
                GetData();

                //--------------------
                short actual_id = arc_cat->GetFirstFile(tafsACTUAL);
                if (actual_id != -1)
                {
                        (*arc_cat->list)[actual_id]->flag = tafsNOT_DOWNLOADED;
                }

                short last_curr_id = arc_cat->GetFirstFile(tafsCURRENT);
                if (last_curr_id != -1)
                {
                        (*arc_cat->list)[last_curr_id]->flag = tafsACTUAL;
                        arc_cat->PackArchive((*arc_cat->list)[last_curr_id]->fname);
                }

                TArcInfo *arc_info = new TArcInfo();
                arc_info->flag = tafsCURRENT;
                strcpy(arc_info->fname,archive->f_name.c_str());
                arc_info->date_time = Date()+Time();

                arc_cat->list->Add(arc_info);
                arc_cat->Save();
                //--------------------

                Del48files();

                MainTimer->Enabled = true;
                ArcTimer->Enabled = true;
                MemoLog->Lines->Add("Пересменка "+TimeToStr(Time()));
                //--------------------
             }
             //---------------
             archive->arc_stat.date_time = Date()+Time();

             archive->arc_stat.RudNameIndex = sys_param->RudNameIndex;
             archive->arc_stat.StvolNameIndex = sys_param->StvolNameIndex;

             archive->arc_stat.smena_id = id_smena;

             strcpy(archive->arc_stat.MashinistName,"");//name_mash.c_str());
             strcpy(archive->arc_stat.MasterName,"");//name_master.c_str());

             archive->WriteStat();
             //---------------

//             SmenaButton->Enabled = false;
             was_avto_peresm = was_man_peresm = true;
}
//---------------------------------------------------------------------------
// start
void __fastcall TMainForm::SmenaButtonClick(TObject *Sender)
{
//        if (!is_init)
  //      {
                if (StvolInitForm->ShowModal() == mrOk)
                {
                        short place = StvolInitForm->RadioGroup2->ItemIndex;   // начальное положение
                        short sel_gor = StvolInitForm->RadioGroup1->ItemIndex; // горизонт выдачи

                        if (sel_gor == 0) // 3-й горизонт
                        {
                           sys_koef->koef.L_MAX = sys_koef->koef.hpp_0+
                                  sys_koef->koef.h0_1+
                                  sys_koef->koef.h1_2+
                                  sys_koef->koef.h2_3;
                           gor_act = 3;
                        }
                        if (sel_gor == 1) // 5-й горизонт
                        {
                           sys_koef->koef.L_MAX = sys_koef->koef.hpp_0+
                                  sys_koef->koef.h0_1+
                                  sys_koef->koef.h1_2+
                                  sys_koef->koef.h2_3+
                                  sys_koef->koef.h3_4+
                                  sys_koef->koef.h4_5;
                           gor_act = 5;
                        }

                        switch (place)
                        {
                                // пп
                                case 0: st.Hl = 0;
                                        st.Hr = sys_koef->koef.L_MAX;
                                        st.direct = 1;
                                        break;
                                // горизонт выдачи
                                case 1: st.Hl = sys_koef->koef.L_MAX;
                                        st.Hr = 0;
                                        st.direct = -1;
                                        break;
                        }
                }
  //      }

//        if (SmenaForm->ShowModal() == mrOk)
  //      {
//                GetPeresm();
    //    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ApdTapiDevice1TapiPortOpen(TObject *Sender)
{
//        Memo2->Lines->Add("Connected");
        ApdProtocol1->StartReceive();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::ApdTapiDevice1TapiFail(TObject *Sender)
{
//        if (ApdTapiDevice1->FailureCode != 0)
  //      {
             //   Sleep(3000);
               // ApdTapiDevice1->AutoAnswer();
                //Sleep(3000);
    //    }
//        MemoM->Lines->Add(IntToStr(ApdTapiDevice1->FailureCode));
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::ApdProtocol1ProtocolFinish(TObject *CP,
      int ErrorCode)
{
    if (ErrorCode == 0)
    {
        // получение команды
//        Memo2->Lines->Add("Get command: ");

        char f_name[60];
        strcpy(f_name,MainForm->sys_param->SysDir);
        strcat(f_name,"\\cmnd.tmp");

        char ccc[5];

        FILE *f = fopen(f_name,"rt");
        fgets(ccc,3,f);
        fclose(f);

        char c = ccc[1];

//        Memo2->Lines->Add(c);

        bool flag = false; // положительный ответ корзины

        // анализ полученной команды
        if (StrToInt(c) == tsaGET_ACTUAL)
        {
                short fid = arc_cat->GetFirstFile(tafsACTUAL);
                if (fid != -1)
                {
                        name_send_file = (*arc_cat->list)[fid]->fname;
                        name_send_file += ".rar";
                        flag = true;
                }
                else
                {
                }
        }
        if (StrToInt(c) == tsaGET_ACTUAL_STAT)
        {
                short fid = arc_cat->GetFirstFile(tafsACTUAL);
                if (fid != -1)
                {
                        name_send_file = (*arc_cat->list)[fid]->fname;
                        name_send_file += ".sta";
                        flag = true;
                }
                else
                {
                }
        }
        if (StrToInt(c) == tsaGET_NOT_DOWNLOADED)
        {
                short fid = arc_cat->GetFirstFile(tafsNOT_DOWNLOADED);
                if (fid != -1)
                {
                        name_send_file = (*arc_cat->list)[fid]->fname;
                        name_send_file += ".rar";
                        flag = true;
                }
                else
                {
                }
        }

        if (flag)
        {
//                Memo2->Lines->Add("Sending...");
                ApdProtocol2->FileMask = name_send_file.c_str();
                ApdProtocol2->StartTransmit();
        }
    }
    else
    {
        ApdTapiDevice1->CancelCall();
//        ApdTapiDevice1->AutoAnswer();
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Button7Click(TObject *Sender)
{
        TestForm->ShowModal();
}
//---------------------------------------------------------------------------
// анализ ErrorCode
void __fastcall TMainForm::ApdProtocol2ProtocolFinish(TObject *CP,
      int ErrorCode)
{
    if (ErrorCode == 0)
    {
/*        short fid = arc_cat->GetFileByName(name_send_file);
        if (fid != -1)
        {
                (*arc_cat->list)[fid]->flag = tafsDOWNLOADED;
                arc_cat->Save();
        }
        else
        {
        }*/
    }
    else
    {
/*        short fid = arc_cat->GetFileByName(name_send_file);
        if (fid != -1)
        {
                (*arc_cat->list)[fid]->flag = tafsNOT_DOWNLOADED;
                arc_cat->Save();
        }
        else
        {
        }*/

         ApdTapiDevice1->CancelCall();
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ExitButtonClick(TObject *Sender)
{
        MainTimer->Enabled = false;
        ArcTimer->Enabled = false;

//        ApdComPort1->Open = false; //??

        ApdTapiDevice1->CancelCall();

        MainForm->Close();
}
//---------------------------------------------------------------------------
// статистика последней смены
void __fastcall TMainForm::LastStatButtonClick(TObject *Sender)
{
        short fid = arc_cat->GetFirstFile(tafsACTUAL);
        if (fid != -1)
        {
                AnsiString fname;
                fname = (*arc_cat->list)[fid]->fname;
                fname += ".sta";

                TArcStat stat;
                FILE *f = fopen(fname.c_str(),"rb");
                fread(&stat,sizeof(TArcStat),1,f);
                fclose(f);

                //----------------
                LastStatForm->StringGrid1->Cells[0][0] = "ДАТА: "+DateToStr(stat.date_time);
                if (stat.smena_id == 0)
                        LastStatForm->StringGrid1->Cells[1][0] = "СМЕНА: I";
                else
                if (stat.smena_id == 1)
                        LastStatForm->StringGrid1->Cells[1][0] = "СМЕНА: II";
                //----------------
                if (stat.RudNameIndex == 0)
                        LastStatForm->StringGrid1->Cells[0][1] = "РУДНИК: Холбинский";

                if (stat.StvolNameIndex == 0)
                        LastStatForm->StringGrid1->Cells[1][1] = "СТВОЛ: Вспомогательный";
                else
                if (stat.StvolNameIndex == 1)
                        LastStatForm->StringGrid1->Cells[1][1] = "СТВОЛ: Главный";
                //----------------
                AnsiString temp = stat.MashinistName;
                LastStatForm->StringGrid1->Cells[0][2] = "МАШИНИСТ: "+temp;
                temp = stat.MasterName;
                LastStatForm->StringGrid1->Cells[1][2] = "МАСТЕР: "+temp;
                //----------------                
                LastStatForm->StringGrid1->Cells[0][4] = "ВЫДАНО: "+IntToStr(stat.Gruz3+stat.Gruz5);
                LastStatForm->StringGrid1->Cells[0][5] = "  III - "+IntToStr(stat.Gruz3);
                LastStatForm->StringGrid1->Cells[1][5] = "   V - "+IntToStr(stat.Gruz5);

                LastStatForm->StringGrid1->Cells[0][7] = "ЦИКЛОВ: "+IntToStr(stat.CP_count);
                LastStatForm->StringGrid1->Cells[1][7] = "ПУТЬ: "+FloatToStrF(stat.Total_L_count,ffFixed,8,2);
                LastStatForm->StringGrid1->Cells[0][8] = "МОЩНОСТЬ: "+FloatToStrF(stat.P,ffFixed,8,2);
                LastStatForm->StringGrid1->Cells[1][8] = "МОТОЧАСЫ: "+FloatToStrF(stat.mh,ffFixed,8,2);
                LastStatForm->StringGrid1->Cells[0][9] = "РТП: "+IntToStr(stat.RTP_count);
                LastStatForm->StringGrid1->Cells[1][9] = "РПМ: "+IntToStr(stat.RPM_count);

                LastStatForm->ShowModal();
                //----------------
        }
        else
        {
                MessageDlg("Данные отсутствуют!",
                        mtWarning, TMsgDlgButtons() << mbCancel, 0);
        }
}
//---------------------------------------------------------------------------
// переписать архивы
void __fastcall TMainForm::CopyArcButtonClick(TObject *Sender)
{
        if (CopyArcForm->ShowModal() == mrOk)
        {
                AnsiString arcfname,stafname,warfname;
//                bool flag;

  //              flag = false;

                // актуальный
                if (CopyArcForm->RadioGroup1->ItemIndex == 0)
                {
                        short fid = arc_cat->GetFirstFile(tafsACTUAL);
                        if (fid != -1)
                        {
                                arcfname = (*arc_cat->list)[fid]->fname;
                                stafname = arcfname;
                                warfname = arcfname;
                                arcfname += ".rar";
                                stafname += ".sta";
                                warfname += ".war";
//                                flag = true;

                                AnsiString dest_arc_fname,dest_sta_fname,dest_war_fname;

                                dest_arc_fname = sys_param->FlashDir;
                                dest_sta_fname = sys_param->FlashDir;
                                dest_war_fname = sys_param->FlashDir;
                                dest_arc_fname += "\\"+ExtractFileName(arcfname);
                                dest_sta_fname += "\\"+ExtractFileName(stafname);
                                dest_war_fname += "\\"+ExtractFileName(warfname);

                                short err;
                                err = CopyFile(arcfname.c_str(),dest_arc_fname.c_str(),false);
                                if (err != 0)
                                {
                                        err = CopyFile(stafname.c_str(),dest_sta_fname.c_str(),false);
//                                        err = CopyFile(warfname.c_str(),dest_war_fname.c_str(),false);
                                        if (err != 0)
                                             MessageDlg("Копирование завершено!",
                                                mtWarning, TMsgDlgButtons() << mbCancel, 0);
                                }
                                else    MessageDlg("Ошибка записи!",
                                        mtWarning, TMsgDlgButtons() << mbCancel, 0);
                        }
                        else    MessageDlg("Нет файлов для копирования!",
                                    mtWarning, TMsgDlgButtons() << mbCancel, 0);
                }
                else
/*                // "забытый"
                if (CopyArcForm->RadioGroup1->ItemIndex == 1)
                {
                        short fid = arc_cat->GetFirstFile(tafsNOT_DOWNLOADED);
                        if (fid != -1)
                        {
                                arcfname = (*arc_cat->list)[fid]->fname;
                                stafname = arcfname;
                                arcfname += ".rar";
                                stafname += ".sta";
                                flag = true;
                        }
                }
                else*/
                // все категории
                if (CopyArcForm->RadioGroup1->ItemIndex == 1)
                {
                        for (int i = 0; i<arc_cat->list->count; i++)
                        {
                           if ((*arc_cat->list)[i]->flag != tafsCURRENT)
                           {
                                arcfname = (*arc_cat->list)[i]->fname;
                                stafname = arcfname;
                                warfname = arcfname;
//                                if ((*arc_cat->list)[i]->flag == tafsCURRENT) arcfname += ".arc";
//                                else
                                arcfname += ".rar";
                                stafname += ".sta";
//                                warfname += ".war";
          //                              flag = true;

                                AnsiString dest_arc_fname,dest_sta_fname,dest_war_fname;

                                dest_arc_fname = sys_param->FlashDir;
                                dest_sta_fname = sys_param->FlashDir;
                                dest_war_fname = sys_param->FlashDir;
                                dest_arc_fname += "\\"+ExtractFileName(arcfname);
                                dest_sta_fname += "\\"+ExtractFileName(stafname);
                                dest_war_fname += "\\"+ExtractFileName(warfname);

                                short err;
                                err = CopyFile(arcfname.c_str(),dest_arc_fname.c_str(),false);
                                if (err != 0)
                                {
                                        err = CopyFile(stafname.c_str(),dest_sta_fname.c_str(),false);
//                                        if (err != 0)
  //                                           MessageDlg("Копирование завершено!",
    //                                            mtWarning, TMsgDlgButtons() << mbCancel, 0);
                                }
                                else    MessageDlg("Ошибка записи!",
                                                mtWarning, TMsgDlgButtons() << mbCancel, 0);
                           }
                        }
                        MessageDlg("Копирование завершено!",
                                     mtWarning, TMsgDlgButtons() << mbCancel, 0);
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IPTestButtonClick(TObject *Sender)
{
        HardTestForm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ApdTapiDevice1TapiPortClose(TObject *Sender)
{
//        Sleep(3000);
  //      ApdTapiDevice1->AutoAnswer();
    //    Sleep(3000);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ModemButtonClick(TObject *Sender)
{
//        ApdTapiDevice1->AutoAnswer();                
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Button1Click(TObject *Sender)
{
        PauseForm->Show();
}
//---------------------------------------------------------------------------


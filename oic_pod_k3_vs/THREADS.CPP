//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "threads.h"
//#include "admin.h"
#include "main_unit.h"
#include "hard_test.h"
#include "test_unit.h"
#include "cpu686.h"
#include "pause.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

__fastcall TGetDataThread::TGetDataThread(bool CreateSuspended)
        : TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall TGetDataThread::Redraw()
{
}

void GetDataFromCPU686()
{
        MainForm->st.current_record->date_time = Date()+Time();

	unsigned int ba,BA[12];
        unsigned char IN0[12],nIN0;

        memset(IN0,0,12);

        ba = 0x110;

	BA[0]=ba+0xA001; BA[1] =BA[0]+1; BA[2] =BA[1]+1;  // FPGA1
	BA[3]=ba+0xA401; BA[4] =BA[3]+1; BA[5] =BA[4]+1;  // FPGA2
	BA[6]=ba+0xA801; BA[7] =BA[6]+1; BA[8] =BA[7]+1;  // FPGA3
	BA[9]=ba+0xAC01; BA[10]=BA[9]+1; BA[11]=BA[10]+1; // FPGA4

	// чтение дискретников
        if (MainForm->DISKRET->_1) for (int i=0; i<3; i++) IN0[i] = inportb2(BA[i]);
        if (MainForm->DISKRET->_2) for (int i=3; i<6; i++) IN0[i] = inportb2(BA[i]);
        if (MainForm->DISKRET->_3) for (int i=6; i<9; i++) IN0[i] = inportb2(BA[i]);
        if (MainForm->DISKRET->_4) for (int i=9; i<12; i++) IN0[i] = inportb2(BA[i]);
        //--------------------

        unsigned int temp;
        int nFPGA,n;

        // для АЦП------
        int ST_RDY = 0x80;  // Бит старт-готов

        int BA_AI;
        int timet;
        short adc;

        float LSB = MainForm->LSB;     // Вес младшего разряда в Амперах

        BA_AI = 0x100;

        outport2(BA_AI+0, 0);		// Сброс контрольного регистра
        outportb2(BA_AI+2,0);	        // Вход StCh + уст. диф. входа
        for (int j=0; j<100; j++) timet = j*j;
        //--------------

        for (int i=0; i<MainForm->ChannelList->count; i++)
        {
                nFPGA = (*MainForm->ChannelList)[i]->NFPGA;
                n = (*MainForm->ChannelList)[i]->n_channel;

                TChannel *ch = (*MainForm->ChannelList)[i];

                if (ch->ChannelType == tchtDISKRET)
                {
                        n /= 2;

                        nIN0 = IN0[(nFPGA-1)*3 + n/8];

                        temp = powl(2,n-(n/8)*8);

                        temp &= nIN0;

                        if (temp > 0) (*MainForm->st.current_record->ChannelDataList)[i]->diskret = true;
                        else (*MainForm->st.current_record->ChannelDataList)[i]->diskret = false;
                }

                if (ch->ChannelType == tchtCOUNTER)
                {
                        n /= 2;

                        unsigned int BA1 = BA[(MainForm->UNIO_TBI->COUNTERS-1)*3]-1; // Базовый адрес для FPGA

                        Word c,c_prev,c2;
                        unsigned bnk[]={0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,3,3};
                        unsigned ba_t[]={0,2,4,6,8,10,0,2,4,6,8,10,0,2,4,6,8,10,0,2,4,6,8,10};

//                        outportb2(BA1,bnk[n]);	        // Анти-дребезг 60 ns
  //                      for (int j=0; j<30; j++) timet = j*j;

                        c = inport2(BA1+ba_t[n]);

/*                        //-анализ переполнения-----
                        c_prev = (*MainForm->st_prev.current_record->ChannelDataList)[i]->counter;
                        if ( c < c_prev )
                        {
                                c2 = (0xFFFF-c_prev) + c;
                                (*MainForm->st_prev.current_record->ChannelDataList)[i]->counter = 0;

                                if (strcmp(ch->ChannelCaption,"ДПИ-1")==0) MainForm->st_prev.DPI = 0;
                        }
                        else c2 = c;*/
                        //-------------------------

//                        MainForm->st.DPI = c2;
                        (*MainForm->st.current_record->ChannelDataList)[i]->counter = c;
                        (*MainForm->st.current_record->ChannelDataList)[i]->analog = c * ch->imp;
                }

                if (ch->ChannelType == tchtANALOG)
                {
                        // номер сканируемого канала
                        outportb2(BA_AI+2,n);
                        for (int j=0; j<100; j++) timet = j*j;

                        outport2(BA_AI+0,0);
                        outportb2(BA_AI+0, ST_RDY);  	 // Старт АЦП
                        while(!(inportb2(BA_AI+0) & ST_RDY));  // Опрос бита готовности

                        adc = inport2(BA_AI+2); // отсчеты АЦП
                        adc &= 0xFFFC;          // обнуление двух младших разрядов - устранение "болтанки"

                        (*MainForm->st.current_record->ChannelDataList)[i]->adc = adc;
                        (*MainForm->st.current_record->ChannelDataList)[i]->analog =
                                                                (ch->a*(adc*LSB*1000.0/1.0)+ch->b)*ch->k*ch->k_trans;
//                                                                (ch->a*(adc*LSB*1000.0/4.0)+ch->b)*ch->k;
                        if (fabs((*MainForm->st.current_record->ChannelDataList)[i]->analog) <= 2.0)
                                (*MainForm->st.current_record->ChannelDataList)[i]->analog = 0;

/*                        AnsiString st;
                        st = IntToStr(adc)+" - "+FloatToStrF(LSB*adc*1000.0/1.0,ffFixed,5,2);
//                        st = IntToStr(adc)+" - "+FloatToStrF(LSB*adc*1000.0/4.0,ffFixed,5,2);
                        if (n == 0) HardTestForm->Memo1->Lines->Add(st);
                        if (n == 1) HardTestForm->Memo2->Lines->Add(st);
                        if (n == 2) HardTestForm->Memo3->Lines->Add(st);
                        if (n == 3) HardTestForm->Memo4->Lines->Add(st);
  */
                }
        }
}

void GetChannelChanges()
{
        bool ON, OFF, pON, pOFF;

        //---Uтг---------------------------------------------------------------------------------
        float Utg = (*MainForm->st.current_record->ChannelDataList)[MainForm->idUtg]->analog =
                    (*MainForm->st.current_record->ChannelDataList)[MainForm->idUtgp]->analog -
                    (*MainForm->st.current_record->ChannelDataList)[MainForm->idUtgm]->analog;

        if (fabs(Utg) <= 2)
        {
                (*MainForm->st.current_record->ChannelDataList)[MainForm->idUtg]->analog = 0;
                Utg = 0;
        }

        if (Utg < 0)
        {
                MainForm->st.sign_Utg = -1;
                MainForm->st.direct = 1;
        }
        else if (Utg > 0)
        {
                MainForm->st.sign_Utg = 1;
                MainForm->st.direct = -1;
        }
        else if (Utg == 0.0) MainForm->st.sign_Utg = 0;
        //-------------------------

        MainForm->st.V = (*MainForm->st.current_record->ChannelDataList)[MainForm->idV]->analog =
                fabs(Utg)/MainForm->sys_koef->koef.V_koef_U;
        //------------------------------------------------------------------------------------

        //----проверка смены режима---------
        bool RG,RL,RR,RO;

        RG = (*MainForm->st.current_record->ChannelDataList)[MainForm->idRG]->diskret;
        RL = (*MainForm->st.current_record->ChannelDataList)[MainForm->idRL]->diskret;
        RR = (*MainForm->st.current_record->ChannelDataList)[MainForm->idRR]->diskret;
        RO = (*MainForm->st.current_record->ChannelDataList)[MainForm->idRO]->diskret;
        if (RG) MainForm->st.mode_id = 0;
        if (RL) MainForm->st.mode_id = 1;
        if (RR) MainForm->st.mode_id = 2;
        if (RO) MainForm->st.mode_id = 3;

        if (MainForm->st.mode_id == MainForm->st_prev.mode_id) MainForm->is_mode_changed = false;
        else
        {
                MainForm->is_mode_changed = true;
        }
        //----------------------------------

        //-------РЗТ------------------------
        ON = (*MainForm->st.current_record->ChannelDataList)[MainForm->idRZTon]->diskret;
        pON = (*MainForm->st_prev.current_record->ChannelDataList)[MainForm->idRZTon]->diskret;
        OFF = (*MainForm->st.current_record->ChannelDataList)[MainForm->idRZToff]->diskret;
        pOFF = (*MainForm->st_prev.current_record->ChannelDataList)[MainForm->idRZToff]->diskret;

        MainForm->is_RZT_change_on = false;
        MainForm->is_RZT_change_off = false;
        MainForm->is_RZT_on = false;
        MainForm->is_RZT_off = false;

//        if (pON && OFF && !ON && !pOFF) MainForm->is_RZT_change_off = true;
  //      if (pOFF && ON && !OFF && !pON) MainForm->is_RZT_change_on = true;
    //    if (ON && !OFF) MainForm->is_RZT_on = true;
      //  if (OFF && !ON) MainForm->is_RZT_off = true;
        if (pON && !ON || OFF && !pOFF) MainForm->is_RZT_change_off = true;
        if (pOFF && !OFF || ON && !pON) MainForm->is_RZT_change_on = true;
        if (ON && !OFF) MainForm->is_RZT_on = true;
        if (OFF && !ON) MainForm->is_RZT_off = true;

        if (MainForm->is_RZT_change_on) MainForm->RKZ_count = 0; // для выдачи вагона
        //---------------------------------

        //-------РКЗ------------------------
        ON = (*MainForm->st.current_record->ChannelDataList)[MainForm->idRKZon]->diskret;
        pON = (*MainForm->st_prev.current_record->ChannelDataList)[MainForm->idRKZon]->diskret;
        OFF = (*MainForm->st.current_record->ChannelDataList)[MainForm->idRKZoff]->diskret;
        pOFF = (*MainForm->st_prev.current_record->ChannelDataList)[MainForm->idRKZoff]->diskret;

        MainForm->is_RKZ_change_on = false;
        MainForm->is_RKZ_change_off = false;
        MainForm->is_RKZ_on = false;
        MainForm->is_RKZ_off = false;

//        if (pON && OFF && !ON && !pOFF) MainForm->is_RKZ_change_off = true;
  //      if (pOFF && ON && !OFF && !pON) MainForm->is_RKZ_change_on = true;
        if (pON && !ON || OFF && !pOFF) MainForm->is_RKZ_change_off = true;
        if (pOFF && !OFF || ON && !pON) MainForm->is_RKZ_change_on = true;
        if (ON && !OFF) MainForm->is_RKZ_on = true;
        if (OFF && !ON) MainForm->is_RKZ_off = true;

        if (MainForm->is_RKZ_change_on) MainForm->RKZ_count++;
        //---------------------------------

        //-------РКН------------------------
        ON = (*MainForm->st.current_record->ChannelDataList)[MainForm->idRKNon]->diskret;
        pON = (*MainForm->st_prev.current_record->ChannelDataList)[MainForm->idRKNon]->diskret;
        OFF = (*MainForm->st.current_record->ChannelDataList)[MainForm->idRKNoff]->diskret;
        pOFF = (*MainForm->st_prev.current_record->ChannelDataList)[MainForm->idRKNoff]->diskret;

        MainForm->is_RKN_change_on = false;
        MainForm->is_RKN_change_off = false;
        MainForm->is_RKN_on = false;
        MainForm->is_RKN_off = false;

//        if (pON && OFF && !ON && !pOFF) MainForm->is_RKN_change_off = true;
  //      if (pOFF && ON && !OFF && !pON) MainForm->is_RKN_change_on = true;
        if (pON && !ON || OFF && !pOFF) MainForm->is_RKN_change_off = true;
        if (pOFF && !OFF || ON && !pON) MainForm->is_RKN_change_on = true;
        if (ON && !OFF) MainForm->is_RKN_on = true;
        if (OFF && !ON) MainForm->is_RKN_off = true;
        //---------------------------------

        //-------РДЗ------------------------
        ON = (*MainForm->st.current_record->ChannelDataList)[MainForm->idRDZon]->diskret;
        pON = (*MainForm->st_prev.current_record->ChannelDataList)[MainForm->idRDZon]->diskret;
        OFF = (*MainForm->st.current_record->ChannelDataList)[MainForm->idRDZoff]->diskret;
        pOFF = (*MainForm->st_prev.current_record->ChannelDataList)[MainForm->idRDZoff]->diskret;

        MainForm->is_RDZ_change_on = false;
        MainForm->is_RDZ_change_off = false;
        MainForm->is_RDZ_on = false;
        MainForm->is_RDZ_off = false;

//        if (pON && OFF && !ON && !pOFF) MainForm->is_RDZ_change_off = true;
  //      if (pOFF && ON && !OFF && !pON) MainForm->is_RDZ_change_on = true;
        if (pON && !ON || OFF && !pOFF) MainForm->is_RDZ_change_off = true;
        if (pOFF && !OFF || ON && !pON) MainForm->is_RDZ_change_on = true;
        if (ON && !OFF) MainForm->is_RDZ_on = true;
        if (OFF && !ON) MainForm->is_RDZ_off = true;
        //---------------------------------

        //-------РПМ------------------------
        ON = (*MainForm->st.current_record->ChannelDataList)[MainForm->idRPMon]->diskret;
        pON = (*MainForm->st_prev.current_record->ChannelDataList)[MainForm->idRPMon]->diskret;
        OFF = (*MainForm->st.current_record->ChannelDataList)[MainForm->idRPMoff]->diskret;
        pOFF = (*MainForm->st_prev.current_record->ChannelDataList)[MainForm->idRPMoff]->diskret;

        MainForm->is_RPM_change_on = false;
        MainForm->is_RPM_change_off = false;
        MainForm->is_RPM_on = false;
        MainForm->is_RPM_off = false;

//        if (pON && OFF && !ON && !pOFF) MainForm->is_RPM_change_off = true;
  //      if (pOFF && ON && !OFF && !pON) MainForm->is_RPM_change_on = true;
        if (pON && !ON || OFF && !pOFF) MainForm->is_RPM_change_off = true;
        if (pOFF && !OFF || ON && !pON) MainForm->is_RPM_change_on = true;
        if (ON && !OFF) MainForm->is_RPM_on = true;
        if (OFF && !ON) MainForm->is_RPM_off = true;
        //---------------------------------

        //-------РТП-----------------------
        ON = (*MainForm->st.current_record->ChannelDataList)[MainForm->idRTPon]->diskret;
        pON = (*MainForm->st_prev.current_record->ChannelDataList)[MainForm->idRTPon]->diskret;
        OFF = (*MainForm->st.current_record->ChannelDataList)[MainForm->idRTPoff]->diskret;
        pOFF = (*MainForm->st_prev.current_record->ChannelDataList)[MainForm->idRTPoff]->diskret;

        MainForm->is_RTP_change_on = false;
        MainForm->is_RTP_change_off = false;
        MainForm->is_RTP_on = false;
        MainForm->is_RTP_off = false;

//        if (pON && OFF && !ON && !pOFF) MainForm->is_RTP_change_off = true;
  //      if (pOFF && ON && !OFF && !pON) MainForm->is_RTP_change_on = true;
        if (pON && !ON || OFF && !pOFF) MainForm->is_RTP_change_off = true;
        if (pOFF && !OFF || ON && !pON) MainForm->is_RTP_change_on = true;
        if (ON && !OFF) MainForm->is_RTP_on = true;
        if (OFF && !ON) MainForm->is_RTP_off = true;
        //---------------------------------

        //-------смена направления---------
        // учесть погрешность в 0,5 м (не здесь)
        // начало цикла
/*        if (MainForm->is_RZT_change_off && !MainForm->is_RTP_on && MainForm->is_RTP_off &&
               (MainForm->st.H == 0 || MainForm->st.H == MainForm->sys_koef->koef.L_MAX) &&
                  MainForm->n_cp == 0 )*/
        if (MainForm->is_RZT_change_off &&
               (MainForm->st.Hl == 0 || MainForm->st.Hl == MainForm->sys_koef->koef.L_MAX))
                  //&& MainForm->n_cp == 0 )
        {
                if (MainForm->st.Hl == 0) MainForm->st.direct = 1;
                if (MainForm->st.Hl == MainForm->sys_koef->koef.L_MAX) MainForm->st.direct = -1;
                MainForm->is_direct_changed = true;

                //MainForm->n_cp = 1;
                MainForm->is_vagon_done = false;
        }
        else
        {
                MainForm->is_direct_changed = false;
        }
        //---------------------------------

        //---учет количества срабатываний--
        if (MainForm->is_RTP_change_off && MainForm->st.V != 0.0)
        {
                MainForm->ArcTimer->Interval = 100;
                MainForm->RTP_count++;
        }
        if (MainForm->is_RTP_change_on || MainForm->st.V == 0.0)
        {
                MainForm->ArcTimer->Interval = MainForm->sys_param->ArcTime;
        }

        // перестановка барабана
        if (MainForm->is_RPM_change_on)
        {
                MainForm->RPM_count++;
        }

        if (MainForm->is_RPM_change_off)// && MainForm->is_RZT_on)
        {
                if (fabs(MainForm->st.Hr-MainForm->hpp) <= 0.5)//MainForm->sys_koef->koef.dH_ned)
                {
//                        MainForm->sys_koef->koef.L_MAX = MainForm->st.Hr = MainForm->hpp;
                        MainForm->gor_act = -1;
                        MainForm->st.direct = 1;
                }
                else
                if (fabs(MainForm->st.Hr-MainForm->h0) <= 1.5)//MainForm->sys_koef->koef.dH_ned)
                {
  //                      MainForm->sys_koef->koef.L_MAX = MainForm->st.Hr = MainForm->h0;
                        MainForm->gor_act = 0;
                        MainForm->st.direct = 1;
                }
                else
                if (fabs(MainForm->st.Hr-MainForm->h1) <= 1.5)//MainForm->sys_koef->koef.dH_ned)
                {
    //                    MainForm->sys_koef->koef.L_MAX = MainForm->st.Hr = MainForm->h1;
                        MainForm->gor_act = 1;
                        MainForm->st.direct = 1;
                }
                else
                if (fabs(MainForm->st.Hr-MainForm->h2) <= 1.5)//MainForm->sys_koef->koef.dH_ned)
                {
      //                  MainForm->sys_koef->koef.L_MAX = MainForm->st.Hr = MainForm->h2;
                        MainForm->gor_act = 2;
                        MainForm->st.direct = 1;
                }
                else
                if (fabs(MainForm->st.Hr-MainForm->h3) <= 1.5)//MainForm->sys_koef->koef.dH_ned)
                {
        //                MainForm->sys_koef->koef.L_MAX = MainForm->st.Hr = MainForm->h3;
                        MainForm->gor_act = 3;
                        MainForm->st.direct = 1;
                }
                else
                if (fabs(MainForm->st.Hr-MainForm->h4) <= 1.5)//MainForm->sys_koef->koef.dH_ned)
                {
      //                  MainForm->sys_koef->koef.L_MAX = MainForm->st.Hr = MainForm->h4;
                        MainForm->gor_act = 4;
                        MainForm->st.direct = 1;
                }
                else
                if (fabs(MainForm->st.Hr-MainForm->h5) <= 1.5)//MainForm->sys_koef->koef.dH_ned)
                {
        //                MainForm->sys_koef->koef.L_MAX = MainForm->st.Hr = MainForm->h5;
                        MainForm->gor_act = 5;
                        MainForm->st.direct = 1;
                }

                MainForm->sys_koef->koef.L_MAX = MainForm->st.Hr; //?????                
        }

        // корректировка положения клети----------------------------------
        if (MainForm->is_RZT_change_on)
        {
                if (fabs(MainForm->st.Hr-MainForm->hpp) <= 0.5)//MainForm->sys_koef->koef.dH_ned)
                        MainForm->st.Hr = MainForm->hpp;
                else
                if (fabs(MainForm->st.Hr-MainForm->h0) <= 1.5)//MainForm->sys_koef->koef.dH_ned)
                        MainForm->st.Hr = MainForm->h0;
                else
                if (fabs(MainForm->st.Hr-MainForm->h1) <= 1.5)//MainForm->sys_koef->koef.dH_ned)
                        MainForm->st.Hr = MainForm->h1;
                else
                if (fabs(MainForm->st.Hr-MainForm->h2) <= 1.5)//MainForm->sys_koef->koef.dH_ned)
                        MainForm->st.Hr = MainForm->h2;
                else
                if (fabs(MainForm->st.Hr-MainForm->h3) <= 1.5)//MainForm->sys_koef->koef.dH_ned)
                        MainForm->st.Hr = MainForm->h3;
                else
                if (fabs(MainForm->st.Hr-MainForm->h4) <= 1.5)//MainForm->sys_koef->koef.dH_ned)
                        MainForm->st.Hr = MainForm->h4;
                else
                if (fabs(MainForm->st.Hr-MainForm->h5) <= 1.5)//MainForm->sys_koef->koef.dH_ned)
                        MainForm->st.Hr = MainForm->h5;


                if (fabs(MainForm->st.Hl-MainForm->hpp) <= 0.5)//MainForm->sys_koef->koef.dH_ned)
                        MainForm->st.Hl = MainForm->hpp;
                else
                if (fabs(MainForm->st.Hl-MainForm->h0) <= 1.5)//MainForm->sys_koef->koef.dH_ned)
                        MainForm->st.Hl = MainForm->h0;
                else
                if (fabs(MainForm->st.Hl-MainForm->h1) <= 1.5)//MainForm->sys_koef->koef.dH_ned)
                        MainForm->st.Hl = MainForm->h1;
                else
                if (fabs(MainForm->st.Hl-MainForm->h2) <= 1.5)//MainForm->sys_koef->koef.dH_ned)
                        MainForm->st.Hl = MainForm->h2;
                else
                if (fabs(MainForm->st.Hl-MainForm->h3) <= 1.5)//MainForm->sys_koef->koef.dH_ned)
                        MainForm->st.Hl = MainForm->h3;
                else
                if (fabs(MainForm->st.Hl-MainForm->h4) <= 1.5)//MainForm->sys_koef->koef.dH_ned)
                        MainForm->st.Hl = MainForm->h4;
                else
                if (fabs(MainForm->st.Hl-MainForm->h5) <= 1.5)//MainForm->sys_koef->koef.dH_ned)
                        MainForm->st.Hl = MainForm->h5;
        }
        //----------------------------------------------------------------

        //---кол-во циклов подъема---------
/*        if (MainForm->is_RZT_change_on)
        {
                if (fabs(MainForm->st.Hl) <= MainForm->sys_koef->koef.dH_ned)
                {
                        MainForm->dH = 0;
                        MainForm->st.V = 0;
                        MainForm->st.Hl = 0;
                }
                else
                if (fabs(MainForm->sys_koef->koef.L_MAX-MainForm->st.Hl) <= MainForm->sys_koef->koef.dH_ned)
                {
                        MainForm->dH = 0;
                        MainForm->st.V = 0;
                        MainForm->st.Hl = MainForm->sys_koef->koef.L_MAX;
                }
        }*/

        //---------------------------------

        //---подсчет пройденного пути в км-
        MainForm->Total_L_count += fabs(MainForm->dH);
        //---------------------------------

        //---выдача груза------------------
/*        if ( MainForm->st.mode_id == 0 && MainForm->is_RZT_change_on &&
               (MainForm->st.H == 0 || MainForm->st.H == MainForm->sys_koef->koef.L_MAX) &&
                    !MainForm->is_vagon_done && MainForm->n_cp == 0)*/
        if ( MainForm->st.mode_id == 0 && MainForm->is_RZT_on && !MainForm->is_RZT_off &&
               (MainForm->st.Hl == 0 || MainForm->st.Hl == MainForm->sys_koef->koef.L_MAX) &&
                  MainForm->RKZ_count == MainForm->RKZ_count_vagon &&
                    !MainForm->is_vagon_done )//&& MainForm->n_cp == 0)
        {
                if (MainForm->gor_act == 3)
                {
                        MainForm->Gruz3++;
                }
                if (MainForm->gor_act == 5)
                {
                        MainForm->Gruz5++;
                }

                MainForm->is_vagon_done = true;
        }
        //---------------------------------
        //---моточасы--
        TTime t = Time();
        Word hourm,minm,secm,msecm;
        DecodeTime(t,hourm,minm,secm,msecm);
        long tmsec = 1000*(hourm*3600+minm*60+secm)+msecm;
        MainForm->st.tmsec = tmsec;

        if (MainForm->st.V > 0)
        {
                float dt = (tmsec-MainForm->st_prev.tmsec)/3600.0/1000.0;
                MainForm->mh += dt;
        }
        //-------------

        // простой
        if (MainForm->st_prev.V != 0.0 && MainForm->st.V == 0.0)
        {
                MainForm->pause_time = 0;
                MainForm->pause_start = true;
        }
        else
        if (MainForm->st_prev.V == 0.0)
                if (MainForm->st.V == 0.0) MainForm->pause_time += MainForm->sys_param->RefrTime/3600.0/1000.0;
                else MainForm->pause_start = false;
        //-------------

        // скорость в режиме "ревизия"
        bool _02,_06,_10;
        _02 = (*MainForm->st.current_record->ChannelDataList)[MainForm->id02]->diskret;
        _06 = (*MainForm->st.current_record->ChannelDataList)[MainForm->id06]->diskret;
        _10 = (*MainForm->st.current_record->ChannelDataList)[MainForm->id10]->diskret;

        MainForm->st.V_rev = MainForm->sys_koef->koef.mode_koefs[MainForm->st.mode_id].Vmax;
        if (_02) MainForm->st.V_rev = 0.2;
        if (_06) MainForm->st.V_rev = 0.6;
        if (_10) MainForm->st.V_rev = 1.0;
        if (MainForm->st.V_rev != MainForm->st_prev.V_rev) MainForm->is_mode_changed = true;
        //----------------------------

        //------------------------------------------------------------------------------------
        // Циклы подъема через Iст и Iдт
/*        float Istprev,Ist;
        Istprev = (*MainForm->st_prev.current_record->ChannelDataList)[MainForm->idIst]->analog;
        Ist = (*MainForm->st.current_record->ChannelDataList)[MainForm->idIst]->analog;

        float Idtprev,Idt;
        Idtprev = (*MainForm->st_prev.current_record->ChannelDataList)[MainForm->idIdt]->analog;
        Idt = (*MainForm->st.current_record->ChannelDataList)[MainForm->idIdt]->analog;
  */
        float Utgprev;
        Utgprev = (*MainForm->st_prev.current_record->ChannelDataList)[MainForm->idUtg]->analog;

/*        if (Istprev == 0.0 && Ist != 0.0) // начало цикла
        {
                MainForm->Ist_cp = 1;
        }

        if (Ist == 0.0 && MainForm->Ist_cp == 1 && MainForm->is_RZT_on) // завершение цикла
        {
                MainForm->CP_count++;
                MainForm->Ist_cp = 0;
        }*/

        if (Utgprev == 0.0 && Utg != 0.0) // начало цикла
        {
                MainForm->Utg_cp = 1;
        }

        if (Utg == 0.0 && MainForm->Utg_cp == 1 && MainForm->is_RZT_on) // завершение цикла
        {
                MainForm->CP_count++;
                MainForm->Utg_cp = 0;
        }
}

void GetDataFromTestForm()
{
        //--------формирование новой архивной точки--------------------
        MainForm->st.current_record->date_time = Date()+Time();

        int ch_id_on,ch_id_off,ch_id_an,ch_id_prog;
        int ch_an_min,ch_an_plus;
        Word ch_id_DPI1,DPI1;

        int ch_H_id;
        float dH;

        //-программная имитация каналов-----------------------------------------
        (*MainForm->st.current_record->ChannelDataList)[MainForm->idRG]->diskret = TestForm->CheckBox1->Checked;
        (*MainForm->st.current_record->ChannelDataList)[MainForm->idRL]->diskret = TestForm->CheckBox3->Checked;
        (*MainForm->st.current_record->ChannelDataList)[MainForm->idRR]->diskret = TestForm->CheckBox5->Checked;
        (*MainForm->st.current_record->ChannelDataList)[MainForm->idRO]->diskret = TestForm->CheckBox7->Checked;

        ch_id_on = GetChannelByNameAndDimension(MainForm->ChannelList,"РЗТ",tdtON)->ChannelID;
        (*MainForm->st.current_record->ChannelDataList)[ch_id_on]->diskret = TestForm->CheckBox13->Checked;

        ch_id_off = GetChannelByNameAndDimension(MainForm->ChannelList,"РЗТ",tdtOFF)->ChannelID;
        (*MainForm->st.current_record->ChannelDataList)[ch_id_off]->diskret = TestForm->CheckBox14->Checked;

        ch_id_on = GetChannelByNameAndDimension(MainForm->ChannelList,"РПМ",tdtON)->ChannelID;
        (*MainForm->st.current_record->ChannelDataList)[ch_id_on]->diskret = TestForm->CheckBox15->Checked;
        ch_id_off = GetChannelByNameAndDimension(MainForm->ChannelList,"РПМ",tdtOFF)->ChannelID;
        (*MainForm->st.current_record->ChannelDataList)[ch_id_off]->diskret = TestForm->CheckBox16->Checked;

        ch_id_on = GetChannelByNameAndDimension(MainForm->ChannelList,"РКН",tdtON)->ChannelID;
        (*MainForm->st.current_record->ChannelDataList)[ch_id_on]->diskret = TestForm->CheckBox21->Checked;
        ch_id_off = GetChannelByNameAndDimension(MainForm->ChannelList,"РКН",tdtOFF)->ChannelID;
        (*MainForm->st.current_record->ChannelDataList)[ch_id_off]->diskret = TestForm->CheckBox22->Checked;

        ch_id_on = GetChannelByNameAndDimension(MainForm->ChannelList,"РДЗ",tdtON)->ChannelID;
        (*MainForm->st.current_record->ChannelDataList)[ch_id_on]->diskret = TestForm->CheckBox23->Checked;
        ch_id_off = GetChannelByNameAndDimension(MainForm->ChannelList,"РДЗ",tdtOFF)->ChannelID;
        (*MainForm->st.current_record->ChannelDataList)[ch_id_off]->diskret = TestForm->CheckBox24->Checked;

        ch_id_on = GetChannelByNameAndDimension(MainForm->ChannelList,"РКЗ",tdtON)->ChannelID;
        (*MainForm->st.current_record->ChannelDataList)[ch_id_on]->diskret = TestForm->CheckBox25->Checked;
        ch_id_off = GetChannelByNameAndDimension(MainForm->ChannelList,"РКЗ",tdtOFF)->ChannelID;
        (*MainForm->st.current_record->ChannelDataList)[ch_id_off]->diskret = TestForm->CheckBox26->Checked;

        ch_id_on = GetChannelByNameAndDimension(MainForm->ChannelList,"РТП",tdtON)->ChannelID;
        (*MainForm->st.current_record->ChannelDataList)[ch_id_on]->diskret = TestForm->CheckBox27->Checked;
        ch_id_off = GetChannelByNameAndDimension(MainForm->ChannelList,"РТП",tdtOFF)->ChannelID;
        (*MainForm->st.current_record->ChannelDataList)[ch_id_off]->diskret = TestForm->CheckBox28->Checked;
        //----------------------------------------------------------------------

        //---Uтг---------------------------------------------------------------------------------
        ch_an_min = GetChannelByNameAndDimension(MainForm->ChannelList,"Uтг-",tdtU)->ChannelID;
        (*MainForm->st.current_record->ChannelDataList)[ch_an_min]->analog = TestForm->TrackBar4->Position;

        ch_an_plus = GetChannelByNameAndDimension(MainForm->ChannelList,"Uтг+",tdtU)->ChannelID;
        (*MainForm->st.current_record->ChannelDataList)[ch_an_plus]->analog = TestForm->TrackBar1->Position;
        //------------------------------------------------------------------------------------

        ch_id_an = GetChannelByNameAndDimension(MainForm->ChannelList,"Iст",tdtI)->ChannelID;
        (*MainForm->st.current_record->ChannelDataList)[ch_id_an]->analog = TestForm->TrackBar2->Position;
        (*MainForm->st.current_record->ChannelDataList)[ch_id_an]->adc = TestForm->TrackBar2->Position;   //?????

        ch_id_an = GetChannelByNameAndDimension(MainForm->ChannelList,"Iдт",tdtI)->ChannelID;
        (*MainForm->st.current_record->ChannelDataList)[ch_id_an]->analog = TestForm->TrackBar3->Position;

        //-ДПИ -----------------------------------------------------------------------------------
        TestForm->Edit1->Text = TestForm->TrackBar5->Position;

        ch_id_DPI1 = GetChannelByNameAndDimension(MainForm->ChannelList,"ДПИ-1",tdtNONE)->ChannelID;
        (*MainForm->st.current_record->ChannelDataList)[ch_id_DPI1]->counter += TestForm->TrackBar5->Position;

        //----------------------------------------------------------------------

        for (int i=0; i<MainForm->ChannelList->count; i++)
        {
                if ((*MainForm->ChannelList)[i]->ChannelType == tchtANALOG)
                {
                        AnsiString st;
                        st = IntToStr((*MainForm->st.current_record->ChannelDataList)[i]->adc)+
                             " - "+
                             FloatToStrF((*MainForm->st.current_record->ChannelDataList)[i]->analog,ffFixed,5,2);
                        if ((*MainForm->ChannelList)[i]->n_channel == 0) HardTestForm->Memo1->Lines->Add(st);
                        if ((*MainForm->ChannelList)[i]->n_channel == 1) HardTestForm->Memo2->Lines->Add(st);
                        if ((*MainForm->ChannelList)[i]->n_channel == 2) HardTestForm->Memo3->Lines->Add(st);
                        if ((*MainForm->ChannelList)[i]->n_channel == 3) HardTestForm->Memo4->Lines->Add(st);
                }
        }

        ch_id_on = GetChannelByNameAndDimension(MainForm->ChannelList,"0.2",tdtON)->ChannelID;
        (*MainForm->st.current_record->ChannelDataList)[ch_id_on]->diskret = TestForm->_02CheckBox->Checked;
        ch_id_on = GetChannelByNameAndDimension(MainForm->ChannelList,"0.6",tdtON)->ChannelID;
        (*MainForm->st.current_record->ChannelDataList)[ch_id_on]->diskret = TestForm->_06CheckBox->Checked;
        ch_id_on = GetChannelByNameAndDimension(MainForm->ChannelList,"1.0",tdtON)->ChannelID;
        (*MainForm->st.current_record->ChannelDataList)[ch_id_on]->diskret = TestForm->_10CheckBox->Checked;
}

void __fastcall TGetDataThread::Update()
{
}

void __fastcall TGetDataThread::Execute()
{
//        while (!Terminated)
  //      {
        this->FreeOnTerminate = true;
        randomize();
        DWORD WaitReturn;

          WaitReturn = WaitForSingleObject(hSem,INFINITE);
          if (WaitReturn == WAIT_OBJECT_0)
          {
//                this->Synchronize(GetDataFromCPU686);
                this->Synchronize(Update);
          }
          ReleaseSemaphore(hSem,1,NULL);
    //    }
}

void SetPrevData()
{
        //---------перезапись предыдущей точки архивации---------------
        MainForm->st_prev.current_record->date_time = MainForm->st.current_record->date_time;
        for (int i=0; i<MainForm->st.current_record->ChannelDataList->count; i++)
        {
                (*MainForm->st_prev.current_record->ChannelDataList)[i]->analog =
                                        (*MainForm->st.current_record->ChannelDataList)[i]->analog;
                (*MainForm->st_prev.current_record->ChannelDataList)[i]->diskret =
                                        (*MainForm->st.current_record->ChannelDataList)[i]->diskret;
                (*MainForm->st_prev.current_record->ChannelDataList)[i]->counter =
                                        (*MainForm->st.current_record->ChannelDataList)[i]->counter;
                (*MainForm->st_prev.current_record->ChannelDataList)[i]->adc =
                                        (*MainForm->st.current_record->ChannelDataList)[i]->adc;
        }
        MainForm->st_prev.mode_id = MainForm->st.mode_id;
        MainForm->st_prev.direct = MainForm->st.direct;
        MainForm->st_prev.DPI = MainForm->st.DPI;//?
        MainForm->st_prev.V = MainForm->st.V;
        MainForm->st_prev.Hl = MainForm->st.Hl;
        MainForm->st_prev.Hr = MainForm->st.Hr;
        MainForm->st_prev.V_rev = MainForm->st.V_rev;
        MainForm->st_prev.tmsec = MainForm->st.tmsec;        
        MainForm->st_prev.sign_Utg = MainForm->st.sign_Utg;

//        if (AdminForm->HardRadioButton->Checked)
  //      {
                MainForm->st_prev.DPI = MainForm->st.DPI;
    //    }
      //  if (AdminForm->ProgRadioButton->Checked)
      //  {
//        }
        //-------------------------------------------------------------
}

void GetProgramData()
{
        Word DPI1;
        float dH;

        (*MainForm->st.current_record->ChannelDataList)[MainForm->idRTPK]->analog = MainForm->RTP_count;
        (*MainForm->st.current_record->ChannelDataList)[MainForm->idRPMK]->analog = MainForm->RPM_count;
        (*MainForm->st.current_record->ChannelDataList)[MainForm->idCP]->analog = MainForm->CP_count;
        (*MainForm->st.current_record->ChannelDataList)[MainForm->idGR3]->analog = MainForm->Gruz3;
        (*MainForm->st.current_record->ChannelDataList)[MainForm->idGR5]->analog = MainForm->Gruz5;
        //----------------------------------------------------------------------

        Word currP,prevP;  bool overfp;
        currP = (*MainForm->st.current_record->ChannelDataList)[MainForm->idP]->counter;
        prevP = (*MainForm->st_prev.current_record->ChannelDataList)[MainForm->idP]->counter;
        if (prevP > currP) overfp = true;
        else overfp = false;
        if (overfp) (*MainForm->st.current_record->ChannelDataList)[MainForm->idP]->analog =
                        (0xFFFF-prevP+currP)*(*MainForm->ChannelList)[MainForm->idP]->imp;
//        else MainForm->Total_P = (*MainForm->st.current_record->ChannelDataList)[MainForm->idP]->analog;
        MainForm->Total_P += (*MainForm->st.current_record->ChannelDataList)[MainForm->idP]->analog-
                                 (*MainForm->st_prev.current_record->ChannelDataList)[MainForm->idP]->analog;
        //----------------------------------------------------------------------

        // V H------------------------------------------------------------------
        DPI1 = (*MainForm->st.current_record->ChannelDataList)[MainForm->idDPI]->counter;
        MainForm->st.DPI = DPI1;

                        Word c_prev;
                        bool overf;
                        //-анализ переполнения-----
                        c_prev = (*MainForm->st_prev.current_record->ChannelDataList)[MainForm->idDPI]->counter;
                        if ( DPI1 < c_prev ) overf = true;
                        else overf = false;

        float Utg = (*MainForm->st.current_record->ChannelDataList)[MainForm->idUtg]->analog;
/*        MainForm->st.V = (*MainForm->st.current_record->ChannelDataList)[ch_id_prog]->analog =
                fabs(Utg)/MainForm->sys_koef->koef.V_koef_U;*/

        (*MainForm->st.current_record->ChannelDataList)[MainForm->idL]->analog = MainForm->Total_L_count;
//        (*MainForm->st.current_record->ChannelDataList)[MainForm->idL]->analog = DPI1;//???

                if (overf) dH = fabs((0xFFFF-c_prev+DPI1)*MainForm->sys_koef->koef.VH_koef_DPI);
                else dH = fabs((DPI1-MainForm->st_prev.DPI)*MainForm->sys_koef->koef.VH_koef_DPI);

                MainForm->dH = dH;

        if (!MainForm->is_RPM_on)
        {
//                dH = (DPI1-MainForm->st_prev.DPI)/MainForm->sys_koef->koef.VH_koef_DPI;

/*                if (overf) dH = fabs((0xFFFF-c_prev+DPI1)*MainForm->sys_koef->koef.VH_koef_DPI);
                else dH = fabs((DPI1-MainForm->st_prev.DPI)*MainForm->sys_koef->koef.VH_koef_DPI);

                MainForm->dH = dH;*/

//                MainForm->st.Hl += MainForm->st.direct*dH;
  //              MainForm->st.Hr -= MainForm->st.direct*dH;
                MainForm->st.Hl -= MainForm->st.sign_Utg*dH;
                MainForm->st.Hr += MainForm->st.sign_Utg*dH;
                (*MainForm->st.current_record->ChannelDataList)[MainForm->idH]->analog = MainForm->st.Hl;
        }
        else
        {
                if (Utg > 0) MainForm->st.Hr += dH;
                else if (Utg < 0) MainForm->st.Hr -= dH;
                (*MainForm->st.current_record->ChannelDataList)[MainForm->idH]->analog =
                        (*MainForm->st_prev.current_record->ChannelDataList)[MainForm->idH]->analog;
        }

        //------------------------------------------------------------------------------------

        // учесть погрешность в dH недоезда
        if (!MainForm->is_RPM_on)
        if (MainForm->st.Hl <= 0 || MainForm->sys_koef->koef.L_MAX-MainForm->st.Hl <= 0)
        {
          if (MainForm->st.Hl <= 0)
          {
                MainForm->st.Hl = 0;
                MainForm->st.Hr = MainForm->sys_koef->koef.L_MAX;
          }
          else
          if (MainForm->sys_koef->koef.L_MAX-MainForm->st.Hl <= 0)
          {
                MainForm->st.Hl = MainForm->sys_koef->koef.L_MAX;
                MainForm->st.Hr = 0;                
          }
          MainForm->dH = 0;
          MainForm->st.V = 0;
        }

        MainForm->mks->draw_setka = MainForm->SetkaCheckBox->Checked;
        MainForm->mks->draw_numbers_x = MainForm->XCheckBox->Checked;
        MainForm->mks->draw_numbers_y = MainForm->YCheckBox->Checked;

//----------------
        // учет моточасов
        (*MainForm->st.current_record->ChannelDataList)[MainForm->idMH]->analog = MainForm->mh;

        // простой
        if (MainForm->pause_start && MainForm->pause_time >= 0.17)
        {
                MainForm->pause_start = false;        
                PauseForm->Show();
        }
        else
        if (MainForm->st.V != 0.0 && PauseForm->Visible)
        {
                PauseForm->Close();
        }

        (*MainForm->st.current_record->ChannelDataList)[MainForm->idALARM]->analog = MainForm->alarm_id;
//----------------
}

void GetData()
{
        SetPrevData();

//        if (AdminForm->ProgRadioButton->Checked)
  //      {
    //            GetDataFromTestForm();
      //  }

   //     if (AdminForm->HardRadioButton->Checked)
     //   {
                GetDataFromCPU686();
       // }
}
//---------------------------------------------------------------------------


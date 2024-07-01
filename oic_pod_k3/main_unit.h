//---------------------------------------------------------------------------

#ifndef main_unitH
#define main_unitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include "objects.cpp"
#include "vis_unit.h"
//#include "cpu686.h"

#include <ImgList.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Graphics.hpp>
#include <ToolWin.hpp>
#include <MPlayer.hpp>
#include "CGAUGES.h"
#include "AdPacket.hpp"
#include "AdPort.hpp"
#include "AdProtcl.hpp"
#include "AdPStat.hpp"
#include "AdTapi.hpp"
#include "ADTrmEmu.hpp"
#include "AdTStat.hpp"
#include "OoMisc.hpp"
//---------------------------------------------------------------------------
struct TSystemState
{
        TArchiveRecord *current_record; // состояния каналов

        int mode_id;  // режим работы (РГ,РЛ,РР,РО)
        int direct;   // направление движения левой клети (подъем = -1, спуск = 1)

        int DPI;      // значение ДПИ
        float V;      // скорость
        float Hl;     // высота левой клети
        float Hr;     // высота правой клети

        float V_rev;  // заданная скорость для режима "ревизия"

        short sign_Utg;

        long tmsec;   // для моточасов
};

class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TStatusBar *MainStatusBar;
        TTimer *DateTimer;
        TTimer *MainTimer;
        TTimer *ArcTimer;
        TImage *Image1;
        TImage *LiftImage1;
        TImage *LiftImage2;
        TImage *H12Image;
        TButton *SmenaButton;
        TButton *Button7;
        TImage *IdtImage;
        TImage *IstImage;
        TImage *UtgImage;
        TImage *VImage;
        TImage *ActGorImage;
        TImage *OnAlarmImage;
        TMemo *MemoLog;
        TCheckBox *SetkaCheckBox;
        TCheckBox *XCheckBox;
        TCheckBox *YCheckBox;
        TAnimate *Animate1;
        TApdComPort *ApdComPort1;
        TApdProtocol *ApdProtocol1;
        TApdTapiDevice *ApdTapiDevice1;
        TApdProtocol *ApdProtocol2;
        TBitBtn *ExitButton;
        TBitBtn *LastStatButton;
        TBitBtn *CopyArcButton;
        TButton *IPTestButton;
        TButton *ModemButton;
        TButton *Button1;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall DateTimerTimer(TObject *Sender);
        void __fastcall MainTimerTimer(TObject *Sender);
        void __fastcall ArcTimerTimer(TObject *Sender);
        void __fastcall CPU686TimerTimer(TObject *Sender);
        void __fastcall SmenaButtonClick(TObject *Sender);
        void __fastcall ApdTapiDevice1TapiPortOpen(TObject *Sender);
        void __fastcall ApdTapiDevice1TapiFail(TObject *Sender);
        void __fastcall ApdProtocol1ProtocolFinish(TObject *CP,
          int ErrorCode);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall ApdProtocol2ProtocolFinish(TObject *CP,
          int ErrorCode);
        void __fastcall ExitButtonClick(TObject *Sender);
        void __fastcall LastStatButtonClick(TObject *Sender);
        void __fastcall CopyArcButtonClick(TObject *Sender);
        void __fastcall IPTestButtonClick(TObject *Sender);
        void __fastcall ApdTapiDevice1TapiPortClose(TObject *Sender);
        void __fastcall ModemButtonClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        AnsiString FileDir;

        TChannelList *ChannelList;

        T_DISKRET_TBI *DISKRET;
        T_UNIO_TBI *UNIO_TBI;

        TVariantList <TVisualisationChannel> *VisualChannelList;

        TSysParams *sys_param;
        TSysKoef *sys_koef;

        TArchive *archive;

        bool is_init;

        TSystemState st_prev; // состояние системы на предыдущем шаге архивации
        TSystemState st;

        bool is_mode_changed;
        bool is_direct_changed;

        bool is_RZT_change_on;
        bool is_RZT_change_off;
        bool is_RZT_on;
        bool is_RZT_off;        

        bool is_RKZ_change_on;
        bool is_RKZ_change_off;
        bool is_RKZ_on;
        bool is_RKZ_off;

        bool is_RKN_change_on;
        bool is_RKN_change_off;
        bool is_RKN_on;
        bool is_RKN_off;

        bool is_RDZ_change_on;
        bool is_RDZ_change_off;
        bool is_RDZ_on;
        bool is_RDZ_off;

        bool is_RPM_change_on;
        bool is_RPM_change_off;
        bool is_RPM_on;
        bool is_RPM_off;        

        bool is_RTP_change_on;
        bool is_RTP_change_off;
        bool is_RTP_on;
        bool is_RTP_off;        

        float dH;      // изменение высоты

        __fastcall TMainForm(TComponent* Owner);
        void GetDiagramFromEtalon();

        void __fastcall GetPeresm();

        void __fastcall ClearStat();

        void __fastcall SetAlarm(short al_id,AnsiString capt);
        void __fastcall Del48files();

        bool CheckCorrectArcSize(AnsiString f_name,TChannelList *ch_list);
        void CheckUpEnd();
        void UpdateKS();

        TKoordSystem *mks;

        TDiagram *diag_low,*diag_hi;
        TDiagram *diag_work;

        TDiagram *diag;

        //-------------------------------------------------
        char idRG,idRL,idRR,idRO;
        char idUtg,idUtgm,idUtgp,idIst,idIdt,idV;
        char idRZTon,idRZToff,idRKZon,idRKZoff,idRKNon,idRKNoff,idRDZon,idRDZoff,
             idRPMon,idRPMoff,idRTPon,idRTPoff;
        char id02,id06,id10;
        char idRTPK,idRPMK,idP,idL,idCP,idGR3,idGR5,idALARM,idMH;
        char idH,idDPI;     
        //-------------------------------------------------

        FILE *tf;  // test file

        short gor_act;        // активный горизонт (3 или 5)

        short RTP_count;      // количество срабатываний РТП
        short RPM_count;      // количество срабатываний РПМ
        short CP_count;       // количество циклов подъема
        float Total_L_count;  // общий пройденный путь (м)
        float Total_P;
        short Gruz3;          // выдача с 3-го горизонта
        short Gruz5;          // выдача с 5-го горизонта

        float LSB;
        int G;

        TRect diag_rect;

// "сигнализация"
// alarm_id == 0 - тревоги нет
// alarm_id == 1 - желтый
// alarm_id == 2 - красный
        short alarm_id;

// для звукового файла
        char *waveBuf;
        HGLOBAL hWave;

//        short n_cp;           // 1 - это цикл, 0 - это не цикл
        short Ist_cp,Idt_cp,Utg_cp;

        float mh;             // моточасы

        //---temp---
        Graphics::TBitmap *btmp;
        //----------

        TRect LiftRect1,LiftRect2;
        Graphics::TBitmap *LiftBtmp1,*LiftBtmp2;

        TRect GorRect;
        Graphics::TBitmap *GorBtmp;

        TRect H12Rect;
        Graphics::TBitmap *H12Btmp;

        bool _1st_boot; // признак первой загрузки
        bool was_man_peresm;// была ли "ручная" пересменка (начало смены)
        bool was_avto_peresm;// была ли "автоматическая" пересменка

        TArcCatalog *arc_cat;  // каталог архивов

        //---------------------------------------------------------
        AnsiString command; //команда-запрос для корзины
        AnsiString ans_command; // ответ корзины
        AnsiString get_file_command; // команда получения файла
        AnsiString name_send_file;   // имя отправляемого файла
        //---------------------------------------------------------

        bool is_vagon_done;

        short RKZ_count;
        short RKZ_count_vagon;

        TLogRecList *users;

        AnsiString name_mash,name_master;

        float pause_time;  // время простоя
        Word pause_reason; // причина простоя
        bool pause_start;

        TWarningList *war_list; // список событий

        float hpp,h0,h1,h2,h3,h4,h5;
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif

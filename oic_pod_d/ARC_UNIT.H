//---------------------------------------------------------------------------

#ifndef arc_unitH
#define arc_unitH
//---------------------------------------------------------------------------
#include "objects.cpp"

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <FileCtrl.hpp>

#include <ExtCtrls.hpp>
#include "AdPacket.hpp"
#include "AdPort.hpp"
#include "AdProtcl.hpp"
#include "AdPStat.hpp"
#include "AdTapi.hpp"
#include "ADTrmEmu.hpp"
#include "AdTStat.hpp"
#include "OoMisc.hpp"
/*#include <DB.hpp>
#include <DBTables.hpp>
#include <MXDB.hpp>
#include <Mxstore.hpp>*/
//---------------------------------------------------------------------------
class TArcForm : public TForm
{
__published:	// IDE-managed Components
        TListView *ListView;
        TBitBtn *LoadButton;
        TBitBtn *CloseButton;
        TBitBtn *RefreshButton;
        TBitBtn *BitBtn1;
        TFileListBox *FileListBox;
        TApdComPort *ApdComPort1;
        TApdTapiStatus *ApdTapiStatus1;
        TApdTapiDevice *ApdTapiDevice1;
        TApdProtocol *ApdProtocol1;
        TApdProtocolStatus *ApdProtocolStatus1;
        TTimer *DialTimer;
        TMemo *Memo1;
        TApdProtocol *ApdProtocol2;
        TBitBtn *BalansButton;
        void __fastcall CloseButtonClick(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall RefreshButtonClick(TObject *Sender);
        void __fastcall ListViewDblClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall DialTimerTimer(TObject *Sender);
        void __fastcall ApdTapiDevice1TapiFail(TObject *Sender);
        void __fastcall ApdTapiDevice1TapiPortOpen(TObject *Sender);
        void __fastcall ApdProtocol1ProtocolFinish(TObject *CP,
          int ErrorCode);
        void __fastcall ApdProtocol2ProtocolFinish(TObject *CP,
          int ErrorCode);
        void __fastcall BalansButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
//-----------------------------------
        AnsiString sys_dir;

        TSysParams *sys_param;
        TLogRecList *users;

        TSheduler *sheduler;

        TVariantList <TChannel>* ChannelList;
        TArcStatList *arc_stat_list;

        char idRG,idRL,idRR,idRO;
        char idRPMon,idRPMoff,idRKZon,idRKZoff,idRDZon,idRDZoff;
        char idUtg,idIst,idIdt,idV,idL,idP;
        char idAV1,idRVPU,idEV21,idROKp,idEV1,idY4,idRKT;
        char idG3,idG5;
        AnsiString file2del;

//-----------------------------------
        TArchiveList *arc_list;

        AnsiString command; //команда-запрос для корзины
        AnsiString ans_command; // ответ корзины
        AnsiString get_file_command; // команда получения файла

        void __fastcall RefreshArhs();

        __fastcall TArcForm(TComponent* Owner);
        short UnpackArc(AnsiString f_name);

        bool is_busy; // флаг занятости модема        
};
//---------------------------------------------------------------------------
extern PACKAGE TArcForm *ArcForm;
//---------------------------------------------------------------------------
#endif

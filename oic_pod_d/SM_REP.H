//---------------------------------------------------------------------------

#ifndef sm_repH
#define sm_repH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include "objects.cpp"
#include <Graphics.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TSmRepForm : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TImage *Image2;
        TLabel *Label1;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *Label14;
        TLabel *Label15;
        TLabel *DateL;
        TLabel *TPL;
        TLabel *Gor3L;
        TLabel *Gor5L;
        TLabel *VagonL;
        TLabel *TotalLL;
        TLabel *CPL;
        TButton *Button1;
        TButton *DiagRTPButton;
        TBitBtn *PrintButton;
        TBitBtn *CloseButton;
        TLabel *MHL;
        TLabel *PL;
        TLabel *SmenaL;
        TLabel *StvolL;
        TLabel *MasterL;
        TLabel *MashL;
        TImage *Image3;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        TButton *Button5;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall PrintButtonClick(TObject *Sender);
        void __fastcall CloseButtonClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall DiagRTPButtonClick(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TSmRepForm(TComponent* Owner);

        TKoordSystem *ks1,*ks2;
        TDiagram *diag1,*diag2;
        TRect diag_rect1,diag_rect2;
        TRect hour_rect;
        TRect _7_rect;

        TCiklPodList *cikl_list;

        TCiklPodList *RTP_cikl_list;

        TWarningList *war_list;
//        TVariantList <TIntList> *RTP_cikl_list;

        TArchive *arh;
        TArcStat *arc_stat;

        short freq_id;               
};
//---------------------------------------------------------------------------
extern PACKAGE TSmRepForm *SmRepForm;
//---------------------------------------------------------------------------
#endif

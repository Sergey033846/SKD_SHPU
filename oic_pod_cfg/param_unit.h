//---------------------------------------------------------------------------

#ifndef param_unitH
#define param_unitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "CSPIN.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TParamForm : public TForm
{
__published:	// IDE-managed Components
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TLabel *Label2;
        TGroupBox *GroupBox2;
        TLabel *Label3;
        TLabel *Label4;
        TCSpinEdit *RefrTimeEdit;
        TCSpinEdit *ArcTimeEdit;
        TLabel *Label5;
        TLabel *Label6;
        TBitBtn *OkButton;
        TBitBtn *CancelButton;
        TComboBox *RudNameEdit;
        TComboBox *StvolNameEdit;
        TGroupBox *GroupBox3;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TTabSheet *TabSheet3;
        TGroupBox *GroupBox4;
        TLabel *Label13;
        TLabel *Label14;
        TEdit *ArcDirEdit;
        TEdit *SysDirEdit;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TLabel *Label15;
        TEdit *MediaDirEdit;
        TSpeedButton *SpeedButton3;
        TCSpinEdit *DayTime1;
        TCSpinEdit *NightTime1;
        TCSpinEdit *NightTime2;
        TCSpinEdit *DayTime2;
        TTabSheet *TabSheet4;
        TRadioGroup *COMRadioGroup;
        TRadioGroup *DIALRadioGroup;
        TLabeledEdit *dtPeresmEdit;
        TLabel *Label16;
        TEdit *RARDirEdit;
        TSpeedButton *SpeedButton4;
        TLabel *Label17;
        TEdit *FlashDirEdit;
        TSpeedButton *SpeedButton5;
        void __fastcall OkButtonClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall SpeedButton4Click(TObject *Sender);
        void __fastcall SpeedButton5Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TParamForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TParamForm *ParamForm;
//---------------------------------------------------------------------------
#endif

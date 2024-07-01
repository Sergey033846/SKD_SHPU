//---------------------------------------------------------------------------

#ifndef chan_formH
#define chan_formH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <CheckLst.hpp>
#include "CSPIN.h"
#include <ComCtrls.hpp>

#include "objects.cpp"
//---------------------------------------------------------------------------
class TChannelForm : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *MainParametersBox;
        TLabel *IDLabel;
        TLabel *CaptionLabel;
        TEdit *CaptionEdit;
        TLabel *TypeLabel;
        TComboBox *TypeEdit;
        TLabel *DimensionLabel;
        TComboBox *DimensionEdit;
        TGroupBox *VisualBox;
        TColorBox *ActColorEdit;
        TLabel *ColorLabel;
        TGroupBox *SystemBox;
        TLabel *FPGALabel;
        TLabel *NChannelLabel;
        TCSpinEdit *FPGAEdit;
        TCSpinEdit *NChannelEdit;
        TCSpinEdit *IDEdit;
        TLabel *MINDimLabel;
        TEdit *MINDimEdit;
        TLabel *MAXDimLabel;
        TEdit *MAXDimEdit;
        TButton *OkButton;
        TComboBox *KindDimEdit;
        TLabel *KindDimLabel;
        TGroupBox *AnalogBox;
        TLabel *Label1;
        TEdit *aEdit;
        TLabel *Label2;
        TEdit *bEdit;
        TLabel *Label3;
        TEdit *kEdit;
        TLabel *Label4;
        TGroupBox *CounterBox;
        TLabel *Label5;
        TEdit *impEdit;
        TLabel *Label6;
        TColorBox *NActColorEdit;
        TGroupBox *TransBox;
        TLabel *Label7;
        TEdit *KTransEdit;
        void __fastcall OkButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        void __fastcall RefreshEdits(TObject *Sender,TChannel *ch);

        __fastcall TChannelForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TChannelForm *ChannelForm;
//---------------------------------------------------------------------------
#endif

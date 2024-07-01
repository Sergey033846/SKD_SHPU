//---------------------------------------------------------------------------

#ifndef rep_i_unitH
#define rep_i_unitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "objects.cpp"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TRepIstIdtForm : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TCheckBox *SetkaCheckBox;
        TBitBtn *KXIncButton;
        TBitBtn *KXDecButton;
        TBitBtn *KYIncButton;
        TBitBtn *KYDecButton;
        TCheckBox *XCheckBox;
        TCheckBox *YCheckBox;
        TBitBtn *BitBtn1;
        TBitBtn *PrintButton;
        TBitBtn *LeftNutton;
        TBitBtn *RightButton;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall XCheckBoxClick(TObject *Sender);
        void __fastcall YCheckBoxClick(TObject *Sender);
        void __fastcall SetkaCheckBoxClick(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall KXIncButtonClick(TObject *Sender);
        void __fastcall KXDecButtonClick(TObject *Sender);
        void __fastcall KYIncButtonClick(TObject *Sender);
        void __fastcall KYDecButtonClick(TObject *Sender);
        void __fastcall PrintButtonClick(TObject *Sender);
        void __fastcall RightButtonClick(TObject *Sender);
        void __fastcall LeftNuttonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TRepIstIdtForm(TComponent* Owner);

        TKoordSystem *ks1,*ks2;
        TDiagram *diag1,*diag2,*diag3;
        TRect diag_rect1;

        short freq_id;
};
//---------------------------------------------------------------------------
extern PACKAGE TRepIstIdtForm *RepIstIdtForm;
//---------------------------------------------------------------------------
#endif

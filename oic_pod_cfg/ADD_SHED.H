//---------------------------------------------------------------------------

#ifndef add_shedH
#define add_shedH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TAddShedForm : public TForm
{
__published:	// IDE-managed Components
        TLabeledEdit *TimeEdit;
        TLabel *Label2;
        TComboBox *StvolEdit;
        TLabeledEdit *PhoneEdit;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TLabel *Label1;
        TComboBox *ActionEdit;
        TCheckBox *BlockCheckBox;
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TAddShedForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAddShedForm *AddShedForm;
//---------------------------------------------------------------------------
#endif

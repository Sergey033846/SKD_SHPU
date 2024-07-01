//---------------------------------------------------------------------------

#ifndef comm_confH
#define comm_confH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TCommConfigForm : public TForm
{
__published:	// IDE-managed Components
        TRadioGroup *RadioGroup1;
        TRadioGroup *RadioGroup2;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
private:	// User declarations
public:		// User declarations
        __fastcall TCommConfigForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TCommConfigForm *CommConfigForm;
//---------------------------------------------------------------------------
#endif

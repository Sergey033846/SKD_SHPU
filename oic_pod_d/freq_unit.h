//---------------------------------------------------------------------------

#ifndef freq_unitH
#define freq_unitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFreqForm : public TForm
{
__published:	// IDE-managed Components
        TRadioGroup *RadioGroup1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
private:	// User declarations
public:		// User declarations
        __fastcall TFreqForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFreqForm *FreqForm;
//---------------------------------------------------------------------------
#endif

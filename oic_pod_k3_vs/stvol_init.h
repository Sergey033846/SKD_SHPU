//---------------------------------------------------------------------------

#ifndef stvol_initH
#define stvol_initH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TStvolInitForm : public TForm
{
__published:	// IDE-managed Components
        TRadioGroup *RadioGroup1;
        TBitBtn *BitBtn1;
        TRadioGroup *RadioGroup2;
private:	// User declarations
public:		// User declarations
        __fastcall TStvolInitForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TStvolInitForm *StvolInitForm;
//---------------------------------------------------------------------------
#endif

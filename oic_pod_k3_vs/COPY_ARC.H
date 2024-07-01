//---------------------------------------------------------------------------

#ifndef copy_arcH
#define copy_arcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TCopyArcForm : public TForm
{
__published:	// IDE-managed Components
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TRadioGroup *RadioGroup1;
private:	// User declarations
public:		// User declarations
        __fastcall TCopyArcForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TCopyArcForm *CopyArcForm;
//---------------------------------------------------------------------------
#endif

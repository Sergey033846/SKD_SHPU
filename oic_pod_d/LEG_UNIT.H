//---------------------------------------------------------------------------

#ifndef leg_unitH
#define leg_unitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TLegendForm : public TForm
{
__published:	// IDE-managed Components
        TBitBtn *BitBtn1;
        TMemo *Memo1;
        void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TLegendForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLegendForm *LegendForm;
//---------------------------------------------------------------------------
#endif

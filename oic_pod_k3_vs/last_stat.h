//---------------------------------------------------------------------------

#ifndef last_statH
#define last_statH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TLastStatForm : public TForm
{
__published:	// IDE-managed Components
        TBitBtn *BitBtn1;
        TStringGrid *StringGrid1;
private:	// User declarations
public:		// User declarations
        __fastcall TLastStatForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLastStatForm *LastStatForm;
//---------------------------------------------------------------------------
#endif

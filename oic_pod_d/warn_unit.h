//---------------------------------------------------------------------------

#ifndef warn_unitH
#define warn_unitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TWarningForm : public TForm
{
__published:	// IDE-managed Components
        TStringGrid *StringGrid;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn1;
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TWarningForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TWarningForm *WarningForm;
//---------------------------------------------------------------------------
#endif

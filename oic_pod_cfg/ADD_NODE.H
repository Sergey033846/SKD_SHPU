//---------------------------------------------------------------------------

#ifndef add_nodeH
#define add_nodeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TAddNodeForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TEdit *XEdit;
        TLabel *Label2;
        TEdit *YEdit;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TAddNodeForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAddNodeForm *AddNodeForm;
//---------------------------------------------------------------------------
#endif

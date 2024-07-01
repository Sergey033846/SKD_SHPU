//---------------------------------------------------------------------------

#ifndef msg_unitH
#define msg_unitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TMsgForm : public TForm
{
__published:	// IDE-managed Components
        TMemo *Memo1;
        TBitBtn *BitBtn1;
        void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TMsgForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMsgForm *MsgForm;
//---------------------------------------------------------------------------
#endif

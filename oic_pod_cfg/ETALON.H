//---------------------------------------------------------------------------

#ifndef etalonH
#define etalonH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TEtalonForm : public TForm
{
__published:	// IDE-managed Components
        TRadioGroup *RadioGroup1;
        TRadioGroup *RadioGroup2;
        TButton *Button9;
        TButton *Button10;
        void __fastcall Button9Click(TObject *Sender);
        void __fastcall Button10Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TEtalonForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEtalonForm *EtalonForm;
//---------------------------------------------------------------------------
#endif

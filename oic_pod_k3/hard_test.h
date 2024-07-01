//---------------------------------------------------------------------------

#ifndef hard_testH
#define hard_testH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class THardTestForm : public TForm
{
__published:	// IDE-managed Components
        TMemo *Memo1;
        TLabel *Label1;
        TLabel *Label2;
        TMemo *Memo2;
        TLabel *Label3;
        TMemo *Memo3;
        TLabel *Label4;
        TMemo *Memo4;
        TEdit *Edit1;
        TLabel *LSBEdit;
        TButton *Button1;
        TLabel *Label5;
        TEdit *Edit2;
        TLabel *Label6;
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall THardTestForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE THardTestForm *HardTestForm;
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------

#ifndef smenaH
#define smenaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TSmenaForm : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TButton *Button2;
        TLabel *Label1;
        TComboBox *ComboBox1;
        TLabel *Label2;
        TComboBox *ComboBox2;
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TSmenaForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSmenaForm *SmenaForm;
//---------------------------------------------------------------------------
#endif

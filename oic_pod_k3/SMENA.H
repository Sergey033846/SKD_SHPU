//---------------------------------------------------------------------------

#ifndef smenaH
#define smenaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>
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
        TLabel *Label3;
        TEdit *Edit1;
        TLabel *Label4;
        TEdit *Edit2;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TSmenaForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSmenaForm *SmenaForm;
//---------------------------------------------------------------------------
#endif

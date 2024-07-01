//---------------------------------------------------------------------------

#ifndef bal_parH
#define bal_parH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TBalParForm : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox4;
        TCheckBox *CheckBox5;
        TCheckBox *CheckBox6;
        TGroupBox *GroupBox2;
        TCheckBox *CheckBox7;
        TCheckBox *CheckBox8;
        TCheckBox *CheckBox9;
        TCheckBox *CheckBox10;
        TCheckBox *CheckBox11;
        TCheckBox *CheckBox12;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TCheckBox *CheckBox13;
        TCheckBox *CheckBox14;
private:	// User declarations
public:		// User declarations
        __fastcall TBalParForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TBalParForm *BalParForm;
//---------------------------------------------------------------------------
#endif

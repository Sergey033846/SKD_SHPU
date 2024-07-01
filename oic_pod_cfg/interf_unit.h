//---------------------------------------------------------------------------

#ifndef interf_unitH
#define interf_unitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TInterfForm : public TForm
{
__published:	// IDE-managed Components
        TPageControl *PageControl2;
        TTabSheet *TabSheet5;
        TPageControl *PageControl3;
        TTabSheet *TabSheet6;
        TGroupBox *GroupBox2;
        TLabel *Label3;
        TLabel *Label4;
        TComboBox *ComboBox2;
        TColorBox *ColorBox1;
        TTabSheet *TabSheet7;
        TTabSheet *TabSheet8;
        TTabSheet *TabSheet9;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TLabel *Label2;
        TComboBox *ComboBox1;
        TColorBox *ColorBox2;
        TGroupBox *GroupBox3;
        TLabel *Label5;
        TLabel *Label6;
        TComboBox *ComboBox3;
        TColorBox *ColorBox3;
        TGroupBox *GroupBox4;
        TLabel *Label7;
        TLabel *Label8;
        TComboBox *ComboBox4;
        TColorBox *ColorBox4;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TGroupBox *GroupBox5;
        TLabel *Label9;
        TColorBox *ColorBox5;
        TTabSheet *TabSheet1;
        TGroupBox *GroupBox6;
        TColorBox *WColorBox;
        TLabel *Label11;
        TColorBox *SColorBox;
        TLabel *Label12;
        TColorBox *ZColorBox;
        TLabel *Label10;
        TLabel *Label13;
        TColorBox *FColorBox;
        TLabel *Label14;
        TColorBox *BkColorBox;
        TTabSheet *TabSheet2;
        TGroupBox *GroupBox7;
        TLabel *Label15;
        TLabel *Label16;
        TComboBox *ComboBox5;
        TColorBox *ColorBox6;
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TInterfForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInterfForm *InterfForm;
//---------------------------------------------------------------------------
#endif

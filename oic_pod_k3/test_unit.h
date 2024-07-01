//---------------------------------------------------------------------------

#ifndef test_unitH
#define test_unitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TTestForm : public TForm
{
__published:	// IDE-managed Components
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox5;
        TCheckBox *CheckBox7;
        TCheckBox *CheckBox9;
        TCheckBox *CheckBox10;
        TCheckBox *CheckBox11;
        TCheckBox *CheckBox12;
        TCheckBox *CheckBox13;
        TCheckBox *CheckBox14;
        TCheckBox *CheckBox15;
        TCheckBox *CheckBox16;
        TCheckBox *CheckBox17;
        TCheckBox *CheckBox18;
        TCheckBox *CheckBox19;
        TCheckBox *CheckBox20;
        TCheckBox *CheckBox21;
        TCheckBox *CheckBox22;
        TCheckBox *CheckBox23;
        TCheckBox *CheckBox24;
        TCheckBox *CheckBox25;
        TCheckBox *CheckBox26;
        TCheckBox *CheckBox27;
        TCheckBox *CheckBox28;
        TTrackBar *TrackBar1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TTrackBar *TrackBar2;
        TTrackBar *TrackBar3;
        TLabel *Label4;
        TTrackBar *TrackBar4;
        TLabel *Label5;
        TTrackBar *TrackBar5;
        TEdit *Edit1;
        TCheckBox *_02CheckBox;
        TCheckBox *_06CheckBox;
        TCheckBox *_10CheckBox;
        void __fastcall CheckBox13Click(TObject *Sender);
        void __fastcall CheckBox14Click(TObject *Sender);
        void __fastcall CheckBox15Click(TObject *Sender);
        void __fastcall CheckBox16Click(TObject *Sender);
        void __fastcall CheckBox27Click(TObject *Sender);
        void __fastcall CheckBox28Click(TObject *Sender);
        void __fastcall CheckBox25Click(TObject *Sender);
        void __fastcall CheckBox26Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TTestForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTestForm *TestForm;
//---------------------------------------------------------------------------
#endif

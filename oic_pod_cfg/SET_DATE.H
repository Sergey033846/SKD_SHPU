//---------------------------------------------------------------------------

#ifndef set_dateH
#define set_dateH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TSetDateTimeForm : public TForm
{
__published:	// IDE-managed Components
        TDateTimePicker *DatePicker;
        TDateTimePicker *TimePicker;
        TLabel *Label1;
        TLabel *Label2;
        TButton *Button1;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TSetDateTimeForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSetDateTimeForm *SetDateTimeForm;
//---------------------------------------------------------------------------
#endif

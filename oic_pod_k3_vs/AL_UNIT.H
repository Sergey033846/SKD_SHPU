//---------------------------------------------------------------------------

#ifndef al_unitH
#define al_unitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TAlarmForm : public TForm
{
__published:	// IDE-managed Components
        TStringGrid *StringGrid1;
private:	// User declarations
public:		// User declarations
        __fastcall TAlarmForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAlarmForm *AlarmForm;
//---------------------------------------------------------------------------
#endif

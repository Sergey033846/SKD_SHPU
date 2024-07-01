//---------------------------------------------------------------------------

#ifndef adminH
#define adminH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>

#include "objects.cpp"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TAdminForm : public TForm
{
__published:	// IDE-managed Components
        TRadioGroup *RadioGroup1;
        TRadioButton *HardRadioButton;
        TRadioButton *ProgRadioButton;
        TButton *Button1;
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TAdminForm(TComponent* Owner);
/*
        AnsiString sys_dir;

        TSysParams *sys_param;
        TLogRecList *users;

        TSheduler *sheduler;*/
};
//---------------------------------------------------------------------------
extern PACKAGE TAdminForm *AdminForm;
//---------------------------------------------------------------------------
#endif

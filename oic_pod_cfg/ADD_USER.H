//---------------------------------------------------------------------------

#ifndef add_userH
#define add_userH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TAddUserForm : public TForm
{
__published:	// IDE-managed Components
        TLabeledEdit *NameEdit;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TLabel *Label2;
        TComboBox *GroupEdit;
        TLabeledEdit *PasswordEdit;
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TAddUserForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAddUserForm *AddUserForm;
//---------------------------------------------------------------------------
#endif

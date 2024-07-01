//---------------------------------------------------------------------------

#ifndef reg_formH
#define reg_formH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>

#include "objects.cpp"
//---------------------------------------------------------------------------
class TUserForm : public TForm
{
__published:	// IDE-managed Components
        TStringGrid *StringGrid;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TBitBtn *BitBtn4;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn4Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall StringGridDblClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TUserForm(TComponent* Owner);

        void RefreshRow(TLoginRecord *rec,int rr);
        void ClearRows();
};
//---------------------------------------------------------------------------
extern PACKAGE TUserForm *UserForm;
//---------------------------------------------------------------------------
#endif

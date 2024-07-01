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
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TAdminForm : public TForm
{
__published:	// IDE-managed Components
        TBitBtn *BitBtn4;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TBitBtn *BitBtn5;
        TBitBtn *BitBtn6;
        TBitBtn *BitBtn7;
        TBitBtn *BitBtn8;
        TBitBtn *BitBtn9;
        void __fastcall N9Click(TObject *Sender);
        void __fastcall BitBtn4Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall BitBtn5Click(TObject *Sender);
        void __fastcall BitBtn6Click(TObject *Sender);
        void __fastcall BitBtn7Click(TObject *Sender);
        void __fastcall BitBtn8Click(TObject *Sender);
        void __fastcall BitBtn9Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TAdminForm(TComponent* Owner);

        AnsiString sys_dir;

        TChannelList *ChannelList;

        TSysParams *sys_param;
        TSysKoef *sys_koef;

        TLogRecList *users;

        TSheduler *sheduler;
};
//---------------------------------------------------------------------------
extern PACKAGE TAdminForm *AdminForm;
//---------------------------------------------------------------------------
#endif

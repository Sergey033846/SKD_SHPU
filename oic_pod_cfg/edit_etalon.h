//---------------------------------------------------------------------------

#ifndef edit_etalonH
#define edit_etalonH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ExtCtrls.hpp>
#include "objects.cpp"
#include <Graphics.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TEditEtalonForm : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TGroupBox *GroupBox1;
        TPopupMenu *PopupMenu1;
        TMenuItem *N1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TBitBtn *BitBtn4;
        TBitBtn *BitBtn5;
        TBitBtn *BitBtn6;
        TBitBtn *BitBtn7;
        TBitBtn *BitBtn8;
        TBitBtn *BitBtn9;
        TBitBtn *BitBtn10;
        TBitBtn *BitBtn12;
        TBitBtn *BitBtn11;
        TBitBtn *BitBtn13;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall Button9Click(TObject *Sender);
        void __fastcall Button10Click(TObject *Sender);
        void __fastcall Button11Click(TObject *Sender);
        void __fastcall Button12Click(TObject *Sender);

        void __fastcall ImageNodeDblClick(TObject *Sender);
        void __fastcall ImageNodeMouseDown(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall N1Click(TObject *Sender);
        void __fastcall Button13Click(TObject *Sender);
        void __fastcall Button14Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        TKoordSystem *koord_system;
        TDiagram *diagram;

        int mode_id; // id режима работы ШПМ
        int speed_id; // id режима скорости
        AnsiString f_name;

        int im_tag;

        TRect diag_rect;

        __fastcall TEditEtalonForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEditEtalonForm *EditEtalonForm;
//---------------------------------------------------------------------------
#endif

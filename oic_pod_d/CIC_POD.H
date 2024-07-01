//---------------------------------------------------------------------------

#ifndef cic_podH
#define cic_podH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include "objects.cpp"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TSmCiklForm : public TForm
{
__published:	// IDE-managed Components
        TStringGrid *StringGrid;
        TGroupBox *GroupBox1;
        TBitBtn *RepButton1;
        TBitBtn *RepButton2;
        TBitBtn *BitBtn5;
        TBitBtn *LoadButon;
        TBitBtn *RepButton3;
        TStatusBar *StatusBar1;
        TBitBtn *RepButton4;
        TBitBtn *RepButton5;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall BitBtn5Click(TObject *Sender);
        void __fastcall LoadButonClick(TObject *Sender);
        void __fastcall RepButton1Click(TObject *Sender);
        void __fastcall RepButton2Click(TObject *Sender);
        void __fastcall RepButton3Click(TObject *Sender);
        void __fastcall RepButton4Click(TObject *Sender);
        void __fastcall RepButton5Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TSmCiklForm(TComponent* Owner);

        TArchive *arh;
        TArcRecList *cikl,*cikl1;
        bool is_cikl_loaded;        
};
//---------------------------------------------------------------------------
extern PACKAGE TSmCiklForm *SmCiklForm;
//---------------------------------------------------------------------------
#endif

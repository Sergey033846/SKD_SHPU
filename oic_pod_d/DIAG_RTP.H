//---------------------------------------------------------------------------

#ifndef diag_rtpH
#define diag_rtpH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>

#include "objects.cpp"
//---------------------------------------------------------------------------
class TDiagRTPForm : public TForm
{
__published:	// IDE-managed Components
        TStringGrid *StringGrid;
        TGroupBox *GroupBox1;
        TBitBtn *RepIstButton;
        TBitBtn *RepUtgButton;
        TBitBtn *CloseButton;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall CloseButtonClick(TObject *Sender);
        void __fastcall RepIstButtonClick(TObject *Sender);
        void __fastcall RepUtgButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TDiagRTPForm(TComponent* Owner);

        TArchive *arh;
        short curr_diag;

        TDateTime smena_beg_time;
};
//---------------------------------------------------------------------------
extern PACKAGE TDiagRTPForm *DiagRTPForm;
//---------------------------------------------------------------------------
#endif

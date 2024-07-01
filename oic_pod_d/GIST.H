//---------------------------------------------------------------------------

#ifndef gistH
#define gistH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <DbChart.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TGistForm : public TForm
{
__published:	// IDE-managed Components
        TDBChart *VagonChart;
        TDBChart *RTPChart;
        TDBChart *CPChart;
        TDBChart *PChart;
        TDBChart *MHChart;
        TDBChart *LChart;
        TBarSeries *Series1;
        TBarSeries *Series2;
        TBarSeries *Series3;
        TBarSeries *Series4;
        TBarSeries *Series5;
        TBarSeries *Series6;
        TBitBtn *CloseButton;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall CloseButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TGistForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGistForm *GistForm;
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------

#ifndef bal_showH
#define bal_showH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <DB.hpp>
#include <DBTables.hpp>
#include <MXDB.hpp>
#include <MXGRID.hpp>
#include <Mxstore.hpp>
#include <DBGrids.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <MXGRAPH.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <MXPIVSRC.hpp>
#include <DbChart.hpp>
#include <Buttons.hpp>
/*#include <Chartfx3.hpp>
#include <OleCtrls.hpp>
#include <VCFI.hpp>*/
//---------------------------------------------------------------------------
class TBalRepForm : public TForm
{
__published:	// IDE-managed Components
        TTable *Table2;
        TDataSource *DataSource2;
        TDBGrid *DBGrid2;
        TDataSource *DataSource3;
        TQuery *Query1;
        TTable *Table1;
        TBitBtn *BitBtn2;
        TBitBtn *GistButton;
        TBitBtn *BitBtn1;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall GistButtonClick(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TBalRepForm(TComponent* Owner);

        bool by_smena,by_day,by_month,by_quarter,by_halfyear,by_year,by_stvol,by_rudnik;
        bool by_vagon,by_mh,by_tp,by_l,by_p,by_cp;

        short GetVisibleColumn(short n);
};
//---------------------------------------------------------------------------
extern PACKAGE TBalRepForm *BalRepForm;
//---------------------------------------------------------------------------
#endif

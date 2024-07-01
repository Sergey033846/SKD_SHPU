//---------------------------------------------------------------------------

#ifndef shed_unitH
#define shed_unitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>
#include "AdPort.hpp"
#include "AdTapi.hpp"
#include "ADTrmEmu.hpp"
#include "AdTStat.hpp"
#include "OoMisc.hpp"
#include "AdProtcl.hpp"
#include "AdPStat.hpp"
#include "AdPacket.hpp"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TShedForm : public TForm
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
        void __fastcall FormShow(TObject *Sender);
        void __fastcall BitBtn4Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall StringGridDblClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TShedForm(TComponent* Owner);

        void ClearRows();
        void RefreshRow(TShedRecord *rec,int rr);
};
//---------------------------------------------------------------------------
extern PACKAGE TShedForm *ShedForm;
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------

#ifndef rep_unit2H
#define rep_unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QRCtrls.hpp>
#include <QuickRpt.hpp>
//---------------------------------------------------------------------------
class TReportForm2 : public TForm
{
__published:	// IDE-managed Components
        TQuickRep *QuickRep1;
        TQRBand *QRBand1;
        TQRLabel *QRLabel1;
        TQRImage *QRImage1;
private:	// User declarations
public:		// User declarations
        __fastcall TReportForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TReportForm2 *ReportForm2;
//---------------------------------------------------------------------------
#endif

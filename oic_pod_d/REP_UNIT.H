//---------------------------------------------------------------------------

#ifndef rep_unitH
#define rep_unitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QRCtrls.hpp>
#include <QuickRpt.hpp>
//---------------------------------------------------------------------------
class TReportForm : public TForm
{
__published:	// IDE-managed Components
        TQuickRep *QuickRep1;
        TQRBand *QRBand1;
        TQRLabel *QRLabel1;
        TQRLabel *QRLabel3;
        TQRLabel *QRLabel2;
        TQRLabel *QRLabel4;
        TQRLabel *QRLabel5;
        TQRLabel *QRLabel6;
        TQRLabel *QRLabel7;
        TQRLabel *QRLabel9;
        TQRLabel *QRLabel10;
        TQRLabel *QRLabel8;
        TQRLabel *QRLabel12;
        TQRLabel *QRLabel13;
        TQRLabel *QRLabel11;
        TQRLabel *QRLabel15;
        TQRImage *QRImage1;
        TQRLabel *DateL;
        TQRLabel *MHL;
        TQRLabel *VagonL;
        TQRLabel *SmenaL;
        TQRLabel *MashL;
        TQRLabel *MasterL;
        TQRLabel *StvolL;
        TQRLabel *RTPL;
        TQRLabel *TotalL;
        TQRLabel *CPL;
        TQRLabel *Gor3L;
        TQRLabel *Gor5L;
        TQRLabel *PL;
private:	// User declarations
public:		// User declarations
        __fastcall TReportForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TReportForm *ReportForm;
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("ARC_UNIT.CPP", ArcForm);
USEFORM("msg_unit.cpp", MsgForm);
USEFORM("REP_UNIT.CPP", ReportForm);
USEFORM("rep_unit2.cpp", ReportForm2);
USEFORM("SM_REP.CPP", SmRepForm);
USEFORM("PRG_UNIT.CPP", ProgressForm);
USEFORM("CIC_POD.CPP", SmCiklForm);
USEFORM("rep_i_unit.cpp", RepIstIdtForm);
USEFORM("DIAG_RTP.CPP", DiagRTPForm);
USEFORM("BAL_PAR.CPP", BalParForm);
USEFORM("bal_show.cpp", BalRepForm);
USEFORM("gist.cpp", GistForm);
USEFORM("warn_unit.cpp", WarningForm);
USEFORM("leg_unit.cpp", LegendForm);
USEFORM("freq_unit.cpp", FreqForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "ÑÊÄ ØÏÌ (ÀÐÌ äèñïåò÷åðà)";
                 Application->CreateForm(__classid(TArcForm), &ArcForm);
                 Application->CreateForm(__classid(TMsgForm), &MsgForm);
                 Application->CreateForm(__classid(TReportForm), &ReportForm);
                 Application->CreateForm(__classid(TReportForm2), &ReportForm2);
                 Application->CreateForm(__classid(TSmRepForm), &SmRepForm);
                 Application->CreateForm(__classid(TProgressForm), &ProgressForm);
                 Application->CreateForm(__classid(TSmCiklForm), &SmCiklForm);
                 Application->CreateForm(__classid(TRepIstIdtForm), &RepIstIdtForm);
                 Application->CreateForm(__classid(TDiagRTPForm), &DiagRTPForm);
                 Application->CreateForm(__classid(TBalParForm), &BalParForm);
                 Application->CreateForm(__classid(TBalRepForm), &BalRepForm);
                 Application->CreateForm(__classid(TGistForm), &GistForm);
                 Application->CreateForm(__classid(TWarningForm), &WarningForm);
                 Application->CreateForm(__classid(TLegendForm), &LegendForm);
                 Application->CreateForm(__classid(TFreqForm), &FreqForm);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------




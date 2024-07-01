//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("main_unit.cpp", MainForm);
USEFORM("test_unit.cpp", TestForm);
USEFORM("al_unit.cpp", AlarmForm);
USEFORM("msg_unit.cpp", MsgForm);
USEFORM("hard_test.cpp", HardTestForm);
USEFORM("SMENA.CPP", SmenaForm);
USEFORM("stvol_init.cpp", StvolInitForm);
USEFORM("last_stat.cpp", LastStatForm);
USEFORM("copy_arc.cpp", CopyArcForm);
USEFORM("passw.cpp", PasswForm);
USEFORM("pause.cpp", PauseForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TTestForm), &TestForm);
                 Application->CreateForm(__classid(TAlarmForm), &AlarmForm);
                 Application->CreateForm(__classid(TMsgForm), &MsgForm);
                 Application->CreateForm(__classid(THardTestForm), &HardTestForm);
                 Application->CreateForm(__classid(TSmenaForm), &SmenaForm);
                 Application->CreateForm(__classid(TStvolInitForm), &StvolInitForm);
                 Application->CreateForm(__classid(TLastStatForm), &LastStatForm);
                 Application->CreateForm(__classid(TCopyArcForm), &CopyArcForm);
                 Application->CreateForm(__classid(TPasswForm), &PasswForm);
                 Application->CreateForm(__classid(TPauseForm), &PauseForm);
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




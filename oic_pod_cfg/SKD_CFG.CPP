//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("chan_form.cpp", ChannelForm);
USEFORM("sh_all_can.cpp", ShowChannelForm);
USEFORM("param_unit.cpp", ParamForm);
USEFORM("etalon.cpp", EtalonForm);
USEFORM("edit_etalon.cpp", EditEtalonForm);
USEFORM("koef_unit.cpp", KoefForm);
USEFORM("admin.cpp", AdminForm);
USEFORM("dir_unit.cpp", DirForm);
USEFORM("interf_unit.cpp", InterfForm);
USEFORM("reg_form.cpp", UserForm);
USEFORM("shed_unit.cpp", ShedForm);
USEFORM("set_date.cpp", SetDateTimeForm);
USEFORM("add_user.cpp", AddUserForm);
USEFORM("add_shed.cpp", AddShedForm);
USEFORM("add_node.cpp", AddNodeForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Конфигуратор СКД ШПМ";
                 Application->CreateForm(__classid(TAdminForm), &AdminForm);
                 Application->CreateForm(__classid(TChannelForm), &ChannelForm);
                 Application->CreateForm(__classid(TShowChannelForm), &ShowChannelForm);
                 Application->CreateForm(__classid(TParamForm), &ParamForm);
                 Application->CreateForm(__classid(TEtalonForm), &EtalonForm);
                 Application->CreateForm(__classid(TEditEtalonForm), &EditEtalonForm);
                 Application->CreateForm(__classid(TKoefForm), &KoefForm);
                 Application->CreateForm(__classid(TDirForm), &DirForm);
                 Application->CreateForm(__classid(TInterfForm), &InterfForm);
                 Application->CreateForm(__classid(TUserForm), &UserForm);
                 Application->CreateForm(__classid(TShedForm), &ShedForm);
                 Application->CreateForm(__classid(TSetDateTimeForm), &SetDateTimeForm);
                 Application->CreateForm(__classid(TAddUserForm), &AddUserForm);
                 Application->CreateForm(__classid(TAddShedForm), &AddShedForm);
                 Application->CreateForm(__classid(TAddNodeForm), &AddNodeForm);
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




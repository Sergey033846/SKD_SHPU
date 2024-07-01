//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "koef_unit.h"
#include "admin.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TKoefForm *KoefForm;
//---------------------------------------------------------------------------
__fastcall TKoefForm::TKoefForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TKoefForm::NoButtonClick(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------
void __fastcall TKoefForm::OkButtonClick(TObject *Sender)
{
        try
        {
                AdminForm->sys_koef->koef.mode_koefs[0].Vmax = StrToFloat(Edit1->Text);
                AdminForm->sys_koef->koef.mode_koefs[0].a_zam = StrToFloat(Edit2->Text);
                AdminForm->sys_koef->koef.mode_koefs[0].a_razg = StrToFloat(Edit3->Text);
                AdminForm->sys_koef->koef.mode_koefs[0].a_oth = StrToFloat(Edit4->Text);
                AdminForm->sys_koef->koef.mode_koefs[0].L_zam = StrToFloat(Edit5->Text);
                AdminForm->sys_koef->koef.mode_koefs[0].L_razg = StrToFloat(Edit6->Text);
                AdminForm->sys_koef->koef.mode_koefs[0].L_oth = StrToFloat(Edit7->Text);
                AdminForm->sys_koef->koef.mode_koefs[0].L_dot = StrToFloat(Edit8->Text);
                AdminForm->sys_koef->koef.mode_koefs[0].V_low = StrToFloat(Edit18->Text);
                AdminForm->sys_koef->koef.mode_koefs[0].V_hi = StrToFloat(Edit19->Text);
                AdminForm->sys_koef->koef.mode_koefs[0].dV_low = StrToFloat(Edit71->Text);
                AdminForm->sys_koef->koef.mode_koefs[0].dV_hi = StrToFloat(Edit72->Text);
                AdminForm->sys_koef->koef.mode_koefs[0].dL_razg = StrToFloat(Edit41->Text);
                AdminForm->sys_koef->koef.mode_koefs[0].dL_zam = StrToFloat(Edit42->Text);
                AdminForm->sys_koef->koef.mode_koefs[0].dV_razg = StrToFloat(Edit49->Text);
                AdminForm->sys_koef->koef.mode_koefs[0].dV_zam = StrToFloat(Edit50->Text);

                AdminForm->sys_koef->koef.mode_koefs[1].Vmax = StrToFloat(Edit9->Text);
                AdminForm->sys_koef->koef.mode_koefs[1].a_zam = StrToFloat(Edit10->Text);
                AdminForm->sys_koef->koef.mode_koefs[1].a_razg = StrToFloat(Edit11->Text);
                AdminForm->sys_koef->koef.mode_koefs[1].a_oth = StrToFloat(Edit12->Text);
                AdminForm->sys_koef->koef.mode_koefs[1].L_zam = StrToFloat(Edit13->Text);
                AdminForm->sys_koef->koef.mode_koefs[1].L_razg = StrToFloat(Edit14->Text);
                AdminForm->sys_koef->koef.mode_koefs[1].L_oth = StrToFloat(Edit15->Text);
                AdminForm->sys_koef->koef.mode_koefs[1].L_dot = StrToFloat(Edit16->Text);
                AdminForm->sys_koef->koef.mode_koefs[1].V_low = StrToFloat(Edit17->Text);
                AdminForm->sys_koef->koef.mode_koefs[1].V_hi = StrToFloat(Edit20->Text);
                AdminForm->sys_koef->koef.mode_koefs[1].dV_low = StrToFloat(Edit69->Text);
                AdminForm->sys_koef->koef.mode_koefs[1].dV_hi = StrToFloat(Edit70->Text);
                AdminForm->sys_koef->koef.mode_koefs[1].dL_razg = StrToFloat(Edit43->Text);
                AdminForm->sys_koef->koef.mode_koefs[1].dL_zam = StrToFloat(Edit44->Text);
                AdminForm->sys_koef->koef.mode_koefs[1].dV_razg = StrToFloat(Edit51->Text);
                AdminForm->sys_koef->koef.mode_koefs[1].dV_zam = StrToFloat(Edit52->Text);

                AdminForm->sys_koef->koef.mode_koefs[2].Vmax = StrToFloat(Edit21->Text);
                AdminForm->sys_koef->koef.mode_koefs[2].a_zam = StrToFloat(Edit22->Text);
                AdminForm->sys_koef->koef.mode_koefs[2].a_razg = StrToFloat(Edit23->Text);
                AdminForm->sys_koef->koef.mode_koefs[2].a_oth = StrToFloat(Edit24->Text);
                AdminForm->sys_koef->koef.mode_koefs[2].L_zam = StrToFloat(Edit25->Text);
                AdminForm->sys_koef->koef.mode_koefs[2].L_razg = StrToFloat(Edit26->Text);
                AdminForm->sys_koef->koef.mode_koefs[2].L_oth = StrToFloat(Edit27->Text);
                AdminForm->sys_koef->koef.mode_koefs[2].L_dot = StrToFloat(Edit28->Text);
                AdminForm->sys_koef->koef.mode_koefs[2].V_low = StrToFloat(Edit29->Text);
                AdminForm->sys_koef->koef.mode_koefs[2].V_hi = StrToFloat(Edit30->Text);
                AdminForm->sys_koef->koef.mode_koefs[2].dV_low = StrToFloat(Edit67->Text);
                AdminForm->sys_koef->koef.mode_koefs[2].dV_hi = StrToFloat(Edit68->Text);
                AdminForm->sys_koef->koef.mode_koefs[2].dL_razg = StrToFloat(Edit45->Text);
                AdminForm->sys_koef->koef.mode_koefs[2].dL_zam = StrToFloat(Edit46->Text);
                AdminForm->sys_koef->koef.mode_koefs[2].dV_razg = StrToFloat(Edit55->Text);
                AdminForm->sys_koef->koef.mode_koefs[2].dV_zam = StrToFloat(Edit56->Text);

                AdminForm->sys_koef->koef.mode_koefs[3].Vmax = StrToFloat(Edit31->Text);
                AdminForm->sys_koef->koef.mode_koefs[3].a_zam = StrToFloat(Edit32->Text);
                AdminForm->sys_koef->koef.mode_koefs[3].a_razg = StrToFloat(Edit33->Text);
                AdminForm->sys_koef->koef.mode_koefs[3].a_oth = StrToFloat(Edit34->Text);
                AdminForm->sys_koef->koef.mode_koefs[3].L_zam = StrToFloat(Edit35->Text);
                AdminForm->sys_koef->koef.mode_koefs[3].L_razg = StrToFloat(Edit36->Text);
                AdminForm->sys_koef->koef.mode_koefs[3].L_oth = StrToFloat(Edit37->Text);
                AdminForm->sys_koef->koef.mode_koefs[3].L_dot = StrToFloat(Edit38->Text);
                AdminForm->sys_koef->koef.mode_koefs[3].V_low = StrToFloat(Edit39->Text);
                AdminForm->sys_koef->koef.mode_koefs[3].V_hi = StrToFloat(Edit40->Text);
                AdminForm->sys_koef->koef.mode_koefs[3].dV_low = StrToFloat(Edit58->Text);
                AdminForm->sys_koef->koef.mode_koefs[3].dV_hi = StrToFloat(Edit59->Text);
                AdminForm->sys_koef->koef.mode_koefs[3].dL_razg = StrToFloat(Edit47->Text);
                AdminForm->sys_koef->koef.mode_koefs[3].dL_zam = StrToFloat(Edit48->Text);
                AdminForm->sys_koef->koef.mode_koefs[3].dV_razg = StrToFloat(Edit53->Text);
                AdminForm->sys_koef->koef.mode_koefs[3].dV_zam = StrToFloat(Edit54->Text);

                AdminForm->sys_koef->koef.V_koef_U = StrToFloat(Edit60->Text);
                AdminForm->sys_koef->koef.VH_koef_DPI = StrToFloat(Edit57->Text);

                AdminForm->sys_koef->koef.hpp_0 = StrToFloat(Edit61->Text);
                AdminForm->sys_koef->koef.h0_1 = StrToFloat(Edit62->Text);
                AdminForm->sys_koef->koef.h1_2 = StrToFloat(Edit63->Text);
                AdminForm->sys_koef->koef.h2_3 = StrToFloat(Edit64->Text);
                AdminForm->sys_koef->koef.h3_4 = StrToFloat(Edit65->Text);
                AdminForm->sys_koef->koef.h4_5 = StrToFloat(Edit66->Text);

                AdminForm->sys_koef->koef.L_MAX = AdminForm->sys_koef->koef.hpp_0+
                                                  AdminForm->sys_koef->koef.h0_1+
                                                  AdminForm->sys_koef->koef.h1_2+
                                                  AdminForm->sys_koef->koef.h2_3+
                                                  AdminForm->sys_koef->koef.h3_4+
                                                  AdminForm->sys_koef->koef.h4_5;

                AdminForm->sys_koef->koef.dH_ned = StrToFloat(Edit74->Text);

                AdminForm->sys_koef->Save();
        }
        catch (...)
        {
        }

        Close();
}
//---------------------------------------------------------------------------
void __fastcall TKoefForm::FormShow(TObject *Sender)
{
        try
        {
                AdminForm->sys_koef->Load();

                Edit1->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[0].Vmax,ffFixed,6,3);
                Edit2->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[0].a_zam,ffFixed,6,3);
                Edit3->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[0].a_razg,ffFixed,6,3);
                Edit4->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[0].a_oth,ffFixed,6,3);
                Edit5->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[0].L_zam,ffFixed,6,3);
                Edit6->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[0].L_razg,ffFixed,6,3);
                Edit7->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[0].L_oth,ffFixed,6,3);
                Edit8->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[0].L_dot,ffFixed,6,3);
                Edit18->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[0].V_low,ffFixed,6,3);
                Edit19->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[0].V_hi,ffFixed,6,3);
                Edit71->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[0].dV_low,ffFixed,6,3);
                Edit72->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[0].dV_hi,ffFixed,6,3);
                Edit41->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[0].dL_razg,ffFixed,6,3);
                Edit42->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[0].dL_zam,ffFixed,6,3);
                Edit49->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[0].dV_razg,ffFixed,6,3);
                Edit50->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[0].dV_zam,ffFixed,6,3);

                Edit9->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[1].Vmax,ffFixed,6,3);
                Edit10->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[1].a_zam,ffFixed,6,3);
                Edit11->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[1].a_razg,ffFixed,6,3);
                Edit12->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[1].a_oth,ffFixed,6,3);
                Edit13->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[1].L_zam,ffFixed,6,3);
                Edit14->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[1].L_razg,ffFixed,6,3);
                Edit15->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[1].L_oth,ffFixed,6,3);
                Edit16->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[1].L_dot,ffFixed,6,3);
                Edit17->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[1].V_low,ffFixed,6,3);
                Edit20->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[1].V_hi,ffFixed,6,3);
                Edit69->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[1].dV_low,ffFixed,6,3);
                Edit70->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[1].dV_hi,ffFixed,6,3);
                Edit43->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[1].dL_razg,ffFixed,6,3);
                Edit44->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[1].dL_zam,ffFixed,6,3);
                Edit51->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[1].dV_razg,ffFixed,6,3);
                Edit52->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[1].dV_zam,ffFixed,6,3);

                Edit21->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[2].Vmax,ffFixed,6,3);
                Edit22->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[2].a_zam,ffFixed,6,3);
                Edit23->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[2].a_razg,ffFixed,6,3);
                Edit24->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[2].a_oth,ffFixed,6,3);
                Edit25->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[2].L_zam,ffFixed,6,3);
                Edit26->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[2].L_razg,ffFixed,6,3);
                Edit27->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[2].L_oth,ffFixed,6,3);
                Edit28->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[2].L_dot,ffFixed,6,3);
                Edit29->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[2].V_low,ffFixed,6,3);
                Edit30->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[2].V_hi,ffFixed,6,3);
                Edit67->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[2].dV_low,ffFixed,6,3);
                Edit68->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[2].dV_hi,ffFixed,6,3);
                Edit45->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[2].dL_razg,ffFixed,6,3);
                Edit46->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[2].dL_zam,ffFixed,6,3);
                Edit55->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[2].dV_razg,ffFixed,6,3);
                Edit56->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[2].dV_zam,ffFixed,6,3);

                Edit31->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[3].Vmax,ffFixed,6,3);
                Edit32->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[3].a_zam,ffFixed,6,3);
                Edit33->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[3].a_razg,ffFixed,6,3);
                Edit34->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[3].a_oth,ffFixed,6,3);
                Edit35->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[3].L_zam,ffFixed,6,3);
                Edit36->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[3].L_razg,ffFixed,6,3);
                Edit37->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[3].L_oth,ffFixed,6,3);
                Edit38->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[3].L_dot,ffFixed,6,3);
                Edit39->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[3].V_low,ffFixed,6,3);
                Edit40->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[3].V_hi,ffFixed,6,3);
                Edit58->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[3].dV_low,ffFixed,6,3);
                Edit59->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[3].dV_hi,ffFixed,6,3);
                Edit47->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[3].dL_razg,ffFixed,6,3);
                Edit48->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[3].dL_zam,ffFixed,6,3);
                Edit53->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[3].dV_razg,ffFixed,6,3);
                Edit54->Text = FloatToStrF(AdminForm->sys_koef->koef.mode_koefs[3].dV_zam,ffFixed,6,3);

                Edit60->Text = FloatToStrF(AdminForm->sys_koef->koef.V_koef_U,ffFixed,6,3);
                Edit57->Text = FloatToStr(AdminForm->sys_koef->koef.VH_koef_DPI);//,ffFixed,6,3);
                LMAXEdit->Text = FloatToStrF(AdminForm->sys_koef->koef.L_MAX,ffFixed,6,3);

                Edit61->Text = FloatToStrF(AdminForm->sys_koef->koef.hpp_0,ffFixed,6,3);
                Edit62->Text = FloatToStrF(AdminForm->sys_koef->koef.h0_1,ffFixed,6,3);
                Edit63->Text = FloatToStrF(AdminForm->sys_koef->koef.h1_2,ffFixed,6,3);
                Edit64->Text = FloatToStrF(AdminForm->sys_koef->koef.h2_3,ffFixed,6,3);
                Edit65->Text = FloatToStrF(AdminForm->sys_koef->koef.h3_4,ffFixed,6,3);
                Edit66->Text = FloatToStrF(AdminForm->sys_koef->koef.h4_5,ffFixed,6,3);

                Edit74->Text = FloatToStrF(AdminForm->sys_koef->koef.dH_ned,ffFixed,6,3);
        }
        catch (...)
        {
        }
}
//---------------------------------------------------------------------------

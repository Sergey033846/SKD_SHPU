//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "rep_i_unit.h"
#include "rep_unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TRepIstIdtForm *RepIstIdtForm;
//---------------------------------------------------------------------------
__fastcall TRepIstIdtForm::TRepIstIdtForm(TComponent* Owner)
        : TForm(Owner)
{
        diag3 = diag2 = NULL;
        ks2 = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TRepIstIdtForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        diag1->lp_list->DestroyList();
        delete diag1;
        delete ks1;

        if (diag2)
        {
                diag2->lp_list->DestroyList();
                delete diag2;
                diag2 = NULL;
        }
        if (diag3)
        {
                diag3->lp_list->DestroyList();
                delete diag3;
                diag3 = NULL;
        }
        if (ks2)
        {
                delete ks2;
                ks2 = NULL;
        }
}
//---------------------------------------------------------------------------
void __fastcall TRepIstIdtForm::XCheckBoxClick(TObject *Sender)
{
        ks1->draw_numbers_x = XCheckBox->Checked;

        ks1->DrawKoordSystem();
        RepIstIdtForm->diag1->RedrawWithOutNodes(freq_id);
        diag1->Redraw();

        if (ks2 && diag2)
        {
                ks2->draw_numbers_x = XCheckBox->Checked;

                ks2->DrawKoordSystem();
                RepIstIdtForm->diag2->RedrawWithOutNodes(freq_id);
                diag2->Redraw();
        }

        if (diag2 && diag3)
        {
                RepIstIdtForm->diag2->RedrawWithOutNodes(freq_id);
                diag2->Redraw();
                RepIstIdtForm->diag3->RedrawWithOutNodes(freq_id);
                diag3->Redraw();
        }
}
//---------------------------------------------------------------------------
void __fastcall TRepIstIdtForm::YCheckBoxClick(TObject *Sender)
{
        ks1->draw_numbers_y = YCheckBox->Checked;

        ks1->DrawKoordSystem();
        RepIstIdtForm->diag1->RedrawWithOutNodes(freq_id);
        diag1->Redraw();

/*        if (ks2 && diag2)
        {
                ks2->draw_numbers_y = YCheckBox->Checked;

                ks2->DrawKoordSystem();
                RepIstIdtForm->diag2->RedrawWithOutNodes();
                diag2->Redraw();
        }*/

        if (diag2 && diag3)
        {
                RepIstIdtForm->diag2->RedrawWithOutNodes(freq_id);
                diag2->Redraw();
                RepIstIdtForm->diag3->RedrawWithOutNodes(freq_id);
                diag3->Redraw();
        }
}
//---------------------------------------------------------------------------
void __fastcall TRepIstIdtForm::SetkaCheckBoxClick(TObject *Sender)
{
        ks1->draw_setka = SetkaCheckBox->Checked;

        ks1->DrawKoordSystem();
        RepIstIdtForm->diag1->RedrawWithOutNodes(freq_id);
        diag1->Redraw();

        if (ks2 && diag2)
        {
                ks2->draw_setka = SetkaCheckBox->Checked;

                ks2->DrawKoordSystem();
                RepIstIdtForm->diag2->RedrawWithOutNodes(freq_id);
                diag2->Redraw();
        }

        if (diag2 && diag3)
        {
                RepIstIdtForm->diag2->RedrawWithOutNodes(freq_id);
                diag2->Redraw();
                RepIstIdtForm->diag3->RedrawWithOutNodes(freq_id);
                diag3->Redraw();
        }
}
//---------------------------------------------------------------------------
void __fastcall TRepIstIdtForm::BitBtn1Click(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------
void __fastcall TRepIstIdtForm::KXIncButtonClick(TObject *Sender)
{
        ks1->koef.kx += 30;

        ks1->DrawKoordSystem();
        RepIstIdtForm->diag1->RedrawWithOutNodes(freq_id);
        diag1->Redraw();

        if (ks2 && diag2)
        {
                ks2->koef.kx += 30;

                ks2->DrawKoordSystem();
                RepIstIdtForm->diag2->RedrawWithOutNodes(freq_id);
                diag2->Redraw();
        }

        if (diag2 && diag3)
        {
                RepIstIdtForm->diag2->RedrawWithOutNodes(freq_id);
                diag2->Redraw();
                RepIstIdtForm->diag3->RedrawWithOutNodes(freq_id);
                diag3->Redraw();
        }
}

void __fastcall TRepIstIdtForm::KXDecButtonClick(TObject *Sender)
{
        if (ks1->koef.kx > 30)
        {
                ks1->koef.kx -= 30;

                ks1->DrawKoordSystem();
                RepIstIdtForm->diag1->RedrawWithOutNodes(freq_id);
                diag1->Redraw();

                if (ks2 && diag2)
                {
                        ks2->koef.kx -= 30;

                        ks2->DrawKoordSystem();
                        RepIstIdtForm->diag2->RedrawWithOutNodes(freq_id);
                        diag2->Redraw();
                }

                if (diag2 && diag3)
                {
                        RepIstIdtForm->diag2->RedrawWithOutNodes(freq_id);
                        diag2->Redraw();
                        RepIstIdtForm->diag3->RedrawWithOutNodes(freq_id);
                        diag3->Redraw();
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TRepIstIdtForm::KYIncButtonClick(TObject *Sender)
{
        ks1->koef.ky += 15;

        ks1->DrawKoordSystem();
        RepIstIdtForm->diag1->RedrawWithOutNodes(freq_id);
        diag1->Redraw();

/*        if (ks2 && diag2)
        {
                ks2->koef.ky += 15;

                ks2->DrawKoordSystem();
                RepIstIdtForm->diag2->RedrawWithOutNodes();
                diag2->Redraw();
        }*/

        if (diag2 && diag3)
        {
                RepIstIdtForm->diag2->RedrawWithOutNodes(freq_id);
                diag2->Redraw();
                RepIstIdtForm->diag3->RedrawWithOutNodes(freq_id);
                diag3->Redraw();
        }
}
//---------------------------------------------------------------------------

void __fastcall TRepIstIdtForm::KYDecButtonClick(TObject *Sender)
{
        if (ks1->koef.ky > 15)
        {
                ks1->koef.ky -= 15;

                ks1->DrawKoordSystem();
                RepIstIdtForm->diag1->RedrawWithOutNodes(freq_id);
                diag1->Redraw();

/*                if (ks2 && diag2)
                {
                        ks2->koef.ky -= 15;

                        ks2->DrawKoordSystem();
                        RepIstIdtForm->diag2->RedrawWithOutNodes();
                        diag2->Redraw();
                }*/

                if (diag2 && diag3)
                {
                        RepIstIdtForm->diag2->RedrawWithOutNodes(freq_id);
                        diag2->Redraw();
                        RepIstIdtForm->diag3->RedrawWithOutNodes(freq_id);
                        diag3->Redraw();
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TRepIstIdtForm::PrintButtonClick(TObject *Sender)
{
/*        ReportForm2->QRImage1->Width = Image1->Width;
        ReportForm2->QRImage1->Height = Image1->Height;
        ReportForm2->QRImage1->Canvas->CopyRect(ReportForm2->QRImage1->ClientRect,
                                                               Image1->Canvas,
                                                               Image1->ClientRect);
  */

        Image1->Picture->SaveToFile("temp.bmp");
        ReportForm2->QRImage1->Picture->LoadFromFile("temp.bmp");
        ReportForm2->QRImage1->Update();
//        DeleteFile("temp.bmp");

        ReportForm2->QuickRep1->Update();
        ReportForm2->QuickRep1->PreviewModal();
}
//---------------------------------------------------------------------------

void __fastcall TRepIstIdtForm::RightButtonClick(TObject *Sender)
{
        ks1->log_koord.x += 0.2;

        ks1->DrawKoordSystem();
        diag1->RedrawWithOutNodes(freq_id);
        diag1->Redraw();

        if (ks2 && diag2)
        {
                ks2->log_koord.x += 0.2;

                ks2->DrawKoordSystem();
                RepIstIdtForm->diag2->RedrawWithOutNodes(freq_id);
                diag2->Redraw();
        }

        if (diag2 && diag3)
        {
                RepIstIdtForm->diag2->RedrawWithOutNodes(freq_id);
                diag2->Redraw();
                RepIstIdtForm->diag3->RedrawWithOutNodes(freq_id);
                diag3->Redraw();
        }
}
//---------------------------------------------------------------------------

void __fastcall TRepIstIdtForm::LeftNuttonClick(TObject *Sender)
{
        ks1->log_koord.x -= 0.2;

        ks1->DrawKoordSystem();
        diag1->RedrawWithOutNodes(freq_id);
        diag1->Redraw();

        if (ks2 && diag2)
        {
                ks2->log_koord.x -= 0.2;

                ks2->DrawKoordSystem();
                RepIstIdtForm->diag2->RedrawWithOutNodes(freq_id);
                diag2->Redraw();
        }

        if (diag2 && diag3)
        {
                RepIstIdtForm->diag2->RedrawWithOutNodes(freq_id);
                diag2->Redraw();
                RepIstIdtForm->diag3->RedrawWithOutNodes(freq_id);
                diag3->Redraw();
        }        
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "edit_etalon.h"
#include "admin.h"
#include "add_node.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEditEtalonForm *EditEtalonForm;

int dx,dy;
//---------------------------------------------------------------------------
__fastcall TEditEtalonForm::TEditEtalonForm(TComponent* Owner)
        : TForm(Owner)
{
        diag_rect = Rect(0,0,Image1->Width,Image1->Height);
        ControlStyle = TControlStyle() << csOpaque;
}
//---------------------------------------------------------------------------
void __fastcall TEditEtalonForm::FormShow(TObject *Sender)
{
        FILE *f = fopen(f_name.c_str(),"rb");

        TPoint pk;
        pk.x = 1+5;
        pk.y = Image1->ClientHeight-10;

        int log_x = 1;
        int log_y = 1;

        koord_system = new TKoordSystem(Image1,diag_rect,pk,log_x,log_y);
        koord_system->log_koord.x = 0;
        koord_system->log_koord.y = 0;
        koord_system->col = clGreen;

        diagram = new TDiagram(koord_system,AdminForm->ChannelList);
        diagram->col = clGreen;

        if (f != NULL)
        {
                fread(&(koord_system->log_koord),sizeof(TLogPoint),1,f);
                fread(&(diagram->col),sizeof(TColor),1,f);
                fread(&(koord_system->koef),sizeof(TKoordKoef),1,f);
                fread(&(koord_system->log_x),sizeof(int),1,f);
                fread(&(koord_system->log_y),sizeof(int),1,f);

                diagram->lp_list->ReadFromFile2(f);

                for (int i=0; i<diagram->lp_list->count; i++)
                {
                        TImage *new_img = new TImage(this);
                        new_img->Parent = this;
                        new_img->Tag = i;
                        new_img->OnDblClick = ImageNodeDblClick;
                        new_img->OnMouseDown = ImageNodeMouseDown;
                        new_img->PopupMenu = PopupMenu1;
                        diagram->img_list->Add(new_img);
                }

                fclose(f);
        }

        koord_system->DrawKoordSystem();
        koord_system->Redraw();
        diagram->RedrawWithNodes();
        diagram->Redraw();
}
//---------------------------------------------------------------------------

// увеличение масштаба по-горизонтали
void __fastcall TEditEtalonForm::Button4Click(TObject *Sender)
{
        koord_system->koef.kx += 5;
        koord_system->DrawKoordSystem();
        diagram->RedrawWithNodes();
        diagram->Redraw();
}
//---------------------------------------------------------------------------

void __fastcall TEditEtalonForm::Button3Click(TObject *Sender)
{
        if (koord_system->koef.kx > 5)
        {
                koord_system->koef.kx -= 5;
                koord_system->DrawKoordSystem();
                diagram->RedrawWithNodes();
                diagram->Redraw();
        }
}
//---------------------------------------------------------------------------

void __fastcall TEditEtalonForm::Button5Click(TObject *Sender)
{
        koord_system->koef.ky += 5;
        koord_system->DrawKoordSystem();
        diagram->RedrawWithNodes();
        diagram->Redraw();
}
//---------------------------------------------------------------------------

void __fastcall TEditEtalonForm::Button6Click(TObject *Sender)
{
        if (koord_system->koef.ky > 5)
        {
                koord_system->koef.ky -= 5;
                koord_system->DrawKoordSystem();
                diagram->RedrawWithNodes();
                diagram->Redraw();
        }
}
//---------------------------------------------------------------------------

void __fastcall TEditEtalonForm::ImageNodeDblClick(TObject *Sender)
{
        AddNodeForm->XEdit->Text = FloatToStrF((*diagram->lp_list)[((TImage *)Sender)->Tag]->x,ffFixed,6,3);
        AddNodeForm->YEdit->Text = FloatToStrF((*diagram->lp_list)[((TImage *)Sender)->Tag]->y,ffFixed,6,3);

        AddNodeForm->BitBtn1->Caption = "Обновить";

        if (AddNodeForm->ShowModal() == mrOk)
        {
                (*diagram->lp_list)[((TImage *)Sender)->Tag]->x = StrToFloat(AddNodeForm->XEdit->Text);
                (*diagram->lp_list)[((TImage *)Sender)->Tag]->y = StrToFloat(AddNodeForm->YEdit->Text);
                koord_system->DrawKoordSystem();
                diagram->RedrawWithNodes();
                diagram->Redraw();
        }

        AddNodeForm->BitBtn1->Caption = "Добавить";
}

/*void __fastcall TEditEtalonForm::Image2MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
        if (Shift.Contains(ssLeft))
        {
                Image2->Left = Image2->Left+X-dx;
                Image2->Top = Image2->Top+Y-dy;
        }
} */
//---------------------------------------------------------------------------

void __fastcall TEditEtalonForm::ImageNodeMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
/*        dx = X;
        dy = Y;*/

        if (Button == mbRight)
        {
                im_tag = ((TImage *)Sender)->Tag;
                PopupMenu1->Popup(((TImage *)Sender)->Left,((TImage *)Sender)->Top);
        }
}
//---------------------------------------------------------------------------

void __fastcall TEditEtalonForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        delete diagram;
        delete koord_system;
}
//---------------------------------------------------------------------------

// добавление нового узла
void __fastcall TEditEtalonForm::Button1Click(TObject *Sender)
{
        AddNodeForm->XEdit->Text = "0";
        AddNodeForm->YEdit->Text = "0";

        if (AddNodeForm->ShowModal() == mrOk)
        {
                TLogPoint *new_point = new TLogPoint;

                try
                {
                        new_point->x = StrToFloat(AddNodeForm->XEdit->Text);
                }
                catch (...)
                {
                        new_point->x = 5;
                }

                try
                {
                        new_point->y = StrToFloat(AddNodeForm->YEdit->Text);
                }
                catch (...)
                {
                        new_point->y = 5;
                }
                diagram->lp_list->Add(new_point);

                TImage *new_img = new TImage(EditEtalonForm);
                new_img->Parent = this;
                new_img->Tag = diagram->lp_list->count-1;
                new_img->OnDblClick = ImageNodeDblClick;
                new_img->OnMouseDown = ImageNodeMouseDown;
                new_img->PopupMenu = PopupMenu1;

                diagram->img_list->Add(new_img);

                diagram->SortNodes(1);

                koord_system->DrawKoordSystem();
                diagram->RedrawWithNodes();
                diagram->Redraw();
        }
}
//---------------------------------------------------------------------------

void __fastcall TEditEtalonForm::Button7Click(TObject *Sender)
{
        if (koord_system->log_koord.x > 0)
        {
                koord_system->log_koord.x -= 1;
                koord_system->DrawKoordSystem();
                diagram->RedrawWithNodes();
                diagram->Redraw();
        }
}
//---------------------------------------------------------------------------

void __fastcall TEditEtalonForm::Button8Click(TObject *Sender)
{
        koord_system->log_koord.x += 1;
        koord_system->DrawKoordSystem();
        diagram->RedrawWithNodes();
        diagram->Redraw();
}
//---------------------------------------------------------------------------

void __fastcall TEditEtalonForm::Button9Click(TObject *Sender)
{
        koord_system->log_koord.y += 1;
        koord_system->DrawKoordSystem();
        diagram->RedrawWithNodes();
        diagram->Redraw();
}
//---------------------------------------------------------------------------

void __fastcall TEditEtalonForm::Button10Click(TObject *Sender)
{
        if (koord_system->log_koord.y > 0)
        {
                koord_system->log_koord.y -= 1;
                koord_system->DrawKoordSystem();
                diagram->RedrawWithNodes();
                diagram->Redraw();
        }
}
//---------------------------------------------------------------------------

void __fastcall TEditEtalonForm::Button11Click(TObject *Sender)
{
        diagram->SortNodes(0);

        FILE *f = fopen(f_name.c_str(),"wb");

        fwrite(&(koord_system->log_koord),sizeof(TLogPoint),1,f);
        fwrite(&(diagram->col),sizeof(TColor),1,f);
        fwrite(&(koord_system->koef),sizeof(TKoordKoef),1,f);
        fwrite(&(koord_system->log_x),sizeof(int),1,f);
        fwrite(&(koord_system->log_y),sizeof(int),1,f);
        fwrite(&(diagram->lp_list->count),sizeof(int),1,f);
        diagram->lp_list->WriteToFile2(f);

        fclose(f);
}
//---------------------------------------------------------------------------

void __fastcall TEditEtalonForm::Button12Click(TObject *Sender)
{
        diagram->SplineByFormula(3,AdminForm->sys_koef->koef,mode_id,speed_id);

        diagram->img_list->DestroyList();

        for (int i=0; i<diagram->lp_list->count; i++)
        {
                TImage *new_img = new TImage(this);
                new_img->Parent = this;
                new_img->Tag = i;
                new_img->OnDblClick = ImageNodeDblClick;
                new_img->OnMouseDown = ImageNodeMouseDown;
                new_img->PopupMenu = PopupMenu1;
                diagram->img_list->Add(new_img);
        }

        koord_system->DrawKoordSystem();
        diagram->RedrawWithNodes();
        diagram->Redraw();
}
//---------------------------------------------------------------------------
// удаление узла
void __fastcall TEditEtalonForm::N1Click(TObject *Sender)
{
        for (int i=0; i<diagram->img_list->count; i++)
        {
                if ((*diagram->img_list)[i]->Tag > im_tag) (*diagram->img_list)[i]->Tag--;
        }

        diagram->lp_list->Del(im_tag);
        diagram->img_list->Del(im_tag);
        koord_system->DrawKoordSystem();

        diagram->SortNodes(1);

        diagram->RedrawWithNodes();
        diagram->Redraw();
}
//---------------------------------------------------------------------------
// перемещение логических координат
void __fastcall TEditEtalonForm::Button13Click(TObject *Sender)
{
        AnsiString st = AddNodeForm->Caption;
        AddNodeForm->Caption = "Начало координат";
        if (AddNodeForm->ShowModal() == mrOk)
        {
                try
                {
                        diagram->ks->log_koord.x = StrToFloat(AddNodeForm->XEdit->Text);
                        diagram->ks->log_koord.y = StrToFloat(AddNodeForm->YEdit->Text);
                }
                catch (...)
                {
                }
                koord_system->DrawKoordSystem();
                diagram->RedrawWithNodes();
                diagram->Redraw();
        }
        AddNodeForm->Caption = st;
}
//---------------------------------------------------------------------------

// удаление всех узлов
void __fastcall TEditEtalonForm::Button14Click(TObject *Sender)
{
        diagram->lp_list->DestroyList();
        diagram->img_list->DestroyList();

        koord_system->DrawKoordSystem();
        diagram->RedrawWithNodes();
        diagram->Redraw();
}
//---------------------------------------------------------------------------



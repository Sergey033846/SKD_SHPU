//---------------------------------------------------------------------------
#pragma hdrstop

#include "vis_unit.h"
#include "main_unit.h"

TVisualisationChannel::TVisualisationChannel(TChannelType v_type,TArchiveRecord *curr_rec)
{
        vis_type = v_type;
        rec = curr_rec;
}

void TVisualisationChannel::Repaint()
{
        Graphics::TBitmap *btmp = MainForm->btmp;
        btmp->Canvas->Brush->Color = clWhite;        

        if (vis_type == tchtDISKRET)
        {
           //-----------------------------
           btmp->Width = r.Width();
           btmp->Height = r.Height();

           TRect RectS;

           RectS = Rect(0,0,r.Width(),r.Height());
           //-----------------------------

           if (ChannelID_off == -1)
           {
                if (ch_id_on_data->diskret)
                {
                        btmp->Canvas->Brush->Color = col;
                        btmp->Canvas->FillRect(RectS);
                        if (col == clYellow) btmp->Canvas->Font->Color = clBlack;
                        else btmp->Canvas->Font->Color = clWhite;
                        btmp->Canvas->Font->Style = TFontStyles()<< fsBold;

                        btmp->Canvas->Font->Name = "Arial";
                        btmp->Canvas->Font->Size = 8;

                        int x = btmp->Width - btmp->Canvas->TextWidth(capt);

                        btmp->Canvas->TextOutA(x/2,0,capt);
                }
                else
                {
                        btmp->Canvas->Brush->Color = coloff;
                        btmp->Canvas->FillRect(RectS);
                        if (coloff == clRed) btmp->Canvas->Font->Color = clWhite;
                        else btmp->Canvas->Font->Color = clBlack;
                        btmp->Canvas->Font->Style = TFontStyles()<< fsBold;
                        btmp->Canvas->Font->Name = "Arial";
                        btmp->Canvas->Font->Size = 8;
                        int x = btmp->Width - btmp->Canvas->TextWidth(capt);

                        btmp->Canvas->TextOutA(x/2,0,capt);
                }
           }

           if (ChannelID_off != -1)
           {
                if (ch_id_on_data->diskret)
                {
                        if (ch_id_off_data->diskret)
                        {
                                btmp->Canvas->Brush->Color = clBlue;
                                btmp->Canvas->FillRect(RectS);
                                btmp->Canvas->Font->Color = clWhite;
                                btmp->Canvas->Font->Style = TFontStyles()<< fsBold;
                                btmp->Canvas->Font->Name = "Arial";
                                btmp->Canvas->Font->Size = 8;
                                int x = btmp->Width - btmp->Canvas->TextWidth(capt);
                                btmp->Canvas->TextOutA(x/2,0,capt);
                        }
                        else
                        {
                                btmp->Canvas->Brush->Color = col;
                                btmp->Canvas->FillRect(RectS);
                                if (col == clYellow) btmp->Canvas->Font->Color = clBlack;
                                else btmp->Canvas->Font->Color = clWhite;
                                btmp->Canvas->Font->Style = TFontStyles()<< fsBold;
                                btmp->Canvas->Font->Name = "Arial";
                                btmp->Canvas->Font->Size = 8;
                                int x = btmp->Width - btmp->Canvas->TextWidth(capt);
                                btmp->Canvas->TextOutA(x/2,0,capt);
                        }
                }
                else
                {
                        if (ch_id_off_data->diskret)
                        {
                                btmp->Canvas->Brush->Color = coloff;
                                btmp->Canvas->FillRect(RectS);
                                if (coloff == clRed) btmp->Canvas->Font->Color = clWhite;
                                else btmp->Canvas->Font->Color = clBlack;
                                btmp->Canvas->Font->Style = TFontStyles()<< fsBold;
                                btmp->Canvas->Font->Name = "Arial";
                                btmp->Canvas->Font->Size = 8;
                                int x = btmp->Width - btmp->Canvas->TextWidth(capt);
                                btmp->Canvas->TextOutA(x/2,0,capt);
                        }
                        else
                        {
                                btmp->Canvas->Brush->Color = clBlue;
                                btmp->Canvas->FillRect(RectS);
                                btmp->Canvas->Font->Color = clWhite;
                                btmp->Canvas->Font->Style = TFontStyles()<< fsBold;
                                btmp->Canvas->Font->Name = "Arial";
                                btmp->Canvas->Font->Size = 8;
                                int x = btmp->Width - btmp->Canvas->TextWidth(capt);
                                btmp->Canvas->TextOutA(x/2,0,capt);
                        }
                }
           };

           MainForm->Image1->Canvas->CopyRect(r,btmp->Canvas,RectS);
        }
        else
        {

             if (capt == "Uтг")
             {
                TImage* img = (TImage*)control;

                        //-----------------------------
                        TRect RectS;

                        RectS = img->ClientRect;

                        btmp->Width = img->Width;
                        btmp->Height = img->Height;

                        btmp->Canvas->CopyRect(RectS,img->Canvas,RectS);
                        //-----------------------------

                float tA = ch_id_analog_data->analog;
                if (tA > 200.0) tA = 200;
                if (tA < -200.0) tA = -200;                
//                float phi = tA*67.5*M_PI/(180*200) + 90*M_PI/180;
                float phi = tA*72*M_PI/(180*200) + 90*M_PI/180;

                int w = img->Width;
                int h = img->Height;
                int dx = (h-12) * cos(phi);
                int dy = (h-12) * sin(phi);
                btmp->Canvas->Pen->Width = 2;
                btmp->Canvas->Pen->Color = clBlack;
                btmp->Canvas->MoveTo(w/2,h);
                btmp->Canvas->LineTo(w/2-dx,h-dy);
                btmp->Canvas->Pen->Width = 1;

                btmp->Canvas->Font->Color = clGray;
//                btmp->Canvas->Font->Style = TFontStyles()<< fsBold;
                btmp->Canvas->Font->Name = "Arial";
                btmp->Canvas->Font->Size = 8;
//                btmp->Canvas->TextOutA(w-45-5,h-15+2,FloatToStrF(tA,ffFixed,8,2));
                btmp->Canvas->TextOutA(w-45+8,0,FloatToStrF(ch_id_analog_data->analog,ffFixed,8,2));

                MainForm->Image1->Canvas->CopyRect(r,btmp->Canvas,RectS);
             }
             else
             if (capt == "Iдт")
             {
                TImage* img = (TImage*)control;

                        //-----------------------------
                        TRect RectS;

                        RectS = img->ClientRect;

                        btmp->Width = img->Width;
                        btmp->Height = img->Height;

                        btmp->Canvas->CopyRect(RectS,img->Canvas,RectS);
                        //-----------------------------

                float tA = ch_id_analog_data->analog;
                if (tA > 500.0) tA = 500.0;
                float phi = tA*140*M_PI/(180*500) + 20*M_PI/180;
                int w = img->Width;
                int h = img->Height;
                int dx = (h-12) * cos(phi);
                int dy = (h-12) * sin(phi);
                btmp->Canvas->Pen->Width = 2;
                btmp->Canvas->Pen->Color = clBlack;
                btmp->Canvas->MoveTo(w/2,h);
                btmp->Canvas->LineTo(w/2-dx,h-dy);
                btmp->Canvas->Pen->Width = 1;

                btmp->Canvas->Font->Color = clGray;
//                btmp->Canvas->Font->Style = TFontStyles()<< fsBold;
                btmp->Canvas->Font->Name = "Arial";
                btmp->Canvas->Font->Size = 8;
//                btmp->Canvas->TextOutA(w-40,h-15,FloatToStrF(tA,ffFixed,8,2));
                btmp->Canvas->TextOutA(w-45+8,0,FloatToStrF(ch_id_analog_data->analog,ffFixed,8,2));

                MainForm->Image1->Canvas->CopyRect(r,btmp->Canvas,RectS);
             }
             else
             if (capt == "Iст")
             {
                TImage* img = (TImage*)control;
                        //-----------------------------
                        TRect RectS;

                        RectS = img->ClientRect;

                        btmp->Width = img->Width;
                        btmp->Height = img->Height;

                        btmp->Canvas->CopyRect(RectS,img->Canvas,RectS);
                        //-----------------------------

                float tA = ch_id_analog_data->analog;
                if (tA > 600.0) tA = 600.0;
                float phi = tA*135*M_PI/(180*600) + 22.5*M_PI/180;
                int w = img->Width;
                int h = img->Height;
                int dx = (h-12) * cos(phi);
                int dy = (h-12) * sin(phi);
                btmp->Canvas->Pen->Width = 2;
                btmp->Canvas->Pen->Color = clBlack;
                btmp->Canvas->MoveTo(w/2,h);
                btmp->Canvas->LineTo(w/2-dx,h-dy);
                btmp->Canvas->Pen->Width = 1;

                btmp->Canvas->Font->Color = clGray;
//                btmp->Canvas->Font->Style = TFontStyles()<< fsBold;
                btmp->Canvas->Font->Name = "Arial";
                btmp->Canvas->Font->Size = 8;
//                btmp->Canvas->TextOutA(w-40,h-15,FloatToStrF(tA,ffFixed,8,2));
                btmp->Canvas->TextOutA(w-45+8,0,FloatToStrF(ch_id_analog_data->analog,ffFixed,8,2));

                MainForm->Image1->Canvas->CopyRect(r,btmp->Canvas,RectS);
             }
             else
             if (capt == "P")
             {
                        //-----------------------------
                        TRect RectS;
                        btmp->Width = r.Width();
                        btmp->Height = r.Height();

                        RectS = Rect(0,0,r.Width(),r.Height());
                        //-----------------------------

                btmp->Canvas->Brush->Color = clWhite;
                btmp->Canvas->FillRect(RectS);
                btmp->Canvas->Font->Color = clBlack;
                btmp->Canvas->Font->Style = TFontStyles()<< fsBold;
                btmp->Canvas->Font->Name = "Arial";
                btmp->Canvas->Font->Size = 9;
                btmp->Canvas->TextOutA(6,0,FloatToStrF(ch_id_analog_data->analog,ffFixed,8,2));

                MainForm->Image1->Canvas->CopyRect(r,btmp->Canvas,RectS);
             }

        if (vis_type == tchtPROGRAM)
        {
                if (capt == "H")
                {
                        //-----------------------------
                        TRect RectS;
                        btmp->Width = r.Width();
                        btmp->Height = r.Height();
                        RectS = Rect(0,0,r.Width(),r.Height());
                        //-----------------------------
                        btmp->Canvas->Brush->Color = clWhite;
                        btmp->Canvas->FillRect(RectS);
                        btmp->Canvas->Font->Color = clBlack;
                        btmp->Canvas->Font->Style = TFontStyles()<< fsBold;
                        btmp->Canvas->Font->Name = "Arial";
                        btmp->Canvas->Font->Size = 9;
                        btmp->Canvas->TextOutA(5,1,FloatToStrF(MainForm->st.Hl,ffFixed,5,1));
                        btmp->Canvas->TextOutA(50,1,FloatToStrF(MainForm->st.Hr,ffFixed,5,1));
//                        btmp->Canvas->TextOutA(50,1,FloatToStrF(MainForm->sys_koef->koef.L_MAX-MainForm->st.Hl,ffFixed,5,1));

                        MainForm->Image1->Canvas->CopyRect(r,btmp->Canvas,RectS);
                        //-----------------------------

                        // вывести фон
                        MainForm->Image1->Canvas->CopyRect(MainForm->LiftRect1,MainForm->LiftBtmp1->Canvas,Rect(0,0,24,28));
                        MainForm->Image1->Canvas->CopyRect(MainForm->LiftRect2,MainForm->LiftBtmp2->Canvas,Rect(0,0,24,28));
                        //------------

                        float hhh;
                hhh = MainForm->sys_koef->koef.hpp_0+
                     MainForm->sys_koef->koef.h0_1+
                     MainForm->sys_koef->koef.h1_2+
                     MainForm->sys_koef->koef.h2_3+
                     MainForm->sys_koef->koef.h3_4+
                     MainForm->sys_koef->koef.h4_5;
//                        if (MainForm->gor_act == 5)
                        {
                                MainForm->LiftImage1->Left = 932;
                                MainForm->LiftImage1->Top = 20+(584-20)*MainForm->st.Hl/hhh-2;
                                MainForm->LiftImage2->Left = 966;
                                MainForm->LiftImage2->Top = 20+(584-20)*MainForm->st.Hr/hhh-2;
//                                MainForm->LiftImage2->Top = 584-(584-20)*MainForm->st.Hl/MainForm->sys_koef->koef.L_MAX-2;
                        }
/*                        if (MainForm->gor_act == 3)
                        {
                                MainForm->LiftImage1->Left = 932;
                                MainForm->LiftImage1->Top = 20+(396-20)*MainForm->st.Hl/MainForm->sys_koef->koef.L_MAX-2;
                                MainForm->LiftImage2->Left = 966;
                                MainForm->LiftImage2->Top = 20+(396-20)*MainForm->st.Hr/MainForm->sys_koef->koef.L_MAX-2;
//                                MainForm->LiftImage2->Top = 396-(396-20)*MainForm->st.Hl/MainForm->sys_koef->koef.L_MAX-2;
                        }
  */
                        //----------------
                        MainForm->LiftRect1.Left = MainForm->LiftImage1->Left;
                        MainForm->LiftRect1.Top = MainForm->LiftImage1->Top;
                        MainForm->LiftRect1.Right = MainForm->LiftImage1->Left+MainForm->LiftImage1->Width;
                        MainForm->LiftRect1.Bottom = MainForm->LiftImage1->Top+MainForm->LiftImage1->Height;

                        MainForm->LiftRect2.Left = MainForm->LiftImage2->Left;
                        MainForm->LiftRect2.Top = MainForm->LiftImage2->Top;
                        MainForm->LiftRect2.Right = MainForm->LiftImage2->Left+MainForm->LiftImage2->Width;
                        MainForm->LiftRect2.Bottom = MainForm->LiftImage2->Top+MainForm->LiftImage2->Height;

                        // запомнить фон
                        MainForm->LiftBtmp1->Canvas->CopyRect(Rect(0,0,24,28),MainForm->Image1->Canvas,MainForm->LiftRect1);
                        MainForm->LiftBtmp2->Canvas->CopyRect(Rect(0,0,24,28),MainForm->Image1->Canvas,MainForm->LiftRect2);
                        //----------------

                        if (MainForm->st.direct == 1)
                        {
                                MainForm->LiftImage2->Canvas->Brush->Color = clBlack;
                                MainForm->LiftImage2->Canvas->Font->Color = clBlack;
                                MainForm->LiftImage2->Canvas->Rectangle(10,12,15,17);

                                MainForm->LiftImage1->Canvas->Brush->Color = clYellow;
                                MainForm->LiftImage1->Canvas->Pen->Color = clBlack;
                                MainForm->LiftImage1->Canvas->Rectangle(MainForm->LiftImage1->ClientRect);
                        }
                        if (MainForm->st.direct == -1)
                        {
                                MainForm->LiftImage1->Canvas->Brush->Color = clBlack;
                                MainForm->LiftImage1->Canvas->Font->Color = clBlack;
                                MainForm->LiftImage1->Canvas->Rectangle(10,12,15,17);

                                MainForm->LiftImage2->Canvas->Brush->Color = clYellow;
                                MainForm->LiftImage2->Canvas->Pen->Color = clBlack;
                                MainForm->LiftImage2->Canvas->Rectangle(MainForm->LiftImage2->ClientRect);
                        }

                        // отобразить на новом месте
                        MainForm->Image1->Canvas->CopyRect(MainForm->LiftRect1,MainForm->LiftImage1->Canvas,Rect(0,0,24,28));
                        MainForm->Image1->Canvas->CopyRect(MainForm->LiftRect2,MainForm->LiftImage2->Canvas,Rect(0,0,24,28));
                        //----------------

                        float LMAX = MainForm->sys_koef->koef.L_MAX;
                        if (MainForm->st.Hl >=0 && MainForm->st.Hl <= 12)
                        {
                                MainForm->H12Image->Canvas->Brush->Color = clRed;
                                MainForm->H12Image->Canvas->Rectangle(MainForm->H12Image->ClientRect);
                                MainForm->H12Image->Top = 47+(611-47+1)*MainForm->st.Hl/12-2;
                        }
                        else
                        if (LMAX-MainForm->st.Hl >=0 && LMAX-MainForm->st.Hl <= 12)
                        {
                                MainForm->H12Image->Canvas->Brush->Color = clRed;
                                MainForm->H12Image->Canvas->Rectangle(MainForm->H12Image->ClientRect);
                                MainForm->H12Image->Top = 47+(611-47+1)*(LMAX-MainForm->st.Hl)/12-2;
                        }
                        else
                        if (MainForm->st.Hl > 12 && LMAX-MainForm->st.Hl > 12)
                        {
                                MainForm->H12Image->Canvas->Brush->Color = clRed;
                                MainForm->H12Image->Canvas->Rectangle(MainForm->H12Image->ClientRect);
                                MainForm->H12Image->Top = 47+(611-47+1)*12/12-2;
                        }

                        MainForm->Image1->Canvas->CopyRect(MainForm->H12Rect,MainForm->H12Btmp->Canvas,Rect(0,0,32,5));

                        MainForm->H12Rect.Top = MainForm->H12Image->Top;
                        MainForm->H12Rect.Bottom = MainForm->H12Image->Top+MainForm->H12Image->Height;

                        MainForm->H12Btmp->Canvas->CopyRect(Rect(0,0,32,5),MainForm->Image1->Canvas,MainForm->H12Rect);
                        MainForm->Image1->Canvas->CopyRect(MainForm->H12Rect,MainForm->H12Image->Canvas,Rect(0,0,32,5));
                }
                else
                if (capt == "SPEED")
                {
                        TImage* img = (TImage*)control;

                        //-----------------------------
                        TRect RectS;

                        RectS = img->ClientRect;

                        btmp->Width = img->Width;
                        btmp->Height = img->Height;

                        btmp->Canvas->CopyRect(RectS,img->Canvas,RectS);
                        //-----------------------------

                        float tA = ch_id_analog_data->analog;
                        if (tA > 6) tA = 6;

                        float phi = tA*135*M_PI/(180*6) + 22.5*M_PI/180;
                        int w = img->Width;
                        int h = img->Height;
                        int dx = (h-12) * cos(phi);
                        int dy = (h-12) * sin(phi);
                        btmp->Canvas->Pen->Width = 2;
                        btmp->Canvas->Pen->Color = clBlack;
                        btmp->Canvas->MoveTo(w/2,h);
                        btmp->Canvas->LineTo(w/2-dx,h-dy);
                        btmp->Canvas->Pen->Width = 1;

                        btmp->Canvas->Font->Color = clGray;
//                        btmp->Canvas->Font->Style = TFontStyles()<< fsBold;
                        btmp->Canvas->Font->Name = "Arial";
                        btmp->Canvas->Font->Size = 8;
//                        btmp->Canvas->TextOutA(w-40,h-15,FloatToStrF(tA,ffFixed,8,2));
                        btmp->Canvas->TextOutA(w-45+8,0,FloatToStrF(ch_id_analog_data->analog,ffFixed,8,2));

                        MainForm->Image1->Canvas->CopyRect(r,btmp->Canvas,RectS);
                }
                else
                if (capt == "ALARM")
                {
                        //-----------------------------
                        TRect RectS;
                        btmp->Width = r.Width();
                        btmp->Height = r.Height();

                        RectS = Rect(0,0,r.Width(),r.Height());
                        //-----------------------------

                        if (MainForm->alarm_id == 0)
                        {
                                btmp->Canvas->Font->Color = clWhite;
                                btmp->Canvas->Brush->Color = clGreen;
                                btmp->Canvas->FillRect(RectS);

                                PlaySound(NULL,0,0);
                        }
                        else
                        {
                                PlaySound(MainForm->waveBuf,0,SND_MEMORY | SND_ASYNC | SND_NOSTOP);
//                                MessageBeep(MB_ICONQUESTION);

                                if (MainForm->alarm_id == 1)
                                {
                                        btmp->Canvas->Font->Color = clBlack;
                                        btmp->Canvas->Brush->Color = clYellow;
                                        btmp->Canvas->FillRect(RectS);
                                }
                                if (MainForm->alarm_id == 2)
                                {
                                        btmp->Canvas->Font->Color = clWhite;
                                        btmp->Canvas->Brush->Color = clRed;
                                        btmp->Canvas->FillRect(RectS);
                                }
                        }

                        btmp->Canvas->Font->Style = TFontStyles()<< fsBold;
                        btmp->Canvas->Font->Name = "Arial";
                        btmp->Canvas->Font->Size = 8;
                        btmp->Canvas->TextOutA(21,15,"—»√ЌјЋ»«ј÷»я");

                        MainForm->Image1->Canvas->CopyRect(r,btmp->Canvas,RectS);
                }
                else
                {
                        //--------------------------
                        TRect RectS;

                        btmp->Width = r.Width();
                        btmp->Height = r.Height();

                        RectS = Rect(0,0,r.Width(),r.Height());
                        //--------------------------

                        btmp->Canvas->Brush->Color = clWhite;
                        btmp->Canvas->FillRect(RectS);
                        btmp->Canvas->Font->Color = clBlack;
                        btmp->Canvas->Font->Style = TFontStyles()<< fsBold;
                        btmp->Canvas->Font->Name = "Arial";
                        btmp->Canvas->Font->Size = 9;

                        if (capt == "L")
                                btmp->Canvas->TextOutA(6,0,FloatToStrF((ch_id_analog_data->analog)/1000.0,ffFixed,8,2));
                        else
                                if (capt == "MH")
                                        btmp->Canvas->TextOutA(6,0,FloatToStrF(ch_id_analog_data->analog,ffFixed,8,2));
                        else
                        {
                                btmp->Canvas->TextOutA(6,0,FloatToStrF(ch_id_analog_data->analog,ffFixed,8,0));
                        }

                        MainForm->Image1->Canvas->CopyRect(r,btmp->Canvas,RectS);
                }
        }
        else
                if (vis_type == tchtCOUNTER)
                {
                };
        }
}

//---------------------------------------------------------------------------

#pragma package(smart_init)

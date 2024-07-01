//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "set_date.h"
#include <dos.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSetDateTimeForm *SetDateTimeForm;
//---------------------------------------------------------------------------
__fastcall TSetDateTimeForm::TSetDateTimeForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSetDateTimeForm::Button1Click(TObject *Sender)
{
        struct date d;
        struct time t;

        Word year,month,day;
        DecodeDate(DatePicker->Date,year,month,day);
        d.da_year = year;
        d.da_mon = month;
        d.da_day = day;

        Word hour,min,sec,msec;
        DecodeTime(TimePicker->Time,hour,min,sec,msec);
        t.ti_hour = hour;
        t.ti_hund = msec/10;
        t.ti_min = min;
        t.ti_sec = sec;

        setdate(&d);
        settime(&t);

        Close();
}
//---------------------------------------------------------------------------
void __fastcall TSetDateTimeForm::FormShow(TObject *Sender)
{
        DatePicker->Date = Date();
        TimePicker->Time = Time();
}
//---------------------------------------------------------------------------

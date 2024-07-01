//---------------------------------------------------------------------------
#ifndef vis_unitH
#define vis_unitH

#include <vcl.h>
#include "objects.cpp"

class TVisualisationChannel
{
public:
        AnsiString capt;
        TArchiveRecord* rec;
        TChannelType vis_type;

        TColor col; // цвет если ВКЛ
        TColor coloff; // цвет если ОТКЛ        

        TControl *control;
        TControl *gr_control;

        TRect r;

        int ChannelID_on;
        int ChannelID_off;
        int ChannelID_analog;

        TChannelData* ch_id_on_data;
        TChannelData* ch_id_off_data;
        TChannelData* ch_id_analog_data;

        TVisualisationChannel(TChannelType vis_type,TArchiveRecord *curr_rec);

        void Repaint();
};
//---------------------------------------------------------------------------
#endif

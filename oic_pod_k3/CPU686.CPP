//---------------------------------------------------------------------------
#pragma hdrstop

#include <conio.h>
#include <dos.h>
#include <mem.h>
#include <stdio.h>

#include "cpu686.h"
#include "main_unit.h"

#define  D_TIME	0x10 // 0x18 -100 ms; 0x10 - 14 ms ; 0x8 - 1mcs  ; 0 - 60ns

// inport - читает из порта
unsigned char inportb2(int port_id)
{
        unsigned char temp;

        asm {
           mov EDX,port_id;
           in AL,DX;
           mov temp,AL;
        }

        return temp;
}

void outportb2(int port_id,unsigned char value)
{
        asm {
           mov AL,value;
           mov EDX,port_id;
           out DX,AL;
        }
}

void outport2(int port_id,unsigned int value)
{
        asm {
           mov EAX,value;
           mov EDX,port_id;
           out DX,AX;
        }
}

// inport - читает из порта
short inport2(int port_id)
{
        int temp;

        asm {
           mov EDX,port_id;
           in AX,DX;
           mov temp,EAX;
        }

        return temp;
}

void init_UNIO()
{
	unsigned int ba,BA[12];

        // инициализация
        ba = 0x110;

	BA[0]=ba+0xA001;
	BA[3]=ba+0xA401;
	BA[6]=ba+0xA801;
	BA[9]=ba+0xAC01;
                
        if (MainForm->DISKRET->_1) outportb2(BA[0]-1,D_TIME);	  // Антидребезг 100 мс
        if (MainForm->DISKRET->_2) outportb2(BA[3]-1,D_TIME);
        if (MainForm->DISKRET->_3) outportb2(BA[6]-1,D_TIME);
        if (MainForm->DISKRET->_4) outportb2(BA[9]-1,D_TIME);

        // счетчики
        unsigned int BA1 = BA[(MainForm->UNIO_TBI->COUNTERS-1)*3]-1; // Базовый адрес для FPGA
        outport2(BA1+1,0xFFFF);	// reset Count 0..15
        outportb2(BA1+3,0xFF);  // reset Count 16..23

                        int n,timet;
                        for (int i=0; i<MainForm->ChannelList->count; i++)
                        {
                             if ((*MainForm->ChannelList)[i]->ChannelType == tchtCOUNTER)
                             {
                                n = (*MainForm->ChannelList)[i]->n_channel;
                                n /= 2;

                                unsigned bnk[]={0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,3,3};

                                outportb2(BA1,bnk[n]);	        // Анти-дребезг 60 ns
                                for (int j=0; j<30; j++) timet = j*j;
                             }
                        }
}

void init_AI()
{
        int BA_AI;
        int nn;
        int G = MainForm->G;

        BA_AI = 0x100;

        // ---- Определение G      -----
        switch (G) {
                case 0 :  nn=0; break;
                case 1 :  nn=0x5555; break;
                case 2 :  nn=0xAAAA; break;
                case 3 :  nn=0xFFFF; break;
        }

        outport2(BA_AI+6,nn);		// Коэф.усиления
        outport2(BA_AI+8,nn);
}

//---------------------------------------------------------------------------

void Clear_UNIO_Counters()
{
        unsigned int ba = 0x110,BA[12];

	BA[0]=ba+0xA001;
	BA[3]=ba+0xA401;
	BA[6]=ba+0xA801;
	BA[9]=ba+0xAC01;

        unsigned int ba1 = BA[(MainForm->UNIO_TBI->COUNTERS-1)*3]-1; // Базовый адрес для FPGA
        outport2(ba1+1,0xFFFF);
        outportb2(ba1+3,0xFF);

        Sleep(10);
}

void CPU686_WDT_on()
{
        outportb2(0x20C,1);
}

void CPU686_WDT_off()
{
        outportb2(0x20C,0);
}

#pragma package(smart_init)

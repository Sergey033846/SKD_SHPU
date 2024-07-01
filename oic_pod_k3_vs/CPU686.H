//---------------------------------------------------------------------------

#ifndef cpu686H
#define cpu686H
//---------------------------------------------------------------------------
unsigned char inportb2(int port_id);
void outportb2(int port_id,unsigned char value);
void outport2(int port_id,unsigned int value);
short inport2(int port_id);
void init_UNIO();
void init_AI();
void Clear_UNIO_Counters();
void CPU686_WDT_on();
void CPU686_WDT_off();

#endif

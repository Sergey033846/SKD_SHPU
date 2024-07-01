//---------------------------------------------------------------------------

#ifndef threadsH
#define threadsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
extern HANDLE hSem;

class TGetDataThread : public TThread
{            
private:
protected:
        void __fastcall Execute();
        void __fastcall Redraw();
        void __fastcall Update();
        //void __fastcall GetDataFromCPU686();
public:
        __fastcall TGetDataThread(bool CreateSuspended);
};

void GetDataFromCPU686();
void GetData();
void SetPrevData();
void GetProgramData();
void GetDataFromTestForm();
void GetChannelChanges();
//---------------------------------------------------------------------------
#endif

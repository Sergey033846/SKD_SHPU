//---------------------------------------------------------------------------

#ifndef sh_all_canH
#define sh_all_canH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include "objects.cpp"
//---------------------------------------------------------------------------
class TShowChannelForm : public TForm
{
__published:	// IDE-managed Components
        TStringGrid *StringGrid;
        TBitBtn *AddButton;
        TBitBtn *DelButton;
        TBitBtn *SaveButton;
        TBitBtn *CloseButton;
        void __fastcall AddButtonClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall SaveButtonClick(TObject *Sender);
        void __fastcall StringGridDblClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall DelButtonClick(TObject *Sender);
        void __fastcall CloseButtonClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TShowChannelForm(TComponent* Owner);

        void __fastcall ClearStringGrid(TObject *Sender);        
        void __fastcall RefreshRow(TObject *Sender,TChannel *ch,int rr);
        void __fastcall GetChannelParamFromForm(TObject *Sender,TChannel *ch);        
};
//---------------------------------------------------------------------------
extern PACKAGE TShowChannelForm *ShowChannelForm;
//---------------------------------------------------------------------------
#endif

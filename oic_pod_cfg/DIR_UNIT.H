//---------------------------------------------------------------------------

#ifndef dir_unitH
#define dir_unitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <FileCtrl.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TDirForm : public TForm
{
__published:	// IDE-managed Components
        TDirectoryListBox *DirectoryListBox1;
        TDriveComboBox *DriveComboBox1;
        TLabel *Label1;
        TLabel *Label2;
        TBitBtn *BitBtn1;
        TLabel *Label3;
private:	// User declarations
public:		// User declarations
        __fastcall TDirForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDirForm *DirForm;
//---------------------------------------------------------------------------
#endif

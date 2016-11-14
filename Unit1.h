//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TMainWindow : public TForm
{
__published:	// IDE-managed Components
        TButton *ButtonPreview;
        TEdit *CommandLine;
        TMainMenu *MainMenu1;
        TMenuItem *File;
        TMenuItem *Open;
        TMenuItem *View;
        TMenuItem *Preview;
        TMenuItem *N1;
        TMenuItem *Save;
        TMenuItem *SaveAs;
        TMenuItem *New;
        TMenuItem *Exit;
        TMenuItem *N2;
        TButton *ButtonGo;
        TImage *StorageView;
        TMemo *CommandLog;
        void __fastcall ButtonPreviewClick(TObject *Sender);
        void __fastcall ButtonGoClick(TObject *Sender);
        void __fastcall CommandLineKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
        __fastcall TMainWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainWindow *MainWindow;
//---------------------------------------------------------------------------
#endif

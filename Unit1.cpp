//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainWindow *MainWindow;
//---------------------------------------------------------------------------
__fastcall TMainWindow::TMainWindow(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMainWindow::ButtonPreviewClick(TObject *Sender)
{
        if (Constraints->MaxHeight == 840 && Constraints->MinHeight == 840)
        {
                Constraints->MaxHeight = 330;
                Constraints->MinHeight = 330;
                Height = 330;
                StorageView->Visible = false;
                ButtonPreview->Caption = "Poka¿ podgl¹d";
        }
        else
        {
                Constraints->MaxHeight = 840;
                Constraints->MinHeight = 840;
                Height = 840;
                StorageView->Visible = true;
                ButtonPreview->Caption = "Ukryj podgl¹d";
        }
}
//---------------------------------------------------------------------------
void __fastcall TMainWindow::ButtonGoClick(TObject *Sender)
{
        CommandLog->Lines->Add(">> " + CommandLine->Text);
        CommandLog->Lines->Add("Nie rozpoznano polecenia");
        CommandLine->Text = "";
}
//---------------------------------------------------------------------------




void __fastcall TMainWindow::CommandLineKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == VK_RETURN)
        {
                ButtonGo->Click();
        }
}
//---------------------------------------------------------------------------


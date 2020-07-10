// ---------------------------------------------------------------------------

#ifndef mainH
#define mainH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>

// ---------------------------------------------------------------------------
class TForm1 : public TForm {
__published: // IDE-managed Components
	TMainMenu *MainMenu1;
	TMenuItem *start1;
	TTimer *Timer1;
	TMenuItem *pause1;
	TTimer *Update;
	TMenuItem *info1;
	TMenuItem *Label1;
	TMenuItem *Label2;
	TMenuItem *N1;
	TMenuItem *Misia1;
	TMenuItem *N2;
	TImage *fon;
	TImage *Buffer;

	void __fastcall start1Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall pause1Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall UpdateTimer(TObject *Sender);
	void __fastcall info1Click(TObject *Sender);

private: // User declarations
public: // User declarations
	__fastcall TForm1(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
// ---------------------------------------------------------------------------
#endif

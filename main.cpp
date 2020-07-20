// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "class.h"
#include "info.h"

#include <pngimage.hpp>
#include <jpeg.hpp>
#include <ctime>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;
Game *game;  //����
TCanvas *canv;  //�������������� ������, ����� ������ ��� �������� ���� ��� ����������

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
	srand(time(NULL));

	TJPEGImage *tmpJ = new TJPEGImage();
	tmpJ->LoadFromFile("Images\\fon.jpg");
	fon->Align = alClient;
	//fon->Stretch = true;   //������ ��������
	fon->Picture->Bitmap->Assign(tmpJ);
	delete tmpJ;

	Buffer->Align = alClient;

	game = new Game(Buffer->Canvas);
	Label1->Caption = "\tTime: " + String((int)game->timeInGame);
	Label2->Caption = "Score: " + String(game->score);
	Misia1->Caption = "\tMission " + String(game->misiaNum) + ": "
		+ String(game->misia);

	canv = new TCanvas();
    canv = fon->Picture->Bitmap->Canvas;
}

// -----------������ �����-----------------------------------------------------
void __fastcall TForm1::start1Click(TObject *Sender) {
	Timer1->Enabled = true; //�������� ������
}

// -----------������-----------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender) {
	Buffer->Canvas->CopyRect(game->MyRect, canv, game->MyRect);//��������� ���� ��� ���� ����
	//���� ���� �� �� ����� �� ������ �����, ��� �������� ����
	if (game->map->proverka_first() || !game->player->isLife) {
		Timer1->Enabled = false;  //���������� ���� ���������������
		ShowMessage("You lost!\nTime: " + String((int)game->timeInGame)
		+ "\nScore: " + String(game->score)); //�������� ���������
		game->restart();  //� � ��������� �������� ������� � ������ ����
		Misia1->Caption = "\tMission " + String(game->misiaNum) + ": "
			+ String(game->misia);
	}
	else{
		game->draw();             //���� ���, ���� ������������
	}

	if (game->misia <= game->score) {
		Timer1->Enabled = false;  //���������� ���� ���������������
		ShowMessage("You win!\nTime " + String((int)game->timeInGame)
		+ "\nScore: " + String(game->score)); //�������� ���������
		game->restart();  //� � ��������� �������� ������� � ������ ����
		Misia1->Caption = "\tMission " + String(game->misiaNum) + ": "
			+ String(game->misia);
	}

	Label1->Caption = "\tTime: " + String((int)game->timeInGame);
	Label2->Caption = "Score: " + String(game->score);

	//���������� (����� �������� �� �������)
	this->Canvas->CopyRect(game->MyRect, Buffer->Canvas, game->MyRect);
	this->SetFocus();
}

// -----------������ �����-----------------------------------------------------
void __fastcall TForm1::pause1Click(TObject *Sender) {
	Timer1->Enabled = !Timer1->Enabled; //������ ��������� ������� �� ���������������
}
// -----------������ ������----------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
	TShiftState Shift)
{
	if (Key == VK_SPACE)  //���� ������, �� ���������� �-� �����
		pause1Click(Sender);
}
// -----------������ ������----------------------------------------------------
void __fastcall TForm1::FormKeyPress(TObject *Sender, System::WideChar &Key)
{
	if (Timer1->Enabled) {
		//���� '�' - �������� �����
		if ((int)Key == 97 || (int)Key ==1092) game->player->state = 0;
		//���� 'D' - �������� ������
		else if ((int)Key == 100 || (int)Key ==1074) game->player->state = 1;
		//���� 'W' � ����� �� � ������ - ������
		else if (((int)Key == 119 || (int)Key ==1094) && game->player->onGround){
			game->player->dy = -25; 			//������ ������
			game->player->onGround = false;     //��������� "� ������"
		}
	}

}
//-------------������ ��������------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
    game->player->state = 2;   //����� ����� �� �����
}
//-------------������������ ������--------------------------------------------

void __fastcall TForm1::UpdateTimer(TObject *Sender)
{
	if (Timer1->Enabled){   //���� ������ �������, ������ 33��
        //��������� ���� ��� ���� ����
		Buffer->Canvas->CopyRect(game->MyRect, canv, game->MyRect);
		game->update();    //���������� �-� ���������� ������
		//���������� (����� �������� �� �������)
		this->Canvas->CopyRect(game->MyRect, Buffer->Canvas, game->MyRect);
	}
}
//-------------������ "����"-------------------------------------------------

void __fastcall TForm1::info1Click(TObject *Sender)
{
	Timer1->Enabled = false; //�������� �����
	Form2->Show();           //� ���������� ����� � �����������
}
//---------------------------------------------------------------------------


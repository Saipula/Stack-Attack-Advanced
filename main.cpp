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
Game *game;  //Игра
TCanvas *canv;  //Дополнительный буффер, чтобы задний фон игрового поля был прозрачным

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
	srand(time(NULL));

	TJPEGImage *tmpJ = new TJPEGImage();
	tmpJ->LoadFromFile("Images\\fon.jpg");
	fon->Align = alClient;
	//fon->Stretch = true;   //Сзачие картинки
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

// -----------Кнопка Старт-----------------------------------------------------
void __fastcall TForm1::start1Click(TObject *Sender) {
	Timer1->Enabled = true; //Включает таймер
}

// -----------Таймер-----------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender) {
	Buffer->Canvas->CopyRect(game->MyRect, canv, game->MyRect);//Установка фона для поля игры
	//Если хотя бы из кубов не достиг верха, или персонаж умер
	if (game->map->proverka_first() || !game->player->isLife) {
		Timer1->Enabled = false;  //Обновление поля останавливается
		ShowMessage("You lost!\nTime: " + String((int)game->timeInGame)
		+ "\nScore: " + String(game->score)); //Вылетает сообщение
		game->restart();  //И у персонажа ставится позиция в центре поля
		Misia1->Caption = "\tMission " + String(game->misiaNum) + ": "
			+ String(game->misia);
	}
	else{
		game->draw();             //Если нет, игра продолжается
	}

	if (game->misia <= game->score) {
		Timer1->Enabled = false;  //Обновление поля останавливается
		ShowMessage("You win!\nTime " + String((int)game->timeInGame)
		+ "\nScore: " + String(game->score)); //Вылетает сообщение
		game->restart();  //И у персонажа ставится позиция в центре поля
		Misia1->Caption = "\tMission " + String(game->misiaNum) + ": "
			+ String(game->misia);
	}

	Label1->Caption = "\tTime: " + String((int)game->timeInGame);
	Label2->Caption = "Score: " + String(game->score);

	//Даблбуффер (Чтобы картинка не мерцала)
	this->Canvas->CopyRect(game->MyRect, Buffer->Canvas, game->MyRect);
	this->SetFocus();
}

// -----------Кнопка паузы-----------------------------------------------------
void __fastcall TForm1::pause1Click(TObject *Sender) {
	Timer1->Enabled = !Timer1->Enabled; //Меняет положение таймера на противоположное
}
// -----------Нажата кнопка----------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
	TShiftState Shift)
{
	if (Key == VK_SPACE)  //Если пробел, то вызивается ф-я паузы
		pause1Click(Sender);
}
// -----------Кнопка зажата----------------------------------------------------
void __fastcall TForm1::FormKeyPress(TObject *Sender, System::WideChar &Key)
{
	if (Timer1->Enabled) {
		//Если 'А' - твижение влево
		if ((int)Key == 97 || (int)Key ==1092) game->player->state = 0;
		//Если 'D' - движение вправо
		else if ((int)Key == 100 || (int)Key ==1074) game->player->state = 1;
		//Если 'W' и игрок не в прижке - прижок
		else if (((int)Key == 119 || (int)Key ==1094) && game->player->onGround){
			game->player->dy = -25; 			//Высота прижка
			game->player->onGround = false;     //Состояние "В прижке"
		}
	}

}
//-------------Кнопка отпущена------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
    game->player->state = 2;   //Игрок стоит на месте
}
//-------------Обнововление игрока--------------------------------------------

void __fastcall TForm1::UpdateTimer(TObject *Sender)
{
	if (Timer1->Enabled){   //Пока таймер включен, каждые 33мс
        //Установка фона для поля игры
		Buffer->Canvas->CopyRect(game->MyRect, canv, game->MyRect);
		game->update();    //Вызивается ф-я обновления игрока
		//Даблбуффер (Чтобы картинка не мерцала)
		this->Canvas->CopyRect(game->MyRect, Buffer->Canvas, game->MyRect);
	}
}
//-------------Кнопка "Инфо"-------------------------------------------------

void __fastcall TForm1::info1Click(TObject *Sender)
{
	Timer1->Enabled = false; //Ставится пауза
	Form2->Show();           //И вызивается форма с информацией
}
//---------------------------------------------------------------------------


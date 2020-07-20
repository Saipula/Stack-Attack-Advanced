//---------------------------------------------------------------------------

#ifndef mapH
#define mapH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>

//---------------------------------------------------------------------------
class Map {

	bool proverka1();
	bool proverka_last();
	TPicture *Cubes[6]; //Кубики

public:
	TCanvas* fild; //Поле
	int score;   //Количество очков
	const static short aH = 8, aW = 12; //Размер карты
	int arr[aW][aH]; //Массив карты
	TPoint *start;  //Начальные координаты
	int w, h;   //Размер кубиков
	void draw();

	Map(TCanvas* fild);
	void update();
	void clear();
	bool proverka_first();
};

#endif

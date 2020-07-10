// ---------------------------------------------------------------------------

#ifndef classH
#define classH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <pngimage.hpp>
#include "map.h"
// ---------------------------------------------------------------------------

class Player {
	TCanvas* fild; //Поле на котором рисуется игра
	TPoint *start; //Левый верхний угол легого верхнего угла(Координаты начала отрисовки)
	Map *map;  //Карта
	int curFrame; //Номер отображаемой картинки
	TPicture *Left1[12], *Right[12], *State; //Наборы картинок персонажа

public:
	bool onGround, isLife; //На земле ли, живой ли
	enum { left,right, stay} state;//добавляем тип перечисления - состояние объекта
	float x, y, dx, dy;
	short w, h, speed; //Ширина, высота, сеорость движения
	Player(Map *map);  //Конструктор
	void update();
	void checkCollisionWithMap(float Dx, float Dy);
	void restart();
	void draw();
};

class Game {
public:
	TRect MyRect; //Прямоугольник с учётом красных кубиков
	Map *map;  //Карта
	Player *player; //Игрок
	float timeInGame;  //Время в игре
	int score, misiaNum, misia;  //Очки, номер миссии, сколько нужно для выполнения миссии

	Game(TCanvas* fild);
	void update();
	void draw();
    void restart();
};

#endif

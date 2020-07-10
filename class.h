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
	TCanvas* fild; //���� �� ������� �������� ����
	TPoint *start; //����� ������� ���� ������ �������� ����(���������� ������ ���������)
	Map *map;  //�����
	int curFrame; //����� ������������ ��������
	TPicture *Left1[12], *Right[12], *State; //������ �������� ���������

public:
	bool onGround, isLife; //�� ����� ��, ����� ��
	enum { left,right, stay} state;//��������� ��� ������������ - ��������� �������
	float x, y, dx, dy;
	short w, h, speed; //������, ������, �������� ��������
	Player(Map *map);  //�����������
	void update();
	void checkCollisionWithMap(float Dx, float Dy);
	void restart();
	void draw();
};

class Game {
public:
	TRect MyRect; //������������� � ������ ������� �������
	Map *map;  //�����
	Player *player; //�����
	float timeInGame;  //����� � ����
	int score, misiaNum, misia;  //����, ����� ������, ������� ����� ��� ���������� ������

	Game(TCanvas* fild);
	void update();
	void draw();
    void restart();
};

#endif

// ---------------------------------------------------------------------------

#pragma hdrstop

#include "class.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

//�����������
Player::Player(Map *map) {
	w = 48; h = w; //������ � ������ ���������
	this->map = map; //����
	this->fild = map->fild; //����� �� ������� ��������
	this->start = map->start; //��������� ���������� ��������� ���� ����
	dx = 0; dy = 0; speed = 16; //�������� ����������� speed �� x � �
	onGround = false;  //�� ����� �� ��������
	curFrame = 0;

//--------------------------------------------------------------------------
	TPngImage *temp;
	temp = new TPngImage();

	for (int i = 0; i < 12; i++) {
		temp->LoadFromFile("Images\\left_" + String(i+1) + ".png");
		Left1[i] = new TPicture();
		Left1[i]->Bitmap->Assign(temp);
		Left1[i]->Bitmap->Transparent = 1;
		Left1[i]->Bitmap->TransparentMode = tmAuto;

		temp->LoadFromFile("Images\\right_" + String(i+1) + ".png");
		Right[i] = new TPicture();
		Right[i]->Bitmap->Assign(temp);
		Right[i]->Bitmap->Transparent = 1;
		Right[i]->Bitmap->TransparentMode = tmAuto;
	}

	temp->LoadFromFile("Images\\state.png");
	State = new TPicture();
	State->Bitmap->Assign(temp);
	State->Bitmap->Transparent = 1;
	State->Bitmap->TransparentMode = tmAuto;

	delete temp;
//---------------------------------------------------------------------------

	restart();
}

//��������� ���������
void Player::draw() {
	switch (state)//��� �������� ��������� �������� � ����������� �� ���������
	{
		case right:
			fild->Draw(x, y, Right[curFrame]->Graphic);
		break;//��������� ���� ������
		case left:
			fild->Draw(x, y, Left1[curFrame]->Graphic);
		break;//��������� ���� �����
		case stay:
			fild->Draw(x, y, State->Graphic);
		break;//� ����� ����
	}
}

//�������� ���������
void Player::update(){
	switch (state)//��� �������� ��������� �������� � ����������� �� ���������
	{
		case right:
			if (curFrame < 11)
				curFrame++;
			else
				curFrame = 0;
			dx = speed;
			break;//��������� ���� ������
		case left:
			if (curFrame < 11)
				curFrame++;
			else
				curFrame = 0;
			dx = -speed;
		break;//��������� ���� �����
		case stay:
			curFrame = 0;
			dx = 0;
		break;//� ����� ����
	}

	x += dx;
	checkCollisionWithMap(dx, 0);//������������ ������������ �� �
	dy += 4;//��������� ������������� � �����
	y += dy;
	checkCollisionWithMap(0, dy);//������������ ������������ �� Y

	draw();
}

//�������� �� ������������ � �����
void Player::checkCollisionWithMap(float Dx, float Dy){
	for (int i = (y - start->y) / map->h; i < ((y - start->y) + h) / map->h; i++)//���������� �� ��������� �����
	for (int j = (x - start->x) / map->w; j < ((x - start->x) + w) / map->w; j++)
	{
		if (map->arr[j][i] != 0)//���� ������� �� ������? ��
		{
			if (Dy>0){y = start->y + (i * map->h - map->h); dy = 0; onGround = true; }//�� Y ����=>���� � ���(����� �� �����) ��� ������. � ���� ������ ���� ���������� ��������� � ��������� ��� �� �����, ��� ���� ������� ��� �� �� ����� ��� ����� ����� ����� �������
			if (Dy<0){if(!onGround)y = start->y + (i * map->h + map->h); isLife = 0;  dy = 0;}//������������ � �������� ������ ����
			if (Dx>0){
				if (map->arr[j+1][i] == 0 && j != map->aW-1 && map->arr[j][i-1] == 0)
					std::swap(map->arr[j][i], map->arr[j+1][i]);
				else
					x = start->x + (j * map->w - map->w);
			}//� ������ ����� ����
			if (Dx<0){
				if (map->arr[j-1][i] == 0 && j != 0 && map->arr[j][i-1] == 0)
					std::swap(map->arr[j][i], map->arr[j-1][i]);
				else
					x = start->x + (j * map->w + map->w);
			}// � ����� ����� ����
		} else {onGround=false;}
	}
}

//��� ������ �������/������ ������ ��������� � �������� �����
void Player::restart(){
	isLife = 1;
	this->x = map->start->x + map->aW/2 * map->w;
	this->y = map->start->y + (map->aH-2) * map->h;
	state = 2;
}

// �����������
Game::Game(TCanvas* fild) {
	map = new Map(fild);
	player = new Player(map);
	timeInGame = 0;
	score = 0;
	misiaNum = 1;
	misia = 10;

	MyRect.Left = map->start->x;
	MyRect.Top = map->start->y;
	MyRect.Right = map->start->x + map->aW * map->w;
	MyRect.Bottom = map->start->y + map->aH * map->h;
}

//����� �����������, ����� ��������
void Game::draw(){
	map->update(); //����� �������� ���
	player->checkCollisionWithMap(0, -0.1);  //�������� �� "���������" �� �����
	player->draw();  //��������� ������
    timeInGame += 0.25;
	score = map->score;
}

//����� ���������, ����� ��������
void Game::update(){
	map->draw();   //����� ��������
	player->update();  //���������� ��������� ������
}

//������� (��� ���������/������)
void Game::restart(){
	timeInGame = 0;
	score = 0;
	player->restart();
	map->clear();       //����� ��������
	misia *= 2;
    misiaNum++;
}


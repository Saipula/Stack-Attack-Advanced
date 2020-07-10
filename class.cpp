// ---------------------------------------------------------------------------

#pragma hdrstop

#include "class.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

// онструктор
Player::Player(Map *map) {
	w = 48; h = w; //Ўирина и высота персонажа
	this->map = map; // ата
	this->fild = map->fild; // анва на которой рисовать
	this->start = map->start; //—тартовые координаты отрисовки пол€ игры
	dx = 0; dy = 0; speed = 16; //—корость перемещени€ speed по x и у
	onGround = false;  //Ќа земле ли персонаж
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

//ќтрисовка персонажа
void Player::draw() {
	switch (state)//тут делаютс€ различные действи€ в зависимости от состо€ни€
	{
		case right:
			fild->Draw(x, y, Right[curFrame]->Graphic);
		break;//состо€ние идти вправо
		case left:
			fild->Draw(x, y, Left1[curFrame]->Graphic);
		break;//состо€ние идти влево
		case stay:
			fild->Draw(x, y, State->Graphic);
		break;//и здесь тоже
	}
}

//ƒвижение персонажа
void Player::update(){
	switch (state)//тут делаютс€ различные действи€ в зависимости от состо€ни€
	{
		case right:
			if (curFrame < 11)
				curFrame++;
			else
				curFrame = 0;
			dx = speed;
			break;//состо€ние идти вправо
		case left:
			if (curFrame < 11)
				curFrame++;
			else
				curFrame = 0;
			dx = -speed;
		break;//состо€ние идти влево
		case stay:
			curFrame = 0;
			dx = 0;
		break;//и здесь тоже
	}

	x += dx;
	checkCollisionWithMap(dx, 0);//обрабатываем столкновение по ’
	dy += 4;//посто€нно прит€гиваемс€ к земле
	y += dy;
	checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y

	draw();
}

//ѕроверка на столкновение с кубом
void Player::checkCollisionWithMap(float Dx, float Dy){
	for (int i = (y - start->y) / map->h; i < ((y - start->y) + h) / map->h; i++)//проходимс€ по элементам карты
	for (int j = (x - start->x) / map->w; j < ((x - start->x) + w) / map->w; j++)
	{
		if (map->arr[j][i] != 0)//если элемент не пусьлй? то
		{
			if (Dy>0){y = start->y + (i * map->h - map->h); dy = 0; onGround = true; }//по Y вниз=>идем в пол(стоим на месте) или падаем. ¬ этот момент надо вытолкнуть персонажа и поставить его на землю, при этом говорим что мы на земле тем самым снова можем прыгать
			if (Dy<0){if(!onGround)y = start->y + (i * map->h + map->h); isLife = 0;  dy = 0;}//столкновение с верхними кра€ми куба
			if (Dx>0){
				if (map->arr[j+1][i] == 0 && j != map->aW-1 && map->arr[j][i-1] == 0)
					std::swap(map->arr[j][i], map->arr[j+1][i]);
				else
					x = start->x + (j * map->w - map->w);
			}//с правым краем куба
			if (Dx<0){
				if (map->arr[j-1][i] == 0 && j != 0 && map->arr[j][i-1] == 0)
					std::swap(map->arr[j][i], map->arr[j-1][i]);
				else
					x = start->x + (j * map->w + map->w);
			}// с левым краем куба
		} else {onGround=false;}
	}
}

//ѕри первом запуске/смерти ставит положение в стредине карты
void Player::restart(){
	isLife = 1;
	this->x = map->start->x + map->aW/2 * map->w;
	this->y = map->start->y + (map->aH-2) * map->h;
	state = 2;
}

//  онструктор
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

// арта обновл€етс€, игрок рисуетс€
void Game::draw(){
	map->update(); //карта здвигает куб
	player->checkCollisionWithMap(0, -0.1);  //ѕроверка не "придавило" ли кубом
	player->draw();  //ќтрисовка игрока
    timeInGame += 0.25;
	score = map->score;
}

//»грак двигаетс€, карта рисуетс€
void Game::update(){
	map->draw();   // арта рисуетс€
	player->update();  //ќбновление положени€ игрока
}

//ќчистка (ѕри проигрише/победе)
void Game::restart(){
	timeInGame = 0;
	score = 0;
	player->restart();
	map->clear();       // арта чиститс€
	misia *= 2;
    misiaNum++;
}


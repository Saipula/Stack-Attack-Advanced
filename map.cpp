//---------------------------------------------------------------------------

#pragma hdrstop

#include "map.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//Конструктор
Map::Map(TCanvas* fild){
	w = 48; h = w;  //Ширина и высота кубиков
	start = new TPoint(100, 50);  //Стартовые координаты отрисовки
	score = 0;
	this->fild = fild;

    for (int i = 0; i < 6; i++) {   //Загрузка кубиков
		Cubes[i] = new TPicture();
		Cubes[i]->LoadFromFile("Images\\Cube" + String(i+1) +".png");
	}

	clear();
}

// Перерисовка поля
// В зависимости от числа в массиве ставится такой цвет куба
void Map::draw() {
	fild->Pen->Color = clBlack;  //Цвет сетки
	fild->Pen->Width = 2;     //Размер метки

	for (int i = 0; i < aW; i++)
		for (int j = 0; j < aH; j++) {
			TPoint tmp(start->x + i*w, start->y + j*h);

			if (arr[i][j] == 0){  //Рисование сетки
				fild->MoveTo(start->x + i*w, start->y + j*h);
				fild->LineTo(start->x + i*w + w, start->y + j*h);
				fild->LineTo(start->x + i*w + w, start->y + j*h + h);
				fild->LineTo(start->x + i*w, start->y + j*h + h);
				fild->LineTo(start->x + i*w, start->y + j*h);
			}
			else if (arr[i][j] == 1)
				fild->Draw(tmp.x, tmp.y, Cubes[5]->Graphic);
			else if (arr[i][j] == 2)
				fild->Draw(tmp.x, tmp.y, Cubes[3]->Graphic);
			else if (arr[i][j] == 3)
				fild->Draw(tmp.x, tmp.y, Cubes[1]->Graphic);
			else if (arr[i][j] == 4)
				fild->Draw(tmp.x, tmp.y, Cubes[0]->Graphic);
			else if (arr[i][j] == 5)
				fild->Draw(tmp.x, tmp.y, Cubes[4]->Graphic);
			else if (arr[i][j] == -1)
				fild->Draw(tmp.x, tmp.y, Cubes[2]->Graphic);
		}


}

// Обновление
void Map::update() {
	if (proverka_last()){ //Если последний ряд полон, он очищается
		for (int i = 1; i < aW-1; i++) {
			int dop_score = 1;

			if (arr[i][aH - 2] == arr[i+1][aH - 2] && i+1 != aW-1)
				dop_score = (dop_score + 1) * 2;

			arr[i][aH - 2] = 0;

			score += dop_score;
		}
	}

	//Если есть "висящие" элементы, они сдвигуются вниз
	if (proverka1()) {
		for (int i = aW - 2; i >= 1; i--)
			for (int j = aH - 3; j >= 0; j--)
				if (arr[i][j] != 0 && arr[i][j + 1] == 0)
					std::swap(arr[i][j], arr[i][j + 1]);
	}
	//Если нету, создаётся новый
	else {
		int tmp = (rand() % (aW-2))+1;
		arr[tmp][0] = (rand() % 5) + 1;
	}

	draw();
}

// Проверка достижения всех элементов дна поля
bool Map::proverka1() {
	for (int i = 1; i < aW-1; i++)
		for (int j = 0; j < aH - 2; j++)
			if (arr[i][j] != 0 && arr[i][j + 1] == 0)
				return true;

	return false;
}

// Проверка последнего ряда
bool Map::proverka_last() {
	for (int i = 1; i < aW-1; i++) {
		if (arr[i][aH - 2])
			continue;
		else
			return false;
	}
	return true;
}

// Очистка поля при проиграше или при создании элемента класса
void Map::clear() {
	for (int i = 0; i < aW; i++)
		for (int j = 0; j < aH; j++)
			if (i == 0 || i == aW-1 || j == aH-1)
				arr[i][j] = -1;
			else
				arr[i][j] = 0;

	draw();
}

//Проверка, достиг ли куб верхнего рядя
bool Map::proverka_first() {
	for (int i = 1; i < aW-1; i++)
		if (arr[i][0] != 0 && arr[i][1] != 0)
			return true;

	return false;
}

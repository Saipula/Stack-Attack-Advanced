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
	TPicture *Cubes[6]; //������

public:
	TCanvas* fild; //����
	int score;   //���������� �����
	const static short aH = 8, aW = 12; //������ �����
	int arr[aW][aH]; //������ �����
	TPoint *start;  //��������� ����������
	int w, h;   //������ �������
	void draw();

	Map(TCanvas* fild);
	void update();
	void clear();
	bool proverka_first();
};

#endif

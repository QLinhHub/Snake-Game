#include <iostream>
#include "Console.h"
#include <string>

using namespace std;

#define MAX 100
int dots = 5;
int mark = 0;
string name[20];
int score[20];
int s = 0;
string mode[20];
bool save = false;

void above_wall();
void below_wall();
void right_wall();
void left_wall();
void wall();

void paint_snake(int[], int[]);
void coord_snake(int[], int[]);

void add_snake(int[], int);
void delete_snake(int[], int);
void replace_snake(int[], int[], int, int);

void delete_old_snake(int[], int[]);

bool check_gameover_by_wall(int, int);
bool check_gameover_by_suicide(int[] , int[]);
bool check_gameover(int[], int[]);

void make_bait(int&, int&, int[], int[]);
void replace_snake_with_bait(int[], int[], int, int);

void mode_easy(int, int, int[], int[], bool, int&, int&);
void mode_normal(int, int, int[], int[], bool, int&, int&);
void mode_hard(int, int, int[], int[], bool, int&, int&);

int main()
{	
	int dem = 0;
	int coordx[MAX], coordy[MAX];
	bool gameOver = false;
	int xbait = 0, ybait = 0;

	resizeConsole(1400, 600);

	int xline = 77, yline = 43;
	bool exit = false;

	ShowCur(false);
	PlaySound(L"nhinvaomua.wav", NULL, SND_ASYNC);
	wall();
	while (!exit)
	{
		ShowCur(false);
		dots = 5;
		mark = 0;
		wall();
		gotoXY(90, 43);
		cout << "SNAKE GAME";
		gotoXY(80, 45);
		cout << "1	Easy";
		gotoXY(80, 47);
		cout << "2	Normal";
		gotoXY(80, 49);
		cout << "3	Hard";
		gotoXY(80, 51);
		cout << "4	Score";
		gotoXY(80, 53);
		cout << "5	Quit";

		if (_kbhit()) {
			char ctrl = _getch();
			if (ctrl == -32) {
				ctrl = _getch();
				if (ctrl == 72 && yline > 45) {// go up
					gotoXY(xline, yline);
					cout << "   ";
					yline -= 2;
					gotoXY(xline, yline);
					cout << "-->";
				}
				else if (ctrl == 80 && yline < 53) {// go down
					gotoXY(xline, yline);
					cout << "   ";
					yline += 2;
					gotoXY(xline, yline);
					cout << "-->";
				}
			}
			else if (ctrl == 13) {
				if (yline == 45) {
					PlaySound(L"nhinvaomua.wav", NULL, SND_ASYNC);
					system("cls");
					ShowCur(false);
					mode_easy(xbait, ybait, coordx, coordy, gameOver, mark, dem);
					mark = 0;
					
				}
				else if (yline == 47) {
					PlaySound(L"nhinvaomua.wav", NULL, SND_ASYNC);
					system("cls");
					ShowCur(false);
					mode_normal(xbait, ybait, coordx, coordy, gameOver, mark, dem);
					mark = 0;
					
				}
				else if (yline == 49) {
					PlaySound(L"nhinvaomua.wav", NULL, SND_ASYNC);
					system("cls");
					ShowCur(false);
					mode_hard(xbait, ybait, coordx, coordy, gameOver, mark, dem);
					mark = 0;
					
				}
				else if (yline == 51) {
					PlaySound(L"nhinvaomua.wav", NULL, SND_ASYNC);
					system("cls");
					for (int i = 0, k = 23; i < dem; i++, k++) {
							gotoXY(80, k);
							cout << name[i] << " : " << score[i] << " in mode " << mode[i];
					}
					_getch();
					system("cls");
				}
				else if (yline == 53)
					break;
			}
			else if (ctrl == 27) {
				exit = true;
			}
		}
	}

	return 0;
}

void above_wall() {
	int x = 50, y = 41, color = 1;
	while (x < 140) {
		gotoXY(x, y);
		SetColor(color);
		if (color > 15)
			color = 1;
		cout << "o";
		x++;
		color++;
	}
	gotoXY(50, 35);
	cout << "MARK: 0 ";
}

void below_wall() {
	int x = 50, y = 66, color = 1;
	while (x < 140) {
		gotoXY(x, y);
		SetColor(color);
		if (color > 15)
			color = 1;
		cout << "o";
		x++;
		color++;
	}
}

void right_wall() {
	int x = 140, y = 41, color = 1;
	while (y < 67) {
		gotoXY(x, y);
		SetColor(color);
		if (color > 15)
			color = 1;
		cout << "o";
		y++;
		color++;
	}
}

void left_wall() {
	int x = 50, y = 41, color = 1;
	while (y < 67) {
		gotoXY(x, y);
		SetColor(color);
		if (color > 15)
			color = 1;
		cout << "o";
		y++;
		color++;
	}
}

void wall() {
	above_wall();
	below_wall();
	right_wall();
	left_wall();
}

void paint_snake(int coordx[], int coordy[])
{
	for (int i = 0; i < dots; i++) {

		gotoXY(coordx[i], coordy[i]);

		/*static int color = 1;
		SetColor(color);
		if (color > 15)
			color = 1;
		color++;*/

		if (i == 0) 
			cout << "O";
		else
			cout << "o";
	}
}

void coord_snake(int coordx[], int coordy[])
{
	int x = 90, y = 53;
	for (int i = 0; i < dots; i++) {
		coordx[i] = x;
		coordy[i] = y;
		x--;
	}
}

void add_coord(int coord[], int c)
{
	for (int i = dots; i > 0; i--)
		coord[i] = coord[i - 1];
	coord[0] = c;
	dots++;
}

void delete_coord(int coord[], int index)
{
	for (int i = index; i < dots; i++)
		coord[i] = coord[i + 1];
	dots--;
}

void replace_snake(int coordx[], int coordy[], int x, int y)
{
	add_coord(coordx, x);
	add_coord(coordy, y);

	delete_coord(coordx, dots - 1);
	delete_coord(coordy, dots - 1);

	paint_snake(coordx, coordy);
}

void delete_old_snake(int crdx[], int crdy[])
{
	for (int i = 0; i < dots; i++) {
		gotoXY(crdx[i], crdy[i]);
		cout << " ";
	}
}

bool check_gameover_by_wall(int x, int y)
{
	// above wall
	if (y == 41)
		return true;
	else if (y == 66)
		return true;
	else if (x == 50)
		return true;
	else if (x == 140)
		return true;
	return false;
}

bool check_gameover_by_suicide(int crdx[], int crdy[])
{
	for (int i = 2; i < dots; i++) {
		if (crdx[i] == crdx[0] && crdy[i] == crdy[0])
			return true;
	}
	return false;
}

bool check_gameover(int crdx[], int crdy[])
{	
	if (crdx[0] == 50 || crdx[0] == 140 || crdy[0] == 41 || crdy[0] == 66)
		return check_gameover_by_wall(crdx[0], crdy[0]);
	else
		return check_gameover_by_suicide(crdx, crdy);
}

void make_bait(int &xbait, int &ybait, int crdx[], int crdy[])
{
	// 10 < xbait < 100
	xbait = rand() % (139 - 51 + 1) + 51;
	// 1 < ybait < 26
	ybait = rand() % (65 - 42 + 1) + 42;
	
	for (int i = 0; i < dots; i++) {
		if (xbait == crdx[i] && ybait == crdy[i]) {
			xbait = rand() % (139 - 51 + 1) + 51;
			ybait = rand() % (65 - 42 + 1) + 42;
		}

	}

	gotoXY(xbait, ybait);
	cout << "*";
}

void replace_snake_with_bait(int coordx[], int coordy[], int x, int y)
{
	add_coord(coordx, x);
	add_coord(coordy, y);

	paint_snake(coordx, coordy);
	//cout << "\a";
}

void mode_easy(int xbait, int ybait, int coordx[], int coordy[], bool gameOver, int& mark, int& dem)
{
	int x = 90, y = 53; // first position of snake
	int check = 2;      // snake move horizontally at beginning
	//system("cls");
	wall();
	srand(time(NULL));
	make_bait(xbait, ybait, coordx, coordy);
	coord_snake(coordx, coordy);
	paint_snake(coordx, coordy);

	while (gameOver == false) {
		//delete_old_snake(coordx, coordy);

		// controle
		if (_kbhit()) {
			char ctrl = _getch();
			if (ctrl == -32) {
				ctrl = _getch();
				if (ctrl == 72 && check != 0) // go up
					check = 1;
				else if (ctrl == 80 && check != 1) // go down
					check = 0;
				else if (ctrl == 77 && check != 3) // turn right
					check = 2;
				else if (ctrl == 75 && check != 2) // turn left
					check = 3;
			}
			else if (ctrl == 32) {
				_getch();
			}
		}

		delete_old_snake(coordx, coordy);
		// move

		if (check == 0)
			y++;   // go down
		else if (check == 1)
			y--;	// go up
		else if (check == 2)
			x++;	// turn right
		else if (check == 3)
			x--;	// turn left

		if (xbait == coordx[0] && ybait == coordy[0]) {
			replace_snake_with_bait(coordx, coordy, xbait, ybait);
			make_bait(xbait, ybait, coordx, coordy);
			gotoXY(56, 35);
			cout << ++mark;
		}
		else
			replace_snake(coordx, coordy, x, y);

		gameOver = check_gameover(coordx, coordy);

		Sleep(130);
	}
	gameOver = false;
	gotoXY(90, 35);
	cout << "GAME OVER";
	//PlaySound(L"STDIO_SOUND_LOGO.wav", NULL, SND_FILENAME);
	cout << "\a";
	system("cls"); 
	gotoXY(90, 23);
	cout << "Your score: " << mark;
	_getch();

	int xs = 90, ys = 28;
	bool enter = false;
	gotoXY(90, 25);
	cout << "Save score?";
	gotoXY(90, 27);
	cout << "Yes";
	gotoXY(95, 27);
	cout << "No";
	gotoXY(90, 28);
	cout << (char)1;
	while (!enter)
	{
		if (_kbhit()) {
			char ctrl = _getch();
			if (ctrl == -32) {
				ctrl = _getch();
				if (ctrl == 77 && xs < 95) {// go right
					gotoXY(xs, ys);
					cout << " ";
					xs += 5;
					gotoXY(xs, ys);
					cout << (char)1;
				}
				else if (ctrl == 75 && xs > 90) {// go left
					gotoXY(xs, ys);
					cout << " ";
					xs -= 5;
					gotoXY(xs, ys);
					cout << (char)1;
				}
			}
			else if (ctrl == 13) {
				if (xs == 90) {
					system("cls");
					gotoXY(90, 23);
					cout << "Your name?" << endl;
					gotoXY(90, 25);
					getline(cin, name[s]);
					score[s] = mark;
					mode[s] = "EASY";
					s++;
					enter = true;
					dem++;
				}
				else
					enter = true;
			}
		}
	}
}

void mode_normal(int xbait, int ybait, int coordx[], int coordy[], bool gameOver, int& mark, int& dem)
{
	int x = 90, y = 53; // first position of snake
	int check = 2;      // snake move horizontally at beginning
	//system("cls");
	wall();
	srand(time(NULL));
	make_bait(xbait, ybait, coordx, coordy);
	coord_snake(coordx, coordy);
	paint_snake(coordx, coordy);

	while (gameOver == false) {
		//delete_old_snake(coordx, coordy);

		// controle
		if (_kbhit()) {
			char ctrl = _getch();
			if (ctrl == -32) {
				ctrl = _getch();
				if (ctrl == 72 && check != 0) // go up
					check = 1;
				else if (ctrl == 80 && check != 1) // go down
					check = 0;
				else if (ctrl == 77 && check != 3) // turn right
					check = 2;
				else if (ctrl == 75 && check != 2) // turn left
					check = 3;
			}
			else if (ctrl == 32) {
				_getch();
			}
		}

		delete_old_snake(coordx, coordy);
		// move

		if (check == 0)
			y++;   // go down
		else if (check == 1)
			y--;	// go up
		else if (check == 2)
			x++;	// turn right
		else if (check == 3)
			x--;	// turn left

		if (xbait == coordx[0] && ybait == coordy[0]) {
			replace_snake_with_bait(coordx, coordy, xbait, ybait);
			make_bait(xbait, ybait, coordx, coordy);
			gotoXY(56, 35);
			cout << ++mark;
		}
		else
			replace_snake(coordx, coordy, x, y);

		gameOver = check_gameover(coordx, coordy);

		Sleep(100);
	}
	gameOver = false;
	gotoXY(90, 35);
	cout << "GAME OVER";
	//PlaySound(L"STDIO_SOUND_LOGO.wav", NULL, SND_FILENAME);
	cout << "\a";
	system("cls");
	gotoXY(90, 23);
	cout << "Your score: " << mark;
	_getch();

	int xs = 90, ys = 28;
	bool enter = false;
	gotoXY(90, 25);
	cout << "Save score?";
	gotoXY(90, 27);
	cout << "Yes";
	gotoXY(95, 27);
	cout << "No";
	gotoXY(90, 28);
	cout << (char)1;
	while (!enter)
	{
		if (_kbhit()) {
			char ctrl = _getch();
			if (ctrl == -32) {
				ctrl = _getch();
				if (ctrl == 77 && xs < 95) {// go right
					gotoXY(xs, ys);
					cout << " ";
					xs += 5;
					gotoXY(xs, ys);
					cout << (char)1;
				}
				else if (ctrl == 75 && xs > 90) {// go left
					gotoXY(xs, ys);
					cout << " ";
					xs -= 5;
					gotoXY(xs, ys);
					cout << (char)1;
				}
			}
			else if (ctrl == 13) {
				if (xs == 90) {
					system("cls");
					gotoXY(90, 23);
					cout << "Your name?" << endl;
					gotoXY(90, 25);
					getline(cin, name[s]);
					score[s] = mark;
					mode[s] = "NORMAL";
					s++;
					enter = true;
					dem++;
				}
				else
					enter = true;
			}
		}
	}
}

void mode_hard(int xbait, int ybait, int coordx[], int coordy[], bool gameOver, int& mark, int& dem)
{
	int x = 90, y = 53; // first position of snake
	int check = 2;      // snake move horizontally at beginning
	//system("cls");
	wall();
	srand(time(NULL));
	make_bait(xbait, ybait, coordx, coordy);
	coord_snake(coordx, coordy);
	paint_snake(coordx, coordy);

	while (gameOver == false) {
		//delete_old_snake(coordx, coordy);

		// controle
		if (_kbhit()) {
			char ctrl = _getch();
			if (ctrl == -32) {
				ctrl = _getch();
				if (ctrl == 72 && check != 0) // go up
					check = 1;
				else if (ctrl == 80 && check != 1) // go down
					check = 0;
				else if (ctrl == 77 && check != 3) // turn right
					check = 2;
				else if (ctrl == 75 && check != 2) // turn left
					check = 3;
			}
			else if (ctrl == 32) {
				_getch();
			}
		}

		delete_old_snake(coordx, coordy);
		// move

		if (check == 0)
			y++;   // go down
		else if (check == 1)
			y--;	// go up
		else if (check == 2)
			x++;	// turn right
		else if (check == 3)
			x--;	// turn left

		if (xbait == coordx[0] && ybait == coordy[0]) {
			replace_snake_with_bait(coordx, coordy, xbait, ybait);
			make_bait(xbait, ybait, coordx, coordy);
			gotoXY(56, 35);
			cout << ++mark;
		}
		else
			replace_snake(coordx, coordy, x, y);

		gameOver = check_gameover(coordx, coordy);

		Sleep(50);
	}
	gameOver = false;
	gotoXY(90, 35);
	cout << "GAME OVER";
	//PlaySound(L"STDIO_SOUND_LOGO.wav", NULL, SND_FILENAME);
	cout << "\a";
	system("cls");
	gotoXY(90, 23);
	cout << "Your score: " << mark;
	_getch();

	int xs = 90, ys = 28;
	bool enter = false;
	gotoXY(90, 25);
	cout << "Save score?";
	gotoXY(90, 27);
	cout << "Yes";
	gotoXY(95, 27);
	cout << "No";
	gotoXY(90, 28);
	cout << (char)1;
	while (!enter)
	{	
		if (_kbhit()) {
			char ctrl = _getch();
			if (ctrl == -32) {
				ctrl = _getch();
				if (ctrl == 77 && xs < 95) {// go right
					gotoXY(xs, ys);
					cout << " ";
					xs += 5;
					gotoXY(xs, ys);
					cout << (char)1;
				}
				else if (ctrl == 75 && xs > 90) {// go left
					gotoXY(xs, ys);
					cout << " ";
					xs -= 5;
					gotoXY(xs, ys);
					cout << (char)1;
				}
			}
			else if (ctrl == 13) {
				if (xs == 90) {
					system("cls");
					gotoXY(90, 23);
					cout << "Your name?" << endl;
					gotoXY(90, 25);
					getline(cin, name[s]);
					score[s] = mark;
					mode[s] = "HARD";
					s++;
					enter = true;
					dem++;
				}
				else {
					enter = true;
				}
			}
		}
	}
	system("cls");
}
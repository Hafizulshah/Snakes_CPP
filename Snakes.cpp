#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

using namespace std;

bool gameOver;
const int height = 20;
const int width = 40;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100], nTail;
char snake = 'o';
char fruit = 'M';

enum eDirection{
	STOP = 0, UP, DOWN, LEFT, RIGHT
};
eDirection dir;

void Setup(){
	gameOver = false;
	dir = STOP;
	x = width/2;
	y = height/2;
	fruitX = rand() % width;
	fruitY = rand() % height;
}

void Draw(){
	system("CLS");
	
	for (int i = 0; i < width; i++){
		cout << "#";
	}
	cout << endl;
	
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			if (j == 0 || j == width - 1){
				cout << "#";
			}
			else if (i == y && j == x){
				cout << snake;
			}
			else if (i == fruitY && j == fruitX){
				cout << fruit;
			}
			else {
				bool print = false;
				
				for(int k = 0; k < nTail; k++){
					if (i == tailY[k] && j == tailX[k]){
						cout << snake;
						print = true;
					}
				}
				if (!print){
					cout << " ";
				}
			}
		}
		cout << endl;
	}
	
	for (int i = 0; i < width; i++){
		cout << "#";
	}
	cout << endl << endl;
	
	cout <<  "Score : " << score << endl;
}

void Input(){
	if (_kbhit()){
		switch(_getch()){
			case 'w' :
				dir = UP;
				break;
			case 'a' :
				dir = LEFT;
				break;
			case 's' :
				dir = DOWN;
				break;
			case 'd' :
				dir = RIGHT;
				break;
			default :
				break;
		}
	}
}

void Logic(){
	int prevX = tailX[0];
	int prevY = tailY[0];
	
	tailX[0] = x;
	tailY[0] = y;
	
	int prev2X, prev2Y;
	
	for (int i = 1; i < nTail; i++){
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	
	switch(dir){
		case UP :
			y--;
			break;
		case DOWN :
			y++;
			break;
		case LEFT :
			x--;
			break;
		case RIGHT :
			x++;
			break;
		default :
			break;
	}
	
	if (x < 1 || x > width-2 || y < 0 || y > height-1){
		gameOver = true;
	}
	
	for (int i = 0; i < nTail; i++){
		if (x == tailX[i] && y == tailY[i]){
			gameOver = true;
		}
	}
	
	if (x == fruitX && y == fruitY){
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}

bool menu(){
	char opt = '2';
	bool repeat = true;
	
	choice:
	while (repeat){
		cout << "SNAKES\n" << endl;
		cout << "1. Start" << endl;
		cout << "2. Set skins" << endl;
		cout << "3. Exit\n" << endl;
		
		cout << "Enter choice : ";
		cin >> opt;
		system("CLS");
		
		if (opt == '1'){
			repeat = false;
			return true;
		}
		else if (opt == '2'){
			cout << "Edit skin\n" << endl;
			cout << "Enter snake's skin" << endl;
			cin >> snake;
			cout << "Enter fruit's skin" << endl;
			cin >> fruit;
			
			cout << "\nSkin Updated!";
			_kbhit();
			system("CLS");
			goto choice;
		}
		else if (opt == '3'){
			repeat = false;
			system("CLS");
			cout << "Good Bye!!!";
			_kbhit();
			abort();
		}
	}
}

int main() {
	int start = menu();
	
	if (start){
		Setup();
	
		while (!gameOver){
			Draw();
			Input();
			Logic();
		}
	}
	
	return 0;
}

#include "head.h"


// gotoxy( 가로축 , 세로축)
void gotoxy(int x,int y)
{
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}


// 키 입력을 받아서 방향키만 걸러줌
int key_get()
{
	int key_get = 0;

	key_get = _getch();

	if(key_get == 0xE0)
		key_get = _getch();

	switch(key_get)
	{
		case LEFT:
			return LEFT;
			
		case RIGHT:
			return RIGHT;

		case UP:
			return UP;

		case DOWN:
			return DOWN;

		case SPACEBAR:
			return SPACEBAR;

		case ESC:
			return ESC;
	}
	return 0;
}

// 커서위치 이동함수
void move_point(int key)
{
	switch(key)
	{
		case LEFT:
			point[0] --;
			break;
			
		case RIGHT:
			point[0] ++;
			break;

		case UP:
			point[1] --;
			break;

		case DOWN:
			point[1] ++;
			break;
	}
}



// 현재 커서 위치가 게임판안에 존재하는지 체크하는 함수
bool key_chk(int key)
{
	switch(key)
	{
		case LEFT:
			if(point[0] > 0)
				return true;
			break;

		case RIGHT:
			if(point[0] < SIZE-1)		// 사이즈보다 -1해주는이유 0부터 시작하므로
				return true;
			break;

		case UP:
			if(point[1] > 0)
				return true;
			break;

		case DOWN:
			if(point[1] < SIZE-1)		// 사이즈보다 -1해주는이유 0부터 시작하므로
				return true;
			break;
	}
	return false;
}


#include "head.h"


// gotoxy( ������ , ������)
void gotoxy(int x,int y)
{
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}


// Ű �Է��� �޾Ƽ� ����Ű�� �ɷ���
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

// Ŀ����ġ �̵��Լ�
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



// ���� Ŀ�� ��ġ�� �����Ǿȿ� �����ϴ��� üũ�ϴ� �Լ�
bool key_chk(int key)
{
	switch(key)
	{
		case LEFT:
			if(point[0] > 0)
				return true;
			break;

		case RIGHT:
			if(point[0] < SIZE-1)		// ������� -1���ִ����� 0���� �����ϹǷ�
				return true;
			break;

		case UP:
			if(point[1] > 0)
				return true;
			break;

		case DOWN:
			if(point[1] < SIZE-1)		// ������� -1���ִ����� 0���� �����ϹǷ�
				return true;
			break;
	}
	return false;
}


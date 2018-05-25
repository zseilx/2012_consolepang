#include "head.h"


// ����ִ� ĭ���� ���� ������ �Ʒ��� ����
// ������ �Ʒ��� ������ ����̹Ƿ� x�� ������ǥ�� �ְ�
// y�� ���� ���� ��ġ�� �˷� ��� �ϹǷ�
// shift�� ���ݺ��� ��ĭ ���� ���� �����ϴ��� �˷���
// block_drop(int x������ǥ, int ����� ������ ��ġ, ���� ĭ��)
void block_drop(int x, int y, int shift)
{
	// y�� --�ذ��� ������ �ش� ������ �� �������� ������ �ϱ⶧����
	for(; y-shift >= 0; y--)
	{
		// ���� ��ġ��ŭ�� ������ �����ͼ� ���� -> ���� ��ġ
		game[x][y] = game[x][y-shift];
		// ���� ��ġ�� ������
		block_delete(x, y-shift);
		// �ش� ��ġ�� �� (x*2�� ���ִ� ������ �� ���� �ܼ�ũ�⸦ 2ĭ �����ϱ⶧��)
		gotoxy(X_SPACE+(x*2), Y_SPACE+y);
		// ��� (screen�� ����)
		block_print(game[x][y], false);
	}
}

// �ش� ��ġ�� �ִ� ���� �����ϰ� ���� ���� ����
void block_delete(int x, int y)
{
	// �ش���ġ �� �����͸� 0���� ����
	game[x][y] = 0;
	// �ش� ��ġ�� �� (x*2�� ���ִ� ������ �� ���� �ܼ�ũ�⸦ 2ĭ �����ϱ⶧��)
	gotoxy(X_SPACE+(x*2), Y_SPACE+y);
	// ��� (screen�� ����)
	block_print(game[x][y], false);
}

// ���� ������� ��� �� ��������
void block_create(int x, int y)
{
	// �ش� ��ġ�� �� �����Ͱ� �������� �������
	if(!game[x][y])
	{
		// �� �����͸� �������� �������ְ�
		game[x][y] = (rand() % BLOCK) + 1;
		// �� ���� �׷������� �����ؾ��ϴ� �������� ����
		gotoxy(X_SPACE+(x*2), Y_SPACE+y);
		// �׷����� ��������
		block_print(game[x][y], false);
	}
}

// ���� ������ ��ȯ (�����¸��)
void block_pang(int x, int y)
{
	// �ش� ��ġ�� ������ ����������� ��ȯ���ִ� ������ �������
	if(game[x][y] < PANG_NUM)
	{
		// �ش� �����ٰ� ���� ������� ��ȯ���ִ� ���� �������
		game[x][y] += PANG_NUM;
		gotoxy(X_SPACE+(x*2), Y_SPACE+y);
		block_print(game[x][y], false);
	}
}


// ������ block_position_change �Լ��� change_block �Լ��� ����� �ϳ��� ��ħ.
void block_position_change(int key)
{
	// ��ġ �ٲٱ��� ��� ������ ����
	int save = 0;
	
	save = game[point[0]][point[1]];


	// Ű �Է¿� ���� ��ġ�� ������� �ٲ�
	switch(key)
	{
		case LEFT:
			game[point[0]][point[1]] = game[point[0]-1][point[1]];
			game[point[0]-1][point[1]] = save;

			gotoxy(GP_X-2,GP_Y);
			block_print(game[point[0]-1][point[1]], false);
			break;
			

		case RIGHT:
			game[point[0]][point[1]] = game[point[0]+1][point[1]];
			game[point[0]+1][point[1]] = save;

			gotoxy(GP_X+2,GP_Y);
			block_print(game[point[0]+1][point[1]], false);
			break;


		case UP:
			game[point[0]][point[1]] = game[point[0]][point[1]-1];
			game[point[0]][point[1]-1] = save;

			gotoxy(GP_X,GP_Y-1);
			block_print(game[point[0]][point[1]-1], false);
			break;


		case DOWN:
			game[point[0]][point[1]] = game[point[0]][point[1]+1];
			game[point[0]][point[1]+1] = save;

			gotoxy(GP_X,GP_Y+1);
			block_print(game[point[0]][point[1]+1], false);
			break;
	}
	// ���� ��������Ʈ�� ��ġ�� �ڸ��� ������� �ٲ�
	gotoxy(GP_X,GP_Y);
	block_print(game[point[0]][point[1]], false);
//	gotoxy(GP_X,GP_Y);
}
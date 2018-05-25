#include "head.h"


// �⺻ ȭ�� ��� (�ʱ����)
// ���� 10ĭ��	
// �� ������ 10 * 20 (����,����)
// ���� ���� �� �� ��ǥ	(14,5)
// ������ ���� �� ��ǥ		(27,5)
// ���� ���� �Ʒ� ��ǥ		(14,11)
// ������ ���� �Ʒ� ��ǥ	(27,11)

// score ��ġ (48,6);

void base_menu_print()
{
	printf("����Ű �̵� || esc����\n");
	printf("�����̽��� �Է��� ����Ű - �ڸ��ٲٱ�\n");
	printf("\n");
	printf("          ������    combo ������\n");
	printf("          ����������������������\n");
	printf("          ����              ����        time  = 60\n");
	printf("          ����              ����        score =     \n");
	printf("          ����              ����        ver_%s\n",VER);
	printf("          ����              ����        ������ : ����ȭ\n");
	printf("          ����              ����\n");
	printf("          ����              ����\n");
	printf("          ����              ����\n");
	printf("          ����������������������\n");
	printf("          ����������������������\n");
}



// ���� �� ȣ��(�ʱ� �� ����)
void block_all_reset()
{
	int i = 0;
	int j = 0;
	
	for(i=0; i<SIZE; i++)
	{
		gotoxy(14,5+i);		// ������ �Ϸ��� gotoxy�� Ŀ�� ��ġ�� �ű�
		for(j=0; j<SIZE; j++)
		{
			game[j][i] = (rand() % BLOCK) + 1;		// �������� ��������ŭ ������ +1(1���ͽ����ϵ���)
			block_print(game[j][i], false);	// ������ ���� ȭ�鿡 �ٷιٷ� �����
		}
	}
}

// ������ ������( �������� ���� )
void game_create()
{
	// ���� ���� �������ְ�
	block_all_reset();

	// ������ ���߿� ���ӵ� ���� ������� ��Ʈ���� �ٽ� ����
	do	{
		pang_delete();
	} while(block_straight_chk(0));
}

// ���� �Űܼ� ��Ʈ���� �ִ� ���� �ִ��� üũ�Լ�
bool pang_chk()
{
	for(int i=0; i<SIZE; i++)
	{
		for(int j=0; j<SIZE; j++)
		{
			if(game[i][j] == ��)
				return true;

			if(i<SIZE && j<SIZE-3)
			{
				// j - x��
				// �ۡ�  ��
				// ��  �ܡ�
				if(game[j][i] == game[j+1][i] && game[j][i] == game[j+3][i])
					return true;
				else if(game[j][i]== game[j+2][i] && game[j][i] == game[j+3][i])
					return true;

				// j - y��
				// �ܡ�
				// ��
				//   ��
				// �ܡ�
				else if(game[i][j] == game[i][j+1] && game[i][j] == game[i][j+3])
					return true;
				else if(game[i][j] == game[i][j+2] && game[i][j] == game[i][j+3])
					return true;
			}

			if(i<SIZE-1 && j<SIZE-2)
			{
				// j - x��
				// �ۡܡ�
				// �ܡۡ�
				if(game[j][i] == game[j+1][i+1] && game[j][i] == game[j+2][i])
					return true;
				else if(game[j][i+1] == game[j+1][i] && game[j][i+1] == game[j+2][i+1])
					return true;
				// �ۡܡ�
				// �ܡۡ�
				else if(game[j][i] == game[j+1][i+1] && game[j][i] == game[j+2][i+1])
					return true;
				else if(game[j][i+1] == game[j+1][i] && game[j][i+1] == game[j+2][i])
					return true;
				// �ۡۡ�
				// �ܡܡ�
				else if(game[j][i] == game[j+1][i] && game[j][i] == game[j+2][i+1])
					return true;
				else if(game[j][i+1] == game[j+1][i+1] && game[j][i+1] == game[j+2][i])
					return true;

				// j - y��
				// �ۡ�
				// �ܡ�
				// �ۡ�
				else if(game[i][j] == game[i+1][j+1] && game[i][j] == game[i][j+2])
					return true;
				else if(game[i+1][j] == game[i][j+1] && game[i+1][j] == game[i+1][j+2])
					return true;

				// �ۡ�
				// �ۡ�
				// �ܡ�
				else if(game[i][j] == game[i][j+1] && game[i][j] == game[i+1][j+2])
					return true;
				else if(game[i+1][j] == game[i+1][j+1] && game[i+1][j] == game[i][j+2])
					return true;
				
				// �ۡ�
				// �ܡ�
				// �ܡ�
				else if(game[i][j] == game[i+1][j+1] && game[i][j] == game[i+1][j+2])
					return true;
				else if(game[i+1][j] == game[i][j+1] && game[i+1][j] == game[i][j+2])
					return true;
			}
		}
	}
	return false;
}


void game_start()
{
	// ���� ������ Ű���尪�� ������ ����
	int key = 0;
	// �ӽ� ������ ī��Ʈ
	int pang_cnt = 0;
	// ���� ���õǾ��� ��� ���� �ٲ��־��� �ȹٲ��־��� üũ
	bool chk = 0;
	 
	// timer_print  ���α׷� �帥 �ð��� END_TIME���� Ŭ ��� -1�� ���ϵ�.
	while(timer_print(END_TIME) != -1)
	{
		if(_kbhit() && key != SPACEBAR)
			key = key_get();
		else if(chk != true && key == SPACEBAR)
		{
			block_print(game[point[0]][point[1]], true);
			chk = true;

			// ��ź�� ��� ����
			if(game[point[0]][point[1]] == ��)
			{
				Sleep(300);
				bomb();

				pang_pang();

				chk = false;
				key = 0;
			}
		}

		// key�� SPACEBAR �Է��� ���ð��
		// �ѹ��� ����Ű �Է��� �޾Ƽ� �ش� ����Ű �����
		// ���� ���õ� ��ġ�� ����ġ�� ��� �ٲ㼭 ��
		else if(_kbhit() && key == SPACEBAR)
		{
			key = key_get();
			chk = false;

			if(key_chk(key))
			{
				// ����ġ ��� �ٲٴ°�.
				block_position_change(key);

				// �� ���ֱ�
				pang_cnt = pang_pang();

				// ������� ����ġ �ٽ� ���󺹱�
				if(pang_cnt == 0)
					block_position_change(key);

				pang_cnt = 0;
				key = 0;
			}
			if(chk == false && key == ESC)
				block_print(game[point[0]][point[1]], false);
		}
		else if(key_chk(key))
		{
			// �ܼ�Ŀ�� ��ǥ�� �̵����ֱ�
			move_point(key);
			key = 0;
		}
		//��Ʈ�� ��� ������ ���½����ֱ�
		if(!pang_chk())
		{
			gotoxy(0,2);
			printf("��Ʈ�� ����� �����ϴ�. ����� ���ġ �մϴ�.");
			Sleep(500);
			game_create();
			gotoxy(0,2);
			printf("                                                  ");
		}

		gotoxy(GP_X, GP_Y);
	}	// __while
}
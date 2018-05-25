#include "head.h"


// ���� ���ӽð� ��°� �ð��� �ٵǸ� ���ᰪ�� ��������
int timer_print(int end_time)
{
	static int old_time = 0;
	int time = clock() / CLOCKS_PER_SEC;


	// ���� �ð��� ����ð����� ũ�ų� ������ (������ ����Ǿ���� ���� �˷���)
	if(time > end_time)
		return -1;

	// ���� �ð��� 1���̻� ���̰� ����� ȭ���� �ð��� ��������
	else if(old_time != time)
	{
		old_time = time;
		gotoxy(48,5);
		printf("%2d",end_time - (clock() / CLOCKS_PER_SEC));
		gotoxy(GP_X,GP_Y);
		return 1;
	}

	return 0;
}

// ���� ���� ���� �������� ���
void score_print(int pang_num)
{
	// ���Ѱ��� ����
	int result = 2;

	// �� �Ѱ��� ������ ����ġ 
	for(int i=pang_num; i>0; i--)
		result ++;

	// ((���Ѱ������� * �� �Ѱ���) * �޺�����ġ) ��ŭ�� ���� ���ھ�� ���ؼ� ���
	score += (int)( (result * pang_num) * COMBO_BONUS );
	gotoxy(48,6);
	printf("%5d",score);
	gotoxy(GP_X,GP_Y);
}

// �޺���ġ ���� ���� �޺� �� ���
void combo_print()
{
	// ���� �޺��� ����ð��� �Ǿ��� üũ
	static int old_time = 0;
	// ���� �ð� üũ
	int time = clock() / CLOCKS_PER_SEC;

	// ���� �޺��� ���� 3�ʰ� ������ �ʾҴٸ�
	if(old_time + 3 >= time) 
		combo_cnt++;
	// �����ٸ� �޺� �ʱ�ȭ
	else
		combo_cnt = 1;

	// ���� �ð��� ����ð����� �ٲ���
	old_time = time;

	// ���� �޺��� ���
	gotoxy(17,3);
	printf("%2d",combo_cnt);
	gotoxy(GP_X,GP_Y);
}


// �� ���� ���� �� ���
// select_chk �� ���� �����̽��ٷ� ���õǾ������� �ǹ���
void block_print(int block, bool select_chk)
{
	switch(block)
	{
		case 0:
			printf("  ");
			break;

		case ��:
			SetColor(1 + (select_chk*SELECT_COLOR_PLUS), 0 );
			printf("��");
			break;

		case ��:
			SetColor(2 + (select_chk*SELECT_COLOR_PLUS), 0 );
			printf("��");
			break;

		case ��:
			SetColor(3 + (select_chk*SELECT_COLOR_PLUS), 0 );
			printf("��");
			break;

		case ��:
			SetColor(4 + (select_chk*SELECT_COLOR_PLUS), 0 );
			printf("��");
			break;

		case ��:
			SetColor(5 + (select_chk*SELECT_COLOR_PLUS), 0 );
			printf("��");
			break;

		case ��:
			SetColor(6 + (select_chk*SELECT_COLOR_PLUS), 0 );
			printf("��");
			break;

		case ��:
			SetColor(7 + (select_chk*SELECT_COLOR_PLUS), 0 );
			printf("��");
			break;

// ��ź ���
		case ��:
			SetColor(  select_chk? 12 : 15 , 0 );
			printf("��");
			break;

// ������ �� ���� ���
		default:
			SetColor(15 , 0 );
			printf("��");
			break;
	}
	SetColor(7 , 0 );
}



// �ܼ�ȭ�� ���� ��� ����
// 7�� �⺻����
void SetColor(int color , int bgcolor )
{
    color   &= 0xf;
    bgcolor &= 0xf ;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4)  | color  );
}

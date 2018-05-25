#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

// ����Ű ����
#define LEFT		75
#define RIGHT		77
#define UP			72
#define DOWN		80
#define SPACEBAR	32
#define ESC			27

// base_menu_print ���� �����̽��ٷ� ����� ������ �ǹ�	(gotoxy���� x��ǥ 14���� ��밡��)
#define X_SPACE 14
// base_menu_print ���� ���� ���ڷ� ���� ��ŭ�� �ǹ� (gotoxy���� y��ǥ 5���� ��밡��)
#define Y_SPACE 5

// ��ǥ���� �ܼ�ȭ��� ��ġ�� ���� ������
// GP_X (x*2�� ���ִ� ������ �� ���� �ܼ�ũ�⸦ x������ 2ĭ �����ϱ⶧��)
// GP_Y y���� ��ĭ
#define GP_X	point[0]*2 + X_SPACE		// point[0]*2 �ϴ� ������ �� ���� ��ĭ�� �����ϹǷ�.
#define GP_Y	point[1] + Y_SPACE

// ������ ũ��
#define SIZE	7
// ����� ���� ��簹��
#define BLOCK	7

// ���� ����
#define VER		"1.01"
// ���� �޺� ���� ���� ����ġ���
#define COMBO_BONUS (1 + ((combo_cnt-1) * 0.5f))
// ���� ���õǾ����� �����ִ� �÷���.
#define SELECT_COLOR_PLUS	8
// ������ ������ �ð�
#define END_TIME	60
// � �̻��� ���� �ѹ��� ������ ��ź�� �����Ǵ°��� ����
#define BOMB		4
// ��ź�� �͠����� �⺻ ����. �� �������ٰ� �޺� ����ġ�� ������ ���� ���� ��ź�͠����� ����
#define BOMB_SCORE	300
// ���� �͠��ٴ� ��ȣ�� �ٶ� ������ ��.
#define PANG_NUM 10

// ��ĭ 0
// �� 1~7
// ��ź 8
// ���� ��� �� �� + PANG_NUM
enum{��=1,��,��,��,��,��,��,��};


// point[0] == x��   point[1] == y��
// ���� Ŀ���� game[][]�迭�� ��ġ�������� ����Ŵ.
extern int point[2];
// ���� ����� �� ��ġ�� ����Ǿ��ִ� ������
// game [x��] [y��]
extern int game[SIZE][SIZE];
// ���� ���� ���� ����
extern int score;
// ���� �޺��� ����
extern int combo_cnt;



// gotoxy( x , y)									
void gotoxy(int x,int y);	//___ key_cursor.cpp �� ����
// Ű �Է� �޾ƿ���											
int key_get();				//___ key_cursor.cpp �� ����
// Ŀ����ġ �̵��Լ�										
void move_point(int key);	//___ key_cursor.cpp �� ����
// ���� Ŀ�� ��ġ�� �����Ǿȿ� �����ϴ��� üũ�ϴ� �Լ�		
bool key_chk(int key);		//___ key_cursor.cpp �� ����


// �⺻ ����ȭ�� ���			
void base_menu_print();				//___ init.cpp �� ����
// game[][] �迭 ��ü���ٰ� ������ ���� �־���
void block_all_reset();				//___ init.cpp �� ����
// ������ ������( �������� ���� )
void game_create();					//___ init.cpp �� ����
// ���� �Űܼ� ��Ʈ���� �ִ� ���� �ִ��� üũ�Լ�
bool pang_chk();					//___ init.cpp �� ����
// ���� �����Լ�
void game_start();					//___ init.cpp �� ����


// �� ���� ���� �� ���
void block_print(int block, bool select_chk);	//___ print.cpp �� ����
// ���� ���ӽð� ��°� �ð��� �ٵǸ� ���ᰪ�� ��������
int timer_print(int end_time);					//___ print.cpp �� ����
// �ܼ�ȭ�� ���� ��� ����
void SetColor(int color , int bgcolor );		//___ print.cpp �� ����
// �޺���ġ ���� ���� �޺� �� ���
void combo_print();								//___ print.cpp �� ����
// ���� ���� ���� �������� ���
void score_print(int pang_num);					//___ print.cpp �� ����



// ����ִ� ĭ���� ���� ������ �Ʒ��� ����
// ������ �Ʒ��� ������ ����̹Ƿ� x�� ������ǥ�� �ְ�
// y�� ���� ���� ��ġ�� �˷� ��� �ϹǷ�
// shift�� ���ݺ��� ��ĭ ���� ���� �����ϴ��� �˷���
// block_drop(int x������ǥ, int ����� ������ ��ġ, ���� ĭ��)	
void block_drop(int x, int y, int shift);			//___ block_state_change_cpp �� ����
// �����̽��� �Է��� ����Ű�������� �ٲ� ������ ��ġ�� �ٽ� ǥ�����ִ� �Լ�
void block_position_change(int key);				//___ block_state_change_cpp �� ����
// ���� ������� ��� �� ��������	
void block_create(int i, int j);					//___ block_state_change_cpp �� ����
// �ش� ��ġ�� �ִ� ���� �����ϰ� ���� ���� ����	
void block_delete(int x, int y);					//___ block_state_change_cpp �� ����
// ���� �͠��� ��� �������͸� �����ϰ� ����������� �������
void block_pang(int x, int y);						//___ block_state_change_cpp �� ����


// ���� ����� ������ �����ϰ� ������ ������ŭ ��������
int pang_delete();						//___ pang_bomb.cpp �� ����
// 3�� �̻��� ���ӵ� ������� ������� ����������� �ٲ��ְ� ���ӵ� ���� ����־����� ��������
int block_straight_chk(int bomb_chk);	//___ pang_bomb.cpp �� ����
// ���� ��Ʈ���� ����������ϰ� ���λ��� �� ������ �κ��� �Լ��� ��ģ�κ�
int pang_pang();						//___ pang_bomb.cpp �� ����
// ��ź�� �������� ��� ����Ǵ� ��ź�����Լ�
void bomb();							//___ pang_bomb.cpp �� ����
// ������ ����� �Ŀ� ��ź�� ��Ʈ���� ��������� ���ִ� �Լ�
void end_bomb();							//___ pang_bomb.cpp �� ����
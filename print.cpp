#include "head.h"


// 남은 게임시간 출력과 시간이 다되면 종료값을 리턴해줌
int timer_print(int end_time)
{
	static int old_time = 0;
	int time = clock() / CLOCKS_PER_SEC;


	// 게임 시간이 종료시간보다 크거나 같을때 (게임이 종료되어야할 때를 알려줌)
	if(time > end_time)
		return -1;

	// 그전 시간과 1초이상 차이가 날경우 화면의 시간을 갱신해줌
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

// 게임 점수 계산과 게임점수 출력
void score_print(int pang_num)
{
	// 블럭한개당 점수
	int result = 2;

	// 블럭 한개당 블럭점수 가중치 
	for(int i=pang_num; i>0; i--)
		result ++;

	// ((블럭한개당점수 * 블럭 총갯수) * 콤보가중치) 만큼을 현재 스코어값에 더해서 출력
	score += (int)( (result * pang_num) * COMBO_BONUS );
	gotoxy(48,6);
	printf("%5d",score);
	gotoxy(GP_X,GP_Y);
}

// 콤보수치 계산과 현재 콤보 수 출력
void combo_print()
{
	// 그전 콤보가 어느시간에 되엇나 체크
	static int old_time = 0;
	// 현재 시간 체크
	int time = clock() / CLOCKS_PER_SEC;

	// 그전 콤보를 한지 3초가 지나지 않았다면
	if(old_time + 3 >= time) 
		combo_cnt++;
	// 지낫다면 콤보 초기화
	else
		combo_cnt = 1;

	// 그전 시간을 현재시간으로 바꿔줌
	old_time = time;

	// 현재 콤보수 출력
	gotoxy(17,3);
	printf("%2d",combo_cnt);
	gotoxy(GP_X,GP_Y);
}


// 블럭 값에 따른 블럭 출력
// select_chk 는 블럭이 스페이스바로 선택되었을때를 의미함
void block_print(int block, bool select_chk)
{
	switch(block)
	{
		case 0:
			printf("  ");
			break;

		case ◆:
			SetColor(1 + (select_chk*SELECT_COLOR_PLUS), 0 );
			printf("◆");
			break;

		case ■:
			SetColor(2 + (select_chk*SELECT_COLOR_PLUS), 0 );
			printf("■");
			break;

		case ▲:
			SetColor(3 + (select_chk*SELECT_COLOR_PLUS), 0 );
			printf("▲");
			break;

		case ★:
			SetColor(4 + (select_chk*SELECT_COLOR_PLUS), 0 );
			printf("★");
			break;

		case ♠:
			SetColor(5 + (select_chk*SELECT_COLOR_PLUS), 0 );
			printf("♠");
			break;

		case ♥:
			SetColor(6 + (select_chk*SELECT_COLOR_PLUS), 0 );
			printf("♥");
			break;

		case ♣:
			SetColor(7 + (select_chk*SELECT_COLOR_PLUS), 0 );
			printf("♣");
			break;

// 폭탄 모양
		case ※:
			SetColor(  select_chk? 12 : 15 , 0 );
			printf("※");
			break;

// 터지기 전 변할 모양
		default:
			SetColor(15 , 0 );
			printf("⊙");
			break;
	}
	SetColor(7 , 0 );
}



// 콘솔화면 색상 출력 설정
// 7이 기본색상
void SetColor(int color , int bgcolor )
{
    color   &= 0xf;
    bgcolor &= 0xf ;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4)  | color  );
}

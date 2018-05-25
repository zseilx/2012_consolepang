#include "head.h"


// 기본 화면 출력 (초기셋팅)
// 공백 10칸씩	
// 총 사이즈 10 * 20 (가로,세로)
// 왼쪽 구석 위 의 좌표	(14,5)
// 오른쪽 구석 위 좌표		(27,5)
// 왼쪽 구석 아래 좌표		(14,11)
// 오른쪽 구석 아래 좌표	(27,11)

// score 위치 (48,6);

void base_menu_print()
{
	printf("방향키 이동 || esc종료\n");
	printf("스페이스바 입력후 방향키 - 자리바꾸기\n");
	printf("\n");
	printf("          ┌──    combo ──┐\n");
	printf("          │┌───────┐│\n");
	printf("          ││              ││        time  = 60\n");
	printf("          ││              ││        score =     \n");
	printf("          ││              ││        ver_%s\n",VER);
	printf("          ││              ││        제작자 : 정영화\n");
	printf("          ││              ││\n");
	printf("          ││              ││\n");
	printf("          ││              ││\n");
	printf("          │└───────┘│\n");
	printf("          └─────────┘\n");
}



// 랜덤 수 호출(초기 블럭 셋팅)
void block_all_reset()
{
	int i = 0;
	int j = 0;
	
	for(i=0; i<SIZE; i++)
	{
		gotoxy(14,5+i);		// 개행을 하려고 gotoxy로 커서 위치를 옮김
		for(j=0; j<SIZE; j++)
		{
			game[j][i] = (rand() % BLOCK) + 1;		// 디파인한 블럭갯수만큼 나눠서 +1(1부터시작하도록)
			block_print(game[j][i], false);	// 생성한 블럭을 화면에 바로바로 출력함
		}
	}
}

// 게임을 생성함( 블럭데이터 삽입 )
void game_create()
{
	// 블럭을 새로 생성해주고
	block_all_reset();

	// 생성된 블럭중에 연속된 블럭이 있을경우 터트리고 다시 생성
	do	{
		pang_delete();
	} while(block_straight_chk(0));
}

// 블럭을 옮겨서 터트릴수 있는 블럭이 있는지 체크함수
bool pang_chk()
{
	for(int i=0; i<SIZE; i++)
	{
		for(int j=0; j<SIZE; j++)
		{
			if(game[i][j] == ※)
				return true;

			if(i<SIZE && j<SIZE-3)
			{
				// j - x축
				// ○○  ○
				// ●  ●●
				if(game[j][i] == game[j+1][i] && game[j][i] == game[j+3][i])
					return true;
				else if(game[j][i]== game[j+2][i] && game[j][i] == game[j+3][i])
					return true;

				// j - y축
				// ●○
				// ●
				//   ○
				// ●○
				else if(game[i][j] == game[i][j+1] && game[i][j] == game[i][j+3])
					return true;
				else if(game[i][j] == game[i][j+2] && game[i][j] == game[i][j+3])
					return true;
			}

			if(i<SIZE-1 && j<SIZE-2)
			{
				// j - x축
				// ○●○
				// ●○●
				if(game[j][i] == game[j+1][i+1] && game[j][i] == game[j+2][i])
					return true;
				else if(game[j][i+1] == game[j+1][i] && game[j][i+1] == game[j+2][i+1])
					return true;
				// ○●●
				// ●○○
				else if(game[j][i] == game[j+1][i+1] && game[j][i] == game[j+2][i+1])
					return true;
				else if(game[j][i+1] == game[j+1][i] && game[j][i+1] == game[j+2][i])
					return true;
				// ○○●
				// ●●○
				else if(game[j][i] == game[j+1][i] && game[j][i] == game[j+2][i+1])
					return true;
				else if(game[j][i+1] == game[j+1][i+1] && game[j][i+1] == game[j+2][i])
					return true;

				// j - y축
				// ○●
				// ●○
				// ○●
				else if(game[i][j] == game[i+1][j+1] && game[i][j] == game[i][j+2])
					return true;
				else if(game[i+1][j] == game[i][j+1] && game[i+1][j] == game[i+1][j+2])
					return true;

				// ○●
				// ○●
				// ●○
				else if(game[i][j] == game[i][j+1] && game[i][j] == game[i+1][j+2])
					return true;
				else if(game[i+1][j] == game[i+1][j+1] && game[i+1][j] == game[i][j+2])
					return true;
				
				// ○●
				// ●○
				// ●○
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
	// 게임 내에서 키보드값을 저장할 변수
	int key = 0;
	// 임시 블럭터진 카운트
	int pang_cnt = 0;
	// 블럭이 선택되었을 경우 색을 바꿔주엇나 안바꿔주엇나 체크
	bool chk = 0;
	 
	// timer_print  프로그램 흐른 시간이 END_TIME보다 클 경우 -1이 리턴됨.
	while(timer_print(END_TIME) != -1)
	{
		if(_kbhit() && key != SPACEBAR)
			key = key_get();
		else if(chk != true && key == SPACEBAR)
		{
			block_print(game[point[0]][point[1]], true);
			chk = true;

			// 폭탄일 경우 터짐
			if(game[point[0]][point[1]] == ※)
			{
				Sleep(300);
				bomb();

				pang_pang();

				chk = false;
				key = 0;
			}
		}

		// key에 SPACEBAR 입력이 들어올경우
		// 한번더 방향키 입력을 받아서 해당 방향키 방향과
		// 현재 선택된 위치의 블럭위치를 잠시 바꿔서 비교
		else if(_kbhit() && key == SPACEBAR)
		{
			key = key_get();
			chk = false;

			if(key_chk(key))
			{
				// 블럭위치 잠시 바꾸는것.
				block_position_change(key);

				// 블럭 터주기
				pang_cnt = pang_pang();

				// 없을경우 블럭위치 다시 원상복귀
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
			// 콘솔커서 좌표값 이동해주기
			move_point(key);
			key = 0;
		}
		//터트릴 블록 없을때 리셋시켜주기
		if(!pang_chk())
		{
			gotoxy(0,2);
			printf("터트릴 블록이 없습니다. 블록을 재배치 합니다.");
			Sleep(500);
			game_create();
			gotoxy(0,2);
			printf("                                                  ");
		}

		gotoxy(GP_X, GP_Y);
	}	// __while
}
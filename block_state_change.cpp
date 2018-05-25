#include "head.h"


// 비어있는 칸으로 위의 블럭들을 아래로 내림
// 위에서 아래로 내리는 경우이므로 x는 고정좌표로 주고
// y는 블럭이 없는 위치를 알려 줘야 하므로
// shift는 지금부터 몇칸 위에 블럭이 존재하는지 알려줌
// block_drop(int x고정좌표, int 땡기기 시작할 위치, 땡길 칸수)
void block_drop(int x, int y, int shift)
{
	// y를 --해가는 이유는 해당 라인의 젤 위까지만 내려야 하기때문에
	for(; y-shift >= 0; y--)
	{
		// 땡길 위치만큼의 위에서 가져와서 저장 -> 현재 위치
		game[x][y] = game[x][y-shift];
		// 땡긴 위치의 블럭제거
		block_delete(x, y-shift);
		// 해당 위치로 감 (x*2를 해주는 이유는 한 블럭당 콘솔크기를 2칸 차지하기때문)
		gotoxy(X_SPACE+(x*2), Y_SPACE+y);
		// 출력 (screen에 정의)
		block_print(game[x][y], false);
	}
}

// 해당 위치에 있는 블럭을 제거하고 게임 값을 삭제
void block_delete(int x, int y)
{
	// 해당위치 블럭 데이터를 0으로 만듬
	game[x][y] = 0;
	// 해당 위치로 감 (x*2를 해주는 이유는 한 블럭당 콘솔크기를 2칸 차지하기때문)
	gotoxy(X_SPACE+(x*2), Y_SPACE+y);
	// 출력 (screen에 정의)
	block_print(game[x][y], false);
}

// 블럭이 비어있을 경우 블럭 생성해줌
void block_create(int x, int y)
{
	// 해당 위치에 블럭 데이터가 존재하지 않을경우
	if(!game[x][y])
	{
		// 블럭 데이터를 랜덤으로 삽입해주고
		game[x][y] = (rand() % BLOCK) + 1;
		// 그 블럭이 그래픽으로 존재해야하는 지점으로 가서
		gotoxy(X_SPACE+(x*2), Y_SPACE+y);
		// 그래픽을 삽입해줌
		block_print(game[x][y], false);
	}
}

// 블럭을 팡으로 변환 (터지는모션)
void block_pang(int x, int y)
{
	// 해당 위치의 블럭값이 터진모양으로 변환해주는 값보다 작을경우
	if(game[x][y] < PANG_NUM)
	{
		// 해당 블럭에다가 터진 모양으로 변환해주는 값을 집어넣음
		game[x][y] += PANG_NUM;
		gotoxy(X_SPACE+(x*2), Y_SPACE+y);
		block_print(game[x][y], false);
	}
}


// 기존의 block_position_change 함수와 change_block 함수의 기능을 하나로 합침.
void block_position_change(int key)
{
	// 위치 바꾸기전 잠시 저장할 변수
	int save = 0;
	
	save = game[point[0]][point[1]];


	// 키 입력에 따른 위치의 블럭모양을 바꿈
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
	// 현재 게임포인트가 위치한 자리의 블럭모양을 바꿈
	gotoxy(GP_X,GP_Y);
	block_print(game[point[0]][point[1]], false);
//	gotoxy(GP_X,GP_Y);
}
#include "head.h"

// 게임이 종료된 후에 폭탄을 터트리고 점수계산을 해주는 함수
void end_bomb()
{
	int bomb_cnt = 1;

	while(bomb_cnt > 0)
	{
		bomb_cnt = 0;
		// 폭탄이 있는가 모든 game[][] 배열을 조회해서 터트림
		for(int j=0; j<SIZE; j++)
		{
			for(int i=0; i<SIZE; i++)
			{
				if(game[i][j] == ※)
				{
					point[0] = i;
					point[1] = j;

					Sleep(300);
					bomb();
					bomb_cnt++;

					// 폭탄을 터트린후 터질 블럭이 있을경우 터짐
//					while( pang_pang() );
					pang_pang();
				}
			}
		}
	}
}

// 폭탄을 선택햇을 경우 실행되는 폭탄동작함수
void bomb()
{
	// 해당 위치의 폭탄 제거
	block_pang(point[0],point[1]);

	// 가로 세로의 블럭을 터진 모양으로 변경
	for(int i=0; i<SIZE; i++)
	{
		if(game[point[0]][i] != ※)
			block_pang(point[0],i);
		if(game[i][point[1]] != ※)
			block_pang(i,point[1]);
	}
	Sleep(300);

	// 터진 모양의 블럭들을 제거
	pang_delete();
	combo_print();

	// 게임 스코어에 폭탄점수 * 콤보보너스를 곱해서 더해줌
	score += (int)(BOMB_SCORE * COMBO_BONUS);
	// 게임 스코어를 표시해줌
	score_print( 0 );
}

// 블럭을 터트리고 점수계산을하고 새로생성 등 터지는 부분을 함수로 뭉친부분
int pang_pang()
{
	int pang = 1;	// block_straight_chk()의 리턴값은 블럭뭉치가 터진 횟수
	int pang_cnt = 0;

	while(pang)
	{
		pang = block_straight_chk(1);

		Sleep(300);
		if(pang != 0)
		{
			combo_print();
			score_print( pang_delete() );
			Sleep(300);
			pang_cnt++;
		}
		timer_print(END_TIME);			// 그냥 콤보중에도 시간을 표시해주기 위함
	}
	return pang_cnt;
}

// 3개 이상의 연속된 블럭모양이 있을경우 터진모양으로 바꿔주고 연속된 블럭이 몇번있었는지 리턴해줌
int block_straight_chk(int bomb_chk)
{
	// 바깥쪽 폴문 - 한 줄씩 내리는 역할
	int i = 0;
	// 안쪽 폴문   - 각각 한문자씩 비교하는 역할
	int j = 0;
	// 연속되는 블럭을 터트릴 때 사용하려고 만든 폴문 변수
	int k = 0;

	// 같을때 카운터를 세림 x,y를 한번에 세리려고 배열로 2개를 만듬
	// 카운트는 기본적으로 1로 초기화하고 똑같은개 한개 생길때마다 1씩증가시킴
	int cnt[2] = {1,1};
	// 변하거나 j가 마지막 배열번호에 도달햇을때 체크해줌으로써 이제 이줄이 끝낫거나
	// 아니면 연속되는 블럭 모양이 끝낫다는 표시를 해줌으로써 터트려야할 분기점을 만들어주는 변수
	// x,y를 한번에 세리려고 배열로 2개를 만듬
	int chk[2] = {0,};

	// 바깥에 연동되는 블럭위치 교환 함수와 연동시키려고 터진 갯수를 세리는 함수
	int out_put = 0;


	for(i=0; i<SIZE; i++)
	{ // for__ i
		for(j=0; j<SIZE; j++)
		{ // for__ j

			if(j < SIZE-1)		// 배열에 끝에 도달하지 않앗을경우
			{			
				if((game[j][i] == game[j+1][i]  ||  game[j][i] + PANG_NUM == game[j+1][i]  ||  game[j][i] == game[j+1][i] + PANG_NUM)
						&& game[j][i] != ※)		// x축 비교 - 현재위치블럭 == 다음위치블럭  && 해당위치가 폭탄이 아닐때
					cnt[0]++;		// x축 cnt[0] ++
				else		// x축 비교 - 현재위치블럭 != 다음위치블럭
					chk[0] = 1;		// x축 chk[0]에 표시의미로 1을 대입


				if((game[i][j] == game[i][j+1]  ||  game[i][j] + PANG_NUM == game[i][j+1]  ||  game[i][j] == game[i][j+1] + PANG_NUM)
						&& game[i][j] != ※)		// y축 비교 - 현재위치블럭 == 다음위치블럭  && 해당위치가 폭탄이 아닐때
					cnt[1]++;		// y축 cnt[1] ++
				else		// y축 비교 - 현재위치블럭 != 다음위치블럭
					chk[1] = 1;		// y축 chk[1]에 표시의미로 1을 대입
			}
			else			// 배열의 끝에 도달햇을 경우
			{
				// 배열의 끝이므로 둘 모두에게 끝낫다는 신호를 줘서 블럭을 터트릴 수 있도록 신호를 줌
				chk[0] = 1;
				chk[1] = 1;
			}

			// x축을 비교해나가는 체크가 1이 되었을때
			// 블럭이 변햇다거나 j가 배열의 끝에 도달햇다는 신호가 왓다는 뜻
			if(chk[0] == 1)
			{
				// cnt가 3개 이상 (같은 블럭이 연속적으로 3개 이상 있다는 뜻)
				if(cnt[0] >= 3)
				{
					// 카운트 갯수만큼 k를 증가시킴
					for(k=0; k<cnt[0]; k++)
					{
						// j-k  점점 감소하면서 <- 방향으로 제거함
						block_pang(j-k, i);
					}
					if(cnt[0] >= BOMB && bomb_chk)
					{
						game[j-(k/2)][i] = ※;
						gotoxy(X_SPACE + (j-(k/2))*2 , Y_SPACE + i);
						block_print(game[j-(k/2)][i], false);
					}
					// 3개이상 연속적으로 같은블럭이 있다는 카운터를 증가
					out_put ++;
				}
				// 블럭을 터트리든 못터트리든 j의 배열이 끝낫거나
				// 연속되는 블럭모양이 끝이 났으므로
				// x축 cnt[0]을 1로 초기화해주고
				// x축 chk[0]을 다시 0으로 변환
				cnt[0] = 1;
				chk[0] = 0;
			}
			// y축을 비교해나가는 체크가 1이 되었을때
			// 블럭이 변햇다거나 j가 배열의 끝에 도달햇다는 신호가 왓다는 뜻
			if(chk[1] == 1)
			{
				// cnt가 3개 이상 (같은 블럭이 연속적으로 3개 이상 있다는 뜻)
				if(cnt[1] >= 3)
				{
					for(k=0; k<cnt[1]; k++)
					{
						block_pang(i, j-k);
					}
					if(cnt[1] >= BOMB && bomb_chk)
					{
						game[i][j-(k/2)] = ※;
						gotoxy(X_SPACE + i*2, Y_SPACE + (j-(k/2)));
						block_print(game[i][j-(k/2)], false);
					}
					// 3개이상 연속적으로 같은블럭이 있다는 카운터를 증가
					out_put ++;
				}
				cnt[1] = 1;
				chk[1] = 0;
			}

		} // for__ j
	} // for__ i
	return out_put;
}


// 터진 모양의 블럭들을 삭제하고 삭제한 갯수만큼 리턴해줌
int pang_delete()
{
	// 세로로 연속되는 블럭의 갯수를 새아림
	int cnt = 0;
	// 터진 블럭들의 연속됨이 끝낫는가체크
	// 터진 블럭들이 끝낫을경우 그만큼 아래로 내리고 위에 새로운 블럭들을 생성해줘야하므로
	int chk = 0;
	// 몇개의 터진 블럭들을 제거햇는가 리턴해줌
	int score_cnt = 0;


	// 세로로 비교해나가는것.

	// x축을 아래로 내려줌  열
	for(int i=0; i<SIZE; i++)
	{
		// y축으로 한칸씩 내려감  행
		for(int j=0; j<SIZE; j++)
		{
			// 터진 블럭을 만낫을경우
			if(game[i][j] > 10)
			{
				block_delete(i,j);
				score_cnt++;
				cnt ++;
			}
			else chk = 1;

			// 터진 블럭들의 연속됨이 끝낫거나 || 줄의 제일 아랫부분에 도달햇을때
			if((chk == 1 || j == 6) && cnt > 0)
			{
				// 블럭을 위에서 아래로 블럭이 터진 갯수만큼의 위에서 당겨옴
				block_drop(i,j-chk,cnt);
				// 터진 갯수만큼의 블럭을 재생성
				for(int k=0; k<= cnt; k++)
				{
					block_create(i,0+k);
				}
				// 연속되는 블럭들이 끝낫기 때문에 카운트를 초기화
				cnt = 0;
			}
			// 체크를 사용햇으므로 초기화
			chk = 0;
		} //___ for_j
		// 다음 줄로 넘어갓기때문에 카운트를 다시 새림
		cnt = 0;
	} //___ for_i
	return score_cnt;
}
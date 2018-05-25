#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

// 방향키 값들
#define LEFT		75
#define RIGHT		77
#define UP			72
#define DOWN		80
#define SPACEBAR	32
#define ESC			27

// base_menu_print 에서 스페이스바로 띄워준 공간을 의미	(gotoxy에서 x좌표 14부터 사용가능)
#define X_SPACE 14
// base_menu_print 에서 개행 문자로 내린 만큼을 의미 (gotoxy에서 y좌표 5부터 사용가능)
#define Y_SPACE 5

// 좌표값과 콘솔화면상 위치의 실제 대응점
// GP_X (x*2를 해주는 이유는 한 블럭당 콘솔크기를 x축으로 2칸 차지하기때문)
// GP_Y y축은 한칸
#define GP_X	point[0]*2 + X_SPACE		// point[0]*2 하는 이유는 한 블럭당 두칸을 차지하므로.
#define GP_Y	point[1] + Y_SPACE

// 게임판 크기
#define SIZE	7
// 적용된 블럭의 모양갯수
#define BLOCK	7

// 게임 버전
#define VER		"1.01"
// 현재 콤보 수에 따른 가중치계산
#define COMBO_BONUS (1 + ((combo_cnt-1) * 0.5f))
// 블럭이 선택되었을때 더해주는 컬러값.
#define SELECT_COLOR_PLUS	8
// 게임이 끝나는 시간
#define END_TIME	60
// 몇개 이상의 블럭이 한번에 터져야 폭탄이 생성되는가를 설정
#define BOMB		4
// 폭탄이 터졋을때 기본 점수. 이 점수에다가 콤보 가중치가 곱해진 값이 실제 폭탄터졋을때 점수
#define BOMB_SCORE	300
// 블럭이 터졋다는 신호를 줄때 더해줄 값.
#define PANG_NUM 10

// 빈칸 0
// 블럭 1~7
// 폭탄 8
// 터진 모양 각 블럭 + PANG_NUM
enum{◆=1,■,▲,★,♠,♥,♣,※};


// point[0] == x축   point[1] == y축
// 현재 커서의 game[][]배열의 위치대응점을 가르킴.
extern int point[2];
// 게임 진행시 각 위치에 저장되어있는 아이콘
// game [x축] [y축]
extern int game[SIZE][SIZE];
// 게임 점수 저장 변수
extern int score;
// 현재 콤보수 저장
extern int combo_cnt;



// gotoxy( x , y)									
void gotoxy(int x,int y);	//___ key_cursor.cpp 에 정의
// 키 입력 받아오기											
int key_get();				//___ key_cursor.cpp 에 정의
// 커서위치 이동함수										
void move_point(int key);	//___ key_cursor.cpp 에 정의
// 현재 커서 위치가 게임판안에 존재하는지 체크하는 함수		
bool key_chk(int key);		//___ key_cursor.cpp 에 정의


// 기본 게임화면 출력			
void base_menu_print();				//___ init.cpp 에 정의
// game[][] 배열 전체에다가 랜덤한 값을 넣어줌
void block_all_reset();				//___ init.cpp 에 정의
// 게임을 생성함( 블럭데이터 삽입 )
void game_create();					//___ init.cpp 에 정의
// 블럭을 옮겨서 터트릴수 있는 블럭이 있는지 체크함수
bool pang_chk();					//___ init.cpp 에 정의
// 게임 시작함수
void game_start();					//___ init.cpp 에 정의


// 블럭 값에 따른 블럭 출력
void block_print(int block, bool select_chk);	//___ print.cpp 에 정의
// 남은 게임시간 출력과 시간이 다되면 종료값을 리턴해줌
int timer_print(int end_time);					//___ print.cpp 에 정의
// 콘솔화면 색상 출력 설정
void SetColor(int color , int bgcolor );		//___ print.cpp 에 정의
// 콤보수치 계산과 현재 콤보 수 출력
void combo_print();								//___ print.cpp 에 정의
// 게임 점수 계산과 게임점수 출력
void score_print(int pang_num);					//___ print.cpp 에 정의



// 비어있는 칸으로 위의 블럭들을 아래로 내림
// 위에서 아래로 내리는 경우이므로 x는 고정좌표로 주고
// y는 블럭이 없는 위치를 알려 줘야 하므로
// shift는 지금부터 몇칸 위에 블럭이 존재하는지 알려줌
// block_drop(int x고정좌표, int 땡기기 시작할 위치, 땡길 칸수)	
void block_drop(int x, int y, int shift);			//___ block_state_change_cpp 에 정의
// 스페이스바 입력후 방향키눌럿을때 바뀐 블럭들의 위치만 다시 표시해주는 함수
void block_position_change(int key);				//___ block_state_change_cpp 에 정의
// 블럭이 비어있을 경우 블럭 생성해줌	
void block_create(int i, int j);					//___ block_state_change_cpp 에 정의
// 해당 위치에 있는 블럭을 제거하고 게임 값을 삭제	
void block_delete(int x, int y);					//___ block_state_change_cpp 에 정의
// 블럭이 터졋을 경우 블럭데이터를 변경하고 터진모양으로 출력해줌
void block_pang(int x, int y);						//___ block_state_change_cpp 에 정의


// 터진 모양의 블럭들을 삭제하고 삭제한 갯수만큼 리턴해줌
int pang_delete();						//___ pang_bomb.cpp 에 정의
// 3개 이상의 연속된 블럭모양이 있을경우 터진모양으로 바꿔주고 연속된 블럭이 몇번있었는지 리턴해줌
int block_straight_chk(int bomb_chk);	//___ pang_bomb.cpp 에 정의
// 블럭을 터트리고 점수계산을하고 새로생성 등 터지는 부분을 함수로 뭉친부분
int pang_pang();						//___ pang_bomb.cpp 에 정의
// 폭탄을 선택햇을 경우 실행되는 폭탄동작함수
void bomb();							//___ pang_bomb.cpp 에 정의
// 게임이 종료된 후에 폭탄을 터트리고 점수계산을 해주는 함수
void end_bomb();							//___ pang_bomb.cpp 에 정의
/*
	�ۼ��� : ����ȭ

	���α׷����� : �ַܼ� �ִ��ΰ����� ����.

	���� ���� -	1. ������ ó�� �����Ҷ� ���� ������� �� ���ڿ��� 3���̻� �������� ������ �ȵ�.
				2. ���� �����߿� ��Ʈ������ ������ .  (��� ��Ʈ���� �ٽ� ��迭) or (�״��� ���� �迭�ȿ� ������ ��Ʈ������ �ֵ���)

	�ۼ��� : 12_1031
			ver_0.01
			���� -	1. �⺻���� ����Ű �ν�
					2. �⺻�޴�
					3. ���������� � ����.
					4. ����Ű(�ܼ� Ŀ��) �̵�
					5. ������� ����

	�ۼ��� : 12_1101
			ver_0.02
			���� -	1. �����̽��� �ν��� �������� ��ġ �ٲ㼭 ȭ�鿡 ����ϱ�
					2. ���� �ʱ� ��������
					3. ���� ȭ�� ���

	�ۼ��� : 12_1102
			ver_0.03
			���� -	1. ������ üũ�ؼ� ��Ʈ���� (���� ���� ��� ������ �˻��ؼ� �ѹ��� ��Ʈ���� �Լ��ۿ� ����.) // �׽�Ʈ ���ؔf��
					2. ������ ������� ���� �ִ� ������ �Ʒ��� ������ �Լ� // �׽�Ʈ ���ؔf��
					3. ���� ���°��� ���� �����ϱ�. // �׽�Ʈ ���ؔf��

	�ۼ��� : 12_1105
			ver_0.04
			���� -	1. ���� üũ�ؼ� ��Ʈ���� �Լ� // ���� �ٸ��Լ����� (3��),block_down����
					2. ���� �����ϴ� �Լ� ����
					3. ���� ������ �Ʒ��� ������ �Լ� ��������.

	�ۼ��� : 12_1107
			ver_0.05
			���� -	1. ���� ������ �Ʒ��� �������Լ� ���� �Ϸ�
					2. ������ �׷��� ������� ���� 70% (11��)
					3. ����� �Լ� ��������(12��)
					4. �� �����ٰ� ���� ���λ��� �����Ϸ� 100%

	�ۼ��� : 12_1110
			ver_0.06
			���� -	1. �޺� �����Ϸ�
					2. ���ھ� ��� �����Ϸ�
					3. Ÿ�̸� ���� �Ϸ�

	�ۼ��� : 12_1113
			ver_0.07
			���� -	1. ��ź ������ ������ ������ ����
					2. �����̽����Է½� Ŭ���� ��ġ�� ������ �����ϴ� �ǹ̷� ������ �ٲ���
					3. ���� �����Ұ� �ִ��� ������ ����ϴ� �Լ� ���� �Ϸ� (�� �׽�Ʈ�� ���� ��Ȯ����)

	�ۼ��� : 12_1115
			ver_0.08
			���� -	1. ������ �ִ��� ������ üũ�Լ�. �߰�������� �����Ƿ�. ���ǹ� �߰� �ʿ�
					2. ��ź���� ����� �Ϸ�.

	�ۼ��� : 12_1117
			ver_0.09
			���� -	1. ���� �Լ� ���� �����ϴ� ������ ���̴� ���ϵ� �����ϰ� �Լ��� ����
					2. �ҽ��ڵ� ��ġ ����
					3. ���� �ð� ������ ��ź ������ ��� ������ ���� �ö󰡴� ���α׷� �ۼ��Ϸ�
					4. ������ �մ��� ������ üũ�� ������� ����� ����Ϸ�
					5. put �Լ� ���� (put_power�� ����)

	�ۼ��� : 12_1119
			ver_1.00
			���� -	1. �Լ� �̸� ����

	�ۼ��� : 12_1122
			ver_1.01
			���� -	1. end_bomb() ���� �˰����� �ణ ����.
					2. pang_pang() ���� �˰����� �ణ ����.
					3. �����Լ� ���� ����ȭ

	�߰��ؾ��Ұ� -	 1. �⺻ �������̽�(����Ű�ν�,�׷���)						// 100%
					 2. �׷��� �̵�(�����̽��� �Է�����)						// 100%
					 3. �������� üũ �Լ�										// 100%		// 11�� ���� üũ�ؼ� �� ���� ���� �����ҵ�
					 4. ���� ��Ʈ���� �Լ�										// 100%
					 5. �ʱ� ���� ������ ��ġ�� ����� ������ �ʰ��ϱ�.			// ������ �ʿ����.. �׳� �����ϸ� �ɵ�. 100%
					 6. ������ ������� ���� �ִ� �������� �Ʒ��� ������		// 100%
					 7. ��ĭ ������� �װ��� ���ο� ������ ����					// 100%
					 8. ���ھ� ���.											// 100%
					 9. ���Ӽ��� �߰�.											// 50%
					10. ���ӽð� �˷��ִ� �� �߰�.								// 100%
					11. ������ �׷���. 100%	( ������ �Լ����� �ٷ� �����°� �ƴ϶� ��� ������ �ٸ����� ���� �ٸ� �׷����� �� ���¿���)
											( �� ���� �Լ��� ������ ��� �ش簪�� �������� ������� ȿ���� �����ҵ�.					 )
											( �� ������ ��ȣ�� ������ �ٸ� ��ȣ�� ������ ���� ������꿡 ��� �����ҵ�				 )
					12. ����� �Լ� �ٽø����( 11�� ������ )					// 100%
					13. 5�� �̻� ���������� ������� ��ź����					// 100%  �߰� ����� �ʿ������� ��
						13_1 - ��ź �ִ°����� �����̽��� �Է��� �ð�� ��ź�� �ٷ� ������ �ϱ�.	// 90% �߰� ����� �ʿ������� ��
					14. �޺� �ý����߰�											// 100%
					15. ��Ʈ�� ������ �������. ���� ��迭 or ���� ���� �������� ��Ʈ�� ���� �����.	// ������ ������ �˾Ƴ�����. �߿�
								// ������ ��� �ѹ��� ���ϱ�� ����			// 100%

*/

#include "head.h"

int point[2] = {0,};
int game[7][7] = {0,};
int score = 0;
int combo_cnt = 0;



int main()
{
	// rand�õ尪 �ʱ�ȭ
	srand( (unsigned int)time(NULL) );

	// ������ �ʱ� �޴� ������ֱ�
	SetColor(15 , 0 );
	base_menu_print();

	// ������ �ʱ� ���������ܵ� ������ֱ� ���ӻ���
	game_create();

	// ���� ����
	game_start();

	// ���� ����
	gotoxy(0,14);
	printf("���� �����Դϴ�. �����ִ� ��ź�� ��� �����ϴ�!!!\n");

	// ��Ʈ�� (�����ִ� ��ź�� ��� ������ ������ ȯ��)
	end_bomb();

	gotoxy(0,15);
	Sleep(3000);

	return 0;
}
// ���� �ڵ�
#pragma once

#include <time.h>
#include <stdlib.h>

int board_2020180001[19][19];


#define BLACK -1
#define WHITE 1

void WhiteAttack_2020180001(int* x, int* y)
{


	// ���÷� �׻� [5,5]���� ���� �ΰ���
	*x = 10;
	*y = 10;

	board_2020180001[*y][*x] = WHITE;
}
void WhiteDefence_2020180001(int x, int y)
{
	// ��밡 ���� ���� ��ġ�� ���޹޾Ƽ� �����մϴ�
	board_2020180001[y][x] = BLACK;
}

void BlackAttack_2020180001(int* x, int* y)
{
	srand((unsigned)time(NULL));
	int ranx = rand() % 19;
	int rany = rand() % 19;

	while (1)
	{
		if (board_2020180001[rany][ranx] != 0)
		{
			ranx = rand() % 19;
			rany = rand() % 19;
		}
		else break;
	}



	// ���÷� �׻� [5,5]���� ���� �ΰ���
	*x = ranx;
	*y = rany;

	board_2020180001[*y][*x] = BLACK;
}
void BlackDefence_2020180001(int x, int y)
{
	// ��밡 ���� ���� ��ġ�� ���޹޾Ƽ� �����մϴ�
	board_2020180001[y][x] = WHITE;
}
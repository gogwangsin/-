
#if 0

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "AI2sup.h"


void MakeGame(char Game[][19])
{

	for (int i = 0; i < 19; i++) {

		for (int k = 0; k < 19; k++) {

			Game[i][k] = '+';
			printf("%c", Game[i][k]);

		}
		printf("\n");
	}
	printf("\n");
}

void PrintGame(char Game[][19])
{
	for (int i = 0; i < 19; i++) {
		for (int k = 0; k < 19; k++) {
			printf("%c", Game[i][k]);
		}
		printf("\n");
	}
	printf("\n");

}


void menu(void)
{
	printf("=========================================\n");
	printf("0. �޴� ���� ���� �� �α�\n");
	printf("1. ��� ���μ��� �� �� ���\n");
	printf("2. �� ���� ���� ���� �� ���\n");
	printf("3. �� �밢�� ���� �� ���\n");
	printf("4. �� ���� ���� �� ��ǥ ���\n");
	printf("5. ���� ����\n");
	printf("=========================================\n");
	printf("��ɾ� �Է� : ");

}
void EveryCount(char Game[][19])
{
	printf("================== 1 =====================\n");

	for (int i = 0; i < 19; i++)
	{
		int countB = 0, countW = 0; // �ʱ�ȭ ���� 

		for (int k = 0; k < 19; k++)
		{
			if (Game[i][k] == 'B') countB++;
			if (Game[i][k] == 'W') countW++;
		}
		printf("���� %02d��° : B : %d W : %d\n", i, countB, countW);
	}
	printf("=========================================\n");

	for (int i = 0; i < 19; i++)
	{
		int countB = 0, countW = 0;

		for (int k = 0; k < 19; k++)
		{
			if (Game[k][i] == 'B') countB++;
			if (Game[k][i] == 'W') countW++;
		}
		printf("���� %02d��° : B : %d W : %d\n", i, countB, countW);
	}
	printf("=========================================\n");


}

void CheckA(char Game[][19])
{
	printf("=========================================\n");
	for (int i = 0; i < 19; i++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0;

		for (int k = 0; k < 19; k++)
		{
			if (Game[k][i] == 'B')
			{
				countB++;
				countW = 0; // �ʱ�ȭ ���� 
				if (countB > sumB) sumB = countB;
			}
			else if (Game[k][i] == 'W')
			{
				countW++;
				countB = 0;
				if (countW > sumW)sumW = countW;
			}
			else
			{
				countW = 0, countB = 0;
			}
		}

		if (sumB > 1 || sumW > 1) // ��±��� ������ 1���� ũ�� 
		{
			printf("���� %02d��° �ִ� ���� �� : ", i); // ���η� ���°� ���� 
			if (sumB > sumW) printf("B : %d", sumB);
			if (sumB < sumW) printf("W : %d", sumW);
			if (sumB == sumW) printf("B : %d, W : %d", sumB, sumW);
			printf("\n");
		}
	}
	printf("=========================================\n");


}
void CheckB(char Game[][19])
{
	printf("=========================================\n");
	for (int i = 0; i < 19; i++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0;

		for (int k = 0; k < 19; k++)
		{
			if (Game[i][k] == 'B')
			{
				countB++;
				countW = 0;
				if (countB > sumB) sumB = countB;
			}
			else if (Game[i][k] == 'W')
			{
				countW++;
				countB = 0;
				if (countW > sumW)sumW = countW;
			}
			else
			{
				countW = 0, countB = 0;
			}
		}

		if (sumB > 1 || sumW > 1)
		{
			printf("���� %02d��° �ִ� ���� �� : ", i);
			if (sumB > sumW) printf("B : %d", sumB);
			if (sumB < sumW) printf("W : %d", sumW);
			if (sumB == sumW) printf("B : %d, W : %d", sumB, sumW);
			printf("\n");
		}
	}
	printf("=========================================\n");


}

void CheckRTLB(char Game[][19])
{
	printf("=========================================\n");

	for (int i = 18, k = 0; i >= 0; i--, k++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0;


		for (int y = 0; y < 2 * k; y++)
		{
			if (y < 19 && i + y < 19) {
				if (Game[0 + y][i + y] == 'B')
				{
					countB++;
					countW = 0;
					if (countB > sumB) sumB = countB;
				}
				else if (Game[0 + y][i + y] == 'W')
				{
					countW++;
					countB = 0;
					if (countW > sumW) sumW = countW;
				}
			}
		}
		if (sumB > 1 || sumW > 1) {
			printf("���� %02d��° �밢�� : ", k);
			if (sumB > sumW) printf("B : %d", sumB);
			if (sumW > sumB) printf("W : %d", sumW);
			if (sumB == sumW) printf("B : %d, W : %d", sumB, sumW);
			printf("\n");
		}
	}


	for (int i = 18, k = 0; i > 0; i--, k++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0;


		for (int y = 0; y < 2 * k; y++)
		{
			if (i + y < 19 && y < 19) {
				if (Game[i + y][y] == 'B')
				{
					countB++;
					countW = 0;
					if (countB > sumB) sumB = countB;
				}
				else if (Game[i + y][y] == 'W')
				{
					countW++;
					countB = 0;
					if (countW > sumW) sumW = countW;
				}
			}
		}
		if (sumB > 1 || sumW > 1) {
			printf("���ϴ� %02d��° �밢�� : ", k);
			if (sumB > sumW) printf("B : %d", sumB);
			if (sumW > sumB) printf("W : %d", sumW);
			if (sumB == sumW) printf("B : %d, W : %d", sumB, sumW);
			printf("\n");
		}
	}
	printf("=========================================\n");

}
void CheckRBLT(char Game[][19])
{
	printf("=========================================\n");

	for (int i = 18, k = 0; i >= 0; i--, k++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0;


		for (int y = 0; y < 2 * k; y++)
		{
			if (18 - y >= 0 && i + y < 19) {
				if (Game[18 - y][i + y] == 'B')
				{
					countB++;
					countW = 0;
					if (countB > sumB) sumB = countB;
				}
				else if (Game[18 - y][i + y] == 'W')
				{
					countW++;
					countB = 0;
					if (countW > sumW) sumW = countW;
				}
			}
		}
		if (sumB > 1 || sumW > 1) {
			printf("���ϴ� %02d��° �밢�� : ", k);
			if (sumB > sumW) printf("B : %d", sumB);
			if (sumW > sumB) printf("W : %d", sumW);
			if (sumB == sumW) printf("B : %d, W : %d", sumB, sumW);
			printf("\n");
		}
	}


	for (int i = 18, k = 0; i > 0; i--, k++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0;


		for (int y = 0; y < 2 * k; y++)
		{
			if (k - y >= 0 && y <= 18) { // <18�� �����Ͱ�����
				if (Game[k - y][y] == 'B')
				{
					countB++;
					countW = 0;
					if (countB > sumB) sumB = countB;
				}
				else if (Game[k - y][y] == 'W')
				{
					countW++;
					countB = 0;
					if (countW > sumW) sumW = countW;
				}
			}
		}
		if (sumB > 1 || sumW > 1) {
			printf("�»�� %02d��° �밢�� : ", k);
			if (sumB > sumW) printf("B : %d", sumB);
			if (sumW > sumB) printf("W : %d", sumW);
			if (sumB == sumW) printf("B : %d, W : %d", sumB, sumW);
			printf("\n");
		}
	}
	printf("=========================================\n");

}

void CheckBindex(char Game[][19])
{
	LIST list[19][19] = { 0 };
	printf("=========================================\n");

	for (int i = 0; i < 19; i++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0;

		for (int k = 1; k < 19; k++)
		{
			if (k - 1 == 0)
			{
				if (Game[i][k - 1] == 'B')
				{
					countB++;

					list[i][k - 1].state = 'B';
					list[i][k - 1].combo = ++sumB;
					list[i][k - 1].Y = i;
					list[i][k - 1].X = 0;
				}
				else if (Game[i][k - 1] == 'W')
				{
					countW++;
					list[i][k - 1].state = 'W';
					list[i][k - 1].combo = ++sumW;
					list[i][k - 1].Y = i;
					list[i][k - 1].X = 0;
				}
			}

			if (Game[i][k] == Game[i][k - 1])
			{
				if (Game[i][k] == 'B')
				{
					countB++;
					sumB = countB; // �޺����⼭ �����ؼ� �ؿ��� �����ϸ� �ɵ� 
					list[i][k].state = 'B';
					list[i][k].combo = sumB;
					list[i][k].Y = i;
					list[i][k].X = k;
				}
				else if (Game[i][k] == 'W')
				{
					countW++;
					sumW = countW;
					list[i][k].state = 'W';
					list[i][k].combo = sumW;
					list[i][k].Y = i;
					list[i][k].X = k;
				}
			}
			else if (Game[i][k] != Game[i][k - 1]) // �ٸ��� sum������ �̻����� -> sum�� �޺��ϱ� �ǵ��� ���� �� �������� => 
			{
				if (Game[i][k] == 'B')
				{
					countW = 0; // count�� �����϶��� sum
					countB = 1;

					list[i][k].state = 'B';
					list[i][k].combo = countB; //cb,cw,comb�� ��� ������ -> ���⼭ �޺� �������ص� ������ ������ 
					list[i][k].Y = i;
					list[i][k].X = k;
				}
				else if (Game[i][k] == 'W')
				{
					countB = 0;
					countW = 1;

					list[i][k].state = 'W';
					list[i][k].combo = countW;
					list[i][k].Y = i;
					list[i][k].X = k;
				}
			}

		}

		int max = 0;
		for (int k = 0; k < 19; k++)
		{
			if (list[i][k].combo > max) max = list[i][k].combo;
		}

		for (int k = 0; k < 19; k++)
		{
			if (max > 1 && list[i][k].combo == max)
			{
				printf("���� %02d��° ���� �� ��ǥ : ", i);

				if (list[i][k].state == 'B')
				{
					printf("B(Y,X) : ");
					for (int j = k + 1 - list[i][k].combo; j <= k; j++)
					{
						printf("(%d,%d) ", list[i][j].Y, list[i][j].X);
					}
				}

				if (list[i][k].state == 'W')
				{
					printf("W(Y,X) : ");
					for (int j = k + 1 - list[i][k].combo; j <= k; j++)
					{
						printf("(%d,%d) ", list[i][j].Y, list[i][j].X);
					}
				}
				if (list[i][k].state != 0) printf("\n");
			}
		}
	}
	printf("=========================================\n");


}



#endif


#if 0

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include"AIsup.h"



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




void EveryCOUNT(char Game[][19])
{
	int countB = 0, countW = 0;

	printf("================ 1 ==================\n");
	for (int i = 0; i < 19; i++)
	{
		for (int k = 0; k < 19; k++)
		{
			if (Game[i][k] == 'B') countB++;
			if (Game[i][k] == 'W') countW++;
		}

		printf("���� %02d��°�� : B: %d, W : %d\n", i, countB, countW);  // �� �ѹ� Ž���ϰ� ���� �ʱ�ȭ
		countB = 0;
		countW = 0;
	}
	printf("====================================\n");

	for (int i = 0; i < 19; i++)
	{
		for (int k = 0; k < 19; k++)
		{
			if (Game[k][i] == 'B') countB++;
			if (Game[k][i] == 'W') countW++; // ���δ� i,k�ٲ㼭
		}

		printf("���� %02d��°�� : B: %d, W : %d\n", i, countB, countW); // ���η� 1 �Ʒ�, 2 �Ʒ�..
		countB = 0;
		countW = 0;
	}
	printf("====================================\n");

}
void menu(void)
{
	printf("====================================\n");
	printf("0. �޴� ���� ���� �� �α�\n");
	printf("1. ���� ���� ��,�� �� ����\n");
	printf("2. ���� ���� ���� �� ���\n");
	printf("3. �밢�� ���� �� ���\n");
	printf("4. ���� ���� ���ӵ� ������ ��ǥ�� ����\n");
	printf("5. ������ �����մϴ�\n");
	printf("====================================\n");
	printf("��ɾ� �Է� : ");

}



void CheckA(char Game[][19])
{
	LIST list[19][19] = { 0 };

	printf("============ 2. ���� ���� ==================\n");

	for (int i = 0; i < 19; i++)
	{
		int sumB = 0, sumW = 0;
		int countB = 0, countW = 0;

		for (int k = 1; k < 19; k++)
		{
			if (k - 1 == 0) // 0�϶� ��ġ���� 
			{
				if (Game[k - 1][i] == 'W')
				{

					countW++;
					list[k - 1][i].combo = ++sumW;
					list[k - 1][i].state = 'W';
					list[k - 1][i].Y = k - 1;
					list[k - 1][i].X = i;

				}
				else if (Game[k - 1][i] == 'B')
				{
					countB++;
					list[k - 1][i].combo = ++sumB;
					list[k - 1][i].state = 'B';
					list[k - 1][i].Y = k - 1;
					list[k - 1][i].X = i;

				}

			}
			if (Game[k][i] == Game[k - 1][i]) // 1���� ���� ���� �� �� 
			{
				if (Game[k][i] == 'W')
				{
					countW++;
					sumW = countW;
					list[k][i].combo = sumW;
					list[k][i].state = 'W';
					list[k][i].Y = k;
					list[k][i].X = i;
				}
				else if (Game[k][i] == 'B') // else ���ϸ� 0,0�Ǽ� �޺��� �ȵ� 
				{
					countB++;
					sumB = countB;
					list[k][i].combo = sumB;
					list[k][i].state = 'B';
					list[k][i].Y = k;
					list[k][i].X = i;
				}
			}
			else if (Game[k][i] != Game[k - 1][i]) // 1���� ���� ���� �� �� 
			{
				if (Game[k][i] == 'W')
				{
					countW = 1;
					countB = 0;

					list[k][i].combo = countW;
					list[k][i].state = 'W';
					list[k][i].Y = k;
					list[k][i].X = i;
				}
				else if (Game[k][i] == 'B')
				{
					countB = 1;
					countW = 0;

					list[k][i].combo = countB;
					list[k][i].state = 'B';
					list[k][i].Y = k;
					list[k][i].X = i;
				}
			}

		}

		int max = 0;
		for (int k = 0; k < 19; k++)
		{
			if (list[k][i].combo > max) max = list[k][i].combo;
		}

		for (int k = 0; k < 19; k++)
		{
			if (max != 0 && list[k][i].combo == max)
			{
				printf("%d���� : ", i); //%02d, i����
				if (list[k][i].state == 'B')
				{
					printf("%c %d", list[k][i].state, list[k][i].combo);
				}

				if (list[k][i].state == 'W')
				{
					printf("%c %d", list[k][i].state, list[k][i].combo);
				}
				if (list[k][i].state != 0)
				{
					printf("\n");
				}
			}
		}

	}
	printf("=========================================\n");

}
void CheckB(char Game[][19]) // ���� [����][����] 
{
	LIST list[19][19] = { 0 };

	printf("============ 2. ���� ���� ==================\n");

	for (int i = 0; i < 19; i++)
	{
		int sumB = 0, sumW = 0;
		int countB = 0, countW = 0;

		for (int k = 1; k < 19; k++)
		{
			if (k - 1 == 0) // 0�϶� ��ġ���� 
			{
				if (Game[i][k - 1] == 'W')
				{

					countW++;
					list[i][k - 1].combo = ++sumW;
					list[i][k - 1].state = 'W';
					list[i][k - 1].Y = i;
					list[i][k - 1].X = k - 1;

				}
				else if (Game[i][k - 1] == 'B')
				{
					countB++;
					list[i][k - 1].combo = ++sumB;
					list[i][k - 1].state = 'B';
					list[i][k - 1].Y = i;
					list[i][k - 1].X = k - 1;

				}

			}
			if (Game[i][k] == Game[i][k - 1]) // 1���� ���� ���� �� �� 
			{
				if (Game[i][k] == 'W')
				{
					countW++;
					sumW = countW;
					list[i][k].combo = sumW;
					list[i][k].state = 'W';
					list[i][k].Y = i;
					list[i][k].X = k;
				}
				else if (Game[i][k] == 'B')
				{
					countB++;
					sumB = countB;
					list[i][k].combo = sumB;
					list[i][k].state = 'B';
					list[i][k].Y = i;
					list[i][k].X = k;
				}
			}
			else if (Game[i][k] != Game[i][k - 1]) // 1���� ���� ���� �� �� 
			{
				if (Game[i][k] == 'W')
				{
					countW = 1;
					countB = 0;

					list[i][k].combo = countW;
					list[i][k].state = 'W';
					list[i][k].Y = i;
					list[i][k].X = k;
				}
				else if (Game[i][k] == 'B')
				{
					countB = 1;
					countW = 0;

					list[i][k].combo = countB;
					list[i][k].state = 'B';
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
			if (max != 0 && list[i][k].combo == max)
			{
				printf("%d���� : ", i);
				if (list[i][k].state == 'B')
				{
					printf("%c %d", list[i][k].state, list[i][k].combo);
				}

				if (list[i][k].state == 'W')
				{
					printf("%c %d", list[i][k].state, list[i][k].combo);
				}
				if (list[i][k].state != 0)
				{
					printf("\n");
				}
			}
		}

	}
	printf("=========================================\n");

}

void CheckRTLB(char Game[][19])
{
	printf("======= �밢 ���� ���� ==============\n");

	for (int i = 18, k = 0; i >= 0; i--, k++) // 18 17 16.... 1  ������ y=0, x 18--, Ȯ���� +,+, ���� x=18, y-- => 2���� Ȯ�μ� �þ 
	{
		int sumB = 0, sumW = 0;
		int countB = 0, countW = 0;

		for (int y = 0; y < 2 * k; y++) // ++ ������ y�� ǥ���ϰ� [0++][18-- 0++] �������� --�ǰ� Ȯ������ ++, �ִ�Ȯ�� +2��
		{

			if (y < 19 && i + y < 19) {// ���⼭ 2*k 36�Ǽ� �ε����� ħ���ϴϱ� y�� �����Ǵϱ� ���ƾ��� y�� ���� ������ ���͙VƮ

				if (Game[0 + y][i + y] == 'B') // y 0���� Ž��, �������� 18--
				{
					countW = 0;
					countB++;
					if (countB > sumB) sumB = countB;

				}
				else if (Game[0 + y][i + y] == 'W')
				{
					countB = 0;
					countW++;
					if (countW > sumW) sumW = countW;
				}
				else
				{
					countW = 0, countB = 0;
				}
			}
		}

		if (sumB > 0 || sumW > 0)
		{
			printf("���� %d��° �밢�� : ", k);// k��°��°͵� ������ 
			if (sumB > sumW) printf("B : %d\n", sumB);
			else if (sumB < sumW) printf("W : %d\n", sumW);
			else printf("B : %d, W : %d\n", sumB, sumW);
		}

	}

	// 0�Ȱ�ġ��
	for (int i = 18, k = 0; i > 0; i--, k++) // 18,0 17,0, 16,0 -> ++. 18 1 18 2 18 3 ..
	{
		int sumB = 0, sumW = 0;
		int countB = 0, countW = 0;

		for (int y = 0; y < 2 * k; y++)
		{
			if (y < 19 && i + y < 19) {

				if (Game[i + y][y + 0] == 'B')
				{
					countW = 0;
					countB++;
					if (countB > sumB) sumB = countB;

				}
				else if (Game[i + y][y + 0] == 'W')
				{
					countB = 0;
					countW++;
					if (countW > sumW) sumW = countW;
				}
				else
				{
					countW = 0, countB = 0;
				}
			}
		}

		if (sumB > 0 || sumW > 0)
		{
			printf("���ϴ� %d��° �밢�� : ", k);
			if (sumB > sumW) printf("B : %d\n", sumB);
			else if (sumB < sumW) printf("W : %d\n", sumW);
			else printf("B : %d, W : %d\n", sumB, sumW);
		}

	}
	printf("=========================================\n");

}
void CheckRBLT(char Game[][19])
{

	for (int i = 18, k = 0; i > 0; i--, k++) // 18 17 16.... 1  ������ y=0, x 18--, Ȯ���� +,+, ���� x=18, y-- => 2���� Ȯ�μ� �þ 
	{
		int sumB = 0, sumW = 0;
		int countB = 0, countW = 0;

		for (int y = 0; y < 2 * k; y++) // ++ ������ y�� ǥ���ϰ� [0++][18-- 0++] �������� --�ǰ� Ȯ������ ++, �ִ�Ȯ�� +2��
		{
			if (y < 19 && k - y >= 0) {
				if (Game[k - y][0 + y] == 'B')
				{
					countW = 0;
					countB++;
					if (countB > sumB) sumB = countB;

				}
				else if (Game[k - y][0 + y] == 'W')
				{
					countB = 0;
					countW++;
					if (countW > sumW) sumW = countW;
				}
				else
				{
					countW = 0, countB = 0;
				}
			}

		}

		if (sumB > 0 || sumW > 0)
		{
			printf("�»�� %d��° �밢�� : ", k);
			if (sumB > sumW) printf("B : %d\n", sumB);
			else if (sumB < sumW) printf("W : %d\n", sumW);
			else printf("B : %d, W : %d\n", sumB, sumW);
		}

	}


	for (int i = 18, k = 0; i >= 0; i--, k++) // 18,0 17,0, 16,0 -> ++. 18 1 18 2 18 3 ..
	{
		int sumB = 0, sumW = 0;
		int countB = 0, countW = 0;

		for (int y = 0; y < 2 * k; y++)
		{
			if (18 - y >= 0 && i + y < 19) {

				if (Game[18 - y][i + y] == 'B')
				{
					countW = 0;
					countB++;
					if (countB > sumB) sumB = countB;

				}
				else if (Game[18 - y][i + y] == 'W')
				{
					countB = 0;
					countW++;
					if (countW > sumW) sumW = countW;
				}
				else
				{
					countW = 0, countB = 0;
				}
			}

		}

		if (sumB > 0 || sumW > 0)
		{
			printf("���ϴ� %d��° �밢�� : ", k);
			if (sumB > sumW) printf("B : %d\n", sumB);
			else if (sumB < sumW) printf("W : %d\n", sumW);
			else printf("B : %d, W : %d\n", sumB, sumW);
		}

	}
	printf("=========================================\n");


}

void CheckBindex(char Game[][19])
{
	LIST list[19][19] = { 0 };

	printf("============ 4. ���� ��ǥ ==================\n");

	for (int i = 0; i < 19; i++)
	{
		int sumB = 0, sumW = 0;
		int countB = 0, countW = 0;

		for (int k = 1; k < 19; k++)
		{
			if (k - 1 == 0) // 0�϶� ��ǥ ��� -> 2���� ���ϸ� 1���� �����ϰ� ���� ���� ������ ���ܼ� ä������ 
			{
				if (Game[i][k - 1] == 'W')
				{

					countW++;
					list[i][k - 1].combo = ++sumW;
					list[i][k - 1].state = 'W';
					list[i][k - 1].Y = i;
					list[i][k - 1].X = k - 1;

				}
				else if (Game[i][k - 1] == 'B')
				{
					countB++;
					list[i][k - 1].combo = ++sumB;
					list[i][k - 1].state = 'B';
					list[i][k - 1].Y = i;
					list[i][k - 1].X = k - 1;

				}

			}
			if (Game[i][k] == Game[i][k - 1]) // 1���� ���� ���� �� �� 
			{
				if (Game[i][k] == 'W')
				{
					countW++;
					sumW = countW;
					list[i][k].combo = sumW;
					list[i][k].state = 'W';
					list[i][k].Y = i;
					list[i][k].X = k;
				}
				else if (Game[i][k] == 'B')
				{
					countB++;
					sumB = countB;
					list[i][k].combo = sumB;
					list[i][k].state = 'B';
					list[i][k].Y = i;
					list[i][k].X = k;
				}
			}
			else if (Game[i][k] != Game[i][k - 1]) // 1���� ���� ���� �� �� 
			{ // �޺� �ʱ�ȭ -> list�� ������� ���� �������� �����ؼ� �ʱ�ȭ�� �̶� �ؾ��� -> ���� ���� ����Ǵ±��� 
				if (Game[i][k] == 'W')
				{
					countW = 1;
					countB = 0;

					list[i][k].combo = countW;
					list[i][k].state = 'W';
					list[i][k].Y = i;
					list[i][k].X = k;
				}
				else if (Game[i][k] == 'B')
				{
					countB = 1;
					countW = 0;

					list[i][k].combo = countB;
					list[i][k].state = 'B';
					list[i][k].Y = i;
					list[i][k].X = k;
				}
			}

		}

		int max = 0;
		for (int k = 0; k < 19; k++)
		{
			if (list[i][k].combo > max) max = list[i][k].combo;//list combo�� ū�� ���� 
		}

		for (int k = 0; k < 19; k++)
		{
			if (max != 0 && list[i][k].combo == max) //// �ִ밡 >1�� �ٲ��� 
			{
				printf("%d���� : ", i);
				if (list[i][k].state == 'B')
				{
					printf("B(Y,X) : ");
					for (int j = k + 1 - list[i][k].combo; j <= k; j++) // �޺� 3�̶��Ҷ� 3, 2, 1,
					{
						printf("(%d,%d)", list[i][j].Y, list[i][j].X);

					}
				}
				// else �Ⱥٴ°� -> B, W������� ����ϰ� 
				if (list[i][k].state == 'W')
				{
					printf("W(Y,X) : ");
					for (int j = k + 1 - list[i][k].combo; j <= k; j++) // �޺� 3�̶��Ҷ� 3, 2, 1,
					{
						printf("(%d,%d)", list[i][j].Y, list[i][j].X);

					}// �ε��� +1 �ؼ� �� ��ġ���� �޺���ŭ +1�ϴ°� 0��° ĭ �������� j<=k�� k�϶� combo�ִ�ġ��
				}
				if (list[i][k].state != 0)
				{
					printf("\n"); // ���� 0�ƴ� -> b,w�� ������ �� ������ 
				}
			}
		}

	}
	printf("=========================================\n");

}


/*

�׻� ������ �Ⱥ��ϴ°� 0 or 18 or i or k
���� �����ϴ°� y
i = 18, i++, k-- y++ y<2*k ( 0�϶�x)
RTLB
[0+y][i+y]
[i+y][y+0]

RBLT
[18-y][i+y]
[k-y][y]*/






#endif

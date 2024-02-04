
#if 1

typedef struct LIST {

	char state;
	int Y, X;
	int combo;

}LIST;


void MakeGame(char Game[][19]);
void PrintGame(char Game[][19]);

void menu(void);
void EveryCount(char Game[][19]);

void CheckA(char Game[][19]);
void CheckB(char Game[][19]);

void CheckRTLB(char Game[][19]);
void CheckRBLT(char Game[][19]);

void CheckBindex(char Game[][19]);


#endif

/*


/*


void menu(void)
{
	printf("=========================================\n");
	printf("0. �޴� ���� ���� �� �α�\n");
	printf("1. ���� ���� ��,�� �� ����\n");
	printf("2. ���� ���� ���� �� ����\n");
	printf("3. �밢�� ���� �� ���\n");
	printf("4. ��� ������ ���� �� ��ǥ\n");
	printf("5. ���� ����\n");
	printf("=========================================\n");
	printf("��ɾ� �Է� : ");
}



void EveryCount(char Game[][19])
{
	int countB = 0, countW = 0;

	printf("=========================================\n");
	for (int i = 0; i < 19; i++)
	{
		for (int k = 0; k < 19; k++)
		{
			if (Game[i][k] == 'B') countB++;
			if (Game[i][k] == 'W') countW++;
		}
		printf("���� %02d��°�� : B %d, W : %d\n", i, countB, countW); // �� �ѹ� Ž���ϰ� ���� �ʱ�ȭ
		countB = 0;
		countW = 0;
	}
	printf("=========================================\n");
	for (int i = 0; i < 19; i++)
	{
		for (int k = 0; k < 19; k++)
		{
			if (Game[k][i] == 'B') countB++;
			if (Game[k][i] == 'W') countW++;
		}
		printf("���� %02d��°�� : B %d, W : %d\n", i, countB, countW); // ���δ� i,k�ٲ㼭
		countB = 0;
		countW = 0;
	}
	printf("=========================================\n");


}

void CheckA(char Game[][19])
{
	printf("=========================================\n");

	for (int i = 0; i < 19; i++)
	{
		int sumB = 0, sumW = 0, countB = 0, countW = 0;

		for (int k = 0; k < 19; k++)
		{
			if (Game[k][i] == 'B')
			{
				countB++;
				countW = 0;
				if (countB > sumB) sumB = countB;
			}
			else if (Game[k][i] == 'W') // else ���ϸ� 0,0�Ǽ� �޺��� �ȵ�
			{
				countW++;
				countB = 0;
				if (countW > sumW) sumW = countW;
			}
			else
			{
				countW = 0, countB = 0;
			}

		}

		if (sumB > 0 || sumW > 0) // ���趧�� >1�� ������
		{
			printf("���� %02d��° �ִ� ���� �� : ", i);
			if (sumB > sumW) printf("B : %d", sumB);
			if (sumW > sumB)printf("W : %d", sumW);
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
		int sumB = 0, sumW = 0, countB = 0, countW = 0;

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
				if (countW > sumW) sumW = countW;
			}
			else
			{
				countW = 0, countB = 0;
			}

		}

		if (sumB > 0 || sumW > 0)
		{
			printf("���� %02d��° �ִ� ���� �� : ",i); //%02d, i����
			if (sumB > sumW) printf("B : %d", sumB);
			if (sumW > sumB)printf("W : %d", sumW);
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
		int sumB = 0, sumW = 0, countB = 0, countW = 0;

		for (int y = 0; y < 2 * k; y++) // ���⼭ 2*k 36�Ǽ� �ε����� ħ���ϴϱ� y�� �����Ǵϱ� ���ƾ��� y�� ���� ������ ���͙VƮ
		{
			if (y < 19 && i + y < 19) {

				if (Game[0 + y][i + y] == 'B')
				{
					countW = 0;
					countB++;
					if (countB > sumB)sumB = countB;
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
			printf("���� %02d��° �밢�� : ",k); // k��°��°͵� ������
			if (sumB > sumW) printf("B : %d\n", sumB);
			if (sumW > sumB) printf("W : %d\n", sumW);
			else printf("B : %d, W : %d\n", sumB, sumW);
		}
	}

	for (int i = 18, k = 0; i > 0; i--, k++) // 0�Ȱ�ġ��
	{
		int sumB = 0, sumW = 0, countB = 0, countW = 0;

		for (int y = 0; y < 2 * k; y++) // ���⼭ 2*k 36�Ǽ� �ε����� ħ���ϴϱ� y�� �����Ǵϱ� ���ƾ��� y�� ���� ������ ���͙VƮ
		{
			if (y < 19 && i + y < 19) {

				if (Game[i + y][0 + y] == 'B')
				{
					countW = 0;
					countB++;
					if (countB > sumB)sumB = countB;
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
			printf("���ϴ� %02d��° �밢�� : ", k); // k��°��°͵� ������
			if (sumB > sumW) printf("B : %d\n", sumB);
			if (sumW > sumB) printf("W : %d\n", sumW);
			else printf("B : %d, W : %d\n", sumB, sumW);
		}
	}
	printf("=========================================\n");



}
void CheckRBLT(char Game[][19])
{
	printf("=========================================\n");

	for (int i = 18, k = 0; i >= 0; i--, k++)
	{
		int countB = 0, countW = 0, sumW = 0, sumB = 0;

		for (int y = 0; y < 2 * k; y++)
		{
			if (k-y >= 0 &&  y < 19) {

				if (Game[k-y][y] == 'B')
				{
					countB++;
					countW = 0;
					if (countB > sumB) sumB = countB;
				}
				else if (Game[k-y][y] == 'W')
				{
					countW++;
					countB = 0;
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
			printf("���ϴ� %02%d��° �밢�� : ", k);
			if (sumB > sumW) printf("B : %d\n", sumB);
			if (sumW > sumB) printf("W : %d\n", sumW);
			else printf("B : %d, W : %d\n", sumB, sumW);
		}
	}

	for (int i = 18, k = 0; i >= 0; i--, k++)
	{
		int countB = 0, countW = 0, sumW = 0, sumB = 0;

		for (int y = 0; y < 2 * k; y++)
		{
			if (18 - y >= 0 && i + y < 19) {

				if (Game[18 - y][y + i] == 'B')
				{
					countB++;
					countW = 0;
					if (countB > sumB) sumB = countB;
				}
				else if (Game[18 - y][y + i] == 'W')
				{
					countW++;
					countB = 0;
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
			printf("���ϴ� %02%d��° �밢�� : ",k);
			if (sumB > sumW) printf("B : %d\n", sumB);
			if (sumW > sumB) printf("W : %d\n", sumW);
			else printf("B : %d, W : %d\n", sumB, sumW);
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
		int sumB = 0, sumW = 0, countB = 0, countW = 0;

		for (int k = 1; k < 19; k++)
		{

			if (k - 1 == 0) // 0�϶� ��ǥ ��� -> 2���� ���ϸ� 1���� �����ϰ� ���� ���� ������ ���ܼ� ä������
			{
				if (Game[i][k - 1] == 'W')
				{
					countW++;
					list[i][k - 1].state = 'W';
					list[i][k - 1].combo = 1; // �޺� 1
					list[i][k - 1].Y = i;
					list[i][k - 1].X = 0;
				}
				else if (Game[i][k - 1] == 'B')
				{
					countB++;
					list[i][k - 1].state = 'B';
					list[i][k - 1].combo = 1;
					list[i][k - 1].Y = i;
					list[i][k - 1].X = 0;
				}
			}

			if (Game[i][k] == Game[i][k - 1])
			{
				if (Game[i][k] == 'W')
				{
					countW++;
					sumW = countW;
					list[i][k].state = 'W';
					list[i][k].combo = sumW; // �޺�
					list[i][k].Y = i;
					list[i][k].X = k;
				}
				else if (Game[i][k] == 'B')
				{
					countB++;
					sumB = countB;
					list[i][k].state = 'B';
					list[i][k].combo = sumB;
					list[i][k].Y = i;
					list[i][k].X = k;
				}

			}
			else if (Game[i][k] != Game[i][k - 1])
			{
				if (Game[i][k] == 'W')
				{
					countW = 1; // �޺� �ʱ�ȭ -> list�� ������� ���� �������� �����ؼ� �ʱ�ȭ�� �̶� �ؾ��� -> ���� ���� ����Ǵ±���
					countB = 0;
					list[i][k].state = 'W';
					list[i][k].combo = countW;
					list[i][k].Y = i;
					list[i][k].X = k;
				}
				else if (Game[i][k] == 'B')
				{
					countW = 0;
					countB = 1;
					list[i][k].state = 'B';
					list[i][k].combo = countB;
					list[i][k].Y = i;
					list[i][k].X = k;
				}
			}

		}

		int max = 0;
		for (int k = 0; k < 19; k++)
		{
			if (list[i][k].combo > max) max = list[i][k].combo; //list combo�� ū�� ����
		}

		for (int k = 0; k < 19; k++)
		{
			if (max != 0 && list[i][k].combo == max) // �ִ밡 >1�� �ٲ���
			{
				printf("%02d���� : ", i);
				if (list[i][k].state == 'B')
				{
					printf("B(X,Y) : ");
					for (int j = k - list[i][k].combo + 1; j <= k; j++)
					{
						printf("(%d,%d)", list[i][j].Y, list[i][j].X);
					}
				}

				if (list[i][k].state == 'W') // else �Ⱥٴ°� -> B, W������� ����ϰ�
				{
					printf("W(X,Y) : ");
					for (int j = k - list[i][k].combo + 1; j <= k; j++) // �ε��� +1 �ؼ� �� ��ġ���� �޺���ŭ +1�ϴ°� 0��° ĭ �������� j<=k�� k�϶� combo�ִ�ġ��
					{
						printf("(%d,%d)", list[i][j].Y, list[i][j].X);
					}
				}

				if (list[i][k].state != 0) printf("\n"); // ���� 0�ƴ� -> b,w�� ������ �� ������
			}
		}

	}
	printf("=========================================\n");


}


*/
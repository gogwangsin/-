#if 1

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
//#include "AI7sup.h"

typedef struct STONE {

	int y, x;
	char team;

}STONE;

typedef struct STACK {

	STONE stone;
	struct STACK* next;

}STACK;

typedef struct LIST {

	char state;
	int Y, X;
	int combo;

}LIST;

STACK* pushStone(STACK* top, int y, int x, char team, int* count);
void printStack(STACK* top, int count);
void PrintGame(char Game[][19], STACK* top);
STACK* popStone(STACK** top, int* count, char Game[][19]);


void MakeGame(char Game[][19]);
void menu(void);
void EveryCount(char Game[][19]);
void CheckA(char Game[][19]);
void CheckB(char Game[][19]);
void CheckRTLB(char Game[][19]);
void CheckRBLT(char Game[][19]);
void CheckBindex(char Game[][19]);

char Game[19][19];

STACK* push2(STACK* back)
{


	return back;
}

int main(void)
{
	MakeGame(Game);

	STACK* top = NULL;
	int count = 0;

	STACK* back = NULL; // ������ ������ ���� 
	STACK* temp = NULL;

	printf("\nó�� ������ ���� �� �Դϴ�.\n");

	for (int i = 1; i <= 361; i++)
	{
		menu();
		int choice;
		if (scanf("%d", &choice) != 1)
		{
			printf("�Է� ����\n");
			exit(1);
		}fgetc(stdin);

		switch (choice)
		{
		case 0: break;
		case 1: EveryCount(Game); i--; continue;
		case 2: CheckB(Game); CheckA(Game); i--; continue;
		case 3: CheckRTLB(Game); CheckRBLT(Game); i--; continue;
		case 4: CheckBindex(Game); i--; continue;
		case 5: exit(1);
		case 6:
			temp = popStone(&top, &count, Game); // temp ������, null, �� ����. 
			if (temp == NULL) continue;

			back = pushStone(back, temp->stone.y, temp->stone.x, temp->stone.team, &count);



			PrintGame(Game, top);
			if (back != NULL)
				printf("���� �� �� �������ϴ�\n");
			//	printStack(top, count);
			printStack(back, count);
			i -= 2;
			if (i < 0) i = 1;
			continue;

		case 7:
			//back�� �ִ°� �����ͼ� push top 
			/*
			top = pushStone(top, Y, X, 'B',&count);
			PrintGame(Game,top);
			printStack(top,count);
			*/

			temp = popStone(&back, &count, Game);
			if (temp == NULL) continue;
			top = pushStone(top, temp->stone.y, temp->stone.x, temp->stone.team, &count);

			PrintGame(Game, top);
			printStack(top, count);
			printStack(back, count);

			continue;

		}


		int Y, X;
		printf("\n( Y , X )�� 0���� �۰ų� 18���� ũ�ٸ� ������ �����մϴ�.\n");

		if (i % 2 == 1)
		{
			printf("\n�˵� ��ǥ�� �Է��Ͽ� �ֽʽÿ� ( Y, X ) : ");
		}
		else if (i % 2 == 0)
		{
			printf("\n�� ��ǥ�� �Է��Ͽ� �ֽʽÿ� ( Y, X ) : ");
		}


		if (scanf("%d %d", &Y, &X) != 2) {
			printf("�Է� ���� �ǹٸ��� �ʽ��ϴ�. ���α׷��� �����մϴ�.\n");
			return 0;
		} fgetc(stdin);




		if (X < 0 || Y < 0 || X > 18 || Y > 18) {
			printf("\n������ ������ϴ�. �ٽ� �Է��� �ּ���.\n");
			i--;
			continue;
		}

		if (Game[Y][X] == 'B' || Game[Y][X] == 'W') {
			printf("\n��ǥ�� �̹� ���� ���� �ֽ��ϴ�.\n");
			i--;
			continue;
		}


		if (i % 2 == 1) {
			top = pushStone(top, Y, X, 'B', &count);
			PrintGame(Game, top);
			printStack(top, count);
		}
		else if (i % 2 == 0) {
			top = pushStone(top, Y, X, 'W', &count);
			PrintGame(Game, top);
			printStack(top, count);

		}

	}



	return 0;
}

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

void PrintGame(char Game[][19], STACK* top)
{
	STACK* cur = top;

	while (cur != NULL)
	{
		Game[cur->stone.y][cur->stone.x] = cur->stone.team; // STACK ����ü�� �ִ� ��ǥ ������ �� ���� �Է� 'A' ����������

		cur = cur->next;
	}

	for (int i = 0; i < 19; i++) {
		for (int k = 0; k < 19; k++) {
			printf("%c", Game[i][k]);
		}
		printf("\n");
	}
	printf("\n");

}

STACK* pushStone(STACK* top, int y, int x, char team, int* count)
{
	*count += 1;

	STACK* new = (STACK*)malloc(sizeof(STACK));
	if (new == NULL)
	{
		printf("���� �Ҵ翡 ����\n");
		return top;
	}

	new->stone.y = y;
	new->stone.x = x;
	new->stone.team = team; // STACK ����ü��ŭ ���ο� �޸� �Ҵ��ؼ� push�� ���� �Է��ϰ� top������ new�� �����ϱ� 

	new->next = top;
	top = new;

	return top;
}

STACK* popStone(STACK** top, int* count, char Game[][19])
{
	// ���������� -> *top�� �ּҰ���
	if (*top == NULL)
	{
		printf("������ �������� �ʽ��ϴ�\n");
		return NULL;
	}
	else
	{
		STACK* temp = *top; // �ּҰ� temp*�� �ǳ��ְ�
		*top = (*top)->next; // ���� ���� �����ϰ�
		temp->next = NULL; // ������ -> next�� �ƹ��͵� ����Ű�� �ʵ��� �����ϰ�
		*count -= 1; // ��ü ���� �Ѱ� ����
		Game[temp->stone.y][temp->stone.x] = '+'; // '+' �� ���� -> ������
		return temp;
	}

}

void printStack(STACK* top, int count)
{

	for (STACK* i = top; i != NULL; i = i->next)
	{
		printf("(%d %d):%c->", i->stone.y, i->stone.x, i->stone.team);
	}
	printf("NULL(�� : %d��) \n", count);
}

void menu(void)
{
	printf("=========================================\n");
	printf("0. �޴� ���� ���� �� �α�\n");
	printf("1 ��� ���� ���� �� �� ����ϱ�\n");
	printf("2. �� ���� ���� �� ���� ���� �� ���\n");
	printf("3. �� �밢�� �� ���� ���� �� ���\n");
	printf("4. ��� �����ٿ��� ���� ���� ��ǥ ���\n");
	printf("5. ���� ����\n");
	printf("6. ������\n");
	printf("7. ������� �����ߴ� �ٵ� �ٽ� �α�\n");
	printf("=========================================\n");
	printf("��ɾ� �Է� : ");

}

void EveryCount(char Game[][19])
{
	printf("=========================================\n");
	for (int i = 0; i < 19; i++)
	{
		int countB = 0, countW = 0;

		for (int k = 0; k < 19; k++)
		{
			if (Game[i][k] == 'B') countB++;
			if (Game[i][k] == 'W') countW++;
		}
		printf("���� %02d��° �� ���� B : %d W : %d\n", i, countB, countW);
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
		printf("���� %02d��° �� ���� B : %d W : %d\n", i, countB, countW);
	}
	printf("=========================================\n");

}
void CheckA(char Game[][19])
{
	for (int i = 0; i < 19; i++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0;

		for (int k = 0; k < 19; k++)
		{
			if (Game[k][i] == 'B')
			{
				countB++;
				countW = 0;
				if (countB > sumB) sumB = countB;
			}
			else if (Game[k][i] == 'W')
			{
				countW++;
				countB = 0;
				if (countW > sumW) sumW = countW;
			}
			else
			{
				countB = 0, countW = 0;
			}
		}

		if (sumB > 1 || sumW > 1)
		{
			if (sumB > sumW) printf("���� %02d��° �ִ� ���� �� B : %d", i, sumB);
			if (sumW > sumB) printf("���� %02d��° �ִ� ���� �� W : %d", i, sumW);
			if (sumB == sumW) printf("���� %02d��° �ִ� ���� �� B : %d W : %d", i, sumB, sumW);
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
				if (countW > sumW) sumW = countW;
			}
			else
			{
				countB = 0, countW = 0;
			}
		}

		if (sumB > 1 || sumW > 1)
		{
			if (sumB > sumW) printf("���� %02d��° �ִ� ���� �� B : %d", i, sumB);
			if (sumW > sumB) printf("���� %02d��° �ִ� ���� �� W : %d", i, sumW);
			if (sumB == sumW) printf("���� %02d��° �ִ� ���� �� B : %d W : %d", i, sumB, sumW);
			printf("\n");
		}
	}
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
		if (sumB > 1 || sumW > 1)
		{
			if (sumB > sumW) printf("���� %02d��° �ִ� ���� �� B : %d", k, sumB);
			if (sumW > sumB) printf("���� %02d��° �ִ� ���� �� W : %d", k, sumW);
			if (sumB == sumW) printf("���� %02d��° �ִ� ���� �� B : %d W : %d", k, sumB, sumW);
			printf("\n");
		}

	}

	for (int i = 18, k = 0; i > 0; i--, k++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0;

		for (int y = 0; y < 2 * k; y++)
		{
			if (y < 19 && i + y < 19) {

				if (Game[i + y][0 + y] == 'B')
				{
					countB++;
					countW = 0;
					if (countB > sumB)sumB = countB;
				}
				else if (Game[i + y][0 + y] == 'W')
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
		if (sumB > 1 || sumW > 1)
		{
			if (sumB > sumW) printf("���ϴ� %02d��° �ִ� ���� �� B : %d", k, sumB);
			if (sumW > sumB) printf("���ϴ� %02d��° �ִ� ���� �� W : %d", k, sumW);
			if (sumB == sumW) printf("���ϴ� %02d��° �ִ� ���� �� B : %d W : %d", k, sumB, sumW);
			printf("\n");
		}


	}


}
void CheckRBLT(char Game[][19])
{

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
					if (countB > sumB)sumB = countB;
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
		if (sumB > 1 || sumW > 1)
		{
			if (sumB > sumW) printf("���ϴ� %02d��° �ִ� ���� �� B : %d", k, sumB);
			if (sumW > sumB) printf("���ϴ� %02d��° �ִ� ���� �� W : %d", k, sumW);
			if (sumB == sumW) printf("���ϴ� %02d��° �ִ� ���� �� B : %d W : %d", k, sumB, sumW);
			printf("\n");
		}

	}

	for (int i = 18, k = 0; i > 0; i--, k++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0;

		for (int y = 0; y < 2 * k; y++)
		{
			if (k - y >= 0 && y < 18) {

				if (Game[k - y][0 + y] == 'B')
				{
					countB++;
					countW = 0;
					if (countB > sumB)sumB = countB;
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
		if (sumB > 1 || sumW > 1)
		{
			if (sumB > sumW) printf("�»�� %02d��° �ִ� ���� �� B : %d", k, sumB);
			if (sumW > sumB) printf("�»�� %02d��° �ִ� ���� �� W : %d", k, sumW);
			if (sumB == sumW) printf("�»�� %02d��° �ִ� ���� �� B : %d W : %d", k, sumB, sumW);
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
					countB = 1;
					sumB = countB;
					list[i][k - 1].state = 'B';
					list[i][k - 1].Y = i;
					list[i][k - 1].X = 0;
					list[i][k - 1].combo = 1;
				}
				else if (Game[i][k - 1] == 'W')
				{
					countW = 1;
					sumW = countW;
					list[i][k - 1].state = 'W';
					list[i][k - 1].Y = i;
					list[i][k - 1].X = 0;
					list[i][k - 1].combo = 1;
				}
			}

			if (Game[i][k] == Game[i][k - 1])
			{
				if (Game[i][k] == 'B')
				{
					countB++;
					countW = 0;
					if (countB > sumB) sumB = countB;
					list[i][k].state = 'B';
					list[i][k].Y = i;
					list[i][k].X = k;
					list[i][k].combo = sumB;

				}
				else if (Game[i][k] == 'W')
				{
					countW++;
					countB = 0;
					if (countW > sumW) sumW = countW;
					list[i][k].state = 'W';
					list[i][k].Y = i;
					list[i][k].X = k;
					list[i][k].combo = sumW;
				}
			}
			else if (Game[i][k] != Game[i][k - 1])
			{
				if (Game[i][k] == 'B')
				{
					countB = 1;
					countW = 0;
					sumB = countB;

					list[i][k].state = 'B';
					list[i][k].Y = i;
					list[i][k].X = k;
					list[i][k].combo = sumB;

				}
				else if (Game[i][k] == 'W')
				{
					countW = 1;
					countB = 0;
					sumW = countW;

					list[i][k].state = 'W';
					list[i][k].Y = i;
					list[i][k].X = k;
					list[i][k].combo = sumW;
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
				printf("���� %02d��° ���� �� ��ǥ ", i);
				if (list[i][k].state == 'B')
				{
					printf("B( Y , X ) : ");
					for (int j = k + 1 - list[i][k].combo; j <= k; j++)
					{
						printf("( %d , %d ) ", list[i][j].Y, list[i][j].X);
					}
				}

				if (list[i][k].state == 'W')
				{
					printf("W( Y , X ) : ");
					for (int j = k + 1 - list[i][k].combo; j <= k; j++)
					{
						printf("( %d , %d ) ", list[i][j].Y, list[i][j].X);
					}
				}

				if (list[i][k].state != 0) printf("\n");
			}
		}
	}
}

#endif
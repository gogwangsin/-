#if 1

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include <stdlib.h>

typedef struct LIST {

	char state;
	int Y, X;
	int combo;

}LIST;


typedef struct STONE {

	int y, x;
	char team;

}STONE;

typedef struct STACK {

	STONE stone;
	struct STACK* next;

}STACK;

void menu(void);
void PrintGame(char Game[][19], STACK* top);
void PrintStack(STACK* stack, int count);
STACK* pushStone(STACK* push, int y, int x, char team);
STACK* popStone(STACK** pop);
STACK* deleteAll(STACK* stack, char Game[][19]);
void saveGame(STACK* top, STACK* back, int countTop, int countBack);
void loadGame(STACK** top, STACK** back, int* countTop, int* countBack, int* i, char Game[][19]);

void MakeGame(char Game[][19]);
void EveryCount(char Game[][19]);
void CheckA(char Game[][19]);
void CheckB(char Game[][19]);
void CheckRTLB(char Game[][19]);
void CheckRBLT(char Game[][19]);
void CheckBindex(char Game[][19]);




int main(void)
{

	STACK* top = NULL;
	STACK* back = NULL;
	STACK* temp = NULL;

	int countTop = 0;
	int countBack = 0;



	char Game[19][19];
	MakeGame(Game);

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
		case 5:
			temp = popStone(&top);
			if (temp == NULL)
			{
				i--; continue;
			}
			else
			{
				countTop--;
				countBack++;
				back = pushStone(back, temp->stone.y, temp->stone.x, temp->stone.team);
				Game[temp->stone.y][temp->stone.x] = '+';

				PrintGame(Game, top);
				PrintStack(back, countBack);
				PrintStack(top, countTop);

				i -= 2;
				if (i < 0) i = 1;
				continue;
			}

		case 6:
			temp = popStone(&back);
			if (temp == NULL)
			{
				i--; continue;
			}
			else
			{
				countTop++;
				countBack--;
				top = pushStone(top, temp->stone.y, temp->stone.x, temp->stone.team);
				Game[temp->stone.y][temp->stone.x] = temp->stone.team;

				PrintGame(Game, top);
				PrintStack(back, countBack);
				PrintStack(top, countTop);

				continue;
			}
		case 7: saveGame(top, back, countTop, countBack); i--; continue;
		case 8:
			top = deleteAll(top, Game);
			back = deleteAll(back, Game);
			countBack = 0;
			countTop = 0;
			i = 1;
			loadGame(&top, &back, &countTop, &countBack, &i, Game);
			i--;
			continue;

		case 9:
		default:
			top = deleteAll(top, Game);
			back = deleteAll(back, Game);
			exit(1);
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
			Game[Y][X] = 'B';
			top = pushStone(top, Y, X, 'B');
			countTop++;

			back = deleteAll(back, Game);
			countBack = 0;

			PrintGame(Game, top);
			PrintStack(back, countBack);
			PrintStack(top, countTop);
		}
		else if (i % 2 == 0) {
			Game[Y][X] = 'W';
			top = pushStone(top, Y, X, 'W');
			countTop++;

			back = deleteAll(back, Game);
			countBack = 0;

			PrintGame(Game, top);
			PrintStack(back, countBack);
			PrintStack(top, countTop);

		}

	}



	return 0;
}






void menu(void)
{
	printf("=========================================\n");
	printf("0. �޴� ���� ���� �� �α�\n");
	printf("1 ��� ���� ���� �� �� ����ϱ�\n");
	printf("2. �� ���� ���� �� ���� ���� �� ���\n");
	printf("3. �� �밢�� �� ���� ���� �� ���\n");
	printf("4. ��� �����ٿ��� ���� ���� ��ǥ ���\n");
	printf("5. ������\n");
	printf("6. �������ߴ� ���� �ٽ� ������\n");
	printf("7. ���� �����ϱ�\n");
	printf("8. ���� �ҷ�����\n");
	printf("9. ���� ����\n");
	printf("=========================================\n");
	printf("��ɾ� �Է� : ");

}
void PrintGame(char Game[][19], STACK* top)
{
	STACK* cur = top;
	while (cur != NULL)
	{
		Game[cur->stone.y][cur->stone.x] = cur->stone.team;
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
void PrintStack(STACK* stack, int count)
{
	for (STACK* i = stack; i != NULL; i = i->next) // ���� ��� �����ͷ� �̵��ϸ鼭
	{
		printf("%c(%d,%d)->", i->stone.team, i->stone.y, i->stone.x);
	}
	printf("NULL(�� ����: %d)\n", count);
}

STACK* pushStone(STACK* push, int y, int x, char team)
{
	STACK* new = (STACK*)malloc(sizeof(STACK));
	if (new == NULL)
	{
		printf("�����Ҵ翡 �����߽��ϴ�\n");
		return push;
	}
	new->stone.y = y;
	new->stone.x = x;
	new->stone.team = team;

	new->next = push;
	push = new;

	return push; // ���� ���� ������ �ּ� ����
}

STACK* popStone(STACK** pop)
{
	if (*pop == NULL)
	{
		printf("������ ����ֽ��ϴ�\n");
		return NULL;
	}
	else
	{
		STACK* temp = *pop;
		*pop = (*pop)->next;
		temp->next = NULL;

		return temp;
	}

}

STACK* deleteAll(STACK* stack, char Game[][19])
{
	if (stack == NULL)
	{
		return NULL;
	}

	STACK* temp = stack;
	while (stack != NULL)
	{
		temp = stack;
		stack = stack->next;
		Game[temp->stone.y][temp->stone.x] = '+';
		free(temp);
	}
	return stack;
}

void saveGame(STACK* top, STACK* back, int countTop, int countBack)
{
	// ���� �����ϱ�
	FILE* fp = fopen("save.txt", "w");
	if (fp == NULL)
	{
		printf("���� ���⿡ �����߽��ϴ�\n");
		return;
	}

	fprintf(fp, "%d %d\n", countTop, countBack);
	// ���Ͽ� ����ϱ�
	// -> �޸��� ���Ͽ� y,x,char team ���پ� ����ǰ�
	// �����̳� \n�� �����ؼ� �����ϰ� ����

	for (int i = 0; i < countTop; i++)
	{
		fprintf(fp, "%d %d %c\n", top->stone.y, top->stone.x, top->stone.team);
		top = top->next;
	}

	for (int i = 0; i < countBack; i++)
	{
		fprintf(fp, "%d %d %c\n", back->stone.y, back->stone.x, back->stone.team);
		back = back->next;
	}

	printf("���� ���忡 �����߽��ϴ�!\n");
	fclose(fp);
}

void loadGame(STACK** top, STACK** back, int* countTop, int* countBack, int* i, char Game[][19])
{
	FILE* fp = fopen("save.txt", "r");
	if (fp == NULL)
	{
		printf("���� ���⿡ �����߽��ϴ�\n");
		return;
	}

	if (fscanf(fp, "%d %d", countTop, countBack) != 2)
	{
		printf("�Է� ����\n");
		exit(1);
	}

	// -----------------------------------------------------------

	for (int i = 0; i < *countTop; i++)
	{
		STACK* new = (STACK*)malloc(sizeof(STACK));
		if (new == NULL)
		{
			printf("�����Ҵ翡 �����߽��ϴ�\n");
			exit(1);
		}

		if (fscanf(fp, "%d %d %c", &new->stone.y, &new->stone.x, &new->stone.team) != 3)
		{
			printf("�Է� ����\n");
			exit(1);
		}
		// new�� �Ҵ��� �޸� ����ü�� ���� �ϳ��� �Է� fscanf
		new->next = *top;
		*top = new;
		Game[new->stone.y][new->stone.x] = new->stone.team;

	}

// -----------------------------------------------------------

	for (int i = 0; i < *countBack; i++)
	{
		STACK* new = (STACK*)malloc(sizeof(STACK));
		if (new == NULL)
		{
			printf("�����Ҵ翡 �����߽��ϴ�\n");
			exit(1);
		}

		if (fscanf(fp, "%d %d %c", &new->stone.y, &new->stone.x, &new->stone.team) != 3)
		{
			printf("�Է� ����\n");
			exit(1);
		}

		new->next = *back;
		*back = new;
	}

	*i += *countTop;
	printf("���� �ε忡 �����߽��ϴ�!\n");
	fclose(fp);

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
#if 0

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define BLACK 1
#define WHITE -1
#define NONE 0

typedef struct LIST {

	char state;
	int Y, X;
	int combo;
	int max; // �޺��������� �ִ밪 ���� -> ���پ� �� 

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

void helpGame(char Game[][19], char Bhelp[][19], char Whelp[][19]);
void printHelp(char HELP[][19]);


void CheckBindex(char Game[][19], char Bhelp[][19], char Whelp[][19]);
void CheckAindex(char Game[][19], char Bhelp[][19], char Whelp[][19]);
void CheckRTindex(char Game[][19], char Bhelp[][19], char Whelp[][19]);
void CheckLBindex(char Game[][19], char Bhelp[][19], char Whelp[][19]);
void CheckRBindex(char Game[][19], char Bhelp[][19], char Whelp[][19]);
void CheckLTindex(char Game[][19], char Bhelp[][19], char Whelp[][19]);


int main(void)
{
	STACK* top = NULL;
	STACK* back = NULL;
	STACK* temp = NULL;

	int countTop = 0;
	int countBack = 0;

	char Game[19][19];
	char Bhelp[19][19];
	char Whelp[19][19]; // �����������ϴ°�

	MakeGame(Game);
	helpGame(Game, Bhelp, Whelp);


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
		case 1:
			if (i % 2 == 1) // �浹 
			{
				printHelp(Bhelp);
				printf("���� �� ���� ���� ������Ʈ\n");
			}
			else if (i % 2 == 0)
			{
				printHelp(Whelp);
				printf("�� �� ���� ���� ������Ʈ\n");

			} i--; continue;

		case 2:
			temp = popStone(&top);
			if (temp == NULL)
			{
				i--; continue;
			}
			else
			{
				countBack++;
				countTop--;
				back = pushStone(back, temp->stone.y, temp->stone.x, temp->stone.team);
				Game[temp->stone.y][temp->stone.x] = '+';
				PrintGame(Game, top);
				printf("������ ���� : "); PrintStack(back, countBack);
				printf("���� ���� : "); PrintStack(top, countTop);

				i -= 2;
				if (i < 0) i = 1;
				continue;
			}
		case 3:
			temp = popStone(&back);
			if (temp == NULL)
			{
				i--; continue;
			}
			else
			{
				countBack--;
				countTop++;
				top = pushStone(top, temp->stone.y, temp->stone.x, temp->stone.team);
				Game[temp->stone.y][temp->stone.x] = temp->stone.team;

				PrintGame(Game, top);
				printf("������ ���� : "); PrintStack(back, countBack);
				printf("���� ���� : "); PrintStack(top, countTop);
				continue;
			}
		case 4: saveGame(top, back, countTop, countBack); i--; continue;
		case 5:
			top = deleteAll(top, Game);
			back = deleteAll(back, Game);
			i = 1;
			countTop = 0;
			countBack = 0;
			loadGame(&top, &back, &countTop, &countBack, &i, Game);
			PrintGame(Game, top);
			helpGame(Game, Bhelp, Whelp);
			CheckAindex(Game, Bhelp, Whelp);
			CheckBindex(Game, Bhelp, Whelp);
			CheckRTindex(Game, Bhelp, Whelp);
			CheckLBindex(Game, Bhelp, Whelp);
			CheckRBindex(Game, Bhelp, Whelp);
			CheckLTindex(Game, Bhelp, Whelp);
			printf("������ ���� : "); PrintStack(back, countBack);
			printf("���� ���� : "); PrintStack(top, countTop);
			printf("���� �ε带 �Ϸ��߽��ϴ�!\n");
			i--;
			continue;
		case 6:
		default:
			top = deleteAll(top, Game);
			back = deleteAll(back, Game);
			printf("������ �����մϴ�!\n");
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
			printf("������ ���� : "); PrintStack(back, countBack);
			printf("���� ���� : "); PrintStack(top, countTop);
		}
		else if (i % 2 == 0) {

			Game[Y][X] = 'W';
			top = pushStone(top, Y, X, 'W');
			countTop++;
			back = deleteAll(back, Game);
			countBack = 0;
			PrintGame(Game, top);
			printf("������ ���� : "); PrintStack(back, countBack);
			printf("���� ���� : "); PrintStack(top, countTop);
		}

		helpGame(Game, Bhelp, Whelp); // �ʱ�ȭ�Ǽ� �ٽ� ����ϱ� 
		CheckAindex(Game, Bhelp, Whelp);
		CheckBindex(Game, Bhelp, Whelp);
		CheckRTindex(Game, Bhelp, Whelp);
		CheckLBindex(Game, Bhelp, Whelp);
		CheckRBindex(Game, Bhelp, Whelp);
		CheckLTindex(Game, Bhelp, Whelp);

	}

	return 0;
}



void CheckAindex(char Game[][19], char Bhelp[][19], char Whelp[][19])
{
	LIST list[19][19] = { 0 };

	for (int i = 0; i < 19; i++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0, countNone = 0;

		int startPoint = 0, endPoint = 0, nonePoint = 0; // ���� �� ���� ��ġ 

		int k = 1;

		for (k = 1; k < 19; k++)
		{
			if (k - 1 == 0)
			{
				if (Game[k - 1][i] == 'B')
				{
					countB = 1;
					sumB = countB;
					startPoint = k - 1;
					endPoint = k - 1;
					list[k - 1][i].state = 'B';
					list[k - 1][i].Y = 0;
					list[k - 1][i].X = i;
					list[k - 1][i].combo = 1;
				}
				else if (Game[k - 1][i] == 'W') // �� ó�� B or W or +
				{
					countW = 1;
					sumW = countW;
					startPoint = k - 1;
					endPoint = k - 1;
					list[k - 1][i].state = 'W';
					list[k - 1][i].Y = 0;
					list[k - 1][i].X = i;
					list[k - 1][i].combo = 1;
				}
				else if (Game[k - 1][i] == '+') // �н� 
				{
					nonePoint = k - 1;
					list[k - 1][i].state = '+';
					list[k - 1][i].Y = 0;
					list[k - 1][i].X = i;
				}
			}


			if (Game[k][i] == Game[k - 1][i]) // ������ ���� �� BB ++ WW 
			{
				if (Game[k][i] == 'B')
				{
					countB++;
					countW = 0;
					endPoint = k;
					if (countB > sumB) sumB = countB;
					list[k][i].state = 'B';
					list[k][i].Y = k;
					list[k][i].X = i;
					list[k][i].combo = sumB;

				}
				else if (Game[k][i] == 'W')
				{
					countW++;
					countB = 0;
					endPoint = k;
					if (countW > sumW) sumW = countW;
					list[k][i].state = 'W';
					list[k][i].Y = k;
					list[k][i].X = i;
					list[k][i].combo = sumW;
				}
				else if (Game[k][i] == '+') // ���� 2�̻󿬼� nonepoint���� ������ ���ö����� k ���� 
				{
					if (k - 2 >= 0 && (Game[k - 2][i] == 'B'))
					{
						list[startPoint][i].max = list[k - 2][i].combo; // ���� ���� ������ ������ϴµ� ���� �ִ��� max�� ����ؾ��� 
					}
					else if (k - 2 >= 0 && (Game[k - 2][i] == 'W'))
					{
						list[startPoint][i].max = list[k - 2][i].combo;
					}
					countNone = 0; // ���� �ʱ�ȭ 
				}
			}
			else if (Game[k][i] != Game[k - 1][i]) // WB +B BW +W B+ W+
			{
				if (Game[k][i] == 'B') // ���� �� ���ؼ� �������ֱ� 
				{
					if (k - 1 >= 0 && (Game[k - 1][i] == 'W'))
					{
						list[startPoint][i].max = list[k - 1][i].combo; // �������� stp max ��� 

						countB = 1;
						countW = 0;
						sumB = countB;
						countNone = 0; // ���� �ʱ�ȭ 
						startPoint = k;
						list[k][i].state = 'B';
						list[k][i].Y = k;
						list[k][i].X = i;
						list[k][i].combo = sumB;

					}
					else  if (k - 1 >= 0 && (Game[k - 1][i] == '+')) // AOB BOB 
					{
						if (countNone == 1) // ���� �ϳ��϶� ������ 
						{
							countB++;
							countW = 0;
							endPoint = k;
							if (countB > sumB) sumB = countB;
							list[k][i].state = 'B';
							list[k][i].Y = k;
							list[k][i].X = i;
							list[k][i].combo = sumB;

						}
						else if (countNone == 0)
						{
							countB = 1;
							countW = 0;
							sumB = countB;
							countNone = 0; // ���� �ʱ�ȭ 
							startPoint = k;
							list[k][i].state = 'B';
							list[k][i].Y = k;
							list[k][i].X = i;
							list[k][i].combo = sumB;
						}
					}
				}
				else if (Game[k][i] == 'W')
				{
					if (k - 1 >= 0 && (Game[k - 1][i] == 'B'))
					{
						list[startPoint][i].max = list[k - 1][i].combo; // ����BW

						countW = 1;
						countB = 0;
						sumW = countW;
						countNone = 0;
						startPoint = k;
						list[k][i].state = 'W';
						list[k][i].Y = k;
						list[k][i].X = i;
						list[k][i].combo = sumW;
					}
					else  if (k - 1 >= 0 && (Game[k - 1][i] == '+'))
					{
						if (countNone == 1) // ���� �ϳ��϶� ������  A0A 
						{
							countW++;
							countB = 0;
							endPoint = k;
							if (countW > sumW) sumW = countW;
							list[k][i].state = 'W';
							list[k][i].Y = k;
							list[k][i].X = i;
							list[k][i].combo = sumW;

						}
						else if (countNone == 0) // 00A A0A0A
						{
							countW = 1;
							countB = 0;
							sumW = countW;
							countNone = 0;
							startPoint = k;
							list[k][i].state = 'W';
							list[k][i].Y = k;
							list[k][i].X = i;
							list[k][i].combo = sumW;
						}
					}
				}
				else if (Game[k][i] == '+') // coutnone 2�� ��������ϰ� // BAO-c1 ABO-c1 AAO-c1 BBO-c1 OBO OAO 00A-c0 
				{
					countNone++; // ó�� ������ġ 

					if (countNone == 1)
					{
						nonePoint = k; //ó��������ġ ���� 

					}
					else if (countNone == 2) // �ι� ���� A0A0    AA0AA0 00AA 00A0A0 �������� ó�� POINT��ġ�� �ٽ� ���� 
					{
						countNone = 0;
						if (k - 1 >= 0 && (Game[k - 1][i] == 'B'))
						{
							list[startPoint][i].max = list[k - 1][i].combo; // 01,10�϶� ���� 
							k = nonePoint;
							continue;
						}
						else if (k - 1 >= 0 && (Game[k - 1][i] == 'W'))
						{
							list[startPoint][i].max = list[k - 1][i].combo; // ����BW
							k = nonePoint;
							continue;
						}
					}
				}

			}
			//-------------------------------------------------------------------------------------------------------

			if (list[k][i].combo == 4) // �޺� 3�Ǵ� 4�϶� 
			{
				list[startPoint][i].max = list[k][i].combo; //�������� �ִ�ġ ���  

				int blanckOn = 0;

				for (int j = startPoint; j <= endPoint; j++) // �ִ� 1~5�϶� 10234
				{
					if (Game[j][i] == '+') //����������
					{
						blanckOn = 1;

						if (list[startPoint][i].state == 'B')
						{
							Whelp[j][i] = 'o'; // �����ִµ� �������϶� -> �鵹 �ʿ� �׸��� 
							if (Whelp[startPoint - 1][i] == 'o') Whelp[startPoint - 1][i] = '+';
							if (Whelp[endPoint + 1][i] == 'o') Whelp[endPoint + 1][i] = '+';
						}
						if (list[startPoint][i].state == 'W')
						{
							Bhelp[j][i] = 'o'; // ��ȣ �ٲܼ����ְ� ����ü�� ��ǥ �����ϰ� �ٲܼ��� �ձ��� 
							if (Bhelp[startPoint - 1][i] == 'o') Bhelp[startPoint - 1][i] = '+';
							if (Bhelp[endPoint + 1][i] == 'o') Bhelp[endPoint + 1][i] = '+';
						}

					}
				}

				if (blanckOn == 0) // ���� ������
				{
					if (list[startPoint][i].state == 'B') //whelp ó���� �������϶�
					{
						if (startPoint - 1 >= 0 && (Game[startPoint - 1][i] == '+')) // �����϶�
						{
							Whelp[startPoint - 1][i] = 'o'; // ����!
						}
						if (endPoint + 1 <= 18 && (Game[endPoint + 1][i] == '+')) // �����϶�
						{
							Whelp[endPoint + 1][i] = 'o'; // ����!
						}
					}
					else if (list[startPoint][i].state == 'W') // bhelp ó���� �鵹�϶� 
					{
						if (startPoint - 1 >= 0 && (Game[startPoint - 1][i] == '+')) // �����϶�
						{
							Bhelp[startPoint - 1][i] = 'o'; // ����! -> B�����ִ� �� 
						}
						if (endPoint + 1 <= 18 && (Game[endPoint + 1][i] == '+')) // �����϶�
						{
							Bhelp[endPoint + 1][i] = 'o'; // ����!
						}
					}
				}

			} // �޺�
			else if (list[k][i].combo == 3) // 3�϶� 
			{
				list[startPoint][i].max = list[k][i].combo; //�������� �ִ�ġ ���  

				for (int j = startPoint; j <= endPoint; j++) // �ִ� 1~5�϶� 10234
				{
					if (Game[j][i] == '+') //����������
					{

						if (list[startPoint][i].state == 'B')
						{
							Whelp[j][i] = 'o'; // �����ִµ� �������϶� -> �鵹 �ʿ� �׸��� 
						}
						if (list[startPoint][i].state == 'W')
						{
							Bhelp[j][i] = 'o';
						}
					}
				}

				if (list[startPoint][i].state == 'B') //whelp ó���� �������϶�
				{
					if (startPoint - 1 >= 0 && (Game[startPoint - 1][i] == '+')) // �����϶�
					{
						Whelp[startPoint - 1][i] = 'o'; // ����!
					}
					if (endPoint + 1 <= 18 && (Game[endPoint + 1][i] == '+')) // �����϶�
					{
						Whelp[endPoint + 1][i] = 'o'; // ����!
					}
				}
				else if (list[startPoint][i].state == 'W') // bhelp ó���� �鵹�϶� 
				{
					if (startPoint - 1 >= 0 && (Game[startPoint - 1][i] == '+')) // �����϶�
					{
						Bhelp[startPoint - 1][i] = 'o'; // ����! -> B�����ִ� �� 
					}
					if (endPoint + 1 <= 18 && (Game[endPoint + 1][i] == '+')) // �����϶�
					{
						Bhelp[endPoint + 1][i] = 'o'; // ����!
					}
				}
			}

		}//-------------------------------------------------------------------------------------------------

		int max = 0;

		for (int k = 0; k < 19; k++)
		{
			if (list[k][i].max > max) max = list[k][i].max; // �� ó�� ���� �޺� �ƽ�ġ �����س��� -> �޺� �ɱ涧 ���� ������ �����ϸ� combo�ٲ�� ���
		} // ���Ӳ��������� combo��ġ�� max�� ����صδ°ž�

		for (int k = 0; k < 19; k++)
		{
			if (max > 1 && (list[k][i].max == max))
			{
				printf("���� %02d��° ���� �� ��ǥ ", i);  // ���� ��� ���ص� �ɵ� 

				if (list[k][i].state == 'B')
				{
					printf("B(Y,X) : ");
					for (int j = k; j <= k + list[k][i].max; j++)
					{
						if (j <= 18 && (list[j][i].state == 'B')) // �������� max�����ϴµ� ������ �������� ��� k=2, max=4-> 
						{
							printf("(%d,%d)", list[j][i].Y, list[j][i].X);
						}
					}
				}

				if (list[k][i].state == 'W')
				{
					printf("W(Y,X) : ");
					for (int j = k; j <= k + list[k][i].max; j++)
					{
						if (j <= 18 && (list[j][i].state == 'W'))
						{
							printf("(%d,%d)", list[j][i].Y, list[j][i].X);
						}
					}
				}

				if (list[k][i].state != 0) printf("\n");
			}
		}

	}


}
void CheckBindex(char Game[][19], char Bhelp[][19], char Whelp[][19])
{
	LIST list[19][19] = { 0 };

	for (int i = 0; i < 19; i++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0, countNone = 0;

		int startPoint = 0, endPoint = 0, nonePoint = 0; // ���� �� ���� ��ġ 

		int k = 1;

		for (k = 1; k < 19; k++)
		{
			if (k - 1 == 0)
			{
				if (Game[i][k - 1] == 'B')
				{
					countB = 1;
					sumB = countB;
					startPoint = k - 1;
					endPoint = k - 1;
					list[i][k - 1].state = 'B';
					list[i][k - 1].Y = i;
					list[i][k - 1].X = 0;
					list[i][k - 1].combo = 1;
				}
				else if (Game[i][k - 1] == 'W') // �� ó�� B or W or +
				{
					countW = 1;
					sumW = countW;
					startPoint = k - 1;
					endPoint = k - 1;
					list[i][k - 1].state = 'W';
					list[i][k - 1].Y = i;
					list[i][k - 1].X = 0;
					list[i][k - 1].combo = 1;
				}
				else if (Game[i][k - 1] == '+') // �н� 
				{
					nonePoint = k - 1;
					list[i][k - 1].state = '+';
					list[i][k - 1].Y = i;
					list[i][k - 1].X = 0;
				}
			}


			if (Game[i][k] == Game[i][k - 1]) // ������ ���� �� BB ++ WW 
			{
				if (Game[i][k] == 'B')
				{
					countB++;
					countW = 0;
					endPoint = k;
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
					endPoint = k;
					if (countW > sumW) sumW = countW;
					list[i][k].state = 'W';
					list[i][k].Y = i;
					list[i][k].X = k;
					list[i][k].combo = sumW;
				}
				else if (Game[i][k] == '+') // ���� 2�̻󿬼� nonepoint���� ������ ���ö����� k ���� 
				{
					if (k - 2 >= 0 && (Game[i][k - 2] == 'B'))
					{
						list[i][startPoint].max = list[i][k - 2].combo; // ���� ���� ������ ������ϴµ� ���� �ִ��� max�� ����ؾ��� 
					}
					else if (k - 2 >= 0 && (Game[i][k - 2] == 'W'))
					{
						list[i][startPoint].max = list[i][k - 2].combo;
					}
					countNone = 0; // ���� �ʱ�ȭ 
				}
			}
			else if (Game[i][k] != Game[i][k - 1]) // WB +B BW +W B+ W+
			{
				if (Game[i][k] == 'B') // ���� �� ���ؼ� �������ֱ� 
				{
					if (k - 1 >= 0 && (Game[i][k - 1] == 'W'))
					{
						list[i][startPoint].max = list[i][k - 1].combo; // �������� stp max ��� 

						countB = 1;
						countW = 0;
						sumB = countB;
						countNone = 0; // ���� �ʱ�ȭ 
						startPoint = k;
						list[i][k].state = 'B';
						list[i][k].Y = i;
						list[i][k].X = k;
						list[i][k].combo = sumB;

					}
					else  if (k - 1 >= 0 && (Game[i][k - 1] == '+')) // AOB BOB 
					{
						if (countNone == 1) // ���� �ϳ��϶� ������ 
						{
							countB++;
							countW = 0;
							endPoint = k;
							if (countB > sumB) sumB = countB;
							list[i][k].state = 'B';
							list[i][k].Y = i;
							list[i][k].X = k;
							list[i][k].combo = sumB;

						}
						else if (countNone == 0)
						{
							countB = 1;
							countW = 0;
							sumB = countB;
							countNone = 0; // ���� �ʱ�ȭ 
							startPoint = k;
							list[i][k].state = 'B';
							list[i][k].Y = i;
							list[i][k].X = k;
							list[i][k].combo = sumB;
						}
					}
				}
				else if (Game[i][k] == 'W')
				{
					if (k - 1 >= 0 && (Game[i][k - 1] == 'B'))
					{
						list[i][startPoint].max = list[i][k - 1].combo; // ����BW

						countW = 1;
						countB = 0;
						sumW = countW;
						countNone = 0;
						startPoint = k;
						list[i][k].state = 'W';
						list[i][k].Y = i;
						list[i][k].X = k;
						list[i][k].combo = sumW;
					}
					else  if (k - 1 >= 0 && (Game[i][k - 1] == '+'))
					{
						if (countNone == 1) // ���� �ϳ��϶� ������  A0A 
						{
							countW++;
							countB = 0;
							endPoint = k;
							if (countW > sumW) sumW = countW;
							list[i][k].state = 'W';
							list[i][k].Y = i;
							list[i][k].X = k;
							list[i][k].combo = sumW;

						}
						else if (countNone == 0) // 00A A0A0A
						{
							countW = 1;
							countB = 0;
							sumW = countW;
							countNone = 0;
							startPoint = k;
							list[i][k].state = 'W';
							list[i][k].Y = i;
							list[i][k].X = k;
							list[i][k].combo = sumW;
						}
					}
				}
				else if (Game[i][k] == '+') // coutnone 2�� ��������ϰ� // BAO-c1 ABO-c1 AAO-c1 BBO-c1 OBO OAO 00A-c0 
				{
					countNone++; // ó�� ������ġ 

					if (countNone == 1)
					{
						nonePoint = k; //ó��������ġ ���� 

					}
					else if (countNone == 2) // �ι� ���� A0A0    AA0AA0 00AA 00A0A0 �������� ó�� POINT��ġ�� �ٽ� ���� 
					{
						countNone = 0;
						if (k - 1 >= 0 && (Game[i][k - 1] == 'B'))
						{
							list[i][startPoint].max = list[i][k - 1].combo;
							k = nonePoint;
							continue;
						}
						else if (k - 1 >= 0 && (Game[i][k - 1] == 'W'))
						{
							list[i][startPoint].max = list[i][k - 1].combo; // ����BW
							k = nonePoint;
							continue;
						}
					}
				}

			}
			//-------------------------------------------------------------------------------------------------------

			if (list[i][k].combo == 4) // �޺� 3�Ǵ� 4�϶� 
			{
				list[i][startPoint].max = list[i][k].combo; //�������� �ִ�ġ ���  

				int blanckOn = 0;

				for (int j = startPoint; j <= endPoint; j++) // �ִ� 1~5�϶� 10234
				{
					if (Game[i][j] == '+') //����������
					{
						blanckOn = 1;

						if (list[i][startPoint].state == 'B')
						{
							Whelp[i][j] = 'o'; // �����ִµ� �������϶� -> �鵹 �ʿ� �׸��� 
							if (Whelp[i][startPoint - 1] == 'o') Whelp[i][startPoint - 1] = '+';
							if (Whelp[i][endPoint + 1] == 'o') Whelp[i][endPoint + 1] = '+';
						}
						if (list[i][startPoint].state == 'W')
						{
							Bhelp[i][j] = 'o';
							if (Bhelp[i][startPoint - 1] == 'o') Bhelp[i][startPoint - 1] = '+';
							if (Bhelp[i][endPoint + 1] == 'o') Bhelp[i][endPoint + 1] = '+';
						}

					}
				}

				if (blanckOn == 0) // ���� ������
				{
					if (list[i][startPoint].state == 'B') //whelp ó���� �������϶�
					{
						if (startPoint - 1 >= 0 && (Game[i][startPoint - 1] == '+')) // �����϶�
						{
							Whelp[i][startPoint - 1] = 'o'; // ����!
						}
						if (endPoint + 1 <= 18 && (Game[i][endPoint + 1] == '+')) // �����϶�
						{
							Whelp[i][endPoint + 1] = 'o'; // ����!
						}
					}
					else if (list[i][startPoint].state == 'W') // bhelp ó���� �鵹�϶� 
					{
						if (startPoint - 1 >= 0 && (Game[i][startPoint - 1] == '+')) // �����϶�
						{
							Bhelp[i][startPoint - 1] = 'o'; // ����! -> B�����ִ� �� 
						}
						if (endPoint + 1 <= 18 && (Game[i][endPoint + 1] == '+')) // �����϶�
						{
							Bhelp[i][endPoint + 1] = 'o'; // ����!
						}
					}
				}

			} // �޺�
			else if (list[i][k].combo == 3) // 3�϶�  3�϶� �ѹ� �����Ѱ��� ���� ���� oBBOBO�ε� OBBOBB
			{
				list[i][startPoint].max = list[i][k].combo; //�������� �ִ�ġ ���  

				for (int j = startPoint; j <= endPoint; j++) // �ִ� 1~5�϶� 10234
				{
					if (Game[i][j] == '+') //����������
					{

						if (list[i][startPoint].state == 'B')
						{
							Whelp[i][j] = 'o'; // �����ִµ� �������϶� -> �鵹 �ʿ� �׸��� 
						}
						if (list[i][startPoint].state == 'W')
						{
							Bhelp[i][j] = 'o';
						}
					}
				}

				if (list[i][startPoint].state == 'B') //whelp ó���� �������϶�
				{
					if (startPoint - 1 >= 0 && (Game[i][startPoint - 1] == '+')) // �����϶�
					{
						Whelp[i][startPoint - 1] = 'o'; // ����!
					}
					if (endPoint + 1 <= 18 && (Game[i][endPoint + 1] == '+')) // �����϶�
					{
						Whelp[i][endPoint + 1] = 'o'; // ����!
					}
				}
				else if (list[i][startPoint].state == 'W') // bhelp ó���� �鵹�϶� 
				{
					if (startPoint - 1 >= 0 && (Game[i][startPoint - 1] == '+')) // �����϶�
					{
						Bhelp[i][startPoint - 1] = 'o'; // ����! -> B�����ִ� �� 
					}
					if (endPoint + 1 <= 18 && (Game[i][endPoint + 1] == '+')) // �����϶�
					{
						Bhelp[i][endPoint + 1] = 'o'; // ����!
					}
				}
			}

		}//-------------------------------------------------------------------------------------------------

		int max = 0;

		for (int k = 0; k < 19; k++)
		{
			if (list[i][k].max > max) max = list[i][k].max; // �� ó�� ���� �޺� �ƽ�ġ �����س��� -> �޺� �ɱ涧 ���� ������ �����ϸ� combo�ٲ�� ���
		} // ���Ӳ��������� combo��ġ�� max�� ����صδ°ž�

		for (int k = 0; k < 19; k++)
		{
			if (max > 1 && (list[i][k].max == max))
			{
				printf("���� %02d��° ���� �� ��ǥ ", i);  // ���� ��� ���ص� �ɵ� 

				if (list[i][k].state == 'B')
				{
					printf("B(Y,X) : ");
					for (int j = k; j <= k + list[i][k].max; j++)
					{
						if (j <= 18 && (list[i][j].state == 'B')) // �������� max�����ϴµ� ������ �������� ��� k=2, max=4-> 
						{
							printf("(%d,%d)", list[i][j].Y, list[i][j].X);
						}
					}
				}

				if (list[i][k].state == 'W')
				{
					printf("W(Y,X) : ");
					for (int j = k; j <= k + list[i][k].max; j++)
					{
						if (j <= 18 && (list[i][j].state == 'W'))
						{
							printf("(%d,%d)", list[i][j].Y, list[i][j].X);
						}
					}
				}

				if (list[i][k].state != 0) printf("\n");
			}
		}

	}
}

void CheckRTindex(char Game[][19], char Bhelp[][19], char Whelp[][19])
{
	LIST list[19][19] = { 0 };

	for (int i = 18, k = 0; i >= 0; i--, k++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0, countNone = 0;

		int startPoint = 0, endPoint = 0, nonePoint = 0; // ���� �� ���� ��ġ 

		for (int y = 1; y < 2 * k; y++)
		{
			if (y < 19 && i + y < 19) // Game[0+y][i+y]  i 18~0, k0 ++, y=0~2*k y�� �����ϴ� �� 
			{
				if (y - 1 == 0) // �� ó���϶� 
				{
					if (Game[y - 1][i + y - 1] == 'B') // y�� 1�̰� y-1�� 0�� ��Ȳ�� �� ó�� 
					{
						countB = 1;
						sumB = countB;
						startPoint = y - 1;
						endPoint = y - 1;
						list[y - 1][i + y - 1].state = 'B';
						list[y - 1][i + y - 1].Y = y - 1;
						list[y - 1][i + y - 1].X = y + i - 1;
						list[y - 1][i + y - 1].combo = 1;
					}
					else if (Game[y - 1][i + y - 1] == 'W')
					{
						countW = 1;
						sumW = countW;
						startPoint = y - 1;
						endPoint = y - 1;
						list[y - 1][i + y - 1].state = 'W';
						list[y - 1][i + y - 1].Y = y - 1;
						list[y - 1][i + y - 1].X = i + y - 1;
						list[y - 1][i + y - 1].combo = 1;
					}
					else if (Game[y - 1][i + y - 1] == '+')
					{
						nonePoint = y - 1;
						list[y - 1][i + y - 1].state = '+';
						list[y - 1][i + y - 1].Y = y - 1;
						list[y - 1][i + y - 1].X = i + y - 1;
					}
				}

				if (Game[0 + y][i + y] == Game[y - 1][i + y - 1]) // ������ ���� �� BB ++ WW  �⺻�� Game[i][y].Game[0+y][i+y]
				{
					if (Game[0 + y][i + y] == 'B')
					{
						countB++;
						countW = 0;
						endPoint = y;
						if (countB > sumB) sumB = countB;
						list[y][i + y].state = 'B';
						list[y][i + y].Y = y;
						list[y][i + y].X = i + y;
						list[y][i + y].combo = sumB;

					}
					else if (Game[y][i + y] == 'W')
					{
						countW++;
						countB = 0;
						endPoint = y;
						if (countW > sumW) sumW = countW;
						list[y][i + y].state = 'W';
						list[y][i + y].Y = y;
						list[y][i + y].X = y + i;
						list[y][i + y].combo = sumW;
					}
					else if (Game[y][y + i] == '+') // ���� 2�̻󿬼� nonepoint���� ������ ���ö����� k ���� 
					{
						if (y - 2 >= 0 && (Game[y - 2][y + i - 2] == 'B'))
						{
							list[startPoint][startPoint + i].max = list[y - 2][y + i - 2].combo; // ���� ���� ������ ������ϴµ� ���� �ִ��� max�� ����ؾ��� 
						}
						else if (y - 2 >= 0 && (Game[y - 2][y + i - 2] == 'W'))
						{
							list[startPoint][startPoint + i].max = list[y - 2][y + i - 2].combo;
						}
						countNone = 0; // ���� �ʱ�ȭ 
					}
				}
				else if (Game[y][i + y] != Game[y - 1][y + i - 1]) // WB +B BW +W B+ W+
				{
					if (Game[y][i + y] == 'B') // ���� �� ���ؼ� �������ֱ� 
					{
						if (y - 1 >= 0 && (Game[y - 1][y + i - 1] == 'W'))
						{
							list[startPoint][startPoint + i].max = list[y - 1][y + i - 1].combo; // �������� stp max ��� 

							countB = 1;
							countW = 0;
							sumB = countB;
							countNone = 0; // ���� �ʱ�ȭ 
							startPoint = y;
							list[y][i + y].state = 'B';
							list[y][i + y].Y = y;
							list[y][i + y].X = i + y;
							list[y][i + y].combo = sumB;

						}
						else  if (y - 1 >= 0 && (Game[y - 1][y + i - 1] == '+')) // AOB BOB 
						{
							if (countNone == 1) // ���� �ϳ��϶� ������ 
							{
								countB++;
								countW = 0;
								endPoint = y;
								if (countB > sumB) sumB = countB;
								list[y][y + i].state = 'B';
								list[y][y + i].Y = y;
								list[y][y + i].X = y + i;
								list[y][y + i].combo = sumB;

							}
							else if (countNone == 0)
							{
								countB = 1;
								countW = 0;
								sumB = countB;
								countNone = 0; // ���� �ʱ�ȭ 
								startPoint = y;
								list[y][y + i].state = 'B';
								list[y][y + i].Y = y;
								list[y][y + i].X = y + i;
								list[y][y + i].combo = sumB;
							}
						}
					}
					else if (Game[y][i + y] == 'W')
					{
						if (y - 1 >= 0 && (Game[y - 1][y + i - 1] == 'B'))
						{
							list[startPoint][startPoint + i].max = list[y - 1][y + i - 1].combo; // ����BW

							countW = 1;
							countB = 0;
							sumW = countW;
							countNone = 0;
							startPoint = y;
							list[y][y + i].state = 'W';
							list[y][y + i].Y = y;
							list[y][y + i].X = y + i;
							list[y][y + i].combo = sumW;
						}
						else  if (y - 1 >= 0 && (Game[y - 1][y + i - 1] == '+'))
						{
							if (countNone == 1) // ���� �ϳ��϶� ������  A0A 
							{
								countW++;
								countB = 0;
								endPoint = y;
								if (countW > sumW) sumW = countW;
								list[y][y + i].state = 'W';
								list[y][y + i].Y = y;
								list[y][y + i].X = y + i;
								list[y][y + i].combo = sumW;

							}
							else if (countNone == 0) // 00A A0A0A
							{
								countW = 1;
								countB = 0;
								sumW = countW;
								countNone = 0;
								startPoint = y;
								list[y][y + i].state = 'W';
								list[y][y + i].Y = y;
								list[y][y + i].X = y + i;
								list[y][y + i].combo = sumW;
							}
						}
					}
					else if (Game[y][y + i] == '+') // coutnone 2�� ��������ϰ� // BAO-c1 ABO-c1 AAO-c1 BBO-c1 OBO OAO 00A-c0 
					{
						countNone++; // ó�� ������ġ 

						if (countNone == 1)
						{
							nonePoint = y; //ó��������ġ ���� 

						}
						else if (countNone == 2) // �ι� ���� A0A0    AA0AA0 00AA 00A0A0 �������� ó�� POINT��ġ�� �ٽ� ���� 
						{
							countNone = 0;
							if (y - 1 >= 0 && (Game[y - 1][y + i - 1] == 'B'))
							{
								list[startPoint][startPoint + i].max = list[y - 1][y + i - 1].combo;
								y = nonePoint;
								continue;
							}
							else if (y - 1 >= 0 && (Game[y - 1][y + i - 1] == 'W'))
							{
								list[startPoint][startPoint + i].max = list[y - 1][y + i - 1].combo; // ����BW
								y = nonePoint;
								continue;
							}
						}
					}

				}
				//-------------------------------------------------------------------------------------------------------

				if (list[y][y + i].combo == 4) // �޺� 3�Ǵ� 4�϶� 
				{
					list[startPoint][startPoint + i].max = list[y][y + i].combo; //�������� �ִ�ġ ���  

					int blanckOn = 0;

					for (int j = startPoint; j <= endPoint; j++) // �ִ� 1~5�϶� 10234 // k�� j�� k�� y�� 
					{
						if (Game[j][j + i] == '+') //����������
						{
							blanckOn = 1;

							if (list[startPoint][startPoint + i].state == 'B')
							{
								Whelp[j][j + i] = 's'; // �����ִµ� �������϶� -> �鵹 �ʿ� �׸��� 
								//	if (Whelp[startPoint - 1][startPoint+i-1] == 'o') Whelp[startPoint - 1][startPoint-1+i] = '+';
								if (Whelp[endPoint + 1][endPoint + 1 + i] == 'o') Whelp[endPoint + 1][endPoint + 1 + i] = '+';
							}
							if (list[startPoint][startPoint + i].state == 'W')
							{
								Bhelp[j][j + i] = 'o';
								if (Bhelp[startPoint - 1][startPoint - 1 + i] == 'o') Bhelp[startPoint - 1][startPoint - 1 + i] = '+';
								if (Bhelp[endPoint + 1][endPoint + 1 + i] == 'o') Bhelp[endPoint + 1][endPoint + 1 + i] = '+';
							}

						}
					}

					if (blanckOn == 0) // ���� ������
					{
						if (list[startPoint][startPoint + i].state == 'B') //whelp ó���� �������϶�
						{
							if (startPoint - 1 >= 0 && (Game[startPoint - 1][startPoint + i - 1] == '+')) // �����϶�
							{
								Whelp[startPoint - 1][startPoint + i - 1] = 'o'; // ����!
							}
							if (endPoint + 1 <= 18 && (Game[endPoint + 1][endPoint + i + 1] == '+')) // �����϶�
							{
								Whelp[endPoint + 1][endPoint + i + 1] = 'o'; // ����!
							}
						}
						else if (list[startPoint][startPoint + i].state == 'W') // bhelp ó���� �鵹�϶� 
						{
							if (startPoint - 1 >= 0 && (Game[startPoint - 1][startPoint + i - 1] == '+')) // �����϶�
							{
								Bhelp[startPoint - 1][startPoint + i - 1] = 'o'; // ����! -> B�����ִ� �� 
							}
							if (endPoint + 1 <= 18 && (Game[endPoint + 1][endPoint + i + 1] == '+')) // �����϶�
							{
								Bhelp[endPoint + 1][endPoint + i + 1] = 'o'; // ����!
							}
						}
					}

				} // �޺�
				else if (list[y][y + i].combo == 3) // 3�϶� 
				{
					list[startPoint][startPoint + i].max = list[y][y + i].combo; //�������� �ִ�ġ ���  

					for (int j = startPoint; j <= endPoint; j++) // �ִ� 1~5�϶� 10234
					{
						if (Game[j][j + i] == '+') //����������
						{

							if (list[startPoint][startPoint + i].state == 'B')
							{
								Whelp[j][j + i] = 'o'; // �����ִµ� �������϶� -> �鵹 �ʿ� �׸��� 
							}
							if (list[startPoint][startPoint + i].state == 'W')
							{
								Bhelp[j][j + i] = 'o';
							}
						}
					}

					if (list[startPoint][i + startPoint].state == 'B') //whelp ó���� �������϶�
					{
						if (startPoint - 1 >= 0 && (Game[startPoint - 1][startPoint + i - 1] == '+')) // �����϶�
						{
							Whelp[startPoint - 1][startPoint + i - 1] = 'o'; // ����!
						}
						if (endPoint + 1 <= 18 && (Game[endPoint + 1][endPoint + i + 1] == '+')) // �����϶�
						{
							Whelp[endPoint + 1][endPoint + i + 1] = 'o'; // ����!
						}
					}
					else if (list[startPoint][i + startPoint].state == 'W') // bhelp ó���� �鵹�϶� 
					{
						if (startPoint - 1 >= 0 && (Game[startPoint - 1][startPoint + i - 1] == '+')) // �����϶�
						{
							Bhelp[startPoint - 1][startPoint + i - 1] = 'o'; // ����! -> B�����ִ� �� 
						}
						if (endPoint + 1 <= 18 && (Game[endPoint + 1][endPoint + i + 1] == '+')) // �����϶�
						{
							Bhelp[endPoint + 1][endPoint + i + 1] = 'o'; // ����!
						}
					}
				}

			}//-------------------------------------------------------------------------------------------------

		}

		int max = 0;

		for (int y = 0; y < 2 * k; y++)
		{
			if (y < 19 && i + y < 19)
			{
				if (list[y][i + y].max > max) max = list[y][y + i].max;
			}
		}

		for (int y = 0; y < 2 * k; y++)
		{
			if (y < 19 && i + y < 19) {

				if (max > 1 && (list[y][y + i].max == max))
				{
					printf("���� %02d��° ���� �� ��ǥ ", k);  // ���� ��� ���ص� �ɵ� 

					if (list[y][y + i].state == 'B')
					{
						printf("B(Y,X) : ");
						for (int j = y; j <= y + list[y][y + i].max; j++)
						{
							if (j <= 18 && (list[j][j + i].state == 'B')) // �������� max�����ϴµ� ������ �������� ��� k=2, max=4-> 
							{
								printf("(%d,%d)", list[j][j + i].Y, list[j][j + i].X);
							}
						}
					}

					if (list[y][y + i].state == 'W')
					{
						printf("W(Y,X) : ");
						for (int j = y; j <= y + list[y][y + i].max; j++)
						{
							if (j <= 18 && (list[j][j + i].state == 'W'))
							{
								printf("(%d,%d)", list[j][j + i].Y, list[j][j + i].X);
							}
						}
					}

					if (list[y][y + i].state != 0) printf("\n");
				}
			}
		}
	}
}
void CheckLBindex(char Game[][19], char Bhelp[][19], char Whelp[][19])
{

}
void CheckRBindex(char Game[][19], char Bhelp[][19], char Whelp[][19])
{

}
void CheckLTindex(char Game[][19], char Bhelp[][19], char Whelp[][19])
{

}


void menu(void)
{
	printf("=========================================\n");
	printf("0. �޴� ���� ���� �� �α�\n");
	printf("1. ���� �� �˷��ֱ� �� ���\n");
	printf("2. ������\n");
	printf("3. ������ �ߴ� ���� �ٽ� ������\n");
	printf("4. ���� �����ϱ�\n");
	printf("5. ���� �ε��ϱ�\n");
	printf("6. ���� �����ϱ�\n");
	printf("=========================================\n");
	printf("��ɾ� �Է� : ");

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
void helpGame(char Game[][19], char Bhelp[][19], char Whelp[][19])
{
	for (int i = 0; i < 19; i++)
	{
		for (int k = 0; k < 19; k++)
		{
			Bhelp[i][k] = Game[i][k];
			Whelp[i][k] = Game[i][k];
		}
	}

}
void printHelp(char HELP[][19])
{
	for (int i = 0; i < 19; i++) {
		for (int k = 0; k < 19; k++) {

			printf("%c", HELP[i][k]);
		}
		printf("\n");
	}
	printf("\n");
	printf("3 �Ǵ� 4 ���� ���� ���� �˷��ִ� ���� ����մϴ�.\n");
}
void PrintStack(STACK* stack, int count)
{
	for (STACK* k = stack; k != NULL; k = k->next)
	{
		printf("%c(%d,%d)->", k->stone.team, k->stone.y, k->stone.x);
	}
	printf("NULL(�� ����: %d)\n", count);
}
STACK* pushStone(STACK* push, int y, int x, char team)
{
	STACK* new = (STACK*)malloc(sizeof(STACK));
	if (new == NULL)
	{
		printf("���� �Ҵ翡 �����߽��ϴ�!\n");
		return push;
	}

	new->stone.y = y;
	new->stone.x = x;
	new->stone.team = team;

	new->next = push;
	push = new;

	return push;
}
STACK* popStone(STACK** pop)
{
	if (*pop == NULL)
	{
		printf("������ ����ֽ��ϴ�!\n");
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
	FILE* fp = fopen("save.txt", "w");
	if (fp == NULL)
	{
		printf("���� ���⿡ �����߽��ϴ�!\n");
		return;
	}

	fprintf(fp, "%d %d\n", countTop, countBack);

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

	printf("���� ������ �Ϸ��߽��ϴ�!\n");
	fclose(fp);

}
void loadGame(STACK** top, STACK** back, int* countTop, int* countBack, int* i, char Game[][19])
{
	FILE* fp = fopen("save.txt", "r");
	if (fp == NULL)
	{
		printf("���� ���⿡ �����߽��ϴ�!\n");
		return;
	}

	if (fscanf(fp, "%d %d", countTop, countBack) != 2)
	{
		printf("�Է� ����!\n");
		exit(1);
	}

	for (int i = 0; i < *countTop; i++)
	{
		STACK* new = (STACK*)malloc(sizeof(STACK));
		if (new == NULL)
		{
			printf("���� �Ҵ翡 �����߽��ϴ�!\n");
			exit(1);
		}

		if (fscanf(fp, "%d %d %c", &new->stone.y, &new->stone.x, &new->stone.team) != 3)
		{
			printf("�Է� ����!\n");
			exit(1);
		}

		new->next = *top;
		*top = new;
		Game[new->stone.y][new->stone.x] = new->stone.team;
	}

	for (int i = 0; i < *countBack; i++)
	{
		STACK* new = (STACK*)malloc(sizeof(STACK));
		if (new == NULL)
		{
			printf("���� �Ҵ翡 �����߽��ϴ�!\n");
			exit(1);
		}

		if (fscanf(fp, "%d %d %c", &new->stone.y, &new->stone.x, &new->stone.team) != 3)
		{
			printf("�Է� ����!\n");
			exit(1);
		}

		new->next = *back;
		*back = new;
	}

	*i += *countTop;

	fclose(fp);


}



// �Ⱦ��¾ֵ� - ���׷��̵� �� ����
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

} // �Ⱦ�
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

} // �Ⱦ� 
void CheckB(char Game[][19])
{
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
} // �Ⱦ� 
void CheckRTLB(char Game[][19])
{

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

}
#endif
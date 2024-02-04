#pragma once
#include<time.h>
#include<stdlib.h>
#include <stdio.h>
#include<math.h>

#define BLACK -1
#define WHITE 1
#define NONE_2020182003 0

#define BLANCK_4_2020182003 9900 // 00x00 ���ݿ켱 
#define FULL_4_2020182003 9800 // x0000x ���ݿ켱 
#define BLANCK_3_2020182003 8900
#define FULL_3_2020182003 8900 // 3���� ���� �켱���� ���� ���� -> ���� ����  


#define ATACK44_2020182003 100 
#define ATACK43_2020182003 900
#define Attack33_2020182003 800
#define Attack22_2020182003 500

/*=====��������================================================================================================== */

typedef struct LIST_2020182003 {

	int state;
	int Y, X;
	int combo;
	int max; // �޺��������� �ִ밪 ���� -> ���پ� �� 

}LIST_2020182003;
typedef struct INDEX_2020182003 {

	int y, x;
	struct INDEX_2020182003* next;

}INDEX_2020182003;

int board_2020182003[19][19];

/*======�Լ�����================================================================================================ */

INDEX_2020182003* Make_SL_2020182003(INDEX_2020182003* head, int x, int y);
void Free_SL_2020182003(INDEX_2020182003** head);
void weight_2020182003(int weight[][19], int Game[][19]);
void Rand_SL_2020182003(INDEX_2020182003* head, int* x, int* y);
int Black_Gard_Weight_2020182003(int weight[][19]);
int White_Gard_Weight_2020182003(int weight[][19]);
void init_stone_2020182003(int weight_max, int* x, int* y, int Game[][19]);
void CheckAindex_2020182003(int weight[][19], int Game[][19]);
void CheckBindex_2020182003(int weight[][19], int Game[][19]);
void CheckRTindex_2020182003(int weight[][19], int Game[][19]);
void CheckLBindex_2020182003(int weight[][19], int Game[][19]);
void CheckRBindex_2020182003(int weight[][19], int Game[][19]);
void CheckLTindex_2020182003(int weight[][19], int Game[][19]);
int PlusCompare_2020182003(int weight[][19]);
int MinusCompare_2020182003(int weight[][19]);


/*======�����Լ�=============================================================================================== */

void WhiteAttack_2020182003(int* x, int* y)
{
	srand((unsigned)time(NULL));

	int Whelp_2020182003[19][19] = { 0 };

	weight_2020182003(Whelp_2020182003, board_2020182003);

	CheckAindex_2020182003(Whelp_2020182003, board_2020182003);
	CheckBindex_2020182003(Whelp_2020182003, board_2020182003);
	CheckRTindex_2020182003(Whelp_2020182003, board_2020182003);
	CheckLBindex_2020182003(Whelp_2020182003, board_2020182003);
	CheckRBindex_2020182003(Whelp_2020182003, board_2020182003);
	CheckLTindex_2020182003(Whelp_2020182003, board_2020182003);

	int plusWhite = PlusCompare_2020182003(Whelp_2020182003); // (+)���ϱ� -> �鵹 ���� ����  
	int minusBlack = MinusCompare_2020182003(Whelp_2020182003); // (-)���ϱ� -> �浹 ���赵  

	int weight_max = 0;

	if (plusWhite == -1 || minusBlack == -1) // ���� �����Ѱ� �ִٴ� ���� 
	{
		int attack = Black_Gard_Weight_2020182003(Whelp_2020182003); // 4���� (+)�ΰ� �� �� ū��  
		int gard = White_Gard_Weight_2020182003(Whelp_2020182003); // 4 ��� (-)�ΰ� �� �� ū�� 

		if (attack == BLANCK_4_2020182003 || attack == FULL_4_2020182003) // ��ĭ 4 ���� 
		{
			weight_max = attack;
		}
		else if (gard == -BLANCK_4_2020182003 || gard == -FULL_4_2020182003) // ���ݿ켱 4�� ���� ���� ���� �ƴϸ� �� ���� 
		{
			weight_max = gard;
		}
	}
	else if (plusWhite == -2 || minusBlack == -2) // ���� �����Ѱ� �ִٴ� ���� 
	{
		int attack = Black_Gard_Weight_2020182003(Whelp_2020182003); // 4���� (+)�ΰ� �� �� ū��  
		int gard = White_Gard_Weight_2020182003(Whelp_2020182003); // 4 ��� (-)�ΰ� �� �� ū�� 

		if (attack == BLANCK_3_2020182003) // ��ĭ 4 ���� 
		{
			weight_max = attack;
		}
		else if (gard == -BLANCK_3_2020182003) // ���ݿ켱 4�� ���� ���� ���� �ƴϸ� �� ���� 
		{
			weight_max = gard;
		}
	}
	else if (plusWhite == 0 && minusBlack == 0) // �Ѵ� ����ġ ���� -> ���� 0�ΰ��� < �⺻ �� �� > 
	{
		weight_max = 0;
	}
	else if (plusWhite != 0 || minusBlack != 0)// ���� �Ѹ��� ���� �ִµ� -1�� �ƴϴϱ� ���� �� �ִ°� 
	{
		int compare = 0;

		if (abs(plusWhite) > abs(minusBlack)) // plus�� (+)�� ū�� ���ݰ��� �� ū ��� 
		{
			weight_max = Black_Gard_Weight_2020182003(Whelp_2020182003); //blackgard -> (+)��ū�� ���� -> ���� 
		}
		else if (abs(plusWhite) < abs(minusBlack)) // minus ���밪�� �� ū��� -> �浹 ���赵 < ����ؾ��� Ÿ�̹� > 
		{
			weight_max = White_Gard_Weight_2020182003(Whelp_2020182003); // (-)�� �� ũ�� ����ؾ��� Ÿ�̹� 
		}
		else
		{
			weight_max = Black_Gard_Weight_2020182003(Whelp_2020182003); // �������� �������� ������ �⺻���� ���� ���� ���ܰ� ������ �𸦶� ���°� 

			if (weight_max == 0)
			{
				weight_max = White_Gard_Weight_2020182003(Whelp_2020182003);
			}
		}
	}



	INDEX_2020182003* head = NULL;

	for (int y = 0; y < 19; y++)
	{
		for (int x = 0; x < 19; x++)
		{
			if (board_2020182003[y][x] == NONE_2020182003 && weight_max != 0 && Whelp_2020182003[y][x] == weight_max) // ����ġ�� �����ε� -> ����ġ ���Լ� ���� �� 
			{
				head = Make_SL_2020182003(head, x, y);
			}
		}
	}

	Rand_SL_2020182003(head, &(*x), &(*y)); // �� �δ� ��ǥ�� �ּ� 
	Free_SL_2020182003(&head);
	init_stone_2020182003(weight_max, &(*x), &(*y), board_2020182003);

	board_2020182003[*y][*x] = WHITE;
}

void BlackAttack_2020182003(int* x, int* y)
{
	srand((unsigned)time(NULL));

	int Bhelp_2020182003[19][19] = { 0 };

	// �� �θ� �⺻ ����ġ 
	weight_2020182003(Bhelp_2020182003, board_2020182003);
	// ���赵�� üũ�ؼ� ����ġ ��ȭ
	CheckAindex_2020182003(Bhelp_2020182003, board_2020182003);
	CheckBindex_2020182003(Bhelp_2020182003, board_2020182003);
	CheckRTindex_2020182003(Bhelp_2020182003, board_2020182003);
	CheckLBindex_2020182003(Bhelp_2020182003, board_2020182003);
	CheckRBindex_2020182003(Bhelp_2020182003, board_2020182003);
	CheckLTindex_2020182003(Bhelp_2020182003, board_2020182003);

	int plusWhite = PlusCompare_2020182003(Bhelp_2020182003); // (+)���ϱ� -> �鵹 ���� ����  
	int minusBlack = MinusCompare_2020182003(Bhelp_2020182003); // (-)���ϱ� -> �浹 ���赵  

	int weight_max = 0;

	if (plusWhite == -1 || minusBlack == -1) // 4 �����̰ų� ����ų� 
	{
		int attack = White_Gard_Weight_2020182003(Bhelp_2020182003);  // �鵹�� ���ƾ��� �� -> �浹���� ���� 
		int gard = Black_Gard_Weight_2020182003(Bhelp_2020182003); // �� -> (+)�� �� ū�� 

		if (attack == -BLANCK_4_2020182003 || attack == -FULL_4_2020182003) // ��ĭ 4 ���� (-) ������ �� 
		{
			weight_max = attack; // -9900�̰ų� -9800�� ��쿡 ���� 
		}
		else if (gard == BLANCK_4_2020182003 || gard == FULL_4_2020182003) // ���ݿ켱 4�� ���� ���� ���� �ƴϸ� �� ���� 
		{
			weight_max = gard; // ���� �����ѵ� ����ؾߵǸ� ��� 
		}
	}
	else if (plusWhite == -2 || minusBlack == -2) // 3 ���ų� ���� ���ݿ켱 
	{
		int attack = White_Gard_Weight_2020182003(Bhelp_2020182003);  // �鵹�� ���ƾ��� �� -> �浹���� ���� 
		int gard = Black_Gard_Weight_2020182003(Bhelp_2020182003); // �� -> (+)�� �� ū�� 

		if (attack == -BLANCK_3_2020182003) // ��ĭ 4 ���� (-) ������ �� 
		{
			weight_max = attack; // -9900�̰ų� -9800�� ��쿡 ���� 
		}
		else if (gard == BLANCK_3_2020182003) // ���ݿ켱 4�� ���� ���� ���� �ƴϸ� �� ���� 
		{
			weight_max = gard; // ���� �����ѵ� ����ؾߵǸ� ��� 
		}
	}
	else if (plusWhite == 0 && minusBlack == 0) // �Ѵ� ����ġ ���� -> ���� 0�ΰ��� < �⺻ �� �� > 
	{
		weight_max = 0;
	}
	else if (plusWhite != 0 || minusBlack != 0)// ���� �Ѹ��� ���� �ִµ� -1�̳� -2�� �ƴϴϱ� ���� �� �ִ°� 
	{
		int compare = 0;

		if (abs(plusWhite) > abs(minusBlack)) // plus�� �� ŭ -> �鵹 ���ݰ��� �� ũ�� -> ������� 
		{
			weight_max = Black_Gard_Weight_2020182003(Bhelp_2020182003);
		}
		else if (abs(plusWhite) < abs(minusBlack)) // minus ���밪�� �� ū��� -> �浹 ���赵 < ����ؾ��� Ÿ�̹� > 
		{
			weight_max = White_Gard_Weight_2020182003(Bhelp_2020182003); // ���� �� ū�� -> �浹 ���� 
		}
		else // ����ġ ������ ����ġ�� 0�� �ƴѵ� ���� ��� -> ����Ʈ�� �����¡? 
		{
			weight_max = White_Gard_Weight_2020182003(Bhelp_2020182003); // - ��ū�� ��� 

			if (weight_max == 0)
			{
				weight_max = Black_Gard_Weight_2020182003(Bhelp_2020182003);
			}

		}
	}// ��� �� ����� �Ǿ��ִµ�  ����ġ ������ ����ġ�� 0�� �ƴѵ� ���� ��� �ߴµ� maxġ�� 0�̸� 


	// ����ġ �� ���� �ƽ�ġ -> ���⿡ ���� 

	INDEX_2020182003* head = NULL;

	for (int y = 0; y < 19; y++)
	{
		for (int x = 0; x < 19; x++)
		{
			if (board_2020182003[y][x] == NONE_2020182003 && weight_max != 0 && Bhelp_2020182003[y][x] == weight_max) // ����ġ �� ū��(�켱����)�� ���� ��ǥ ����  
			{
				head = Make_SL_2020182003(head, x, y);
			}
		}
	}

	Rand_SL_2020182003(head, &(*x), &(*y)); // �� �δ� ��ǥ�� �ּ� ����ġ ���� ���� 
	Free_SL_2020182003(&head);
	init_stone_2020182003(weight_max, &(*x), &(*y), board_2020182003); // ����ġ 0�� �� ������ ��ġ�� 

	board_2020182003[*y][*x] = BLACK;
}

void WhiteDefence_2020182003(int x, int y)
{
	board_2020182003[y][x] = BLACK;
}
void BlackDefence_2020182003(int x, int y)
{
	board_2020182003[y][x] = WHITE;
}

/*======�Լ�����=============================================================================================== */


// ����ġ ����ϴ� �Լ�, NONE�� ���� �� �ٲ�� �ؼ� ����ġ�� �̿��� ���� �ִ� �������� ��ĥ ���� ����
void weight_2020182003(int weight[][19], int Game[][19])
{
	for (int i = 0; i < 19; i++)
	{
		for (int k = 0; k < 19; k++)
		{
			if (Game[i][k] == WHITE)
			{
				for (int m = -1; m < 2; m++)
				{
					for (int n = -1; n < 2; n++)
					{
						if (m + i >= 0 && m + i <= 18 && n + k >= 0 && n + k <= 18)
						{
							if (Game[m + i][n + k] == NONE_2020182003)
								weight[m + i][n + k] += 2;
						}
					}
				}
			}
			else if (Game[i][k] == BLACK)
			{
				for (int m = -1; m < 2; m++)
				{
					for (int n = -1; n < 2; n++)
					{
						if (m + i >= 0 && m + i <= 18 && n + k >= 0 && n + k <= 18)
						{
							if (Game[m + i][n + k] == NONE_2020182003)
								weight[m + i][n + k] -= 2;
						}
					}
				}
			}

		}
	}
}

// ����ġ �ƽ��� ��ǥ �̱ۿ��Ḯ��Ʈ�� ���� 
INDEX_2020182003* Make_SL_2020182003(INDEX_2020182003* head, int x, int y)
{
	INDEX_2020182003* newNODE = (INDEX_2020182003*)malloc(sizeof(INDEX_2020182003));
	if (newNODE == NULL)
	{
		printf("�����Ҵ� ����\n");
		exit(1);
	}
	newNODE->x = x;
	newNODE->y = y;
	newNODE->next = head;

	head = newNODE;
	return head;
}

// �޸� Free�Լ� 
void Free_SL_2020182003(INDEX_2020182003** head)
{
	if (*head == NULL)
	{
		return;
	}

	INDEX_2020182003* cur = *head;

	while (*head != NULL)
	{
		cur = *head;
		*head = (*head)->next;
		free(cur);
	}
}

// x,y ����ġ �� ���� ���� 
void Rand_SL_2020182003(INDEX_2020182003* head, int* x, int* y)
{
	if (head == NULL)
	{
		return;
	}

	int i = 0;

	INDEX_2020182003* cur = head;

	while (cur != NULL) // 0~n-1
	{
		i++;
		cur = cur->next;
	}

	int pick = rand() % i;

	cur = head;
	i = 0;

	while (cur != NULL) // ���� -> 
	{
		if (pick == i) break;
		i++;
		cur = cur->next;
	}

	*x = cur->x;
	*y = cur->y;

}

// �˵� ���� ����ġ �ְ����� -> �� (+)��� ��ȣ���� weight > max 
int Black_Gard_Weight_2020182003(int weight[][19])
{
	int max = 0;

	for (int i = 0; i < 19; i++)
	{
		for (int k = 0; k < 19; k++)
		{
			if (weight[i][k] > max) max = weight[i][k];
		}
	}

	return max;
}

// �� ���� ����ġ �ְ����� -> �˵� (-)����  weight < max -> ������
int White_Gard_Weight_2020182003(int weight[][19])
{
	int max = 0;

	for (int i = 0; i < 19; i++)
	{
		for (int k = 0; k < 19; k++)
		{
			if (weight[i][k] < max) max = weight[i][k];
		}
	}

	return max;
}

// ����ġ 0�϶� ������ ��ġ 
void init_stone_2020182003(int weight_max, int* x, int* y, int Game[][19])
{
	if (weight_max != 0) return;

	while (1)
	{
		*x = rand() % 19;
		*y = rand() % 19;
		if (Game[*y][*x] != NONE_2020182003)
		{
			continue;
		}
		else break;

	}

}

// ���μ� ����ġ ������Ʈ - �켱���� 1. 4���ݰ��� 2. 4����Ǯ 3. 3���� 
void CheckAindex_2020182003(int weight[][19], int Game[][19])
{
	LIST_2020182003 list[19][19] = { 0 };

	for (int i = 0; i < 19; i++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0, countNone = 0;

		int startPoint = 0, endPoint = 0, nonePoint = 0; // ���� �� ���� ��ġ 

		int k = 1;

		for (k = 1; k < 19; k++)
		{
			if (k - 1 == 0)
			{
				if (Game[k - 1][i] == BLACK)
				{
					countB = 1;
					sumB = countB;
					startPoint = k - 1;
					endPoint = k - 1;
					list[k - 1][i].state = BLACK;
					list[k - 1][i].Y = 0;
					list[k - 1][i].X = i;
					list[k - 1][i].combo = 1;
				}
				else if (Game[k - 1][i] == WHITE) // �� ó�� B or W or +
				{
					countW = 1;
					sumW = countW;
					startPoint = k - 1; // ��ŸƮ 
					endPoint = k - 1; // ���� 
					list[k - 1][i].state = WHITE;
					list[k - 1][i].Y = 0;
					list[k - 1][i].X = i;
					list[k - 1][i].combo = 1;
				}
				else if (Game[k - 1][i] == NONE_2020182003) // �н� 
				{
					nonePoint = k - 1;
					list[k - 1][i].state = NONE_2020182003;
					list[k - 1][i].Y = 0;
					list[k - 1][i].X = i;
				}
			}


			if (Game[k][i] == Game[k - 1][i]) // ������ ���� �� BB ++ WW 
			{
				if (Game[k][i] == BLACK)
				{
					countB++;
					countW = 0;
					endPoint = k;
					if (countB > sumB) sumB = countB;
					list[k][i].state = BLACK;
					list[k][i].Y = k;
					list[k][i].X = i;
					list[k][i].combo = sumB;

				}
				else if (Game[k][i] == WHITE)
				{
					countW++;
					countB = 0;
					endPoint = k;
					if (countW > sumW) sumW = countW;
					list[k][i].state = WHITE;
					list[k][i].Y = k;
					list[k][i].X = i;
					list[k][i].combo = sumW;
				}
				else if (Game[k][i] == NONE_2020182003) // ���� 2�̻󿬼� nonepoint���� ������ ���ö����� k ���� 
				{
					if (k - 2 >= 0 && (Game[k - 2][i] == BLACK))
					{
						list[startPoint][i].max = list[k - 2][i].combo; // 2�� �ڿ� ���� ���� ������ ������ϴµ� ���� �ִ��� max�� ����ؾ��� 
					}
					else if (k - 2 >= 0 && (Game[k - 2][i] == WHITE))
					{
						list[startPoint][i].max = list[k - 2][i].combo;
					}
					countNone = 0; // ���� �ʱ�ȭ 
				}
			}
			else if (Game[k][i] != Game[k - 1][i]) // WB +B / BW +W / B+ W+
			{
				if (Game[k][i] == BLACK) // ���� �� ���ؼ� �������ֱ� 
				{
					if (k - 1 >= 0 && (Game[k - 1][i] == WHITE))
					{
						list[startPoint][i].max = list[k - 1][i].combo; // �������� stp max ��� 

						countB = 1; // ������ �� / ������ �� 
						countW = 0;
						sumB = countB;
						countNone = 0; // ���� �ʱ�ȭ 
						startPoint = k;
						list[k][i].state = BLACK;
						list[k][i].Y = k;
						list[k][i].X = i;
						list[k][i].combo = sumB;

					}
					else  if (k - 1 >= 0 && (Game[k - 1][i] == NONE_2020182003)) // AOB BOB 
					{
						if (countNone == 1) // ���� �ϳ��϶� ������ 
						{
							countB++;
							countW = 0;
							endPoint = k;
							if (countB > sumB) sumB = countB;
							list[k][i].state = BLACK;
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
							list[k][i].state = BLACK;
							list[k][i].Y = k;
							list[k][i].X = i;
							list[k][i].combo = sumB;
						}
					}
				}
				else if (Game[k][i] == WHITE)
				{
					if (k - 1 >= 0 && (Game[k - 1][i] == BLACK))
					{
						list[startPoint][i].max = list[k - 1][i].combo; // ����BW

						countW = 1;
						countB = 0;
						sumW = countW;
						countNone = 0;
						startPoint = k;
						list[k][i].state = BLACK;
						list[k][i].Y = k;
						list[k][i].X = i;
						list[k][i].combo = sumW;
					}
					else  if (k - 1 >= 0 && (Game[k - 1][i] == NONE_2020182003))
					{
						if (countNone == 1) // ���� �ϳ��϶� ������  A0A 
						{
							countW++;
							countB = 0;
							endPoint = k;
							if (countW > sumW) sumW = countW;
							list[k][i].state = WHITE;
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
							list[k][i].state = WHITE;
							list[k][i].Y = k;
							list[k][i].X = i;
							list[k][i].combo = sumW;
						}
					}
				}
				else if (Game[k][i] == NONE_2020182003) // coutnone 2�� ��������ϰ� // BAO-c1 ABO-c1 AAO-c1 BBO-c1 OBO OAO 00A-c0 
				{
					countNone++; // ó�� ������ġ 

					if (countNone == 1)
					{
						nonePoint = k; //ó��������ġ ���� 
					}
					else if (countNone == 2) // �ι� ���� A0A0    AA0AA0 00AA 00A0A0 �������� ó�� POINT��ġ�� �ٽ� ���� 
					{
						countNone = 0;
						if (k - 1 >= 0 && (Game[k - 1][i] == BLACK))
						{
							list[startPoint][i].max = list[k - 1][i].combo; // 01,10�϶� ���� 
							k = nonePoint;
							continue;
						}
						else if (k - 1 >= 0 && (Game[k - 1][i] == WHITE))
						{
							list[startPoint][i].max = list[k - 1][i].combo; // ����BW
							k = nonePoint;
							continue;
						}
					}
				}

			}
			//-------------------------------------------------------------------------------------------------------

			if (list[k][i].combo == 3) // 3�϶�  X00X0X ���� 8900 / ����X 8800 �ǹ̰� �ֳ�?
			{
				list[startPoint][i].max = list[k][i].combo; //�������� �ִ�ġ ���  

				for (int j = startPoint; j <= endPoint; j++) // �ִ� 1~5�϶� 10234
				{
					if (Game[j][i] == NONE_2020182003) //����������
					{

						if (list[startPoint][i].state == BLACK)
						{
							weight[j][i] = -BLANCK_3_2020182003; // �����ִµ� �������϶� -> �鵹 �ʿ� �׸��� 
						}
						if (list[startPoint][i].state == WHITE)
						{
							weight[j][i] = BLANCK_3_2020182003; //89
						}
					}
				}

				if (list[startPoint][i].state == BLACK) //whelp ó���� �������϶�
				{
					if (startPoint - 1 >= 0 && (Game[startPoint - 1][i] == NONE_2020182003)) // �����϶�
					{
						weight[startPoint - 1][i] = -FULL_3_2020182003; // 88!
					}
					if (endPoint + 1 <= 18 && (Game[endPoint + 1][i] == NONE_2020182003)) // �����϶�
					{
						weight[endPoint + 1][i] = -FULL_3_2020182003; // ����!
					}
				}
				else if (list[startPoint][i].state == WHITE) // bhelp ó���� �鵹�϶� 
				{
					if (startPoint - 1 >= 0 && (Game[startPoint - 1][i] == NONE_2020182003)) // ���� ������
					{
						weight[startPoint - 1][i] = FULL_3_2020182003; // ����! -> B�����ִ� �� 
					}
					if (endPoint + 1 <= 18 && (Game[endPoint + 1][i] == NONE_2020182003)) // �����϶�
					{
						weight[endPoint + 1][i] = FULL_3_2020182003; // ����!
					}
				}
			}
			else if (list[k][i].combo == 4) // �޺� 3�Ǵ� 4�϶� 
			{
				list[startPoint][i].max = list[k][i].combo; //�������� �ִ�ġ ���  

				int blanckOn = 0;

				for (int j = startPoint; j <= endPoint; j++) // �ִ� 1~5�϶� 10234
				{
					if (Game[j][i] == NONE_2020182003) //���������� 9900
					{
						blanckOn = 1;

						if (list[startPoint][i].state == BLACK)
						{
							weight[j][i] = -BLANCK_4_2020182003; // �浹 �ֺ� -9900 / �浹�� 00X00�� ��� -> �鵹 ���� ����ġ (-) 
						}
						if (list[startPoint][i].state == WHITE)
						{
							weight[j][i] = BLANCK_4_2020182003; // �鵹 �ֺ� 9900
						}

					}
				}

				if (blanckOn == 0) // ���� ������ 4 ���� 9800 
				{
					if (list[startPoint][i].state == BLACK) //whelp ó���� �������϶�
					{
						if (startPoint - 1 >= 0 && (Game[startPoint - 1][i] == NONE_2020182003)) // ���� ������  -> �̰� ���ϰ� NONE���� �ϸ� +-2�� ������ ����ġ �� ���� 
						{
							weight[startPoint - 1][i] = -FULL_4_2020182003; // �浹 ���� -> ������ �翷�� �����̸� -> -98
						}
						if (endPoint + 1 <= 18 && (Game[endPoint + 1][i] == NONE_2020182003)) // �����϶�
						{
							weight[endPoint + 1][i] = -FULL_4_2020182003; // ����!
						}
					}
					else if (list[startPoint][i].state == WHITE) // bhelp ó���� �鵹�϶� 
					{
						if (startPoint - 1 >= 0 && (Game[startPoint - 1][i] == NONE_2020182003)) // �����϶�
						{
							weight[startPoint - 1][i] = FULL_4_2020182003; // ����! -> B�����ִ� �� 
						}
						if (endPoint + 1 <= 18 && (Game[endPoint + 1][i] == NONE_2020182003)) // �����϶�
						{
							weight[endPoint + 1][i] = FULL_4_2020182003; // ����!
						}
					}
				}

			} // �޺�
		}
	}
}

// ���μ� ����ġ ������Ʈ
void CheckBindex_2020182003(int weight[][19], int Game[][19])
{
	LIST_2020182003 list[19][19] = { 0 };

	for (int i = 0; i < 19; i++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0, countNone = 0;

		int startPoint = 0, endPoint = 0, nonePoint = 0; // ���� �� ���� ��ġ 

		int k = 1;

		for (k = 1; k < 19; k++)
		{
			if (k - 1 == 0)
			{
				if (Game[i][k - 1] == BLACK)
				{
					countB = 1;
					sumB = countB;
					startPoint = k - 1;
					endPoint = k - 1;
					list[i][k - 1].state = BLACK;
					list[i][k - 1].Y = i;
					list[i][k - 1].X = 0;
					list[i][k - 1].combo = 1;
				}
				else if (Game[i][k - 1] == WHITE) // �� ó�� B or W or +
				{
					countW = 1;
					sumW = countW;
					startPoint = k - 1;
					endPoint = k - 1;
					list[i][k - 1].state = WHITE;
					list[i][k - 1].Y = i;
					list[i][k - 1].X = 0;
					list[i][k - 1].combo = 1;
				}
				else if (Game[i][k - 1] == NONE_2020182003) // �н� 
				{
					nonePoint = k - 1;
					list[i][k - 1].state = NONE_2020182003;
					list[i][k - 1].Y = i;
					list[i][k - 1].X = 0;
				}
			}


			if (Game[i][k] == Game[i][k - 1]) // ������ ���� �� BB ++ WW 
			{
				if (Game[i][k] == BLACK)
				{
					countB++;
					countW = 0;
					endPoint = k;
					if (countB > sumB) sumB = countB;
					list[i][k].state = BLACK;
					list[i][k].Y = i;
					list[i][k].X = k;
					list[i][k].combo = sumB;

				}
				else if (Game[i][k] == WHITE)
				{
					countW++;
					countB = 0;
					endPoint = k;
					if (countW > sumW) sumW = countW;
					list[i][k].state = WHITE;
					list[i][k].Y = i;
					list[i][k].X = k;
					list[i][k].combo = sumW;
				}
				else if (Game[i][k] == NONE_2020182003) // ���� 2�̻󿬼� nonepoint���� ������ ���ö����� k ���� 
				{
					if (k - 2 >= 0 && (Game[i][k - 2] == BLACK))
					{
						list[i][startPoint].max = list[i][k - 2].combo; // ���� ���� ������ ������ϴµ� ���� �ִ��� max�� ����ؾ��� 
					}
					else if (k - 2 >= 0 && (Game[i][k - 2] == WHITE))
					{
						list[i][startPoint].max = list[i][k - 2].combo;
					}
					countNone = 0; // ���� �ʱ�ȭ 
				}
			}
			else if (Game[i][k] != Game[i][k - 1]) // WB +B BW +W B+ W+
			{
				if (Game[i][k] == BLACK) // ���� �� ���ؼ� �������ֱ� 
				{
					if (k - 1 >= 0 && (Game[i][k - 1] == WHITE))
					{
						list[i][startPoint].max = list[i][k - 1].combo; // �������� stp max ��� 

						countB = 1;
						countW = 0;
						sumB = countB;
						countNone = 0; // ���� �ʱ�ȭ 
						startPoint = k;
						list[i][k].state = BLACK;
						list[i][k].Y = i;
						list[i][k].X = k;
						list[i][k].combo = sumB;

					}
					else  if (k - 1 >= 0 && (Game[i][k - 1] == NONE_2020182003)) // AOB BOB 
					{
						if (countNone == 1) // ���� �ϳ��϶� ������ 
						{
							countB++;
							countW = 0;
							endPoint = k;
							if (countB > sumB) sumB = countB;
							list[i][k].state = BLACK;
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
							list[i][k].state = BLACK;
							list[i][k].Y = i;
							list[i][k].X = k;
							list[i][k].combo = sumB;
						}
					}
				}
				else if (Game[i][k] == WHITE)
				{
					if (k - 1 >= 0 && (Game[i][k - 1] == BLACK))
					{
						list[i][startPoint].max = list[i][k - 1].combo; // ����BW

						countW = 1;
						countB = 0;
						sumW = countW;
						countNone = 0;
						startPoint = k;
						list[i][k].state = WHITE;
						list[i][k].Y = i;
						list[i][k].X = k;
						list[i][k].combo = sumW;
					}
					else  if (k - 1 >= 0 && (Game[i][k - 1] == NONE_2020182003))
					{
						if (countNone == 1) // ���� �ϳ��϶� ������  A0A 
						{
							countW++;
							countB = 0;
							endPoint = k;
							if (countW > sumW) sumW = countW;
							list[i][k].state = WHITE;
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
							list[i][k].state = WHITE;
							list[i][k].Y = i;
							list[i][k].X = k;
							list[i][k].combo = sumW;
						}
					}
				}
				else if (Game[i][k] == NONE_2020182003) // coutnone 2�� ��������ϰ� // BAO-c1 ABO-c1 AAO-c1 BBO-c1 OBO OAO 00A-c0 
				{
					countNone++; // ó�� ������ġ 

					if (countNone == 1)
					{
						nonePoint = k; //ó��������ġ ���� 

					}
					else if (countNone == 2) // �ι� ���� A0A0    AA0AA0 00AA 00A0A0 �������� ó�� POINT��ġ�� �ٽ� ���� 
					{
						countNone = 0;
						if (k - 1 >= 0 && (Game[i][k - 1] == BLACK))
						{
							list[i][startPoint].max = list[i][k - 1].combo;
							k = nonePoint; // ó�� ������ġ�� �ٽ� for�� 
							continue;
						}
						else if (k - 1 >= 0 && (Game[i][k - 1] == WHITE))
						{
							list[i][startPoint].max = list[i][k - 1].combo; // ����BW
							k = nonePoint;
							continue;
						}
					}
				}

			}
			//-------------------------------------------------------------------------------------------------------

			if (list[i][k].combo == 3) // 3�϶�  3�϶� �ѹ� �����Ѱ��� ���� ���� oBBOBO�ε� OBBOBB
			{
				list[i][startPoint].max = list[i][k].combo; //�������� �ִ�ġ ���  

				for (int j = startPoint; j <= endPoint; j++) // �ִ� 1~5�϶� 10234
				{
					if (Game[i][j] == NONE_2020182003) //����������
					{

						if (list[i][startPoint].state == BLACK)
						{
							weight[i][j] = -BLANCK_3_2020182003; // �����ִµ� �������϶� -> �鵹 �ʿ� �׸��� 
						}
						if (list[i][startPoint].state == WHITE)
						{
							weight[i][j] = BLANCK_3_2020182003;
						}
					}
				}

				if (list[i][startPoint].state == BLACK) //whelp ó���� �������϶�
				{
					if (startPoint - 1 >= 0 && (Game[i][startPoint - 1] == NONE_2020182003)) // �����϶�
					{
						weight[i][startPoint - 1] = -FULL_3_2020182003; // ����!
					}
					if (endPoint + 1 <= 18 && (Game[i][endPoint + 1] == NONE_2020182003)) // �����϶�
					{
						weight[i][endPoint + 1] = -FULL_3_2020182003; // ����!
					}
				}
				else if (list[i][startPoint].state == WHITE) // bhelp ó���� �鵹�϶� 
				{
					if (startPoint - 1 >= 0 && (Game[i][startPoint - 1] == NONE_2020182003)) // �����϶�
					{
						weight[i][startPoint - 1] = FULL_3_2020182003; // ����! -> B�����ִ� �� 
					}
					if (endPoint + 1 <= 18 && (Game[i][endPoint + 1] == NONE_2020182003)) // �����϶�
					{
						weight[i][endPoint + 1] = FULL_3_2020182003; // ����!
					}
				}
			}
			else if (list[i][k].combo == 4) // �޺� 3�Ǵ� 4�϶� 
			{
				list[i][startPoint].max = list[i][k].combo; //�������� �ִ�ġ ���  

				int blanckOn = 0;

				for (int j = startPoint; j <= endPoint; j++) // �ִ� 1~5�϶� 10234
				{
					if (Game[i][j] == NONE_2020182003) //����������
					{
						blanckOn = 1;

						if (list[i][startPoint].state == BLACK)
						{
							weight[i][j] = -BLANCK_4_2020182003; // �����ִµ� �������϶� -> �鵹 �ʿ� �׸��� 
						}
						if (list[i][startPoint].state == WHITE)
						{
							weight[i][j] = BLANCK_4_2020182003;
						}

					}
				}

				if (blanckOn == 0) // ���� ������
				{
					if (list[i][startPoint].state == BLACK) //whelp ó���� �������϶�
					{
						if (startPoint - 1 >= 0 && (Game[i][startPoint - 1] == NONE_2020182003)) // �����϶�
						{
							weight[i][startPoint - 1] = -FULL_4_2020182003; // ����!
						}
						if (endPoint + 1 <= 18 && (Game[i][endPoint + 1] == NONE_2020182003)) // �����϶�
						{
							weight[i][endPoint + 1] = -FULL_4_2020182003; // ����!
						}
					}
					else if (list[i][startPoint].state == WHITE) // bhelp ó���� �鵹�϶� 
					{
						if (startPoint - 1 >= 0 && (Game[i][startPoint - 1] == NONE_2020182003)) // �����϶�
						{
							weight[i][startPoint - 1] = FULL_4_2020182003; // ����! -> B�����ִ� �� 
						}
						if (endPoint + 1 <= 18 && (Game[i][endPoint + 1] == NONE_2020182003)) // �����϶�
						{
							weight[i][endPoint + 1] = FULL_4_2020182003; // ����!
						}
					}
				}

			} // �޺�
		}
	}
}

// ���� �밢�� ����ġ ������Ʈ 
void CheckRTindex_2020182003(int weight[][19], int Game[][19])
{
	LIST_2020182003 list[19][19] = { 0 };

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
					if (Game[y - 1][i + y - 1] == BLACK) // y�� 1�̰� y-1�� 0�� ��Ȳ�� �� ó�� 
					{
						countB = 1;
						sumB = countB;
						startPoint = y - 1;
						endPoint = y - 1;
						list[y - 1][i + y - 1].state = BLACK;
						list[y - 1][i + y - 1].Y = y - 1;
						list[y - 1][i + y - 1].X = y + i - 1;
						list[y - 1][i + y - 1].combo = 1;
					}
					else if (Game[y - 1][i + y - 1] == WHITE)
					{
						countW = 1;
						sumW = countW;
						startPoint = y - 1;
						endPoint = y - 1;
						list[y - 1][i + y - 1].state = WHITE;
						list[y - 1][i + y - 1].Y = y - 1;
						list[y - 1][i + y - 1].X = i + y - 1;
						list[y - 1][i + y - 1].combo = 1;
					}
					else if (Game[y - 1][i + y - 1] == NONE_2020182003)
					{
						nonePoint = y - 1;
						list[y - 1][i + y - 1].state = NONE_2020182003;
						list[y - 1][i + y - 1].Y = y - 1;
						list[y - 1][i + y - 1].X = i + y - 1;
					}
				}

				if (Game[0 + y][i + y] == Game[y - 1][i + y - 1]) // ������ ���� �� BB ++ WW  �⺻�� Game[i][y].Game[0+y][i+y]
				{
					if (Game[0 + y][i + y] == BLACK)
					{
						countB++;
						countW = 0;
						endPoint = y;
						if (countB > sumB) sumB = countB;
						list[y][i + y].state = BLACK;
						list[y][i + y].Y = y;
						list[y][i + y].X = i + y;
						list[y][i + y].combo = sumB;

					}
					else if (Game[y][i + y] == WHITE)
					{
						countW++;
						countB = 0;
						endPoint = y;
						if (countW > sumW) sumW = countW;
						list[y][i + y].state = WHITE;
						list[y][i + y].Y = y;
						list[y][i + y].X = y + i;
						list[y][i + y].combo = sumW;
					}
					else if (Game[y][y + i] == NONE_2020182003) // ���� 2�̻󿬼� nonepoint���� ������ ���ö����� k ���� 
					{
						if (y - 2 >= 0 && (Game[y - 2][y + i - 2] == BLACK))
						{
							list[startPoint][startPoint + i].max = list[y - 2][y + i - 2].combo; // ���� ���� ������ ������ϴµ� ���� �ִ��� max�� ����ؾ��� 
						}
						else if (y - 2 >= 0 && (Game[y - 2][y + i - 2] == WHITE))
						{
							list[startPoint][startPoint + i].max = list[y - 2][y + i - 2].combo;
						}
						countNone = 0; // ���� �ʱ�ȭ 
					}
				}
				else if (Game[y][i + y] != Game[y - 1][y + i - 1]) // WB +B BW +W B+ W+
				{
					if (Game[y][i + y] == BLACK) // ���� �� ���ؼ� �������ֱ� 
					{
						if (y - 1 >= 0 && (Game[y - 1][y + i - 1] == WHITE))
						{
							list[startPoint][startPoint + i].max = list[y - 1][y + i - 1].combo; // �������� stp max ��� 

							countB = 1;
							countW = 0;
							sumB = countB;
							countNone = 0; // ���� �ʱ�ȭ 
							startPoint = y;
							list[y][i + y].state = BLACK;
							list[y][i + y].Y = y;
							list[y][i + y].X = i + y;
							list[y][i + y].combo = sumB;

						}
						else  if (y - 1 >= 0 && (Game[y - 1][y + i - 1] == NONE_2020182003)) // AOB BOB 
						{
							if (countNone == 1) // ���� �ϳ��϶� ������ 
							{
								countB++;
								countW = 0;
								endPoint = y;
								if (countB > sumB) sumB = countB;
								list[y][y + i].state = BLACK;
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
								list[y][y + i].state = BLACK;
								list[y][y + i].Y = y;
								list[y][y + i].X = y + i;
								list[y][y + i].combo = sumB;
							}
						}
					}
					else if (Game[y][i + y] == WHITE)
					{
						if (y - 1 >= 0 && (Game[y - 1][y + i - 1] == BLACK))
						{
							list[startPoint][startPoint + i].max = list[y - 1][y + i - 1].combo; // ����BW

							countW = 1;
							countB = 0;
							sumW = countW;
							countNone = 0;
							startPoint = y;
							list[y][y + i].state = WHITE;
							list[y][y + i].Y = y;
							list[y][y + i].X = y + i;
							list[y][y + i].combo = sumW;
						}
						else  if (y - 1 >= 0 && (Game[y - 1][y + i - 1] == NONE_2020182003))
						{
							if (countNone == 1) // ���� �ϳ��϶� ������  A0A 
							{
								countW++;
								countB = 0;
								endPoint = y;
								if (countW > sumW) sumW = countW;
								list[y][y + i].state = WHITE;
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
								list[y][y + i].state = WHITE;
								list[y][y + i].Y = y;
								list[y][y + i].X = y + i;
								list[y][y + i].combo = sumW;
							}
						}
					}
					else if (Game[y][y + i] == NONE_2020182003) // coutnone 2�� ��������ϰ� // BAO-c1 ABO-c1 AAO-c1 BBO-c1 OBO OAO 00A-c0 
					{
						countNone++; // ó�� ������ġ 

						if (countNone == 1)
						{
							nonePoint = y; //ó��������ġ ���� 

						}
						else if (countNone == 2) // �ι� ���� A0A0    AA0AA0 00AA 00A0A0 �������� ó�� POINT��ġ�� �ٽ� ���� 
						{
							countNone = 0;
							if (y - 1 >= 0 && (Game[y - 1][y + i - 1] == BLACK))
							{
								list[startPoint][startPoint + i].max = list[y - 1][y + i - 1].combo;
								y = nonePoint;
								continue;
							}
							else if (y - 1 >= 0 && (Game[y - 1][y + i - 1] == WHITE))
							{
								list[startPoint][startPoint + i].max = list[y - 1][y + i - 1].combo; // ����BW
								y = nonePoint;
								continue;
							}
						}
					}

				}
				//-------------------------------------------------------------------------------------------------------

				 // �޺�
				if (list[y][y + i].combo == 3) // 3�϶� 
				{
					list[startPoint][startPoint + i].max = list[y][y + i].combo; //�������� �ִ�ġ ���  

					for (int j = startPoint; j <= endPoint; j++) // �ִ� 1~5�϶� 10234
					{
						if (Game[j][j + i] == NONE_2020182003) //����������
						{

							if (list[startPoint][startPoint + i].state == BLACK)
							{
								weight[j][j + i] = -BLANCK_3_2020182003; // �����ִµ� �������϶� -> �鵹 �ʿ� �׸��� 
							}
							if (list[startPoint][startPoint + i].state == WHITE)
							{
								weight[j][j + i] = BLANCK_3_2020182003;
							}
						}
					}

					if (list[startPoint][i + startPoint].state == BLACK) //whelp ó���� �������϶�
					{
						if (startPoint - 1 >= 0 && (Game[startPoint - 1][startPoint + i - 1] == NONE_2020182003)) // �����϶�
						{
							weight[startPoint - 1][startPoint + i - 1] = -FULL_3_2020182003; // ����!
						}
						if (endPoint + 1 <= 18 && (Game[endPoint + 1][endPoint + i + 1] == NONE_2020182003)) // �����϶�
						{
							weight[endPoint + 1][endPoint + i + 1] = -FULL_3_2020182003; // ����!
						}
					}
					else if (list[startPoint][i + startPoint].state == WHITE) // bhelp ó���� �鵹�϶� 
					{
						if (startPoint - 1 >= 0 && (Game[startPoint - 1][startPoint + i - 1] == NONE_2020182003)) // �����϶�
						{
							weight[startPoint - 1][startPoint + i - 1] = FULL_3_2020182003; // ����! -> B�����ִ� �� 
						}
						if (endPoint + 1 <= 18 && (Game[endPoint + 1][endPoint + i + 1] == NONE_2020182003)) // �����϶�
						{
							weight[endPoint + 1][endPoint + i + 1] = FULL_3_2020182003; // ����!
						}
					}
				}
				else if (list[y][y + i].combo == 4) // �޺� 3�Ǵ� 4�϶� 
				{
					list[startPoint][startPoint + i].max = list[y][y + i].combo; //�������� �ִ�ġ ���  

					int blanckOn = 0;

					for (int j = startPoint; j <= endPoint; j++) // �ִ� 1~5�϶� 10234 // k�� j�� k�� y�� 
					{
						if (Game[j][j + i] == NONE_2020182003) //����������
						{
							blanckOn = 1;

							if (list[startPoint][startPoint + i].state == BLACK)
							{
								weight[j][j + i] = -BLANCK_4_2020182003; // �����ִµ� �������϶� -> �鵹 �ʿ� �׸��� 
							}
							if (list[startPoint][startPoint + i].state == WHITE)
							{
								weight[j][j + i] = BLANCK_4_2020182003;
							}

						}
					}

					if (blanckOn == 0) // ���� ������
					{
						if (list[startPoint][startPoint + i].state == BLACK) //whelp ó���� �������϶�
						{
							if (startPoint - 1 >= 0 && (Game[startPoint - 1][startPoint + i - 1] == NONE_2020182003)) // �����϶�
							{
								weight[startPoint - 1][startPoint + i - 1] = -FULL_4_2020182003; // ����!
							}
							if (endPoint + 1 <= 18 && (Game[endPoint + 1][endPoint + i + 1] == NONE_2020182003)) // �����϶�
							{
								weight[endPoint + 1][endPoint + i + 1] = -FULL_4_2020182003; // ����!
							}
						}
						else if (list[startPoint][startPoint + i].state == WHITE) // bhelp ó���� �鵹�϶� 
						{
							if (startPoint - 1 >= 0 && (Game[startPoint - 1][startPoint + i - 1] == NONE_2020182003)) // �����϶�
							{
								weight[startPoint - 1][startPoint + i - 1] = FULL_4_2020182003; // ����! -> B�����ִ� �� 
							}
							if (endPoint + 1 <= 18 && (Game[endPoint + 1][endPoint + i + 1] == NONE_2020182003)) // �����϶�
							{
								weight[endPoint + 1][endPoint + i + 1] = FULL_4_2020182003; // ����!
							}
						}
					}
				}
			}
		}
	}
}

// ���ϴ� �밢�� ����ġ ������Ʈ 
void CheckLBindex_2020182003(int weight[][19], int Game[][19])
{
	LIST_2020182003 list[19][19] = { 0 };

	for (int i = 18, k = 0; i > 0; i--, k++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0, countNone = 0;

		int startPoint = 0, endPoint = 0, nonePoint = 0; // ���� �� ���� ��ġ 

		for (int y = 1; y < 2 * k; y++)
		{
			if (y < 19 && i + y < 19) // Game[0+y][i+y]  i 18~0, k0 ++, y=0~2*k y�� �����ϴ� �� 
			{
				if (y - 1 == 0) // �� ó���϶� 
				{
					if (Game[i + y - 1][y - 1] == BLACK) // y�� 1�̰� y-1�� 0�� ��Ȳ�� �� ó�� 
					{
						countB = 1;
						sumB = countB;
						startPoint = y - 1;
						endPoint = y - 1;
						list[i + y - 1][y - 1].state = BLACK;
						list[i + y - 1][y - 1].Y = y - 1 + i;
						list[i + y - 1][y - 1].X = y - 1;
						list[i + y - 1][y - 1].combo = 1;
					}
					else if (Game[i + y - 1][y - 1] == WHITE)
					{
						countW = 1;
						sumW = countW;
						startPoint = y - 1;
						endPoint = y - 1;
						list[i + y - 1][y - 1].state = WHITE;
						list[i + y - 1][y - 1].Y = i + y - 1;
						list[i + y - 1][y - 1].X = y - 1;
						list[i + y - 1][y - 1].combo = 1;
					}
					else if (Game[i + y - 1][y - 1] == NONE_2020182003)
					{
						nonePoint = y - 1;
						list[i + y - 1][y - 1].state = NONE_2020182003;
						list[i + y - 1][y - 1].Y = i + y - 1;
						list[i + y - 1][y - 1].X = y - 1;
					}
				}

				if (Game[i + y][0 + y] == Game[i + y - 1][y - 1]) // ������ ���� �� BB ++ WW  �⺻�� Game[i][y].Game[0+y][i+y]
				{
					if (Game[i + y][0 + y] == BLACK)
					{
						countB++;
						countW = 0;
						endPoint = y;
						if (countB > sumB) sumB = countB;
						list[i + y][y].state = BLACK;
						list[i + y][y].Y = y + i;
						list[i + y][y].X = y;
						list[i + y][y].combo = sumB;

					}
					else if (Game[y + i][0 + y] == WHITE)
					{
						countW++;
						countB = 0;
						endPoint = y;
						if (countW > sumW) sumW = countW;
						list[i + y][y].state = WHITE;
						list[i + y][y].Y = y + i;
						list[i + y][y].X = y;
						list[i + y][y].combo = sumW;
					}
					else if (Game[y + i][y + 0] == NONE_2020182003) // ���� 2�̻󿬼� nonepoint���� ������ ���ö����� k ���� 
					{
						if (y - 2 >= 0 && (Game[y - 2 + i][y - 2] == BLACK))
						{
							list[startPoint + i][startPoint].max = list[y - 2 + i][y - 2].combo; // ���� ���� ������ ������ϴµ� ���� �ִ��� max�� ����ؾ��� 
						}
						else if (y - 2 >= 0 && (Game[y - 2 + i][y - 2] == WHITE))
						{
							list[startPoint + i][startPoint].max = list[y - 2 + i][y - 2].combo;
						}
						countNone = 0; // ���� �ʱ�ȭ 
					}
				}
				else if (Game[y + i][y] != Game[y - 1 + i][y - 1]) // WB +B BW +W B+ W+
				{
					if (Game[y + i][y] == BLACK) // ���� �� ���ؼ� �������ֱ� 
					{
						if (y - 1 >= 0 && (Game[y - 1 + i][y - 1] == WHITE))
						{
							list[startPoint + i][startPoint].max = list[y - 1 + i][y - 1].combo; // �������� stp max ��� 

							countB = 1;
							countW = 0;
							sumB = countB;
							countNone = 0; // ���� �ʱ�ȭ 
							startPoint = y;
							list[y + i][y].state = BLACK;
							list[y + i][y].Y = y + i;
							list[y + i][y].X = y;
							list[y + i][y].combo = sumB;

						}
						else  if (y - 1 >= 0 && (Game[y - 1 + i][y - 1] == NONE_2020182003)) // AOB BOB 
						{
							if (countNone == 1) // ���� �ϳ��϶� ������ 
							{
								countB++;
								countW = 0;
								endPoint = y;
								if (countB > sumB) sumB = countB;
								list[y + i][y].state = BLACK;
								list[y + i][y].Y = y + i;
								list[y + i][y].X = y;
								list[y + i][y].combo = sumB;

							}
							else if (countNone == 0)
							{
								countB = 1;
								countW = 0;
								sumB = countB;
								countNone = 0; // ���� �ʱ�ȭ 
								startPoint = y;
								list[y + i][y].state = BLACK;
								list[y + i][y].Y = y + i;
								list[y + i][y].X = y;
								list[y + i][y].combo = sumB;
							}
						}
					}
					else if (Game[y + i][y] == WHITE)
					{
						if (y - 1 >= 0 && (Game[y - 1 + i][y - 1] == BLACK))
						{
							list[startPoint + i][startPoint].max = list[y - 1 + i][y - 1].combo; // ����BW

							countW = 1;
							countB = 0;
							sumW = countW;
							countNone = 0;
							startPoint = y;
							list[y + i][y].state = WHITE;
							list[y + i][y].Y = y + i;
							list[y + i][y].X = y;
							list[y + i][y].combo = sumW;
						}
						else  if (y - 1 >= 0 && (Game[y - 1 + i][y - 1] == NONE_2020182003))
						{
							if (countNone == 1) // ���� �ϳ��϶� ������  A0A 
							{
								countW++;
								countB = 0;
								endPoint = y;
								if (countW > sumW) sumW = countW;
								list[y + i][y].state = WHITE;
								list[y + i][y].Y = y + i;
								list[y + i][y].X = y;
								list[y + i][y].combo = sumW;

							}
							else if (countNone == 0) // 00A A0A0A
							{
								countW = 1;
								countB = 0;
								sumW = countW;
								countNone = 0;
								startPoint = y;
								list[y + i][y].state = WHITE;
								list[y + i][y].Y = y + i;
								list[y + i][y].X = y;
								list[y + i][y].combo = sumW;
							}
						}
					}
					else if (Game[y + i][y] == NONE_2020182003) // coutnone 2�� ��������ϰ� // BAO-c1 ABO-c1 AAO-c1 BBO-c1 OBO OAO 00A-c0 
					{
						countNone++; // ó�� ������ġ 

						if (countNone == 1)
						{
							nonePoint = y; //ó��������ġ ���� 

						}
						else if (countNone == 2) // �ι� ���� A0A0    AA0AA0 00AA 00A0A0 �������� ó�� POINT��ġ�� �ٽ� ���� 
						{
							countNone = 0;
							if (y - 1 >= 0 && (Game[y - 1 + i][y - 1] == BLACK))
							{
								list[startPoint + i][startPoint].max = list[y - 1 + i][y - 1].combo;
								y = nonePoint;
								continue;
							}
							else if (y - 1 >= 0 && (Game[y - 1 + i][y - 1] == WHITE))
							{
								list[startPoint + i][startPoint].max = list[y - 1 + i][y - 1].combo; // ����BW
								y = nonePoint;
								continue;
							}
						}
					}

				}
				//-------------------------------------------------------------------------------------------------------

				 // �޺�
				if (list[y + i][y].combo == 3) // 3�϶� 
				{
					list[startPoint + i][startPoint].max = list[y + i][y].combo; //�������� �ִ�ġ ���  

					for (int j = startPoint; j <= endPoint; j++) // �ִ� 1~5�϶� 10234
					{
						if (Game[j + i][j] == NONE_2020182003) //����������
						{

							if (list[startPoint + i][startPoint].state == BLACK)
							{
								weight[j + i][j] = -BLANCK_3_2020182003; // �����ִµ� �������϶� -> �鵹 �ʿ� �׸��� 
							}
							if (list[startPoint + i][startPoint].state == WHITE)
							{
								weight[j + i][j] = BLANCK_3_2020182003;
							}
						}
					}

					if (list[startPoint + i][startPoint].state == BLACK) //whelp ó���� �������϶�
					{
						if (startPoint - 1 >= 0 && (Game[startPoint - 1 + i][startPoint - 1] == NONE_2020182003)) // �����϶�
						{
							weight[startPoint - 1 + i][startPoint - 1] = -FULL_3_2020182003; // ����!
						}
						if (endPoint + 1 <= 18 && (Game[endPoint + 1 + i][endPoint + 1] == NONE_2020182003)) // �����϶�
						{
							weight[endPoint + 1 + i][endPoint + 1] = -FULL_3_2020182003; // ����!
						}
					}
					else if (list[startPoint + i][startPoint].state == WHITE) // bhelp ó���� �鵹�϶� 
					{
						if (startPoint - 1 >= 0 && (Game[startPoint - 1 + i][startPoint - 1] == NONE_2020182003)) // �����϶�
						{
							weight[startPoint - 1 + i][startPoint - 1] = FULL_3_2020182003; // ����! -> B�����ִ� �� 
						}
						if (endPoint + 1 <= 18 && (Game[endPoint + 1 + i][endPoint + 1] == NONE_2020182003)) // �����϶�
						{
							weight[endPoint + 1 + i][endPoint + 1] = FULL_3_2020182003; // ����!
						}
					}
				}
				else if (list[y + i][y].combo == 4) // �޺� 3�Ǵ� 4�϶� 
				{
					list[startPoint + i][startPoint].max = list[y + i][y].combo; //�������� �ִ�ġ ���  

					int blanckOn = 0;

					for (int j = startPoint; j <= endPoint; j++) // �ִ� 1~5�϶� 10234 // k�� j�� k�� y�� 
					{
						if (Game[j + i][j] == NONE_2020182003) //����������
						{
							blanckOn = 1;

							if (list[startPoint + i][startPoint].state == BLACK)
							{
								weight[j + i][j] = -BLANCK_4_2020182003; // �����ִµ� �������϶� -> �鵹 �ʿ� �׸��� 
							}
							if (list[startPoint + i][startPoint].state == WHITE)
							{
								weight[j + i][j] = BLANCK_4_2020182003;
							}

						}
					}

					if (blanckOn == 0) // ���� ������
					{
						if (list[startPoint + i][startPoint].state == BLACK) //whelp ó���� �������϶�
						{
							if (startPoint - 1 >= 0 && (Game[startPoint - 1 + i][startPoint - 1] == NONE_2020182003)) // �����϶�
							{
								weight[startPoint - 1 + i][startPoint - 1] = -FULL_4_2020182003; // ����!
							}
							if (endPoint + 1 <= 18 && (Game[endPoint + 1 + i][endPoint + 1] == NONE_2020182003)) // �����϶�
							{
								weight[endPoint + 1 + i][endPoint + 1] = -FULL_4_2020182003; // ����!
							}
						}
						else if (list[startPoint + i][startPoint].state == WHITE) // bhelp ó���� �鵹�϶� 
						{
							if (startPoint - 1 >= 0 && (Game[startPoint - 1 + i][startPoint - 1] == NONE_2020182003)) // �����϶�
							{
								weight[startPoint - 1 + i][startPoint - 1] = FULL_4_2020182003; // ����! -> B�����ִ� �� 
							}
							if (endPoint + 1 <= 18 && (Game[endPoint + 1 + i][endPoint + 1] == NONE_2020182003)) // �����϶�
							{
								weight[endPoint + 1 + i][endPoint + 1] = FULL_4_2020182003; // ����!
							}
						}
					}
				}
			}

		}
	}
}

// ���ϴ� �밢�� ����ġ ������Ʈ
void CheckRBindex_2020182003(int weight[][19], int Game[][19])
{
	LIST_2020182003 list[19][19] = { 0 };

	for (int i = 18, k = 0; i >= 0; i--, k++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0, countNone = 0;

		int startPoint = 0, endPoint = 0, nonePoint = 0; // ���� �� ���� ��ġ 

		for (int y = 1; y < 2 * k; y++)
		{
			if (18 - y >= 0 && i + y < 19) // Game[0+y][i+y]  i 18~0, k0 ++, y=0~2*k y�� �����ϴ� �� 
			{
				if (y - 1 == 0) // �� ó���϶� 
				{
					if (Game[18 - y + 1][i + y - 1] == BLACK) // y�� 1�̰� y-1�� 0�� ��Ȳ�� �� ó�� 
					{
						countB = 1;
						sumB = countB;
						startPoint = y - 1;
						endPoint = y - 1;
						list[18 - y + 1][i + y - 1].state = BLACK; // ������ 
						list[18 - y + 1][i + y - 1].Y = 18 - y + 1;
						list[18 - y + 1][i + y - 1].X = y + i - 1;
						list[18 - y + 1][i + y - 1].combo = 1;
					}
					else if (Game[18 - y + 1][i + y - 1] == WHITE)
					{
						countW = 1;
						sumW = countW;
						startPoint = y - 1;
						endPoint = y - 1;
						list[18 - y + 1][i + y - 1].state = WHITE;
						list[18 - y + 1][i + y - 1].Y = 18 - y + 1;
						list[18 - y + 1][i + y - 1].X = i + y - 1;
						list[18 - y + 1][i + y - 1].combo = 1;
					}
					else if (Game[18 - y + 1][i + y - 1] == NONE_2020182003)
					{
						nonePoint = y - 1;
						list[18 - y + 1][i + y - 1].state = NONE_2020182003;
						list[18 - y + 1][i + y - 1].Y = 18 - y + 1;
						list[18 - y + 1][i + y - 1].X = i + y - 1;
					}
				}
				// ������ y�� +1 x�� -1  ���� 18-y][i + y
				if (Game[18 - y][i + y] == Game[18 - y + 1][i + y - 1]) // ������ ���� �� BB ++ WW  �⺻�� Game[i][y].Game[0+y][i+y]
				{
					if (Game[18 - y][i + y] == BLACK)
					{
						countB++;
						countW = 0;
						endPoint = y;
						if (countB > sumB) sumB = countB;
						list[18 - y][i + y].state = BLACK;
						list[18 - y][i + y].Y = 18 - y;
						list[18 - y][i + y].X = i + y;
						list[18 - y][i + y].combo = sumB;

					}
					else if (Game[18 - y][i + y] == WHITE)
					{
						countW++;
						countB = 0;
						endPoint = y;
						if (countW > sumW) sumW = countW;
						list[18 - y][i + y].state = WHITE;
						list[18 - y][i + y].Y = 18 - y;
						list[18 - y][i + y].X = y + i;
						list[18 - y][i + y].combo = sumW;
					}
					else if (Game[18 - y][y + i] == NONE_2020182003) // ���� 2�̻󿬼� nonepoint���� ������ ���ö����� k ���� 
					{
						if (y - 2 >= 0 && (Game[18 - y + 2][y + i - 2] == BLACK))
						{ // startpoint = y [y][y+i] = [18-y][y+i]
							list[18 - startPoint][startPoint + i].max = list[18 - y + 2][y + i - 2].combo; // ���� ���� ������ ������ϴµ� ���� �ִ��� max�� ����ؾ��� 
						}
						else if (y - 2 >= 0 && (Game[18 - y + 2][y + i - 2] == WHITE))
						{
							list[18 - startPoint][startPoint + i].max = list[18 - y + 2][y + i - 2].combo;
						}
						countNone = 0; // ���� �ʱ�ȭ 
					}
				}
				else if (Game[18 - y][i + y] != Game[18 - y + 1][y + i - 1]) // WB +B BW +W B+ W+
				{
					if (Game[18 - y][i + y] == BLACK) // ���� �� ���ؼ� �������ֱ� 
					{
						if (y - 1 >= 0 && (Game[18 - y + 1][y + i - 1] == WHITE))
						{
							list[18 - startPoint][startPoint + i].max = list[18 - y + 1][y + i - 1].combo; // �������� stp max ��� 

							countB = 1;
							countW = 0;
							sumB = countB;
							countNone = 0; // ���� �ʱ�ȭ 
							startPoint = y;
							list[18 - y][i + y].state = BLACK;
							list[18 - y][i + y].Y = 18 - y;
							list[18 - y][i + y].X = i + y;
							list[18 - y][i + y].combo = sumB;

						}
						else  if (y - 1 >= 0 && (Game[18 - y + 1][y + i - 1] == NONE_2020182003)) // AOB BOB 
						{
							if (countNone == 1) // ���� �ϳ��϶� ������ 
							{
								countB++;
								countW = 0;
								endPoint = y;
								if (countB > sumB) sumB = countB;
								list[18 - y][y + i].state = BLACK;
								list[18 - y][y + i].Y = 18 - y;
								list[18 - y][y + i].X = y + i;
								list[18 - y][y + i].combo = sumB;

							}
							else if (countNone == 0)
							{
								countB = 1;
								countW = 0;
								sumB = countB;
								countNone = 0; // ���� �ʱ�ȭ 
								startPoint = y;
								list[18 - y][y + i].state = BLACK;
								list[18 - y][y + i].Y = 18 - y;
								list[18 - y][y + i].X = y + i;
								list[18 - y][y + i].combo = sumB;
							}
						}
					}
					else if (Game[18 - y][i + y] == WHITE)
					{
						if (y - 1 >= 0 && (Game[18 - y + 1][y + i - 1] == BLACK))
						{
							list[18 - startPoint][startPoint + i].max = list[18 - y + 1][y + i - 1].combo; // ����BW

							countW = 1;
							countB = 0;
							sumW = countW;
							countNone = 0;
							startPoint = y;
							list[18 - y][y + i].state = WHITE;
							list[18 - y][y + i].Y = 18 - y;
							list[18 - y][y + i].X = y + i;
							list[18 - y][y + i].combo = sumW;
						}
						else  if (y - 1 >= 0 && (Game[18 - y + 1][y + i - 1] == NONE_2020182003))
						{
							if (countNone == 1) // ���� �ϳ��϶� ������  A0A 
							{
								countW++;
								countB = 0;
								endPoint = y;
								if (countW > sumW) sumW = countW;
								list[18 - y][y + i].state = WHITE;
								list[18 - y][y + i].Y = 18 - y;
								list[18 - y][y + i].X = y + i;
								list[18 - y][y + i].combo = sumW;

							}
							else if (countNone == 0) // 00A A0A0A
							{
								countW = 1;
								countB = 0;
								sumW = countW;
								countNone = 0;
								startPoint = y;
								list[18 - y][y + i].state = WHITE;
								list[18 - y][y + i].Y = 18 - y;
								list[18 - y][y + i].X = y + i;
								list[18 - y][y + i].combo = sumW;
							}
						}
					}
					else if (Game[18 - y][y + i] == NONE_2020182003) // coutnone 2�� ��������ϰ� // BAO-c1 ABO-c1 AAO-c1 BBO-c1 OBO OAO 00A-c0 
					{
						countNone++; // ó�� ������ġ 

						if (countNone == 1)
						{
							nonePoint = y; //ó��������ġ ���� 

						}
						else if (countNone == 2) // �ι� ���� A0A0    AA0AA0 00AA 00A0A0 �������� ó�� POINT��ġ�� �ٽ� ���� 
						{
							countNone = 0;
							if (y - 1 >= 0 && (Game[18 - y + 1][y + i - 1] == BLACK))
							{
								list[18 - startPoint][startPoint + i].max = list[18 - y + 1][y + i - 1].combo;
								y = nonePoint;
								continue;
							}
							else if (y - 1 >= 0 && (Game[18 - y + 1][y + i - 1] == WHITE))
							{
								list[18 - startPoint][startPoint + i].max = list[18 - y + 1][y + i - 1].combo; // ����BW
								y = nonePoint;
								continue;
							}
						}
					}

				}
				//-------------------------------------------------------------------------------------------------------

				 // �޺�
				if (list[18 - y][y + i].combo == 3) // 3�϶� 
				{
					list[18 - startPoint][startPoint + i].max = list[18 - y][y + i].combo; //�������� �ִ�ġ ���  

					for (int j = startPoint; j <= endPoint; j++) // �ִ� 1~5�϶� 10234
					{
						if (Game[18 - j][j + i] == NONE_2020182003) //����������
						{

							if (list[18 - startPoint][startPoint + i].state == BLACK)
							{
								weight[18 - j][j + i] = -BLANCK_3_2020182003; // �����ִµ� �������϶� -> �鵹 �ʿ� �׸��� 
							}
							if (list[18 - startPoint][startPoint + i].state == WHITE) // st == y / y-1][y-1+i 
							{
								weight[18 - j][j + i] = BLANCK_3_2020182003;
							}
						}
					}
					//
					if (list[18 - startPoint][i + startPoint].state == BLACK) //whelp ó���� �������϶�
					{
						if (startPoint - 1 >= 0 && (Game[18 - startPoint + 1][startPoint + i - 1] == NONE_2020182003)) // �����϶�
						{
							weight[18 - startPoint + 1][startPoint + i - 1] = -FULL_3_2020182003; // ����!
						}
						if (endPoint + 1 <= 18 && (Game[18 - endPoint - 1][endPoint + i + 1] == NONE_2020182003)) // �����϶�
						{
							weight[18 - endPoint - 1][endPoint + i + 1] = -FULL_3_2020182003; // ����!
						}
					}
					else if (list[18 - startPoint][i + startPoint].state == WHITE) // bhelp ó���� �鵹�϶� 
					{
						if (startPoint - 1 >= 0 && (Game[18 - startPoint + 1][startPoint + i - 1] == NONE_2020182003)) // �����϶�
						{
							weight[18 - startPoint + 1][startPoint + i - 1] = FULL_3_2020182003; // ����! -> B�����ִ� �� 
						}
						if (endPoint + 1 <= 18 && (Game[18 - endPoint - 1][endPoint + i + 1] == NONE_2020182003)) // �����϶�
						{
							weight[18 - endPoint - 1][endPoint + i + 1] = FULL_3_2020182003; // ����!
						}
					}
				}
				else if (list[18 - y][y + i].combo == 4) // �޺� 3�Ǵ� 4�϶� 
				{
					list[18 - startPoint][startPoint + i].max = list[18 - y][y + i].combo; //�������� �ִ�ġ ���  

					int blanckOn = 0;

					for (int j = startPoint; j <= endPoint; j++) // �ִ� 1~5�϶� 10234 // k�� j�� k�� y�� 
					{
						if (Game[18 - j][j + i] == NONE_2020182003) //����������
						{
							blanckOn = 1;

							if (list[18 - startPoint][startPoint + i].state == BLACK)
							{
								weight[18 - j][j + i] = -BLANCK_4_2020182003; // �����ִµ� �������϶� -> �鵹 �ʿ� �׸��� 
							}
							if (list[18 - startPoint][startPoint + i].state == WHITE)
							{
								weight[18 - j][j + i] = BLANCK_4_2020182003;
							}

						}
					}

					if (blanckOn == 0) // ���� ������
					{
						if (list[18 - startPoint][startPoint + i].state == BLACK) //whelp ó���� �������϶�
						{
							if (startPoint - 1 >= 0 && (Game[18 - startPoint + 1][startPoint + i - 1] == NONE_2020182003)) // �����϶�
							{
								weight[18 - startPoint + 1][startPoint + i - 1] = -FULL_4_2020182003; // ����!
							}
							if (endPoint + 1 <= 18 && (Game[18 - endPoint - 1][endPoint + i + 1] == NONE_2020182003)) // �����϶�
							{
								weight[18 - endPoint - 1][endPoint + i + 1] = -FULL_4_2020182003; // ����!
							}
						}
						else if (list[18 - startPoint][18 - startPoint + i].state == WHITE) // bhelp ó���� �鵹�϶� 
						{
							if (startPoint - 1 >= 0 && (Game[18 - startPoint + 1][startPoint + i - 1] == NONE_2020182003)) // �����϶�
							{
								weight[18 - startPoint + 1][startPoint + i - 1] = FULL_4_2020182003; // ����! -> B�����ִ� �� 
							}
							if (endPoint + 1 <= 18 && (Game[18 - endPoint - 1][endPoint + i + 1] == NONE_2020182003)) // �����϶�
							{
								weight[18 - endPoint - 1][endPoint + i + 1] = FULL_4_2020182003; // ����!
							}
						}
					}
				}
			}
		}
	}
}

// �»�� �밢�� ����ġ ������Ʈ
void CheckLTindex_2020182003(int weight[][19], int Game[][19])
{
	LIST_2020182003 list[19][19] = { 0 };

	for (int i = 18, k = 0; i > 0; i--, k++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0, countNone = 0;

		int startPoint = 0, endPoint = 0, nonePoint = 0; // ���� �� ���� ��ġ 

		for (int y = 1; y < 2 * k; y++)
		{
			if (k - y >= 0 && y < 18) // Game[0+y][i+y]  i 18~0, k0 ++, y=0~2*k y�� �����ϴ� �� 
			{
				if (y - 1 == 0) // �� ó���϶� 
				{
					if (Game[k - y + 1][y - 1] == BLACK) // y�� 1�̰� y-1�� 0�� ��Ȳ�� �� ó�� 
					{
						countB = 1;
						sumB = countB;
						startPoint = y - 1;
						endPoint = y - 1;
						list[k - y + 1][y - 1].state = BLACK;
						list[k - y + 1][y - 1].Y = k - y + 1;
						list[k - y + 1][y - 1].X = y - 1;
						list[k - y + 1][y - 1].combo = 1;
					}
					else if (Game[i + y - 1][y - 1] == WHITE)
					{
						countW = 1;
						sumW = countW;
						startPoint = y - 1;
						endPoint = y - 1;
						list[k - y + 1][y - 1].state = WHITE;
						list[k - y + 1][y - 1].Y = k - y + 1;
						list[k - y + 1][y - 1].X = y - 1;
						list[k - y + 1][y - 1].combo = 1;
					}
					else if (Game[i + y - 1][y - 1] == NONE_2020182003)
					{
						nonePoint = y - 1;
						list[k - y + 1][y - 1].state = NONE_2020182003;
						list[k - y + 1][y - 1].Y = k - y + 1;
						list[k - y + 1][y - 1].X = y - 1;
					}
				}

				if (Game[k - y][0 + y] == Game[k - y + 1][y - 1]) // ������ ���� �� BB ++ WW  �⺻�� Game[i][y].Game[0+y][i+y]
				{
					if (Game[k - y][0 + y] == BLACK)
					{
						countB++;
						countW = 0;
						endPoint = y;
						if (countB > sumB) sumB = countB;
						list[k - y][y].state = BLACK;
						list[k - y][y].Y = k - y;
						list[k - y][y].X = y;
						list[k - y][y].combo = sumB;

					}
					else if (Game[k + i][0 + y] == WHITE)
					{
						countW++;
						countB = 0;
						endPoint = y;
						if (countW > sumW) sumW = countW;
						list[k - y][y].state = WHITE;
						list[k - y][y].Y = k - y;
						list[k - y][y].X = y;
						list[k - y][y].combo = sumW;
					}
					else if (Game[k - i][y + 0] == NONE_2020182003) // ���� 2�̻󿬼� nonepoint���� ������ ���ö����� k ���� 
					{
						if (y - 2 >= 0 && (Game[k - y + 2][y - 2] == BLACK))
						{
							list[k - startPoint][startPoint].max = list[k - y + 2][y - 2].combo; // ���� ���� ������ ������ϴµ� ���� �ִ��� max�� ����ؾ��� 
						}
						else if (y - 2 >= 0 && (Game[k - y + 2][y - 2] == WHITE))
						{
							list[k - startPoint][startPoint].max = list[k - y + 2][y - 2].combo;
						}
						countNone = 0; // ���� �ʱ�ȭ 
					}
				}
				else if (Game[k - y][y] != Game[k - y + 1][y - 1]) // WB +B BW +W B+ W+
				{
					if (Game[k - y][y] == BLACK) // ���� �� ���ؼ� �������ֱ� 
					{
						if (y - 1 >= 0 && (Game[k - y + 1][y - 1] == WHITE))
						{
							list[k - startPoint][startPoint].max = list[k - y + 1][y - 1].combo; // �������� stp max ��� 

							countB = 1;
							countW = 0;
							sumB = countB;
							countNone = 0; // ���� �ʱ�ȭ 
							startPoint = y;
							list[k - y][y].state = BLACK;
							list[k - y][y].Y = k - y;
							list[k - y][y].X = y;
							list[k - y][y].combo = sumB;

						}
						else  if (y - 1 >= 0 && (Game[k - y + 1][y - 1] == NONE_2020182003)) // AOB BOB 
						{
							if (countNone == 1) // ���� �ϳ��϶� ������ 
							{
								countB++;
								countW = 0;
								endPoint = y;
								if (countB > sumB) sumB = countB;
								list[k - y][y].state = BLACK;
								list[k - y][y].Y = k - y;
								list[k - y][y].X = y;
								list[k - y][y].combo = sumB;

							}
							else if (countNone == 0)
							{
								countB = 1;
								countW = 0;
								sumB = countB;
								countNone = 0; // ���� �ʱ�ȭ 
								startPoint = y;
								list[k - y][y].state = BLACK;
								list[k - y][y].Y = k - y;
								list[k - y][y].X = y;
								list[k - y][y].combo = sumB;
							}
						}
					}
					else if (Game[k - y][y] == WHITE)
					{
						if (y - 1 >= 0 && (Game[k - y + 1][y - 1] == BLACK))
						{
							list[k - startPoint][startPoint].max = list[k - y + 1][y - 1].combo; // ����BW

							countW = 1;
							countB = 0;
							sumW = countW;
							countNone = 0;
							startPoint = y;
							list[k - y][y].state = WHITE;
							list[k - y][y].Y = k - y;
							list[k - y][y].X = y;
							list[k - y][y].combo = sumW;
						}
						else  if (y - 1 >= 0 && (Game[k - y + 1][y - 1] == NONE_2020182003))
						{
							if (countNone == 1) // ���� �ϳ��϶� ������  A0A 
							{
								countW++;
								countB = 0;
								endPoint = y;
								if (countW > sumW) sumW = countW;
								list[k - y][y].state = WHITE;
								list[k - y][y].Y = k - y;
								list[k - y][y].X = y;
								list[k - y][y].combo = sumW;

							}
							else if (countNone == 0) // 00A A0A0A
							{
								countW = 1;
								countB = 0;
								sumW = countW;
								countNone = 0;
								startPoint = y;
								list[k - y][y].state = WHITE;
								list[k - y][y].Y = k - y;
								list[k - y][y].X = y;
								list[k - y][y].combo = sumW;
							}
						}
					}
					else if (Game[k - y][y] == NONE_2020182003) // coutnone 2�� ��������ϰ� // BAO-c1 ABO-c1 AAO-c1 BBO-c1 OBO OAO 00A-c0 
					{
						countNone++; // ó�� ������ġ 

						if (countNone == 1)
						{
							nonePoint = y; //ó��������ġ ���� 

						}
						else if (countNone == 2) // �ι� ���� A0A0    AA0AA0 00AA 00A0A0 �������� ó�� POINT��ġ�� �ٽ� ���� 
						{
							countNone = 0;
							if (y - 1 >= 0 && (Game[k - y + 1][y - 1] == BLACK))
							{
								list[k - startPoint][startPoint].max = list[k - y + 1][y - 1].combo;
								y = nonePoint;
								continue;
							}
							else if (y - 1 >= 0 && (Game[k - y + 1][y - 1] == WHITE))
							{
								list[k - startPoint][startPoint].max = list[k - y + 1][y - 1].combo; // ����BW
								y = nonePoint;
								continue;
							}
						}
					}

				}
				//-------------------------------------------------------------------------------------------------------

				 // �޺�
				if (list[k - y][y].combo == 3) // 3�϶� 
				{
					list[k - startPoint][startPoint].max = list[k - y][y].combo; //�������� �ִ�ġ ���  

					for (int j = startPoint; j <= endPoint; j++) // �ִ� 1~5�϶� 10234
					{
						if (Game[k - j][j] == NONE_2020182003) //����������
						{

							if (list[k - startPoint][startPoint].state == BLACK)
							{
								weight[k - j][j] = -BLANCK_3_2020182003; // �����ִµ� �������϶� -> �鵹 �ʿ� �׸��� 
							}
							if (list[k - startPoint][startPoint].state == WHITE)
							{
								weight[k - j][j] = BLANCK_3_2020182003;
							}
						}
					}

					if (list[k - startPoint][startPoint].state == BLACK) //whelp ó���� �������϶�
					{
						if (startPoint - 1 >= 0 && (Game[k - startPoint + 1][startPoint - 1] == NONE_2020182003)) // �����϶�
						{
							weight[k - startPoint + 1][startPoint - 1] = -FULL_3_2020182003; // ����!
						}
						if (endPoint + 1 <= 18 && (Game[k - endPoint - 1][endPoint + 1] == NONE_2020182003)) // �����϶�
						{
							weight[k - endPoint - 1][endPoint + 1] = -FULL_3_2020182003; // ����!
						}//	weight[k - endPoint - 1 + i][endPoint + 1] = -FULL_3_2020182003; i�� ��������

					}
					else if (list[k - startPoint][startPoint].state == WHITE) // bhelp ó���� �鵹�϶� 
					{
						if (startPoint - 1 >= 0 && (Game[k - startPoint + 1][startPoint - 1] == NONE_2020182003)) // �����϶�
						{
							weight[k - startPoint + 1][startPoint - 1] = FULL_3_2020182003; // ����! -> B�����ִ� �� 
						}
						if (endPoint + 1 <= 18 && (Game[k - endPoint - 1][endPoint + 1] == NONE_2020182003)) // �����϶�
						{
							weight[k - endPoint - 1][endPoint + 1] = FULL_3_2020182003; // ����!
						}
					}
				}
				else if (list[k - y][y].combo == 4) // �޺� 3�Ǵ� 4�϶� 
				{
					list[k - startPoint][startPoint].max = list[k - y][y].combo; //�������� �ִ�ġ ���  

					int blanckOn = 0;

					for (int j = startPoint; j <= endPoint; j++) // �ִ� 1~5�϶� 10234 // k�� j�� k�� y�� 
					{
						if (Game[k - j][j] == NONE_2020182003) //����������
						{
							blanckOn = 1;

							if (list[k - startPoint][startPoint].state == BLACK)
							{
								weight[k - j][j] = -BLANCK_4_2020182003; // �����ִµ� �������϶� -> �鵹 �ʿ� �׸��� 
							}
							if (list[k - startPoint][startPoint].state == WHITE)
							{
								weight[k - j][j] = BLANCK_4_2020182003;
							}

						}
					}

					if (blanckOn == 0) // ���� ������
					{
						if (list[k - startPoint][startPoint].state == BLACK) //whelp ó���� �������϶�
						{
							if (startPoint - 1 >= 0 && (Game[k - startPoint + 1][startPoint - 1] == NONE_2020182003)) // �����϶�
							{
								weight[k - startPoint + 1][startPoint - 1] = -FULL_4_2020182003; // ����!
							}
							if (endPoint + 1 <= 18 && (Game[k - endPoint - 1][endPoint + 1] == NONE_2020182003)) // �����϶�
							{
								weight[k - endPoint - 1][endPoint + 1] = -FULL_4_2020182003; // ����!
							}
						}
						else if (list[k - startPoint][startPoint].state == WHITE) // bhelp ó���� �鵹�϶� 
						{
							if (startPoint - 1 >= 0 && (Game[k - startPoint + 1][startPoint - 1] == NONE_2020182003)) // �����϶�
							{
								weight[k - startPoint + 1][startPoint - 1] = FULL_4_2020182003; // ����! -> B�����ִ� �� 
							}
							if (endPoint + 1 <= 18 && (Game[k - endPoint - 1][endPoint + 1] == NONE_2020182003)) // �����϶�
							{
								weight[k - endPoint - 1][endPoint + 1] = FULL_4_2020182003; // ����!
							}
						}
					}
				}
			}
		}
	}
}

// ���� ����� ������ -> �������� ������� int�� ��ȯ���ִ� �Լ� -> (+)�� ��츸 ������ 
int PlusCompare_2020182003(int weight[][19])
{
	int sum = 0;

	int stop = 0;
	int stop2 = 0;

	for (int i = 0; i < 19; i++)
	{
		for (int k = 0; k < 19; k++)
		{
			if (weight[i][k] == FULL_4_2020182003 // ���� ���� �� -> �߰��ϸ� ������ 
				|| weight[i][k] == -FULL_4_2020182003
				|| weight[i][k] == BLANCK_4_2020182003
				|| weight[i][k] == -BLANCK_4_2020182003)
			{
				stop++;
				break;
			}

			if (weight[i][k] == FULL_3_2020182003 // ���� ���� �� -> �߰��ϸ� ������ 
				|| weight[i][k] == -FULL_3_2020182003
				|| weight[i][k] == BLANCK_3_2020182003
				|| weight[i][k] == -BLANCK_3_2020182003)
			{
				stop2++;
			}

			if (weight[i][k] > 0)
			{
				sum += weight[i][k]; // ����϶� ���� 
			}
		}
	}

	if (sum == 0)
	{
		return 0;
	}
	else if (stop != 0)
	{
		return -1;
	}
	else if (stop2 != 0)
	{
		return -2;
	}
	else
	{
		return sum;
	}
}

// ���� ����� ������ -> �������� ������� int�� ��ȯ���ִ� �Լ� -> (-)�� ��츸 ������ 
int MinusCompare_2020182003(int weight[][19])
{
	int sum = 0;

	int stop = 0;
	int stop2 = 0;

	for (int i = 0; i < 19; i++)
	{
		for (int k = 0; k < 19; k++)
		{
			if (weight[i][k] == FULL_4_2020182003 // ���� ���� �� -> �߰��ϸ� ������ 
				|| weight[i][k] == -FULL_4_2020182003
				|| weight[i][k] == BLANCK_4_2020182003
				|| weight[i][k] == -BLANCK_4_2020182003)
			{
				stop++;
				break;
			}

			if (weight[i][k] == FULL_3_2020182003 // ���� ���� �� -> �߰��ϸ� ������ 
				|| weight[i][k] == -FULL_3_2020182003
				|| weight[i][k] == BLANCK_3_2020182003
				|| weight[i][k] == -BLANCK_3_2020182003)
			{
				stop2++;
			}

			if (weight[i][k] < 0)
			{
				sum -= weight[i][k]; // ����϶� ���� 
			}


		}
	}

	if (sum == 0)
	{
		return 0;
	}
	else if (stop != 0)
	{
		return -1;
	}
	else if (stop2 != 0)
	{
		return -2;
	}
	else
	{
		return sum;
	}


}
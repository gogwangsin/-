

#if 1

#include<iostream>
#include "Judgment.h"

#include "Omok_2020182003.h"
#include "Omok_2018180042.h"

using namespace std;

int main(void)
{
	Judgment judgment;

	judgment.SetYourFunc( 
#if 1
		// �浹 �����, �鵹 ���� 
		BlackAttack_2018180042,/*����*/
		BlackDefence_2018180042,

		WhiteAttack_2020182003,
		WhiteDefence_2020182003
#endif
// ======================================
#if 0
		// �浹 ����, �鵹 ����� 
		BlackAttack_2020182003,/*����*/
		BlackDefence_2020182003,

		WhiteAttack_2018180042,
		WhiteDefence_2018180042
#endif
	);
	judgment.GamePlay();

}

#endif


#if 0
srand((unsigned)time(NULL));

int white_x = rand() % 18;
int white_y = rand() % 18;

while (1)
{
	if (board_2020182003[white_y][white_x] == BLACK || board_2020182003[white_y][white_x] == WHITE)
	{
		white_x = rand() % 18;
		white_y = rand() % 18;
	}
	else break;
}



#endif
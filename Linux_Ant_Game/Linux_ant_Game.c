#include<stdio.h>
#include<stdlib.h>//abs 등의 기능을 사용하기 위해 포함시켰습니다.
#include<time.h>//시간에 따라 지속적으로 임의의 숫자를 선정하기 위해 포함시켰습니다.

#define RED "\x1b[31m"//빨강, 파랑, 노랑의 색으로 글자를 출력하기 위한 매크로 입니다.
#define BLUE "\x1b[34m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[0m"//글자 색을 검정색으로 재설정하기 위한 매크로 입니다.

#define MAXROW 8//사용할 행과 열을 먼저 8로 설정합니다.(이후에는 필요한 부분만 선택적으로 다루고, 출력합니다.)
#define MAXCOLUMN 8

int ReadMap(char map[][MAXCOLUMN], int antCounts[][MAXCOLUMN], int*, int*, int*);//map.txt 파일에서 작업에 사용될 게임의 정보를 가져옵니다.
void PrintMap(char map[][MAXCOLUMN], int, int);//map.txt 로부터 얻은 정보를 바탕으로 A, B, N을 사용해 영역을 표시하는 배열을 출력합니다.
void PrintAntCounts(char map[][MAXCOLUMN], int antCounts[][MAXCOLUMN], int, int);//map.txt 로부터 얻은 정보를 바탕으로 해당 영역에 있는 개미의 수로 배열을 출력합니다.
void PrintResult(char map[][MAXCOLUMN], int antCounts[][MAXCOLUMN], int, int, int, int, int, int, int);//게임이 끝나면, 그 결과를 replay.txt 파일에 출력합니다.
int leftColumnDistance(char a[][MAXCOLUMN], int, int);//배열을 다룰때에 선택한 영역의 왼쪽방향으로 가장 가까운 영역까지의 거리를 계산합니다.
int rightColumnDistance(char a[][MAXCOLUMN], int, int);//배열을 다룰때에 선택한 영역의 오른쪽방향으로 가장 가까운 영역까지의 거리를 계산합니다.
int upRowDistance(char a[][MAXCOLUMN], int);//배열을 다룰때에 선택한 영역의 위쪽방향으로 가장 가까운 영역까지의 거리를 계산합니다. 좌우의 거리는 무시합니다.
int downRowDistance(char a[][MAXCOLUMN], int);//배열을 다룰때에 선택한 영역의 아래쪽방향으로 가장 가까운 영역까지의 거리를 계산합니다. 좌우의 거리는 무시합니다.
void dstn(int ary[][MAXCOLUMN], char arr[][MAXCOLUMN], int, int, int, int, int*, int*, int*);//move turn 중, 상하좌우 이동가능한 영역을 고르고, 어떤 영역으로 갈지 선택하는 과정입니다.
void dstn_com(int ary[][MAXCOLUMN], char arr[][MAXCOLUMN], int, int, int, int, int*, int*, int*);//move turn 중, 컴퓨터의 이동가능 영역을 고르고 그 중 하나를 선택하는 과정을 자동으로 시행합니다.
void AntMove(int a[][MAXCOLUMN], int, int, int, int, int);//fight turn에 해당하며, 개미의 이동 이후 해당 영역에 남아있는 개미의 수를 계산합니다.
void breed(int ary[][MAXCOLUMN], char arr[][MAXCOLUMN], int, int);//breeding turn 때 각 영역에서 개미의 수가 증가하는 과정입니다.
void PrintMap_after(char ary[][MAXCOLUMN], int arr[][MAXCOLUMN], int, int);//각 턴이 끝나면 그 과정을 반영하여 새로운 map배열을 출력합니다.
void PrintAntCounts_after(char ary[][MAXCOLUMN], int arr[][MAXCOLUMN], int, int);//각 턴이 끝나면 그 과정을 반영하여 새로운 antCounts배열을 출력합니다.
void check(int arr[][MAXCOLUMN], int, int, int*);//게임이 끝날 조건을 충족하는지 판단하는 함수입니다.
void last_ifm(int arr[][MAXCOLUMN], int, int, int*, int*, int*, int*);//replay.txt 에 출력할 정보를 따로 정리하는 함수입니다.


int main()
{

	int row, column, regionCount;//게임에 사용될 배열의 열과 행을 각각 row, column이 나타내고, 게임 시작시 나타나는 중립영역의 개수를 regionCount가 나타냅니다.
	int start_r = 0, start_r_com = 0, start_c = 0, start_c_com = 0, dstn_r = 0, dstn_r_com = 0, dstn_c = 0, dstn_c_com = 0, num, num_com, send_num = 0, send_num_com = 0, check_num, grd_num, grd_num_com, total_ant, total_ant_com;//사용자와 컴퓨터의 개미의 이동에 있어서 시작하는 칸, 도착하는 칸의 열과 행, 이동하는 개미의 수, 이동후 남은 영역의 수, 남은 개미의 수를 모두 따로 구분한 변수들입니다. 
	int i, j, q, q_com, Q, Q_com, p, p_com;//게임 과정에 있어서 사용자에게 알려줄 선택지의 개수와 선택한 결과를 저장하기 위한 변수입니다.
	int term = 0;//예외 처리 과정에서 사용되는 변수입니다.
	char test;//마찬가지로 예외 처리 과정에서 사용됩니다.
	char gameResult;//게임의 승패 혹은 무승부를 W, L, D로 나타내는 변수입니다.
	char map[MAXROW][MAXCOLUMN];//게임에서 사용될 배열로, 이후에는 필요한 부분만 사용하게 됩니다.
	int antCounts[MAXROW][MAXCOLUMN] = {0};//마찬가지로 게임에서 사용될 개미의 마리수를 나타내는 배열로, 이후에는 필요한 부분만 사용합니다.

	if (ReadMap(map, antCounts, &row, &column, &regionCount) == 0)//가장 먼저, map.txt 파일로 부터 배열과 영역의 정보를 가져옵니다.
	{
		printf("There is no valid file.");//예외처리 -- 파일이 없다면 이러한 문구를 띄우며 프로그램을 종료하게 됩니다.
		return 0;
	}
	else
	{
		PrintMap(map, row, column);//map.txt 로부터 정보를 잘 입력받았으면 배열 map과 antCounts의 필요한 부분만을 제한하여 출력합니다. row 와 column에 저장된 값을 통해 제한할 수 있습니다.
		printf("\n---------------------\n");
		PrintAntCounts(map, antCounts, row, column);
		printf("\n\n");
	}
	for (;;)//move, fight, breeding turn이 게임이 끝나기 전까지 무한 반복하는 과정입니다.
	{
		for (i = 0, q = 0, q_com = 0; i < row; i++)//사용자와 컴퓨터가 고를, 개미를 이동시킬 영역의 개수를 판단하는 과정입니다. antCounts의 각 칸에 저장된 수가 양수이면 사용자가 고를 수 있는 영역이고, 음수이면 컴퓨터가 고를 수 있는 땅입니다. 
		{
			for (j = 0; j < column; j++)
			{
				if (antCounts[i][j] > 0)
				{
					q += 1;
					printf("%d : (%d, %d)\n", q, i, j);
				}
				if (antCounts[i][j] < 0)
				{
					q_com += 1;
				}
			}
		} 
		srand(time(NULL));
		Q_com = rand() % q_com + 1;//컴퓨터에게 주어진 보기의 개수 중 하나를 임의로 선택합니다.
		printf("where ants start? ");//사용자가 선택할 보기를 입력받는 부분입니다.
		for (;;)//예외처리 -- 범위 밖의 정수나 실수, 문자를 입력받으면 재입력 받도록하는 부분입니다.
		{
			if (scanf("%d%c", &term, &test) != 2 || test != '\n')//%d 와 %c를 연속으로 입력받는다면 정수입력 후 \n가 %c를 통해 scan될 것입니다. 소수를 입력한다면 . 부분에 의해 잘못된 입력이라고 판단할 수 있고, 문자가 입력된다면 scanf의 반환값을 통해 잘못된 입력임을 판단합니다.
			{
				for (;;)//이렇게 범위에 의한 오류가 아닌 입력 형태에 의한 오류라면, \n를 scan할 수 있을 때까지 getchar()를 통해 무한 루프를 방지할 수 있고, 오류 문구를 띄우며 재입력 받도록 합니다.
				{
					if (getchar() == '\n')
					{
						printf("Please type an integer from 1 to %d ", q);
						break;
					}						
				}
			}
			else if (term < 1 || term > q)//입력 형태는 올바르지만 정수의 범위에 의한 오류가 나타날 때도 오류문구를 띄우며 재입력 받도록 합니다.
			{
				printf("please type an integer from 1 to %d ", q);
			}
			else
			{
				Q = term;//형태와 범위를 모두 만족한 올바른 입력값이라면 그 수를 변수에 저장하여 다음 과정에서 사용하게 됩니다.
				break;
			}
		}
		for (p = 0, p_com = 0, i = 0; i < row; i++)//컴퓨터와 사용자가 고른 보기를 바탕으로 정보를 끌어옵니다. 보기를 출력하는 과정과 같은 과정을 반복한다면, 두 과정은 같은 순서로 진행되기 때문에 어떤 정보를 담고있는 보기를 선택했는지 알 수 있습니다. 따라서 사용자나 컴퓨터가 고른 보기에 해당하는 만큼만 for문을 진행하여 정보를 끌어옵니다.
		{
			for (j = 0; j < column; j++)
			{
				if (antCounts[i][j] > 0)//이 과정에서도 antCounts 배열에 저장된 수가 음수인지 양수인지에 따라 사용자와 컴퓨터가 고른 보기의 행, 열 정보를 쉽게 구분할 수 있습니다.
				{
					p += 1;
					if (p == Q)
					{
						start_r = i;
						start_c = j;
					}
				}
				if (antCounts[i][j] < 0)
				{
					p_com += 1;
					if (p_com == Q_com)
					{
						start_r_com = i;
						start_c_com = j;
					}
				}
			}
		}
		printf("\n");
		dstn(antCounts, map, row, column, start_r, start_c, &dstn_r, &dstn_c, &num);//사용자와 컴퓨터가 고른 보기로 부터 개미를 이동시킬 칸으로 배열의 어느 부분을 선택했는지 확인 한 이후, 해당 칸으로부터 좌우상하로 움직일 수 있는 보기를 출력하고, 이전과 같은 방식으로 보기를 입력받아 배열의 어떤 칸을 선택했는지 판단합니다.
		dstn_com(antCounts, map, row, column, start_r_com, start_c_com, &dstn_r_com, &dstn_c_com, &num_com);//사용자가 입력하는 과정을 컴퓨터는 자동으로 임의의 정수를 출력하여 처리합니다.
		printf("\nHow many ants go?(0 ~ %d) ", antCounts[start_r][start_c] - 1);//사용자가 고른 두 영역 사이에서 이동할 개미의 수를 입력받습니다.
		for (term = 0, send_num = 0;;)//예외처리 -- 보기를 선택할 때와 같은 방식을 사용합니다.
		{
			if (scanf("%d%c", &term, &test) != 2 || test != '\n')//입력 형식이 잘못되어 소수나 문자가 입력된다면 오류 문구를 띄우고 재입력 받도록 합니다.
			{
				for (;;)
				{
					if (getchar() == '\n')
					{
						printf("Please type an integer from 0 to %d ", antCounts[start_r][start_c]-1);
						break;
					}
				}
			}
			else if (term < 0 || term > antCounts[start_r][start_c]-1)//입력 형식을 올바르지만 정수의 범위가 잘못되었을 경우 오류 문구를 띄우고 재입력 받도록 합니다.
			{
				printf("Please type an integer from 0 to %d ", antCounts[start_r][start_c] - 1);
			}
			else//입력의 조건이 모두 충족되었다면 그 값을 변수에 저장하여 이후 과정에 사용하도록 합니다.
			{
				send_num = term;
				break;
			}
		}
		system("cls");//개미의 이동 이후에 바뀔 map과 antCounts 배열을 깔끔하게 표시하기 위해 콘솔 화면을 초기화합니다.
		if (abs(antCounts[start_r_com][start_c_com]) == 1)//만약 컴퓨터가 개미를 보낼 영역에 남아있는 개미의 수가 1이라면, 개미의 수가 1이 아닐 때에 사용할 식에서 수학적인 오류가 생기기 때문에 두 경우를 분리하여 작성했습니다.
		{
			send_num_com = -1;
		}
		else
		{
			send_num_com = -(rand() % (abs(antCounts[start_r_com][start_c_com]) - 1) + 0);//위에서 언급한 식으로, 특정 영역에 최소한 1마리는 남을 수 있도록 임의의 숫자를 선정합니다.
		}
		AntMove(antCounts, start_r, start_c, dstn_r, dstn_c, send_num);//사용자가 선택한 영역 간에, 선택한 개미의 수 만큼 개미가 이동한 결과를 반영하여 배열의 각 값을 변형하는 과정입니다.
		AntMove(antCounts, start_r_com, start_c_com, dstn_r_com, dstn_c_com, send_num_com);//컴퓨터가 임의로 선정한 영역과 개미의 수 만큼 개미가 이동한 결과를 반영하여 배열의 각 값을 변형하는 과정입니다. 이 두 과정은 시작점이 같을 수 없기 때문에, 두 과정에는 순서가 있지만 결과적으로 동시 턴제의 조건을 만족한다고 간주해도 무방합니다.
		printf("Human sends %d ants from (%d, %d) to (%d, %d)\n", send_num, start_r, start_c, dstn_r, dstn_c);//사용자와 컴퓨터에 의해 이동된 영역과 개미의 수를 출력하여 그 과정을 보기쉽게 전달합니다.
		printf("Computer sends %d ants from (%d, %d) to (%d, %d)\n", abs(send_num_com), start_r_com, start_c_com, dstn_r_com, dstn_c_com);
		printf("---------------------\n");
		printf("ants fight each other!\n\n");//fight turn으로 넘어감을 명시하는 부분입니다.
		PrintMap_after(map, antCounts, row, column);//특정 영역에 대한 개미의 입출을 고려하여 map배열과 antCoutns배열을 출력하는 부분입니다.
		printf("---------------------\n");
		PrintAntCounts_after(map, antCounts, row, column);
		check(antCounts, row, column, &check_num);//fight turn이후 게임이 끝날 조건을 만족하였는지 확인합니다.
		if (check_num != 0)//check_num은 check함수에서 반환하는 값으로, 그 값이 0일 경우에는 게임이 끝날 조건을 충족하지 못한 것이고, 1, 2, 3일 경우에는 게임이 끝날 조건을 충족한 경우입니다.
		{
			break;//따라서 check_num에 반환된 값이 0이 아니라면, for문을 빠져나가고 게임을 마무리 하기 위한 과정을 진행합니다.
		}
		breed(antCounts, map, row, column);//게임이 끝나지 않았다면, 각 영역에 존재하는 개미의 수를 증가시킵니다. basement에서는 2만큼, 그 외의 영역에서는 1만큼 증가됩니다.
		printf("\nants breeding!\n\n");
		PrintMap_after(map, antCounts, row, column);//breeding turn의 결과를 반영하여 새로워진 map, antCounts배열을 출력합니다.
		printf("---------------------\n");
		PrintAntCounts_after(map, antCounts, row, column);
		printf("\n\n");//여기까지가 게임의 한 단계입니다. 게임이 끝날 조건을 만족할 때까지 이 단계를 무한히 반복합니다.
	}
	if (check_num == 1)//게임이 끝나고, 그 결과를 분류합니다. check_num에 반환된 값이 1이면 사용자가 패배, 2이면 사용자가 승리, 3이면 사용자와 컴퓨터가 비겼음을 뜻합니다.
	{
		gameResult = 'L';
		printf("\nyou lose..\n\n");
	}
	else if (check_num == 3)
	{
		gameResult = 'D';
		printf("\ndraw.\n\n");
	}
	else if (check_num == 2)
	{
		gameResult = 'W';
		printf("\nyou win!!\n\n");
	}
	PrintMap_after(map, antCounts, row, column);//게임이 끝났을 때의 map, antCounts 배열을 출력하여 어떤 양상으로 종료되었는지 명시합니다.
	printf("---------------------\n");
	PrintAntCounts_after(map, antCounts, row, column);
	last_ifm(antCounts, row, column, &grd_num, &grd_num_com, &total_ant, &total_ant_com);//게임이 끝난 결과를 요약하여 파일에 정리하기 위해 필요한 정보를 뽑아냅니다. 사용자와 컴퓨터가 갖고있는 영역의 개수, 사용자와 컴퓨터에게 남아있는 개미의 총 수가 그 정보입니다.
	PrintResult(map, antCounts, row, column, gameResult, grd_num, grd_num_com, total_ant, total_ant_com);//필요한 정보를 모두 뽑아냈다면 replay.txt 파일에 그 정보를 순서에 맞게 출력합니다.
}

int ReadMap(char map[][MAXCOLUMN], int antCounts[][MAXCOLUMN], int* row, int* column, int* regionCount)//map.txt 파일로 부터 배열의 정보와 영역의 정보를 받아오는 함수입니다.
{
	int i, r, c;
	char A, B, N;
	map[0][0] = 'A';//두 배열의 첫번째 칸은 항상 A와 10이 각각 저장됩니다.
	antCounts[0][0] = 10;
	FILE* infile;
	infile = fopen("map.txt", "r");//map.txt 파일을 읽기 형식으로 여는 과정입니다.
	if (infile == NULL)//예외처리 -- 파일이 없을 경우에는 0을 반환하고, 이 반환값을 바탕으로 오류 문구를 출력하게 됩니다.
	{
		return 0;
	}
	
	fscanf(infile, "%d", row);//파일에 적혀있는 순서대로 행, 열, 중립영역의 개수를 저장합니다.
	fscanf(infile, "%d", column);
	fscanf(infile, "%d", regionCount);
	map[*row - 1][*column - 1] = 'B';//저장한 행, 열을 바탕으로 배열의 가장 끝 부분은 항상 B, -10의 정보를 부여하게 됩니다.(음수를 부여한 이유는 각 영역이 누구의 땅인지 쉽게 구별하기 위함입니다.)
	antCounts[*row - 1][*column - 1] = -10;
	for (i = 0; i < (2 * *regionCount); i++)//중립영역의 개수만큼 반복적으로 행과 열을 scan하여 배열 상의 중립 영역의 위치를 결정합니다. 
	{
		fscanf(infile, "%d", &r);
		fscanf(infile, "%d", &c);
		map[r][c] = 'N';
	}
	return 1;
}

void PrintMap(char map[][MAXCOLUMN], int row, int column)//map배열을 출력하는 함수입니다. 배열의 필요한 부분에 대해서 모두 이 과정을 거치게 되며, map배열과 비교하여 A, B, N의 문자가 저장되어 있는 부분은 주어진 색깔을 부여하여 출력하도록 합니다.
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < column; j++)
		{
			if (j == 0)
			{
				printf(" ");
			}
			if (map[i][j] == 'A')
			{
				printf(RED);
				printf(" %c ", map[i][j]);
				printf(RESET);
			}
			else if (map[i][j] == 'B')
			{
				printf(BLUE);
				printf(" %c " , map[i][j]);
				printf(RESET);
			}
			else if (map[i][j] == 'N')
			{
				printf(YELLOW);
				printf(" %c ", map[i][j]);
				printf(RESET);
			}
			else
			{
				printf(" 0 ");
			}

		}
		if (i==row-1)
		{
			break;
		}
		printf("\n");
	}
}

void PrintAntCounts(char map[][MAXCOLUMN], int antCounts[][MAXCOLUMN], int row, int column)//antCounts배열을 출력하는 함수입니다. map배열에 A, B, N 문자가 저장되어 있다면, 해당 칸에 대응하는 antCounts의 숫자를 주어진 색깔을 입혀 출력합니다. 배열의 필요한 부분에 대해서 모두 이 과정이 진행됩니다.
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < column; j++)
		{
			if (j == 0)
			{
				printf(" ");
			}
			if (map[i][j] == 'A')
			{
				printf(RED);
				printf("%2d ", abs(antCounts[i][j]));
				printf(RESET);
			}
			else if (map[i][j] == 'B')
			{
				printf(BLUE);
				printf("%2d ", abs(antCounts[i][j]));
				printf(RESET);

			}
			else if (map[i][j] == 'N')
			{
				printf(YELLOW);
				printf( "%2d ", abs(antCounts[i][j]));
				printf(RESET);
			}
			else
			{
				printf(" 0 ");
			}

		}
		printf("\n");
	}
}

int leftColumnDistance(char a[][MAXCOLUMN], int r,int c)//배열의 특정한 칸과 같은 행 상에 있는 칸들에 대해서, 왼쪽으로 가장 가까운 영역까지의 거리를 측정합니다.
{
	int i, j;
	int result = MAXCOLUMN;
	for (i = 0; i <= r; i++)
	{
		if (i == r)
		{
			for (j = 0; j < c; j++)
			{
				if ((a[i][j] == 'A') || (a[i][j] == 'N') || (a[i][j] == 'B'))
				{
					if ((c - j) < result)
					{
						result = c - j;
					}
				}
			}
		}
	}
	return result;
}

int rightColumnDistance(char a[][MAXCOLUMN], int r, int c)//배열의 특정한 칸과 같은 행 상에 있는 칸들에 대해서, 오른쪽으로 가장 가까운 영역까지의 거리를 측정합니다.
{
	int i, j;
	int result = MAXCOLUMN;
	for (i = 0; i <= r; i++)
	{
		if (i == r)
		{
			for (j = MAXCOLUMN - 1; j > c; j--)
			{
				if ((a[i][j] == 'A') || (a[i][j] == 'N') || (a[i][j] == 'B'))
				{
					if ((j - c) < result)
					{
						result = j - c;
					}
				}
			}
		}
	}
	return result;
}

int upRowDistance(char a[][MAXCOLUMN], int r)//배열의 특정한 칸에 대하여, 위쪽으로 가장 가까운 영역까지의 거리를 측정합니다. 좌우의 거리, 즉 열의 차이는 고려하지 않습니다.
{
	int i, j;
	int result = MAXCOLUMN;
	for (i = 0; i < r; i++)
	{
		for (j = 0; j <MAXCOLUMN; j++)
		{
			if ((a[i][j] == 'A') || (a[i][j] == 'N') || (a[i][j] == 'B'))
				if ((r-i) < result)
				{
					result = r-i;
				}
		}
	}
	return result;
}

int downRowDistance(char a[][MAXCOLUMN], int r)//배열의 특정한 칸에 대하여, 아래쪽으로 가장 가까운 영역까지의 거리를 측정합니다. 좌우의 거리, 즉 열의 차이는 고려하지 않습니다.
{
	int i, j;
	int result = MAXCOLUMN;
	for (i = MAXCOLUMN-1; i > r; i--)
	{
		for (j = 0; j < MAXCOLUMN; j++)
		{
			if ((a[i][j] == 'A') || (a[i][j] == 'N') || (a[i][j] == 'B'))
				if ((i - r) < result)
				{
					result = i-r;
				}
		}
	}
	return result;
}

void AntMove(int a[][MAXCOLUMN], int from_r, int from_c, int to_r, int to_c, int n)//선택된 두 영역간의 특정한 숫자 만큼의 개미의 이동 과정을 계산합니다. 음수인 경우에 따로 수학적인 오류는 없습니다.
{
	a[from_r][from_c] -= n;
	a[to_r][to_c] += n;
}

void dstn(int ary[][MAXCOLUMN], char arr[][MAXCOLUMN], int r_of_ary, int c_of_ary, int r_of_start, int c_of_start, int* r_of_end, int* c_of_end, int* num)
{//특정 영역을 선택한 이후에 개미를 이동시킬 수 있는 영역을 선택하는 과정입니다.
	int i, j, k, Q = 0;
	int term = 0;
	char test;
	for (i = 0, k = 0; i < r_of_ary; i++)//먼저 배열의 각 행을 조사합니다.
	{
		if (r_of_start - i == upRowDistance(arr, r_of_start))//조사하는 행이 선택한 영역보다 위에 있는 경우에는, 어떠한 행이 upRowDistance와 같은지를 비교하고, 만족하는 행에 대해서는 그 행에 존재하는 모든 영역을 이동할 수 있는 영역으로 인식합니다.
		{
			for (j = 0; j < c_of_ary; j++)
			{
				if (arr[i][j] == 'A' || arr[i][j] == 'B' || arr[i][j] == 'N')
				{
					k += 1;
					printf("%d : (%d, %d)\n", k, i, j);
				}
			}
		}
		else if (i == r_of_start)//조사하는 행이 선택한 영역의 행과 같은 경우에는, 선택한 영역의 좌우 leftColumnDistance와 rightColumnDistance를 판단하여 이동할 수 있는 영역을 판단합니다.
		{
			for (j = 0; j < c_of_start; j++)
			{
				if ((arr[i][j] == 'A' || arr[i][j] == 'B' || arr[i][j] == 'N') && ((c_of_start - j) == leftColumnDistance(arr, r_of_start, c_of_start)))
				{
					k += 1;
					printf("%d : (%d, %d)\n", k, i, j);
				}
			}
			for (j = c_of_start + 1; j < c_of_ary; j++)
			{
				if ((arr[i][j] == 'A' || arr[i][j] == 'B' || arr[i][j] == 'N') && ((j - c_of_start) == rightColumnDistance(arr, r_of_start, c_of_start)))
				{
					k += 1;
					printf("%d : (%d, %d)\n", k, i, j);
				}
			}
		}
		else if (i - r_of_start == downRowDistance(arr, r_of_start))//조사하는 행이 선택한 영역보다 아래에 있을 경우에는, 어떠한 행이 downRowDistance를 만족하는지 확인하고, 그 행 상에 있는 모든 영역에 대해 이동할 수 있는 영역으로 간주합니다.
		{
			for (j = 0; j < c_of_ary; j++)
			{
				if (arr[i][j] == 'A' || arr[i][j] == 'B' || arr[i][j] == 'N')
				{
					k += 1;//이동할 수 있는 영역을 인식할 때마다, k변수에는 1씩 추가됩니다. k변수는 이동할 수 있는 영역의 개수를 세는 변수입니다. 즉 사용자에게 출력할 유효한 보기의 개수와 같습니다.
					printf("%d : (%d, %d)\n", k, i, j);
				}
			}
		}
	}
	printf("where ants go? ");//사용자에게 개미를 이동시킬 영역을 보기로 모두 출력했다면, 사용자로부터 특정 보기를 입력받습니다.
	for (;;)//예외처리 -- 다른 때와 같은 방식을 취합니다.
	{
		if (scanf("%d%c", &term, &test) != 2 || test != '\n')//정수가 아닌 소수와 같은 실수나, 문자를 입력받았을 경우, 오류 문구와 함께 재입력 받도록 합니다.
		{
			for (;;)
			{
				if (getchar() == '\n')
				{
					printf("Please type an integer from 1 to %d ", k);
					break;
				}
			}
		}
		else if (term < 1 || term > k)//입력 형태는 올바르지만 정수의 범위가 올바르지 않을 경우, 또한 오류 문구와 함께 재입력 받도록 합니다.
		{
			printf("please type an integer from 1 to %d ", k);
		}
		else//입력 조건을 만족시켰을 경우, 입력된 정수를 필요한 변수에 저장합니다.
		{
			*num = term;
			break;
		}
	}
	for (i = 0, k = 0; i < r_of_ary; i++)//정수를 입력받기 전과 동일한 형태의 과정입니다. 이동할 수 있는 영역을 인식할 때마다 어떠한 변수에 1을 추가하면서, 이전에 입력받은 정수와 비교하여 서로 같아질 때까지 과정을 반복합니다.
	{
		if (r_of_start - i == upRowDistance(arr, r_of_start))
		{
			for (j = 0; j < c_of_ary; j++)
			{
				if (arr[i][j] == 'A' || arr[i][j] == 'B' || arr[i][j] == 'N')
				{
					k += 1;
					if (k == *num)//이렇게 두 변수의 값이 같아졌을 경우, 개미를 이동시킬 영역의 배열 정보를 저장하여 이후에 사용할 수 있도록 합니다.
					{
						*r_of_end = i;
						*c_of_end = j;
					}
				}
			}
		}
		else if (i == r_of_start)
		{
			for (j = 0; j < c_of_start; j++)
			{
				if ((arr[i][j] == 'A' || arr[i][j] == 'B' || arr[i][j] == 'N') && ((c_of_start - j) == leftColumnDistance(arr, r_of_start, c_of_start)))
				{
					k += 1;
					if (k == *num)
					{
						*r_of_end = i;
						*c_of_end = j;
					}
				}
			}
			for (j = c_of_start + 1; j < c_of_ary; j++)
			{
				if ((arr[i][j] == 'A' || arr[i][j] == 'B' || arr[i][j] == 'N') && ((j - c_of_start) == rightColumnDistance(arr, r_of_start, c_of_start)))
				{
					k += 1;
					if (k == *num)
					{
						*r_of_end = i;
						*c_of_end = j;
					}
				}
			}
		}
		else if (i - r_of_start == downRowDistance(arr, r_of_start))
		{
			for (j = 0; j < c_of_ary; j++)
			{
				if (arr[i][j] == 'A' || arr[i][j] == 'B' || arr[i][j] == 'N')
				{
					k += 1;
					if (k == *num)
					{
						*r_of_end = i;
						*c_of_end = j;
					}
				}
			}
		}
	}
}

void dstn_com(int ary[][MAXCOLUMN], char arr[][MAXCOLUMN], int r_of_ary, int c_of_ary, int r_of_start_com, int c_of_start_com, int* r_of_end_com, int* c_of_end_com, int* num_com)
{//사용자가 개미를 이동시킬 영역을 선택하는 과정과 동일합니다. 단, 보기를 출력하고 선택하는 과정이 없이, 유효한 영역에 대해 임의의 숫자를 골라 주어진 영역에 대응시켜 개미를 이동시킬 영역을 자동으로 고를 수 있게 됩니다.
	int i, j, k;
	for (i = 0, k = 0; i < r_of_ary; i++)
	{
		if (r_of_start_com - i == upRowDistance(arr, r_of_start_com))
		{
			for (j = 0; j < c_of_ary; j++)
			{
				if (arr[i][j] == 'A' || arr[i][j] == 'B' || arr[i][j] == 'N')
				{
					k += 1;
				}
			}
		}
		else if (i == r_of_start_com)
		{
			for (j = 0; j < c_of_start_com; j++)
			{
				if ((arr[i][j] == 'A' || arr[i][j] == 'B' || arr[i][j] == 'N') && ((c_of_start_com - j) == leftColumnDistance(arr, r_of_start_com, c_of_start_com)))
				{
					k += 1;
				}
			}
			for (j = c_of_start_com + 1; j < c_of_ary; j++)
			{
				if ((arr[i][j] == 'A' || arr[i][j] == 'B' || arr[i][j] == 'N') && ((j - c_of_start_com) == rightColumnDistance(arr, r_of_start_com, c_of_start_com)))
				{
					k += 1;
				}
			}
		}
		else if (i - r_of_start_com == downRowDistance(arr, r_of_start_com))
		{
			for (j = 0; j < c_of_ary; j++)
			{
				if (arr[i][j] == 'A' || arr[i][j] == 'B' || arr[i][j] == 'N')
				{
					k += 1;
				}
			}
		}
	}
	*num_com = rand() % k + 1;
	for (i = 0, k = 0; i < r_of_ary; i++)
	{
		if (r_of_start_com - i == upRowDistance(arr, r_of_start_com))
		{
			for (j = 0; j < c_of_ary; j++)
			{
				if (arr[i][j] == 'A' || arr[i][j] == 'B' || arr[i][j] == 'N')
				{
					k += 1;
					if (k == *num_com)//이렇게 두 변수의 값을 비교하여 배열의 정보를 가져오는 과정이 같습니다.
					{
						*r_of_end_com = i;
						*c_of_end_com = j;
					}
				}
			}
		}
		else if (i == r_of_start_com)
		{
			for (j = 0; j < c_of_start_com; j++)
			{
				if ((arr[i][j] == 'A' || arr[i][j] == 'B' || arr[i][j] == 'N') && ((c_of_start_com - j) == leftColumnDistance(arr, r_of_start_com, c_of_start_com)))
				{
					k += 1;
					if (k == *num_com)
					{
						*r_of_end_com = i;
						*c_of_end_com = j;
					}
				}
			}
			for (j = c_of_start_com + 1; j < c_of_ary; j++)
			{
				if ((arr[i][j] == 'A' || arr[i][j] == 'B' || arr[i][j] == 'N') && ((j - c_of_start_com) == rightColumnDistance(arr, r_of_start_com, c_of_start_com)))
				{
					k += 1;
					if (k == *num_com)
					{
						*r_of_end_com = i;
						*c_of_end_com = j;
					}
				}
			}
		}
		else if (i - r_of_start_com == downRowDistance(arr, r_of_start_com))
		{
			for (j = 0; j < c_of_ary; j++)
			{
				if (arr[i][j] == 'A' || arr[i][j] == 'B' || arr[i][j] == 'N')
				{
					k += 1;
					if (k == *num_com)
					{
						*r_of_end_com = i;
						*c_of_end_com = j;
					}
				}
			}
		}
	}

}

void breed(int ary[][MAXCOLUMN], char arr[][MAXCOLUMN], int r_of_ary, int c_of_ary)//antCounts배열의 개미가 남아있는 영역에 대해 그 수를 1혹은 2만큼 증가시키는 함수입니다.
{
	int i, j;
	for (i = 0; i < r_of_ary; i++)
	{
		for (j = 0; j < c_of_ary; j++)
		{
			if ((i == 0) && (j == 0))//배열의 첫번째 칸은 A의 basement로서, 매 턴마다 2만큼 증가합니다.
			{
				ary[i][j] += 2;
			}
			else if ((i == (r_of_ary - 1)) && ((j == c_of_ary - 1)))//배열의 유효한 범위 내에서 마지막 칸은 B의 basement로서, 마찬가지로 매 턴마다 2만큼 증가해야합니다.. 하지만 B의 지역은 그 수가 음수로 나타나 있기 때문에 배열 상에는 2만큼 뺀 값을 새로이 저장합니다.
			{
				ary[i][j] -= 2;
			}
			else if (arr[i][j] == 'A')//basement가 아닌 영역에 대해서는, A의 영역의 개미의 수는 1만큼 증가합니다.
			{
				ary[i][j] += 1;
			}
			else if (arr[i][j] == 'B')//B의 영역은 같은 방식으로 1만큼 뺀 값을 배열에 저장합니다.
			{
				ary[i][j] -= 1;
			}

		}
	}
}

void PrintMap_after(char ary[][MAXCOLUMN], int arr[][MAXCOLUMN], int row, int column)//어떤 과정이 진행된 결과를 반영하여 새로운 map배열을 출력하는 함수입니다.
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < column; j++)
		{
			if (j == 0)
			{
				printf(" ");
			}
			if (ary[i][j] == 'A' || ary[i][j] == 'B' || ary[i][j] == 'N')//어떤 과정이 진행되기 전 map 배열에 A, B, N이 기록되어있는 칸에 대해서는 과정 전후로 숫자의 변화를 비교해야 합니다. 그 값이 0을 기준으로 바뀌었다면, map배열에 새로운 문자를 저장합니다. 
			{
				if (arr[i][j] < 0)
				{
					ary[i][j] = 'B';
				}
				else if (arr[i][j] == 0)
				{
					ary[i][j] = 'N';
				}
				else if (arr[i][j] > 0)
				{
					ary[i][j] = 'A';
				}
			}
			if (ary[i][j] == 'A')//위 과정을 통해 map배열이 새로고침 되었다면, 각 영역이 A, B, N중 어떤 것인지 판단하여 알맞을 색깔을 입혀 출력합니다.
			{
				printf(RED);
				printf(" %c ", ary[i][j]);
				printf(RESET);
			}
			else if (ary[i][j] == 'B')
			{
				printf(BLUE);
				printf(" %c ", ary[i][j]);
				printf(RESET);
			}
			else if (ary[i][j] == 'N')
			{
				printf(YELLOW);
				printf(" %c ", ary[i][j]);
				printf(RESET);
			}
			else
			{
				printf(" 0 ");
			}
		}
		printf("\n");
	}
}

void PrintAntCounts_after(char ary[][MAXCOLUMN], int arr[][MAXCOLUMN], int row, int column)//어떤 과정 이후의 결과를 반영하여 새로워진 antCounts배열을 출력하는 함수입니다. 이 함수는 항상 PrintMap_after함수 뒤에 오기때문에, 이미 map배열은 새로고침 된 상태입니다. 따라서 map배열을 기준으로 삼아 알맞은 값을 출력하도록 합니다.
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < column; j++)
		{
			if (j == 0)
			{
				printf(" ");
			}
			if (ary[i][j] == 'A')//이렇게 map배열에 저장되어 있는 문자를 비교하여 같은 칸에 해당하는 antCounts 배열의 숫자를 특정 색깔을 입혀 출력합니다.
			{
				printf(RED);
				printf("%2d ", abs(arr[i][j]));
				printf(RESET);
			}
			else if (ary[i][j] == 'B')
			{
				printf(BLUE);
				printf("%2d ", abs(arr[i][j]));
				printf(RESET);
			}
			else if (ary[i][j] == 'N')
			{
				printf(YELLOW);
				printf("%2d ", abs(arr[i][j]));
				printf(RESET);
			}
			else
			{
				printf(" 0 ");
			}
		}
		printf("\n");
	}
}

void check(int arr[][MAXCOLUMN], int row, int column, int* num)//게임이 끝날 조건을 만족하였는지 확인하는 함수입니다.
{
	if ((arr[0][0] <= 0) && (arr[row-1][column-1] < 0))//첫번째 칸이 0보다 작거나 같고, 마지막 칸이 0보다 작다면, A는 basement의 개미를 모두 잃은 것이고, B는 그렇지 않습니다. 따라서 사용자가 패배한 결과입니다. 즉, num에 저장되는 값이 1인 경우는 사용자가 패배했다는 뜻을 담고 있습니다.
	{
		*num = 1;
	}
	else if ((arr[0][0] > 0) && (arr[row-1][column-1] >= 0))//첫번째 칸이 0보다 크고, 마지막 칸이 0보다 크거나 같다면, B는 basement의 개미를 모두 잃은 것이고, A는 그렇지 않습니다. 따라서 사용자가 승리한 결과입니다. 즉, num에 저장되는 값이 2인 경우는 사용자가 승리했다는 뜻을 담고 있습니다.
	{
		*num = 2;
	}
	else if ((arr[0][0] <= 0) && (arr[row-1][column-1] >= 0))//첫번째 칸이 0보다 작거나 같고, 마지막 칸이 0보다 크거나 같다면, A와 B 모두 basement의 개미를 모두 잃은 것입니다. 따라서 사용자와 컴퓨터가 비긴 결과입니다. 즉, num에 저장되는 값이 3인 경우는 사용자와 컴퓨터가 비겼다는 뜻을 담고 있습니다.
	{
		*num = 3;
	}
	else if ((arr[0][0] > 0) && (arr[row-1][column-1] < 0))//첫번째 칸이 0보다 크고, 마지막 칸이 0보다 작다면, A와 B 모두 basement의 개미를 보유하고 있다는 것입니다. 게임은 끝나지 않았고, num에 저장되는 값이 0인 경우는 게임이 끝나지 않았다는 뜻을 담고 있습니다.
	{
		*num = 0;
	}
}

void last_ifm(int arr[][MAXCOLUMN], int row, int column, int* grd_num, int* grd_num_com, int* total_ant, int* total_ant_com)//게임이 끝난 후 필요한 정보들을 요약하여 정리하는 함수입니다.
{
	int i, j;
	for (i = 0, *grd_num = 0, *grd_num_com = 0, *total_ant = 0, *total_ant_com = 0; i < row; i++)//사용자와 컴퓨터가 보유한 영역의 개수와, 보유한 개미의 총합이 그 정보들입니다.
	{
		for (j = 0; j < column; j++)
		{
			if (arr[i][j] > 0)
			{
				*grd_num += 1;//이런 식으로 사용자 혹은 컴퓨터의 영역을 인지할 때마다 변수에는 1씩 더해지기 때문에 마지막에 저장되어 있는 값은 보유한 영역의 총 개수를 나타낼 것입니다.
				*total_ant = *total_ant + arr[i][j];//각 영역을 인지한 이후에는 antCounts배열에 저장되어 있는 숫자를 추가합니다. 마지막에는 보유한 개미의 총합을 나타낼 것입니다. 물론 컴퓨터의 개미는 절댓값을 씌워 양수의 형태로 저장합니다.
			}
			else if (arr[i][j] < 0)
			{
				*grd_num_com += 1;
				*total_ant_com = *total_ant_com + abs(arr[i][j]);
			}
		}
	}
}

void PrintResult(char map[][MAXCOLUMN], int antCounts[][MAXCOLUMN], int row, int column, int gameResult, int grd_num, int grd_num_com, int total_ant, int total_ant_com)//게임 결과의 요약 내용을 replay.txt 파일에 출력하는 함수입니다.
{
	FILE* outfile;
	outfile = fopen("replay.txt", "w");
	fprintf(outfile, "%c\n", gameResult);//첫번째 줄에는 사용자의 승패 결과를 출력합니다.
	fprintf(outfile, "%d %d\n", grd_num, total_ant);//두번째 줄에는 사용자의 영역의 수, 사용자가 보유한 개미의 총합을 출력합니다.
	fprintf(outfile, "%d %d\n", grd_num_com, total_ant_com);//세번째 줄에는 컴퓨터의 영역의 수, 컴퓨터가 보유한 개미의 총합을 출력합니다.
	fclose(outfile);
}
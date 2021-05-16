#include<stdio.h>
#include<stdlib.h>//abs ���� ����� ����ϱ� ���� ���Խ��׽��ϴ�.
#include<time.h>//�ð��� ���� ���������� ������ ���ڸ� �����ϱ� ���� ���Խ��׽��ϴ�.

#define RED "\x1b[31m"//����, �Ķ�, ����� ������ ���ڸ� ����ϱ� ���� ��ũ�� �Դϴ�.
#define BLUE "\x1b[34m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[0m"//���� ���� ���������� �缳���ϱ� ���� ��ũ�� �Դϴ�.

#define MAXROW 8//����� ��� ���� ���� 8�� �����մϴ�.(���Ŀ��� �ʿ��� �κи� ���������� �ٷ��, ����մϴ�.)
#define MAXCOLUMN 8

int ReadMap(char map[][MAXCOLUMN], int antCounts[][MAXCOLUMN], int*, int*, int*);//map.txt ���Ͽ��� �۾��� ���� ������ ������ �����ɴϴ�.
void PrintMap(char map[][MAXCOLUMN], int, int);//map.txt �κ��� ���� ������ �������� A, B, N�� ����� ������ ǥ���ϴ� �迭�� ����մϴ�.
void PrintAntCounts(char map[][MAXCOLUMN], int antCounts[][MAXCOLUMN], int, int);//map.txt �κ��� ���� ������ �������� �ش� ������ �ִ� ������ ���� �迭�� ����մϴ�.
void PrintResult(char map[][MAXCOLUMN], int antCounts[][MAXCOLUMN], int, int, int, int, int, int, int);//������ ������, �� ����� replay.txt ���Ͽ� ����մϴ�.
int leftColumnDistance(char a[][MAXCOLUMN], int, int);//�迭�� �ٷ궧�� ������ ������ ���ʹ������� ���� ����� ���������� �Ÿ��� ����մϴ�.
int rightColumnDistance(char a[][MAXCOLUMN], int, int);//�迭�� �ٷ궧�� ������ ������ �����ʹ������� ���� ����� ���������� �Ÿ��� ����մϴ�.
int upRowDistance(char a[][MAXCOLUMN], int);//�迭�� �ٷ궧�� ������ ������ ���ʹ������� ���� ����� ���������� �Ÿ��� ����մϴ�. �¿��� �Ÿ��� �����մϴ�.
int downRowDistance(char a[][MAXCOLUMN], int);//�迭�� �ٷ궧�� ������ ������ �Ʒ��ʹ������� ���� ����� ���������� �Ÿ��� ����մϴ�. �¿��� �Ÿ��� �����մϴ�.
void dstn(int ary[][MAXCOLUMN], char arr[][MAXCOLUMN], int, int, int, int, int*, int*, int*);//move turn ��, �����¿� �̵������� ������ ����, � �������� ���� �����ϴ� �����Դϴ�.
void dstn_com(int ary[][MAXCOLUMN], char arr[][MAXCOLUMN], int, int, int, int, int*, int*, int*);//move turn ��, ��ǻ���� �̵����� ������ ���� �� �� �ϳ��� �����ϴ� ������ �ڵ����� �����մϴ�.
void AntMove(int a[][MAXCOLUMN], int, int, int, int, int);//fight turn�� �ش��ϸ�, ������ �̵� ���� �ش� ������ �����ִ� ������ ���� ����մϴ�.
void breed(int ary[][MAXCOLUMN], char arr[][MAXCOLUMN], int, int);//breeding turn �� �� �������� ������ ���� �����ϴ� �����Դϴ�.
void PrintMap_after(char ary[][MAXCOLUMN], int arr[][MAXCOLUMN], int, int);//�� ���� ������ �� ������ �ݿ��Ͽ� ���ο� map�迭�� ����մϴ�.
void PrintAntCounts_after(char ary[][MAXCOLUMN], int arr[][MAXCOLUMN], int, int);//�� ���� ������ �� ������ �ݿ��Ͽ� ���ο� antCounts�迭�� ����մϴ�.
void check(int arr[][MAXCOLUMN], int, int, int*);//������ ���� ������ �����ϴ��� �Ǵ��ϴ� �Լ��Դϴ�.
void last_ifm(int arr[][MAXCOLUMN], int, int, int*, int*, int*, int*);//replay.txt �� ����� ������ ���� �����ϴ� �Լ��Դϴ�.


int main()
{

	int row, column, regionCount;//���ӿ� ���� �迭�� ���� ���� ���� row, column�� ��Ÿ����, ���� ���۽� ��Ÿ���� �߸������� ������ regionCount�� ��Ÿ���ϴ�.
	int start_r = 0, start_r_com = 0, start_c = 0, start_c_com = 0, dstn_r = 0, dstn_r_com = 0, dstn_c = 0, dstn_c_com = 0, num, num_com, send_num = 0, send_num_com = 0, check_num, grd_num, grd_num_com, total_ant, total_ant_com;//����ڿ� ��ǻ���� ������ �̵��� �־ �����ϴ� ĭ, �����ϴ� ĭ�� ���� ��, �̵��ϴ� ������ ��, �̵��� ���� ������ ��, ���� ������ ���� ��� ���� ������ �������Դϴ�. 
	int i, j, q, q_com, Q, Q_com, p, p_com;//���� ������ �־ ����ڿ��� �˷��� �������� ������ ������ ����� �����ϱ� ���� �����Դϴ�.
	int term = 0;//���� ó�� �������� ���Ǵ� �����Դϴ�.
	char test;//���������� ���� ó�� �������� ���˴ϴ�.
	char gameResult;//������ ���� Ȥ�� ���ºθ� W, L, D�� ��Ÿ���� �����Դϴ�.
	char map[MAXROW][MAXCOLUMN];//���ӿ��� ���� �迭��, ���Ŀ��� �ʿ��� �κи� ����ϰ� �˴ϴ�.
	int antCounts[MAXROW][MAXCOLUMN] = {0};//���������� ���ӿ��� ���� ������ �������� ��Ÿ���� �迭��, ���Ŀ��� �ʿ��� �κи� ����մϴ�.

	if (ReadMap(map, antCounts, &row, &column, &regionCount) == 0)//���� ����, map.txt ���Ϸ� ���� �迭�� ������ ������ �����ɴϴ�.
	{
		printf("There is no valid file.");//����ó�� -- ������ ���ٸ� �̷��� ������ ���� ���α׷��� �����ϰ� �˴ϴ�.
		return 0;
	}
	else
	{
		PrintMap(map, row, column);//map.txt �κ��� ������ �� �Է¹޾����� �迭 map�� antCounts�� �ʿ��� �κи��� �����Ͽ� ����մϴ�. row �� column�� ����� ���� ���� ������ �� �ֽ��ϴ�.
		printf("\n---------------------\n");
		PrintAntCounts(map, antCounts, row, column);
		printf("\n\n");
	}
	for (;;)//move, fight, breeding turn�� ������ ������ ������ ���� �ݺ��ϴ� �����Դϴ�.
	{
		for (i = 0, q = 0, q_com = 0; i < row; i++)//����ڿ� ��ǻ�Ͱ� ��, ���̸� �̵���ų ������ ������ �Ǵ��ϴ� �����Դϴ�. antCounts�� �� ĭ�� ����� ���� ����̸� ����ڰ� �� �� �ִ� �����̰�, �����̸� ��ǻ�Ͱ� �� �� �ִ� ���Դϴ�. 
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
		Q_com = rand() % q_com + 1;//��ǻ�Ϳ��� �־��� ������ ���� �� �ϳ��� ���Ƿ� �����մϴ�.
		printf("where ants start? ");//����ڰ� ������ ���⸦ �Է¹޴� �κ��Դϴ�.
		for (;;)//����ó�� -- ���� ���� ������ �Ǽ�, ���ڸ� �Է¹����� ���Է� �޵����ϴ� �κ��Դϴ�.
		{
			if (scanf("%d%c", &term, &test) != 2 || test != '\n')//%d �� %c�� �������� �Է¹޴´ٸ� �����Է� �� \n�� %c�� ���� scan�� ���Դϴ�. �Ҽ��� �Է��Ѵٸ� . �κп� ���� �߸��� �Է��̶�� �Ǵ��� �� �ְ�, ���ڰ� �Էµȴٸ� scanf�� ��ȯ���� ���� �߸��� �Է����� �Ǵ��մϴ�.
			{
				for (;;)//�̷��� ������ ���� ������ �ƴ� �Է� ���¿� ���� �������, \n�� scan�� �� ���� ������ getchar()�� ���� ���� ������ ������ �� �ְ�, ���� ������ ���� ���Է� �޵��� �մϴ�.
				{
					if (getchar() == '\n')
					{
						printf("Please type an integer from 1 to %d ", q);
						break;
					}						
				}
			}
			else if (term < 1 || term > q)//�Է� ���´� �ùٸ����� ������ ������ ���� ������ ��Ÿ�� ���� ���������� ���� ���Է� �޵��� �մϴ�.
			{
				printf("please type an integer from 1 to %d ", q);
			}
			else
			{
				Q = term;//���¿� ������ ��� ������ �ùٸ� �Է°��̶�� �� ���� ������ �����Ͽ� ���� �������� ����ϰ� �˴ϴ�.
				break;
			}
		}
		for (p = 0, p_com = 0, i = 0; i < row; i++)//��ǻ�Ϳ� ����ڰ� �� ���⸦ �������� ������ ����ɴϴ�. ���⸦ ����ϴ� ������ ���� ������ �ݺ��Ѵٸ�, �� ������ ���� ������ ����Ǳ� ������ � ������ ����ִ� ���⸦ �����ߴ��� �� �� �ֽ��ϴ�. ���� ����ڳ� ��ǻ�Ͱ� �� ���⿡ �ش��ϴ� ��ŭ�� for���� �����Ͽ� ������ ����ɴϴ�.
		{
			for (j = 0; j < column; j++)
			{
				if (antCounts[i][j] > 0)//�� ���������� antCounts �迭�� ����� ���� �������� ��������� ���� ����ڿ� ��ǻ�Ͱ� �� ������ ��, �� ������ ���� ������ �� �ֽ��ϴ�.
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
		dstn(antCounts, map, row, column, start_r, start_c, &dstn_r, &dstn_c, &num);//����ڿ� ��ǻ�Ͱ� �� ����� ���� ���̸� �̵���ų ĭ���� �迭�� ��� �κ��� �����ߴ��� Ȯ�� �� ����, �ش� ĭ���κ��� �¿���Ϸ� ������ �� �ִ� ���⸦ ����ϰ�, ������ ���� ������� ���⸦ �Է¹޾� �迭�� � ĭ�� �����ߴ��� �Ǵ��մϴ�.
		dstn_com(antCounts, map, row, column, start_r_com, start_c_com, &dstn_r_com, &dstn_c_com, &num_com);//����ڰ� �Է��ϴ� ������ ��ǻ�ʹ� �ڵ����� ������ ������ ����Ͽ� ó���մϴ�.
		printf("\nHow many ants go?(0 ~ %d) ", antCounts[start_r][start_c] - 1);//����ڰ� �� �� ���� ���̿��� �̵��� ������ ���� �Է¹޽��ϴ�.
		for (term = 0, send_num = 0;;)//����ó�� -- ���⸦ ������ ���� ���� ����� ����մϴ�.
		{
			if (scanf("%d%c", &term, &test) != 2 || test != '\n')//�Է� ������ �߸��Ǿ� �Ҽ��� ���ڰ� �Էµȴٸ� ���� ������ ���� ���Է� �޵��� �մϴ�.
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
			else if (term < 0 || term > antCounts[start_r][start_c]-1)//�Է� ������ �ùٸ����� ������ ������ �߸��Ǿ��� ��� ���� ������ ���� ���Է� �޵��� �մϴ�.
			{
				printf("Please type an integer from 0 to %d ", antCounts[start_r][start_c] - 1);
			}
			else//�Է��� ������ ��� �����Ǿ��ٸ� �� ���� ������ �����Ͽ� ���� ������ ����ϵ��� �մϴ�.
			{
				send_num = term;
				break;
			}
		}
		system("cls");//������ �̵� ���Ŀ� �ٲ� map�� antCounts �迭�� ����ϰ� ǥ���ϱ� ���� �ܼ� ȭ���� �ʱ�ȭ�մϴ�.
		if (abs(antCounts[start_r_com][start_c_com]) == 1)//���� ��ǻ�Ͱ� ���̸� ���� ������ �����ִ� ������ ���� 1�̶��, ������ ���� 1�� �ƴ� ���� ����� �Ŀ��� �������� ������ ����� ������ �� ��츦 �и��Ͽ� �ۼ��߽��ϴ�.
		{
			send_num_com = -1;
		}
		else
		{
			send_num_com = -(rand() % (abs(antCounts[start_r_com][start_c_com]) - 1) + 0);//������ ����� ������, Ư�� ������ �ּ��� 1������ ���� �� �ֵ��� ������ ���ڸ� �����մϴ�.
		}
		AntMove(antCounts, start_r, start_c, dstn_r, dstn_c, send_num);//����ڰ� ������ ���� ����, ������ ������ �� ��ŭ ���̰� �̵��� ����� �ݿ��Ͽ� �迭�� �� ���� �����ϴ� �����Դϴ�.
		AntMove(antCounts, start_r_com, start_c_com, dstn_r_com, dstn_c_com, send_num_com);//��ǻ�Ͱ� ���Ƿ� ������ ������ ������ �� ��ŭ ���̰� �̵��� ����� �ݿ��Ͽ� �迭�� �� ���� �����ϴ� �����Դϴ�. �� �� ������ �������� ���� �� ���� ������, �� �������� ������ ������ ��������� ���� ������ ������ �����Ѵٰ� �����ص� �����մϴ�.
		printf("Human sends %d ants from (%d, %d) to (%d, %d)\n", send_num, start_r, start_c, dstn_r, dstn_c);//����ڿ� ��ǻ�Ϳ� ���� �̵��� ������ ������ ���� ����Ͽ� �� ������ ���⽱�� �����մϴ�.
		printf("Computer sends %d ants from (%d, %d) to (%d, %d)\n", abs(send_num_com), start_r_com, start_c_com, dstn_r_com, dstn_c_com);
		printf("---------------------\n");
		printf("ants fight each other!\n\n");//fight turn���� �Ѿ�� ����ϴ� �κ��Դϴ�.
		PrintMap_after(map, antCounts, row, column);//Ư�� ������ ���� ������ ������ ����Ͽ� map�迭�� antCoutns�迭�� ����ϴ� �κ��Դϴ�.
		printf("---------------------\n");
		PrintAntCounts_after(map, antCounts, row, column);
		check(antCounts, row, column, &check_num);//fight turn���� ������ ���� ������ �����Ͽ����� Ȯ���մϴ�.
		if (check_num != 0)//check_num�� check�Լ����� ��ȯ�ϴ� ������, �� ���� 0�� ��쿡�� ������ ���� ������ �������� ���� ���̰�, 1, 2, 3�� ��쿡�� ������ ���� ������ ������ ����Դϴ�.
		{
			break;//���� check_num�� ��ȯ�� ���� 0�� �ƴ϶��, for���� ���������� ������ ������ �ϱ� ���� ������ �����մϴ�.
		}
		breed(antCounts, map, row, column);//������ ������ �ʾҴٸ�, �� ������ �����ϴ� ������ ���� ������ŵ�ϴ�. basement������ 2��ŭ, �� ���� ���������� 1��ŭ �����˴ϴ�.
		printf("\nants breeding!\n\n");
		PrintMap_after(map, antCounts, row, column);//breeding turn�� ����� �ݿ��Ͽ� ���ο��� map, antCounts�迭�� ����մϴ�.
		printf("---------------------\n");
		PrintAntCounts_after(map, antCounts, row, column);
		printf("\n\n");//��������� ������ �� �ܰ��Դϴ�. ������ ���� ������ ������ ������ �� �ܰ踦 ������ �ݺ��մϴ�.
	}
	if (check_num == 1)//������ ������, �� ����� �з��մϴ�. check_num�� ��ȯ�� ���� 1�̸� ����ڰ� �й�, 2�̸� ����ڰ� �¸�, 3�̸� ����ڿ� ��ǻ�Ͱ� ������� ���մϴ�.
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
	PrintMap_after(map, antCounts, row, column);//������ ������ ���� map, antCounts �迭�� ����Ͽ� � ������� ����Ǿ����� ����մϴ�.
	printf("---------------------\n");
	PrintAntCounts_after(map, antCounts, row, column);
	last_ifm(antCounts, row, column, &grd_num, &grd_num_com, &total_ant, &total_ant_com);//������ ���� ����� ����Ͽ� ���Ͽ� �����ϱ� ���� �ʿ��� ������ �̾Ƴ��ϴ�. ����ڿ� ��ǻ�Ͱ� �����ִ� ������ ����, ����ڿ� ��ǻ�Ϳ��� �����ִ� ������ �� ���� �� �����Դϴ�.
	PrintResult(map, antCounts, row, column, gameResult, grd_num, grd_num_com, total_ant, total_ant_com);//�ʿ��� ������ ��� �̾Ƴ´ٸ� replay.txt ���Ͽ� �� ������ ������ �°� ����մϴ�.
}

int ReadMap(char map[][MAXCOLUMN], int antCounts[][MAXCOLUMN], int* row, int* column, int* regionCount)//map.txt ���Ϸ� ���� �迭�� ������ ������ ������ �޾ƿ��� �Լ��Դϴ�.
{
	int i, r, c;
	char A, B, N;
	map[0][0] = 'A';//�� �迭�� ù��° ĭ�� �׻� A�� 10�� ���� ����˴ϴ�.
	antCounts[0][0] = 10;
	FILE* infile;
	infile = fopen("map.txt", "r");//map.txt ������ �б� �������� ���� �����Դϴ�.
	if (infile == NULL)//����ó�� -- ������ ���� ��쿡�� 0�� ��ȯ�ϰ�, �� ��ȯ���� �������� ���� ������ ����ϰ� �˴ϴ�.
	{
		return 0;
	}
	
	fscanf(infile, "%d", row);//���Ͽ� �����ִ� ������� ��, ��, �߸������� ������ �����մϴ�.
	fscanf(infile, "%d", column);
	fscanf(infile, "%d", regionCount);
	map[*row - 1][*column - 1] = 'B';//������ ��, ���� �������� �迭�� ���� �� �κ��� �׻� B, -10�� ������ �ο��ϰ� �˴ϴ�.(������ �ο��� ������ �� ������ ������ ������ ���� �����ϱ� �����Դϴ�.)
	antCounts[*row - 1][*column - 1] = -10;
	for (i = 0; i < (2 * *regionCount); i++)//�߸������� ������ŭ �ݺ������� ��� ���� scan�Ͽ� �迭 ���� �߸� ������ ��ġ�� �����մϴ�. 
	{
		fscanf(infile, "%d", &r);
		fscanf(infile, "%d", &c);
		map[r][c] = 'N';
	}
	return 1;
}

void PrintMap(char map[][MAXCOLUMN], int row, int column)//map�迭�� ����ϴ� �Լ��Դϴ�. �迭�� �ʿ��� �κп� ���ؼ� ��� �� ������ ��ġ�� �Ǹ�, map�迭�� ���Ͽ� A, B, N�� ���ڰ� ����Ǿ� �ִ� �κ��� �־��� ������ �ο��Ͽ� ����ϵ��� �մϴ�.
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

void PrintAntCounts(char map[][MAXCOLUMN], int antCounts[][MAXCOLUMN], int row, int column)//antCounts�迭�� ����ϴ� �Լ��Դϴ�. map�迭�� A, B, N ���ڰ� ����Ǿ� �ִٸ�, �ش� ĭ�� �����ϴ� antCounts�� ���ڸ� �־��� ������ ���� ����մϴ�. �迭�� �ʿ��� �κп� ���ؼ� ��� �� ������ ����˴ϴ�.
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

int leftColumnDistance(char a[][MAXCOLUMN], int r,int c)//�迭�� Ư���� ĭ�� ���� �� �� �ִ� ĭ�鿡 ���ؼ�, �������� ���� ����� ���������� �Ÿ��� �����մϴ�.
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

int rightColumnDistance(char a[][MAXCOLUMN], int r, int c)//�迭�� Ư���� ĭ�� ���� �� �� �ִ� ĭ�鿡 ���ؼ�, ���������� ���� ����� ���������� �Ÿ��� �����մϴ�.
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

int upRowDistance(char a[][MAXCOLUMN], int r)//�迭�� Ư���� ĭ�� ���Ͽ�, �������� ���� ����� ���������� �Ÿ��� �����մϴ�. �¿��� �Ÿ�, �� ���� ���̴� ������� �ʽ��ϴ�.
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

int downRowDistance(char a[][MAXCOLUMN], int r)//�迭�� Ư���� ĭ�� ���Ͽ�, �Ʒ������� ���� ����� ���������� �Ÿ��� �����մϴ�. �¿��� �Ÿ�, �� ���� ���̴� ������� �ʽ��ϴ�.
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

void AntMove(int a[][MAXCOLUMN], int from_r, int from_c, int to_r, int to_c, int n)//���õ� �� �������� Ư���� ���� ��ŭ�� ������ �̵� ������ ����մϴ�. ������ ��쿡 ���� �������� ������ �����ϴ�.
{
	a[from_r][from_c] -= n;
	a[to_r][to_c] += n;
}

void dstn(int ary[][MAXCOLUMN], char arr[][MAXCOLUMN], int r_of_ary, int c_of_ary, int r_of_start, int c_of_start, int* r_of_end, int* c_of_end, int* num)
{//Ư�� ������ ������ ���Ŀ� ���̸� �̵���ų �� �ִ� ������ �����ϴ� �����Դϴ�.
	int i, j, k, Q = 0;
	int term = 0;
	char test;
	for (i = 0, k = 0; i < r_of_ary; i++)//���� �迭�� �� ���� �����մϴ�.
	{
		if (r_of_start - i == upRowDistance(arr, r_of_start))//�����ϴ� ���� ������ �������� ���� �ִ� ��쿡��, ��� ���� upRowDistance�� �������� ���ϰ�, �����ϴ� �࿡ ���ؼ��� �� �࿡ �����ϴ� ��� ������ �̵��� �� �ִ� �������� �ν��մϴ�.
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
		else if (i == r_of_start)//�����ϴ� ���� ������ ������ ��� ���� ��쿡��, ������ ������ �¿� leftColumnDistance�� rightColumnDistance�� �Ǵ��Ͽ� �̵��� �� �ִ� ������ �Ǵ��մϴ�.
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
		else if (i - r_of_start == downRowDistance(arr, r_of_start))//�����ϴ� ���� ������ �������� �Ʒ��� ���� ��쿡��, ��� ���� downRowDistance�� �����ϴ��� Ȯ���ϰ�, �� �� �� �ִ� ��� ������ ���� �̵��� �� �ִ� �������� �����մϴ�.
		{
			for (j = 0; j < c_of_ary; j++)
			{
				if (arr[i][j] == 'A' || arr[i][j] == 'B' || arr[i][j] == 'N')
				{
					k += 1;//�̵��� �� �ִ� ������ �ν��� ������, k�������� 1�� �߰��˴ϴ�. k������ �̵��� �� �ִ� ������ ������ ���� �����Դϴ�. �� ����ڿ��� ����� ��ȿ�� ������ ������ �����ϴ�.
					printf("%d : (%d, %d)\n", k, i, j);
				}
			}
		}
	}
	printf("where ants go? ");//����ڿ��� ���̸� �̵���ų ������ ����� ��� ����ߴٸ�, ����ڷκ��� Ư�� ���⸦ �Է¹޽��ϴ�.
	for (;;)//����ó�� -- �ٸ� ���� ���� ����� ���մϴ�.
	{
		if (scanf("%d%c", &term, &test) != 2 || test != '\n')//������ �ƴ� �Ҽ��� ���� �Ǽ���, ���ڸ� �Է¹޾��� ���, ���� ������ �Բ� ���Է� �޵��� �մϴ�.
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
		else if (term < 1 || term > k)//�Է� ���´� �ùٸ����� ������ ������ �ùٸ��� ���� ���, ���� ���� ������ �Բ� ���Է� �޵��� �մϴ�.
		{
			printf("please type an integer from 1 to %d ", k);
		}
		else//�Է� ������ ���������� ���, �Էµ� ������ �ʿ��� ������ �����մϴ�.
		{
			*num = term;
			break;
		}
	}
	for (i = 0, k = 0; i < r_of_ary; i++)//������ �Է¹ޱ� ���� ������ ������ �����Դϴ�. �̵��� �� �ִ� ������ �ν��� ������ ��� ������ 1�� �߰��ϸ鼭, ������ �Է¹��� ������ ���Ͽ� ���� ������ ������ ������ �ݺ��մϴ�.
	{
		if (r_of_start - i == upRowDistance(arr, r_of_start))
		{
			for (j = 0; j < c_of_ary; j++)
			{
				if (arr[i][j] == 'A' || arr[i][j] == 'B' || arr[i][j] == 'N')
				{
					k += 1;
					if (k == *num)//�̷��� �� ������ ���� �������� ���, ���̸� �̵���ų ������ �迭 ������ �����Ͽ� ���Ŀ� ����� �� �ֵ��� �մϴ�.
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
{//����ڰ� ���̸� �̵���ų ������ �����ϴ� ������ �����մϴ�. ��, ���⸦ ����ϰ� �����ϴ� ������ ����, ��ȿ�� ������ ���� ������ ���ڸ� ��� �־��� ������ �������� ���̸� �̵���ų ������ �ڵ����� �� �� �ְ� �˴ϴ�.
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
					if (k == *num_com)//�̷��� �� ������ ���� ���Ͽ� �迭�� ������ �������� ������ �����ϴ�.
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

void breed(int ary[][MAXCOLUMN], char arr[][MAXCOLUMN], int r_of_ary, int c_of_ary)//antCounts�迭�� ���̰� �����ִ� ������ ���� �� ���� 1Ȥ�� 2��ŭ ������Ű�� �Լ��Դϴ�.
{
	int i, j;
	for (i = 0; i < r_of_ary; i++)
	{
		for (j = 0; j < c_of_ary; j++)
		{
			if ((i == 0) && (j == 0))//�迭�� ù��° ĭ�� A�� basement�μ�, �� �ϸ��� 2��ŭ �����մϴ�.
			{
				ary[i][j] += 2;
			}
			else if ((i == (r_of_ary - 1)) && ((j == c_of_ary - 1)))//�迭�� ��ȿ�� ���� ������ ������ ĭ�� B�� basement�μ�, ���������� �� �ϸ��� 2��ŭ �����ؾ��մϴ�.. ������ B�� ������ �� ���� ������ ��Ÿ�� �ֱ� ������ �迭 �󿡴� 2��ŭ �� ���� ������ �����մϴ�.
			{
				ary[i][j] -= 2;
			}
			else if (arr[i][j] == 'A')//basement�� �ƴ� ������ ���ؼ���, A�� ������ ������ ���� 1��ŭ �����մϴ�.
			{
				ary[i][j] += 1;
			}
			else if (arr[i][j] == 'B')//B�� ������ ���� ������� 1��ŭ �� ���� �迭�� �����մϴ�.
			{
				ary[i][j] -= 1;
			}

		}
	}
}

void PrintMap_after(char ary[][MAXCOLUMN], int arr[][MAXCOLUMN], int row, int column)//� ������ ����� ����� �ݿ��Ͽ� ���ο� map�迭�� ����ϴ� �Լ��Դϴ�.
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
			if (ary[i][j] == 'A' || ary[i][j] == 'B' || ary[i][j] == 'N')//� ������ ����Ǳ� �� map �迭�� A, B, N�� ��ϵǾ��ִ� ĭ�� ���ؼ��� ���� ���ķ� ������ ��ȭ�� ���ؾ� �մϴ�. �� ���� 0�� �������� �ٲ���ٸ�, map�迭�� ���ο� ���ڸ� �����մϴ�. 
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
			if (ary[i][j] == 'A')//�� ������ ���� map�迭�� ���ΰ�ħ �Ǿ��ٸ�, �� ������ A, B, N�� � ������ �Ǵ��Ͽ� �˸��� ������ ���� ����մϴ�.
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

void PrintAntCounts_after(char ary[][MAXCOLUMN], int arr[][MAXCOLUMN], int row, int column)//� ���� ������ ����� �ݿ��Ͽ� ���ο��� antCounts�迭�� ����ϴ� �Լ��Դϴ�. �� �Լ��� �׻� PrintMap_after�Լ� �ڿ� ���⶧����, �̹� map�迭�� ���ΰ�ħ �� �����Դϴ�. ���� map�迭�� �������� ��� �˸��� ���� ����ϵ��� �մϴ�.
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
			if (ary[i][j] == 'A')//�̷��� map�迭�� ����Ǿ� �ִ� ���ڸ� ���Ͽ� ���� ĭ�� �ش��ϴ� antCounts �迭�� ���ڸ� Ư�� ������ ���� ����մϴ�.
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

void check(int arr[][MAXCOLUMN], int row, int column, int* num)//������ ���� ������ �����Ͽ����� Ȯ���ϴ� �Լ��Դϴ�.
{
	if ((arr[0][0] <= 0) && (arr[row-1][column-1] < 0))//ù��° ĭ�� 0���� �۰ų� ����, ������ ĭ�� 0���� �۴ٸ�, A�� basement�� ���̸� ��� ���� ���̰�, B�� �׷��� �ʽ��ϴ�. ���� ����ڰ� �й��� ����Դϴ�. ��, num�� ����Ǵ� ���� 1�� ���� ����ڰ� �й��ߴٴ� ���� ��� �ֽ��ϴ�.
	{
		*num = 1;
	}
	else if ((arr[0][0] > 0) && (arr[row-1][column-1] >= 0))//ù��° ĭ�� 0���� ũ��, ������ ĭ�� 0���� ũ�ų� ���ٸ�, B�� basement�� ���̸� ��� ���� ���̰�, A�� �׷��� �ʽ��ϴ�. ���� ����ڰ� �¸��� ����Դϴ�. ��, num�� ����Ǵ� ���� 2�� ���� ����ڰ� �¸��ߴٴ� ���� ��� �ֽ��ϴ�.
	{
		*num = 2;
	}
	else if ((arr[0][0] <= 0) && (arr[row-1][column-1] >= 0))//ù��° ĭ�� 0���� �۰ų� ����, ������ ĭ�� 0���� ũ�ų� ���ٸ�, A�� B ��� basement�� ���̸� ��� ���� ���Դϴ�. ���� ����ڿ� ��ǻ�Ͱ� ��� ����Դϴ�. ��, num�� ����Ǵ� ���� 3�� ���� ����ڿ� ��ǻ�Ͱ� ���ٴ� ���� ��� �ֽ��ϴ�.
	{
		*num = 3;
	}
	else if ((arr[0][0] > 0) && (arr[row-1][column-1] < 0))//ù��° ĭ�� 0���� ũ��, ������ ĭ�� 0���� �۴ٸ�, A�� B ��� basement�� ���̸� �����ϰ� �ִٴ� ���Դϴ�. ������ ������ �ʾҰ�, num�� ����Ǵ� ���� 0�� ���� ������ ������ �ʾҴٴ� ���� ��� �ֽ��ϴ�.
	{
		*num = 0;
	}
}

void last_ifm(int arr[][MAXCOLUMN], int row, int column, int* grd_num, int* grd_num_com, int* total_ant, int* total_ant_com)//������ ���� �� �ʿ��� �������� ����Ͽ� �����ϴ� �Լ��Դϴ�.
{
	int i, j;
	for (i = 0, *grd_num = 0, *grd_num_com = 0, *total_ant = 0, *total_ant_com = 0; i < row; i++)//����ڿ� ��ǻ�Ͱ� ������ ������ ������, ������ ������ ������ �� �������Դϴ�.
	{
		for (j = 0; j < column; j++)
		{
			if (arr[i][j] > 0)
			{
				*grd_num += 1;//�̷� ������ ����� Ȥ�� ��ǻ���� ������ ������ ������ �������� 1�� �������� ������ �������� ����Ǿ� �ִ� ���� ������ ������ �� ������ ��Ÿ�� ���Դϴ�.
				*total_ant = *total_ant + arr[i][j];//�� ������ ������ ���Ŀ��� antCounts�迭�� ����Ǿ� �ִ� ���ڸ� �߰��մϴ�. ���������� ������ ������ ������ ��Ÿ�� ���Դϴ�. ���� ��ǻ���� ���̴� ������ ���� ����� ���·� �����մϴ�.
			}
			else if (arr[i][j] < 0)
			{
				*grd_num_com += 1;
				*total_ant_com = *total_ant_com + abs(arr[i][j]);
			}
		}
	}
}

void PrintResult(char map[][MAXCOLUMN], int antCounts[][MAXCOLUMN], int row, int column, int gameResult, int grd_num, int grd_num_com, int total_ant, int total_ant_com)//���� ����� ��� ������ replay.txt ���Ͽ� ����ϴ� �Լ��Դϴ�.
{
	FILE* outfile;
	outfile = fopen("replay.txt", "w");
	fprintf(outfile, "%c\n", gameResult);//ù��° �ٿ��� ������� ���� ����� ����մϴ�.
	fprintf(outfile, "%d %d\n", grd_num, total_ant);//�ι�° �ٿ��� ������� ������ ��, ����ڰ� ������ ������ ������ ����մϴ�.
	fprintf(outfile, "%d %d\n", grd_num_com, total_ant_com);//����° �ٿ��� ��ǻ���� ������ ��, ��ǻ�Ͱ� ������ ������ ������ ����մϴ�.
	fclose(outfile);
}
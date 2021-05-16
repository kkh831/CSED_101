#include<stdio.h>
#include<stdlib.h>//system("cls")�� ����ϱ� ���� stdlib.h�� ���Խ��׽��ϴ�.
#include<math.h>//����� ������ ��հ��� ������ȯ�� ���������� �����ϱ� ���� math.h�� ���Խ��׽��ϴ�.

char print_divider();//'='40���� ����Ͽ� �ܰ踦 �����ϴ� �Լ��Դϴ�.
char print_poles(int, int, int);//3���� ����� '��'�� ǥ���ϴ� �Լ��Դϴ�.
char print_one_pole(int, int);//��տ� ���ԵǾ� �ִ� ���ڸ� '��'�� ��ȯ�Ͽ� ǥ���ϴ� �Լ��Դϴ�.
void process(int);//�� ��° step����, �ش� step������ �� ����� ����� �����, ��� ������ �������� �� ��� ������ ��Ʋ�� �����ϴ� �Լ��Դϴ�.
int check_not_empty(int);//�Է¹��� ������ ����� ����ִ���, �� ����� ��Ÿ���� ���ڰ� 0�� �ƴ����� Ȯ���ϴ� �Լ��Դϴ�.
int check_valid_move(int, int);//���� �ű� ��հ� �Ű��� ��տ� �����Ǿ��ִ� ������ ���踦 �ľ��Ͽ� �ϳ����� ž�� ��Ģ�� ��߳����� Ȯ���ϴ� �Լ��Դϴ�.
int check_finish(int, int, int);//��� ���� ù��° ������κ��� �ٸ� ������� �ϳ����� ž�� ��Ģ��� �̵��Ǿ������� �ľ��Ͽ� ������ �������ϴ� �Լ��Դϴ�.
void shifting(int*, int*);//���� �ű� ��հ� �Ű��� ����� �Է��ϰ� �Ǹ� �� ��տ� ������ ���ڸ� ���� ������ ��ȯ�ϴ� �Լ��Դϴ�.
int head_of_number(int);//� ���� ���� ���� �ڸ����� ���ڸ� ��ȯ�ϴ� �Լ��Դϴ�. ex) 3647�� �Է��ϸ� 3�� ��ȯ
int cipher(int);//� ���� ���ڸ��� �������� ��ȯ�ϴ� �Լ��Դϴ�. ex) 27254�� �Է��ϸ� 5�� ��ȯ
int smallest_number(int);//� ���� ���� �ڸ� ���� ��ȯ�ϴ� �Լ��Դϴ�.

int main()
{
	int floor;
	printf("�ϳ����� ž �� ���� �����ּ���(1������ 5�� ����): ");
	scanf("%d", &floor);//�ϳ����� ž ������ �Է� �޽��ϴ�.
	for (1 ; ; )
	{
		if (floor < 1 || floor > 5)//�Էµ� ���� ��ȿ�� ���� ���� ���� ���� ���� ���ǹ��Դϴ�.
		{
			printf("�߸��� �Է��Դϴ�. 1���� 5 ������ ���ڸ� �Է����ּ���: ");
			scanf("%d", &floor);//�ش� ���ǿ��� ���� ���� ���ڸ� �Է��� ���� �䱸�ϰ� �Է¹޽��ϴ�. ���� for ���� ���� �ٽ� ��ȿ�� ���� ���� �ִ����� �˻��մϴ�.
		}
		
		if (floor >= 1 && floor <= 5)//�Էµ� ���� ��ȿ�� ���� ���� �ִٸ�, break�� ���� for ���� ���������ϴ�.
			break;
	}
	process(floor);//�Էµ� �� ���� �ش��ϴ� ��� �ϳ����� ž ������ �����մϴ�.
}

void process(int floor)
{
	int step, from, to, number_of_pole1, number_of_pole2, number_of_pole3, number_of_from, number_of_to;//step�� �ܰ踦, from�� to�� ���� �ű� ��հ� �Ű��� �����, number_of_pole 1,2,3 �� �� ��տ� ����� ���ڸ�, number_of_from, to�� ���� ���� �ű� ��հ� �Ű��� ��տ� ����� ���ڸ� ��Ī�մϴ�.
	for (step = 1, number_of_pole1 = 12345 / pow(10, 5 - floor), number_of_pole2 = 0, number_of_pole3 = 0; ; step++)//���� ū for�����μ�, step�� ���ں��� �� �ܰ��� ����� ǥ���ϰ�, ������ ������ �Ǵ��մϴ�. step�� 1�϶�, pole�� ������ 12345�� 10�� �������� ���� ������ ��������ν� ������ ǥ���� �� �ֽ��ϴ�.
	{
		print_divider();
		printf(">>>Step %d\n", step);//���° step���� for���� ������ ���� ǥ���մϴ�.
		print_poles(number_of_pole1, number_of_pole2, number_of_pole3);//�ش� �ܰ��� ��յ鿡 ����� ���ڸ� '��'�� ǥ���մϴ�.
		print_divider();
		if (step >= 2)//���� ��� �Ű����� ��� �������ϴ� �Լ��μ�, ù��° �ܰ�� ���ܽ��� �������ڸ��� ������� �����մϴ�.
		{
			if (check_finish(number_of_pole1, number_of_pole2, number_of_pole3))//ù��° ����� ���� �ٸ� ������� ��� �Ű����� ��츦 �Ǵ��� �´ٸ� �����ϰ�, Ʋ���ٸ� break�� ���� ��ü for���� ���������� ������ ������ �̾ �����մϴ�.
			{
				printf("���� ��� �ٸ� ������� �Ű������ϴ�. ������ �����մϴ�.");
				break;
			}
		}
		printf("1.���� �ű� ����� �������ּ���.<1-3>: ");
		scanf("%d", &from);//���� �ű� ����� �Է¹޽��ϴ�.

		for (; ;)
		{
			if (from < 1 || from > 3)//�Է¹��� ���ڰ� ��ȿ�� ������ �ִ����� �Ǵ��Ͽ�, ������ ����ٸ� ���ο� ���ڸ� �Է��ϱ⸦ �䱸�ϰ� ���Ӱ� ������ �� ������ ������ �����ϰ�, ���Ӱ� �Է¹��� ���ڰ� �ٽ� ������ ����ٸ� for���� ���� �ٽ� ��ȿ�� ������ �ִ����� �Ǵ��ϴ� ������ ��Ĩ�ϴ�.
			{
				printf("1.�߸��� �Է��Դϴ�. 1���� 3 ������ ���ڸ� �Է����ּ���: ");
				scanf("%d", &from);
			}

			if (from == 1)//���� �ű� ������� ù��° ����� �������� ��, ���� ù��° ����� ����ִ� ���� Ȯ���ϰ�, ����ִٸ� �ٸ� ���ڸ� �Է��ϱ⸦ �䱸�ϰ�, ������� �ʴٸ� ù��° ��տ� ����� ���ڸ� number_of_from�� �����մϴ�. �� ������ ���� shifting�Լ����� number_of_to �� ���ϱ� ���ؼ� �Դϴ�.
			{
				if (check_not_empty(number_of_pole1) == 1)
				{
					number_of_from = number_of_pole1;
					break;
				}
				else
				{
					printf("1.�ش� ����� ����ֽ��ϴ�. ������� ���� ����� �������ּ���: ");
					scanf("%d", &from);
				}
				
			}

			if (from == 2)//ù��° ����� �������� ���� ���� �����Դϴ�.
			{
				if (check_not_empty(number_of_pole2) == 1)
				{
					number_of_from = number_of_pole2;
					break;
				}
				else
				{
					printf("1.�ش� ����� ����ֽ��ϴ�. ������� ���� ����� �������ּ���: ");
					scanf("%d", &from);
				}
			}

			if (from == 3)//ù��° ����� �������� ���� ���� �����Դϴ�.
			{
				if (check_not_empty(number_of_pole3) == 1)
				{
					number_of_from = number_of_pole3;
					break;
				}
				else
				{
					printf("1.�ش� ����� ����ֽ��ϴ�. ������� ���� ����� �������ּ���: ");
					scanf("%d", &from);
				}
			}
		}
		

		printf("2.���� �Ű��� ����� �������ּ���.<1-3>: ");
		scanf("%d", &to);//���� �Ű��� ����� �Է¹޽��ϴ�.
		for (; ;)
		{
			if (to < 1 || to > 3)//���� �Ű��� ������� �Է¹��� ���ڰ� ��ȿ�� �������� �ִ��� Ȯ���ϰ�, ����ٸ� �ٽ� for���� ���� ���ο� ���ڸ� �Է¹�����, �������� �ִٸ� ������ ������ �����մϴ�.
			{
				printf("2.�߸��� �Է��Դϴ�. 1���� 3 ������ ���ڸ� �Է����ּ���: ");
				scanf("%d", &to);
			}

			else if (to == 1)//���� �Ű��� ������� ù��° ����� �����ߴٸ�, �̵��� ���õ� �� ����� ���õǾ����Ƿ� �� ��տ� ����� ���ڸ� ���Ͽ� �ϳ����� ž ��Ģ�� �����ϴ��� Ȯ���մϴ�.
			{
				if (check_valid_move(head_of_number((int)number_of_from), head_of_number((int)number_of_pole1))==1)//���� �ű� ����� ���� �� ���� ���� �Ű��� ����� ���� �� �� ���� �̵��ȴٴ� ���� ����Ͽ� ���ڸ� ���մϴ�. �ϳ����� ž ��Ģ�� �����Ϸ��� ���� �ű� ��տ� ����� ������ ���� ���� �ڸ��� ���� ���� �Ű��� ��տ� ����� ������ ���� ���� �ڸ��� ������ �۾ƾ� �մϴ�.
				{
					if (number_of_from == number_of_pole1)//�ϳ����� ž ��Ģ�� �����ߴٸ�, number_of_to�� ���� �Ű��� ����� ���ڸ� �����մϴ�. ���� number_of_from�� number_of_to�� ����� ���� ���� shifting�� �̷�����ϴ�. �� ������ shifting�Լ� �κп��� ����˴ϴ�. ����, ��ü for���� ���� ���� �ܰ�� �Ѿ�� ���� ��츦 ���� shifting�� ����� �� ��տ� ���Ӱ� �����մϴ�.
					{
						number_of_to = number_of_pole1;
						shifting(&number_of_from, &number_of_to);
						number_of_pole1 = number_of_to;
						number_of_pole1 = number_of_from;
						break;
					}
					else if (number_of_from == number_of_pole2)//ù��° if���� ������ �����Դϴ�.
					{
						number_of_to = number_of_pole1;
						shifting(&number_of_from, &number_of_to);
						number_of_pole1 = number_of_to;
						number_of_pole2 = number_of_from;
						break;
					}
					else if (number_of_from == number_of_pole3)//ù��° if���� ������ �����Դϴ�.
					{
						number_of_to = number_of_pole1;
						shifting(&number_of_from, &number_of_to);
						number_of_pole1 = number_of_to;
						number_of_pole3 = number_of_from;
						break;
					}
				}
				else
				{
					printf("2.�ϳ����� ž ��Ģ�� ��߳��ϴ�. �ٸ� ����� �������ּ���: ");//�ϳ����� ž ��Ģ�� �Ǵ��� ��� ��Ģ�� ��߳��ٸ�, shifting �ܰ�� �Ѿ�� �ʰ� ���ο� ���ڸ� �Է¹��� �� for���� ���� ���� ������ �ݺ��մϴ�.
					scanf("%d", &to);
				}
			}
			else if (to == 2)//���� �Ű��� ������� �ι�° ����� ������ ������, ù��° ����� �������� ���� �����մϴ�.
			{
				if (check_valid_move(head_of_number((int)number_of_from), head_of_number((int)number_of_pole2))==1)
				{
					if (number_of_from == number_of_pole1)
					{
						number_of_to = number_of_pole2;
						shifting(&number_of_from, &number_of_to);
						number_of_pole2 = number_of_to;
						number_of_pole1 = number_of_from;
						break;
					}
					else if (number_of_from == number_of_pole2)
					{
						number_of_to = number_of_pole2;
						shifting(&number_of_from, &number_of_to);
						number_of_pole2 = number_of_to;
						number_of_pole2 = number_of_from;
						break;
					}
					else if (number_of_from == number_of_pole3)
					{
						number_of_to = number_of_pole2;
						shifting(&number_of_from, &number_of_to);
						number_of_pole2 = number_of_to;
						number_of_pole3 = number_of_from;
						break;
					}
				}
				else
				{
					printf("2.�ϳ����� ž ��Ģ�� ��߳��ϴ�. �ٸ� ����� �������ּ���: ");
					scanf("%d", &to);
				}
			}
			else if (to == 3)//���� �Ű��� ������� ����° ����� ������ ������, ù��° ����� �������� ���� �����մϴ�.
			{
				if (check_valid_move(head_of_number((int)number_of_from), head_of_number((int)number_of_pole3))==1)
				{
					if (number_of_from == number_of_pole1)
					{
						number_of_to = number_of_pole3;
						shifting(&number_of_from, &number_of_to);
						number_of_pole3 = number_of_to;
						number_of_pole1 = number_of_from;
						break;
					}
					else if (number_of_from == number_of_pole2)
					{
						number_of_to = number_of_pole3;
						shifting(&number_of_from, &number_of_to);
						number_of_pole3 = number_of_to;
						number_of_pole2 = number_of_from;
						break;
					}
					else if (number_of_from == number_of_pole3)
					{
						number_of_to = number_of_pole3;
						shifting(&number_of_from, &number_of_to);
						number_of_pole3 = number_of_to;
						number_of_pole3 = number_of_from;
						break;
					}
				}
				else
				{
					printf("2.�ϳ����� ž ��Ģ�� ��߳��ϴ�. �ٸ� ����� �������ּ���: ");
					scanf("%d", &to);
				}
			}
		}
			system("cls");//�� ����� shifting�� ������ ǥ�õǾ��� ��յ��� ����� ����ϴ�.
			printf("Block Moved!\n");//block�� �Ű����ٴ� ǥ�ø� ���ݴϴ�.
	}//���� step2�� ������ �����մϴ�.
}

char print_divider()//�ܰ踦 �����ϴ� �Լ���, '='�� 40�� �ݺ��ϴ� for���� �ι� �ݺ��ϴ� ���������� ����մϴ�.
{
	int i, j;
	for (j = 1; j <= 2; j++)
	{
		for (i = 1; i <= 40; i++)
		{
			printf("=");
		}
		printf("\n");
	}
}

char print_poles(int number_of_pole1, int number_of_pole2, int number_of_pole3)//�� ����� ���鿡 ����� ���ڸ� ����Ͽ� ���� ����մϴ�.
{
	printf("[��� 1]\n");
	print_one_pole(number_of_pole1, cipher(number_of_pole1));
	printf("\n");
	printf("[��� 2]\n");
	print_one_pole(number_of_pole2, cipher(number_of_pole2));
	printf("\n");
	printf("[��� 3]\n");
	print_one_pole(number_of_pole3, cipher(number_of_pole3));
}

char print_one_pole(int a, int b)//�� ����� ���� ����ϴ� �Լ��Դϴ�. ����� ������ �ڸ��� ��ŭ �ݺ��ϴ� for�� ������, 10�� �������� ���� ���� ���� �ڸ��� ��ŭ '��'�� ����ϴ� for���� �����ϴ� ���������� ��������ν� ����� ������ '��'�� ǥ���� �� �ֽ��ϴ�. ����� ���ڰ� 0�̸� ����� ����ٴ� ���� 'Pole is empty'�� ����մϴ�.
{
	int c, d;
	if (a == 0)
	{
		printf("Pole is empty\n");
	}
	else
	{
		for (c = 1; c <= b; c++)
		{
			for (d = 1; d <= smallest_number(a / pow(10, b - c)); d++)
			{
				printf("��");
			}
			printf("\n");
		}
	}
}


int check_not_empty(int k)//��տ� ����� ������ 0�̸� ����� ����ٰ� �Ǵ��ϴ� �Լ��Դϴ�.
{
	int result;
	if (k == 0)
	{
		result = 0;
	}
	else
	{
		result = 1;
	}
	return result;
}

int check_valid_move(int a, int b)//�ϳ����� ž ��Ģ�� �ٰ��Ͽ� ��ȿ�� �̵������� �Ǵ��ϴ� �Լ��Դϴ�. ������ �� ����� ���� ���� �ڸ��� ���� ���Ͽ� �Ǵ��մϴ�. ���� �Ű��� ����� ����ִٸ� ��� ����� ���� �� �� �ֱ� ������ ���Ǻο� b!=0�� ���Խ��׽��ϴ�.
{
	int result;
	if (a > b && b != 0)
	{
		result = 0;
	}
	else
	{
		result = 1;
	}
	return result;
}
int check_finish(int a, int b, int c)//ù��° ����� ���� �ٸ� ������� ��� �Ű��������� �Ǵ��ϴ� �Լ��Դϴ�. ��Ģ�� ��߳��� �ʴ� �̵��� ���� �� ������� ��� ���� �𿴴ٸ�, ������ �� ����� ����ִٴ� ���� ����߽��ϴ�. ���� ��� �� ��տ� ����� ���� ��� 0�̸� ������ ������ �ϵ��� �Ǿ��ֽ��ϴ�. ��, process�Լ����� ù step�� ���� �����߽��ϴ�.
{
	int result;
	if (a == 0 && b == 0 || b == 0 && c == 0 || a == 0 && c == 0 )
	{
		result = 1;
	}
	else
	{
		result = 0;
	}
	return result;
}

int head_of_number(int x)//� ���� ���� ���� �ڸ��� ���� ���ϴ� �Լ���, �Է¹��� ���� 101���� �۾��� ������ 10���� ��� ������ �� ���� ��ȯ�ϴ� for�� �����Դϴ�.
{
	int quotient;
	for (quotient = x; quotient >= 10;)
	{
		quotient = quotient / 10;
	}
	return quotient;
}

int cipher(int x)//� ���� �ڸ����� ���ϴ� �Լ��Դϴ�. ���õ� �������� ž�� ���� �ִ� 5���� �����Ͽ��� ������ if���� ����Ͽ� ������ ���ڿ� ���� �ڸ����� �Ǵ��ϰ� �Ͽ����ϴ�. ���� ž�� ���� ������ �����ٸ� 10�� �������� ������� �������������� �Ǵ��Ͽ� �ڸ����� ���� �� �ֽ��ϴ�.
{
	int a;
	if (x / 10000 >= 1)
	{
		a = 5;
	}
	else if (x / 1000 >= 1)
	{
		a = 4;
	}
	else if (x / 100 >= 1)
	{
		a = 3;
	}
	else if (x / 10 >= 1)
	{
		a = 2;
	}
	else if (x / 1 >= 1)
	{
		a = 1;
	}
	else
	{
		a = 0;
	}
	return a;
}

void shifting(int *a, int *b)//���õ� �� ��տ� ����� ���ڰ��� ��ȯ�� �̷������ �Լ��Դϴ�. ���� �ű� ����� ���� ���� �ڸ��� ���� ���� �Ű��� ����� ���� ���� �ڸ��� �� �տ� ��ġ��Ű�� �������, head_of_number �Լ��� cipher�Լ��� ���� ����� �� �ֽ��ϴ�.
{
	if (*b == 0)
	{
		*b = head_of_number(*a);
		*a = *a - head_of_number(*a)*pow(10, cipher(*a) - 1);
	}
	else
	{
		*b = *b + head_of_number(*a)*pow(10, cipher(*b));
		*a = *a - head_of_number(*a)*pow(10, cipher(*a) - 1);
	}
}
int smallest_number(int a)//� ������ ���� �ڸ� ���� ���ϴ� �Լ���, �� ���ڸ� 10���� ���� �������� ���� ���� �� �ֽ��ϴ�.
{
	return a % 10;
}

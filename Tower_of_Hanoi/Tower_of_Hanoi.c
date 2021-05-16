#include<stdio.h>
#include<stdlib.h>//system("cls")를 사용하기 위해 stdlib.h를 포함시켰습니다.
#include<math.h>//기둥의 정보와 기둥간의 정보교환을 수학적으로 시행하기 위해 math.h를 포함시켰습니다.

char print_divider();//'='40개를 출력하여 단계를 구분하는 함수입니다.
char print_poles(int, int, int);//3개의 기둥을 '□'로 표현하는 함수입니다.
char print_one_pole(int, int);//기둥에 포함되어 있는 숫자를 '□'로 변환하여 표현하는 함수입니다.
void process(int);//몇 번째 step인지, 해당 step에서의 세 기둥의 모양은 어떠한지, 모든 시행이 끝났는지 등 모든 과정을 통틀어 시행하는 함수입니다.
int check_not_empty(int);//입력받은 순서의 기둥이 비어있는지, 즉 기둥을 나타내는 숫자가 0이 아닌지를 확인하는 함수입니다.
int check_valid_move(int, int);//블럭을 옮길 기둥과 옮겨질 기둥에 내포되어있는 숫자의 관계를 파악하여 하노이의 탑의 규칙에 어긋나는지 확인하는 함수입니다.
int check_finish(int, int, int);//모든 블럭이 첫번째 기둥으로부터 다른 기둥으로 하노이의 탑의 규칙대로 이동되었는지를 파악하여 과정을 마무리하는 함수입니다.
void shifting(int*, int*);//블럭을 옮길 기둥과 옮겨질 기둥을 입력하게 되면 각 기둥에 내포된 숫자를 통해 정보를 교환하는 함수입니다.
int head_of_number(int);//어떤 수의 가장 높은 자리수의 숫자를 반환하는 함수입니다. ex) 3647을 입력하면 3을 반환
int cipher(int);//어떤 수가 몇자리의 수인지를 반환하는 함수입니다. ex) 27254를 입력하면 5를 반환
int smallest_number(int);//어떤 수의 일의 자리 수를 반환하는 함수입니다.

int main()
{
	int floor;
	printf("하노이의 탑 층 수를 정해주세요(1층부터 5층 사이): ");
	scanf("%d", &floor);//하노이의 탑 층수를 입력 받습니다.
	for (1 ; ; )
	{
		if (floor < 1 || floor > 5)//입력된 수가 유효한 범위 내에 있지 않을 때의 조건문입니다.
		{
			printf("잘못된 입력입니다. 1부터 5 사이의 숫자를 입력해주세요: ");
			scanf("%d", &floor);//해당 조건에서 범위 내의 숫자를 입력할 것을 요구하고 입력받습니다. 이후 for 문에 의해 다시 유효한 범위 내에 있는지를 검사합니다.
		}
		
		if (floor >= 1 && floor <= 5)//입력된 수가 유효한 범위 내에 있다면, break를 통해 for 문을 빠져나갑니다.
			break;
	}
	process(floor);//입력된 층 수에 해당하는 모든 하노이의 탑 과정을 실행합니다.
}

void process(int floor)
{
	int step, from, to, number_of_pole1, number_of_pole2, number_of_pole3, number_of_from, number_of_to;//step은 단계를, from과 to는 블럭을 옮길 기둥과 옮겨질 기둥을, number_of_pole 1,2,3 은 각 기둥에 내재된 숫자를, number_of_from, to는 각각 블럭을 옮길 기둥과 옮겨질 기둥에 내재된 숫자를 지칭합니다.
	for (step = 1, number_of_pole1 = 12345 / pow(10, 5 - floor), number_of_pole2 = 0, number_of_pole3 = 0; ; step++)//가장 큰 for문으로서, step의 숫자부터 각 단계의 기둥을 표현하고, 마무리 할지를 판단합니다. step이 1일때, pole의 정보는 12345를 10의 제곱수로 나눈 몫으로 계산함으로써 적절히 표현할 수 있습니다.
	{
		print_divider();
		printf(">>>Step %d\n", step);//몇번째 step인지 for문의 순서에 따라 표시합니다.
		print_poles(number_of_pole1, number_of_pole2, number_of_pole3);//해당 단계의 기둥들에 내재된 숫자를 '□'로 표현합니다.
		print_divider();
		if (step >= 2)//블럭이 모두 옮겨졌을 경우 마무리하는 함수로서, 첫번째 단계는 제외시켜 실행하자마자 종료됨을 방지합니다.
		{
			if (check_finish(number_of_pole1, number_of_pole2, number_of_pole3))//첫번째 기둥의 블럭이 다른 기둥으로 모두 옮겨졌을 경우를 판단해 맞다면 종료하고, 틀리다면 break를 통해 전체 for문을 빠져나가고 나머지 과정을 이어서 진행합니다.
			{
				printf("블럭이 모두 다른 기둥으로 옮겨졌습니다. 퍼즐을 종료합니다.");
				break;
			}
		}
		printf("1.블럭을 옮길 기둥을 선택해주세요.<1-3>: ");
		scanf("%d", &from);//블럭을 옮길 기둥을 입력받습니다.

		for (; ;)
		{
			if (from < 1 || from > 3)//입력받은 숫자가 유효한 범위에 있는지를 판단하여, 범위를 벗어났다면 새로운 숫자를 입력하기를 요구하고 새롭게 저장한 뒤 나머지 과정을 진행하고, 새롭게 입력받은 숫자가 다시 범위를 벗어났다면 for문에 의해 다시 유효한 범위에 있는지를 판단하는 과정을 거칩니다.
			{
				printf("1.잘못된 입력입니다. 1부터 3 사이의 숫자를 입력해주세요: ");
				scanf("%d", &from);
			}

			if (from == 1)//블럭을 옮길 기둥으로 첫번째 기둥을 선택했을 때, 먼저 첫번째 기둥이 비어있는 지를 확인하고, 비어있다면 다른 숫자를 입력하기를 요구하고, 비어있지 않다면 첫번째 기둥에 내재된 숫자를 number_of_from에 저장합니다. 그 이유는 이후 shifting함수에서 number_of_to 와 비교하기 위해서 입니다.
			{
				if (check_not_empty(number_of_pole1) == 1)
				{
					number_of_from = number_of_pole1;
					break;
				}
				else
				{
					printf("1.해당 기둥이 비어있습니다. 비어있지 않은 기둥을 선택해주세요: ");
					scanf("%d", &from);
				}
				
			}

			if (from == 2)//첫번째 기둥을 선택했을 때와 같은 과정입니다.
			{
				if (check_not_empty(number_of_pole2) == 1)
				{
					number_of_from = number_of_pole2;
					break;
				}
				else
				{
					printf("1.해당 기둥이 비어있습니다. 비어있지 않은 기둥을 선택해주세요: ");
					scanf("%d", &from);
				}
			}

			if (from == 3)//첫번째 기둥을 선택했을 때와 같은 과정입니다.
			{
				if (check_not_empty(number_of_pole3) == 1)
				{
					number_of_from = number_of_pole3;
					break;
				}
				else
				{
					printf("1.해당 기둥이 비어있습니다. 비어있지 않은 기둥을 선택해주세요: ");
					scanf("%d", &from);
				}
			}
		}
		

		printf("2.블럭이 옮겨질 기둥을 선택해주세요.<1-3>: ");
		scanf("%d", &to);//블럭이 옮겨질 기둥을 입력받습니다.
		for (; ;)
		{
			if (to < 1 || to > 3)//블럭이 옮겨질 기둥으로 입력받은 숫자가 유효한 범위내에 있는지 확인하고, 벗어났다면 다시 for문을 통해 새로운 숫자를 입력받으며, 범위내에 있다면 나머지 과정을 시행합니다.
			{
				printf("2.잘못된 입력입니다. 1부터 3 사이의 숫자를 입력해주세요: ");
				scanf("%d", &to);
			}

			else if (to == 1)//블럭이 옮겨질 기둥으로 첫번째 기둥을 선택했다면, 이동과 관련된 두 기둥이 선택되었으므로 두 기둥에 내재된 숫자를 비교하여 하노이의 탑 규칙을 만족하는지 확인합니다.
			{
				if (check_valid_move(head_of_number((int)number_of_from), head_of_number((int)number_of_pole1))==1)//블럭을 옮길 기둥의 가장 윗 블럭이 블럭이 옮겨질 기둥의 가장 윗 블럭 위로 이동된다는 점을 고려하여 숫자를 비교합니다. 하노이의 탑 규칙을 만족하려면 블럭을 옮길 기둥에 내재된 숫자의 가장 높은 자리의 수가 블럭이 옮겨질 기둥에 내재된 숫자의 가장 높은 자리의 수보다 작아야 합니다.
				{
					if (number_of_from == number_of_pole1)//하노이의 탑 규칙을 만족했다면, number_of_to에 블럭이 옮겨질 기둥의 숫자를 저장합니다. 이후 number_of_from과 number_of_to에 내재된 숫자 간의 shifting이 이루어집니다. 이 과정은 shifting함수 부분에서 설명됩니다. 또한, 전체 for문에 의해 다음 단계로 넘어갔을 때의 경우를 위해 shifting의 결과를 각 기둥에 새롭게 저장합니다.
					{
						number_of_to = number_of_pole1;
						shifting(&number_of_from, &number_of_to);
						number_of_pole1 = number_of_to;
						number_of_pole1 = number_of_from;
						break;
					}
					else if (number_of_from == number_of_pole2)//첫번째 if문과 동일한 과정입니다.
					{
						number_of_to = number_of_pole1;
						shifting(&number_of_from, &number_of_to);
						number_of_pole1 = number_of_to;
						number_of_pole2 = number_of_from;
						break;
					}
					else if (number_of_from == number_of_pole3)//첫번째 if문과 동일한 과정입니다.
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
					printf("2.하노이의 탑 규칙에 어긋납니다. 다른 기둥을 선택해주세요: ");//하노이의 탑 규칙을 판단한 결과 규칙과 어긋난다면, shifting 단계로 넘어가지 않고 새로운 숫자를 입력받은 뒤 for문에 의해 같은 과정을 반복합니다.
					scanf("%d", &to);
				}
			}
			else if (to == 2)//블럭이 옮겨질 기둥으로 두번째 기둥을 선택한 것으로, 첫번째 기둥을 선택했을 경우와 동일합니다.
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
					printf("2.하노이의 탑 규칙에 어긋납니다. 다른 기둥을 선택해주세요: ");
					scanf("%d", &to);
				}
			}
			else if (to == 3)//블럭이 옮겨질 기둥으로 세번째 기둥을 선택한 것으로, 첫번째 기둥을 선택했을 경우와 동일합니다.
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
					printf("2.하노이의 탑 규칙에 어긋납니다. 다른 기둥을 선택해주세요: ");
					scanf("%d", &to);
				}
			}
		}
			system("cls");//두 기둥의 shifting이 끝나면 표시되었던 기둥들의 모양을 지웁니다.
			printf("Block Moved!\n");//block이 옮겨졌다는 표시를 해줍니다.
	}//이후 step2의 과정을 진행합니다.
}

char print_divider()//단계를 구분하는 함수로, '='를 40번 반복하는 for문을 두번 반복하는 이중포문을 사용합니다.
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

char print_poles(int number_of_pole1, int number_of_pole2, int number_of_pole3)//세 기둥의 블럭들에 내재된 숫자를 사용하여 각각 출력합니다.
{
	printf("[기둥 1]\n");
	print_one_pole(number_of_pole1, cipher(number_of_pole1));
	printf("\n");
	printf("[기둥 2]\n");
	print_one_pole(number_of_pole2, cipher(number_of_pole2));
	printf("\n");
	printf("[기둥 3]\n");
	print_one_pole(number_of_pole3, cipher(number_of_pole3));
}

char print_one_pole(int a, int b)//한 기둥의 블럭을 출력하는 함수입니다. 내재된 숫자의 자릿수 만큼 반복하는 for문 내에서, 10의 제곱수로 나눈 몫의 일의 자리수 만큼 '□'를 출력하는 for문을 실행하는 이중포문을 사용함으로써 기둥의 정보를 '□'로 표현할 수 있습니다. 내재된 숫자가 0이면 기둥이 비었다는 뜻의 'Pole is empty'를 출력합니다.
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
				printf("□");
			}
			printf("\n");
		}
	}
}


int check_not_empty(int k)//기둥에 내재된 정보가 0이면 기둥이 비었다고 판단하는 함수입니다.
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

int check_valid_move(int a, int b)//하노이의 탑 규칙에 근거하여 유효한 이동인지를 판단하는 함수입니다. 선택한 두 기둥의 가장 높은 자리의 수를 비교하여 판단합니다. 블럭이 옮겨질 기둥이 비어있다면 모든 경우의 블럭이 올 수 있기 때문에 조건부에 b!=0을 포함시켰습니다.
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
int check_finish(int a, int b, int c)//첫번째 기둥의 블럭이 다른 기둥으로 모두 옮겨졌는지를 판단하는 함수입니다. 규칙에 어긋나지 않는 이동을 통해 한 기둥으로 모든 블럭이 모였다면, 나머지 두 기둥은 비어있다는 점을 사용했습니다. 따라서 어떠한 두 기둥에 내재된 수가 모두 0이면 과정을 마무리 하도록 되어있습니다. 단, process함수에서 첫 step의 경우는 제외했습니다.
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

int head_of_number(int x)//어떤 수의 가장 높은 자리의 수를 구하는 함수로, 입력받은 수를 101보다 작아질 때까지 10으로 계속 나누어 그 몫을 반환하는 for문 형식입니다.
{
	int quotient;
	for (quotient = x; quotient >= 10;)
	{
		quotient = quotient / 10;
	}
	return quotient;
}

int cipher(int x)//어떤 수의 자릿수를 구하는 함수입니다. 제시된 문제에서 탑의 수를 최대 5개로 지정하였기 때문에 if문을 사용하여 각각의 숫자에 대해 자릿수를 판단하게 하였습니다. 만약 탑의 수에 제한이 없었다면 10의 제곱수로 몇번까지 나누어지는지를 판단하여 자릿수를 구할 수 있습니다.
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

void shifting(int *a, int *b)//선택된 두 기둥에 내재된 숫자간에 교환이 이루어지는 함수입니다. 블럭을 옮길 기둥의 가장 높은 자리의 수를 블럭이 옮겨질 기둥의 가장 높은 자리의 수 앞에 위치시키는 방식으로, head_of_number 함수와 cipher함수를 통해 계산할 수 있습니다.
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
int smallest_number(int a)//어떤 숫자의 일의 자리 수를 구하는 함수로, 그 숫자를 10으로 나눈 나머지를 통해 구할 수 있습니다.
{
	return a % 10;
}

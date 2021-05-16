#include <stdio.h>
#include <stdlib.h>//동적할당을 사용하기 위해 stdlib 헤더를 include 했습니다.
#include<string.h>//string과 관련한 기능을 사용하기 위해 string 헤더를 include 했습니다.
//운영체제 : windows, 컴파일러 : visual studio

int order_check(char, int*, int*, int*, char*, char*, int*, char**);//사용자에게 f, b, o, q 입력값을 받았을 때에 관련한 함수입니다.

int main()
{
	char *str[10], str_src_1[62], str_src_2[62];//str은 페이지 줄에 대한 배열로서, 10줄의 2차원 배열로 사용했습니다. str_src_1, str_src_2는 파일로 부터 글을 읽어들일 때 사용할 배열로서, word wrap기능을 사용하기 위해 62의 크기를 사용했습니다. 
	char file_name[31];//사용자가 다룰 파일의 이름을 저장할 배열입니다.
	char file_name_src[31];//파일의 이름을 잘못 입력했을 경우에 생길 오류를 방지하기 위해 보조적인 변수를 사용했습니다.
	char order = 0;//order는 사용자가 입력하는 f, b, o, q의 명령을 저장할 변수입니다.
	int page_num = 1, page_end = 0, char_num = 62, valid_num =1, gc_ck=1, i, j, k;//page_num은 사용자가 읽을 콘솔창 상의 페이지 수이며, page_end는 페이지에 나타나는 줄 수, char_num은 fgets를 통해 읽어올 문자 수 입니다. valid_num은 가장 끝 혹은 가장 처음 페이지일 경우를 판단하는 변수입니다. gc_ck는 scanf를 위해 미리 getchar를 실행해야 하는지를 판단하는 함수입니다. 나머지 변수는 for문 상에서 사용하는 보조적인 변수들입니다.
	printf("* Text File Viewer *\n");
	printf("file name: ");//사용자에게 읽어들일 파일의 이름을 입력하도록 요구합니다.
 	scanf("%s", file_name);//사용자로부터 파일의 이름을 스캔합니다.
	FILE* infile;
	infile = fopen(file_name, "r");//파일의 입력을 입력받으면 해당 파일을 읽기 모드로 엽니다.
	for (k=0;;k++)
	{
		if (k == 0)//k가 0인경우를 따로 분류한 이유는 다른 파일을 읽던 도중 다른 파일로 넘어가는 과정에서 생기는 오류를 방지하기 위해서입니다.
		{
			for (; fopen(file_name, "r") == NULL;)//사용자가 입력한 이름의 파일을 열 수 없을 때, 열 수 없다는 오류 문구를 출력하고, 사용자에게 Enter를 입력하도록 요구합니다.
			{
				printf("Unable to open %s\n", file_name);
				printf("Press Enter to continue...");
				getchar();
				if (getchar() == '\n')//사용자가 Enter를 입력하면, 콘솔 창을 새로고침하고 다시 파일의 이름을 입력하도록 요구합니다.
				{
					system("cls");
					printf("* Text File Viewer *\n");
					printf("file name: ");
					scanf("%s", file_name);
					infile = fopen(file_name, "r");
				}
			}
			system("cls");//파일을 열기 위한 과정이 끝나면, 콘솔 창을 새로고침합니다.
		}
		else//k가 0이 아닌 경우 즉, 다른 파일을 읽던 도중 새로운 파일을 읽고자 하는 경우에, 입력한 이름의 파일을 열 수 없다면, 오류 문구와 함께 새로운 이름을 입력받고, 사용자에게 출력되던 화면을 다시 출력하도록 합니다.
		{
			for (; fopen(file_name, "r") == NULL;)
			{
				printf("Unable to open %s\n", file_name);
				printf("Press Enter to continue...");
				getchar();
				if (getchar() == '\n')
				{
					system("cls");
					printf("* Text File Viewer *\n");
					printf("file name: ");
					scanf("%s", file_name);
				}
			}

			for (i = 0; i < 10; i++)//새로운 파일을 여는데에 성공했다면, 이전에 동적할당을 통해 제공한 str배열의 공간을 free를 통해 제거해줍니다.
			{
				free(*(str + i));
			}
		}
		for (j = 0; j < page_num; j++)//파일의 내용을 읽어 오는 부분입니다. page_num 변수를 사용한 이유는, 파일을 다시 열게 되면 이전에 읽었던 부분을 읽은 후 새로운 부분을 읽어 새로운 부분만 출력해야하기 때문에, page_num을 부여하여 어느 부분까지 읽고 출력해야하는 지를 판단하기 위함입니다.
		{
			for (i = 0; i < 10; i++)//최대 10줄을 출력할 수 있다는 점과 관련된 부분입니다.
			{
				if (fgets(str_src_1, char_num, infile) != 0)//파일을 열어 char_num - 1 만큼의 글을 읽어들입니다. char_num에는 기본적으로 62의 숫자가 저장되어 있는데, 이는 word wrap과 관련되어 있습니다. 60개의 문자만 읽어들인다면, 어느 부분을 잘라내어야 할 지 판단할 수 없습니다. 따라서 61개의 문자를 읽어들여 잘라낼 부분을 판단하도록 설계했습니다.
				{
					char_num = 62;
					if (i == 0 && j == 0)//가장 처음 글을 읽어 들일 때를 분리했습니다. 이후에 char_num을 상황에 맞게 부여하는데, 파일을 읽던 도중 다른 파일을 열게 되면 그에 영향을 받아 첫 줄에서 62개의 문자를 읽어들이지 못할 수 있기 떄문입니다.
					{
						*(str + i) = (char*)malloc(strlen(str_src_1)+1);//처음에는 str_src_1 즉 읽어온 글자 수와 NULL값을 부여할 수 있도록 동적할당을 실행합니다.
						strcpy(*(str + i), str_src_1);//읽어온 글자를 str의 첫번째 주소에 저장합니다.
						if (strrchr(str_src_1, '\n') != NULL)//만약 읽어들인 문자에 \n가 존재하면, \n까지 다음줄로 넘어가지 않도록, \n가 저장되어 있는 칸을 \0으로 바꾸어줍니다. 그리고, 다음줄로 넘기기 위해 잘라놓은 부분이 없으므로 char_num에는 다시 62의 숫자를 저장해줍니다.
						{
							*(*(str + i) + strlen(str_src_1)) = '\0';
							str_src_2[0] = '\0';
							char_num = 62;
						}
						else//\n이 존재하지 않는다면, 잘라낼 부분을 strrchr과 ' '을 통해 판단하고, 마지막 ' '이 존재했던 부분에는 \0을 저장하여 마지막에 출력할 부분을 정해줍니다. 또한, 다음에 읽어들일 문자의 수는 62 - 이번 줄에서 넘어갈 단어의 개수 + 1 개 입니다. +1이 붙은 이유는, 넘긴 단어에 ' '가 포함되어 있고, 실질적으로 공백은 삭제한 뒤 다음줄로 넘겨주기 때문입니다.
						{
							*(*(str + i) + strlen(str_src_1) - strlen(strrchr(str_src_1, ' '))) = '\0';
							strcpy(str_src_2, strrchr(str_src_1, ' '));
							char_num = char_num - strlen(strrchr(str_src_1, ' ')) + 1;
						}
					}
					else//처음 글을 읽는 경우가 아닐 때에도 대부분 비슷한 흐름을 가지고 있습니다.
					{
						if (strrchr(str_src_1, '\n') != NULL)
						{
							if (strlen(str_src_2) == 0)
							{
								*(str + i) = (char*)malloc(strlen(str_src_1)+1);//읽어들인 문자들 사이에 \n가 존재하고, 이전 줄로 부터 넘어온 단어들이 없다면, 읽어들인 문자들은 그대로 str배열에 추가합니다. \n가 위치한 곳이 멀어야 61번째 칸이기 떄문입니다. 따라서 읽어들인 문자의 수 만큼 동적할당을 실행하고, 넘겨줄 문자가 없으므로 str_src_2 배열의 첫 칸에 NULL값을 저장합니다.
								strcpy(*(str + i), str_src_1);
								*(*(str + i) + strlen(str_src_1)) = '\0';
								str_src_2[0] = '\0';
								char_num = 62;
							}
							else//읽어들인 문자들 사이에 \n가 존재하지만, 이전 줄로 부터 넘어온 단어들이 있다면, 이번에 읽어들인 문자의 수 + 이전 줄로부터 넘어온 문자들의 수 + 1 의 크기의 동적할당을 실행합니다. 마지막 부분에 \0을 넣어주기 위해 1칸을 늘려 할당합니다. 먼저 이전 과정에서 넘어온 배열의 0번째가 아닌 1번쨰 칸부터 str배열에 넣어주고, 이번에 읽어들인 문자들을 추가로 넣어줍니다. 또한 다음 과정으로 넘겨줄 부분이 없으므로 str_src_2 배열의 첫 칸에는 NULL값을, char_num에는 62를 저장합니다.
							{
								*(str + i) = (char*)malloc(strlen(str_src_1)+strlen(str_src_2) + 1);
								strcpy(*(str + i), str_src_2 + 1);
								strcat(*(str + i), str_src_1);
								*(*(str + i) + strlen(str_src_1) + strlen(str_src_2)) = '\0';
								str_src_2[0] = '\0';
								char_num = 62;
							}
						}
						else if (strlen(str_src_2) == 1)//읽어들인 문자들 사이에 \n가 존재하지 않고, 이전 과정에서 받은 문자의 개수가 1이라면, 그것은 공백이므로 붙여줄 필요가 없습니다. 따라서 이번에 읽어들인 문자의 개수 + 1 만큼 동적할당을 실행시켜 주고, 이번에 읽어들인 문자를 모두 str에 복사합니다. 복사된 줄에서 마지막 공백에 해당하는 부분에는 NULL값을 저장하고, 공백 이후의 모든 문자는 str_src_2 배열에 복사합니다. 또한, char_num 에는 62-(str_src_2)의 길이 + 1 을 저장합니다. +1은 str_src_2에서 공백에 해당하는 부분을 없앨 것이기 때문에 1개 더 읽어들여야 함을 뜻합니다.
						{

							*(str + i) = (char*)malloc(strlen(str_src_1)+1);
							strcpy(*(str + i), str_src_1);
							*(*(str + i) + strlen(str_src_1) - strlen(strrchr(str_src_1, ' '))) = '\0';
							strcpy(str_src_2, strrchr(str_src_1, ' '));
							char_num = char_num - strlen(strrchr(str_src_1, ' ')) + 1;
						}
						else
						{
							*(str + i) = (char*)malloc(strlen(str_src_2) + strlen(str_src_1)+1);
							if (strlen(str_src_2) == 0)//읽어들인 문자들 사이에 \n가 존재하지 않고, 이전 과정에서 받은 문자의 개수가 2 이상이며, str_src_2의 길이가 0이라면, str_src_1의 길이 + str_src_2의 길이(0) + 1 만큼 동적할당을 실행하고, 이번에 읽어들인 str_src_1의 문자를 복사합니다. 또한, 마지막 공백에 해당하는 부분에는 NULL값을 저장합니다.
							{
								strcpy(*(str + i), str_src_1);
								*(*(str + i) + strlen(str_src_2) + strlen(str_src_1) - strlen(strrchr(str_src_1, ' '))) = '\0';
							}
							else//읽어들인 문자들 사이에 \n가 존재하지 않고, 이전 과정에서 받은 문자의 개수가 2 이상이라면, str_src_1의 길이 + str_src_2의 길이 + 1 만큼 동적할당을 실행하고, str_src_2의 공백을 제외한 부분을 복사한 후, 이번에 읽어들인 str_src_1의 문자를 복사합니다. 또한, 마지막 공백에 해당하는 부분에는 NULL값을 저장합니다.
							{
								strcpy(*(str + i), str_src_2 + 1);
								strcat(*(str + i), str_src_1);
								*(*(str + i) + strlen(str_src_2) - 1 + strlen(str_src_1) - strlen(strrchr(str_src_1, ' '))) = '\0';
							}//추가로, 다음 과정으로 넘겨줄 문자열을 고르기 위해 마지막 공백을 포함한 그 이후의 문자들을 str_src_2에 저장합니다. 
							strcpy(str_src_2, strrchr(str_src_1, ' '));
							char_num = char_num - strlen(strrchr(str_src_1, ' ')) + 1;
						}
					}
					page_end = i + 1;//여기까지가 word wrap에 해당하는 부분이며, 해당 페이지 내에서 출력할 줄 수를 저장하기 위해 fets가 성공적일 때마다 page_end 변수에 i+1을 저장합니다. page_num++로 하지 않은 이유는, 이 for문을 여러번 돌릴 것이기 때문에 i가 초기화 되며 page_num도 같이 초기화되도록 하기 위해서 입니다.
				}
				else//10줄을 채우지 못하고 파일이 끝났을 경우, valid_num에 0을 저장합니다. 이 것은 마지막 페이지 이므로 명령 f가 유효하지 않음을 암시합니다. 또한, 마지막 줄에서 잘라낸 부분을 다시 붙여주기 위해 str_src_2에 저장된 문자열을 i-1번째의 str배열에 저장하고 for문을 중단합니다. 나머지 배열의 첫 칸에는 모두 NULL값을 저장합니다.
				{
					valid_num = 0;
					if (strlen(str_src_2) != 0)
					{
						strcat(*(str + i - 1), str_src_2);
					}
					*(*(str + i)) = '\0';
				}
			}
		}
		fclose(infile);//문장을 읽어오는것을 마쳤다면, 열었떤 파일을 다시 닫아줍니다.
		for (i = 0; i < 10; i++)//페이지의 마지막 줄 까지, 저장했던 str배열을 통해 출력하여 사용자에게 해당 페이지를 보여줍니다. 각 줄에 대해 \n가 존재하는 경우, 줄을 구분하기 위한 \n과 중복될 수 있어 \n의 존재 유무에 따라 다른 경우로 분리하여 출력하도록 했습니다.
		{
			if (strrchr(*(str + i), '\n') != 0)
			{
				printf("%s", *(str + i));
			}
			else
				printf("%s\n", *(str + i));
		}
		printf("==================================================[%d, %d]\n", 1 + 10 * (page_num - 1), 10 * (page_num - 1) + page_end);//페이지와 명령 부분을 구분하는 줄과 페이지 수, 페이지 수+줄 수 를 출력합니다. 페이지 수에는 줄 수 * 10 이 내재되어 있기 때문에, 적당한 수식을 통해 각각을 표현했습니다.
		printf("f, b, o, q> ");//사용자가 선택할 명령의 보기를 제시하고, 사용자의 명령을 성공적으로 입력받기 위해 getchar()의 유무를 판단한 뒤, 사용자에게 명령 문자를 입력받습니다.
		if (gc_ck == 0)
			gc_ck = 1;
		else
			getchar();
		scanf("%c", &order);
		for (; order != 'f' && order != 'b' && order != 'o' && order != 'q';)//사용자가 입력한 명령 문자가 f, b, o, q 중에 없다면, 콘솔 창을 새로고침하고, 사용자에게 출력되어 있던 화면을 다시 출력합니다. 이후, 사용자가 유효한 명령어를 입력할 때까지 사용자의 명령어를 스캔합니다.
		{
			system("cls");
			for (i = 0; i < 10; i++)
			{
				if (strrchr(*(str + i), '\n') != 0)
				{
					printf("%s", *(str + i));
				}
				else
					printf("%s\n", *(str + i));
			}
			if (valid_num == 0)
				printf("\n");
			printf("==================================================[%d, %d]\n", 1 + 10 * (page_num - 1), 10 * (page_num - 1) + page_end);
			printf("f, b, o, q> ");
			getchar();
			scanf("%c", &order);
			if (order != 'o')
				system("cls");
		}
		if (order_check(order, &char_num, &valid_num, &page_num, file_name, file_name_src, &gc_ck, str) == 1)//사용자의 명령에 따라 각 변수를 조정하는 함수입니다. 입력 값이 q인 경우에 한하여 1을 반환하고, 다른 입력값에 대해서는 0을 반환합니다. 따라서 q를 입력했을 경우에 한하여 프로그램을 종료합니다.
			break;
	}
	return 0;
}

int order_check(char order, int *char_num, int *valid_num, int *page_num, char *file_name, char *file_name_src, int *gc_ck, char **str)
{
	int i;
	FILE* infile;
	infile = fopen(file_name, "r");
	if (order == 'f')//사용자가 f를 입력했다면, 콘솔 창을 새로고침하고, 페이지 수를 1 더해줍니다. 마지막 페이지인 경우에는 페이지 수를 더하지 않고 유지하여 같은 화면이 출력될 수 있도록 합니다. 또한, char_num을 62로 조정하여 main함수 내에서 적당한 숫자로 전환되도록 합니다.
	{
		system("cls");
		if (*valid_num != 0)
		{
			*page_num += 1;
		}
		*char_num = 62;
		*valid_num = 1;
	}
	else if (order == 'b')//사용자가 b를 입력했다면, 콘솔창을 새로고침하고, 페이지 수를 1 빼줍니다. 페이지 수가 1보다 작아졌다면(0이 되었다면), 다시 1로 설정하여 같은 화면이 출력될 수 있도록 합니다. char_num을 62로 조정하고, 이전 화면의 마지막 페이지로 부터 넘어왔을 경우를 대비하여 valid_num을 1로 초기화합니다.
	{
		system("cls");
		*page_num -= 1;
		if (*page_num < 1)
		{
			*page_num = 1;
		}
		*char_num = 62;
		*valid_num = 1;
	}
	else if (order == 'o')//사용자가 o를 입력했다면, 새로 열 파일의 이름을 스캔하도록 문구를 출력하고, 입력을 스캔합니다. 입력한 이름이 열 수 없는 파일일 경우를 대비하여, file_name_src 에 스캔하며, 파일을 열었을 때 NULL값이 반환되지 않는다면 file_name에 복사합니다. 파일을 열 수 없다면, 열 수 없다는 문구를 제시합니다. main함수를 거쳐 다시 돌아오면 새로운 명령어를 입력받을 수 있습니다. 파일을 성공적으로 열었다면, page_num과 char_num을 각각 1과 62로 초기화 하고, 마찬가지로 마지막 페이지로 부터 넘어왔을 경우를 대비해 valid_num을 1로 저장합니다.
	{
		printf("filename: ");
		scanf("%s", file_name_src);
		if (fopen(file_name_src, "r") != NULL)
		{
			for (i = 0; *(file_name_src + i - 1) != '\0'; i++)
			{
				*(file_name + i) = *(file_name_src + i);
			}
			system("cls");
			fclose(infile);
			*page_num = 1;
			*char_num = 62;
			*valid_num = 1;
		}
		else
		{
			getchar();
			printf("Unable to open %s\n", file_name_src);
			printf("Press Enter to continue...");
			if (getchar() == '\n')
				system("cls");
			*gc_ck = 0;
		}
	}
	else if (order == 'q')//사용자가 q를 입력했다면, 할당된 공간을 free를 통해 모두 삭제하고 1을 반환합니다. 이는 프로그램을 종료한다는 뜻을 나타냅니다.
	{
		for (i = 0; i < 10; i++)
		{
			free(*(str + i));
		}
		return 1;
	}
	return 0;
}

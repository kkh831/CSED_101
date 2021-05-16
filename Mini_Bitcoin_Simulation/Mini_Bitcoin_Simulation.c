#pragma once
#include<stdio.h>
#include<string.h>//문자열에 대한 함수를 사용하기 위해 string.h.를 include했습니다.
#include"user.h"//user list에 대한 함수를 사용하기 위해 해당 내용을 담고있는 user.h를 include 했습니다.
#include"block.h"//block list에 대한 함수를 사용하기 위해 해당 내용을 담고있는 block.h를 include 했습니다.
#include"trans.h"//transaction list에 대한 함수를 사용하기 위해 해당 내용을 담고있는 trans.h를 include 했습니다.
#include<crtdbg.h>

void start_screen();//초기 화면을 출력하는 함수입니다.
void adj_order(char*);//사용자 명령에 대해 대문자와 소문자의 구별을 없애는 함수입니다.
void order_check(char*);//사용자 명령이 유효한지 판단하는 함수입니다.
void ending(LIST_USER*, LIST_BLOCK*, LIST_TRANS*);//프로그램 종료시 txt파일에 필요한 정보를 출력하는 함수입니다.

int main()
{
	LIST_USER user_list;//user 정보에 대한 리스트를 만들어 주고, 리스트 내의 head, tail, count에 대한 정보를 초기화합니다.
	user_list.count = 0;
	user_list.head = NULL;
	user_list.tail = user_list.head;

	LIST_BLOCK block_list;//block 정보에 대한 리스트를 만들어 주고, 리스트 내의 head, tail, count에 대한 정보를 초기화합니다.
	block_list.count = 0;
	block_list.head = NULL;
	block_list.tail = block_list.head;

	LIST_TRANS trans_list;//transaction 정보에 대한 리스트를 만들어 주고, 리스트 내의 head, tail, count에 대한 정보를 초기화합니다.
	trans_list.count = 0;
	trans_list.head = NULL;
	trans_list.tail = trans_list.head;


	char user_order[10], user_name[21], selected_user[21];//사용자의 명령을 저장할 변수와, 각 명령에서 사용 및 비교할 이름 문자열에 대한 변수를 만들어줍니다.
	start_screen();//초기화면을 출력합니다.

	for (;;)
	{
		printf("\n>> ");
		scanf("%s", user_order);//사용자로 부터 명령을 입력받습니다.
		adj_order(user_order);//사용자가 입력한 명령에 대해 대문자와 소문자의 구별을 없애 인식합니다.(결과는 소문자로 정렬합니다.)
		order_check(user_order);//사용자가 입력한 명령이 초기화면 상에 보이는 명령들 중 하나인지를 확인합니다. 잘못된 명령을 입력했을 경우, 새로운 명령을 입력하도록 요구합니다.
		if (strcmp(user_order, "help") == 0)//사용자가 입력한 명령이 'help' 일 경우, 초기화면을 다시 출력하여 입력할 수 있는 명령 보기를 알려줍니다.
		{
			start_screen();
		}
		else if (strcmp(user_order, "useradd") == 0)//사용자가 입력한 명령이 'useradd' 일 경우, user list에 추가할 이름 입력을 요구합니다.
		{
			printf("Enter user name >> ");
			scanf("%s", user_name);
			if (user_check(&user_list, user_name) == 1)//이미 list상에 존재하는 이름을 입력했을 경우, 이미 존재한다는 문구를 출력합니다.
			{
				printf("Already exist\n");
			}
			else if (user_check(&user_list, user_name) == 0)//list 상에 존재하지 않는 이름을 입력했을 경우, 성공적으로 등록했다는 문구를 출력하고, 추가된 user의 정보(이름, 보유 coin)을 출력합니다. 
			{
				printf("User name : %s\n", user_name);
				printf("Coin : 0\n");
				printf("USER REGISTER SUCCESS\n");
				NODE_USER *temp;
				temp = (NODE_USER*)malloc(sizeof(NODE_USER));
				insert_user(&user_list, temp, user_name, selected_user);//user에 대한 정보를 user list상에 추가합니다.(linked list 삽입)
			}
		}
		else if (strcmp(user_order, "userlist") == 0)//사용자가 입력한 명령이 'userlist' 일 경우, user list에 접근하여 등록되어 있는 모든 user의 정보를 출력합니다.
		{
			all_user(&user_list);
		}
		else if (strcmp(user_order, "getuser") == 0)//사용자가 입력한 명령이 'getuser' 일 경우, user list에 접근하여 현재 활동이 가능한 user에 대한 정보를 출력합니다.
		{
			selected_ifm(&user_list, selected_user);
		}
		else if (strcmp(user_order, "chuser") == 0)//사용자가 입력한 명령이 'chuser' 일 경우, 변경할 user의 이름을 입력하도록 하고, 입력된 이름을 바탕으로 user를 전환할 수 있는지 판단하여 결과에 따라 적절한 절차를 진행합니다.(user.c에서 자세히 설명)
		{
			printf("Enter user name >> ");
			scanf("%s", user_name);
			ch_selected(&user_list, user_name, selected_user);
		}
		else if (strcmp(user_order, "mkgenblk") == 0)//사용자가 입력한 명령이 'mkgenblk' 일 경우, 현재 등록되어 있는 활동 가능한 user의 입장에서, block list에 첫번째 block인 genesis block을 생성합니다.
		{
			NODE_BLOCK* temp1;
			temp1 = (NODE_BLOCK*)malloc(sizeof(NODE_BLOCK));

			NODE_USER* temp2 = user_list.head;

			insert_gen_block(&block_list, temp1, &user_list, temp2, selected_user);
		}
		else if (strcmp(user_order, "blklist") == 0)//사용자가 입력한 명령이 'blklist' 일 경우, block list에 접근하여 존재하는 모든 block과, 각각의 block이 포함하고 있는 transaction 정보를 출력합니다.
		{
			all_block(&block_list, &trans_list);
		}
		else if (strcmp(user_order, "mktx") == 0)//사용자가 입력한 명령이 'mktx' 일 경우, 현재 등록되어 있는 활동 가능한 user의 입장에서, transaction list에 접근하여 새로운 transaction을 생성합니다.
		{
			NODE_TRANS* temp1;
			temp1 = (NODE_TRANS*)malloc(sizeof(NODE_TRANS));
			insert_trans(&trans_list, temp1, &user_list, selected_user);
		}
		else if (strcmp(user_order, "txlist") == 0)//사용자가 입력한 명령이 'txlist' 일 경우, transaction list에 접근하여, block에 포함되지 않은 transaction에 한하여 그 정보를 모두 출력합니다.
		{
			all_trans(&trans_list);
		}
		else if (strcmp(user_order, "mkblk") == 0)//사용자가 입력한 명령이 'mkblk' 일 경우, block list에 접근하여, 새로운 block을 만들고, transaction list에 접근하여 block에 등록할 수 있는 transaction을 찾아 새로 등록한 block에 포함시킵니다.
		{
			NODE_BLOCK* temp;
			temp = (NODE_BLOCK*)malloc(sizeof(NODE_BLOCK));
			make_block(&block_list, temp, &trans_list, &user_list, selected_user);
		}
		else if (strcmp(user_order, "quit") == 0)//사용자가 입력한 명령이 'quit' 일 경우, User.txt, Transaction.txt, BlockChain.txt 파일을 열어 프로그램의 결과를 출력하고, 프로그램을 종료합니다.
		{
			ending(&user_list, &block_list, &trans_list);
			break;
		}



	}
	NODE_USER *user_end = user_list.head;//모든 프로그램을 끝내고, 각 list에 접근하여 동적할당 해주었던 메모리를 해제하기 위해 노드포인터를 사용합니다.
	for (;;)//노드포인터를 각 리스트의 헤드에 두고, 리스트가 빈 리스트가 될 때까지 헤드를 할당 해제하는 방식으로 모든 노드를 할당 해제합니다. user, transaction, block의 list에서 같은 과정을 반복합니다.
	{
		if (user_end->next != NULL)
		{
			user_list.head = user_end->next;
			free(user_end);
			user_end = user_list.head;
		}
		else
		{
			free(user_end);
			break;
		}
	}

	NODE_TRANS *trans_end = trans_list.head;
	for (;;)
	{
		if (trans_end->next != NULL)
		{
			trans_list.head = trans_end->next;
			free(trans_end);
			trans_end = trans_list.head;
		}
		else
		{
			free(trans_end);
			break;
		}
	}

	NODE_BLOCK *block_end = block_list.head;
	for (;;)
	{
		if (block_end->next != NULL)
		{
			block_list.head = block_end->next;
			free(block_end);
			block_end = block_list.head;
		}
		else
		{
			free(block_end);
			break;
		}
	}
	_CrtDumpMemoryLeaks();
	return 0;
}

void start_screen()//초기화면을 출력하는 함수입니다.
{
	printf("-----------------------------\n");
	printf(" * Mini Bitcoin Simulation *\n");
	printf("-----------------------------\n");
	printf("help: 명령어 목록 보기\n");
	printf("useradd: 사용자 등록\n");
	printf("userlist: 등록된 모든 사용자 보기\n");
	printf("getUser: 현재 사용자 확인\n");
	printf("chuser: 사용자 변경\n");
	printf("mkGenBLK: Genesis Block 생성\n");
	printf("mkTx: Transaction 생성\n");
	printf("Txlist: Transaction 목록 보기\n");
	printf("mkBLK: Block 생성\n");
	printf("blklist: BlockChain(거래내역) 확인\n");
	printf("quit: 프로그램 종료\n");
	printf("-----------------------------\n");
}

void adj_order(char *a)//사용자가 입력한 명령을 문자열에 저장한 뒤, 각 문자를 하나씩 읽어 대문자일 경우 소문자로 바꾸는 작업을 실행하는 함수입니다. 아스키 코드를 사용하여 정보를 조정하였습니다.
{
	for (; *a != '\0'; a++)
	{
		if (*a < 97)
			*a = *a + 32;
	}
}

void order_check(char *a)//사용자가 입력한 명령이 유효한 지 판단하는 함수입니다. 입력한 명령이 초기화면 상에 나타나는 명령들 중 하나가 아닐 경우, 새로운 명령을 입력받습니다. 사용자가 입력한 명령은 이미 adj_order함수를 거쳤으므로, 각 명령의 소문자 전환 상태와 비교하게 됩니다.
{
	for (; strcmp(a, "help") != 0 && strcmp(a, "useradd") != 0 && strcmp(a, "userlist") != 0 && strcmp(a, "getuser") != 0 && strcmp(a, "chuser") != 0 && strcmp(a, "mkgenblk") != 0 && strcmp(a, "mktx") != 0 && strcmp(a, "txlist") != 0 && strcmp(a, "mkblk") != 0 && strcmp(a, "blklist") != 0 && strcmp(a, "quit") != 0;)
	{
		printf("wrong command!\n\n");
		printf(">> ");
		scanf("%s", a);
		adj_order(a);
	}
}

void ending(LIST_USER *a, LIST_BLOCK *b, LIST_TRANS *c)//사용자가 quit 명령을 입력하였을 경우, user list, block list, transaction list에 접근합니다. BlockChain.txt, Transaction.txt, User.txt파일을 쓰기 형식으로 열고, 프로그램을 실행한 결과를 출력합니다.
{
	FILE* file_block;
	FILE* file_trans;
	FILE* file_user;
	file_block = fopen("BlockChain.txt", "w");
	file_trans = fopen("Transaction.txt", "w");
	file_user = fopen("User.txt", "w");

	NODE_BLOCK* ptr;

	NODE_TRANS* ptr1;

	int i = 0;
	for (ptr = b->head; ptr != NULL; ptr = ptr->next, i++)//BlockChain.txt 파일의 경우, block list에 존재하는 block들과 각 block에 포함되어 있는 transaction 정보를 출력합니다.
	{
		if (ptr->blk_inf.blk_num == 1)
		{
			fprintf(file_block, "Block\n");
			fprintf(file_block, "Sender %s\n", ptr->blk_inf.sender);
			fprintf(file_block, "Receiver %s\n", ptr->blk_inf.receiver);
			fprintf(file_block, "coin 100");
		}
		else
		{
			fprintf(file_block, "Block\n");
			fprintf(file_block, "Sender %s\n", ptr->blk_inf.sender);
			fprintf(file_block, "Receiver %s\n", ptr->blk_inf.receiver);
			fprintf(file_block, "coin 100\n");
			for (ptr1 = c->head; ptr1 != NULL && ptr1->trs_inf.trans_num != ptr->blk_inf.blk_num; ptr1 = ptr1->next);
			for (;; ptr1 = ptr1->next)
			{
				if (ptr1 == NULL)
					break;
				else if (ptr1->trs_inf.trans_num == ptr->blk_inf.blk_num)
				{
					fprintf(file_block, "Sender %s\n", ptr1->trs_inf.sender);
					fprintf(file_block, "Receiver %s\n", ptr1->trs_inf.receiver);
					fprintf(file_block, "Coin %d\n", ptr1->trs_inf.trans_coin);
				}
			}
		}
	}

	NODE_TRANS* tptr;
	fprintf(file_trans, "Transaction");
	for (i = 0, tptr = c->head; tptr != NULL; tptr = tptr->next)//Transaction.txt 파일의 경우, transactinon list에 접근하여, block에 포함되지 못한 모든 transaction의 정보를 출력합니다.
	{
		if (tptr->trs_inf.trans_num == 0)
		{
			fprintf(file_trans, "\nSender %s\n", tptr->trs_inf.sender);
			fprintf(file_trans, "Receiver %s\n", tptr->trs_inf.receiver);
			fprintf(file_trans, "coin %d", tptr->trs_inf.trans_coin);
			i++;
		}
	}


	NODE_USER* uptr;
	uptr = a->head;
	fprintf(file_user, "User");
	for (i = 1; uptr != NULL; uptr = uptr->next, i++)//User.txt 파일의 경우, user list에 접근하여, 존재하는 모든 user와 각 user가 소지하고 있는 coin 정보를 출력합니다.
	{
		fprintf(file_user, "\n%s %d", uptr->user.name, uptr->user.coin);
	}
}

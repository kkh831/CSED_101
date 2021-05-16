#pragma once
#include<stdio.h>
#include<string.h>//���ڿ��� ���� �Լ��� ����ϱ� ���� string.h.�� include�߽��ϴ�.
#include"user.h"//user list�� ���� �Լ��� ����ϱ� ���� �ش� ������ ����ִ� user.h�� include �߽��ϴ�.
#include"block.h"//block list�� ���� �Լ��� ����ϱ� ���� �ش� ������ ����ִ� block.h�� include �߽��ϴ�.
#include"trans.h"//transaction list�� ���� �Լ��� ����ϱ� ���� �ش� ������ ����ִ� trans.h�� include �߽��ϴ�.
#include<crtdbg.h>

void start_screen();//�ʱ� ȭ���� ����ϴ� �Լ��Դϴ�.
void adj_order(char*);//����� ��ɿ� ���� �빮�ڿ� �ҹ����� ������ ���ִ� �Լ��Դϴ�.
void order_check(char*);//����� ����� ��ȿ���� �Ǵ��ϴ� �Լ��Դϴ�.
void ending(LIST_USER*, LIST_BLOCK*, LIST_TRANS*);//���α׷� ����� txt���Ͽ� �ʿ��� ������ ����ϴ� �Լ��Դϴ�.

int main()
{
	LIST_USER user_list;//user ������ ���� ����Ʈ�� ����� �ְ�, ����Ʈ ���� head, tail, count�� ���� ������ �ʱ�ȭ�մϴ�.
	user_list.count = 0;
	user_list.head = NULL;
	user_list.tail = user_list.head;

	LIST_BLOCK block_list;//block ������ ���� ����Ʈ�� ����� �ְ�, ����Ʈ ���� head, tail, count�� ���� ������ �ʱ�ȭ�մϴ�.
	block_list.count = 0;
	block_list.head = NULL;
	block_list.tail = block_list.head;

	LIST_TRANS trans_list;//transaction ������ ���� ����Ʈ�� ����� �ְ�, ����Ʈ ���� head, tail, count�� ���� ������ �ʱ�ȭ�մϴ�.
	trans_list.count = 0;
	trans_list.head = NULL;
	trans_list.tail = trans_list.head;


	char user_order[10], user_name[21], selected_user[21];//������� ����� ������ ������, �� ��ɿ��� ��� �� ���� �̸� ���ڿ��� ���� ������ ������ݴϴ�.
	start_screen();//�ʱ�ȭ���� ����մϴ�.

	for (;;)
	{
		printf("\n>> ");
		scanf("%s", user_order);//����ڷ� ���� ����� �Է¹޽��ϴ�.
		adj_order(user_order);//����ڰ� �Է��� ��ɿ� ���� �빮�ڿ� �ҹ����� ������ ���� �ν��մϴ�.(����� �ҹ��ڷ� �����մϴ�.)
		order_check(user_order);//����ڰ� �Է��� ����� �ʱ�ȭ�� �� ���̴� ��ɵ� �� �ϳ������� Ȯ���մϴ�. �߸��� ����� �Է����� ���, ���ο� ����� �Է��ϵ��� �䱸�մϴ�.
		if (strcmp(user_order, "help") == 0)//����ڰ� �Է��� ����� 'help' �� ���, �ʱ�ȭ���� �ٽ� ����Ͽ� �Է��� �� �ִ� ��� ���⸦ �˷��ݴϴ�.
		{
			start_screen();
		}
		else if (strcmp(user_order, "useradd") == 0)//����ڰ� �Է��� ����� 'useradd' �� ���, user list�� �߰��� �̸� �Է��� �䱸�մϴ�.
		{
			printf("Enter user name >> ");
			scanf("%s", user_name);
			if (user_check(&user_list, user_name) == 1)//�̹� list�� �����ϴ� �̸��� �Է����� ���, �̹� �����Ѵٴ� ������ ����մϴ�.
			{
				printf("Already exist\n");
			}
			else if (user_check(&user_list, user_name) == 0)//list �� �������� �ʴ� �̸��� �Է����� ���, ���������� ����ߴٴ� ������ ����ϰ�, �߰��� user�� ����(�̸�, ���� coin)�� ����մϴ�. 
			{
				printf("User name : %s\n", user_name);
				printf("Coin : 0\n");
				printf("USER REGISTER SUCCESS\n");
				NODE_USER *temp;
				temp = (NODE_USER*)malloc(sizeof(NODE_USER));
				insert_user(&user_list, temp, user_name, selected_user);//user�� ���� ������ user list�� �߰��մϴ�.(linked list ����)
			}
		}
		else if (strcmp(user_order, "userlist") == 0)//����ڰ� �Է��� ����� 'userlist' �� ���, user list�� �����Ͽ� ��ϵǾ� �ִ� ��� user�� ������ ����մϴ�.
		{
			all_user(&user_list);
		}
		else if (strcmp(user_order, "getuser") == 0)//����ڰ� �Է��� ����� 'getuser' �� ���, user list�� �����Ͽ� ���� Ȱ���� ������ user�� ���� ������ ����մϴ�.
		{
			selected_ifm(&user_list, selected_user);
		}
		else if (strcmp(user_order, "chuser") == 0)//����ڰ� �Է��� ����� 'chuser' �� ���, ������ user�� �̸��� �Է��ϵ��� �ϰ�, �Էµ� �̸��� �������� user�� ��ȯ�� �� �ִ��� �Ǵ��Ͽ� ����� ���� ������ ������ �����մϴ�.(user.c���� �ڼ��� ����)
		{
			printf("Enter user name >> ");
			scanf("%s", user_name);
			ch_selected(&user_list, user_name, selected_user);
		}
		else if (strcmp(user_order, "mkgenblk") == 0)//����ڰ� �Է��� ����� 'mkgenblk' �� ���, ���� ��ϵǾ� �ִ� Ȱ�� ������ user�� ���忡��, block list�� ù��° block�� genesis block�� �����մϴ�.
		{
			NODE_BLOCK* temp1;
			temp1 = (NODE_BLOCK*)malloc(sizeof(NODE_BLOCK));

			NODE_USER* temp2 = user_list.head;

			insert_gen_block(&block_list, temp1, &user_list, temp2, selected_user);
		}
		else if (strcmp(user_order, "blklist") == 0)//����ڰ� �Է��� ����� 'blklist' �� ���, block list�� �����Ͽ� �����ϴ� ��� block��, ������ block�� �����ϰ� �ִ� transaction ������ ����մϴ�.
		{
			all_block(&block_list, &trans_list);
		}
		else if (strcmp(user_order, "mktx") == 0)//����ڰ� �Է��� ����� 'mktx' �� ���, ���� ��ϵǾ� �ִ� Ȱ�� ������ user�� ���忡��, transaction list�� �����Ͽ� ���ο� transaction�� �����մϴ�.
		{
			NODE_TRANS* temp1;
			temp1 = (NODE_TRANS*)malloc(sizeof(NODE_TRANS));
			insert_trans(&trans_list, temp1, &user_list, selected_user);
		}
		else if (strcmp(user_order, "txlist") == 0)//����ڰ� �Է��� ����� 'txlist' �� ���, transaction list�� �����Ͽ�, block�� ���Ե��� ���� transaction�� ���Ͽ� �� ������ ��� ����մϴ�.
		{
			all_trans(&trans_list);
		}
		else if (strcmp(user_order, "mkblk") == 0)//����ڰ� �Է��� ����� 'mkblk' �� ���, block list�� �����Ͽ�, ���ο� block�� �����, transaction list�� �����Ͽ� block�� ����� �� �ִ� transaction�� ã�� ���� ����� block�� ���Խ�ŵ�ϴ�.
		{
			NODE_BLOCK* temp;
			temp = (NODE_BLOCK*)malloc(sizeof(NODE_BLOCK));
			make_block(&block_list, temp, &trans_list, &user_list, selected_user);
		}
		else if (strcmp(user_order, "quit") == 0)//����ڰ� �Է��� ����� 'quit' �� ���, User.txt, Transaction.txt, BlockChain.txt ������ ���� ���α׷��� ����� ����ϰ�, ���α׷��� �����մϴ�.
		{
			ending(&user_list, &block_list, &trans_list);
			break;
		}



	}
	NODE_USER *user_end = user_list.head;//��� ���α׷��� ������, �� list�� �����Ͽ� �����Ҵ� ���־��� �޸𸮸� �����ϱ� ���� ��������͸� ����մϴ�.
	for (;;)//��������͸� �� ����Ʈ�� ��忡 �ΰ�, ����Ʈ�� �� ����Ʈ�� �� ������ ��带 �Ҵ� �����ϴ� ������� ��� ��带 �Ҵ� �����մϴ�. user, transaction, block�� list���� ���� ������ �ݺ��մϴ�.
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

void start_screen()//�ʱ�ȭ���� ����ϴ� �Լ��Դϴ�.
{
	printf("-----------------------------\n");
	printf(" * Mini Bitcoin Simulation *\n");
	printf("-----------------------------\n");
	printf("help: ��ɾ� ��� ����\n");
	printf("useradd: ����� ���\n");
	printf("userlist: ��ϵ� ��� ����� ����\n");
	printf("getUser: ���� ����� Ȯ��\n");
	printf("chuser: ����� ����\n");
	printf("mkGenBLK: Genesis Block ����\n");
	printf("mkTx: Transaction ����\n");
	printf("Txlist: Transaction ��� ����\n");
	printf("mkBLK: Block ����\n");
	printf("blklist: BlockChain(�ŷ�����) Ȯ��\n");
	printf("quit: ���α׷� ����\n");
	printf("-----------------------------\n");
}

void adj_order(char *a)//����ڰ� �Է��� ����� ���ڿ��� ������ ��, �� ���ڸ� �ϳ��� �о� �빮���� ��� �ҹ��ڷ� �ٲٴ� �۾��� �����ϴ� �Լ��Դϴ�. �ƽ�Ű �ڵ带 ����Ͽ� ������ �����Ͽ����ϴ�.
{
	for (; *a != '\0'; a++)
	{
		if (*a < 97)
			*a = *a + 32;
	}
}

void order_check(char *a)//����ڰ� �Է��� ����� ��ȿ�� �� �Ǵ��ϴ� �Լ��Դϴ�. �Է��� ����� �ʱ�ȭ�� �� ��Ÿ���� ��ɵ� �� �ϳ��� �ƴ� ���, ���ο� ����� �Է¹޽��ϴ�. ����ڰ� �Է��� ����� �̹� adj_order�Լ��� �������Ƿ�, �� ����� �ҹ��� ��ȯ ���¿� ���ϰ� �˴ϴ�.
{
	for (; strcmp(a, "help") != 0 && strcmp(a, "useradd") != 0 && strcmp(a, "userlist") != 0 && strcmp(a, "getuser") != 0 && strcmp(a, "chuser") != 0 && strcmp(a, "mkgenblk") != 0 && strcmp(a, "mktx") != 0 && strcmp(a, "txlist") != 0 && strcmp(a, "mkblk") != 0 && strcmp(a, "blklist") != 0 && strcmp(a, "quit") != 0;)
	{
		printf("wrong command!\n\n");
		printf(">> ");
		scanf("%s", a);
		adj_order(a);
	}
}

void ending(LIST_USER *a, LIST_BLOCK *b, LIST_TRANS *c)//����ڰ� quit ����� �Է��Ͽ��� ���, user list, block list, transaction list�� �����մϴ�. BlockChain.txt, Transaction.txt, User.txt������ ���� �������� ����, ���α׷��� ������ ����� ����մϴ�.
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
	for (ptr = b->head; ptr != NULL; ptr = ptr->next, i++)//BlockChain.txt ������ ���, block list�� �����ϴ� block��� �� block�� ���ԵǾ� �ִ� transaction ������ ����մϴ�.
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
	for (i = 0, tptr = c->head; tptr != NULL; tptr = tptr->next)//Transaction.txt ������ ���, transactinon list�� �����Ͽ�, block�� ���Ե��� ���� ��� transaction�� ������ ����մϴ�.
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
	for (i = 1; uptr != NULL; uptr = uptr->next, i++)//User.txt ������ ���, user list�� �����Ͽ�, �����ϴ� ��� user�� �� user�� �����ϰ� �ִ� coin ������ ����մϴ�.
	{
		fprintf(file_user, "\n%s %d", uptr->user.name, uptr->user.coin);
	}
}

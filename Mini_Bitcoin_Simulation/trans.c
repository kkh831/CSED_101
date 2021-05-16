#pragma once
#include"user.h"
#include"block.h"
#include"trans.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>





void insert_trans(LIST_TRANS *a, NODE_TRANS *b, LIST_USER* c, char *send)//���ο� transaction�� ����ϴ� �Լ��Դϴ�.
{
	NODE_USER* ptr;

	NODE_TRANS* pre;

	char user_name[21];
	int coin;
	printf("Receiver name: ");//�ŷ� ���� ������ �̸��� �Է��ϵ��� �մϴ�.
	scanf("%s", user_name);
	for (ptr = c->head; ptr != NULL && strcmp(ptr->user.name, user_name) != 0; ptr = ptr->next);//user list�� �����Ͽ�, �Է��� �̸��� user�� �ִ��� Ȯ���մϴ�.
	if (ptr == NULL)//user�� ���� ���, user�� ���ٴ� ������ ����մϴ�.
	{
		printf("There is no user\n");
	}
	else//user�� ������ ���,
	{
		printf("Amounts of coins to transfer: ");//�ŷ��� coin�� �Է��ϵ��� �մϴ�.
		scanf("%d", &coin);
		for (ptr = c->head; strcmp(ptr->user.name, send) != 0; ptr = ptr->next);//user list�� �������� ������ �о� �����ϰ� �ִ� coin ������ Ȯ���մϴ�.
		if (coin > ptr->user.coin)//user�� ������ coin�� transaction ���� coin���� �۴ٸ�, �ش� transaction�� ��ȿ���� �����Ƿ�, coin�� �����ϴٴ� ������ ����մϴ�.
		{
			printf("Your coin is not enough\n");
		}
		else if (a->count == 0)//transaction�� ��ȿ�� ���, transaction list�� �����Ͽ� list�� ����ٸ� ù��° ĭ��, list�� ������� �ʴٸ� ���� �ڿ� transaction�� �߰��մϴ�. transaction�� ��� ������ ��µǱ� ������ ���ʿ� ����մϴ�.
		{
			b->next = a->head;
			a->head = b;
			a->count += 1;
			a->tail = b;
			b->trs_inf.trans_coin = coin;
			strcpy(b->trs_inf.sender, send);
			strcpy(b->trs_inf.receiver, user_name);
			b->trs_inf.trans_num = 0;
			printf("TRANSACTION CREATION SUCCESS\n");
		}
		else
		{
			b->next = NULL;
			pre = a->tail;
			pre->next = b;
			a->tail = b;

			a->count += 1;
			b->trs_inf.trans_coin = coin;
			strcpy(b->trs_inf.sender, send);
			strcpy(b->trs_inf.receiver, user_name);
			b->trs_inf.trans_num = 0;
			printf("TRANSACTION CREATION SUCCESS\n");
		}
	}
}

void all_trans(LIST_TRANS *a)//block�� ���Ե��� ���� ��� transaction ������ ����ϴ� �Լ��Դϴ�.
{
	int i = 0;
	NODE_TRANS* ptr;
	if (a->count == 0)//transaction list�� �����Ͽ�, ��ϵ� transaction�� ���ٸ� transaction�� ���ٴ� ������ ����մϴ�.
	{
		printf("There is no transaction\n");
	}
	else//transaction list�� ������� �ʴٸ�, 
	{
		for (i = 0, ptr = a->head; ptr != NULL; ptr = ptr->next)
		{
			if (ptr->trs_inf.trans_num == 0)//�� transaction�� ����Ǿ� �ִ� trans_num�� Ȯ���Ͽ� block�� ���ԵǾ� �ִ��� �Ǵ��� ��, block�� ���ԵǾ� ���� �ʴٸ� �ش� transaction�� �ŷ� �۽�, ������ ������ coin������ ����մϴ�.
			{
				if (i != 0)
					printf("\n");
				printf("Sender : %s\n", ptr->trs_inf.sender);
				printf("Receiver : %s\n", ptr->trs_inf.receiver);
				printf("Transferred coin : %d\n", ptr->trs_inf.trans_coin);
				i++;
			}
		}
		if (i == 0)//��� transaction�� block�� ���ԵǾ� ����� transaction�� ���ٸ�, transaction�� ���ٴ� ������ ����մϴ�.
		{
			printf("There is no transaction\n");
		}
	}
}
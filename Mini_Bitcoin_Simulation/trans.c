#pragma once
#include"user.h"
#include"block.h"
#include"trans.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>





void insert_trans(LIST_TRANS *a, NODE_TRANS *b, LIST_USER* c, char *send)//새로운 transaction을 등록하는 함수입니다.
{
	NODE_USER* ptr;

	NODE_TRANS* pre;

	char user_name[21];
	int coin;
	printf("Receiver name: ");//거래 상의 수신자 이름을 입력하도록 합니다.
	scanf("%s", user_name);
	for (ptr = c->head; ptr != NULL && strcmp(ptr->user.name, user_name) != 0; ptr = ptr->next);//user list에 접근하여, 입력한 이름의 user가 있는지 확인합니다.
	if (ptr == NULL)//user가 없을 경우, user가 없다는 문구를 출력합니다.
	{
		printf("There is no user\n");
	}
	else//user가 존재할 경우,
	{
		printf("Amounts of coins to transfer: ");//거래할 coin을 입력하도록 합니다.
		scanf("%d", &coin);
		for (ptr = c->head; strcmp(ptr->user.name, send) != 0; ptr = ptr->next);//user list의 수신자의 정보를 읽어 보유하고 있는 coin 정보를 확인합니다.
		if (coin > ptr->user.coin)//user가 보유한 coin이 transaction 상의 coin보다 작다면, 해당 transaction은 유효하지 않으므로, coin이 부족하다는 문구를 출력합니다.
		{
			printf("Your coin is not enough\n");
		}
		else if (a->count == 0)//transaction이 유효할 경우, transaction list에 접근하여 list가 비었다면 첫번째 칸에, list가 비어있지 않다면 가장 뒤에 transaction을 추가합니다. transaction은 등록 순으로 출력되기 때문에 뒤쪽에 등록합니다.
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

void all_trans(LIST_TRANS *a)//block에 포함되지 않은 모든 transaction 정보를 출력하는 함수입니다.
{
	int i = 0;
	NODE_TRANS* ptr;
	if (a->count == 0)//transaction list에 접근하여, 등록된 transaction이 없다면 transaction이 없다는 문구를 출력합니다.
	{
		printf("There is no transaction\n");
	}
	else//transaction list가 비어있지 않다면, 
	{
		for (i = 0, ptr = a->head; ptr != NULL; ptr = ptr->next)
		{
			if (ptr->trs_inf.trans_num == 0)//각 transaction에 저장되어 있는 trans_num을 확인하여 block에 포함되어 있는지 판단한 뒤, block에 포함되어 있지 않다면 해당 transaction의 거래 송신, 수신자 정보와 coin정보를 출력합니다.
			{
				if (i != 0)
					printf("\n");
				printf("Sender : %s\n", ptr->trs_inf.sender);
				printf("Receiver : %s\n", ptr->trs_inf.receiver);
				printf("Transferred coin : %d\n", ptr->trs_inf.trans_coin);
				i++;
			}
		}
		if (i == 0)//모든 transaction이 block에 포함되어 출력할 transaction이 없다면, transaction이 없다는 문구를 출력합니다.
		{
			printf("There is no transaction\n");
		}
	}
}
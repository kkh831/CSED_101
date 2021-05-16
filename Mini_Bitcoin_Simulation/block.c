#pragma once
#include<stdio.h>
#include<string.h>
#include"user.h"
#include"block.h"
#include"trans.h"

void insert_gen_block(LIST_BLOCK *a, NODE_BLOCK *b, LIST_USER *c, NODE_USER *d, char *receive)//genesis block을 생성하는 함수입니다.
{
	if (a->count != 0)
	{
		printf("Genesis block has been already created\n");//genesis block이 이미 생성되어 있다면, block list의 count는 1을 나타낼 것입니다. count의 상태에 따라 genesis block가 이미 만들어졌는지를 판단하고, 이미 존재한다면 오류 문구를 출력합니다.
	}
	else//genesis block이 존재하지 않는다면, block list에 접근하여 첫번째 linked list에 genesis block을 삽입합니다. genesis block의 구조체에 접근하여 sender, receiver 등의 정보를 조정합니다.
	{
		b->next = a->head;
		a->head = b;
		a->count += 1;
		a->tail = b;
		strcpy(b->blk_inf.sender, "Nothing");
		strcpy(b->blk_inf.receiver, receive);
		b->blk_inf.trans_coin = 100;
		b->blk_inf.blk_num = a->count;
		for (d = c->head; strcmp(d->user.name, b->blk_inf.receiver) != 0; d = d->next);
		d->user.coin += 100;
		printf("GENESIS BLOCK CREATION SUCCESS\n");
	}
}

void all_block(LIST_BLOCK *a, LIST_TRANS *b)//block list에 접근하여 모든 block과 각 block에 포함된 transaction 정보를 출력합니다.
{
	NODE_BLOCK* ptr;
	NODE_TRANS* ptr1;

	int i;
	for (i = 0, ptr = a->head; ptr != NULL; ptr = ptr->next)//block list 상의 모든 block에 대해 과정을 처리합니다.
	{
		if (ptr->blk_inf.blk_num == 1)//genesis block의 경우, 생성 시에 생성 순서인 1을 제공받기 때문에, 이 숫자를 비교하여 genesis block을 출력할 지 일반 block을 출력할 지 판단할 수 있습니다.
		{
			if (i > 0)
				printf("\n\n");
			printf("======Genesis Block======\n");
			printf("***Special Transaction***\n");
			printf("Sender : %s\n", ptr->blk_inf.sender);
			printf("Receiver : %s\n", ptr->blk_inf.receiver);
			printf("Transferred coin : 100");
			i++;
		}
		else//일반 block을 출력할 경우,
		{
			if (ptr->blk_inf.blk_num > 1)
			{
				if (i > 0)
					printf("\n\n");
				printf("==========Block==========\n");
				printf("***Special Transaction***\n");
				printf("Sender : %s\n", ptr->blk_inf.sender);
				printf("Receiver : %s\n", ptr->blk_inf.receiver);
				printf("Transferred coin : 100\n");
				i++;
				for (ptr1 = b->head; ptr1 != NULL && ptr1->trs_inf.trans_num != ptr->blk_inf.blk_num; ptr1 = ptr1->next);//block을 생성할 시 해당 block에 포함되는 transaction에는 block의 생성 순서 번호를 입력합니다. 따라서 이 번호를 비교하여 각 block에 대해 출력할 transaction을 판단할 수 있습니다.
				for (;; ptr1 = ptr1->next)
				{
					if (ptr1 == NULL)
						break;
					else if (ptr1->trs_inf.trans_num == ptr->blk_inf.blk_num)
					{
						printf("\n***Transaction***\n");
						printf("Sender : %s\n", ptr1->trs_inf.sender);
						printf("Receiver : %s\n", ptr1->trs_inf.receiver);
						printf("Transferred coin : %d\n", ptr1->trs_inf.trans_coin);
					}
				}
			}

		}
	}
	printf("\n");
}

void make_block(LIST_BLOCK *a, NODE_BLOCK *node, LIST_TRANS *b, LIST_USER *c, char *name)//새로운 block을 생성하는 함수입니다. 
{
	int step1 = 0, step2 = 0;

	int count = 0;
	if (a->count == 0)//block list에 접근하여 아무런 block이 존재하지 않을 경우, genesis block을 먼저 생성하라는 문구를 출력합니다.
	{
		printf("Create genesis block first\n");
	}
	else//genesis block이 존재할 경우, 
	{
		int i = 0;
		int count = 0;
		NODE_TRANS* ptr1;

		NODE_USER* ptr3;
		NODE_USER* ptr4;
		NODE_USER* ptr5;
		NODE_USER* ptr6;

		a->count += 1;
		node->next = a->head;
		a->head = node;
		strcpy(node->blk_inf.sender, "Nothing");
		strcpy(node->blk_inf.receiver, name);
		ptr1 = b->head;//새로 만들 block을 block list의 첫번째 칸에 삽입합니다. 사용자가 모든 block을 출력하고자 할때 최근에 등록된 block부터 출력하기 위해 첫번째 칸에 삽입합니다.
		for (;;)
		{

			for (; ptr1 != NULL && ptr1->trs_inf.trans_num != 0; ptr1 = ptr1->next);//block에 포함시킬 transaction을 찾기 위해, transaction의 trans_num을 비교하여 block에 포함되어 있지 않은 transaction을 검색합니다.
			if (ptr1 == NULL)//처리할 transaction이 없다면 NULL 포인터가 반환될 것이므로 이 경우 포함시킬 transaction이 없다는 문구를 출력합니다.
			{
				node->blk_inf.blk_num = -1;
				printf("There is not enough transaction\n");
				break;
			}
			for (ptr3 = c->head; strcmp(ptr3->user.name, ptr1->trs_inf.sender) != 0; ptr3 = ptr3->next);//처리할 transaction의 sender 이름을 파악하여, user list에 접근해 해당 user를 검색합니다.
			if (ptr3->user.coin >= ptr1->trs_inf.trans_coin)//user가 소지한 coin이 transaction에 등록된 거래될 coin보다 클 경우, 해당 transaction은 유효하다고 판단하여 새로 생성한 block에 포함시킵니다. 유효하지 않을 경우, 다음 transaction에 접근하여 같은 과정을 반복합니다.
			{
				ptr1->trs_inf.trans_num = a->count;
				ptr3->user.coin -= (ptr1->trs_inf.trans_coin);
				for (ptr4 = c->head; strcmp(ptr4->user.name, ptr1->trs_inf.receiver) != 0; ptr4 = ptr4->next);
				ptr4->user.coin += (ptr1->trs_inf.trans_coin);
				step1 = 1;//block에 새로운 transaction을 포함시키는 데에 성공했다면, 다음 step으로 넘어갈 수 있는 조건을 만들어줍니다.
				for (ptr4 = c->head; strcmp(ptr4->user.name, name) != 0; ptr4 = ptr4->next);
				ptr4->user.coin += 100;
				node->blk_inf.blk_num = a->count;
				break;
			}
		}

		if (step1)//block에 첫번째 transaction이 추가되었다면, 
		{
			for (;;)
			{
				for (; ptr1 != NULL && (ptr1->trs_inf.trans_num != 0 || strcmp(ptr1->trs_inf.sender, ptr3->user.name) == 0); ptr1 = ptr1->next);//위의 과정과 같이, block에 포함되지 않은 transaction을 탐색합니다.
				if (ptr1 == NULL)
					break;
				for (ptr4 = c->head; strcmp(ptr4->user.name, ptr1->trs_inf.sender) != 0; ptr4 = ptr4->next);//탐색한 transaction의 정보를 읽어 비교할 user를 찾고, 유효한 transaction인지 판단합니다. 유효하지 않을 경우, 다음 transaction에 접근하여 같은 과정을 반복합니다.
				if (ptr4->user.coin >= ptr1->trs_inf.trans_coin)
				{
					ptr1->trs_inf.trans_num = a->count;
					ptr4->user.coin -= ptr1->trs_inf.trans_coin;
					for (ptr5 = c->head; strcmp(ptr5->user.name, ptr1->trs_inf.receiver) != 0; ptr5 = ptr5->next);
					ptr5->user.coin += (ptr1->trs_inf.trans_coin);
					step2 = 1;//transaction이 유효할 경우 다음 step으로 넘어갈 수 있는 조건을 만들어줍니다.
					break;
				}
			}
		}
		if (step2)//block에 두번째 transaction이 추가되었을 경우에도 위의 과정과 같은 과정을 실행합니다. 단 한 block에는 최대 3개의 transaction이 포함될 수 있다는 점을 감안하여 이 step이 마지막 step이 되도록 설계했습니다.
		{
			for (;;)
			{
				for (; ptr1 != NULL && (ptr1->trs_inf.trans_num != 0 || strcmp(ptr1->trs_inf.sender, ptr3->user.name) == 0 || strcmp(ptr1->trs_inf.sender, ptr4->user.name) == 0); ptr1 = ptr1->next);
				if (ptr1 == NULL)
					break;
				for (ptr5 = c->head; strcmp(ptr5->user.name, ptr1->trs_inf.sender) != 0; ptr5 = ptr5->next);
				if (ptr5->user.coin >= ptr1->trs_inf.trans_coin)
				{
					ptr1->trs_inf.trans_num = a->count;
					ptr5->user.coin -= ptr1->trs_inf.trans_coin;
					for (ptr6 = c->head; strcmp(ptr6->user.name, ptr1->trs_inf.receiver) != 0; ptr6 = ptr6->next);
					ptr6->user.coin += (ptr1->trs_inf.trans_coin);
					break;
				}
			}
		}
		if (step1)//block에 최소한 하나의 transaction이 포함되었을 경우 block을 생성했다는 문구를 출력합니다.
			printf("BLOCK CREATION SUCCESS\n");
	}
}
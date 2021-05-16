#pragma once
#include<stdio.h>
#include<string.h>
#include"user.h"
#include"block.h"
#include"trans.h"

void insert_gen_block(LIST_BLOCK *a, NODE_BLOCK *b, LIST_USER *c, NODE_USER *d, char *receive)//genesis block�� �����ϴ� �Լ��Դϴ�.
{
	if (a->count != 0)
	{
		printf("Genesis block has been already created\n");//genesis block�� �̹� �����Ǿ� �ִٸ�, block list�� count�� 1�� ��Ÿ�� ���Դϴ�. count�� ���¿� ���� genesis block�� �̹� ������������� �Ǵ��ϰ�, �̹� �����Ѵٸ� ���� ������ ����մϴ�.
	}
	else//genesis block�� �������� �ʴ´ٸ�, block list�� �����Ͽ� ù��° linked list�� genesis block�� �����մϴ�. genesis block�� ����ü�� �����Ͽ� sender, receiver ���� ������ �����մϴ�.
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

void all_block(LIST_BLOCK *a, LIST_TRANS *b)//block list�� �����Ͽ� ��� block�� �� block�� ���Ե� transaction ������ ����մϴ�.
{
	NODE_BLOCK* ptr;
	NODE_TRANS* ptr1;

	int i;
	for (i = 0, ptr = a->head; ptr != NULL; ptr = ptr->next)//block list ���� ��� block�� ���� ������ ó���մϴ�.
	{
		if (ptr->blk_inf.blk_num == 1)//genesis block�� ���, ���� �ÿ� ���� ������ 1�� �����ޱ� ������, �� ���ڸ� ���Ͽ� genesis block�� ����� �� �Ϲ� block�� ����� �� �Ǵ��� �� �ֽ��ϴ�.
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
		else//�Ϲ� block�� ����� ���,
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
				for (ptr1 = b->head; ptr1 != NULL && ptr1->trs_inf.trans_num != ptr->blk_inf.blk_num; ptr1 = ptr1->next);//block�� ������ �� �ش� block�� ���ԵǴ� transaction���� block�� ���� ���� ��ȣ�� �Է��մϴ�. ���� �� ��ȣ�� ���Ͽ� �� block�� ���� ����� transaction�� �Ǵ��� �� �ֽ��ϴ�.
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

void make_block(LIST_BLOCK *a, NODE_BLOCK *node, LIST_TRANS *b, LIST_USER *c, char *name)//���ο� block�� �����ϴ� �Լ��Դϴ�. 
{
	int step1 = 0, step2 = 0;

	int count = 0;
	if (a->count == 0)//block list�� �����Ͽ� �ƹ��� block�� �������� ���� ���, genesis block�� ���� �����϶�� ������ ����մϴ�.
	{
		printf("Create genesis block first\n");
	}
	else//genesis block�� ������ ���, 
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
		ptr1 = b->head;//���� ���� block�� block list�� ù��° ĭ�� �����մϴ�. ����ڰ� ��� block�� ����ϰ��� �Ҷ� �ֱٿ� ��ϵ� block���� ����ϱ� ���� ù��° ĭ�� �����մϴ�.
		for (;;)
		{

			for (; ptr1 != NULL && ptr1->trs_inf.trans_num != 0; ptr1 = ptr1->next);//block�� ���Խ�ų transaction�� ã�� ����, transaction�� trans_num�� ���Ͽ� block�� ���ԵǾ� ���� ���� transaction�� �˻��մϴ�.
			if (ptr1 == NULL)//ó���� transaction�� ���ٸ� NULL �����Ͱ� ��ȯ�� ���̹Ƿ� �� ��� ���Խ�ų transaction�� ���ٴ� ������ ����մϴ�.
			{
				node->blk_inf.blk_num = -1;
				printf("There is not enough transaction\n");
				break;
			}
			for (ptr3 = c->head; strcmp(ptr3->user.name, ptr1->trs_inf.sender) != 0; ptr3 = ptr3->next);//ó���� transaction�� sender �̸��� �ľ��Ͽ�, user list�� ������ �ش� user�� �˻��մϴ�.
			if (ptr3->user.coin >= ptr1->trs_inf.trans_coin)//user�� ������ coin�� transaction�� ��ϵ� �ŷ��� coin���� Ŭ ���, �ش� transaction�� ��ȿ�ϴٰ� �Ǵ��Ͽ� ���� ������ block�� ���Խ�ŵ�ϴ�. ��ȿ���� ���� ���, ���� transaction�� �����Ͽ� ���� ������ �ݺ��մϴ�.
			{
				ptr1->trs_inf.trans_num = a->count;
				ptr3->user.coin -= (ptr1->trs_inf.trans_coin);
				for (ptr4 = c->head; strcmp(ptr4->user.name, ptr1->trs_inf.receiver) != 0; ptr4 = ptr4->next);
				ptr4->user.coin += (ptr1->trs_inf.trans_coin);
				step1 = 1;//block�� ���ο� transaction�� ���Խ�Ű�� ���� �����ߴٸ�, ���� step���� �Ѿ �� �ִ� ������ ������ݴϴ�.
				for (ptr4 = c->head; strcmp(ptr4->user.name, name) != 0; ptr4 = ptr4->next);
				ptr4->user.coin += 100;
				node->blk_inf.blk_num = a->count;
				break;
			}
		}

		if (step1)//block�� ù��° transaction�� �߰��Ǿ��ٸ�, 
		{
			for (;;)
			{
				for (; ptr1 != NULL && (ptr1->trs_inf.trans_num != 0 || strcmp(ptr1->trs_inf.sender, ptr3->user.name) == 0); ptr1 = ptr1->next);//���� ������ ����, block�� ���Ե��� ���� transaction�� Ž���մϴ�.
				if (ptr1 == NULL)
					break;
				for (ptr4 = c->head; strcmp(ptr4->user.name, ptr1->trs_inf.sender) != 0; ptr4 = ptr4->next);//Ž���� transaction�� ������ �о� ���� user�� ã��, ��ȿ�� transaction���� �Ǵ��մϴ�. ��ȿ���� ���� ���, ���� transaction�� �����Ͽ� ���� ������ �ݺ��մϴ�.
				if (ptr4->user.coin >= ptr1->trs_inf.trans_coin)
				{
					ptr1->trs_inf.trans_num = a->count;
					ptr4->user.coin -= ptr1->trs_inf.trans_coin;
					for (ptr5 = c->head; strcmp(ptr5->user.name, ptr1->trs_inf.receiver) != 0; ptr5 = ptr5->next);
					ptr5->user.coin += (ptr1->trs_inf.trans_coin);
					step2 = 1;//transaction�� ��ȿ�� ��� ���� step���� �Ѿ �� �ִ� ������ ������ݴϴ�.
					break;
				}
			}
		}
		if (step2)//block�� �ι�° transaction�� �߰��Ǿ��� ��쿡�� ���� ������ ���� ������ �����մϴ�. �� �� block���� �ִ� 3���� transaction�� ���Ե� �� �ִٴ� ���� �����Ͽ� �� step�� ������ step�� �ǵ��� �����߽��ϴ�.
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
		if (step1)//block�� �ּ��� �ϳ��� transaction�� ���ԵǾ��� ��� block�� �����ߴٴ� ������ ����մϴ�.
			printf("BLOCK CREATION SUCCESS\n");
	}
}
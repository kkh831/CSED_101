#pragma once
#include<stdio.h>
#include"trans.h"
#include"user.h"

typedef struct//������ block�� ������ ������ ����ü�� �����մϴ�. block ������ ������ �۽��ڿ� ������, coin(special transaction), block�� ���� ���� ������ ���ԵǾ� �ֽ��ϴ�.
{
	char sender[21];
	char receiver[21];
	int trans_coin;
	int blk_num;
} block_inf;

typedef struct node2//block list�� ����Դϴ�.
{
	block_inf blk_inf;
	struct node2 *next;
}NODE_BLOCK;

typedef struct//block list�Դϴ�.
{
	int count;
	NODE_BLOCK *head;
	NODE_BLOCK *tail;
}LIST_BLOCK;

void insert_gen_block(LIST_BLOCK*, NODE_BLOCK*, LIST_USER*, NODE_USER*, char*);//c���Ͽ��� ����.

void all_block(LIST_BLOCK*, LIST_TRANS*);//c���Ͽ��� ����.

void make_block(LIST_BLOCK*, NODE_BLOCK*, LIST_TRANS*, LIST_USER*, char*);//c���Ͽ��� ����.
#pragma once
#include<stdio.h>
#include"user.h"
#include"block.h"

typedef struct//������ transaction�� ������ ������ ����ü�� �����մϴ�. �ŷ��� �۽�, �����ڿ� �ŷ� coin ����, transaction�� ��� block�� ���ԵǾ������� �ǹ��ϸ� trans_num�� ���ԵǾ� �ֽ��ϴ�.
{
	char sender[21];
	char receiver[21];
	int trans_coin;
	int trans_num;
} trans_inf;

typedef struct node3//transaction list�� ����Դϴ�.
{
	trans_inf trs_inf;
	struct node3 *next;
}NODE_TRANS;

typedef struct//transaction list �Դϴ�. 
{
	int count;
	NODE_TRANS *head;
	NODE_TRANS *tail;
}LIST_TRANS;

void insert_trans(LIST_TRANS*, NODE_TRANS*, LIST_USER*, char*);//c���Ͽ��� ����.
void all_trans(LIST_TRANS*);//c���Ͽ��� ����.
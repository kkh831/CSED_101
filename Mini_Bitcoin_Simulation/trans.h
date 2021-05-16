#pragma once
#include<stdio.h>
#include"user.h"
#include"block.h"

typedef struct//각각의 transaction에 포함할 정보를 구조체로 선언합니다. 거래의 송신, 수신자와 거래 coin 정보, transaction이 어느 block에 포함되었는지를 의미하를 trans_num이 포함되어 있습니다.
{
	char sender[21];
	char receiver[21];
	int trans_coin;
	int trans_num;
} trans_inf;

typedef struct node3//transaction list의 노드입니다.
{
	trans_inf trs_inf;
	struct node3 *next;
}NODE_TRANS;

typedef struct//transaction list 입니다. 
{
	int count;
	NODE_TRANS *head;
	NODE_TRANS *tail;
}LIST_TRANS;

void insert_trans(LIST_TRANS*, NODE_TRANS*, LIST_USER*, char*);//c파일에서 설명.
void all_trans(LIST_TRANS*);//c파일에서 설명.
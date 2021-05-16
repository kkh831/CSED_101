#pragma once
#include<stdio.h>
#include"trans.h"
#include"user.h"

typedef struct//각각의 block에 포함할 정보를 구조체로 선언합니다. block 생성에 관여한 송신자와 수신자, coin(special transaction), block의 생성 순서 정보가 포함되어 있습니다.
{
	char sender[21];
	char receiver[21];
	int trans_coin;
	int blk_num;
} block_inf;

typedef struct node2//block list의 노드입니다.
{
	block_inf blk_inf;
	struct node2 *next;
}NODE_BLOCK;

typedef struct//block list입니다.
{
	int count;
	NODE_BLOCK *head;
	NODE_BLOCK *tail;
}LIST_BLOCK;

void insert_gen_block(LIST_BLOCK*, NODE_BLOCK*, LIST_USER*, NODE_USER*, char*);//c파일에서 설명.

void all_block(LIST_BLOCK*, LIST_TRANS*);//c파일에서 설명.

void make_block(LIST_BLOCK*, NODE_BLOCK*, LIST_TRANS*, LIST_USER*, char*);//c파일에서 설명.
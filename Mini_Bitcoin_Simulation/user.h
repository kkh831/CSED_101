#pragma once
#include<stdio.h>

typedef struct//각각의 user에 포함할 정보를 구조체로 선언합니다. user의 이름, user가 현재 보유하고 있는 coin 정보가 포함되어 있습니다.
{
	char name[21];
	int coin;
} inform;

typedef struct node1//user list의 노드입니다.
{
	inform user;
	struct node1 *next;
}NODE_USER;

typedef struct//user list 입니다.
{
	int count;
	NODE_USER *head;
	NODE_USER *tail;
}LIST_USER;

void insert_user(LIST_USER*, NODE_USER*, char*, char*);//c파일에서 설명.

int user_check(LIST_USER*, char*);//c파일에서 설명.

void all_user(LIST_USER*);//c파일에서 설명.

void selected_ifm(LIST_USER*, char*);//c파일에서 설명.

void ch_selected(LIST_USER*, char*, char*);//c파일에서 설명.
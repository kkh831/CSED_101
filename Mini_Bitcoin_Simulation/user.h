#pragma once
#include<stdio.h>

typedef struct//������ user�� ������ ������ ����ü�� �����մϴ�. user�� �̸�, user�� ���� �����ϰ� �ִ� coin ������ ���ԵǾ� �ֽ��ϴ�.
{
	char name[21];
	int coin;
} inform;

typedef struct node1//user list�� ����Դϴ�.
{
	inform user;
	struct node1 *next;
}NODE_USER;

typedef struct//user list �Դϴ�.
{
	int count;
	NODE_USER *head;
	NODE_USER *tail;
}LIST_USER;

void insert_user(LIST_USER*, NODE_USER*, char*, char*);//c���Ͽ��� ����.

int user_check(LIST_USER*, char*);//c���Ͽ��� ����.

void all_user(LIST_USER*);//c���Ͽ��� ����.

void selected_ifm(LIST_USER*, char*);//c���Ͽ��� ����.

void ch_selected(LIST_USER*, char*, char*);//c���Ͽ��� ����.
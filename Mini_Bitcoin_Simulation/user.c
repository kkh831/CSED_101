#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"user.h"



void insert_user(LIST_USER *a, NODE_USER *b, char *name, char *selected)//���ο� user�� ����ϴ� �Լ��Դϴ�.
{
	if ((a->count) == 0)//user list�� �����Ͽ�, �ƹ��� user�� ��ϵǾ� ���� ���� ���, ù��° ĭ�� ���ο� user�� ����մϴ�.
	{
		b->next = a->head;
		a->head = b;
		a->count += 1;
		a->tail = b;
		b->user.coin = 0;
		strcpy(b->user.name, name);
		strcpy(selected, name);
	}
	else//user list�� �̹� user�� ������ ���, list�� ���� �ڿ� ���ο� user�� ����մϴ�.
	{
		NODE_USER *pre;

		b->next = NULL;
		pre = a->tail;
		pre->next = b;
		a->tail = b;
		a->count += 1;
		b->user.coin = 0;
		strcpy(b->user.name, name);
	}
}

int user_check(LIST_USER *a, char *b)//user�� ����ϴ� ��������, �Է��� �̸��� user�� user list�� �����ϴ��� Ȯ���ϴ� �Լ��Դϴ�.
{
	int result = 0;
	NODE_USER* ptr;
	ptr = a->head;
	if (a->count == 0)//user list�� ����ִٸ� ��ġ�� �ʴ´ٰ� �Ǵ��Ͽ� 0�� ��ȯ�մϴ�.
	{
		return 0;
	}
	else
	{
		for (; ptr != NULL; ptr = ptr->next)
		{
			if (strcmp(ptr->user.name, b) == 0)//�̸��� ��ĥ ��찡 �ִٸ�, ����� �� ���ٴ� ���� 1�� ��ȯ�մϴ�. �̸��� ��ġ�� ��찡 ���ٸ�, �ʱ�ȭ �ߴ� ���� 0�� ��ȯ�˴ϴ�.
			{
				result = 1;
				break;
			}
		}
		return result;
	}
}

void all_user(LIST_USER *a)//��� user�� �� user�� ������ ����ϴ� �Լ��Դϴ�.
{
	int i;
	NODE_USER* ptr;
	ptr = a->head;
	if (a->count == 0)//user list�� ������� ���, user�� ���ٴ� ������ ����մϴ�.
	{
		printf("There is no current user\n");
	}
	else//user list�� user�� ������ ���, 
	{
		for (i = 1; ptr != NULL; ptr = ptr->next, i++)//�� user�� ���Ͽ� �̸��� ������ coin ������ ����մϴ�.
		{
			printf("%d. Name : %s\n", i, ptr->user.name);
			printf("   Coin : %d\n", ptr->user.coin);
		}
	}
}

void selected_ifm(LIST_USER *a, char *b)//Ư�� user�� ���� ������ ����ϴ� �Լ��Դϴ�.
{
	NODE_USER* ptr;
	if (a->count == 0)//user list�� ����� ���, user�� ���ٴ� ������ ����մϴ�.
	{
		printf("There is no current user\n");
	}
	else//user list�� user�� ������ ���, �Է��� �̸��� user�� �ִ����� Ȯ���Ͽ�, user�� �ִٸ� �� ������ ����մϴ�.
	{
		for (ptr = a->head; strcmp(ptr->user.name, b) != 0; ptr = ptr->next);
		printf("Current user name : %s\n", ptr->user.name);
		printf("Amounts of coin : %d\n", ptr->user.coin);
	}
}

void ch_selected(LIST_USER *a, char *name, char *ch_name)//Ȱ���� �ڰ��� �־����� user�� �Ѹ��Դϴ�. Ȱ���� �ڰ��� �־��� user�� �����ϴ� �Լ��Դϴ�.
{
	NODE_USER* ptr;
	for (ptr = a->head; ptr != NULL && strcmp(ptr->user.name, name) != 0; ptr = ptr->next);
	if (ptr == NULL)//user list�� �����Ͽ�, �Է��� �̸��� ���Ͽ� ����Ű�� user�� ���� ���, user�� ���ٴ� ������ ����մϴ�.
	{
		printf("There is no user\n");
	}
	else//�Է��� �̸��� user�� Ž���ϴ� ���� �������� ���, �ش� user���� Ȱ�� �ڰ��� �ο��ϰ�, ������ ������ ����մϴ�.
	{
		strcpy(ch_name, name);
		printf("USER CHANGE SUCCESS\n");
	}
}
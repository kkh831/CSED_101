#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"user.h"



void insert_user(LIST_USER *a, NODE_USER *b, char *name, char *selected)//새로운 user를 등록하는 함수입니다.
{
	if ((a->count) == 0)//user list에 접근하여, 아무런 user가 등록되어 있지 않을 경우, 첫번째 칸에 새로운 user를 등록합니다.
	{
		b->next = a->head;
		a->head = b;
		a->count += 1;
		a->tail = b;
		b->user.coin = 0;
		strcpy(b->user.name, name);
		strcpy(selected, name);
	}
	else//user list상에 이미 user가 존재할 경우, list의 제일 뒤에 새로운 user를 등록합니다.
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

int user_check(LIST_USER *a, char *b)//user를 등록하는 과정에서, 입력한 이름의 user가 user list상에 존재하는지 확인하는 함수입니다.
{
	int result = 0;
	NODE_USER* ptr;
	ptr = a->head;
	if (a->count == 0)//user list가 비어있다면 겹치지 않는다고 판단하여 0을 반환합니다.
	{
		return 0;
	}
	else
	{
		for (; ptr != NULL; ptr = ptr->next)
		{
			if (strcmp(ptr->user.name, b) == 0)//이름이 겹칠 경우가 있다면, 등록할 수 없다는 뜻의 1을 반환합니다. 이름이 겹치는 경우가 없다면, 초기화 했던 값인 0이 반환됩니다.
			{
				result = 1;
				break;
			}
		}
		return result;
	}
}

void all_user(LIST_USER *a)//모든 user와 각 user의 정보를 출력하는 함수입니다.
{
	int i;
	NODE_USER* ptr;
	ptr = a->head;
	if (a->count == 0)//user list가 비어있을 경우, user가 없다는 문구를 출력합니다.
	{
		printf("There is no current user\n");
	}
	else//user list에 user가 존재할 경우, 
	{
		for (i = 1; ptr != NULL; ptr = ptr->next, i++)//각 user에 대하여 이름과 보유한 coin 정보를 출력합니다.
		{
			printf("%d. Name : %s\n", i, ptr->user.name);
			printf("   Coin : %d\n", ptr->user.coin);
		}
	}
}

void selected_ifm(LIST_USER *a, char *b)//특정 user에 대한 정보를 출력하는 함수입니다.
{
	NODE_USER* ptr;
	if (a->count == 0)//user list가 비었을 경우, user가 없다는 문구를 출력합니다.
	{
		printf("There is no current user\n");
	}
	else//user list에 user가 존재할 경우, 입력한 이름의 user가 있는지를 확인하여, user가 있다면 그 정보를 출력합니다.
	{
		for (ptr = a->head; strcmp(ptr->user.name, b) != 0; ptr = ptr->next);
		printf("Current user name : %s\n", ptr->user.name);
		printf("Amounts of coin : %d\n", ptr->user.coin);
	}
}

void ch_selected(LIST_USER *a, char *name, char *ch_name)//활동할 자격이 주어지는 user는 한명입니다. 활동할 자격이 주어질 user를 변경하는 함수입니다.
{
	NODE_USER* ptr;
	for (ptr = a->head; ptr != NULL && strcmp(ptr->user.name, name) != 0; ptr = ptr->next);
	if (ptr == NULL)//user list에 접근하여, 입력한 이름과 비교하여 가리키는 user가 없을 경우, user가 없다는 문구를 출력합니다.
	{
		printf("There is no user\n");
	}
	else//입력한 이름의 user를 탐색하는 데에 성공했을 경우, 해당 user에게 활동 자격을 부여하고, 적절한 문구를 출력합니다.
	{
		strcpy(ch_name, name);
		printf("USER CHANGE SUCCESS\n");
	}
}
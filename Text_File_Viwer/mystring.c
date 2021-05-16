#include <stddef.h>

int mystrlen(char *str)
{
	int result, i;
	for (result = 0, i = 0;; i++)
	{
		if (str[i] == '\0')
		{
			break;
		}
		result += 1;
	}
	return result;
}

char *mystrcpy(char *toStr, char *fromStr)
{
	char *a;
	for (a = toStr;; toStr++, fromStr++)
	{
		*toStr = *fromStr;
		if (*fromStr == '\0')
			break;
	}
	return a;
}

int mystrcmp(char *str1, char *str2)
{
	int result;
	for (result = 0;; str1++, str2++)
	{
		if (*str1 < *str2)
		{
			result = -1;
			break;
		}
		else if (*str1 == '\0' && *str2 == '\0')
		{
			break;
		}
		else if (*str1 > *str2)
		{
			result = 1;
			break;
		}
	}
	return result;
}

char *mystrcat(char *dest, char *src)
{
	char *a;
	for (a = dest; *dest != '\0'; dest++);
	for (; *dest = *src; dest++, src++);
	return a;
}

char *mystrrchr(char *str, char c)
{
	int i, j;
	for (i = 0, j = 0; *str != '\0'; str++, i++)
	{
		if (*str == c)
			j = i;
	}
	return str - i + j;
}

#include <stdio.h>
#include <string.h>
#include "func.h"

int main()
{
	char text[102];
	int cap=0, low=0, i=0;
	
	//ввод текста
	scanf("%s", text);
	text[strlen(text)-1]='\0';
	printf("Исходный текст: %s\n", text);
	text[strlen(text)]='.';
	
	//подсчёт заглавных и строчных букв
	for (i=0; text[i]!='.'; ++i)
	{
		if (text[i]>='a'&&text[i]<='z')
			low++;
		else if (text[i]>='A'&&text[i]<='Z')
			cap++;
	}
	
	//Использование правил изменения текста
	if (low==cap)
	{
		printf("Using Rule_1\n");
		rule1(text);
	}
	else
	{
		printf("Using Rule_2\n");
		rule2(text);
	}
	text[strlen(text)-1]='\0';
	
	//вывод преобразованного текста
	printf("Итоговый текст: %s\n", text);
	return 0;
}

#include<stdio.h>
#include<string.h>
int main()
{
	char str1[100], str2[100], str3[100], temp[100];
	gets_s(str1, 100);
	gets_s(str2, 100);
	gets_s(str3, 100);
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int len3 = strlen(str3);
	for (int i = 0; str1[i] != 0; i++)
	{
		strncpy_s(temp,str1+i,len2);
		if (strcmp(temp, str2) == 0)
		{
			strcpy_s(temp, strlen(str1) - i - len2+2, str1 + i + len2);
			strcpy_s(str1 + i, len3 + 1, str3);
			strcpy_s(str1 + i + len3, strlen(temp)+1, temp);
		}
	}
	printf("%s", str1);
}


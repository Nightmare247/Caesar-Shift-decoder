#include <ctype.h>
#include <stdio.h>

void encode(char str[], int key)
{
	key = key % 26;
	int c = 0;

	while (str[c] != '\0')
	{
		str[c] = tolower(str[c]);
		if (isalpha(str[c]))
		{
			str[c] = (str[c] - 97 + key) % 26 + 97;
		}
		c++;
	}
}

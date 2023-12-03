#include <iostream>
#include <string.h>

void insert(char[], const int, char[], const int, int);
int find_len(char[], const int);

int main()
{
	setlocale(LC_ALL, "");

	const int TEXT_SIZE = 100;
	char text[TEXT_SIZE] = "привет, как дела Артем, ";
	const int SUBTEXT_SIZE = 11;
	char subtext[SUBTEXT_SIZE] = { 'н', 'а', 'п', 'р', 'и', 'м', 'е', 'р', ',', ' ', '\0'};
	
	for (int i = 0; i < TEXT_SIZE - 1; ++i)
	{
		if (text[i] == ',' && text[i + 1] == ' ')
		{
			insert(text, TEXT_SIZE, subtext, SUBTEXT_SIZE, i + 1);
			i += i + 1 + SUBTEXT_SIZE;
		}
	}

	std::cout << text;
}

void insert(char text[], const int TEXT_SIZE, char subtext[], const int SUBTEXT_SIZE, int index)
{
	int text_len = find_len(text, TEXT_SIZE);

	strcat_s(text, TEXT_SIZE, subtext);

	int counter = 0;

	for (int i = text_len; i < (text_len * 2) - (index + 1); ++i)
	{
		text[text_len + counter] = text[index + 1 + counter];
		++counter;
	}

	counter = 0;

	for (int i = index + 1; i < SUBTEXT_SIZE + index; ++i)
	{
		text[i] = subtext[counter];
		++counter;
	}

	counter = 0;

	for (int i = index + SUBTEXT_SIZE; i < text_len + SUBTEXT_SIZE - 1; ++i)
	{
		text[i] = text[text_len + counter];
		++counter;
	}

	text[text_len + SUBTEXT_SIZE - 1] = 0;
}

int find_len(char text[], const int SIZE)
{
	int text_len = 0;

	for (int i = 0; i < SIZE; ++i)
	{
		if (text[i] == '\0')
		{
			break;
		}

		++text_len;
	}

	return text_len;
}

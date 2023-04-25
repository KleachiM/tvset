#include <iostream>
#include "CTVSet.h"
#include "InputHandler.h"

using namespace std;

void PrintStartMessage()
{
	cout << endl << "Введите комадну или q для выхода. Команды: TurnOn, TurnOff, Info," << endl;
	cout << "SelectChannel <номер канала | имя канала>, SelectPreviousChannel, DeleteChannelName <имя канала>," << endl;
	cout << "SetChannelName <номер канала> <имя>, GetChannelName <номер канала>, GetChannelByName <имя канала>" << endl;
}

int main()
{
	PrintStartMessage();
	CTVSet tv;
	std::string line;
	while (getline(cin, line))
	{
		if ((line == "q") || (line == "Q"))
		{
			break;
		}
		if (!HandleInput(tv, line))
		{
			cout << "Введите корректную команду" << endl;
		}
		PrintStartMessage();
	}
}
/*
 * Замечания:
 * добавить пустые строки между методами в tvset.cpp
 * возвращать константную ссылку GetChanneNamesList
 * использовать map вместо vector
 * парсить команды с помощью stringstream
 * пофиксить SelectChannel
 */
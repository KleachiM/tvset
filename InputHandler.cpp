#include "InputHandler.h"
#include <iostream>
#include <sstream>
#include <optional>
#include <numeric>
//TODO: парсить команды с помощью stringstream
std::string VectorToStringFromElement(std::vector<std::string> vectorOfString, int elementNum = 0)
{
	return std::accumulate(vectorOfString.begin() + elementNum, vectorOfString.end(), std::string(),
		[](std::string& x, std::string& y) {
			return x.empty() ? y : x + " " + y;
		});
}

std::vector<std::string> GetParsedUserInput(const std::string& inputString)
{
	std::vector<std::string> parsedUserInput;
	std::istringstream strm(inputString);
	while (!strm.eof())
	{
		std::string tmp;
		strm >> tmp;
		if (tmp.empty())
		{
			break;
		}
		parsedUserInput.push_back(tmp);
	}
	if (parsedUserInput.size() > 0)
	{
		std::transform(parsedUserInput.at(0).begin(), parsedUserInput.at(0).end(),
			parsedUserInput.at(0).begin(),
			[](unsigned char c) {return std::tolower(c);});
	}
	return parsedUserInput;
}

bool TurnOn(CTVSet& tv)
{
	tv.TurnOn();
	std::cout << "TV turned on" << std::endl;
	return true;
}

bool TurnOff(CTVSet& tv)
{
	tv.TurnOff();
	std::cout << "TV turned off" << std::endl;
	return true;
}

bool Info(const CTVSet& tv)
{
	if (!tv.GetState())
	{
		std::cout << "TV is turned off" << std::endl;
		return true;
	}
	std::cout << "TV is turned on" << std::endl;
	std::cout << "Current channel is " << tv.GetCurrentChannelNum() << std::endl;
	std::vector<std::string> channelNamesList = tv.GetChannelNamesList();
	for (int i = 0; i < channelNamesList.size(); i++)
	{
		if (!channelNamesList.at(i).empty())
		{
			std::cout << i + 1 << " - " << tv.GetChannelName(i + 1) << std::endl;
		}
	}
	return true;
}

bool SelectChannel(CTVSet& tv, const std::vector<std::string>& parsedInput)
{
	//TODO: упростить
	if (parsedInput.size() < 2)
	{
		std::cout << "Неправильное количество аргументов. Пример использования: " << std::endl;
		std::cout << "SelectChannel <номер канала> или SelectChannel <имя канала>" << std::endl;
		return false;
	}
	std::string argument = VectorToStringFromElement(parsedInput, 1);
	try
	{
		std::size_t pos; int channelNum = std::stoi(argument, &pos);
		if (pos == argument.size())
		{
			if (!tv.SelectChannel(channelNum))
			{
				std::cout << "Невозможно установить канал № " << channelNum << std::endl;
				return false;
			}
		}
		else
		{
			if (!tv.SelectChannel(argument))
			{
				std::cout << "Невозможно установить канал с именем '" << argument << "'" << std::endl;
				return false;
			}
		}
	}
	catch(std::invalid_argument const& ex)
	{
		if (!tv.SelectChannel(argument))
		{
			std::cout << "Невозможно установить канал с именем '" << argument << "'" << std::endl;
			return false;
		}
	}
	catch(std::out_of_range const& ex)
	{
		std::cout << "Невозможно установить канал № " << argument << std::endl;
		return false;
	}
	std::cout << "Включен канал " << argument << std::endl;
	return true;
}

std::optional<int> GetIntFromString(const std::string& intAsString)
{
	try
	{
		std::size_t pos;
		int intFromString = std::stoi(intAsString, &pos);
		if (pos == intAsString.size())
		{
			return intFromString;
		}
		return std::nullopt;
	}
	catch (std::exception const& ex)
	{
		return std::nullopt;
	}
}

bool SetChannelName(CTVSet& tv, const std::vector<std::string>& parsedInput)
{
	if (parsedInput.size() < 3)
	{
		std::cout << "Неправильное количество аргументов. Пример использования:" << std::endl;
		std::cout << "SetChannelName <номер канала> <имя канала>" << std::endl;
		return false;
	}
	auto channelNum = GetIntFromString(parsedInput.at(1));
	if (!channelNum)
	{
		std::cout << "Неправильный номер канала. Пример использования:" << std::endl;
		std::cout << "SetChannelName <номер канала> <имя канала>" << std::endl;
		return false;
	}
	std::string channelName = VectorToStringFromElement(parsedInput, 2);
	if (!tv.SetChannelName(*channelNum, channelName))
	{
		return false;
	}
	return true;
}

bool DeleteChannelName(CTVSet& tv, const std::vector<std::string>& parsedInput)
{
	if (parsedInput.size() < 2)
	{
		std::cout << "Неправильный формат команды. Пример использования:" << std::endl;
		std::cout << "DeleteChannelName <имя канала>" << std::endl;
		return false;
	}
	std::string channelToDelete = VectorToStringFromElement(parsedInput, 1);
	tv.DeleteChannelName(channelToDelete);
	return true;
}

bool GetChannelName(CTVSet& tv, const std::vector<std::string>& parsedInput)
{
	if (parsedInput.size() != 2)
	{
		std::cout << "Неправильный формат команды. Пример использования:" << std::endl;
		std::cout << "GetChannelName <номер канала>" << std::endl;
		return false;
	}
	auto channelNum = GetIntFromString(parsedInput.at(1));
	if (!channelNum)
	{
		std::cout << "Неправильный формат команды. Пример использования:" << std::endl;
		std::cout << "GetChannelName <номер канала>" << std::endl;
		return false;
	}
	std::string channelName = tv.GetChannelName(*channelNum);
	if (channelName.empty())
	{
		std::cout << "У канала " << *channelNum << " нет имени" << std::endl;
		return false;
	}
	std::cout << "Имя канала: " << channelName << std::endl;
	return true;
}

bool GetChannelByName(CTVSet& tv, const std::vector<std::string>& parsedInput)
{
	if (parsedInput.size() < 2)
	{
		std::cout << "Неправильный формат команды. Пример использования:" << std::endl;
		std::cout << "GetChannelByName <имя канала>" << std::endl;
		return false;
	}
	std::string channelName = VectorToStringFromElement(parsedInput, 1);
	int channelNum = tv.GetChannelByName(channelName);
	if (channelNum == 0)
	{
		std::cout << "Канал с именем " << channelName << " не найден" << std::endl;
		return false;
	}
	std::cout << "Номер канала: " << channelNum << std::endl;
	return true;
}

bool SelectPreviousChannel(CTVSet& tv)
{
	tv.SelectPreviousChannel();
	std::cout << "Включен канал " << tv.GetCurrentChannelNum() << std::endl;
	return true;
}

bool HandleInput(CTVSet& tv, const std::string& userInput)
{
	//TODO: сократить
	std::vector<std::string> parsedInput = GetParsedUserInput(userInput);
	if (parsedInput.size() == 0)
	{
		return false;
	}
	std::string action = parsedInput.at(0);
	if (action == "turnon")
	{
		return TurnOn(tv);
	}
	if (action == "turnoff")
	{
		return TurnOff(tv);
	}
	if (action == "info")
	{
		return Info(tv);
	}
	if (action == "selectchannel")
	{
		return SelectChannel(tv, parsedInput);
	}
	if (action == "setchannelname")
	{
		return SetChannelName(tv, parsedInput);
	}
	if (action == "deletechannelname")
	{
		return DeleteChannelName(tv, parsedInput);
	}
	if (action == "getchannelname")
	{
		return GetChannelName(tv, parsedInput);
	}
	if (action == "getchannelbyname")
	{
		return GetChannelByName(tv, parsedInput);
	}
	if (action == "selectpreviouschannel")
	{
		return SelectPreviousChannel(tv);
	}
	return false;
}
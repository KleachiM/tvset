#ifndef TVSET_CTVSET_H
#define TVSET_CTVSET_H

#include <string>
#include <vector>

const int MIN_CHANNEL = 1;
const int MAX_CHANNEL = 99;

class CTVSet
{
public:
	CTVSet();
	~CTVSet();
	void TurnOn();
	void TurnOff();
	bool SelectChannel(const int channelNum);
	bool SelectChannel(const std::string& channelName);
	void SelectPreviousChannel();

	bool SetChannelName(const int channelNum, const std::string& channelName);
	std::string GetChannelName(const int channelNum)const;
	int GetChannelByName(const std::string& channelName)const;
	bool DeleteChannelName(const std::string& channelName);

	bool GetState()const;
	int GetCurrentChannelNum()const;
	std::vector<std::string> GetChannelNamesList()const; //TODO: возвращать ссылку
private:
	bool m_tvIsOn = false;
	int m_currChannelNum = 0;
	int m_prevChannelNum = 1;
//TODO: использовать map
	std::vector<std::string> m_channelNames;
};

#endif // TVSET_CTVSET_H

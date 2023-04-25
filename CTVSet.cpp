#include "CTVSet.h"
#include <iostream>

CTVSet::CTVSet()
: m_tvIsOn(false), m_currChannelNum(0), m_prevChannelNum(1),
	m_channelNames(MAX_CHANNEL)
{

}

CTVSet::~CTVSet()
{
}

bool CTVSet::GetState() const
{
	return m_tvIsOn;
}

void CTVSet::TurnOn()
{
	if (!m_tvIsOn)
	{
		m_tvIsOn = true;
		m_currChannelNum = m_prevChannelNum;
	}
}

void CTVSet::TurnOff()
{
	m_tvIsOn = false;
	m_prevChannelNum = m_currChannelNum;
	m_currChannelNum = 0;
}

//TODO: убрать const
bool CTVSet::SelectChannel(const int channelNum)
{
	if (!m_tvIsOn)
	{
		return false;
	}
	if ((channelNum < MIN_CHANNEL) || (channelNum > MAX_CHANNEL))
	{
		return false;
	}
	m_prevChannelNum = m_currChannelNum;
	m_currChannelNum = channelNum;
	return true;
}

bool CTVSet::SelectChannel(const std::string& channelName)
{
	int channelNum = GetChannelByName(channelName);
	if (channelNum == 0)
	{
		return false;
	}
	m_prevChannelNum = m_currChannelNum;
	m_currChannelNum = channelNum;
	return true;
}

void CTVSet::SelectPreviousChannel()
{
	if ((!m_tvIsOn) || (m_currChannelNum == m_prevChannelNum) || (m_prevChannelNum == 0))
	{
		return;
	}
	std::swap(m_currChannelNum, m_prevChannelNum);
}

int CTVSet::GetCurrentChannelNum() const
{
	return m_currChannelNum;
}

bool CTVSet::SetChannelName(const int channelNum, const std::string& channelName)
{
	if ((!m_tvIsOn) || (channelNum < MIN_CHANNEL) || (channelNum > MAX_CHANNEL))
	{
		return false;
	}
	auto it = std::find(m_channelNames.begin(), m_channelNames.end(), channelName);
	if (it != m_channelNames.end())
	{
		m_channelNames.erase(it);
	}
	m_channelNames.at(channelNum - 1) = channelName;
	return true;
}

std::string CTVSet::GetChannelName(const int channelNum)const
{
	if ((channelNum < MIN_CHANNEL) || (channelNum > MAX_CHANNEL))
	{
		return std::string ();
	}
	return m_channelNames.at(channelNum - 1);
}

int CTVSet::GetChannelByName(const std::string& channelName)const
{
	auto it = std::find(m_channelNames.begin(), m_channelNames.end(), channelName);
	if (it == m_channelNames.end())
	{
		return 0;
	}
	return 1 + it - m_channelNames.begin();
}

bool CTVSet::DeleteChannelName(const std::string& channelName)
{
	auto it = std::find(m_channelNames.begin(), m_channelNames.end(), channelName);
	if (it != m_channelNames.end())
	{
		m_channelNames.erase(it);
		return true;
	}
	return false;
}

std::vector<std::string> CTVSet::GetChannelNamesList() const
{
	return m_channelNames;
}

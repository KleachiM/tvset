#include "../InputHandler.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Unknown command")
{
	CTVSet tv;
	REQUIRE_FALSE(HandleInput(tv, "notExist"));
}

TEST_CASE("Turn on tv and then turn off")
{
	CTVSet tv;
	REQUIRE(HandleInput(tv, "TurnOn"));
	REQUIRE(tv.GetState() == true);

	REQUIRE(HandleInput(tv, "TurnOff"));
	REQUIRE(tv.GetState() == false);
}

TEST_CASE("Show info")
{
	CTVSet tv;
	REQUIRE(HandleInput(tv, "Info"));
}

TEST_CASE("Selecting channel")
{
	CTVSet tv;
	tv.TurnOn();
	REQUIRE(HandleInput(tv, "SelectChannel 3"));
	REQUIRE(tv.GetCurrentChannelNum() == 3);
}

TEST_CASE("Bad selecting channel (not existing string arg)")
{
	CTVSet tv;
	tv.TurnOn();
	REQUIRE_FALSE(HandleInput(tv, "SelectChannel bad"));
}

TEST_CASE("Bad selecting channel (empty string arg)")
{
	CTVSet tv;
	tv.TurnOn();
	REQUIRE_FALSE(HandleInput(tv, "SelectChannel   "));
}

TEST_CASE("Ignore extra spaces")
{
	CTVSet tv;
	tv.TurnOn();
	REQUIRE(HandleInput(tv, "SetChannelName 5  Extra  spaces "));
	REQUIRE(tv.GetChannelName(5) == "Extra spaces");
}

TEST_CASE("Delete channel name")
{
	CTVSet tv;
	tv.TurnOn();
	REQUIRE(tv.SetChannelName(5, "5 channel"));
	REQUIRE(HandleInput(tv, "DeleteChannelName 5 channel"));
	REQUIRE_FALSE(tv.GetChannelName(5) == "5 channel");
}

TEST_CASE("Get channel name by number")
{
	CTVSet tv;
	tv.TurnOn();
	tv.SetChannelName(5, "5 channel");
	REQUIRE(HandleInput(tv, "GetChannelName 5"));
	REQUIRE_FALSE(HandleInput(tv, "GetChannelName 6"));
	REQUIRE_FALSE(HandleInput(tv, ""));
	REQUIRE_FALSE(HandleInput(tv, "GetChannelName  "));
}

TEST_CASE("Get channel by name")
{
	CTVSet tv;
	tv.TurnOn();
	tv.SetChannelName(5, "5 channel");
	REQUIRE(HandleInput(tv, "GetChannelByName 5 channel"));
	REQUIRE_FALSE(HandleInput(tv, "GetChannelByName 6 channel"));
}
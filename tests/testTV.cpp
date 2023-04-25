#include "../CTVSet.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("tv initialization")
{
	CTVSet tv;
	REQUIRE_FALSE(tv.GetState());
	REQUIRE(tv.GetCurrentChannelNum() == 0);
}

TEST_CASE("turning tv on")
{
	CTVSet tv;
	tv.TurnOn();
	REQUIRE(tv.GetState());
	REQUIRE(tv.GetCurrentChannelNum() == 1);
}

TEST_CASE("turning tv on and turning off")
{
	CTVSet tv;
	tv.TurnOn();
	tv.TurnOff();
	REQUIRE_FALSE(tv.GetState());
	REQUIRE(tv.GetCurrentChannelNum() == 0);
}

TEST_CASE("selecting valid channel")
{
	CTVSet tv;
	tv.TurnOn();
	tv.SelectChannel(2);
	REQUIRE(tv.GetCurrentChannelNum() == 2);
}

TEST_CASE("selecting not valid channel")
{
	CTVSet tv;
	tv.TurnOn();
	tv.SelectChannel(100);
	REQUIRE(tv.GetCurrentChannelNum() == 1);
}

SCENARIO("Select not valid channel after select valid channel don't change channel")
{
	GIVEN("turned TV")
	{
		CTVSet tv;
		tv.TurnOn();

		THEN("default channel after first turning is 1")
		{
			REQUIRE(tv.GetCurrentChannelNum() == 1);
		}

		WHEN("Selecting valid chanel change current channel")
		{
			tv.SelectChannel(2);

			THEN("Current channel is 2")
			{
				REQUIRE(tv.GetCurrentChannelNum() == 2);
			}

			WHEN("Selecting not valid channel after valid channel")
			{
				tv.SelectChannel(100);
			}

			THEN("Not change channel with not valid channel num")
			{
				REQUIRE(tv.GetCurrentChannelNum() == 2);
			}
		}
	}
}

SCENARIO("Not turned tv not select channel")
{
	GIVEN("TV")
	{
		CTVSet tv;

		WHEN("Select channel on not turned tv")
		{
			tv.SelectChannel(2);
			THEN("Channel not change")
			{
				REQUIRE(tv.GetCurrentChannelNum() == 0);
			}
		}
	}
}

SCENARIO("Channels not change after TV turn of")
{
	GIVEN("TV turn on")
	{
		CTVSet tv;
		tv.TurnOn();

		WHEN("Change channel and turn off tv")
		{
			tv.SelectChannel(2);
			tv.TurnOff();

			THEN("Channels not change")
			{
				REQUIRE(tv.GetCurrentChannelNum() == 0);
			}
		}
	}
}

SCENARIO("TV turn on with previous channel")
{
	GIVEN("TV turn on")
	{
		CTVSet tv;
		tv.TurnOn();

		THEN("After first turning on channel is 1")
		{
			REQUIRE(tv.GetCurrentChannelNum() == 1);
		}

		WHEN("Select channel 2, TV turn off and then turn on")
		{
			tv.SelectChannel(2);
			tv.TurnOff();
			tv.TurnOn();

			THEN("Current channel is 2")
			{
				REQUIRE(tv.GetCurrentChannelNum() == 2);
			}
		}
	}
}

SCENARIO("Selecting previous channel")
{
	GIVEN("turned TV")
	{
		CTVSet tv;
		tv.TurnOn();

		WHEN("Select channel 2 and then channel 3 and then prev chan")
		{
			tv.SelectChannel(2);
			tv.SelectChannel(3);
			tv.SelectPreviousChannel();

			THEN("Curr channel is 2")
			{
				REQUIRE(tv.GetCurrentChannelNum() == 2);
			}
		}
	}
}

SCENARIO("Double selecting previous channel")
{
	GIVEN("turned TV, selected 2 and then 3 channel")
	{
		CTVSet tv;
		tv.TurnOn();
		tv.SelectChannel(2);
		tv.SelectChannel(3);

		WHEN("After double select previous channel, channel is 3")
		{
			tv.SelectPreviousChannel();
			THEN("Curr channel is 2")
			{
				REQUIRE(tv.GetCurrentChannelNum() == 2);
			}

			tv.SelectPreviousChannel();
			THEN("Curr channel is 3")
			{
				REQUIRE(tv.GetCurrentChannelNum() == 3);
			}
		}
	}
}

TEST_CASE("Setting channel name")
{
	CTVSet tv;
	tv.TurnOn();
	tv.SetChannelName(1, "first");
	REQUIRE(tv.GetChannelName(1) == "first");
}

TEST_CASE("Impossible set name in not turned tv")
{
	CTVSet tv;
	tv.SetChannelName(1, "first");
	REQUIRE(tv.GetChannelName(1).empty());
}

TEST_CASE("Impossible set name by not valid channel num")
{
	CTVSet tv;
	tv.TurnOn();
	tv.SetChannelName(100, "impossible");
	REQUIRE_FALSE(tv.GetChannelName(100) == "impossible");
}

TEST_CASE("Create and delete channel")
{
	CTVSet tv;
	tv.TurnOn();
	tv.SetChannelName(1, "first");
	REQUIRE(tv.GetChannelName(1) == "first");

	tv.DeleteChannelName("first");
	REQUIRE(tv.GetChannelName(1).empty());
}

TEST_CASE("Get channel number by name")
{
	CTVSet tv;
	tv.TurnOn();
	tv.SetChannelName(1, "first");
	REQUIRE(tv.GetChannelByName("first") == 1);
	REQUIRE(tv.GetChannelByName("notExist") == 0);
}

TEST_CASE("Selecting channel by name")
{
	CTVSet tv;
	tv.TurnOn();
	tv.SetChannelName(2, "second");
	tv.SelectChannel("second");
	REQUIRE(tv.GetCurrentChannelNum() == 2);
}
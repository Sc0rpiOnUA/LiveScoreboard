#define CATCH_CONFIG_MAIN
#include "Catch2/catch_amalgamated.hpp"
#include "../Scoreboard.h"



TEST_CASE("Ping", "[scoreboard]")
{
	Scoreboard scoreboard;
	REQUIRE(scoreboard.Ping() == "Pong");
}

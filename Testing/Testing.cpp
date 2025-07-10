#include "pch.h"
#include "CppUnitTest.h"
#include "../LiveScoreboard/Scoreboard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(Test)
	{
	public:		
		TEST_METHOD(Ping)
		{
			Scoreboard scoreboard;
			Assert::AreEqual(std::string("Pong"), scoreboard.Ping());
		}
	};

	TEST_CLASS(MatchTesting)
	{
	public:
		TEST_METHOD(CreateMatch)
		{
			Match match("Germany", "Italy");
			
			Assert::AreEqual(std::string("Germany"), match.GetHomeTeamName());
			Assert::AreEqual(std::string("Italy"), match.GetAwayTeamName());
			Assert::AreEqual(0, match.GetHomeTeamScore());
			Assert::AreEqual(0, match.GetAwayTeamScore());
			Assert::AreEqual(0, match.GetScoreSum());
		}
		TEST_METHOD(ModifyMatch)
		{
			Match match("Germany", "Italy");
			match.UpdateTeamNames("Brazil", "USA");
			match.UpdateScore(3, 2);

			Assert::AreEqual(std::string("Brazil"), match.GetHomeTeamName());
			Assert::AreEqual(std::string("USA"), match.GetAwayTeamName());
			Assert::AreEqual(3, match.GetHomeTeamScore());
			Assert::AreEqual(2, match.GetAwayTeamScore());
			Assert::AreEqual(5, match.GetScoreSum());
		}
	};
}

#include "pch.h"
#include "CppUnitTest.h"
#include "../LiveScoreboard/Scoreboard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
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

	TEST_CLASS(ScoreboardTesting)
	{
	public:
		TEST_METHOD(AddMatch)
		{
			Scoreboard scoreboard;

			scoreboard.AddMatch("Germany", "Italy");

			Assert::AreEqual(std::string("Germany"), scoreboard.GetScoreboard()[0].GetHomeTeamName());
			Assert::AreEqual(std::string("Italy"), scoreboard.GetScoreboard()[0].GetAwayTeamName());
			Assert::AreEqual(0, scoreboard.GetScoreboard()[0].GetHomeTeamScore());
			Assert::AreEqual(0, scoreboard.GetScoreboard()[0].GetAwayTeamScore());
			Assert::AreEqual(0, scoreboard.GetScoreboard()[0].GetScoreSum());			
		}
		TEST_METHOD(UpdateMatchScore)
		{
			Scoreboard scoreboard;

			scoreboard.AddMatch("Germany", "Italy");
			scoreboard.UpdateMatchScore(0, 2, 3);

			Assert::AreEqual(std::string("Germany"), scoreboard.GetScoreboard()[0].GetHomeTeamName());
			Assert::AreEqual(std::string("Italy"), scoreboard.GetScoreboard()[0].GetAwayTeamName());
			Assert::AreEqual(2, scoreboard.GetScoreboard()[0].GetHomeTeamScore());
			Assert::AreEqual(3, scoreboard.GetScoreboard()[0].GetAwayTeamScore());
			Assert::AreEqual(5, scoreboard.GetScoreboard()[0].GetScoreSum());
		}

		TEST_METHOD(UpdateEmptyScoreboard)
		{
			bool caughtException = false;
			Scoreboard scoreboard;

			try
			{
				scoreboard.UpdateMatchScore(0, 2, 3);
			}
			catch (const std::exception& e)
			{
				caughtException = true;
				Logger::WriteMessage(e.what());
			}
			if (!caughtException)
			{
				Assert::Fail(L"No exception thrown while one was expected!");
			}
		}

		TEST_METHOD(UpdateMatchOutOfRange)
		{
			bool caughtException = false;
			Scoreboard scoreboard;

			try
			{
				scoreboard.AddMatch("Germany", "Italy");
				scoreboard.UpdateMatchScore(1, 2, 3);
			}
			catch (const std::exception& e)
			{
				caughtException = true;
				Logger::WriteMessage(e.what());
			}
			if (!caughtException)
			{
				Assert::Fail(L"No exception thrown while one was expected!");
			}
		}

		TEST_METHOD(UpdateWithNegativeScores)
		{
			bool caughtException = false;
			Scoreboard scoreboard;

			try
			{
				scoreboard.AddMatch("Germany", "Italy");
				scoreboard.UpdateMatchScore(0, -2, -3);
			}
			catch (const std::exception& e)
			{
				caughtException = true;
				Logger::WriteMessage(e.what());
			}
			if (!caughtException)
			{
				Assert::Fail(L"No exception thrown while one was expected!");
			}
		}

		TEST_METHOD(RemoveMatch)
		{
			Scoreboard scoreboard;

			scoreboard.AddMatch("Germany", "Italy");
			scoreboard.RemoveMatch(0);			

			Assert::AreEqual(static_cast <size_t>(0), scoreboard.GetScoreboard().size());
		}

		TEST_METHOD(RemoveMatchFromEmpty)
		{
			bool caughtException = false;
			Scoreboard scoreboard;

			try
			{
				scoreboard.RemoveMatch(0);
			}
			catch (const std::exception& e)
			{
				caughtException = true;
				Logger::WriteMessage(e.what());
			}
			if (!caughtException)
			{
				Assert::Fail(L"No exception thrown while one was expected!");
			}
		}
		
	};
}

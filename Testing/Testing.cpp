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

		TEST_METHOD(FinishMatch)
		{
			Scoreboard scoreboard;

			scoreboard.AddMatch("Germany", "Italy");
			scoreboard.FinishMatch(0);			

			Assert::AreEqual(static_cast <size_t>(0), scoreboard.GetScoreboard().size());
		}

		TEST_METHOD(FinishMatchInEmpty)
		{
			bool caughtException = false;
			Scoreboard scoreboard;

			try
			{
				scoreboard.FinishMatch(0);
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

		TEST_METHOD(GetSummary)
		{
			Scoreboard scoreboard;
			std::string matchString;

			scoreboard.AddMatch("Mexico", "Canada");
			scoreboard.AddMatch("Spain", "Brazil");
			scoreboard.AddMatch("Germany", "France");
			scoreboard.AddMatch("Uruguay", "Italy");
			scoreboard.AddMatch("Argentina", "Australia");

			scoreboard.UpdateMatchScore(0, 0, 5);
			scoreboard.UpdateMatchScore(1, 10, 2);
			scoreboard.UpdateMatchScore(2, 2, 2);
			scoreboard.UpdateMatchScore(3, 6, 6);
			scoreboard.UpdateMatchScore(4, 3, 1);

			for each (Match match in scoreboard.GetSummary())
			{
				matchString = match.GetHomeTeamName() + " " + std::to_string(match.GetHomeTeamScore()) + " - "
					+ match.GetAwayTeamName() + " " + std::to_string(match.GetAwayTeamScore());
				Logger::WriteMessage(matchString.c_str());
			}

			//Checking the home team name/score is enough, since UpdateMatchScore is checked more thoroughly in other tests
			//Checking scoreboard summary. It should be sorted by sum of goals
			Assert::AreEqual(std::string("Uruguay"), scoreboard.GetSummary()[0].GetHomeTeamName());
			Assert::AreEqual(6, scoreboard.GetSummary()[0].GetHomeTeamScore());
			Assert::AreEqual(std::string("Spain"), scoreboard.GetSummary()[1].GetHomeTeamName());
			Assert::AreEqual(10, scoreboard.GetSummary()[1].GetHomeTeamScore());
			Assert::AreEqual(std::string("Mexico"), scoreboard.GetSummary()[2].GetHomeTeamName());
			Assert::AreEqual(0, scoreboard.GetSummary()[2].GetHomeTeamScore());
			Assert::AreEqual(std::string("Argentina"), scoreboard.GetSummary()[3].GetHomeTeamName());
			Assert::AreEqual(3, scoreboard.GetSummary()[3].GetHomeTeamScore());
			Assert::AreEqual(std::string("Germany"), scoreboard.GetSummary()[4].GetHomeTeamName());
			Assert::AreEqual(2, scoreboard.GetSummary()[4].GetHomeTeamScore());
			
		}
		
	};
}

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
			std::vector <std::string> desiredSummary{ 
				"Uruguay 6 - Italy 6",
				"Spain 10 - Brazil 2",
				"Mexico 0 - Canada 5",
				"Argentina 3 - Australia 1",
				"Germany 2 - France 2" };

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

			for (int i = 0; i < scoreboard.GetSummary().size(); i++)
			{
				matchString = scoreboard.GetSummary()[i].GetHomeTeamName() + " " + std::to_string(scoreboard.GetSummary()[i].GetHomeTeamScore()) + " - "
					+ scoreboard.GetSummary()[i].GetAwayTeamName() + " " + std::to_string(scoreboard.GetSummary()[i].GetAwayTeamScore());
				Logger::WriteMessage(matchString.c_str());
				Assert::AreEqual(desiredSummary[i], matchString);				
			}			
		}

		TEST_METHOD(GetSummaryModified)
		{
			std::vector <std::string> desiredSummary{ 
				"Egypt 8 - India 7",
				"Uruguay 6 - Italy 6",
				"Spain 10 - Brazil 2",
				"USA 2 - Chile 5",
				"Mexico 0 - Canada 5",				
				"Germany 2 - France 2" };

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

			scoreboard.FinishMatch(4);

			scoreboard.AddMatch("USA", "Chile");
			scoreboard.AddMatch("Egypt", "India");
			scoreboard.UpdateMatchScore(4, 2, 5);
			scoreboard.UpdateMatchScore(5, 8, 7);

			for (int i = 0; i < scoreboard.GetSummary().size(); i++)
			{
				matchString = scoreboard.GetSummary()[i].GetHomeTeamName() + " " + std::to_string(scoreboard.GetSummary()[i].GetHomeTeamScore()) + " - "
					+ scoreboard.GetSummary()[i].GetAwayTeamName() + " " + std::to_string(scoreboard.GetSummary()[i].GetAwayTeamScore());
				Logger::WriteMessage(matchString.c_str());
				Assert::AreEqual(desiredSummary[i], matchString);
			}
		}
		
	};
}

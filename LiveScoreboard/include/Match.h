#pragma once
#include <iostream>
using namespace std;

class Match
{
private:
	string homeTeamName;
	int homeTeamScore;
	string awayTeamName;
	int awayTeamScore;

public:
	Match() = delete;
	Match(string homeTeam, string awayTeam);

	int GetScoreSum();
	string GetHomeTeamName();
	int GetHomeTeamScore();
	string GetAwayTeamName();
	int GetAwayTeamScore();

	void UpdateTeamNames(string homeTeam, string awayTeam);
	void UpdateScore(int homeScore, int awayScore);
};
#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "include/Match.h"

class Scoreboard
{
private:
	std::vector<Match> scoreboard;
public:	
	void AddMatch(string team1, string team2);
	void UpdateMatchScore(int index, int homeTeamScore, int awayTeamScore);
	void FinishMatch(int index);
	std::vector<Match> GetSummary();
	std::vector<Match> GetScoreboard();
};



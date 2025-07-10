#include "../include/Match.h"

Match::Match(string homeTeam, string awayTeam)
{
	homeTeamName = homeTeam;
	awayTeamName = awayTeam;
	homeTeamScore = 0;
	awayTeamScore = 0;
}

int Match::GetScoreSum()
{
	return homeTeamScore + awayTeamScore;
}

string Match::GetHomeTeamName()
{
	return homeTeamName;
}

int Match::GetHomeTeamScore()
{
	return homeTeamScore;
}

string Match::GetAwayTeamName()
{
	return awayTeamName;
}

int Match::GetAwayTeamScore()
{
	return awayTeamScore;
}


void Match::UpdateTeamNames(string homeTeam, string awayTeam)
{
	homeTeamName = homeTeam;
	awayTeamName = awayTeam;
}

void Match::UpdateScore(int homeScore, int awayScore)
{
	homeTeamScore = homeScore;
	awayTeamScore = awayScore;
}
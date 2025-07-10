#include "Scoreboard.h"

void Scoreboard::AddMatch(string team1, string team2)
{
    scoreboard.push_back(Match(team1, team2));        
}

void Scoreboard::UpdateMatchScore(int index, int homeTeamScore, int awayTeamScore)
{
    if (index < 0 || index >= scoreboard.size())
    {
        throw std::out_of_range("out of range");
    }
    else if (homeTeamScore < 0 || awayTeamScore < 0)
    {
        throw std::invalid_argument("team scores can't be negative");
    }
    else
    {
        scoreboard.at(index).UpdateScore(homeTeamScore, awayTeamScore);
    }    
}

void Scoreboard::RemoveMatch(int index)
{
    if (scoreboard.size() == 0)
    {
        throw std::out_of_range("scoreboard is empty");
    }
    else if (index < 0 || index >= scoreboard.size())
    {
        throw std::out_of_range("out of range");
    }
    else
    {
        scoreboard.erase(scoreboard.begin() + index);
    }
}

std::vector<Match> Scoreboard::GetSummary()
{
    return scoreboard;
}

std::vector<Match> Scoreboard::GetScoreboard()
{
    return scoreboard;
}

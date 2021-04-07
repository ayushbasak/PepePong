#include "Score.h"

Score::Score()
{
	score1 = 0;
	score2 = 0;
}

int Score::getScore1()
{
	return score1;
}

int Score::getScore2()
{
	return score2;
}

void Score::setScore1(int x)
{
	score1 = x;
}

void Score::setScore2(int x)
{
	score2 = x;
}

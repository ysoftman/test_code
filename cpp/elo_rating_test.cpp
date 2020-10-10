// ysoftman
// ELO rating
// http://en.wikipedia.org/wiki/Elo_rating_system
// http://webpd77.egloos.com/4102040
#include <stdio.h>
#include <math.h>

const int ELO_CRITERION = 400;
const int ELO_K = 100;
const float ELO_GAME_RESULT_WIN = 1.0;
const float ELO_GAME_RESULT_DRAW = 0.5;
const float ELO_GAME_RESULT_LOSE = 0.0;

float EloRating(float Ra, float Rb, float Sa)
{
	// A 의 승률
	float Ea = 1 / (1 + pow(10, ((Rb - Ra) / ELO_CRITERION)));
	// A 의 승률에 기반해 얼마만큼의 추가 점수를 줄 지 결정
	float newRa = Ra + (ELO_K * (Sa - Ea));
	return newRa;
}

int main()
{
	float PlayerLevelA = 500;
	float PlayerLevelB = 200;
	printf("PlayerLevelA = %f, PlayerLevelB = %f\n\n", PlayerLevelA, PlayerLevelB);

	float NewLevelA = 0;
	float NewLevelB = 0;

	NewLevelA = EloRating(PlayerLevelA, PlayerLevelB, ELO_GAME_RESULT_WIN);
	printf("A Win... NewLevel = %f\n", NewLevelA);
	NewLevelA = EloRating(PlayerLevelA, PlayerLevelB, ELO_GAME_RESULT_DRAW);
	printf("A Draw... NewLevel = %f\n", NewLevelA);
	NewLevelA = EloRating(PlayerLevelA, PlayerLevelB, ELO_GAME_RESULT_LOSE);
	printf("A Lose... NewLevel = %f\n", NewLevelA);

	NewLevelB = EloRating(PlayerLevelB, PlayerLevelA, ELO_GAME_RESULT_WIN);
	printf("B Win... NewLevel = %f\n", NewLevelB);
	NewLevelB = EloRating(PlayerLevelB, PlayerLevelA, ELO_GAME_RESULT_DRAW);
	printf("B Draw... NewLevel = %f\n", NewLevelB);
	NewLevelB = EloRating(PlayerLevelB, PlayerLevelA, ELO_GAME_RESULT_LOSE);
	printf("B Lose... NewLevel = %f\n", NewLevelB);

	return 0;
}

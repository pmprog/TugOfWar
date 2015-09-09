
#pragma once

#include <string>

class PlayerInfo
{
	public:
		std::string Name;
		bool Local;
		bool AI;

		int Money;
		float IntrestRate;
		int DelayIntrest;
		int AttackMap[5][3];
		int CurrentTier;

		PlayerInfo(std::string PlayerName, bool IsLocal, bool IsAI)
		{
			Name = PlayerName;
			Local = IsLocal;
			AI = IsAI;

			// Start with 100c, intrest rate of 10%, and a tiering of 1 (in case I put tank tiers in)
			Money = 100;
			IntrestRate = 0.10f;
			DelayIntrest = 0;
			CurrentTier = 1;

			for( int y = 0; y < 3; y++ )
			{
				for( int x = 0; x < 5; x++ )
				{
					AttackMap[x][y] = 0;
				}
			}
		};
};

class GameInfo
{

	public:
		PlayerInfo* BlueTeam[3];
		PlayerInfo* RedTeam[3];

		GameInfo()
		{
			for( int i = 0; i < 3; i++ )
			{
				BlueTeam[i] = nullptr;
				RedTeam[i] = nullptr;
			}

		};

};
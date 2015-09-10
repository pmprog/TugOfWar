
#pragma once

#include <string>

class GameInfo;

class TurnInfo
{
	public:
		enum Actions
		{
			NONE,
			BUY_RED_TANK,
			BUY_GREEN_TANK,
			BUY_BLUE_TANK,
			SELL_TANK,
			BUY_INTEREST
		};

		Actions Action;
		int GridX;
		int GridY;

};

class PlayerInfo
{
	public:
		std::string Name;
		bool Local;
		bool AI;
		bool BlueTeam;
		int TeamIndex;
		GameInfo* GameData;

		int Money;
		float InterestRate;
		int DelayInterest;
		int AttackMap[5][5];
		int CurrentTier;

		std::vector<std::vector<TurnInfo*>> TurnData;

		PlayerInfo(std::string PlayerName, bool IsLocal, bool IsAI)
		{
			Name = PlayerName;
			Local = IsLocal;
			AI = IsAI;

			// Start with 100c, intrest rate of 10%, and a tiering of 1 (in case I put tank tiers in)
			Money = 100;
			InterestRate = 0.10f;
			DelayInterest = 0;
			CurrentTier = 1;

			for( int y = 0; y < 5; y++ )
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
		bool AmHost;

		int BlueLife;
		PlayerInfo* BlueTeam[3];
		int BlueCurrent;

		int RedLife;
		PlayerInfo* RedTeam[3];
		int RedCurrent;

		GameInfo(bool Host)
		{
			AmHost = Host;
			BlueLife = 100;
			RedLife = 100;
			BlueCurrent = 2;
			RedCurrent = 2;
			for( int i = 0; i < 3; i++ )
			{
				BlueTeam[i] = nullptr;
				RedTeam[i] = nullptr;
			}

		};

		void NextTurn()
		{
			do
			{
				BlueCurrent = (BlueCurrent + 1) % 3;
			} while( BlueTeam[BlueCurrent] == nullptr );

			do
			{
				RedCurrent = (RedCurrent + 1) % 3;
			} while( RedTeam[RedCurrent] == nullptr );

		};

};
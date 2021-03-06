
#pragma once

#include <string>

class GameInfo;

class TurnInfo
{
	public:
		enum Actions
		{
			NONE = -1,
			BUY_RED_TANK,
			BUY_GREEN_TANK,
			BUY_BLUE_TANK,
			SELL_TANK,
			BUY_INTEREST,
		};

		Actions Action;
		int GridX;
		int GridY;

		TurnInfo( Actions Act )
		{
			Action = Act;
			GridX = 0;
			GridY = 0;
		};

		TurnInfo( Actions Act, int X, int Y )
		{
			Action = Act;
			GridX = X;
			GridY = Y;
		};

};

class PlayerTurnInfo
{
	public:
		std::vector<TurnInfo*> TurnData;
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
		int AttackMap[4][5];
		int CurrentTier;

		std::vector<PlayerTurnInfo*> TurnData;

		PlayerInfo(std::string PlayerName, bool IsLocal, bool IsAI)
		{
			Name = PlayerName;
			Local = IsLocal;
			AI = IsAI;

			// Start with 100c, intrest rate of 10%, and a tiering of 1 (in case I put tank tiers in)
			Money = 200;
			InterestRate = 0.10f;
			DelayInterest = 0;
			CurrentTier = 1;

			for( int y = 0; y < 5; y++ )
			{
				for( int x = 0; x < 4; x++ )
				{
					AttackMap[x][y] = -1;
				}
			}
		};
};

class GameInfo
{

	public:
		bool AmHost;

    int StartingLife = 30;
    int TurnIncome = 15;
		int TankCost = 50;
		int TankSell = 30;
		int InterestCost = 40;
		float InterestIncrease = 0.1f;

		int BlueLife;
		PlayerInfo* BlueTeam[3];
		int BlueCurrent;

		int RedLife;
		PlayerInfo* RedTeam[3];
		int RedCurrent;

		GameInfo(bool Host)
		{
			AmHost = Host;
			BlueLife = StartingLife;
			RedLife = StartingLife;
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
		  float bonus;
			do
			{
				BlueCurrent = (BlueCurrent + 1) % 3;
			} while( BlueTeam[BlueCurrent] == nullptr );
			BlueTeam[BlueCurrent]->TurnData.push_back( new PlayerTurnInfo() );

			// Add turn income, then add interest bonus
			BlueTeam[BlueCurrent]->Money += TurnIncome;
			bonus = BlueTeam[BlueCurrent]->Money * BlueTeam[BlueCurrent]->InterestRate;
			if( bonus < 1.0f )
      {
        bonus = 1.0f;
      }
			BlueTeam[BlueCurrent]->Money += (int)bonus;

			do
			{
				RedCurrent = (RedCurrent + 1) % 3;
			} while( RedTeam[RedCurrent] == nullptr );
			RedTeam[RedCurrent]->TurnData.push_back( new PlayerTurnInfo() );

			// Add turn income, then add interest bonus
			RedTeam[RedCurrent]->Money += TurnIncome;
			bonus = RedTeam[RedCurrent]->Money * RedTeam[RedCurrent]->InterestRate;
			if( bonus < 1.0f )
      {
        bonus = 1.0f;
      }
			RedTeam[RedCurrent]->Money += (int)bonus;

		};

};

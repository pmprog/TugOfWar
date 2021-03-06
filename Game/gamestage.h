
#pragma once

#include "includes.h"
#include "resources.h"
#include "gameinfo.h"

class GameTankInfo
{
  public:
    int Colour;
    int X;
    int Y;
    bool BlueTeam;
    bool Dead;
};

class GameStage : public Stage
{

	private:
		GameInfo* currentgame;
		ALLEGRO_BITMAP* background;
		bool performbattle;
		TTFFont* textfont;

		std::vector<GameTankInfo*> battletanks;

		void GenerateBackground();
		void ProcessTank(GameTankInfo* Tank);

		void ProcessAndValidatePacket(Event *e);
		void ApplyPacket(Event *e);

  public:
		GameStage(GameInfo* Game);


    // Stage control
    virtual void Begin();
    virtual void Pause();
    virtual void Resume();
    virtual void Finish();
    virtual void EventOccurred(Event *e);
    virtual void Update();
    virtual void Render();
		virtual bool IsTransition();
};


#pragma once

#include "gamestage.h"

class GameTurnAIStage : public Stage
{

	private:
		TTFFont* optionfont;
		GameStage* currentgame;
		PlayerInfo* currentplayer;

		int currentturntime;
		bool turnfinished;

		ALLEGRO_THREAD* aithread;
		static void* ProcessAI(ALLEGRO_THREAD *thread, void *arg);

  public:
		GameTurnAIStage( GameStage* Owner, PlayerInfo* Player );

    // Stage control
    virtual void Begin();
    virtual void Pause();
    virtual void Resume();
    virtual void Finish();
    virtual void EventOccurred(Event *e);
    virtual void Update();
    virtual void Render();
		virtual bool IsTransition();

		GameStage* GetGame();
		PlayerInfo* GetPlayer();
		void CompleteTurn();
};

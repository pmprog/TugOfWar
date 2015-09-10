
#pragma once

#include "includes.h"
#include "resources.h"
#include "gameinfo.h"

class GameStage : public Stage
{

	private:
		GameInfo* currentgame;
		ALLEGRO_BITMAP* background;
		bool performbattle;
		int battlecountdown;

		void GenerateBackground();

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

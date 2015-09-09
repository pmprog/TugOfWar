
#pragma once

#include "gamestage.h"

class GameTurnAIStage : public Stage
{

	private:
		TTFFont* optionfont;
		GameStage* currentgame;

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
};

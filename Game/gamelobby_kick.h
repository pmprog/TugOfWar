
#pragma once

#include "gamelobbystage.h"

class GameLobbyKickStage : public Stage
{

	private:
		TTFFont* optionfont;
		GameLobbyStage* lobby;

  public:
		GameLobbyKickStage( GameLobbyStage* Owner );

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

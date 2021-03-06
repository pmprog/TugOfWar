
#pragma once

#include "gamelobbystage.h"

class GameLobbyAddLocalStage : public Stage
{

	private:
		TTFFont* optionfont;
		PlayerInfo* player;
		Form* editform;
		TextEdit* editname;

  public:
		GameLobbyAddLocalStage( PlayerInfo* ConfigurePlayer );

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

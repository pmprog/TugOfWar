
#pragma once

#include "includes.h"
#include "resources.h"
#include "gameinfo.h"
#include "input.h"

class GameLobbyStage : public Stage
{

	private:
		TTFFont* optionfont;
		TTFFont* helpfont;
		Network* networkconnection;
		GameInfo* currentinfo;
		int selection;
		bool selectionteamisblue;

		void InputEvent(InputItems::ItemSet inputevent);
		void NetworkEvent(Event* e);
		void RenderPlayerSlot(bool BlueTeam, int Index, int X, int Y);

  public:

		GameLobbyStage();
		GameLobbyStage(Network* Connection);

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

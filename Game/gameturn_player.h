
#pragma once

#include "gamestage.h"

class GameTurnPlayerStage : public Stage
{

	private:
		TTFFont* optionfont;
		GameStage* currentgame;
		PlayerInfo* currentplayer;
		ALLEGRO_BITMAP* background;
		bool playeracknowledgedturn;
		bool selectinggrid;
		int gridx;
		int gridy;

		int selectionmenu;

		void GenerateBackground();
		void RenderMenuButton( int Index, int Y, std::string Label );

  public:
		GameTurnPlayerStage( GameStage* Owner, PlayerInfo* Player );

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

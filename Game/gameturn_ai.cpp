
#include "gameturn_ai.h"

GameTurnAIStage::GameTurnAIStage( GameStage* Owner, PlayerInfo* Player )
{
	currentgame = Owner;
	currentplayer = Player;
	optionfont = FontCache::LoadFont( "resources/armalite.ttf", 32 );
	aithread = nullptr;
}

void GameTurnAIStage::Begin()
{
	currentturntime = 0;
	turnfinished = false;

	aithread = al_create_thread( ProcessAI, (void*)this );
	al_start_thread( aithread );
}

void GameTurnAIStage::Pause()
{
}

void GameTurnAIStage::Resume()
{
}

void GameTurnAIStage::Finish()
{
	if( !turnfinished )
	{
		al_set_thread_should_stop( aithread );
	}
}

void GameTurnAIStage::EventOccurred(Event *e)
{
}

void GameTurnAIStage::Update()
{
	currentturntime++;
	// Turn can't be more than 5 seconds, but keep alive for at least 1 second
	if( (currentturntime > FRAMEWORK->GetFramesPerSecond() && turnfinished) || currentturntime >= (FRAMEWORK->GetFramesPerSecond() * 5) )
	{
		delete FRAMEWORK->ProgramStages->Pop();
	}
}

void GameTurnAIStage::Render()
{
	currentgame->Render();
	al_draw_filled_rectangle( 0, 0, DISPLAY->GetWidth(), DISPLAY->GetHeight(), al_map_rgba( 0, 0, 0, 128 ) );

	al_draw_filled_rectangle( 0, 150, DISPLAY->GetWidth(), 330, ( currentplayer->BlueTeam ? al_map_rgb( 30, 167, 225 ) : al_map_rgb( 232, 106, 23 ) ) );
	optionfont->DrawString( 404, 284 - (optionfont->GetFontHeight() / 2), currentplayer->Name + " is thinking...", FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
	optionfont->DrawString( 400, 280 - (optionfont->GetFontHeight() / 2), currentplayer->Name + " is thinking...", FontHAlign::CENTRE, al_map_rgb( 255, 255, 255 ) );
}

bool GameTurnAIStage::IsTransition()
{
	return false;
}

GameStage* GameTurnAIStage::GetGame()
{
	return currentgame;
}

PlayerInfo* GameTurnAIStage::GetPlayer()
{
	return currentplayer;
}

void GameTurnAIStage::CompleteTurn()
{
	turnfinished = true;
}

void* GameTurnAIStage::ProcessAI(ALLEGRO_THREAD *thread, void *arg)
{
	GameTurnAIStage* aiplayer = (GameTurnAIStage*)arg;

	// Abort
	if( al_get_thread_should_stop(thread) )
	{
		aiplayer->CompleteTurn();
		return nullptr;
	}

	aiplayer->GetPlayer()->TurnData.back()->TurnData.push_back( new TurnInfo( TurnInfo::Actions::NONE ) );

	aiplayer->CompleteTurn();
	return nullptr;
}

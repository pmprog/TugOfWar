
#include "gamelobbystage.h"
#include "menu.h"
#include "input.h"
#include "gamelobby_addai.h"
#include "gamelobby_addlocal.h"
#include "gamelobby_kick.h"

GameLobbyStage::GameLobbyStage()
{
	networkconnection = nullptr;
}

GameLobbyStage::GameLobbyStage(Network* Connection)
{
	networkconnection = Connection;
}

void GameLobbyStage::Begin()
{
	optionfont = FontCache::LoadFont( "resources/armalite.ttf", 32 );
	// AUDIO->PlayMusic( "resources/Paul Hannay (Feekzoid) - Last_Ninja_4_loader [1].ogg", true );

}

void GameLobbyStage::Pause()
{
}

void GameLobbyStage::Resume()
{
}

void GameLobbyStage::Finish()
{
	AUDIO->StopMusic();

	if( networkconnection != nullptr )
	{
		delete networkconnection;
		networkconnection = nullptr;
	}
}

void GameLobbyStage::EventOccurred(Event *e)
{
	InputItems::ItemSet inputevent = InputItems::NONE;

	if( e->Type == EVENT_KEY_DOWN )
	{
		if( e->Data.Keyboard.KeyCode == ALLEGRO_KEY_ESCAPE )
		{
			delete FRAMEWORK->ProgramStages->Pop();
			return;
		}

		inputevent = Input::GetItemFromEvent( e );
	}

	if( e->Type == EVENT_JOYSTICK_BUTTON_DOWN && inputevent == InputItems::NONE )
	{
		inputevent = Input::GetItemFromEvent( e );
	}

	switch( inputevent )
	{
		case InputItems::SELECT:
			delete FRAMEWORK->ProgramStages->Pop();
			return;
			break;
		case InputItems::X:
			FRAMEWORK->ProgramStages->Push( new GameLobbyAddLocalStage( this ) );
			break;
		case InputItems::B:
			FRAMEWORK->ProgramStages->Push( new GameLobbyAddAIStage( this ) );
			break;
		case InputItems::Y:
			FRAMEWORK->ProgramStages->Push( new GameLobbyKickStage( this ) );
			break;
		case InputItems::START:
			//FRAMEWORK->ProgramStages->Push( new GameLobbyAddLocalStage( this ) );
			break;

	}
}

void GameLobbyStage::Update()
{
}

void GameLobbyStage::Render()
{
	al_clear_to_color( al_map_rgb( 255, 220, 128 ) );

	optionfont->DrawString( (DISPLAY->GetWidth() / 2) + 2, 12, "Lobby", FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
	optionfont->DrawString( (DISPLAY->GetWidth() / 2), 10, "Lobby", FontHAlign::CENTRE, al_map_rgb( 255, 255, 0 ) );

	GameResources::DrawPanel( GameResources::BluePanel, 5, 80, 13, 8, 8 );
	optionfont->DrawString( 15, 85, "Blue Team", FontHAlign::LEFT, al_map_rgb( 255, 255, 255 ) );

	GameResources::DrawButton( GameResources::WhiteButtonUp, 15, 140, 23, 3 );
	GameResources::DrawButton( GameResources::WhiteButtonUp, 15, 192, 23, 3 );
	GameResources::DrawButton( GameResources::WhiteButtonUp, 15, 244, 23, 3 );

	GameResources::DrawPanel( GameResources::RedPanel, 405, 80, 13, 8, 8 );
	optionfont->DrawString( 415, 85, "Red Team", FontHAlign::LEFT, al_map_rgb( 255, 255, 255 ) );

	GameResources::DrawButton( GameResources::WhiteButtonUp, 415, 140, 23, 3 );
	GameResources::DrawButton( GameResources::WhiteButtonUp, 415, 192, 23, 3 );
	GameResources::DrawButton( GameResources::WhiteButtonUp, 415, 244, 23, 3 );

	// Add Local Player
	int textoff = (50 - optionfont->GetFontHeight()) / 2;
	al_draw_bitmap( Input::GetIcon( InputItems::X ), 10, 320, 0 );
	optionfont->DrawString( 64, 320 + textoff, "Add Local Player", FontHAlign::LEFT, al_map_rgb( 0, 0, 0 ) );

	if( networkconnection == nullptr || networkconnection->IsServer() )
	{
		// Add AI
		al_draw_bitmap( Input::GetIcon( InputItems::B ), 10, 370, 0 );
		optionfont->DrawString( 64, 370 + textoff, "Add CPU Player", FontHAlign::LEFT, al_map_rgb( 0, 0, 0 ) );

		// Kick Player/AI
		al_draw_bitmap( Input::GetIcon( InputItems::Y ), 10, 420, 0 );
		optionfont->DrawString( 64, 420 + textoff, "Kick Player", FontHAlign::LEFT, al_map_rgb( 0, 0, 0 ) );

		// Start game
		al_draw_bitmap( Input::GetIcon( InputItems::START ), 500, 370, 0 );
		optionfont->DrawString( 554, 370 + textoff, "Start", FontHAlign::LEFT, al_map_rgb( 0, 0, 0 ) );
	}

	// Abort/Disconnect
	al_draw_bitmap( Input::GetIcon( InputItems::SELECT ), 500, 420, 0 );
	optionfont->DrawString( 554, 420 + textoff, "Quit", FontHAlign::LEFT, al_map_rgb( 0, 0, 0 ) );

}

bool GameLobbyStage::IsTransition()
{
	return false;
}


#include "gamelobbystage.h"
#include "menu.h"
#include "input.h"
#include "gamelobby_addai.h"
#include "gamelobby_addlocal.h"
#include "gamelobby_kick.h"

GameLobbyStage::GameLobbyStage()
{
	networkconnection = nullptr;
	currentinfo = new GameInfo();
	selection = 0;
}

GameLobbyStage::GameLobbyStage(Network* Connection)
{
	selection = 0;
	networkconnection = Connection;
	currentinfo = new GameInfo();

	if( !Connection->IsServer() )
	{
		// TODO: Request gameinfo from server
	}
}

void GameLobbyStage::Begin()
{
	optionfont = FontCache::LoadFont( "resources/armalite.ttf", 32 );
	helpfont = FontCache::LoadFont( "resources/armalite.ttf", 16 );
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

	if( inputevent != InputItems::NONE )
	{
		InputEvent( inputevent );
	}

	NetworkEvent( e );

}

void GameLobbyStage::InputEvent(InputItems::ItemSet inputevent)
{
	switch( inputevent )
	{
		case InputItems::UP:
			if( selection > 1 )
			{
				selection -= 2;
			}
			break;
		case InputItems::DOWN:
			if( selection < 4 )
			{
				selection += 2;
			}
			break;
		case InputItems::LEFT:
			if( (selection % 2) == 1 )
			{
				selection--;
			}
			break;
		case InputItems::RIGHT:
			if( (selection % 2) == 0 )
			{
				selection++;
			}
			break;

		case InputItems::SELECT:
			delete FRAMEWORK->ProgramStages->Pop();
			return;
			break;
		case InputItems::X:
			if( networkconnection == nullptr )
			{
				FRAMEWORK->ProgramStages->Push( new GameLobbyAddLocalStage( this ) );
			}
			break;
		case InputItems::B:
			if( networkconnection == nullptr )
			{
				FRAMEWORK->ProgramStages->Push( new GameLobbyAddAIStage( this ) );
			}
			break;
		case InputItems::Y:
			if( networkconnection == nullptr || networkconnection->IsServer() )
			{
				FRAMEWORK->ProgramStages->Push( new GameLobbyKickStage( this ) );
			}
			break;
		case InputItems::START:

			if( networkconnection == nullptr || networkconnection->IsServer() )
			{
				//FRAMEWORK->ProgramStages->Push( new GameStage( this ) );
			}
			break;

	}
}

void GameLobbyStage::NetworkEvent(Event* e)
{
	if( e->Type == EVENT_NETWORK_CONNECTION_REQUEST )
	{
		bool freeslot = false;
		freeslot = ( currentinfo->BlueA_Present ? true : freeslot );
		freeslot = ( currentinfo->BlueB_Present ? true : freeslot );
		freeslot = ( currentinfo->BlueC_Present ? true : freeslot );
		freeslot = ( currentinfo->RedA_Present ? true : freeslot );
		freeslot = ( currentinfo->RedB_Present ? true : freeslot );
		freeslot = ( currentinfo->RedC_Present ? true : freeslot );
		if( freeslot )
		{
			// TODO: Accept player and balance teams
		}
	}
	if( e->Type == EVENT_NETWORK_CONNECTED )
	{
		// TODO: Send current game info
	}
	if( e->Type == EVENT_NETWORK_DISCONNECTED )
	{
		// TODO: Remove disconnected users
	}
	if( e->Type == EVENT_NETWORK_PACKET_RECEIVED )
	{
		// TODO: Process packet info
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

	RenderPlayerSlot( true, 0, currentinfo->BlueA_Present, currentinfo->BlueA_Name, currentinfo->BlueA_Local, currentinfo->BlueA_AI, 15, 140 );
	RenderPlayerSlot( true, 2, currentinfo->BlueB_Present, currentinfo->BlueB_Name, currentinfo->BlueB_Local, currentinfo->BlueB_AI, 15, 192 );
	RenderPlayerSlot( true, 4, currentinfo->BlueC_Present, currentinfo->BlueC_Name, currentinfo->BlueC_Local, currentinfo->BlueC_AI, 15, 244 );

	GameResources::DrawPanel( GameResources::RedPanel, 405, 80, 13, 8, 8 );
	optionfont->DrawString( 415, 85, "Red Team", FontHAlign::LEFT, al_map_rgb( 255, 255, 255 ) );

	RenderPlayerSlot( false, 1, currentinfo->RedA_Present, currentinfo->RedA_Name, currentinfo->RedA_Local, currentinfo->RedA_AI, 415, 140 );
	RenderPlayerSlot( false, 3, currentinfo->RedB_Present, currentinfo->RedB_Name, currentinfo->RedB_Local, currentinfo->RedB_AI, 415, 192 );
	RenderPlayerSlot( false, 5, currentinfo->RedC_Present, currentinfo->RedC_Name, currentinfo->RedC_Local, currentinfo->RedC_AI, 415, 244 );

	int textoff = (50 - helpfont->GetFontHeight()) / 2;
	if( networkconnection == nullptr )
	{
		// Add Local Player
		al_draw_bitmap( Input::GetIcon( InputItems::X ), 10, 320, 0 );
		helpfont->DrawString( 64, 320 + textoff, "Add Local Player", FontHAlign::LEFT, al_map_rgb( 0, 0, 0 ) );

		// Add AI
		al_draw_bitmap( Input::GetIcon( InputItems::B ), 10, 370, 0 );
		helpfont->DrawString( 64, 370 + textoff, "Add CPU Player", FontHAlign::LEFT, al_map_rgb( 0, 0, 0 ) );
	}

	if( networkconnection == nullptr || networkconnection->IsServer() )
	{
		// Kick Player/AI
		al_draw_bitmap( Input::GetIcon( InputItems::Y ), 10, 420, 0 );
		helpfont->DrawString( 64, 420 + textoff, "Kick Player", FontHAlign::LEFT, al_map_rgb( 0, 0, 0 ) );

		// Start game
		al_draw_bitmap( Input::GetIcon( InputItems::START ), 500, 370, 0 );
		helpfont->DrawString( 554, 370 + textoff, "Start", FontHAlign::LEFT, al_map_rgb( 0, 0, 0 ) );
	}

	// Abort/Disconnect
	al_draw_bitmap( Input::GetIcon( InputItems::SELECT ), 500, 420, 0 );
	helpfont->DrawString( 554, 420 + textoff, "Quit", FontHAlign::LEFT, al_map_rgb( 0, 0, 0 ) );

}

bool GameLobbyStage::IsTransition()
{
	return false;
}

void GameLobbyStage::RenderPlayerSlot(bool BlueTeam, int Index, bool Present, std::string Name, bool Local, bool AI, int X, int Y)
{
	SpriteSheet* btnimg = GameResources::WhiteButtonDown;
	bool btnup = false;

	if( networkconnection == nullptr || networkconnection->IsServer() )
	{
		if( selection == Index && currentinfo->BlueA_Present )
		{
			btnimg = (BlueTeam ? GameResources::BlueButtonUp : GameResources::RedButtonUp);
			btnup = true;
		} else if( currentinfo->BlueA_Present ) {
			btnimg = (BlueTeam ? GameResources::BlueButtonUp : GameResources::RedButtonDown);
		} else if( selection == Index ) {
			btnimg = GameResources::WhiteButtonUp;
			btnup = true;
		}
	}
	GameResources::DrawButton( btnimg, btnup, X, Y, 23, 3 );
}


#include "gamelobbystage.h"
#include "menu.h"
#include "input.h"
#include "gamelobby_addlocal.h"
#include "gamestage.h"

GameLobbyStage::GameLobbyStage()
{
	networkconnection = nullptr;
	currentinfo = new GameInfo( true );
	selection = 0;
	selectionteamisblue = true;
}

GameLobbyStage::GameLobbyStage(Network* Connection)
{
	selection = 0;
	networkconnection = Connection;
	currentinfo = new GameInfo( Connection->IsServer() );

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
			if( selection > 0 )
			{
				selection--;
			}
			break;
		case InputItems::DOWN:
			if( selection < 2 )
			{
				selection++;
			}
			break;
		case InputItems::LEFT:
			selectionteamisblue = true;
			break;
		case InputItems::RIGHT:
			selectionteamisblue = false;
			break;

		case InputItems::SELECT:
			delete FRAMEWORK->ProgramStages->Pop();
			return;
			break;
		case InputItems::X:
			if( networkconnection == nullptr )
			{
				PlayerInfo* p = nullptr;
				if( selectionteamisblue )
				{
					if( currentinfo->BlueTeam[selection] == nullptr)
					{
						currentinfo->BlueTeam[selection] = new PlayerInfo( "", true, false );
					}
					p = currentinfo->BlueTeam[selection];
				} else {
					if( currentinfo->RedTeam[selection] == nullptr)
					{
						currentinfo->RedTeam[selection] = new PlayerInfo( "", true, false );
					}
					p = currentinfo->RedTeam[selection];
				}
				p->BlueTeam = selectionteamisblue;
				p->TeamIndex = selection;
				p->GameData = currentinfo;
				FRAMEWORK->ProgramStages->Push( new GameLobbyAddLocalStage( p ) );
			}
			break;
		case InputItems::B:
			if( networkconnection == nullptr )
			{
				PlayerInfo* p = nullptr;
				if( selectionteamisblue )
				{
					if( currentinfo->BlueTeam[selection] == nullptr )
					{
						p = new PlayerInfo( "CPU", true, true );
						currentinfo->BlueTeam[selection] = p;
					}
				} else {
					if( currentinfo->RedTeam[selection] == nullptr )
					{
						p = new PlayerInfo( "CPU", true, true );
						currentinfo->RedTeam[selection] = p;
					}
				}
				if( p != nullptr )
				{
					p->BlueTeam = selectionteamisblue;
					p->TeamIndex = selection;
					p->GameData = currentinfo;
				}
			}
			break;
		case InputItems::Y:
			if( networkconnection == nullptr || networkconnection->IsServer() )
			{
				PlayerInfo* p = nullptr;
				if( selectionteamisblue )
				{
					p = currentinfo->BlueTeam[selection];
					currentinfo->BlueTeam[selection] = nullptr;
				} else {
					p = currentinfo->RedTeam[selection];
					currentinfo->RedTeam[selection] = nullptr;
				}

				if( p != nullptr )
				{
					if( !p->Local )
					{
						// TODO: Disconnect
					}
					delete p;
				}
			}
			break;
		case InputItems::START:

			if( networkconnection == nullptr || networkconnection->IsServer() )
			{
				// TODO: Tell clients to start the game
				FRAMEWORK->ProgramStages->Push( new GameStage( currentinfo ) );
			}
			break;

	}
}

void GameLobbyStage::NetworkEvent(Event* e)
{
	if( e->Type == EVENT_NETWORK_CONNECTION_REQUEST )
	{
		bool freeslot = false;
		for( int i = 0; i < 3; i++ )
		{
			freeslot = ( currentinfo->BlueTeam[i] == nullptr ? true : freeslot );
			freeslot = ( currentinfo->RedTeam[i] == nullptr ? true : freeslot );
		}
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

	RenderPlayerSlot( true, 0, 15, 140 );
	RenderPlayerSlot( true, 1, 15, 192 );
	RenderPlayerSlot( true, 2, 15, 244 );

	GameResources::DrawPanel( GameResources::RedPanel, 405, 80, 13, 8, 8 );
	optionfont->DrawString( 415, 85, "Red Team", FontHAlign::LEFT, al_map_rgb( 255, 255, 255 ) );

	RenderPlayerSlot( false, 0, 415, 140 );
	RenderPlayerSlot( false, 1, 415, 192 );
	RenderPlayerSlot( false, 2, 415, 244 );

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

void GameLobbyStage::RenderPlayerSlot(bool BlueTeam, int Index, int X, int Y)
{
	ButtonColours::Colours colour = ButtonColours::WHITE;
	bool btnup = false;
	PlayerInfo* p = (BlueTeam ? currentinfo->BlueTeam[Index] : currentinfo->RedTeam[Index]);

	if( p != nullptr )
	{
		colour = (BlueTeam ? ButtonColours::BLUE : ButtonColours::RED );
	}

	if( networkconnection == nullptr || networkconnection->IsServer() )
	{
		if( selection == Index && selectionteamisblue == BlueTeam )
		{
			colour = ButtonColours::YELLOW;
			btnup = true;
		}
	}
	GameResources::DrawButton( colour, btnup, X, Y, 23, 3 );
	if( p != nullptr )
	{
		helpfont->DrawString( X + 184, Y + 24 - (helpfont->GetFontHeight() / 2) + (!btnup ? 4 : 0), p->Name, FontHAlign::CENTRE, al_map_rgb( 0, 0, 0 ) );
		// helpfont->DrawString( X + 184, Y + 24 - (helpfont->GetFontHeight() / 2) + (!btnup ? 4 : 0) - 2, p->Name, FontHAlign::CENTRE, al_map_rgb( 255, 255, 255 ) );
	}

}

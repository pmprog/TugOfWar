
#include "gamestage.h"
#include "gameturn_player.h"
#include "gameturn_ai.h"
#include "gameturn_network.h"
#include "../Framework/Primitives/strings.h"

GameStage::GameStage(GameInfo* Game)
{
	currentgame = Game;
	background = nullptr;
	performbattle = false;
	GenerateBackground();
	textfont = FontCache::LoadFont( "resources/armalite.ttf", 32 );
	// Set to first players
	currentgame->NextTurn();
}

void GameStage::Begin()
{
	// AUDIO->PlayMusic( "resources/Paul Hannay (Feekzoid) - Last_Ninja_4_loader [1].ogg", true );
}

void GameStage::Pause()
{
}

void GameStage::Resume()
{
}

void GameStage::Finish()
{
	AUDIO->StopMusic();
	al_destroy_bitmap( background );
}

void GameStage::EventOccurred(Event *e)
{
	if( e->Type == EVENT_KEY_DOWN )
	{
		if( e->Data.Keyboard.KeyCode == ALLEGRO_KEY_ESCAPE )
		{
			delete FRAMEWORK->ProgramStages->Pop();
			return;
		}
	}

	if( e->Type == EVENT_NETWORK_PACKET_RECEIVED )
	{
		if( currentgame->AmHost )
		{
			// Process and distribute
			ProcessAndValidatePacket(e);
		} else {
			// Drive from here
			ApplyPacket(e);
		}
	}
}

void GameStage::Update()
{

	if( performbattle )
	{

		if( battletanks.size() > 0 )
		{
      // Move tanks, and calculate battles
			for( int idx = 0; idx < battletanks.size(); idx++ )
      {
        GameTankInfo* t = battletanks.at( idx );
        ProcessTank( t );
      }

      // Remove dead tanks
			for( int idx = battletanks.size() - 1; idx >= 0; idx-- )
      {
        GameTankInfo* t = battletanks.at( idx );
        if( t->Dead )
        {
          battletanks.erase( battletanks.begin() + idx );
        }
      }

		} else {
			performbattle = false;
			currentgame->NextTurn();
		}

	} else if( currentgame->AmHost ) {
		// Drive from here
		PlayerInfo* blue = currentgame->BlueTeam[currentgame->BlueCurrent];
		PlayerInfo* red = currentgame->RedTeam[currentgame->RedCurrent];

		if( blue->Local && blue->TurnData.back()->TurnData.size() == 0 )
		{
			if( !blue->AI )
			{
				FRAMEWORK->ProgramStages->Push( new GameTurnPlayerStage( this, blue ) );
			} else {
				FRAMEWORK->ProgramStages->Push( new GameTurnAIStage( this, blue ) );
			}
			return;
		}

		if( red->Local && red->TurnData.back()->TurnData.size() == 0 )
		{
			if( !red->AI )
			{
				FRAMEWORK->ProgramStages->Push( new GameTurnPlayerStage( this, red ) );
			} else {
				FRAMEWORK->ProgramStages->Push( new GameTurnAIStage( this, red ) );
			}
			return;
		}

		if( blue->TurnData.back()->TurnData.size() == 0 )
		{
			FRAMEWORK->ProgramStages->Push( new GameTurnNetworkStage( this, blue ) );
			return;
		}

		if( red->TurnData.back()->TurnData.size() == 0 )
		{
			FRAMEWORK->ProgramStages->Push( new GameTurnNetworkStage( this, red ) );
			return;
		}

		performbattle = true;
		for( int y = 0; y < 5; y++ )
    {
      for( int x = 0; x < 4; x++ )
      {
        if( blue->AttackMap[x][y] >= 0 && blue->AttackMap[x][y] < 3 )
        {
          GameTankInfo* ti = new GameTankInfo();
          ti->Colour = blue->AttackMap[x][y];
          ti->BlueTeam = true;
          ti->X = (x * 90) - 315;
          ti->Y = 45 + (y * 90);
          ti->Dead = false;
          battletanks.push_back( ti );
        }
        if( red->AttackMap[x][y] >= 0 && red->AttackMap[x][y] < 3 )
        {
          GameTankInfo* ti = new GameTankInfo();
          ti->Colour = red->AttackMap[x][y];
          ti->BlueTeam = false;
          ti->X = 845 + (x * 90);
          ti->Y = 45 + (y * 90);
          ti->Dead = false;
          battletanks.push_back( ti );
        }
      }
    }

	} else {
		// Check last packet, if not heard anything for a while, ping and check
	}
}

void GameStage::Render()
{
	al_draw_bitmap( background, 0, 0, 0 );

	// Draw Blue Team's Health
	al_draw_filled_rectangle( 0, 450, (int)((400.0f / (float)currentgame->StartingLife) * (float)currentgame->BlueLife), 480, al_map_rgb( 30, 167, 225 ) );
	textfont->DrawString( 6, 480 - textfont->GetFontHeight(), "Blue Team: " + Strings::FromNumber( currentgame->BlueLife ), FontHAlign::LEFT, al_map_rgb( 0, 0, 0 ) );
	textfont->DrawString( 4, 478 - textfont->GetFontHeight(), "Blue Team: " + Strings::FromNumber( currentgame->BlueLife ), FontHAlign::LEFT, al_map_rgb( 255, 255, 255 ) );
	// Draw Red Team's Health
	al_draw_filled_rectangle( 800 - (int)((400.0f / (float)currentgame->StartingLife) * (float)currentgame->RedLife), 450, 800, 480, al_map_rgb( 232, 106, 23 ) );
	textfont->DrawString( 794, 480 - textfont->GetFontHeight(), "Red Team: " + Strings::FromNumber( currentgame->RedLife ), FontHAlign::RIGHT, al_map_rgb( 0, 0, 0 ) );
	textfont->DrawString( 796, 478 - textfont->GetFontHeight(), "Red Team: " + Strings::FromNumber( currentgame->RedLife ), FontHAlign::RIGHT, al_map_rgb( 255, 255, 255 ) );

  for( int idx = 0; idx < battletanks.size(); idx++ )
  {
    GameTankInfo* t = battletanks.at( idx );
    // Already processed
    if( !t->Dead )
    {
      GameResources::DrawTank( t->Colour, t->X, t->Y, (t->BlueTeam ? Angle(90) : Angle(270) ) );
    }
  }

}

bool GameStage::IsTransition()
{
	return false;
}

void GameStage::GenerateBackground()
{
	int backgroundindex = rand() % 3;

  background = al_create_bitmap( 1024, 512 );
	DISPLAY->SetTarget( background );

	int iw = al_get_bitmap_width( GameResources::BackgroundTiles.at(backgroundindex) );
	int ih = al_get_bitmap_height( GameResources::BackgroundTiles.at(backgroundindex) );
	int bx = 0;
	int by = 0;

	al_hold_bitmap_drawing( true );
	while( by < 512 )
	{
		while( bx < 1024 )
		{
			al_draw_bitmap( GameResources::BackgroundTiles.at(backgroundindex), bx, by, 0 );
			bx += iw;
		}
		by += ih;
		bx = 0;
	}
	al_hold_bitmap_drawing( false );

	DISPLAY->ClearTarget();
}

void GameStage::ProcessTank(GameTankInfo* Tank)
{
  GameTankInfo* t = Tank;
  // Already processed
  if( !t->Dead )
  {
    t->X += ( t->BlueTeam ? 2 : -2 );

    for( int idx = 0; idx < battletanks.size(); idx++ )
    {
      GameTankInfo* topp = battletanks.at( idx );
      if( !topp->Dead && t->BlueTeam != topp->BlueTeam && t->Y == topp->Y && Maths::Abs( t->X - topp->X ) <= 45 )
      {
        // Check collision
        if( topp->Colour == t->Colour )
        {
          topp->Dead = true;;
          t->Dead = true;
        }
        if( topp->Colour == ((t->Colour + 1) % 3) )
        {
          topp->Dead = true;
        }
        if( t->Colour == ((topp->Colour + 1) % 3) )
        {
          t->Dead = true;
        }
      }
    }

    if( t->X < 0 && !t->BlueTeam )
    {
      currentgame->BlueLife--;
      t->Dead = true;
    }
    if( t->X > 800 && t->BlueTeam )
    {
      currentgame->RedLife--;
      t->Dead = true;
    }
  }
}

void GameStage::ProcessAndValidatePacket(Event *e)
{
}

void GameStage::ApplyPacket(Event *e)
{
}

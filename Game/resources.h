
#pragma once

#include "includes.h"

class ButtonColours
{
	public:
		enum Colours
		{
			WHITE = 0,
			BLUE = 1,
			RED = 2,
			YELLOW = 3
		};
};

class GameResources
{

  public:
		static std::vector<ALLEGRO_BITMAP*> BackgroundTiles;
		static SpriteSheet* BluePanel;
		static SpriteSheet* RedPanel;
		static SpriteSheet* CombinedButtons;

		static void InitResources();

		static void DrawTank(int Colour, int X, int Y, Angle Rotation);
		static void DrawPanel(SpriteSheet* Graphics, int X, int Y, int TilesWide, int TilesHigh, int HeaderTilesWide);
		static void DrawButton(ButtonColours::Colours Colour, bool IsRaised, int X, int Y, int TilesWide, int TilesHigh);
};

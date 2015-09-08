
#pragma once

#include "includes.h"

class GameResources
{

  public:
		static std::vector<ALLEGRO_BITMAP*> BackgroundTiles;
		static SpriteSheet* BluePanel;
		static SpriteSheet* RedPanel;
		static SpriteSheet* WhiteButtonUp;
		static SpriteSheet* WhiteButtonDown;
		static SpriteSheet* BlueButtonUp;
		static SpriteSheet* BlueButtonDown;
		static SpriteSheet* RedButtonUp;
		static SpriteSheet* RedButtonDown;

		static void InitResources();

		static void DrawTank(int Colour, int X, int Y, Angle Rotation);
		static void DrawPanel(SpriteSheet* Graphics, int X, int Y, int TilesWide, int TilesHigh, int HeaderTilesWide);
		static void DrawButton(SpriteSheet* Graphics, bool IsRaised, int X, int Y, int TilesWide, int TilesHigh);
};

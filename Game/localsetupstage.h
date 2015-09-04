
#pragma once

#include "includes.h"
#include "resources.h"

class LocalSetupStage : public Stage
{

	private:
		TTFFont* optionfont;
		SpriteSheet* bluepanel;
		SpriteSheet* redpanel;

		void DrawPanel(SpriteSheet* PanelGraphics, int X, int Y, int TilesWide, int TilesHigh, int HeaderTilesWide);

  public:
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

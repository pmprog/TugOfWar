
#pragma once

#include "includes.h"
#include "resources.h"

#define MENU_SPACING	600

class NetworkMenu : public Stage
{
	private:
		int backgroundindex;
		int menutime;
		int rendertime;
		TTFFont* titlefont;
		TTFFont* optionfont;
		int sliderindex;
		int slidertarget;
		int sliderprevious;
		int sliderstart;

		void GenerateBackground();
		void RenderLocal(int X);
		void RenderNetwork(int X);
		void RenderHelp(int X);
		void RenderSettings(int X);
		void RenderQuit(int X);

  public:
		ALLEGRO_BITMAP* background;

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

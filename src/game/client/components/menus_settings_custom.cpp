#include <game/client/gameclient.h>

#include "menus.h"

void CMenus::RenderSettingsCustom(CUIRect MainView)
{
	CUIRect LeftSide, RightSide;
	MainView.HSplitMid(&LeftSide, &MainView);
	LeftSide.VSplitMid(&LeftSide, &RightSide);

	LeftSide.Draw(ColorRGBA(0.f, 1.f, 0.f, 0.1f), 0, 0);
	RightSide.Draw(ColorRGBA(0.f, 0.f, 1.f, 0.1f), 0, 0);
	MainView.Draw(ColorRGBA(1.f, 0.f, 0.f, 0.1f), 0, 0);
}

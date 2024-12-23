#include <game/client/gameclient.h>

#include "game/client/animstate.h"
#include "game/localization.h"
#include "menus.h"

void CMenus::RenderSettingsCustom(CUIRect MainView)
{
	const float LineSize = 20.0f;
	const float ColorPickerLineSize = 25.0f;
	const float HeadlineFontSize = 20.0f;
	const float HeadlineHeight = 30.0f;
	const float MarginSmall = 5.0f;
	const float MarginBetweenViews = 20.0f;

	const float ColorPickerLabelSize = 13.0f;
	const float ColorPickerLineSpacing = 5.0f;

	CUIRect Label, Button, LeftSide, RightSide, Preview;
	MainView.HSplitMid(&LeftSide, &MainView, MarginBetweenViews);
	LeftSide.VSplitMid(&LeftSide, &RightSide, MarginBetweenViews);

	if(g_Config.m_Debug)
	{
		LeftSide.Draw(ColorRGBA(0.f, 1.f, 0.f, 0.1f), 0, 0);
		RightSide.Draw(ColorRGBA(0.f, 0.f, 1.f, 0.1f), 0, 0);
		MainView.Draw(ColorRGBA(1.f, 0.f, 0.f, 0.1f), 0, 0);
	}

	LeftSide.HSplitTop(HeadlineHeight, &Label, &LeftSide);
	Ui()->DoLabel(&Label, Localize("HitBoxes"), HeadlineFontSize, TEXTALIGN_ML);
	LeftSide.HSplitTop(MarginSmall, nullptr, &LeftSide);

	LeftSide.HSplitTop(LineSize, &Button, &LeftSide);
	if(DoButton_CheckBox(&g_Config.m_ClShowTeeHitboxOwn, Localize("Show hitbox of own tee"), g_Config.m_ClShowTeeHitboxOwn, &Button))
		g_Config.m_ClShowTeeHitboxOwn = g_Config.m_ClShowTeeHitboxOwn ? 0 : 1;
	LeftSide.HSplitTop(LineSize, &Button, &LeftSide);
	if(DoButton_CheckBox(&g_Config.m_ClShowTeeHitboxOther, Localize("Show hitbox of other tees"), g_Config.m_ClShowTeeHitboxOther, &Button))
		g_Config.m_ClShowTeeHitboxOther = g_Config.m_ClShowTeeHitboxOther ? 0 : 1;
	const ColorRGBA TeeHitboxInnerColorDefault(1.f, 0.7f, 1.f, 0.3f);
	const ColorRGBA TeeHitboxOuterColorDefault(1.f, 1.f, 0.7f, 0.3f);
	static CButtonContainer s_TeeHitboxInner, s_TeeHitboxOuter;
	DoLine_ColorPicker(&s_TeeHitboxInner, ColorPickerLineSize, ColorPickerLabelSize, ColorPickerLineSpacing, &LeftSide, Localize("Tee hitbox inner color"), &g_Config.m_ClShowTeeHitboxInnerColor, TeeHitboxInnerColorDefault, false, nullptr, true);
	DoLine_ColorPicker(&s_TeeHitboxOuter, ColorPickerLineSize, ColorPickerLabelSize, ColorPickerLineSpacing, &LeftSide, Localize("Tee hitbox outer color"), &g_Config.m_ClShowTeeHitboxOuterColor, TeeHitboxOuterColorDefault, false, nullptr, true);

	LeftSide.HSplitTop(LineSize, &Button, &LeftSide);
	if(DoButton_CheckBox(&g_Config.m_ClShowHammerHitboxOwn, Localize("Show hammer hitbox of own tee"), g_Config.m_ClShowHammerHitboxOwn, &Button))
		g_Config.m_ClShowHammerHitboxOwn = g_Config.m_ClShowHammerHitboxOwn ? 0 : 1;
	LeftSide.HSplitTop(LineSize, &Button, &LeftSide);
	if(DoButton_CheckBox(&g_Config.m_ClShowHammerHitboxOther, Localize("Show hammer hitbox of other tees"), g_Config.m_ClShowHammerHitboxOther, &Button))
		g_Config.m_ClShowHammerHitboxOther = g_Config.m_ClShowHammerHitboxOther ? 0 : 1;
	const ColorRGBA HammerHitboxColorDefault(1.f, 1.f, 1.f, 0.3f);
	static CButtonContainer s_HammerHitbox;
	DoLine_ColorPicker(&s_HammerHitbox, ColorPickerLineSize, ColorPickerLabelSize, ColorPickerLineSpacing, &LeftSide, Localize("Hammer hitbox color"), &g_Config.m_ClShowHammerHitboxColor, HammerHitboxColorDefault, false, nullptr, true);


	// Preview
	CTeeRenderInfo OwnSkinInfo;
	OwnSkinInfo.Apply(m_pClient->m_Skins.Find(g_Config.m_ClPlayerSkin));
	OwnSkinInfo.ApplyColors(g_Config.m_ClPlayerUseCustomColor, g_Config.m_ClPlayerColorBody, g_Config.m_ClPlayerColorFeet);
	OwnSkinInfo.m_Size = 50.0f;

	CTeeRenderInfo DummySkinInfo;
	DummySkinInfo.Apply(m_pClient->m_Skins.Find(g_Config.m_ClDummySkin));
	DummySkinInfo.ApplyColors(g_Config.m_ClDummyUseCustomColor, g_Config.m_ClDummyColorBody, g_Config.m_ClDummyColorFeet);
	DummySkinInfo.m_Size = 50.0f;

	auto DoHitboxPreviewTee = [=](vec2 Pos, vec2 Dir, bool HammerHitbox, bool TeeHitbox, CTeeRenderInfo* Info) {
		if(HammerHitbox)
			RenderTools()->RenderHammerHitbox(Pos, Dir);
		if(TeeHitbox)
			RenderTools()->RenderTeeHitbox(Pos);
		else
			RenderTools()->RenderTee(CAnimState::GetIdle(), Info, 0, Dir, Pos);
	};

	LeftSide.VSplitRight(170.f, &LeftSide, &Preview);
	vec2 Center = vec2(Preview.x, Preview.y);

	// dummies
	vec2 MainTeePos = Center - vec2(40.f, 0.f);
	DoHitboxPreviewTee(MainTeePos, direction(angle(Ui()->MousePos() - MainTeePos)), g_Config.m_ClShowHammerHitboxOwn, g_Config.m_ClShowTeeHitboxOwn, &OwnSkinInfo);
	vec2 DummyTeePos = Center + vec2(40.f, 0.f);
	DoHitboxPreviewTee(DummyTeePos, direction(angle(Ui()->MousePos() - DummyTeePos)), g_Config.m_ClShowHammerHitboxOther, g_Config.m_ClShowTeeHitboxOther, &DummySkinInfo);

	// floor
	Graphics()->TextureClear();
	Graphics()->TextureSet(m_pClient->m_MapImages.GetEntities(MAP_IMAGE_ENTITY_LAYER_TYPE_ALL_EXCEPT_SWITCH));
	Graphics()->BlendNormal();
	Graphics()->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	for(int i = -2; i <= 2; i++)
		RenderTools()->RenderTile(Center.x - (i * 32.f) - 16.f, Center.y + 14.f, TILE_SOLID, 32.f, ColorRGBA(1.0f, 1.0f, 1.0f, 1.0f));
}

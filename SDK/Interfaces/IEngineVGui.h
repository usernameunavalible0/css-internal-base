//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $Workfile:     $
// $Date:         $
// $NoKeywords: $
//=============================================================================//
#if !defined( IENGINEVGUI_H )
#define IENGINEVGUI_H

#ifdef _WIN32
#pragma once
#endif

#include "IVModelRender.h"

class Panel;

enum VGuiPanel_t
{
	PANEL_ROOT = 0,
	PANEL_GAMEUIDLL,
	PANEL_CLIENTDLL,
	PANEL_TOOLS,
	PANEL_INGAMESCREENS,
	PANEL_GAMEDLL,
	PANEL_CLIENTDLL_TOOLS
};

enum PaintMode_t
{
	PAINT_UIPANELS = (1 << 0),
	PAINT_INGAMEPANELS = (1 << 1),
	PAINT_CURSOR = (1 << 2),
};

class IEngineVGui
{
public:
	virtual					~IEngineVGui(void) = 0;
	virtual VPANEL	GetPanel(VGuiPanel_t type) = 0;
	virtual bool			IsGameUIVisible() = 0;
};

namespace I { inline IEngineVGui* EngineVGui = nullptr; }

#endif // IENGINEVGUI_H
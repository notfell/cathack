#pragma once

//#define DEV_BUILD

#define PI 3.14159265359f
#define HALF_CIRCLE 180

#define DEFINE_MEMBER(type, name, offset) struct { char pad##name[offset]; type name; }

#define WIN32_LEAN_AND_MEAN
#define isKeyPressed(key) GetAsyncKeyState(key) & 0x8000
#define isKeyReleased(key) GetAsyncKeyState(key) & 0x1

#define PLAYER_BASE 0x10F4F4
#define ENTITIES_LIST_BASE 0x10F4F8
#define PLAYER_POSITION 0x34

#define PLAYER_ROTATION 0x40

#define VIEW_MATRIX 0x101AE8

// win lib
#include <vector>
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <filesystem>
#include <fstream>
#include <shlobj_core.h>
#include <atlbase.h>
#include <functional>
#include <math.h>
#include <shellapi.h>
#include <urlmon.h>

#include "structs.h"

// proc
#include "proc/proc.h"

// mem
#include "mem/mem.h"

// game
#include "game/game.h"
#include "game/entity/entity.h"
#include "game/world/world.h"

// gui
#include "gui/gui.h"
#include "gui/components/components.h"

#include "d2doverlay/includes/DirectOverlay.h"

// utils
#include "utils/utils.h"

// discord
#include "discord/discord.h"
#include <discord_register.h>
#include <discord_rpc.h>

// modules
#include "modules/modules.h"

#include "modules/aim/aim.h"
#include "modules/visuals/visuals.h"
#include "modules/misc/misc.h"

// cli
#include "cli/cli.h"

// main
#include "main/main.h"

// protect
#include "protect/security.h"

// lib
#pragma comment(lib, "urlmon.lib")
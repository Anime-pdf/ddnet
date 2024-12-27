/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */

// This file can be included several times.

#ifndef MACRO_CONFIG_INT
#error "The config macros must be defined"
#define MACRO_CONFIG_INT(Name, ScriptName, Def, Min, Max, Save, Desc) ;
#define MACRO_CONFIG_COL(Name, ScriptName, Def, Save, Desc) ;
#define MACRO_CONFIG_STR(Name, ScriptName, Len, Def, Save, Desc) ;
#endif

MACRO_CONFIG_INT(ClShowHookCollOwnOverride, cl_show_hook_coll_own_override, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Override server's GAMEINFOFLAG_ALLOW_HOOK_COLL flag")

MACRO_CONFIG_INT(ClApplySoloOnUnique, cl_apply_solo_unique, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Make client think everyone has solo modificator on unique servers")

MACRO_CONFIG_COL(ClShowTeeHitboxInnerColor, cl_show_tee_hitbox_inner_color, 0xFFB3FE4D, CFGFLAG_CLIENT | CFGFLAG_SAVE | CFGFLAG_COLALPHA, "Own tee hitbox inner circle color");
MACRO_CONFIG_COL(ClShowTeeHitboxOuterColor, cl_show_tee_hitbox_outer_color, 0xFEFFB34D, CFGFLAG_CLIENT | CFGFLAG_SAVE | CFGFLAG_COLALPHA, "Own tee hitbox outer circle color");
MACRO_CONFIG_INT(ClShowTeeHitboxOwn, cl_show_tee_hitbox_own, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show hitbox of local tee")
MACRO_CONFIG_INT(ClShowTeeHitboxOther, cl_show_tee_hitbox_other, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show hitbox of other tees")

MACRO_CONFIG_COL(ClShowHammerHitboxColor, cl_show_hammer_hitbox_color, 0xFFFFFF4D, CFGFLAG_CLIENT | CFGFLAG_SAVE | CFGFLAG_COLALPHA, "Hammer hitbox color");
MACRO_CONFIG_INT(ClShowHammerHitboxOwn, cl_show_hammer_hitbox_own, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show hitbox of hammer for local tee")
MACRO_CONFIG_INT(ClShowHammerHitboxOther, cl_show_hammer_hitbox_others, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show hitbox of hammer for other tees")

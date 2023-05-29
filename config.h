/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int barmargin      = 8;
static const unsigned int borderpx       = 2;        /* border pixel of windows */
static const unsigned int gappx          = 0;        /* gaps between windows */
static const unsigned int snap           = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 0;        /* 0 means no systray */
static const int showbar                 = 1;        /* 0 means no bar */
static const int topbar                  = 1;        /* 0 means bottom bar */
static const char *fonts[]               = { "Terminus:size=12:style=Bold", "Glyph:size=12", "Cozette:size=12:antialias=false", "Symbols Nerd Font Mono:size=12:antialias=false", "DungGeunMo:size=12:antialias=false" };
static const int focusonwheel            = 1;
static const char dmenufont[]            = "Terminus:size=12:style=Bold";
static char color0[]                     = "#000000";
static char color1[]                     = "#000000";
static char color2[]                     = "#000000";
static char color3[]                     = "#000000";
static char color4[]                     = "#000000";
static char color5[]                     = "#000000";
static char color6[]                     = "#000000";
static char color7[]                     = "#000000";
static char color8[]                     = "#ffffff";
static char color9[]                     = "#ffffff";
static char color10[]                    = "#ffffff";
static char color11[]                    = "#ffffff";
static char color12[]                    = "#ffffff";
static char color13[]                    = "#ffffff";
static char color14[]                    = "#ffffff";
static char color15[]                    = "#ffffff";
static char *colors[][3] = {
	/*                     fg       bg       border  */
	[SchemeNorm]       = { color15, color0,  color8  },
	[SchemeSel]        = { color0,  color15, color15 },
	[SchemeUrgentNorm] = { color9,  color0,  color9  },
	[SchemeUrgentSel]  = { color0,  color9,  color9  },
	[SchemeBar0]       = { color15, color0,  color0  },
	[SchemeBar1]       = { color9,  color0,  color0  },
	[SchemeBar2]       = { color10, color0,  color0  },
	[SchemeBar3]       = { color11, color0,  color0  },
	[SchemeBar4]       = { color12, color0,  color0  },
	[SchemeBar5]       = { color13, color0,  color0  },
	[SchemeBar6]       = { color14, color0,  color0  },
	[SchemeSymbol]     = { color0,  color10, color15 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "class",    NULL,       NULL,       0,            0,           -1 },
	{ "discord",  NULL,       NULL,       1 << 3,       0,           -1 },
	{ "webcord",  NULL,       NULL,       1 << 3,       0,           -1 },
	{ "WebCord",  NULL,       NULL,       1 << 3,       0,           -1 },
	{ "Unity",    NULL,       NULL,       1 << 1,       0,           -1 },
	{ "unityhub", NULL,       NULL,       1 << 1,       0,           -1 },
	{ "Godot",    NULL,       NULL,       1 << 1,       0,           -1 },
	{ "Godot Engine", NULL,   NULL,       1 << 1,       0,           -1 },
};

/* layout(s) */
static const float mfact        = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;   /* number of clients in master area */
static const int resizehints    = 1;   /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0;   /* 1 will force focus on the fullscreen window */


static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "=",      tile },    /* first entry is default */
	{ " ",      NULL },    /* no layout function means floating behavior */
	{ "[",      monocle },
	{ "@",      spiral },
	{ "\\",     dwindle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]      = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", color10, "-nf", color0, "-sb", color15, "-sf", color0, NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	/* bar */
	{ MODKEY,                       XK_v,      togglebar,      {0} },
	
	/* window focusing */
	{ MODKEY,                       XK_n,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_e,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_p,      zoom,           {0} },

	/* window positioning */
	{ MODKEY,                       XK_l,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_m,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_comma,  setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0 } },

	/* window interaction */
	{ MODKEY,                       XK_f,      togglefullscreen, {0} },
	{ MODKEY,                       XK_w,      killclient,     {0} },

	/* tagging */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_0,                      9)
	TAGKEYS(                        XK_minus,                  10)
	TAGKEYS(                        XK_equal,                  11)
	{ MODKEY,                       XK_grave,  view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_grave,  tag,            {.ui = ~0 } },

	/* Emergency quitting */
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


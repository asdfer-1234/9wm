/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int barmargin = 4;
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 0;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=12", "Symbols Nerd Font Mono:size=12" };
static const int focusonwheel       = 1;
static const char dmenufont[]       = "monospace:size=12";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char color0[]                = "#ffffff";
static char color1[]                = "#ffffff";
static char color2[]                = "#ffffff";
static char color3[]                = "#ffffff";
static char color4[]                = "#ffffff";
static char color5[]                = "#ffffff";
static char color6[]                = "#ffffff";
static char color7[]                = "#ffffff";
static char color8[]                = "#ffffff";
static char color9[]                = "#ffffff";
static char color10[]               = "#ffffff";
static char color11[]               = "#ffffff";
static char color12[]               = "#ffffff";
static char color13[]               = "#ffffff";
static char color14[]               = "#ffffff";
static char color15[]               = "#ffffff";
static char *colors[][3] = {
	/*               fg           bg           border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
	[SchemeBar0] = { color9,      normbgcolor, normbordercolor },
	[SchemeBar1] = { color10,     normbgcolor, normbordercolor },
	[SchemeBar2] = { color11,     normbgcolor, normbordercolor },
	[SchemeBar3] = { color12,     normbgcolor, normbordercolor },
	[SchemeBar4] = { color13,     normbgcolor, normbordercolor },
	[SchemeBar5] = { color14,     normbgcolor, normbordercolor },
	[Scheme0]    = { color0,      normbgcolor, normbordercolor },
	[Scheme1]    = { color1,      normbgcolor, normbordercolor },
	[Scheme2]    = { color2,      normbgcolor, normbordercolor },
	[Scheme3]    = { color3,      normbgcolor, normbordercolor },
	[Scheme4]    = { color4,      normbgcolor, normbordercolor },
	[Scheme5]    = { color5,      normbgcolor, normbordercolor },
	[Scheme6]    = { color6,      normbgcolor, normbordercolor },
	[Scheme7]    = { color7,      normbgcolor, normbordercolor },
	[Scheme8]    = { color8,      normbgcolor, normbordercolor },
	[Scheme9]    = { color9,      normbgcolor, normbordercolor },
	[Scheme10]   = { color10,     normbgcolor, normbordercolor },
	[Scheme11]   = { color11,     normbgcolor, normbordercolor },
	[Scheme12]   = { color12,     normbgcolor, normbordercolor },
	[Scheme13]   = { color13,     normbgcolor, normbordercolor },
	[Scheme14]   = { color14,     normbgcolor, normbordercolor },
	[Scheme15]   = { color15,     normbgcolor, normbordercolor },
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
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */


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
static const char *dmenucmd[]   = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]    = { "st", NULL };
static const char *firefoxcmd[] = { "firefox", NULL };

static const char *upvol[]   = { "amixer", "-q", "set", "Master", "5%+", "unmute", NULL };
static const char *downvol[] = { "amixer", "-q", "set", "Master", "5%-", "unmute", NULL };
static const char *mutevol[] = { "amixer", "-q", "set", "Master", "toggle", NULL };
static const char *updatebar[]={ "bash" "~/computer/packages/suckless/dwm-bar/dwm_bar_onetime.sh" };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_a,      spawn,          {.v = firefoxcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_m,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_comma,  setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_p,      zoom,           {0} },
	{ MODKEY,                       XK_w,      killclient,     {0} },
	{ MODKEY,                       XK_asciitilde,  view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_asciitilde,  tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0 } },
	{ MODKEY,                       XK_f,      togglefullscreen, {0} },
	{ MODKEY,                       XK_t,      spawn,          {.v = upvol} },
	{ MODKEY,                       XK_g,      spawn,          {.v = downvol} },
	{ MODKEY,                       XK_v,      spawn,          {.v = mutevol} },
	{ MODKEY,                       XK_z,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_x,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[4]} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


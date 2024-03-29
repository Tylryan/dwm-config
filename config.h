/* See LICENSE file for copyright and license details. */

// TODO: Fix tag bindings
//
/* appearance */
static const unsigned int borderpx   = 2;        /* border pixel of windows */
static const unsigned int fborderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx      = 6;        /* gaps between windows */

static const unsigned int snap       = 32;       /* snap pixel */
static const int showbar             = 1;        /* 0 means no bar */
static const int topbar              = 1;        /* 0 means bottom bar */
static const char *fonts[]           = { "FontAwesome:size=13" };
static const char dmenufont[]        = "FontAwesome:size=13";
static const char col_gray1[]        = "#222222";
static const char col_gray2[]        = "#444444";
static const char col_gray3[]        = "#bbbbbb";
static const char col_gray4[]        = "#eeeeee";
static const char col_cyan[]         = "#005577";
static const char *colors[][3]       = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray1,  col_cyan  },
};

#include <X11/XF86keysym.h>

// Volume
static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%",     NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%",     NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL };


/* tagging */
static const char *tags[] = { "1", "2", "3", "4"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Galculator",  NULL,       NULL,       0,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALT    Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *browser[]  = { "firefox", NULL };
static const char *screenshot[]  = { "gnome-terminal -a -c", NULL };
static const char *lock_suspend[] = {"bash", "-c", "i3lock --color 000000 && systemctl suspend"};

static Key keys[] = {
	/* modifier                     key        function        argument */
    // Applications
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             		    XK_Return, spawn,          {.v = termcmd  } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = browser  } },
	{ MODKEY,                       XK_x,      spawn,          {.v = lock_suspend} },
	{ MODKEY,                       XK_s,      spawn,          {.v = screenshot} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
    // TODO: Focus window panes. There must be a better way
	{ MODKEY,                       XK_h,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_l,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },		    // Horizontal Layout
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },		    // Vertical Layout
	{ MODKEY,                       XK_u,      setmfact,       {.f = -0.05} },		    // Increase Window Size
	{ MODKEY,                       XK_o,      setmfact,       {.f = +0.05} },		    // Decrease Window Size
    // TODO: Better window swapper
	{ MODKEY|ShiftMask,             XK_j, 	   zoom,           {0} },                   // Swap windows panes (Only works for two windows)
	{ MODKEY,                       XK_Tab,    view,           {0} },                   // Switch to previous tag/window
	{ MODKEY,             		    XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },	// Tile
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} }, 	// Floating
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },	// Full-screen
	{ MODKEY,                       XK_space,  setlayout,      {0} },			        // Set Layout to Previous Layout
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ ControlMask|ALT,              XK_h,      viewtoleft,     {-1} },                  // Previous workspace (tag)
	{ ControlMask|ALT,              XK_l,      viewtoright,    {0} },                   // Next workspace (tag)
	{ ALT|ShiftMask,                XK_h,      tagtoleft,      {0} },                   // Send this workspace to the right one
	{ ALT|ShiftMask,                XK_l,      tagtoright,     {0} },                   // Send this workspace to the left one
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },            // Focus Previous Monitor?
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },            // Focus Next Monitor?
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	// VOLUME CONTROL
	{ 0,                       XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
	{ 0,                       XF86XK_AudioMute, spawn, 	   {.v = mutevol } },
	{ 0,                       XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } },
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
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


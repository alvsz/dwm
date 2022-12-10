/* See LICENSE file for copyright and license details. */

/* appearance */
static const char *fonts[]      = { "SF Mono:style=medium:size=11", "Siji:size=14","Iosevka:size=18" };
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */

/* ----------------- gaps ---------------- */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */

/* ----------------- bar ----------------- */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int usealtbar          = 1;        /* 1 means use non-dwm status bar */
static const char *altbarclass      = "eww-bar"; /* Alternate bar class name */
static const char *altbarcmd        = "$HOME/.config/dwm/bar.sh"; /* Alternate bar launch command */

/* ------------- colorscheme ------------- */
#include "/home/mamba/.cache/wal/colors-wal-c.h"
static char *colors[][3]        = {
	/*                        fg             bg              border  */
	[SchemeNorm]        = { foreground,    background,     background  },
	[SchemeSel]         = { color15,       background,     color15     },
	[SchemeScratchSel]  = { color14,       background,     color14     },
	[SchemeScratchNorm] = { color8,        background,     color8      },
};

/* -------------- tags ----------------- */
static const char *tags[]       = { "", "爵", "", "", "", "", "屢" };

#define APP_TERM                "st"
#define CLASS_SP                "ScratchPad"
#define TITLE_SP                "scratchpad"

#include "/home/mamba/.config/dwm/rules.h"

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",        tile },                     /* Default: Master on left, Slaves on right */
	{ "",        NULL },                     /* No layout function means floating behaviour */
	{ "",        monocle },                  /* All windows on top of each other */
	{ "",        centeredmaster },           /* Master in middle, Slaves on sides */
	{ "[@]",      spiral },                   /* Fibonacci spiral 
	{ "|C|",      centeredfloatingmaster },   /* Same as centeredmaster but Master floats 
	{ "|D|",      deck },                     /* Master on left, Slaves in monocle-like mode on right 
	{ "[G]",      grid },                     /* Grid layout 
	{ "|@|",      dwindle },                  /* Decreasing in size right and leftward 
	{ "|B|",      bstack },                   /* Master on top, Slaves on bottom 
	{ "|G|",      gaplessgrid },              /* Grid layout but without gaps */
	{ NULL,       NULL },
};

/* ----------- key definitions ----------- */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* --------------- commands -------------- */
/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* first arg only serves to match against key in rules */
static const char *scratchcmd[] = { "t", APP_TERM, "-c", CLASS_SP, "-t", TITLE_SP, NULL };
static const char *scratchspt[] = { "s", APP_TERM, "-c", CLASS_SP, "-t", "spotify", "-e", "spt", NULL };
static const char *scratchtry[] = { "a", "stalonetray", NULL };

static const char *termcmd[] = { APP_TERM, NULL };
static const char *tabterm[] = { "tabbed", "-n", "terminal", "-c", "-k", "-r 2", APP_TERM, "-w", "''", NULL };

/* ------------- keybindings ------------- */
#include <X11/XF86keysym.h>

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_Return,  spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_t,       spawn,          {.v = tabterm } },
	{ MODKEY,                       XK_d,       spawn,          SHCMD("rofi -show drun -theme spotlight-dark") },
	{ MODKEY|ShiftMask,             XK_q,       quit,           {1} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,       quit,           {0} },
	{ MODKEY|ShiftMask,             XK_l,       spawn,          SHCMD("loginctl lock-session") },
	
	/* ---------- layouts ---------- */
	{ MODKEY,                       XK_u,       setlayout,      {.v = &layouts[0] } }, /* tile */
	{ MODKEY,                       XK_i,       setlayout,      {.v = &layouts[3] } }, /* centeredmaster */
	{ MODKEY,                       XK_o,       setlayout,      {.v = &layouts[2] } }, /* monocle */
	{ MODKEY|ShiftMask,             XK_space,   setlayout,      {.v = &layouts[1] } }, /* floating */
	{ MODKEY|ShiftMask,             XK_p,       cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,   togglefloating, {0} },
	
	/* ------------ gaps ----------- */
	{ MODKEY|ShiftMask,             XK_equal,   togglegaps,     {0} },        /* toggle  gaps */
	{ MODKEY|ShiftMask,             XK_minus,   defaultgaps,    {0} },        /* reset   gaps */
	{ MODKEY,                       XK_minus,   incrgaps,       {.i = -1 } }, /* dec all gaps */
	{ MODKEY,                       XK_equal,   incrgaps,       {.i = +1 } }, /* inc all gaps */
	{ MODKEY|ControlMask,           XK_Left,    incrovgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_Right,   incrovgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_Up,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_Down,    incrohgaps,     {.i = +1 } },
	
	/* ----------- stack ----------- */
	{ MODKEY,                       XK_q,       killclient,     {0} },
	{ MODKEY,                       XK_Up,      rotatestack,    {.i = +1 } },
	{ MODKEY,                       XK_Down,    rotatestack,    {.i = -1 } },
	{ Mod1Mask,                     XK_Tab,     focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Up,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Down,    incnmaster,     {.i = -1 } },
	
	/* ----------- resize ---------- 
	{ MODKEY,                       XK_space,   togglefloating,          {0} },
	{ MODKEY|ShiftMask,             XK_f,       togglefullscreen,        {0} },
	{ MODKEY|ControlMask,           XK_f,       togglefakefullscreen,    {0} }, */
	{ MODKEY,                       XK_Left,    setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_Right,   setmfact,       {.f = +0.05} },

	/* ------------ bar ------------ */
	//	{ MODKEY,                       XK_p,       togglebar,      {0} },
       	{ MODKEY,                       XK_p,       spawn,      SHCMD("eww windows | grep -o '*bar' && eww close bar || eww open bar") },
	
	/* ---------- monitor ---------- */
	{ MODKEY,                       XK_comma,   focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,  tagmon,         {.i = +1 } },

	/* --------- scratchpad -------- */
	{ MODKEY|ControlMask,           XK_x,       setscratch,     {.v = scratchcmd } },
	{ MODKEY|ShiftMask,             XK_x,       removescratch,  {.v = scratchcmd } },
	{ MODKEY,                       XK_x,       togglescratch,  {.v = scratchcmd } },
	{ MODKEY,                       XK_s,       togglescratch,  {.v = scratchspt } },
	{ MODKEY|ShiftMask,             XK_t,       togglescratch,  {.v = scratchtry } },

	/* ------------ tag ------------ */
	{ MODKEY,                       XK_0,       view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,       tag,            {.ui = ~0 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)

	/* ---------- keyboard --------- */
	#include "/home/mamba/.config/dwm/keys.h"
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    viewnext,       {0} },
	{ MODKEY|ShiftMask,             XK_Tab,       shiftviewclients, { .i = +1 } },
	{ MODKEY|ShiftMask,             XK_backslash, shiftviewclients, { .i = -1 } },
	{ MODKEY|ShiftMask,             XK_Right,  tagtonext,      {0} },
	{ MODKEY|ShiftMask,             XK_Left,   tagtoprev,      {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button3,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button2,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY|ShiftMask,         Button1,        dragmfact,      {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
  IPCCOMMAND(  view,                1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggleview,          1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tag,                 1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggletag,           1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tagmon,              1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  focusmon,            1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  focusstack,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  zoom,                1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  incnmaster,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  killclient,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  togglefloating,      1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  setmfact,            1,      {ARG_TYPE_FLOAT}  ),
  IPCCOMMAND(  setlayoutsafe,       1,      {ARG_TYPE_PTR}    ),
  IPCCOMMAND(  quit,                1,      {ARG_TYPE_NONE}   )
};


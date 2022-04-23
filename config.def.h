/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;         /* border pixel of windows */
static const unsigned int snap      = 32;        /* snap pixel */
static const unsigned int gappih    = 10;        /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;        /* vert inner gap between windows */
static const unsigned int gappoh    = 10;        /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;        /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;         /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;         /* 0 means no bar */
static const int usealtbar          = 1;         /* 1 means use non-dwm status bar */
static const char *altbarclass      = "Polybar"; /* Alternate bar class name */
static const char *altbarcmd        = "/home/mamba/.config/polybar/bar.sh"; /* Alternate bar launch command */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 0;        /* vertical padding of bar */
static const int sidepad            = 0;        /* horizontal padding of bar */
static const char *fonts[]          = { "Cantarell:size=13", "Iosevka:size=14" };
static const char dmenufont[]       = "Cantarell:size=13";

#include "/home/mamba/.cache/wal/colors-wal-dwm.h"
#include <X11/XF86keysym.h>

/* tagging */
static const char *tags[] = { "", "爵", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                            instance         title                 tags mask     isfloating   monitor */
	{ "Pwcalculator",                   NULL,            NULL,                 0,            1,           -1 },
	{ "Qalculate-gtk",                  NULL,            NULL,                 0,            1,           -1 },
	{ "st-256color",                    NULL,            NULL,                 1,            0,           -1 },
	{ "firefox",                        NULL,            NULL,                 1 << 1,       0,           -1 },
	{ "librewolf",                      NULL,            NULL,                 1 << 1,       0,           -1 },
	{ NULL,                             "Places",        NULL,                 1 << 1,       1,           -1 },
	{ "Com.github.gabutakut.gabutdm",   NULL,            NULL,                 1 << 1,       0,           -1 },
	{ "Gedit",                          NULL,            NULL,                 1 << 2,       0,           -1 },
	{ NULL,                             "libreoffice",   NULL,                 1 << 2,       0,           -1 },
	{ "Gimp",                           NULL,            NULL,                 1 << 2,       0,           -1 },
	{ "Org.gnome.Nautilus",             NULL,            NULL,                 1 << 3,       0,           -1 },
	{ "Geary",                          NULL,            NULL,                 1 << 4,       0,           -1 },
	{ "discord",                        NULL,            NULL,                 1 << 4,       0,           -1 },
	{ "Lutris",                         NULL,            NULL,                 1 << 5,       0,           -1 },
	{ "Steam",                          NULL,            NULL,                 1 << 5,       0,           -1 },
	{ "Steam",                          NULL,            "Lista de amigos",    1 << 5,       1,           -1 },
	{ "Steam",                          NULL,            "Steam — Novidades",  1 << 5,       1,           -1 },
	{ "Rare",                           NULL,            NULL,                 1 << 5,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",        spiral },
	{ "",        NULL },    /* no layout function means floating behavior */
	{ "|M|",      centeredmaster },
	{ "[M]",      monocle },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "[]=",      tile },    /* first entry is default */
	{ ">M>",      centeredfloatingmaster },
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
static const char *dmenucmd[]          = { "dmenu_run_i", "-i", "-l", "7", "-g", "2", "-h", "30", "-bw", "5", "-fn", dmenufont, "-p", "Executar:⠀", "-sb", sel_bg, "-sf", sel_fg, NULL };
static const char *clipmenucmd[]       = { "clipmenu",    "-i", "-l", "7", "-g", "2", "-h", "30", "-bw", "5", "-i", "-fn", dmenufont, "-sb", sel_bg, "-sf", sel_fg, NULL };
static const char *termcmd[]           = { "st", NULL };

static const char *audiostop[]         = { "playerctl", "stop", NULL };
static const char *audioprev[]         = { "playerctl", "previous", NULL };
static const char *audioplay[]         = { "playerctl", "play-pause", NULL };
static const char *audionext[]         = { "playerctl", "next", NULL };

static const char *explorer[]          = { "nautilus", NULL };
static const char *homepage[]          = { "firefox", NULL };
static const char *mail[]              = { "org.gnome.Geary", NULL };
static const char *calculator[]        = { "io.github.Qalculate", NULL };

static const char *tools[]             = { "spot", NULL };
static const char *audiolowervolume[]  = { "pactl", "set-sink-volume", "0", "-5%",     NULL };
static const char *audioraisevolume[]  = { "pactl", "set-sink-volume", "0", "+5%",     NULL };
static const char *audiomute[]         = { "pactl", "set-sink-mute",   "0", "toggle",  NULL };

static const char *printcis[]          = { "gnome-screenshot", NULL };
static const char *printtrans[]        = { "gnome-screenshot", "-c", NULL };
static const char *printareacis[]      = { "gnome-screenshot", "-a", NULL };
static const char *printareatrans[]    = { "gnome-screenshot", "-a", "-c", NULL };
static const char *printgui[]          = { "gnome-screenshot", "-i", NULL };

static Key keys[] = {
	/* modifier                     key                         function        argument */
	{ MODKEY,                       XK_d,                       spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,                  spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_t,                       spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_v,                       spawn,          {.v = clipmenucmd } },
	
	{ 0,                            XF86XK_AudioStop,           spawn,          {.v = audiostop } },
	{ 0,                            XF86XK_AudioPrev,           spawn,          {.v = audioprev } },
	{ 0,                            XF86XK_AudioPlay,           spawn,          {.v = audioplay } },
	{ 0,                            XF86XK_AudioNext,           spawn,          {.v = audionext } },
	{ MODKEY,                       XK_j,                       spawn,          {.v = audioprev } },
	{ MODKEY,                       XK_k,                       spawn,          {.v = audioplay } },
	{ MODKEY,                       XK_l,                       spawn,          {.v = audionext } },

	{ 0,                            XF86XK_Explorer,            spawn,          {.v = explorer } },
	{ 0,                            XF86XK_HomePage,            spawn,          {.v = homepage } },
	{ 0,                            XF86XK_Mail,                spawn,          {.v = mail } },
	{ 0,                            XF86XK_Calculator,          spawn,          {.v = calculator } },
	{ MODKEY,                       XK_f,                       spawn,          {.v = explorer } },
	{ MODKEY,                       XK_b,                       spawn,          {.v = homepage } },
	{ MODKEY,                       XK_e,                       spawn,          {.v = mail } },

	{ 0,                            XF86XK_Tools,               spawn,          {.v = tools } },
	{ 0,                            XF86XK_AudioMute,           spawn,          {.v = audiomute } },
	{ 0,                            XF86XK_AudioLowerVolume,    spawn,          {.v = audiolowervolume } },
	{ 0,                            XF86XK_AudioRaiseVolume,    spawn,          {.v = audioraisevolume } },
	
	{ 0,                            XK_Print,                   spawn,          {.v = printcis } },
	{ ControlMask,                  XK_Print,                   spawn,          {.v = printtrans } },
	{ ShiftMask,                    XK_Print,                   spawn,          {.v = printareacis } },
	{ ShiftMask|ControlMask,        XK_Print,                   spawn,          {.v = printareatrans } },
	{ MODKEY,                       XK_Print,                   spawn,          {.v = printgui } },

	{ MODKEY,                       XK_p,                       togglebar,      {0} },
	{ MODKEY,                       XK_Up,                      rotatestack,    {.i = +1 } },
	{ MODKEY,                       XK_Down,                    rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_Right,                   focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Left,                    focusstack,     {.i = -1 } },
	{ Mod1Mask,                     XK_Tab,                     focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Up,                      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Down,                    incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Left,                    setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_Right,                   setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,                  zoom,           {0} },
	{ MODKEY,                       XK_equal,                   incrgaps,       {.i = +1 } },
	{ MODKEY,                       XK_minus,                   incrgaps,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_equal,                   togglegaps,     {0} },
	{ MODKEY|ShiftMask,             XK_minus,                   defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,                     view,           {0} },
	{ MODKEY,                       XK_q,                       killclient,     {0} },
	{ MODKEY,                       XK_b,                       setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_n,                       setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_m,                       setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,                   setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,                   togglefloating, {0} },
	{ MODKEY,                       XK_0,                       view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                       tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                   focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                  tagmon,         {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_q,                       quit,           {0} },
	{ MODKEY|ShiftMask,             XK_q,                       quit,           {1} },
	
	TAGKEYS(                        XK_1,                                       0)
	TAGKEYS(                        XK_2,                                       1)
	TAGKEYS(                        XK_3,                                       2)
	TAGKEYS(                        XK_4,                                       3)
	TAGKEYS(                        XK_5,                                       4)
	TAGKEYS(                        XK_6,                                       5)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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


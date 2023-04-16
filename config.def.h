/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;         /* border pixel of windows */
static const unsigned int snap      = 10;        /* snap pixel */
static const int swallowfloating    = 0;         /* 1 means swallow floating windows by default */
static const char *fonts[]          = { "monospace:size=10" };

/* ---------------- gaps ----------------- */
static const unsigned int gappih    = 10;        /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;        /* vert inner gap between windows */
static const unsigned int gappoh    = 10;        /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;        /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;         /* 1 means no outer gap when there is only one window */

/* ---------------- bar ------------------ */
static const int showbar            = 1;         /* 0 means no bar */
static const int topbar             = 1;         /* 0 means bottom bar */
static const int usealtbar          = 1;         /* 1 means use non-dwm status bar */
static const char *altbarclass      = "eww-bar";      /* Alternate bar class name */
// static const char *altbartitle      = "Eww - bar";    /* Alternate bar title name */
static const char *altbarcmd        = "$XDG_CONFIG_HOME/dwm/bar.sh"; /* Alternate bar launch command */

/* ------------- colorscheme ------------- */
#include "/home/mamba/.cache/wal/colors-wal-c.h"
static char *colors[][4]        = {
  /*                        fg             bg             border        float  */
  [SchemeNorm]        = { foreground,    background,    background,   background   },
  [SchemeSel]         = { color5,        background,    color5,       foreground   },
  [SchemeUrg]         = { color1,        background,    color1,       color1       },
  [SchemeScratchSel]  = { color6,        background,    color6,       color6       },
  [SchemeScratchNorm] = { color4,        background,    color4,       color4       },
};

/* ------------ tagging ----------------- */
static const char *tags[]       = { "", "爵", "", "", "", "", "屢" };

#define APP_TERM                "alacritty"
#define CLASS_SP                "ScratchPad"
#define TITLE_SP                "scratchpad"

#include "rules.h"

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
  /* symbol     arrange function */
  { "",        tile },    /* first entry is default */
  { "",        NULL },    /* no layout function means floating behavior */
  { "",        monocle },
  { "",        centeredmaster }, /*
  { "[@]",      spiral }, 
  { "[\\]",     dwindle },
  { "H[]",      deck },
  { "TTT",      bstack },
  { "===",      bstackhoriz },
  { "HHH",      grid },
  { "###",      nrowgrid },
  { "---",      horizgrid },
  { ":::",      gaplessgrid },
  { ">M>",      centeredfloatingmaster }, */
  { NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG)						\
  { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
  { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
static const char *roficmd[] = { "rofi", "-show", "drun", NULL };
static const char *termcmd[] = { APP_TERM, NULL };
static const char *tabterm[] = { "tabbed", "-n", "terminal", "-c", "-k", "-r 2", APP_TERM, "--embed", "''", NULL };

/* first arg only serves to match against key in rules */
static const char *scratchcmd[] = { "t", APP_TERM, "--class", CLASS_SP, "-t", TITLE_SP, NULL };
static const char *scratchspt[] = { "s", APP_TERM, "--class", CLASS_SP, "-t", "spotify", "-e", "spt", NULL };
// static const char *scratchcal[] = { "c", APP_TERM, "--class", CLASS_SP, "-t", "calendar", "-e", "calcurse", NULL };
static const char *scratchcal[] = { "c", "eww", "open", "pwcalc", NULL };
// static const char *scratchtry[] = { "a", "stalonetray", NULL };

#include <X11/XF86keysym.h>

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static const Key keys[] = {
#include "keys.h"
  /* modifier                     key          function        argument */
  { MODKEY|ShiftMask,             XK_Tab,      view,           {0} },
	
  { MODKEY,                       XK_u,        setlayout,      {.v = &layouts[0] } }, /* tile */
  { MODKEY,                       XK_i,        setlayout,      {.v = &layouts[3] } }, /* centeredmaster */
  { MODKEY,                       XK_o,        setlayout,      {.v = &layouts[2] } }, /* monocle */
  { MODKEY|ShiftMask,             XK_space,    setlayout,      {.v = &layouts[1] } }, /* floating */
	
  /* ------------ bar ------------ */
  { MODKEY,                       XK_p,       spawn,              SHCMD("eww open bar --toggle") },
	
  /* --------- scratchpad -------- */
  { MODKEY|ControlMask,           XK_x,        toggleinscratch,   {.v = scratchcmd } },
  { MODKEY,                       XK_x,        togglescratch,     {.v = scratchcmd } },
  { MODKEY,                       XK_s,        togglescratch,     {.v = scratchspt } },
  { MODKEY,                       XK_w,        togglescratch,     {.v = scratchcal } },
  // { MODKEY|ShiftMask,             XK_t,        togglescratch,     {.v = scratchtry } },

  { MODKEY,                       XK_Tab,      viewnext,       {0} },
  { MODKEY|ShiftMask,             XK_Right,    tagtonext,      {0} },
  { MODKEY|ShiftMask,             XK_Left,     tagtoprev,      {0} },

  TAGKEYS(                        XK_1,        0)
  TAGKEYS(                        XK_2,        1)
  TAGKEYS(                        XK_3,        2)
  TAGKEYS(                        XK_4,        3)
  TAGKEYS(                        XK_5,        4)
  TAGKEYS(                        XK_6,        5)
  TAGKEYS(                        XK_7,        6)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
  /* click                event mask          button          function         argument */
  { ClkLtSymbol,          0,                  Button1,        setlayout,       {0} },
  { ClkLtSymbol,          0,                  Button3,        setlayout,       {.v = &layouts[2]} },
  { ClkWinTitle,          0,                  Button2,        zoom,            {0} },
  { ClkStatusText,        0,                  Button2,        spawn,           {.v = termcmd } },
	
  { ClkClientWin,         MODKEY,             Button1,        movemouse,       {0} },
  { ClkClientWin,         MODKEY,             Button3,        togglefloating,  {0} },
  { ClkClientWin,         MODKEY,             8,              toggleinscratch, {.v = scratchcmd } },
  { ClkClientWin,         MODKEY,             Button2,        resizemouse,     {0} },
  { ClkClientWin,         MODKEY|ShiftMask,   Button1,        dragmfact,       {0} },
  { ClkClientWin,         MODKEY,             Button4,        incnmaster,      {.i = +1 } },
  { ClkClientWin,         MODKEY,             Button5,        incnmaster,      {.i = -1 } },
  { ClkRootWin,           0,                  Button3,        spawn,           SHCMD("jgmenu_run") },
  { ClkRootWin,           0,                  8,              spawn,           {.v = roficmd } },
	
  { ClkTagBar,            0,                  Button1,        view,            {0} },
  { ClkTagBar,            0,                  Button3,        toggleview,      {0} },
  { ClkTagBar,            MODKEY,             Button1,        tag,             {0} },
  { ClkTagBar,            MODKEY,             Button3,        toggletag,       {0} },
};

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signum>"` */
static Signal signals[] = {
  /* signum       function        argument  */
  { 1,            togglescratch,  {.v = scratchcmd } },
  { 2,            togglescratch,  {.v = scratchspt } },
  { 3,            togglescratch,  {.v = scratchcal } },
  // { 4,            togglescratch,  {.v = scratchtry } },
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
  IPCCOMMAND(  zoom,                1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  incnmaster,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  killclient,          1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  togglefloating,      1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  setmfact,            1,      {ARG_TYPE_FLOAT}  ),
  IPCCOMMAND(  setlayoutsafe,       1,      {ARG_TYPE_PTR}    ),
  IPCCOMMAND(  quit,                1,      {ARG_TYPE_NONE}   )
};


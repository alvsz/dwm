	{ MODKEY|ShiftMask,    XK_Return,                   spawn,          {.v = termcmd } },
	{ MODKEY,              XK_t,                        spawn,          {.v = tabterm } },
	{ MODKEY,              XK_d,                        spawn,          SHCMD("rofi -show drun") },
	{ MODKEY|ShiftMask,             XK_q,               quit,           {1} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,               quit,           {0} },
	{ MODKEY|ShiftMask,             XK_l,               spawn,          SHCMD("loginctl lock-session") },
	  
	{ MODKEY,               XK_q,                       killclient,     {0} },
	  
	/* ----------- stack ----------- */
	{ MODKEY,               XK_Up,                      rotatestack,    {.i = -1 } },
	{ MODKEY,               XK_Down,                    rotatestack,    {.i = +1 } },
	{ Mod1Mask,             XK_Tab,                     focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_Up,                      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_Down,                    incnmaster,     {.i = -1 } },
        { MODKEY,               XK_Return,                  zoom,           {0} },

	/* ----------- resize ---------- */
	{ MODKEY,               XK_Left,                    setmfact,       {.f = -0.05} },
	{ MODKEY,               XK_Right,                   setmfact,       {.f = +0.05} },
	{ MODKEY,               XK_space,                   togglefloating,          {0} },
	  
	/* ---------- monitor ---------- */
	{ MODKEY,               XK_comma,                   focusmon,       {.i = -1 } },
	{ MODKEY,               XK_period,                  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_comma,                   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,     XK_period,                  tagmon,         {.i = +1 } },

	/* ------------ gaps ----------- */
	{ MODKEY|ShiftMask,     XK_equal,                   togglegaps,     {0} },        /* toggle  gaps */
	{ MODKEY|ShiftMask,     XK_minus,                   defaultgaps,    {0} },        /* reset   gaps */
	{ MODKEY,               XK_minus,                   incrgaps,       {.i = -1 } }, /* dec all gaps */
	{ MODKEY,               XK_equal,                   incrgaps,       {.i = +1 } }, /* inc all gaps */
	{ MODKEY|ControlMask,   XK_Left,                    incrovgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,   XK_Right,                   incrovgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,   XK_Up,                      incrohgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,   XK_Down,                    incrohgaps,     {.i = +1 } },
	  
	/* ----------- other ----------- */
	{ MODKEY,               XK_0,                       view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,     XK_0,                       tag,            {.ui = ~0 } },

       	{ MODKEY,               XK_r,                       spawn,          SHCMD("eww windows | grep -o '*dashboard' && eww close dashboard || eww open dashboard") },
       	{ MODKEY,               XK_c,                       spawn,          SHCMD("eww windows | grep -o '*calendar' && eww close calendar || eww open calendar") },
	  
	{ 0,                    XF86XK_AudioStop,           spawn,          SHCMD("playerctl stop") },
	{ 0,                    XF86XK_AudioPrev,           spawn,          SHCMD("midia previous") },
	{ 0,                    XF86XK_AudioPlay,           spawn,          SHCMD("midia play-pause") },
	{ 0,                    XF86XK_AudioNext,           spawn,          SHCMD("midia next") },
	{ MODKEY,               XK_j,                       spawn,          SHCMD("midia previous") },
	{ MODKEY,               XK_k,                       spawn,          SHCMD("midia play-pause") },
	{ MODKEY,               XK_l,                       spawn,          SHCMD("midia next") },

	{ 0,                    XF86XK_AudioMute,           spawn,          SHCMD("volume mute") },
	{ 0,                    XF86XK_AudioLowerVolume,    spawn,          SHCMD("volume down") },
	{ 0,                    XF86XK_AudioRaiseVolume,    spawn,          SHCMD("volume up") },
	{ MODKEY,               XK_F1,                      spawn,          SHCMD("volume mute") },
	{ MODKEY,               XK_F2,                      spawn,          SHCMD("volume down") },
	{ MODKEY,               XK_F3,                      spawn,          SHCMD("volume up") },	

	{ 0,                    XF86XK_MonBrightnessDown,   spawn,          SHCMD("backlight down") },
	{ 0,                    XF86XK_MonBrightnessUp,     spawn,          SHCMD("backlight up") },
	{ MODKEY,               XK_F4,                      spawn,          SHCMD("backlight down") },
	{ MODKEY,               XK_F5,                      spawn,          SHCMD("backlight up") },

	{ 0,                    XF86XK_TouchpadToggle,      spawn,          SHCMD("touchpad") },
	{ MODKEY,               XK_F6,                      spawn,          SHCMD("touchpad") },

	/* ------------ apps ----------- */
	{ MODKEY,               XK_f,                       spawn,          SHCMD("$EXPLORER") },
	{ MODKEY,               XK_b,                       spawn,          SHCMD("$BROWSER") },
	{ MODKEY,               XK_e,                       spawn,          SHCMD("xdg-email") },
	{ MODKEY,               XK_m,                       spawn,          SHCMD("rofi -show emoji -emoji-mode copy") },
	{ MODKEY,               XK_v,                       spawn,          SHCMD("CM_LAUNCHER=rofi clipmenu -i ") },
	{ 0,                    XF86XK_Calculator,          spawn,          SHCMD("$CALCULATOR") },
	{ 0,                    XK_Print,                   spawn,          SHCMD("screenshot") },
	{ ShiftMask,            XK_Print,                   spawn,          SHCMD("screenshot select") },
	{ ControlMask,          XK_Print,                   spawn,          SHCMD("screenshot window") },

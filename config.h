/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappih    = 5;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;       /* vert inner gap between windows */
static const unsigned int gappoh    = 5;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 5;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 4;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Google Sans Medium:size=9", "FuraCode Nerd Font:size=10" };
static const char col_gray1[]       = "#000000";
static const char col_gray2[]       = "#262626";
static const char col_gray3[]       = "#ffffff";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray4, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray2,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "爵", "", "", "", "ﱣ", "ﱣ", "ﱣ", "ﱣ", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "mpv",      NULL,       NULL,       0,       	    1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define MODKEY1 Mod1Mask
#define TAGKEYS(KEY,TAG) \
{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *launcher[]		=	{ "rofi", "-show", "drun", NULL };
static const char *termcmd[]		=	{ "termite", NULL };
static const char *screenshot[]		=	{ "/home/law/apps/scripts/screenshot.sh", NULL };
static const char *screenshotsave[]	=	{ "/home/law/apps/scripts/screenshot.sh", "--save", NULL };
static const char *statusbarupdate[]	=	{ "/home/law/apps/scripts/statusbarnoloop.sh","--ref", NULL };
static const char *audiomute[]		=	{"/home/law/apps/scripts/volume.sh", "--toggle", NULL };
static const char *audioinc[]		=	{"/home/law/apps/scripts/volume.sh", "--inc",  NULL };
static const char *audiodec[]		=	{"/home/law/apps/scripts/volume.sh", "--dec",  NULL };
static const char *brightnessinc[]	=	{ "xbacklight", "-inc" ,"5", NULL };
static const char *brightnessdec[]	=	{ "xbacklight", "-dec" ,"5", NULL };
static const char *mpctoggle[]		=	{ "mpc", "toggle",NULL };
static const char *mpcnext[]		=	{ "mpc", "next",NULL };
static const char *mpcprev[]		=	{ "mpc", "prev",NULL };
static const char *files[]		=	{ "nautilus" ,NULL };
static const char *suspend[]		=	{ "systemctl", "suspend" ,NULL };
static const char *lock[]		=	{ "xsecurelock" ,NULL };

static Key keys[] = {
	/* modifier                     key        			function        argument */
	{ 0,                       	XK_Print,  			spawn,		{.v = screenshot } },
	{ 0,             		XF86XK_AudioMute,		spawn,		{.v = audiomute } },
	{ 0,             		XF86XK_AudioRaiseVolume,	spawn,         	{.v = audioinc } },
	{ 0,             		XF86XK_AudioLowerVolume,	spawn,          {.v = audiodec } },
	{ 0,             		XF86XK_MonBrightnessUp, 	spawn,          {.v = brightnessinc } },
	{ 0,             		XF86XK_MonBrightnessDown,	spawn,          {.v = brightnessdec } },
	{ 0,             		XF86XK_AudioPlay, 		spawn,          {.v = mpctoggle } },
	{ 0,             		XF86XK_AudioNext, 		spawn,          {.v = mpcnext } },
	{ 0,             		XF86XK_AudioPrev, 		spawn,          {.v = mpcprev } },
	{ MODKEY,                       XK_space,  			spawn,		{.v = launcher } },
	{ MODKEY,                       XK_e, 				spawn,		{.v = files } },
	{ MODKEY,                       XK_Print, 			spawn,		{.v = screenshotsave } },
	{ MODKEY|ShiftMask,             XK_Return, 			spawn,          {.v = termcmd } },
	{ MODKEY,             		XK_u, 				spawn,          {.v = lock } },
	{ MODKEY|ShiftMask,             XK_u, 				spawn,          {.v = suspend } },
	{ MODKEY,                       XK_b,      			togglebar,      {0} },
	{ MODKEY,                       XK_j,      			focusstack,     {.i = +1 } },
	{ MODKEY1,                      XK_Tab,    			quickSwap,     	{0}},
	{ MODKEY1|ShiftMask,            XK_Tab,    			focusstack,     {.i = +1}},
	{ MODKEY,                       XK_k,      			focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      			incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      			incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      			setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      			setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, 			zoom,           {0} },
	{ MODKEY,                       XK_Tab,    			view,           {0} },
	{ MODKEY,             		XK_w,      			killclient,     {0} },
	{ MODKEY,                       XK_t,      			setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      			setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      			setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  			togglefloating, {0} },
	{ MODKEY,                       XK_0,      			view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      			tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  			focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, 			focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  			tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, 			tagmon,         {.i = +1 } },
	{ MODKEY|MODKEY1,              XK_h,      			incrgaps,       {.i = +1 } },
	{ MODKEY|MODKEY1,              XK_l,      			incrgaps,       {.i = -1 } },
	{ MODKEY|MODKEY1|ShiftMask,    XK_h,      			incrogaps,      {.i = +1 } },
	{ MODKEY|MODKEY1|ShiftMask,    XK_l,      			incrogaps,      {.i = -1 } },
	{ MODKEY|MODKEY1|ControlMask,  XK_h,      			incrigaps,      {.i = +1 } },
	{ MODKEY|MODKEY1|ControlMask,  XK_l,      			incrigaps,      {.i = -1 } },
	{ MODKEY|MODKEY1,              XK_0,      			togglegaps,     {0} },
	{ MODKEY|MODKEY1|ShiftMask,    XK_0,      			defaultgaps,    {0} },
	{ MODKEY,                       XK_y,     			incrihgaps,     {.i = +1 } },
	{ MODKEY,                       XK_o,     			incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_y,     			incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_o,     			incrivgaps,     {.i = -1 } },
	{ MODKEY|MODKEY1,              XK_y,      			incrohgaps,     {.i = +1 } },
	{ MODKEY|MODKEY1,              XK_o,      			incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,     			incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,     			incrovgaps,     {.i = -1 } },
	TAGKEYS(                        	XK_1,                      0)
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
	{ ClkWinTitle,          0,              Button3,        focusstack,     {.i = +1 } },
	{ ClkWinTitle,          0,              Button1,        quickSwap,     	{0} },
	{ ClkWinTitle,          0,              Button2,        spawn,     	{.v = mpctoggle } },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = launcher } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkStatusText,        0,         	Button1,        spawn,     	{.v = statusbarupdate} },
};


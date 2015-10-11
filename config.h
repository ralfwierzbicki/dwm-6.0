/* See LICENSE file for copyright and license details. */

/* appearance */
#define NUMCOLORS 9
static const char colors[NUMCOLORS][ColLast][10] = {
  // border   foreground background
  { "#444444", "#bbbbbb", "#222222" },  // normal
  { "#488EF9", "#8ebe27", "#222222" },  // selected
  { "#ffb910", "#ffb910", "#222222" },  // urgent/warning
  { "#ff4200", "#ff4200", "#222222" },  // error
  { "#444444", "#ffffff", "#222222" },  // white 5
  { "#444444", "#ffff00", "#222222" },
  
  { "#444444", "#5a7b00", "#222222" },
  { "#444444", "#77a300", "#222222" },
  { "#444444", "#8ec300", "#222222" },
};

static const char font[] = "Terminus2 8"; //Ohsnap.Icons 8";
static const char dmenufont[] = "Terminess Powerline";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 2;        /* gap pixel between windows */
static const unsigned int snap      = 2;        /* snap pixel */
static const unsigned int systrayspacing = 4;   /* systray spacing */
static const Bool showsystray       = True;     /* False means no systray */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
static const char scratchpadname[]  = "Scratchpad";

static const Rule rules[] = {
        /* xprop(1):
         *      WM_CLASS(STRING) = instance, class
         *      WM_NAME(STRING) = title
         */
        /* class                instance        title           tags mask       iscentered      isfloating      monitor */
        { "Gimp",               NULL,           NULL,           0,              False,          True,           -1 },
        { "Thunderbird",        NULL,           NULL,           1 << 0,         False,          False,          -1 },
        { "Google-chrome",      NULL,           NULL,           1 << 2,         False,          False,          -1 },
        { "Firefox",            NULL,           NULL,           1 << 2,         False,          False,          -1 },
        { "Xfce4-terminal",     NULL,           NULL,           1 << 3,         False,          False,          -1 },
        { "Gnome-terminal",     NULL,           NULL,           1 << 3,         False,          False,          -1 },
        { "Xterm",              NULL,           NULL,           1 << 3,         False,          False,          -1 },
        { "URxvt",              NULL,           NULL,           1 << 3,         False,          False,          -1 },
        { "Xfce4-appfinder",    NULL,           NULL,           0,              True,           True,           -1 },
        { "Qikec",              NULL,           NULL,           0,              False,          True,           -1 },
	{ "QtCreator",		NULL,		NULL,		1 << 4,		False,		False,		-1 },
};

/* layout(s) */
static const float mfact      = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

#include "gaplessgrid.c"

static const Layout layouts[] = {
        /* symbol     arrange function */
        { "É",	True, tile },    /* first entry is default */
        { "Ê",	False, NULL },    /* no layout function means floating behavior */
        { "Ë",	False, monocle },
	{ "Í",	False, gaplessgrid },
};

/* tagging */
static Tag tags[] = {
  /* name     layout      mfact   nmaster */
  { "1",   &layouts[2], -1,    -1 },
  { "2",   &layouts[0], -1,    -1 },
  { "3",   &layouts[0], -1,    -1 },
  { "4",   &layouts[3], -1,    -1 },
  { "5",   &layouts[0], -1,    -1 },
  { "6",   &layouts[0], -1,    -1 },
  { "7",   &layouts[0], -1,    -1 },
  { "8",   &layouts[0], -1,    -1 },
  { "9",   &layouts[1], -1,    -1 },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-hist", "/home/ralf/.dmenu_history", "-m", dmenumon, "-fn", dmenufont, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG], "-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
static const char *termcmd[]  = { "urxvtc", NULL };
static const char *quitcmd[] = { "xfce4-session-logout", "-f", NULL };

static Key keys[] = {
        /* modifier                     key        function        argument */
        { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
        { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
        { MODKEY,                       XK_b,      togglebar,      {0} },
        { MODKEY,                       XK_k,      focusstack,     {.i = +1 } },
        { MODKEY,                       XK_Tab,    focusstack,     {.i = -1 } },
        { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
        { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
        { MODKEY,                       XK_Left,   setmfact,       {.f = -0.05} },
        { MODKEY,                       XK_Right,  setmfact,       {.f = +0.05} },
        { MODKEY,                       XK_Return, zoom,           {0} },
        /*{ MODKEY,                       XK_Tab,    view,           {0} },*/
        { MODKEY,                       XK_c,      killclient,     {0} },
        { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
        { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
        { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
        { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
        { MODKEY,                       XK_space,  setlayout,      {0} },
        { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
        { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
        { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
        { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
        { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
        { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
        { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
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
	{ MODKEY,                       XK_q,      spawn,          {.v = quitcmd } },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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


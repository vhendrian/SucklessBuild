/* See LICENSE file for copyright and license details. */
/*Author : Veri Hendrian*/
/* appearance */
static const unsigned int borderpx  	 = 2;        /* border pixel of windows */
static const Gap default_gap        = {.isgap = 1, .realgap = 10, .gappx = 10};
static const unsigned int snap      	 = 32;       /* snap pixel */

static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */

static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        	 = 1;     /* 0 means no systray */


static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */

//static const int vertpad            = 10;       /* vertical padding of bar */
//static const int sidepad            = 10;       /* horizontal padding of bar */
static const char buttonbar[]       = "LeafOS";

static const char *fonts[]          =
{
/* System Fonts : */
"monospace:size=10",
//"Operator Mono:style=Bold:size=10:antialias=true:autohint=true",
//"Source Code Pro:style=Bold:size=10:antialias=true:autohint=true",
//"JetBrains Mono:style=Bold:size=8:antialias=true:autohint=true",
//"Fantasque Sans Mono:style=Bold:size=12:antialias=true:autohint=true",
//"monospace:style=Bold:size=10:antialias=true:autohint=true"
/* Emoji & Icon Fonts : */
//"JoyPixels:size=10:antialias=true:autohint=true",
//"Font Awesome 6 Free Solid:pixelsize=12",
//"Font Awesome 6 Brands:pixelsize=12",
/* Nerd Fonts : */
//"JetBrainsMono Nerd Font:style=Medium:size=8:antialias=true:autohint=true",
//"FantasqueSansMono Nerd Font:style=Bold:size=12:antialias=true:autohint=true",
//"Roboto Mono for Powerline:pixelsize=14:antialias=true:autohint=true",
//"SauceCodePro Nerd Font Mono:weight=bold:pixelsize=10:antialias=true:hinting=true",

};
static const char dmenufont[]       = "monospace:size=10";

static const char normbgcolor[]     = "#181818";
static const char normbordercolor[] = "#252525";
static const char normfgcolor[]     = "#DEDEDE";
static const char selfgcolor[]      = "#3FC5B7";
static const char selbordercolor[]  = "#3FC5B7";
static const char selbgcolor[]      = "#181818";
static const char titlebordercolor[] = "#3FC5B7";
static const char titlebgcolor[]     = "#181818";
static const char titlefgcolor[]      = "#3FC5B7";
static const char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
       [SchemeTitle]  = { titlefgcolor, titlebgcolor },
};
static const XPoint stickyicon[]    = { {0,0}, {4,0}, {4,8}, {2,6}, {0,8}, {0,0} }; /* represents the icon as an array of vertices */
static const XPoint stickyiconbb    = {4,8};	/* defines the bottom right corner of the polygon's bounding box (speeds up scaling) */


/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };


static const unsigned int ulinepad     = 5;    /* horizontal padding between the underline and tag */
static const unsigned int ulinestroke  = 2;    /* thickness / height of the underline */
static const unsigned int ulinevoffset = 0;    /* how far above the bottom of the bar the line should appear */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title            tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",     NULL,       NULL,            0,         1,          0,           0,        -1 },
	{ "Firefox",  NULL,       NULL,            1 << 8,    0,          0,          -1,        -1 },
	{ "kitty",       NULL,       NULL,            0,         0,          1,           0,        -1 },
	{ NULL,       NULL,       "Event Tester",  0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */


#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
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
static const char *dmenucmd[] = { "dmenu_run", "-c", "-l", "10", "-p", "Run : ", NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *powermenucmd[]  = { "dmenu-powermenu", NULL };

#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key        function        argument */

	{ MODKEY,                       XK_x,      spawn,          {.v = powermenucmd } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             			XK_Return, spawn,          {.v = termcmd } }, 

        //showhide window
	{ MODKEY,                       XK_n,      hidewin,        {0} },
	{ MODKEY|ShiftMask,             XK_n,      restorewin,     {0} },


    //shiftview
    { MODKEY,             	    	XK_Right,  shiftview,        { .i = +1 } },
    { MODKEY,             	        XK_Left,   shiftview,        { .i = -1 } },
    { MODKEY,             	        XK_Up,     shiftviewclients, { .i = +1 } },
    { MODKEY,             	        XK_Down,   shiftviewclients, { .i = -1 } },

    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },

    { MODKEY|ShiftMask,             XK_Left,   setmfact,       {.f = -0.05} },
    { MODKEY|ShiftMask,             XK_Right,  setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_Up,     setcfact,       {.f = +0.25} },
    { MODKEY|ShiftMask,             XK_Down,   setcfact,       {.f = -0.25} },

	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },

	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },

	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
	
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	{Mod1Mask,                      XK_Tab,    spawn,          SHCMD("alttab")},

	//close dwm
	{ MODKEY,	                XK_q,      killclient,     {0} },
	//quit dwm
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	//restart dwm
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} },

    // ----------------- Hardware ------------------

    // volume
    {0, XF86XK_AudioLowerVolume,  spawn,  SHCMD(" amixer set Master 5%-")},
    {0, XF86XK_AudioRaiseVolume,  spawn,  SHCMD(" amixer set Master 5%+")},
    {0, XF86XK_AudioMute, 	  	  spawn,  SHCMD(" amixer set Master toggle")},

    // brightness
    {0, XF86XK_MonBrightnessUp,    spawn,  SHCMD("brightnessctl set +5%")},
    {0, XF86XK_MonBrightnessDown,  spawn,  SHCMD("brightnessctl set 5%-")},


};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkButton,		0,		Button1,	spawn,		{.v = dmenucmd } },
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	/* placemouse options, choose which feels more natural:
	 *    0 - tiled position is relative to mouse cursor
	 *    1 - tiled postiion is relative to window center
	 *    2 - mouse pointer warps to window center
	 *
	 * The moveorplace uses movemouse or placemouse depending on the floating state
	 * of the selected client. Set up individual keybindings for the two if you want
	 * to control these separately (i.e. to retain the feature to move a tiled window
	 * into a floating position).
	 */
	{ ClkClientWin,         MODKEY,         Button1,        moveorplace,    {.i = 1} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


/* See LICENSE file for copyright and license details. */

/* appearance */
static char* font         = "JetBrainsMonoNF:size=12:style=bold";
static char* normbgcolor  = "#222222";
static char* normfgcolor  = "#cccccc";
static char* selbgcolor   = "#555555";
static char* selfgcolor   = "#ffffff";
static char* urgbgcolor   = "#111111";
static char* urgfgcolor   = "#cc0000";
static char* before       = "<";
static char* after        = ">";
static char* titletrim    = "...";
static int tabwidth       = 200;
static int focusnew       = 1;
static int urgentswitch   = 0;
static int separator      = 4;

/*
 * Where to place a new tab when it is opened. When npisrelative is True,
 * then the current position is changed + newposition. If npisrelative
 * is False, then newposition is an absolute position.
 */
static int newposition   = 1;
static int npisrelative  = 1;

#define SETPROP(p) { \
        .v = (char *[]){ "/bin/sh", "-c", \
                "prop=\"`xwininfo -children -id $1 | grep '^     0x' |" \
                "sed -e's@^ *\\(0x[0-9a-f]*\\) \"\\([^\"]*\\)\".*@\\1 \\2@' |" \
                "xargs -0 printf %b | dmenu -l 10 -w $1`\" &&" \
                "xprop -id $1 -f $0 8s -set $0 \"$prop\"", \
                p, winid, NULL \
        } \
}

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
	{ "font",         STRING,  &font},
	{ "normbgcolor",  STRING,  &normbgcolor},
	{ "normfgcolor",  STRING,  &normfgcolor},
	{ "selbgcolor",   STRING,  &selbgcolor},
	{ "selfgcolor",   STRING,  &selfgcolor},
	{ "urgbgcolor",   STRING,  &urgbgcolor},
	{ "urgfgcolor",   STRING,  &urgfgcolor},
	{ "before",       STRING,  &before},
	{ "after",        STRING,  &after},
	{ "titletrim",    STRING,  &titletrim},
	{ "tabwidth",     INTEGER, &tabwidth},
	{ "focusnew",     INTEGER, &focusnew},
	{ "urgentswitch", INTEGER, &urgentswitch},
	{ "newposition",  INTEGER, &newposition},
	{ "npisrelative", INTEGER, &npisrelative},
	{ "separator",    INTEGER, &separator},
};

#define CTRL  ControlMask
#define ALT   Mod1Mask
#define SHIFT ShiftMask
#define SUPER Mod4Mask
static const Key keys[] = {
	/* modifier          key        function     argument */
	{ ALT,               XK_t,      spawn,       { 0 } },

	{ ALT,               XK_Tab,    rotate,      { .i = 0 } },
	{ ALT|CTRL,          XK_k,      rotate,      { .i = +1 } },
	{ ALT|CTRL,          XK_j,      rotate,      { .i = -1 } },
	{ ALT|CTRL,          XK_l,      movetab,     { .i = +1 } },
	{ ALT|CTRL,          XK_h,      movetab,     { .i = -1 } },

	{ ALT,               XK_x,      killclient,  { 0 } },
	
	{ ALT,               XK_Return, spawn,       SETPROP("_TABBED_SELECT_TAB") },
	{ ALT,               XK_1,      move,        { .i = 0 } },
	{ ALT,               XK_2,      move,        { .i = 1 } },
	{ ALT,               XK_3,      move,        { .i = 2 } },
	{ ALT,               XK_4,      move,        { .i = 3 } },
	{ ALT,               XK_5,      move,        { .i = 4 } },
	{ ALT,               XK_6,      move,        { .i = 5 } },
	{ ALT,               XK_7,      move,        { .i = 6 } },
	{ ALT,               XK_8,      move,        { .i = 7 } },
	{ ALT,               XK_9,      move,        { .i = 8 } },
	{ ALT,               XK_0,      move,        { .i = 9 } },

	{ ALT,               XK_u,      focusurgent, { 0 } },
	{ ALT|ShiftMask,     XK_u,      toggle,      { .v = (void*) &urgentswitch } },

	// { 0,                 XK_F11,    fullscreen,  { 0 } },
};

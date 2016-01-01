#ifndef __GEVENTTYPE__
#define __GEVENTTYPE__

enum GEventType{
	ET_NONE,
	ET_KEYBOARD,
	ET_MOUSE,
	ET_INPUT
};

enum GKeyEventType
{
	KET_NONE,
	KET_KEYDOWN,
	KET_KEYUP
};

enum GMouseEventType {
	MET_NONE,
	MET_LBDOWN,
	MET_LBUP,
	MET_RBDOWN,
	MET_RBUP,
	MET_MOVE
};

#endif
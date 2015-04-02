/* File : Eureka.i */
%module Eureka

/*SWIG includes for propper operations of wrapper*/
%include carrays.i
%include cstring.i
%include cdata.i
%include cpointer.i
%include exception.i
%include std_vector.i
%include std_map.i
%include std_string.i

/*Engine includes for the wrapper*/
%{
#include "rand_generators.h"
#include "sqlkeywords.h"
#include "physics.h"
#include "data_base.h"
#include "draw_base.h"
#include "ui.h"
#include "unit.h"
#include "trigger.h"
#include "Timer.h"
#include "database.h"
#include "typedefs.h"
#include "conversion.h"
#include "modules.h"
#include "unitmanager.h"
#include "particlesystem.h"
#include "threading.h"
#include "networking.h"
#include "iomanager.h"
#include "layersystem.h"
#include "info.h"
#include "timersystem.h"
#include "triggermanager.h"
#include "uimanager.h"
#include "level.h"
#include "soundqueue.h"
#include "videoplayer.h"
#include "cursor.h"
#include "game.h"
/*This is a small compilation error fix*/
#undef IN
#define IN 0x8000
%}

/*Renaming clashes*/
%rename(SetForceCountDouble) SetForceCount(double,char);
%rename(searchCharIndex_char) searchCharIndex(char,char[]);

/* Let's just grab the original header file here */
%include "rand_generators.h"
%include "sqlkeywords.h"
%include "physics.h"
%include "data_base.h"
%include "draw_base.h"
%include "ui.h"
%include "unit.h"
%include "trigger.h"
%include "Timer.h"
%include "typedefs.h"
%include "database.h"
%include "conversion.h"
%include "modules.h"
%include "unitmanager.h"
%include "particlesystem.h"
%include "threading.h"
%include "networking.h"
%include "iomanager.h"
%include "layersystem.h"
%include "info.h"
%include "triggermanager.h"
%include "timersystem.h"
%include "uimanager.h"
%include "level.h"
%include "soundqueue.h"
%include "videoplayer.h"
%include "cursor.h"
%include "game.h"
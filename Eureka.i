/* File : Eureka.i */
%module Eureka

/*SWIG includes for propper operations of wrapper*/
%include carrays.i
%include cstring.i
%include cdata.i
%include exception.i

/*Engine includes for the wrapper*/
%{
#include "rand_generators.h"
#include "sqlkeywords_modifiedForSWIG.h"
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
#include "info_modifiedForSWIG.h"
#include "timersystem.h"
#include "triggermanager.h"
#include "uimanager.h"
#include "level.h"
#include "BST.h"
#include "game.h"
%}

/* Let's just grab the original header file here */
%include "rand_generators.h"
%include "sqlkeywords_modifiedForSWIG.h"
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
%include "info_modifiedForSWIG.h"
%include "triggermanager.h"
%include "timersystem.h"
%include "uimanager.h"
%include "level.h"
%include "BST.h"
%include "game.h"
//
//  WebDebug.h
//  viewer-webed
//
//  Created by Matthew Rupp on 2/29/16.
//  Copyright © 2016 MSU. All rights reserved.
//

#ifndef WebDebug_h
#define WebDebug_h

#include <emscripten.h>
#include <iostream>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

//If we're sending it as a stream, which stream should we use?
#define DEBUG_STREAM std::cerr

//Should we send debug information through the worker messaging interface?
#define D_SEND_JSON 0

//How detailed should our debug output be
#define D_VERBOSITY 1

//Constants to define different types of debugging
#define D_FLOW 1
#define D_MSG_IN 2
#define D_MSG_OUT 4
#define D_STATUS 8
#define D_EVENTS 16
#define D_ACTIONS 32
#define D_ERROR 64

////What should we be outputting for debug purposes?


//#define DEBUG_LEVEL \
//  (D_FLOW | D_MSG_IN | D_MSG_OUT | D_STATUS | D_EVENTS | D_ACTIONS | D_ERROR)

#define DEBUG_LEVEL (D_STATUS | D_MSG_IN)

#ifdef NDEBUG 

  #define D_(...) do{}while(0);

#else

  #define D_0(LEVEL, MSG) D_1(LEVEL, MSG, 0)

  #define D_1(LEVEL, MSG, VERBOSITY)\
  do{\
    if ( ( (LEVEL) & (DEBUG_LEVEL) ) && (VERBOSITY <= D_VERBOSITY) )\
    {\
      if ( !D_SEND_JSON ){\
        DEBUG_STREAM << std::endl << "[AVIDA] " << MSG << std::endl;\
      }\
    }\
  } while(0);
  
  #define D_SELECT(_0, _1, FUNC, ...) FUNC
  
  #define D_(LEVEL, MSG, ...) D_SELECT(_0, ##__VA_ARGS__, D_1, D_0)(LEVEL, MSG, ##__VA_ARGS__)


#endif  //NDEBUG

#endif /* WebDebug_h */

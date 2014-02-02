// logging.h - Handles various logging (and related) utilities.

#ifndef  ___STEAM_API_BRIDGE_LOGGING_H___
#define  ___STEAM_API_BRIDGE_LOGGING_H___

#define __ABORT(MSG, ...) { \
  WINE_ERR("Abort! " MSG "\n", ##__VA_ARGS__); \
  __abort__(); \
}
void __abort__() __attribute__ ((noreturn));

#define __STUB(ARGS, ...) { \
  WINE_ERR("Stub! " ARGS "\n", ##__VA_ARGS__); \
  __stub__(); \
}
void __stub__() __attribute__ ((noreturn));

#endif //___STEAM_API_BRIDGE_LOGGING_H___


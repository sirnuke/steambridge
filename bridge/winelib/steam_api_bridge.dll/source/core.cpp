// core.cpp - Handles the core API calls

#include <cstdio>

#include "api.h"


extern "C"
{

int steam_bridge_say_hello()
{
  printf("Hello world!\n");
  return 24;
}

}

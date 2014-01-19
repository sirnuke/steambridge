// state.h - Records the state of the app, specifically stuff that's
//           internal and can't be cleanly tossed back to the app via 
//           the existing (and expected) classes/interfaces.

#pragma once

#include <deque>

class AppState
{
  public:
    AppState();
    ~AppState();

    void setSafeMode(bool safe);
    bool getSafeMode();

    void addCallbackWrapper(class CallbackWrapper *wrapper);

    class SteamUserWrapper *getSteamUser();

  private:
    bool safeMode;

    std::deque<class CallbackWrapper *> callbackWrappers;

    class SteamUserWrapper *steamUser;
};

extern AppState state;


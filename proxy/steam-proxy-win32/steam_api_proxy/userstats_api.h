// userstats_api.h - Header for the userstats wrapper

#pragma once

#include <string>

#include "types.h"

class SteamUserStatsWrapper
{
  public:
    SteamUserStatsWrapper();

    virtual bool RequestCurrentStats();

    virtual bool GetStat(const char *pchName, int32 *pData);
    virtual bool GetStat(const char *pchName, float *pData);

    virtual bool SetStat(const char *pchName, int32 nData);
    virtual bool SetStat(const char *pchName, float fData);
    virtual bool UpdateAvgRateStat(const char *pchName, float flCountThisSession, double dSessionLength);

    virtual bool GetAchievement(const char *pchName, bool *pbAchieved);
    virtual bool SetAchievement(const char *pchName);
    virtual bool ClearAchievement(const char *pchName);

    virtual bool GetAchievementAndUnlockTime(const char *pchName, bool *pbAchieved, uint32 *punUnlockTime);

    virtual bool StoreStats();

    virtual int GetAchievementIcon(const char *pchName);

    virtual const char *GetAchievementDisplayAttribute(const char *pchName, const char *pchKey);

    virtual bool IndicateAchievementProgress(const char *pchName, uint32 nCurProgress, uint32 nMaxProgress);

    virtual uint32 GetNumAchievements();
    virtual const char *GetAchievementName(uint32 iAchievement);

    // SteamAPICall_t ... (CSteamID)
    virtual SteamAPICall_t RequestUserStats(uint64 steamIDUser);

    // bool ... (CSteamID, const char *, int32 *)
    virtual bool GetUserStat(uint64 steamIDUser, const char *pchName, int32 *pData);

    // bool ... (CSteamID, const char *, float *)
    virtual bool GetUserStat(uint64 steamIDUser, const char *pchName, float *pData);

    // bool ... (CSteamID, const char *, bool *)
    virtual bool GetUserAchievement(uint64 steamIDUser, const char *pchName, bool *pbAchieved);

    // bool ... (CSteamID, const char *, bool *, uint32 *)
    virtual bool GetUserAchievementAndUnlockTime(uint64 steamIDUser, const char *pchName, bool *pbAchieved, uint32 *punUnlockTime);

    // I approve of this argument's name
    virtual bool ResetAllStats(bool bAchievementsToo);

    // SteamAPICall_t ... (const char *, ELeaderboardSortMethod, ELeaderboardDisplayType)
    virtual SteamAPICall_t FindOrCreateLeaderboard(const char *pchLeaderboardName, int eLeaderboardSortMethod, int eLeaderboardDisplayType);

    virtual SteamAPICall_t FindLeaderboard(const char *pchLeaderboardName);

    virtual const char *GetLeaderboardName(SteamLeaderboard_t hSteamLeaderboard);

    virtual int GetLeaderboardEntryCount(SteamLeaderboard_t hSteamLeaderboard);

    // ELeaderboardSortMethod ... (SteamLeaderboard_t)
    virtual int GetLeaderboardSortMethod(SteamLeaderboard_t hSteamLeaderboard);

    // ELeaderboardDisplayType ... (SteamLeaderboard_t)
    virtual int GetLeaderboardDisplayType(SteamLeaderboard_t hSteamLeaderboard);

    // SteamAPICall_t ... (SteamLeaderboard_t, ELeaderboardDataRequest, int, int)
    virtual SteamAPICall_t DownloadLeaderboardEntries(SteamLeaderboard_t hSteamLeaderboard, int eLeaderboardDataRequest, int nRangeStart, int nRangeEnd);

    // SteamAPICall_t ... (SteamLeaderboard_t, CSteamID *, int)
    virtual SteamAPICall_t DownloadLeaderboardEntriesForUsers(SteamLeaderboard_t hSteamLeaderboard, uint64 *prgUsers, int cUsers);

    virtual bool GetDownloadedLeaderboardEntry(SteamLeaderboardEntries_t hSteamLeaderboardEntries, int index, LeaderboardEntry_t *pLeaderboardEntry, int32 *pDetails, int cDetailsMax);

    // SteamAPICall_t ... (SteamLeaderboard_t, ELeaderboardUploadScoreMethod, int32, const int32 *, int)
    virtual SteamAPICall_t UploadLeaderboardScore(SteamLeaderboard_t hSteamLeaderboard, int eLeaderboardUploadScoreMethod, int32 nScore, const int32 *pScoreDetails, int cScoreDetailsCount);

    virtual SteamAPICall_t AttachLeaderboardUGC(SteamLeaderboard_t hSteamLeaderboard, UGCHandle_t hUGC);

    virtual SteamAPICall_t GetNumberOfCurrentPlayers();

    virtual SteamAPICall_t RequestGlobalAchievementPercentages();

    virtual int GetMostAchievedAchievementInfo(char *pchName, uint32 unNameBufLen, float *pflPercent, bool *pbAchieved);

    virtual int GetNextMostAchievedAchievementInfo(int iIteratorPrevious, char *pchName, uint32 unNameBufLen, float *pflPercent, bool *pbAchieved);

    virtual bool GetAchievementAchievedPercent(const char *pchName, float *pflPercent);

    virtual SteamAPICall_t RequestGlobalStats(int nHistoryDays);

    virtual bool GetGlobalStat(const char *pchStatName, int64 *pData);
    virtual bool GetGlobalStat(const char *pchStatName, double *pData);

    virtual int32 GetGlobalStatHistory(const char *pchStatName, int64 *pData, uint32 cubData);
    virtual int32 GetGlobalStatHistory(const char *pchStatName, double *pData, uint32 cubData);

};


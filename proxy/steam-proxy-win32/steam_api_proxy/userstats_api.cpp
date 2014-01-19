// userstats_api.cpp - Implements the userstats wrapper and related APIs.

#include "stdafx.h"

#include <steam_api_bridge.h>

#include "logging.h"
#include "state.h"
#include "steam_api_proxy.h"
#include "userstats_api.h"
#include "types.h"

SteamUserStatsWrapper::SteamUserStatsWrapper()
  __STUB__

bool SteamUserStatsWrapper::RequestCurrentStats()
  __STUB__

bool SteamUserStatsWrapper::GetStat(const char *pchName, int32 *pData)
  __STUB__
bool SteamUserStatsWrapper::GetStat(const char *pchName, float *pData)
  __STUB__

bool SteamUserStatsWrapper::SetStat(const char *pchName, int32 nData)
  __STUB__
bool SteamUserStatsWrapper::SetStat(const char *pchName, float fData)
  __STUB__
bool SteamUserStatsWrapper::UpdateAvgRateStat(const char *pchName, float flCountThisSession, double dSessionLength)
  __STUB__

bool SteamUserStatsWrapper::GetAchievement(const char *pchName, bool *pbAchieved)
  __STUB__
bool SteamUserStatsWrapper::SetAchievement(const char *pchName)
  __STUB__
bool SteamUserStatsWrapper::ClearAchievement(const char *pchName)
  __STUB__

bool SteamUserStatsWrapper::GetAchievementAndUnlockTime(const char *pchName, bool *pbAchieved, uint32 *punUnlockTime)
  __STUB__

bool SteamUserStatsWrapper::StoreStats()
  __STUB__

int SteamUserStatsWrapper::GetAchievementIcon(const char *pchName)
  __STUB__

const char *SteamUserStatsWrapper::GetAchievementDisplayAttribute(const char *pchName, const char *pchKey)
  __STUB__

bool SteamUserStatsWrapper::IndicateAchievementProgress(const char *pchName, uint32 nCurProgress, uint32 nMaxProgress)
  __STUB__

uint32 SteamUserStatsWrapper::GetNumAchievements()
  __STUB__
const char *SteamUserStatsWrapper::GetAchievementName(uint32 iAchievement)
  __STUB__

SteamAPICall_t SteamUserStatsWrapper::RequestUserStats(uint64 steamIDUser)
  __STUB__

bool SteamUserStatsWrapper::GetUserStat(uint64 steamIDUser, const char *pchName, int32 *pData)
  __STUB__

bool SteamUserStatsWrapper::GetUserStat(uint64 steamIDUser, const char *pchName, float *pData)
  __STUB__

bool SteamUserStatsWrapper::GetUserAchievement(uint64 steamIDUser, const char *pchName, bool *pbAchieved)
  __STUB__

bool SteamUserStatsWrapper::GetUserAchievementAndUnlockTime(uint64 steamIDUser, const char *pchName, bool *pbAchieved, uint32 *punUnlockTime)
  __STUB__

bool SteamUserStatsWrapper::ResetAllStats(bool bAchievementsToo)
  __STUB__

SteamAPICall_t SteamUserStatsWrapper::FindOrCreateLeaderboard(const char *pchLeaderboardName, int eLeaderboardSortMethod, int eLeaderboardDisplayType)
  __STUB__

SteamAPICall_t SteamUserStatsWrapper::FindLeaderboard(const char *pchLeaderboardName)
  __STUB__

const char *SteamUserStatsWrapper::GetLeaderboardName(SteamLeaderboard_t hSteamLeaderboard)
  __STUB__

int SteamUserStatsWrapper::GetLeaderboardEntryCount(SteamLeaderboard_t hSteamLeaderboard)
  __STUB__

int SteamUserStatsWrapper::GetLeaderboardSortMethod(SteamLeaderboard_t hSteamLeaderboard)
  __STUB__

int SteamUserStatsWrapper::GetLeaderboardDisplayType(SteamLeaderboard_t hSteamLeaderboard)
  __STUB__

SteamAPICall_t SteamUserStatsWrapper::DownloadLeaderboardEntries(SteamLeaderboard_t hSteamLeaderboard, int eLeaderboardDataRequest, int nRangeStart, int nRangeEnd)
  __STUB__

SteamAPICall_t SteamUserStatsWrapper::DownloadLeaderboardEntriesForUsers(SteamLeaderboard_t hSteamLeaderboard, uint64 *prgUsers, int cUsers)
  __STUB__

bool SteamUserStatsWrapper::GetDownloadedLeaderboardEntry(SteamLeaderboardEntries_t hSteamLeaderboardEntries, int index, LeaderboardEntry_t *pLeaderboardEntry, int32 *pDetails, int cDetailsMax)
  __STUB__

SteamAPICall_t SteamUserStatsWrapper::UploadLeaderboardScore(SteamLeaderboard_t hSteamLeaderboard, int eLeaderboardUploadScoreMethod, int32 nScore, const int32 *pScoreDetails, int cScoreDetailsCount)
  __STUB__

SteamAPICall_t SteamUserStatsWrapper::AttachLeaderboardUGC(SteamLeaderboard_t hSteamLeaderboard, UGCHandle_t hUGC)
  __STUB__

SteamAPICall_t SteamUserStatsWrapper::GetNumberOfCurrentPlayers()
  __STUB__

SteamAPICall_t SteamUserStatsWrapper::RequestGlobalAchievementPercentages()
  __STUB__

int SteamUserStatsWrapper::GetMostAchievedAchievementInfo(char *pchName, uint32 unNameBufLen, float *pflPercent, bool *pbAchieved)
  __STUB__

int SteamUserStatsWrapper::GetNextMostAchievedAchievementInfo(int iIteratorPrevious, char *pchName, uint32 unNameBufLen, float *pflPercent, bool *pbAchieved)
  __STUB__

bool SteamUserStatsWrapper::GetAchievementAchievedPercent(const char *pchName, float *pflPercent)
  __STUB__

SteamAPICall_t SteamUserStatsWrapper::RequestGlobalStats(int nHistoryDays)
  __STUB__

bool SteamUserStatsWrapper::GetGlobalStat(const char *pchStatName, int64 *pData)
  __STUB__

bool SteamUserStatsWrapper::GetGlobalStat(const char *pchStatName, double *pData)
  __STUB__

int32 SteamUserStatsWrapper::GetGlobalStatHistory(const char *pchStatName, int64 *pData, uint32 cubData)
  __STUB__

int32 SteamUserStatsWrapper::GetGlobalStatHistory(const char *pchStatName, double *pData, uint32 cubData)
  __STUB__


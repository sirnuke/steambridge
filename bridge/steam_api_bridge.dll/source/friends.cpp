// friends.cpp - Implements various functions related to the ISteamFriends class
// Copyright (c) 2014 Bryan DeGrendel
//
// See COPYING and license/LICENSE.steambridge for license information

#include <cstdio>

#include <steam_api.h>

#define NOMINMAX
#include <wine/debug.h>

#include "api.h"
#include "logging.h"
#include "state.h"

WINE_DEFAULT_DEBUG_CHANNEL(steambridge);

#define _THIN_WRAPPER(API, TRACE, ...) { \
  WINE_TRACE("(%p," TRACE ")\n", steamFriends, ##__VA_ARGS__); \
  if (!steamFriends) __ABORT("NULL steamFriends pointer!"); \
  return steamFriends->API(__VA_ARGS__); \
}

extern "C"
{

STEAM_API_BRIDGE_API class ISteamFriends *SteamFriends_()
{
  WINE_TRACE("\n");
  if (!state)
  {
    WINE_ERR("NULL internal state (init not called?)\n");
    return NULL;
  }
  return state->getSteamFriends();
}

const char *SteamFriends_GetPersonaName(ISteamFriends *steamFriends)
  _THIN_WRAPPER(GetPersonaName, "")

SteamAPICall_t SteamFriends_SetPersonaName(ISteamFriends *steamFriends, const char *pchPersonaName)
  _THIN_WRAPPER(SetPersonaName, "\"%s\"", pchPersonaName)

EPersonaState SteamFriends_GetPersonaState(ISteamFriends *steamFriends)
  _THIN_WRAPPER(GetPersonaState, "")

int SteamFriends_GetFriendCount(ISteamFriends *steamFriends, int iFriendFlags)
  _THIN_WRAPPER(GetFriendCount, "%i", iFriendFlags)

void SteamFriends_GetFriendByIndex(ISteamFriends *steamFriends, int iFriend, int iFriendFlags,
    CSteamID *result)
{
  WINE_TRACE("(%p,%i,%i,%p)\n", steamFriends, iFriend, iFriendFlags, result);

  if (!steamFriends) __ABORT("NULL steamFriends pointer!");
  if (!result) __ABORT("NULL CSteamID result pointer!");

  *result = steamFriends->GetFriendByIndex(iFriend, iFriendFlags);
}

EFriendRelationship SteamFriends_GetFriendRelationship(ISteamFriends *steamFriends,
    CSteamID steamIDFriend)
  _THIN_WRAPPER(GetFriendRelationship, "%llu", steamIDFriend)

EPersonaState SteamFriends_GetFriendPersonaState(ISteamFriends *steamFriends,
    CSteamID steamIDFriend)
  _THIN_WRAPPER(GetFriendPersonaState, "%llu", steamIDFriend)

const char *SteamFriends_GetFriendPersonaName(ISteamFriends *steamFriends, CSteamID steamIDFriend)
  _THIN_WRAPPER(GetFriendPersonaName, "%llu", steamIDFriend)

bool SteamFriends_GetFriendGamePlayed(ISteamFriends *steamFriends, CSteamID steamIDFriend,
    FriendGameInfo_t *pFriendGameInfo)
  _THIN_WRAPPER(GetFriendGamePlayed, "%llu,%p", steamIDFriend, pFriendGameInfo)

const char *SteamFriends_GetFriendPersonaNameHistory(ISteamFriends *steamFriends,
    CSteamID steamIDFriend, int iPersonaName)
  _THIN_WRAPPER(GetFriendPersonaNameHistory, "%llu,%i", steamIDFriend, iPersonaName)

bool SteamFriends_HasFriend(ISteamFriends *steamFriends, CSteamID steamIDFriend, int iFriendFlags)
  _THIN_WRAPPER(HasFriend, "%llu,%i", steamIDFriend, iFriendFlags)

int SteamFriends_GetClanCount(ISteamFriends *steamFriends)
  _THIN_WRAPPER(GetClanCount, "")

void SteamFriends_GetClanByIndex(ISteamFriends *steamFriends, int iClan, CSteamID *result)
{
  WINE_TRACE("(%p,%i,%p)\n", steamFriends, iClan, result);

  if (!steamFriends) __ABORT("NULL steamFriends pointer!");
  if (!result) __ABORT("NULL CSteamID result pointer!");

  *result = steamFriends->GetClanByIndex(iClan);
}

const char *SteamFriends_GetClanName(ISteamFriends *steamFriends, CSteamID steamIDClan)
  _THIN_WRAPPER(GetClanName, "%llu", steamIDClan)

const char *SteamFriends_GetClanTag(ISteamFriends *steamFriends, CSteamID steamIDClan)
  _THIN_WRAPPER(GetClanTag, "%llu", steamIDClan)

bool SteamFriends_GetClanActivityCounts(ISteamFriends *steamFriends, CSteamID steamIDClan,
    int *pnOnline, int *pnInGame, int *pnChatting)
  _THIN_WRAPPER(GetClanActivityCounts, "%llu,%p,%p,%p", steamIDClan, pnOnline, pnInGame, pnChatting)

SteamAPICall_t SteamFriends_DownloadClanActivityCounts(ISteamFriends *steamFriends,
    CSteamID *psteamIDClans, int cClansToRequest)
  _THIN_WRAPPER(DownloadClanActivityCounts, "%p,%i", psteamIDClans, cClansToRequest)

int SteamFriends_GetFriendCountFromSource(ISteamFriends *steamFriends, CSteamID steamIDSource)
  _THIN_WRAPPER(GetFriendCountFromSource, "%llu", steamIDSource);

void SteamFriends_GetFriendFromSourceByIndex(ISteamFriends *steamFriends, CSteamID steamIDSource,
    int iFriend, CSteamID *result)
{
  WINE_TRACE("(%p,%llu,%i,%p", steamFriends, steamIDSource, iFriend, result);

  if (!steamFriends) __ABORT("NULL steamFriends pointer!");
  if (!result) __ABORT("NULL CSteamID result pointer!");

  *result = steamFriends->GetFriendFromSourceByIndex(steamIDSource, iFriend);
}

bool SteamFriends_IsUserInSource(ISteamFriends *steamFriends, CSteamID steamIDUser,
    CSteamID steamIDSource)
  _THIN_WRAPPER(IsUserInSource, "%llu,%llu", steamIDUser, steamIDSource)

void SteamFriends_SetInGameVoiceSpeaking(ISteamFriends *steamFriends, CSteamID steamIDUser,
    bool bSpeaking)
  _THIN_WRAPPER(SetInGameVoiceSpeaking, "%llu,%i", steamIDUser, bSpeaking)

void SteamFriends_ActivateGameOverlay(ISteamFriends *steamFriends, const char *pchDialog)
  _THIN_WRAPPER(ActivateGameOverlay, "\"%s\"", pchDialog)

void SteamFriends_ActivateGameOverlayToUser(ISteamFriends *steamFriends, const char *pchDialog,
    CSteamID steamID)
  _THIN_WRAPPER(ActivateGameOverlayToUser, "\"%s\",%llu", pchDialog, steamID)

void SteamFriends_ActivateGameOverlayToWebPage(ISteamFriends *steamFriends, const char *pchURL)
  _THIN_WRAPPER(ActivateGameOverlayToWebPage, "\"%s\"", pchURL)

void SteamFriends_ActivateGameOverlayToStore(ISteamFriends *steamFriends, AppId_t nAppID,
    EOverlayToStoreFlag eFlag)
  _THIN_WRAPPER(ActivateGameOverlayToStore, "%u,%i", nAppID, eFlag)

void SteamFriends_SetPlayedWith(ISteamFriends *steamFriends, CSteamID steamIDUserPlayedWith)
  _THIN_WRAPPER(SetPlayedWith, "%llu", steamIDUserPlayedWith)

void SteamFriends_ActivateGameOverlayInviteDialog(ISteamFriends *steamFriends,
    CSteamID steamIDLobby)
  _THIN_WRAPPER(ActivateGameOverlayInviteDialog, "%llu", steamIDLobby);

int SteamFriends_GetSmallFriendAvatar(ISteamFriends *steamFriends, CSteamID steamIDFriend)
  _THIN_WRAPPER(GetSmallFriendAvatar, "%llu", steamIDFriend);

int SteamFriends_GetMediumFriendAvatar(ISteamFriends *steamFriends, CSteamID steamIDFriend)
  _THIN_WRAPPER(GetMediumFriendAvatar, "%llu", steamIDFriend);

int SteamFriends_GetLargeFriendAvatar(ISteamFriends *steamFriends, CSteamID steamIDFriend)
  _THIN_WRAPPER(GetLargeFriendAvatar, "%llu", steamIDFriend);

bool SteamFriends_RequestUserInformation(ISteamFriends *steamFriends, CSteamID steamIDUser, bool bRequireNameOnly)
  _THIN_WRAPPER(RequestUserInformation, "%llu,%i", steamIDUser, bRequireNameOnly)

SteamAPICall_t SteamFriends_RequestClanOfficerList(ISteamFriends *steamFriends,
    CSteamID steamIDClan)
  _THIN_WRAPPER(RequestClanOfficerList, "%llu", steamIDClan)

void SteamFriends_GetClanOwner(ISteamFriends *steamFriends, CSteamID steamIDClan, CSteamID *result)
{
  WINE_TRACE("(%p,%llu,%p", steamFriends, steamIDClan, result);
  if (!steamFriends) __ABORT("NULL steamFriends pointer!");
  if (!result) __ABORT("NULL CSteamID result pointer!");
  *result = steamFriends->GetClanOwner(steamIDClan);
}

int SteamFriends_GetClanOfficerCount(ISteamFriends *steamFriends, CSteamID steamIDClan)
  _THIN_WRAPPER(GetClanOfficerCount, "%llu", steamIDClan)

void SteamFriends_GetClanOfficerByIndex(ISteamFriends *steamFriends, CSteamID steamIDClan,
    int iOfficer, CSteamID *result)
{
  WINE_TRACE("(%p,%llu,%i,%p", steamFriends, steamIDClan, iOfficer, result);
  if (!steamFriends) __ABORT("NULL steamFriends pointer!");
  if (!result) __ABORT("NULL CSteamID result pointer!");
  *result = steamFriends->GetClanOfficerByIndex(steamIDClan, iOfficer);
}

uint32 SteamFriends_GetUserRestrictions(ISteamFriends *steamFriends)
  _THIN_WRAPPER(GetUserRestrictions, "")

bool SteamFriends_SetRichPresence(ISteamFriends *steamFriends, const char *pchKey,
    const char *pchValue)
  _THIN_WRAPPER(SetRichPresence, "\"%s\",\"%s\"", pchKey, pchValue)

void SteamFriends_ClearRichPresence(ISteamFriends *steamFriends)
  _THIN_WRAPPER(ClearRichPresence, "")

const char *SteamFriends_GetFriendRichPresence(ISteamFriends *steamFriends, CSteamID steamIDFriend,
    const char *pchKey)
  _THIN_WRAPPER(GetFriendRichPresence, "%llu,\"%s\"", steamIDFriend, pchKey)

int SteamFriends_GetFriendRichPresenceKeyCount(ISteamFriends *steamFriends, CSteamID steamIDFriend)
  _THIN_WRAPPER(GetFriendRichPresenceKeyCount, "%llu", steamIDFriend)

const char *SteamFriends_GetFriendRichPresenceKeyByIndex(ISteamFriends *steamFriends,
    CSteamID steamIDFriend, int iKey)
  _THIN_WRAPPER(GetFriendRichPresenceKeyByIndex, "%llu,%i", steamIDFriend, iKey)

void SteamFriends_RequestFriendRichPresence(ISteamFriends *steamFriends, CSteamID steamIDFriend)
  _THIN_WRAPPER(RequestFriendRichPresence, "%llu", steamIDFriend)

bool SteamFriends_InviteUserToGame(ISteamFriends *steamFriends, CSteamID steamIDFriend,
    const char *pchConnectString)
  _THIN_WRAPPER(InviteUserToGame, "%llu,\"%s\"", steamIDFriend, pchConnectString)

int SteamFriends_GetCoplayFriendCount(ISteamFriends *steamFriends)
  _THIN_WRAPPER(GetCoplayFriendCount, "")

void SteamFriends_GetCoplayFriend(ISteamFriends *steamFriends, int iCoplayFriend, CSteamID *result)
{
  WINE_TRACE("(%p,%i,%p", steamFriends, iCoplayFriend, result);
  if (!steamFriends) __ABORT("NULL steamFriends pointer!");
  if (!result) __ABORT("NULL CSteamID result pointer!");
  *result = steamFriends->GetCoplayFriend(iCoplayFriend);
}

int SteamFriends_GetFriendCoplayTime(ISteamFriends *steamFriends, CSteamID steamIDFriend)
  _THIN_WRAPPER(GetFriendCoplayTime, "%llu", steamIDFriend)

AppId_t SteamFriends_GetFriendCoplayGame(ISteamFriends *steamFriends, CSteamID steamIDFriend)
  _THIN_WRAPPER(GetFriendCoplayGame, "%llu", steamIDFriend)

SteamAPICall_t SteamFriends_JoinClanChatRoom(ISteamFriends *steamFriends, CSteamID steamIDClan)
  _THIN_WRAPPER(JoinClanChatRoom, "%llu", steamIDClan)

bool SteamFriends_LeaveClanChatRoom(ISteamFriends *steamFriends, CSteamID steamIDClan)
  _THIN_WRAPPER(LeaveClanChatRoom, "%llu", steamIDClan)

int SteamFriends_GetClanChatMemberCount(ISteamFriends *steamFriends, CSteamID steamIDClan)
  _THIN_WRAPPER(GetClanChatMemberCount, "%llu", steamIDClan)

void SteamFriends_GetChatMemberByIndex(ISteamFriends *steamFriends, CSteamID steamIDClan, int iUser,
    CSteamID *result)
{
  WINE_TRACE("(%p,%llu,%i,%p", steamFriends, steamIDClan, iUser, result);
  if (!steamFriends) __ABORT("NULL steamFriends pointer!");
  if (!result) __ABORT("NULL CSteamID result pointer!");
  *result = steamFriends->GetChatMemberByIndex(steamIDClan, iUser);
}

bool SteamFriends_SendClanChatMessage(ISteamFriends *steamFriends, CSteamID steamIDClanChat,
    const char *pchText)
  _THIN_WRAPPER(SendClanChatMessage, "%llu,\"%s\"", steamIDClanChat, pchText)

int SteamFriends_GetClanChatMessage(ISteamFriends *steamFriends, CSteamID steamIDClanChat,
    int iMessage, void *prgchText, int cchTextMax, EChatEntryType *type, CSteamID *id)
  _THIN_WRAPPER(GetClanChatMessage, "%llu,%i,%p,%i,%p,%p", steamIDClanChat, iMessage, prgchText,
      cchTextMax, type, id)

bool SteamFriends_IsClanChatAdmin(ISteamFriends *steamFriends, CSteamID steamIDClanChat,
    CSteamID steamIDUser)
  _THIN_WRAPPER(IsClanChatAdmin, "%llu,%llu", steamIDClanChat, steamIDUser)

bool SteamFriends_IsClanChatWindowOpenInSteam(ISteamFriends *steamFriends, CSteamID steamIDClanChat)
  _THIN_WRAPPER(IsClanChatWindowOpenInSteam, "%llu", steamIDClanChat)

bool SteamFriends_OpenClanChatWindowInSteam(ISteamFriends *steamFriends, CSteamID steamIDClanChat)
  _THIN_WRAPPER(OpenClanChatWindowInSteam, "%llu", steamIDClanChat)

bool SteamFriends_CloseClanChatWindowInSteam(ISteamFriends *steamFriends, CSteamID steamIDClanChat)
  _THIN_WRAPPER(CloseClanChatWindowInSteam, "%llu", steamIDClanChat)

bool SteamFriends_SetListenForFriendsMessages(ISteamFriends *steamFriends, bool bInterceptEnabled)
  _THIN_WRAPPER(SetListenForFriendsMessages, "%i", bInterceptEnabled)

bool SteamFriends_ReplyToFriendMessage(ISteamFriends *steamFriends, CSteamID steamIDFriend,
    const char *pchMsgToSend)
  _THIN_WRAPPER(ReplyToFriendMessage, "%llu,\"%s\"", steamIDFriend, pchMsgToSend)

int SteamFriends_GetFriendMessage(ISteamFriends *steamFriends, CSteamID steamIDFriend,
    int iMessageID, void *pvData, int cubData, EChatEntryType *peChatEntryType)
  _THIN_WRAPPER(GetFriendMessage, "%llu,%i,%p,%i,%p", steamIDFriend, iMessageID, pvData, cubData,
      peChatEntryType)

SteamAPICall_t SteamFriends_GetFollowerCount(ISteamFriends *steamFriends, CSteamID steamID)
  _THIN_WRAPPER(GetFollowerCount, "%llu", steamID)

SteamAPICall_t SteamFriends_IsFollowing(ISteamFriends *steamFriends, CSteamID steamID)
  _THIN_WRAPPER(IsFollowing, "%llu", steamID)

SteamAPICall_t SteamFriends_EnumerateFollowingList(ISteamFriends *steamFriends, uint32 unStartIndex)
  _THIN_WRAPPER(EnumerateFollowingList, "%u", unStartIndex)

} // extern "C"


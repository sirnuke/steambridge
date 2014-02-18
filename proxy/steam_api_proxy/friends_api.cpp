// friends_api.cpp - Implements the friends wrapper and various related APIs
// Copyright (c) 2014 Bryan DeGrendel
//
// See COPYING and license/LICENSE.steambridge for license information

#include "stdafx.h"

#include "friends_api.h"
#include "logging.h"
#include "state.h"
#include "steam_api_proxy.h"
#include "types.h"

#include <steam_api_bridge.h>

#define _THIN_WRAPPER(API, TRACE, ...) { \
  __TRACE("" TRACE "", ##__VA_ARGS__); \
  return SteamFriends_  ##API(steamFriends, ##__VA_ARGS__); \
}

SteamFriendsWrapper::SteamFriendsWrapper() : steamFriends(NULL)
{
  __TRACE("(this=0x%p)", this);
  steamFriends = SteamFriends_();
  __LOG("Wrapping ISteamFriends (0x%p) into (0x%p)", steamFriends, this);
}

const char *SteamFriendsWrapper::GetPersonaName()
  _THIN_WRAPPER(GetPersonaName, "")

SteamAPICall_t SteamFriendsWrapper::SetPersonaName(const char *pchPersonaName)
  _THIN_WRAPPER(SetPersonaName, "\"%s\"", pchPersonaName)

int SteamFriendsWrapper::GetPersonaState()
  _THIN_WRAPPER(GetPersonaState, "")

int SteamFriendsWrapper::GetFriendCount(int iFriendFlags)
  _THIN_WRAPPER(GetFriendCount, "%i", iFriendFlags)

CSteamID SteamFriendsWrapper::GetFriendByIndex(int iFriend, int iFriendFlags)
{
  __TRACE("(%i,%i)", iFriend, iFriendFlags);
  CSteamID id;
  SteamFriends_GetFriendByIndex(steamFriends, iFriend, iFriendFlags, &id);
  return id;
}

int SteamFriendsWrapper::GetFriendRelationship(CSteamID steamIDFriend)
  _THIN_WRAPPER(GetFriendRelationship, "%llu", steamIDFriend)

int SteamFriendsWrapper::GetFriendPersonaState(CSteamID steamIDFriend)
  _THIN_WRAPPER(GetFriendPersonaState, "%llu", steamIDFriend)

const char *SteamFriendsWrapper::GetFriendPersonaName(CSteamID steamIDFriend)
  _THIN_WRAPPER(GetFriendPersonaName, "%llu", steamIDFriend)

bool SteamFriendsWrapper::GetFriendGamePlayed(CSteamID steamIDFriend,
    struct FriendGameInfo_t *pFriendGameInfo)
  _THIN_WRAPPER(GetFriendGamePlayed, "%llu,0x%p", steamIDFriend, pFriendGameInfo)

const char *SteamFriendsWrapper::GetFriendPersonaNameHistory(
    CSteamID steamIDFriend, int iPersonaName)
  _THIN_WRAPPER(GetFriendPersonaNameHistory, "%llu,%i", steamIDFriend, iPersonaName)

bool SteamFriendsWrapper::HasFriend(CSteamID steamIDFriend, int iFriendFlags)
  _THIN_WRAPPER(HasFriend, "%llu,%i", steamIDFriend, iFriendFlags)

int SteamFriendsWrapper::GetClanCount()
  _THIN_WRAPPER(GetClanCount, "")

CSteamID SteamFriendsWrapper::GetClanByIndex(int iClan)
{
  __TRACE("(%i)", iClan);
  CSteamID id;
  SteamFriends_GetClanByIndex(steamFriends, iClan, &id);
  return id;
}

const char *SteamFriendsWrapper::GetClanName(CSteamID steamIDClan)
  _THIN_WRAPPER(GetClanName, "%llu", steamIDClan)

const char *SteamFriendsWrapper::GetClanTag(CSteamID steamIDClan)
  _THIN_WRAPPER(GetClanTag, "%llu", steamIDClan)

bool SteamFriendsWrapper::GetClanActivityCounts(CSteamID steamIDClan,
    int *pnOnline, int *pnInGame, int *pnChatting)
  _THIN_WRAPPER(GetClanActivityCounts, "%llu,0x%p,0x%p,0x%p", steamIDClan, pnOnline, pnInGame, pnChatting)

SteamAPICall_t SteamFriendsWrapper::DownloadClanActivityCounts(
    CSteamID *psteamIDClans, int cClansToRequest)
  _THIN_WRAPPER(DownloadClanActivityCounts, "0x%p,%i", psteamIDClans, cClansToRequest)

int SteamFriendsWrapper::GetFriendCountFromSource(CSteamID steamIDSource)
  _THIN_WRAPPER(GetFriendCountFromSource, "%llu", steamIDSource)

CSteamID SteamFriendsWrapper::GetFriendFromSourceByIndex(CSteamID steamIDSource,
    int iFriend)
{
  __TRACE("(%llu,%i)", steamIDSource, iFriend);
  CSteamID id;
  SteamFriends_GetFriendFromSourceByIndex(steamFriends, steamIDSource, iFriend, &id);
  return id;
}

bool SteamFriendsWrapper::IsUserInSource(CSteamID steamIDUser,
    CSteamID steamIDSource)
  _THIN_WRAPPER(IsUserInSource, "%llu,%llu", steamIDUser, steamIDSource)

void SteamFriendsWrapper::SetInGameVoiceSpeaking(CSteamID steamIDUser,
    bool bSpeaking)
  _THIN_WRAPPER(SetInGameVoiceSpeaking, "%llu,%i", steamIDUser, bSpeaking)

void SteamFriendsWrapper::ActivateGameOverlay(const char *pchDialog)
  _THIN_WRAPPER(ActivateGameOverlay, "\"%s\"", pchDialog)

void SteamFriendsWrapper::ActivateGameOverlayToUser(const char *pchDialog,
    CSteamID steamID)
  _THIN_WRAPPER(ActivateGameOverlayToUser, "\"%s\",%llu", pchDialog, steamID)

void SteamFriendsWrapper::ActivateGameOverlayToWebPage(const char *pchURL)
  _THIN_WRAPPER(ActivateGameOverlayToWebPage, "\"%s\"", pchURL)

void SteamFriendsWrapper::ActivateGameOverlayToStore(AppId_t nAppID, int eFlag)
  _THIN_WRAPPER(ActivateGameOverlayToStore, "%u,%i", nAppID, eFlag)

void SteamFriendsWrapper::SetPlayedWith(CSteamID steamIDUserPlayedWith)
  _THIN_WRAPPER(SetPlayedWith, "%llu", steamIDUserPlayedWith);

void SteamFriendsWrapper::ActivateGameOverlayInviteDialog(CSteamID steamIDLobby)
  _THIN_WRAPPER(ActivateGameOverlayInviteDialog, "%llu", steamIDLobby)

int SteamFriendsWrapper::GetSmallFriendAvatar(CSteamID steamIDFriend)
  _THIN_WRAPPER(GetSmallFriendAvatar, "%llu", steamIDFriend)

int SteamFriendsWrapper::GetMediumFriendAvatar(CSteamID steamIDFriend)
  _THIN_WRAPPER(GetMediumFriendAvatar, "%llu", steamIDFriend)

int SteamFriendsWrapper::GetLargeFriendAvatar(CSteamID steamIDFriend)
  _THIN_WRAPPER(GetLargeFriendAvatar, "%llu", steamIDFriend)

bool SteamFriendsWrapper::RequestUserInformation(CSteamID steamIDUser,
    bool bRequireNameOnly)
  _THIN_WRAPPER(RequestUserInformation, "%llu,%i", steamIDUser, bRequireNameOnly)

SteamAPICall_t SteamFriendsWrapper::RequestClanOfficerList(
    CSteamID steamIDClan)
  _THIN_WRAPPER(RequestClanOfficerList, "%llu", steamIDClan)

CSteamID SteamFriendsWrapper::GetClanOwner(CSteamID steamIDClan)
{
  __TRACE("(%llu)", steamIDClan);
  CSteamID id;
  SteamFriends_GetClanOwner(steamFriends, steamIDClan, &id);
  return id;
}

int SteamFriendsWrapper::GetClanOfficerCount(CSteamID steamIDClan)
  _THIN_WRAPPER(GetClanOfficerCount, "%llu", steamIDClan)

CSteamID SteamFriendsWrapper::GetClanOfficerByIndex(CSteamID steamIDClan,
    int iOfficer)
{
  __TRACE("(%llu,%i)", steamIDClan, iOfficer);
  CSteamID id;
  SteamFriends_GetClanOfficerByIndex(steamFriends, steamIDClan, iOfficer, &id);
  return id;
}

uint32 SteamFriendsWrapper::GetUserRestrictions()
  _THIN_WRAPPER(GetUserRestrictions, "")

bool SteamFriendsWrapper::SetRichPresence(const char *pchKey,
    const char *pchValue)
  _THIN_WRAPPER(SetRichPresence, "\"%s\",\"%s\"", pchKey, pchValue)

void SteamFriendsWrapper::ClearRichPresence()
  _THIN_WRAPPER(ClearRichPresence, "")

const char *SteamFriendsWrapper::GetFriendRichPresence(CSteamID steamIDFriend,
    const char *pchKey)
  _THIN_WRAPPER(GetFriendRichPresence, "%llu,\"%s\"", steamIDFriend, pchKey)

int SteamFriendsWrapper::GetFriendRichPresenceKeyCount(CSteamID steamIDFriend)
  _THIN_WRAPPER(GetFriendRichPresenceKeyCount, "%llu", steamIDFriend)

const char *SteamFriendsWrapper::GetFriendRichPresenceKeyByIndex(
    CSteamID steamIDFriend, int iKey)
  _THIN_WRAPPER(GetFriendRichPresenceKeyByIndex, "%llu,%i", steamIDFriend, iKey)

void SteamFriendsWrapper::RequestFriendRichPresence(CSteamID steamIDFriend)
  _THIN_WRAPPER(RequestFriendRichPresence, "%llu", steamIDFriend)

bool SteamFriendsWrapper::InviteUserToGame(CSteamID steamIDFriend,
    const char *pchConnectString)
  _THIN_WRAPPER(InviteUserToGame, "%llu,\"%s\"", steamIDFriend, pchConnectString)

int SteamFriendsWrapper::GetCoplayFriendCount()
  _THIN_WRAPPER(GetCoplayFriendCount, "")

CSteamID SteamFriendsWrapper::GetCoplayFriend(int iCoplayFriend)
{
  __TRACE("(%i)", iCoplayFriend);
  CSteamID id;
  SteamFriends_GetCoplayFriend(steamFriends, iCoplayFriend, &id);
  return id;
}

int SteamFriendsWrapper::GetFriendCoplayTime(CSteamID steamIDFriend)
  _THIN_WRAPPER(GetFriendCoplayTime, "%llu", steamIDFriend)

AppId_t SteamFriendsWrapper::GetFriendCoplayGame(CSteamID steamIDFriend)
  _THIN_WRAPPER(GetFriendCoplayGame, "%llu", steamIDFriend)

SteamAPICall_t SteamFriendsWrapper::JoinClanChatRoom(CSteamID steamIDClan)
  _THIN_WRAPPER(JoinClanChatRoom, "%llu", steamIDClan)

bool SteamFriendsWrapper::LeaveClanChatRoom(CSteamID steamIDClan)
  _THIN_WRAPPER(LeaveClanChatRoom, "%llu", steamIDClan)

int SteamFriendsWrapper::GetClanChatMemberCount(CSteamID steamIDClan)
  _THIN_WRAPPER(GetClanChatMemberCount, "%llu", steamIDClan)

CSteamID SteamFriendsWrapper::GetChatMemberByIndex(CSteamID steamIDClan, int iUser)
{
  __TRACE("(%llu,%i)", steamIDClan, iUser);
  CSteamID id;
  SteamFriends_GetChatMemberByIndex(steamFriends, steamIDClan, iUser, &id);
  return id;
}

bool SteamFriendsWrapper::SendClanChatMessage(CSteamID steamIDClanChat,
    const char *pchText)
  _THIN_WRAPPER(SendClanChatMessage, "%llu,\"%s\"", steamIDClanChat, pchText)

int SteamFriendsWrapper::GetClanChatMessage(CSteamID steamIDClanChat,
    int iMessage, void *prgchText, int cchTextMax, int *pint, CSteamID *pid)
  _THIN_WRAPPER(GetClanChatMessage, "%llu,%i,0x%p,%i,0x%p,0x%p", steamIDClanChat, iMessage, prgchText,
      cchTextMax, pint, pid)

bool SteamFriendsWrapper::IsClanChatAdmin(CSteamID steamIDClanChat,
    CSteamID steamIDUser)
  _THIN_WRAPPER(IsClanChatAdmin, "%llu,%llu", steamIDClanChat, steamIDUser)

bool SteamFriendsWrapper::IsClanChatWindowOpenInSteam(CSteamID steamIDClanChat)
  _THIN_WRAPPER(IsClanChatWindowOpenInSteam, "%llu", steamIDClanChat)

bool SteamFriendsWrapper::OpenClanChatWindowInSteam(CSteamID steamIDClanChat)
  _THIN_WRAPPER(OpenClanChatWindowInSteam, "%llu", steamIDClanChat)

bool SteamFriendsWrapper::CloseClanChatWindowInSteam(CSteamID steamIDClanChat)
  _THIN_WRAPPER(CloseClanChatWindowInSteam, "%llu", steamIDClanChat)

bool SteamFriendsWrapper::SetListenForFriendsMessages(bool bInterceptEnabled)
  _THIN_WRAPPER(SetListenForFriendsMessages, "%i", bInterceptEnabled)

bool SteamFriendsWrapper::ReplyToFriendMessage(CSteamID steamIDFriend,
    const char *pchMsgToSend)
  _THIN_WRAPPER(ReplyToFriendMessage, "%llu,\"%s\"", steamIDFriend, pchMsgToSend)

int SteamFriendsWrapper::GetFriendMessage(CSteamID steamIDFriend,
    int iMessageID, void *pvData, int cubData, int *peChatEntryType)
  _THIN_WRAPPER(GetFriendMessage, "%llu,%i,0x%p,%i,0x%p", steamIDFriend, iMessageID, pvData, cubData,
    peChatEntryType)

SteamAPICall_t SteamFriendsWrapper::GetFollowerCount(CSteamID steamID)
  _THIN_WRAPPER(GetFollowerCount, "%llu", steamID)

SteamAPICall_t SteamFriendsWrapper::IsFollowing(CSteamID steamID)
  _THIN_WRAPPER(IsFollowing, "%llu", steamID)

SteamAPICall_t SteamFriendsWrapper::EnumerateFollowingList(uint32 unStartIndex)
  _THIN_WRAPPER(EnumerateFollowingList, "%u", unStartIndex)

extern "C"
{

STEAM_API_PROXY_API void *SteamFriends()
{
  __TRACE("");
  return state.getSteamFriends();
}

} // extern "C"


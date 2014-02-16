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

SteamFriendsWrapper::SteamFriendsWrapper() : steamFriends(NULL)
{
  __TRACE("(this=0x%p)", this);
  steamFriends = steam_bridge_SteamFriends();
  __LOG("Wrapping ISteamFriends (0x%p) into (0x%p)", steamFriends, this);
}

const char *SteamFriendsWrapper::GetPersonaName()
{
  __TRACE("()");
  return steam_bridge_SteamFriends_GetPersonaName(steamFriends);
}

SteamAPICall_t SteamFriendsWrapper::SetPersonaName(const char *pchPersonaName)
  __STUB("(\"%s\")", pchPersonaName)

int SteamFriendsWrapper::GetPersonaState()
  __STUB("")

int SteamFriendsWrapper::GetFriendCount(int iFriendFlags)
{
  __TRACE("(%i)", iFriendFlags);
  return steam_bridge_SteamFriends_GetFriendCount(steamFriends, iFriendFlags);
}

CSteamID SteamFriendsWrapper::GetFriendByIndex(int iFriend, int iFriendFlags)
  __STUB("(%i,%i)", iFriend, iFriendFlags)

int SteamFriendsWrapper::GetFriendRelationship(CSteamID steamIDFriend)
  __STUB("(%llu)", steamIDFriend)

int SteamFriendsWrapper::GetFriendPersonaState(CSteamID steamIDFriend)
  __STUB("(%llu)", steamIDFriend)

const char *SteamFriendsWrapper::GetFriendPersonaName(CSteamID steamIDFriend)
  __STUB("(%llu)", steamIDFriend)

bool SteamFriendsWrapper::GetFriendGamePlayed(CSteamID steamIDFriend,
    struct FriendGameInfo_t *pFriendGameInfo)
  __STUB("(%llu,0x%p)", steamIDFriend, pFriendGameInfo)

const char *SteamFriendsWrapper::GetFriendPersonaNameHistory(
    CSteamID steamIDFriend, int iPersonaName)
  __STUB("(%llu,%i)", steamIDFriend, iPersonaName)

bool SteamFriendsWrapper::HasFriend(CSteamID steamIDFriend, int iFriendFlags)
  __STUB("(%llu,%i)", steamIDFriend, iFriendFlags)

int SteamFriendsWrapper::GetClanCount()
  __STUB("")

CSteamID SteamFriendsWrapper::GetClanByIndex(int iClan)
  __STUB("(%i)", iClan)

const char *SteamFriendsWrapper::GetClanName(CSteamID steamIDClan)
  __STUB("(%llu)", steamIDClan)

const char *SteamFriendsWrapper::GetClanTag(CSteamID steamIDClan)
  __STUB("(%llu)", steamIDClan)

bool SteamFriendsWrapper::GetClanActivityCounts(CSteamID steamIDClan,
    int *pnOnline, int *pnInGame, int *pnChatting)
  __STUB("(%llu,0x%p,0x%p,0x%p)", steamIDClan, pnOnline, pnInGame, pnChatting)

SteamAPICall_t SteamFriendsWrapper::DownloadClanActivityCounts(
    CSteamID *psteamIDClans, int cClansToRequest)
  __STUB("(0x%p,%i)", psteamIDClans, cClansToRequest)

int SteamFriendsWrapper::GetFriendCountFromSource(CSteamID steamIDSource)
  __STUB("(%llu)", steamIDSource)

CSteamID SteamFriendsWrapper::GetFriendFromSourceByIndex(CSteamID steamIDSource,
    int iFriend)
  __STUB("(%llu,%i)", steamIDSource, iFriend)

bool SteamFriendsWrapper::IsUserInSource(CSteamID steamIDUser,
    CSteamID steamIDSource)
  __STUB("(%llu,%llu)", steamIDUser, steamIDSource)

void SteamFriendsWrapper::SetInGameVoiceSpeaking(CSteamID steamIDUser,
    bool bSpeaking)
  __STUB("(%llu,%i)", steamIDUser, bSpeaking)

void SteamFriendsWrapper::ActivateGameOverlay(const char *pchDialog)
  __STUB("(\"%s\")", pchDialog)

void SteamFriendsWrapper::ActivateGameOverlayToUser(const char *pchDialog,
    CSteamID steamID)
  __STUB("(\"%s\",%llu)", pchDialog, steamID)

void SteamFriendsWrapper::ActivateGameOverlayToWebPage(const char *pchURL)
  __STUB("(\"%s\")", pchURL)

void SteamFriendsWrapper::ActivateGameOverlayToStore(AppId_t nAppID, int eFlag)
  __STUB("(%u,%i)", nAppID, eFlag)

void SteamFriendsWrapper::SetPlayedWith(CSteamID steamIDUserPlayedWith)
{
  __TRACE("(%llu)", steamIDUserPlayedWith.id);
  steam_bridge_SteamFriends_SetPlayedWith(steamFriends, steamIDUserPlayedWith);
}

void SteamFriendsWrapper::ActivateGameOverlayInviteDialog(CSteamID steamIDLobby)
  __STUB("(%llu)", steamIDLobby)

int SteamFriendsWrapper::GetSmallFriendAvatar(CSteamID steamIDFriend)
  __STUB("(%llu)", steamIDFriend)

int SteamFriendsWrapper::GetMediumFriendAvatar(CSteamID steamIDFriend)
  __STUB("(%llu)", steamIDFriend)

int SteamFriendsWrapper::GetLargeFriendAvatar(CSteamID steamIDFriend)
  __STUB("(%llu)", steamIDFriend)

bool SteamFriendsWrapper::RequestUserInformation(CSteamID steamIDUser,
    bool bRequireNameOnly)
  __STUB("(%llu,%i)", steamIDUser, bRequireNameOnly)

SteamAPICall_t SteamFriendsWrapper::RequestClanOfficerList(
    CSteamID steamIDClan)
  __STUB("(%llu)", steamIDClan)

CSteamID SteamFriendsWrapper::GetClanOwner(CSteamID steamIDClan)
  __STUB("(%llu)", steamIDClan)

int SteamFriendsWrapper::GetClanOfficerCount(CSteamID steamIDClan)
  __STUB("(%llu)", steamIDClan)

CSteamID SteamFriendsWrapper::GetClanOfficerByIndex(CSteamID steamIDClan,
    int iOfficer)
  __STUB("(%llu,%i)", steamIDClan, iOfficer)

uint32 SteamFriendsWrapper::GetUserRestrictions()
  __STUB("")

bool SteamFriendsWrapper::SetRichPresence(const char *pchKey,
    const char *pchValue)
  __STUB("(\"%s\",\"%s\")", pchKey, pchValue)

void SteamFriendsWrapper::ClearRichPresence()
  __STUB("")

const char *SteamFriendsWrapper::GetFriendRichPresence(CSteamID steamIDFriend,
    const char *pchKey)
  __STUB("(%llu,\"%s\")", steamIDFriend, pchKey)

int SteamFriendsWrapper::GetFriendRichPresenceKeyCount(CSteamID steamIDFriend)
  __STUB("(%llu)", steamIDFriend)

const char *SteamFriendsWrapper::GetFriendRichPresenceKeyByIndex(
    CSteamID steamIDFriend, int iKey)
  __STUB("(%llu,%i)", steamIDFriend, iKey)

void SteamFriendsWrapper::RequestFriendRichPresence(CSteamID steamIDFriend)
  __STUB("(%llu)", steamIDFriend)

bool SteamFriendsWrapper::InviteUserToGame(CSteamID steamIDFriend,
    const char *pchConnectString)
  __STUB("(%llu,\"%s\")", steamIDFriend, pchConnectString)

int SteamFriendsWrapper::GetCoplayFriendCount()
  __STUB("")

CSteamID SteamFriendsWrapper::GetCoplayFriend(int iCoplayFriend)
  __STUB("(%i)", iCoplayFriend)

int SteamFriendsWrapper::GetFriendCoplayTime(CSteamID steamIDFriend)
  __STUB("(%llu)", steamIDFriend)

AppId_t SteamFriendsWrapper::GetFriendCoplayGame(CSteamID steamIDFriend)
  __STUB("(%llu)", steamIDFriend)

SteamAPICall_t SteamFriendsWrapper::JoinClanChatRoom(CSteamID steamIDClan)
  __STUB("(%llu)", steamIDClan)

bool SteamFriendsWrapper::LeaveClanChatRoom(CSteamID steamIDClan)
  __STUB("(%llu)", steamIDClan)

int SteamFriendsWrapper::GetClanChatMemberCount(CSteamID steamIDClan)
  __STUB("(%llu)", steamIDClan)

CSteamID SteamFriendsWrapper::GetChatMemberByIndex(CSteamID steamIDClan, int iUser)
  __STUB("(%llu,%i)", steamIDClan, iUser)

bool SteamFriendsWrapper::SendClanChatMessage(CSteamID steamIDClanChat,
    const char *pchText)
  __STUB("(%llu,\"%s\")", steamIDClanChat, pchText)

int SteamFriendsWrapper::GetClanChatMessage(CSteamID steamIDClanChat,
    int iMessage, void *prgchText, int cchTextMax, int *pint, CSteamID *pid)
  __STUB("(%llu,%i,0x%p,%i,0x%p,0x%p)", steamIDClanChat, iMessage, prgchText,
      cchTextMax, pint, pid)

bool SteamFriendsWrapper::IsClanChatAdmin(CSteamID steamIDClanChat,
    CSteamID steamIDUser)
  __STUB("(%llu,%llu)", steamIDClanChat, steamIDUser)

bool SteamFriendsWrapper::IsClanChatWindowOpenInSteam(CSteamID steamIDClanChat)
  __STUB("(%llu)", steamIDClanChat)

bool SteamFriendsWrapper::OpenClanChatWindowInSteam(CSteamID steamIDClanChat)
  __STUB("(%llu)", steamIDClanChat)

bool SteamFriendsWrapper::CloseClanChatWindowInSteam(CSteamID steamIDClanChat)
  __STUB("(%llu)", steamIDClanChat)

bool SteamFriendsWrapper::SetListenForFriendsMessages(bool bInterceptEnabled)
  __STUB("(%i)", bInterceptEnabled)

bool SteamFriendsWrapper::ReplyToFriendMessage(CSteamID steamIDFriend,
    const char *pchMsgToSend)
  __STUB("(%llu,\"%s\")", steamIDFriend, pchMsgToSend)

int SteamFriendsWrapper::GetFriendMessage(CSteamID steamIDFriend,
    int iMessageID, void *pvData, int cubData, int *peChatEntryType)
  __STUB("(%llu,%i,0x%p,%i,0x%p)", steamIDFriend, iMessageID, pvData, cubData,
    peChatEntryType)

SteamAPICall_t SteamFriendsWrapper::GetFollowerCount(CSteamID steamID)
  __STUB("(%llu)", steamID)

SteamAPICall_t SteamFriendsWrapper::IsFollowing(CSteamID steamID)
  __STUB("(%llu)", steamID)

SteamAPICall_t SteamFriendsWrapper::EnumerateFollowingList(uint32 unStartIndex)
  __STUB("(%u)", unStartIndex)

extern "C"
{

STEAM_API_PROXY_API void *SteamFriends()
{
  __TRACE("()");
  return state.getSteamFriends();
}

} // extern "C"


// friends_api.cpp - Implements the friends wrapper and various related APIs.

#include "stdafx.h"

#include <steam_api_bridge.h>

#include "friends_api.h"
#include "logging.h"
#include "state.h"
#include "steam_api_proxy.h"
#include "types.h"

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

uint64 SteamFriendsWrapper::GetFriendByIndex(int iFriend, int iFriendFlags)
  __STUB("(%i,%i)", iFriend, iFriendFlags)

int SteamFriendsWrapper::GetFriendRelationship(uint64 steamIDFriend)
  __STUB("(%lu)", steamIDFriend)

int SteamFriendsWrapper::GetFriendPersonaState(uint64 steamIDFriend)
  __STUB("(%lu)", steamIDFriend)

const char *SteamFriendsWrapper::GetFriendPersonaName(uint64 steamIDFriend)
  __STUB("(%lu)", steamIDFriend)

bool SteamFriendsWrapper::GetFriendGamePlayed(uint64 steamIDFriend,
    FriendGameInfo_t *pFriendGameInfo)
  __STUB("(%lu,0x%p)", steamIDFriend, pFriendGameInfo)

const char *SteamFriendsWrapper::GetFriendPersonaNameHistory(
    uint64 steamIDFriend, int iPersonaName)
  __STUB("(%lu,%i)", steamIDFriend, iPersonaName)

bool SteamFriendsWrapper::HasFriend(uint64 steamIDFriend, int iFriendFlags)
  __STUB("(%lu,%i)", steamIDFriend, iFriendFlags)

int SteamFriendsWrapper::GetClanCount()
  __STUB("")

uint64 SteamFriendsWrapper::GetClanByIndex(int iClan)
  __STUB("(%i)", iClan)

const char *SteamFriendsWrapper::GetClanName(uint64 steamIDClan)
  __STUB("(%lu)", steamIDClan)

const char *SteamFriendsWrapper::GetClanTag(uint64 steamIDClan)
  __STUB("(%lu)", steamIDClan)

bool SteamFriendsWrapper::GetClanActivityCounts(uint64 steamIDClan,
    int *pnOnline, int *pnInGame, int *pnChatting)
  __STUB("(%lu,0x%p,0x%p,0x%p)", steamIDClan, pnOnline, pnInGame, pnChatting)

SteamAPICall_t SteamFriendsWrapper::DownloadClanActivityCounts(
    uint64 *psteamIDClans, int cClansToRequest)
  __STUB("(0x%p,%i)", psteamIDClans, cClansToRequest)

int SteamFriendsWrapper::GetFriendCountFromSource(uint64 steamIDSource)
  __STUB("(%lu)", steamIDSource)

uint64 SteamFriendsWrapper::GetFriendFromSourceByIndex(uint64 steamIDSource,
    int iFriend)
  __STUB("(%i)", iFriend)

bool SteamFriendsWrapper::IsUserInSource(uint64 steamIDUser,
    uint64 steamIDSource)
  __STUB("(%lu,%lu)", steamIDUser, steamIDSource)

void SteamFriendsWrapper::SetInGameVoiceSpeaking(uint64 steamIDUser, bool bSpeaking)
  __STUB("(%lu,%i)", steamIDUser, bSpeaking)

void SteamFriendsWrapper::ActivateGameOverlay(const char *pchDialog)
  __STUB("(\"%s\")", pchDialog)

void SteamFriendsWrapper::ActivateGameOverlayToUser(const char *pchDialog,
    uint64 steamID)
  __STUB("(\"%s\",%lu)", pchDialog, steamID)

void SteamFriendsWrapper::ActivateGameOverlayToWebPage(const char *pchURL)
  __STUB("(\"%s\")", pchURL)

void SteamFriendsWrapper::ActivateGameOverlayToStore(AppId_t nAppID, int eFlag)
  __STUB("(%u,%i)", nAppID, eFlag)

void SteamFriendsWrapper::SetPlayedWith(uint64 steamIDUserPlayedWith)
  __STUB("(%lu)", steamIDUserPlayedWith)

void SteamFriendsWrapper::ActivateGameOverlayInviteDialog(uint64 steamIDLobby)
  __STUB("(%lu)", steamIDLobby)

int SteamFriendsWrapper::GetSmallFriendAvatar(uint64 steamIDFriend)
  __STUB("(%lu)", steamIDFriend)

int SteamFriendsWrapper::GetMediumFriendAvatar(uint64 steamIDFriend)
  __STUB("(%lu)", steamIDFriend)

int SteamFriendsWrapper::GetLargeFriendAvatar(uint64 steamIDFriend)
  __STUB("(%lu)", steamIDFriend)

bool SteamFriendsWrapper::RequestUserInformation(uint64 steamIDUser,
    bool bRequireNameOnly)
  __STUB("(%lu,%i)", steamIDUser, bRequireNameOnly)

SteamAPICall_t SteamFriendsWrapper::RequestClanOfficerList(uint64 steamIDClan)
  __STUB("(%lu)", steamIDClan)

uint64 SteamFriendsWrapper::GetClanOwner(uint64 steamIDClan)
  __STUB("(%lu)", steamIDClan)

int SteamFriendsWrapper::GetClanOfficerCount(uint64 steamIDClan)
  __STUB("(%lu)", steamIDClan)

uint64 SteamFriendsWrapper::GetClanOfficerByIndex(uint64 steamIDClan,
    int iOfficer)
  __STUB("(%lu,%i)", steamIDClan, iOfficer)

uint32 SteamFriendsWrapper::GetUserRestrictions()
  __STUB("")

bool SteamFriendsWrapper::SetRichPresence(const char *pchKey,
    const char *pchValue)
  __STUB("(\"%s\",\"%s\")", pchKey, pchValue)

void SteamFriendsWrapper::ClearRichPresence()
  __STUB("")

const char *SteamFriendsWrapper::GetFriendRichPresence(uint64 steamIDFriend,
    const char *pchKey)
  __STUB("(%lu,\"%s\")", steamIDFriend, pchKey)

int SteamFriendsWrapper::GetFriendRichPresenceKeyCount(uint64 steamIDFriend)
  __STUB("(%lu)", steamIDFriend)

const char *SteamFriendsWrapper::GetFriendRichPresenceKeyByIndex(
    uint64 steamIDFriend, int iKey)
  __STUB("(%lu,%i)", steamIDFriend, iKey)

void SteamFriendsWrapper::RequestFriendRichPresence(uint64 steamIDFriend)
  __STUB("(%lu)", steamIDFriend)

bool SteamFriendsWrapper::InviteUserToGame(uint64 steamIDFriend,
    const char *pchConnectString)
  __STUB("(%lu,\"%s\")", steamIDFriend, pchConnectString)

int SteamFriendsWrapper::GetCoplayFriendCount()
  __STUB()

uint64 SteamFriendsWrapper::GetCoplayFriend(int iCoplayFriend)
  __STUB("(%i)", iCoplayFriend)

int SteamFriendsWrapper::GetFriendCoplayTime(uint64 steamIDFriend)
  __STUB("(%lu)", steamIDFriend)

AppId_t SteamFriendsWrapper::GetFriendCoplayGame(uint64 steamIDFriend)
  __STUB("(%lu)", steamIDFriend)

SteamAPICall_t SteamFriendsWrapper::JoinClanChatRoom(uint64 steamIDClan)
  __STUB("(%lu)", steamIDClan)

bool SteamFriendsWrapper::LeaveClanChatRoom(uint64 steamIDClan)
  __STUB("(%lu)", steamIDClan)

int SteamFriendsWrapper::GetClanChatMemberCount(uint64 steamIDClan)
  __STUB("(%lu)", steamIDClan)

uint64 SteamFriendsWrapper::GetChatMemberByIndex(uint64 steamIDClan, int iUser)
  __STUB("(%lu,%i)", steamIDClan, iUser)

bool SteamFriendsWrapper::SendClanChatMessage(uint64 steamIDClanChat,
    const char *pchText)
  __STUB("(%lu,\"%s\")", steamIDClanChat, pchText)

int SteamFriendsWrapper::GetClanChatMessage(uint64 steamIDClanChat,
    int iMessage, void *prgchText, int cchTextMax, int *pint, uint64 *puint64)
  __STUB("(%lu,%i,0x%p,%i,0x%p,0x%p)", steamIDClanChat, iMessage, prgchText,
      cchTextMax, pint, puint64)

bool SteamFriendsWrapper::IsClanChatAdmin(uint64 steamIDClanChat,
    uint64 steamIDUser)
  __STUB(("(%lu,%lu)", steamIDClanChat, steamIDUser)

bool SteamFriendsWrapper::IsClanChatWindowOpenInSteam(uint64 steamIDClanChat)
  __STUB("(%lu)", steamIDClanChat)

bool SteamFriendsWrapper::OpenClanChatWindowInSteam(uint64 steamIDClanChat)
  __STUB("(%lu)", steamIDClanChat)

bool SteamFriendsWrapper::CloseClanChatWindowInSteam(uint64 steamIDClanChat)
  __STUB("(%lu)", steamIDClanChat)

bool SteamFriendsWrapper::SetListenForFriendsMessages(bool bInterceptEnabled)
  __STUB("(%i)", bInterceptEnabled)

bool SteamFriendsWrapper::ReplyToFriendMessage(uint64 steamIDFriend,
  const char *pchMsgToSend)
  __STUB("(%lu,\"%s\")", steamIDFriend, pchMsgToSend)

int SteamFriendsWrapper::GetFriendMessage(uint64 steamIDFriend, int iMessageID,
  void *pvData, int cubData, int *peChatEntryType)
  __STUB("(%lu,%i,0x%p,%i,0x%p)", steamIDFriend, iMessageID, pvData, cubData,
    peChatEntryType)

SteamAPICall_t SteamFriendsWrapper::GetFollowerCount(uint64 steamID)
  __STUB("(%lu)", steamID)

SteamAPICall_t SteamFriendsWrapper::IsFollowing(uint64 steamID)
  __STUB("(%lu)", steamID)

SteamAPICall_t SteamFriendsWrapper::EnumerateFollowingList(uint32 unStartIndex)
  __STUB("(%u)", unStartIndex)

extern "C"
{

STEAM_API_PROXY_API void *SteamFriends()
{
  __TRACE();
  return state.getSteamFriends();
}

} // extern "C"


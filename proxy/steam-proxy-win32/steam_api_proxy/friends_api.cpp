// friendsl_api.cpp - Implements the friends wrapper and various related APIs.
#include "stdafx.h"

#include <steam_api_bridge.h>

#include "friends_api.h"
#include "logging.h"
#include "state.h"
#include "steam_api_proxy.h"
#include "types.h"


SteamFriendsWrapper::SteamFriendsWrapper()
{
  isteamfriends = steam_bridge_SteamFriends();
}

const char *SteamFriendsWrapper::GetPersonaName()
{
  return steam_bridge_SteamFriends_GetPersonaName(isteamfriends);
}

uint64 SteamFriendsWrapper::SetPersonaName(const char *pchPersonaName)
  __STUB__

int SteamFriendsWrapper::GetPersonaState()
  __STUB__

int SteamFriendsWrapper::GetFriendCount(int iFriendFlags)
{
  return steam_bridge_SteamFriends_GetFriendCount(isteamfriends, iFriendFlags);
}

uint64 SteamFriendsWrapper::GetFriendByIndex(int iFriend, int iFriendFlags)
  __STUB__

int SteamFriendsWrapper::GetFriendRelationship(uint64 steamIDFriend)
  __STUB__

int SteamFriendsWrapper::GetFriendPersonaState(uint64 steamIDFriend)
  __STUB__

const char *SteamFriendsWrapper::GetFriendPersonaName(uint64 steamIDFriend)
  __STUB__

bool SteamFriendsWrapper::GetFriendGamePlayed(uint64 steamIDFriend, FriendGameInfo_t *pFriendGameInfo )
  __STUB__

const char *SteamFriendsWrapper::GetFriendPersonaNameHistory(uint64 steamIDFriend, int iPersonaName)
  __STUB__

bool SteamFriendsWrapper::HasFriend(uint64 steamIDFriend, int iFriendFlags)
  __STUB__

int SteamFriendsWrapper::GetClanCount()
  __STUB__

uint64 SteamFriendsWrapper::GetClanByIndex(int iClan)
  __STUB__

const char *SteamFriendsWrapper::GetClanName(uint64 steamIDClan)
  __STUB__

const char *SteamFriendsWrapper::GetClanTag(uint64 steamIDClan)
  __STUB__

bool SteamFriendsWrapper::GetClanActivityCounts(uint64 steamIDClan, int *pnOnline, int *pnInGame, int *pnChatting)
  __STUB__

uint64 SteamFriendsWrapper::DownloadClanActivityCounts(uint64 *psteamIDClans, int cClansToRequest)
  __STUB__

int SteamFriendsWrapper::GetFriendCountFromSource(uint64 steamIDSource)
  __STUB__

uint64 SteamFriendsWrapper::GetFriendFromSourceByIndex(uint64 steamIDSource, int iFriend)
  __STUB__

bool SteamFriendsWrapper::IsUserInSource(uint64 steamIDUser, uint64 steamIDSource)
  __STUB__

void SteamFriendsWrapper::SetInGameVoiceSpeaking(uint64 steamIDUser, bool bSpeaking)
  __STUB__

void SteamFriendsWrapper::ActivateGameOverlay(const char *pchDialog)
  __STUB__

void SteamFriendsWrapper::ActivateGameOverlayToUser(const char *pchDialog, uint64 steamID)
  __STUB__

void SteamFriendsWrapper::ActivateGameOverlayToWebPage(const char *pchURL)
  __STUB__

void SteamFriendsWrapper::ActivateGameOverlayToStore(uint32 nAppID, int eFlag)
  __STUB__

void SteamFriendsWrapper::SetPlayedWith(uint64 steamIDUserPlayedWith)
  __STUB__

void SteamFriendsWrapper::ActivateGameOverlayInviteDialog(uint64 steamIDLobby)
  __STUB__

int SteamFriendsWrapper::GetSmallFriendAvatar(uint64 steamIDFriend)
  __STUB__

int SteamFriendsWrapper::GetMediumFriendAvatar(uint64 steamIDFriend)
  __STUB__

int SteamFriendsWrapper::GetLargeFriendAvatar(uint64 steamIDFriend)
  __STUB__

bool SteamFriendsWrapper::RequestUserInformation(uint64 steamIDUser, bool bRequireNameOnly)
  __STUB__

uint64 SteamFriendsWrapper::RequestClanOfficerList(uint64 steamIDClan)
  __STUB__

uint64 SteamFriendsWrapper::GetClanOwner(uint64 steamIDClan)
  __STUB__

int SteamFriendsWrapper::GetClanOfficerCount(uint64 steamIDClan)
  __STUB__

uint64 SteamFriendsWrapper::GetClanOfficerByIndex(uint64 steamIDClan, int iOfficer)
  __STUB__

uint32 SteamFriendsWrapper::GetUserRestrictions()
  __STUB__

bool SteamFriendsWrapper::SetRichPresence(const char *pchKey, const char *pchValue)
  __STUB__

void SteamFriendsWrapper::ClearRichPresence()
  __STUB__

const char *SteamFriendsWrapper::GetFriendRichPresence(uint64 steamIDFriend, const char *pchKey)
  __STUB__

int SteamFriendsWrapper::GetFriendRichPresenceKeyCount(uint64 steamIDFriend)
  __STUB__

const char *SteamFriendsWrapper::GetFriendRichPresenceKeyByIndex(uint64 steamIDFriend, int iKey)
  __STUB__

void SteamFriendsWrapper::RequestFriendRichPresence(uint64 steamIDFriend)
  __STUB__

bool SteamFriendsWrapper::InviteUserToGame(uint64 steamIDFriend, const char *pchConnectString)
  __STUB__

int SteamFriendsWrapper::GetCoplayFriendCount()
  __STUB__

uint64 SteamFriendsWrapper::GetCoplayFriend(int iCoplayFriend)
  __STUB__

int SteamFriendsWrapper::GetFriendCoplayTime(uint64 steamIDFriend)
  __STUB__

uint32 SteamFriendsWrapper::GetFriendCoplayGame(uint64 steamIDFriend)
  __STUB__

uint64 SteamFriendsWrapper::JoinClanChatRoom(uint64 steamIDClan)
  __STUB__

bool SteamFriendsWrapper::LeaveClanChatRoom(uint64 steamIDClan)
  __STUB__

int SteamFriendsWrapper::GetClanChatMemberCount(uint64 steamIDClan)
  __STUB__

uint64 SteamFriendsWrapper::GetChatMemberByIndex(uint64 steamIDClan, int iUser)
  __STUB__

bool SteamFriendsWrapper::SendClanChatMessage(uint64 steamIDClanChat, const char *pchText)
  __STUB__

int SteamFriendsWrapper::GetClanChatMessage(uint64 steamIDClanChat, int iMessage, void *prgchText, int cchTextMax, int *, uint64 * )
  __STUB__

bool SteamFriendsWrapper::IsClanChatAdmin(uint64 steamIDClanChat, uint64 steamIDUser)
  __STUB__

bool SteamFriendsWrapper::IsClanChatWindowOpenInSteam(uint64 steamIDClanChat)
  __STUB__

bool SteamFriendsWrapper::OpenClanChatWindowInSteam(uint64 steamIDClanChat)
  __STUB__

bool SteamFriendsWrapper::CloseClanChatWindowInSteam(uint64 steamIDClanChat )
  __STUB__

bool SteamFriendsWrapper::SetListenForFriendsMessages(bool bInterceptEnabled )
  __STUB__

bool SteamFriendsWrapper::ReplyToFriendMessage(uint64 steamIDFriend, const char *pchMsgToSend)
  __STUB__

int SteamFriendsWrapper::GetFriendMessage(uint64 steamIDFriend, int iMessageID, void *pvData, int cubData, int *peChatEntryType)
  __STUB__

uint64 SteamFriendsWrapper::GetFollowerCount(uint64 steamID)
  __STUB__

uint64 SteamFriendsWrapper::IsFollowing(uint64 steamID)
  __STUB__

uint64 SteamFriendsWrapper::EnumerateFollowingList(uint32 unStartIndex)
  __STUB__

extern "C"
{

STEAM_API_PROXY_API void *SteamFriends()
{
  return state.getSteamFriends();
}

} // extern "C"


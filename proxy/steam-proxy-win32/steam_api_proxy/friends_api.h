// friends_api.h - Header for the friends_api code (specifically 
//                 SteamFriendsWrapper)

#pragma once

#include <string>

#include "types.h"

// TODO: This is a placeholder, need to investigate how this is being
//       packed in the real steam_api libraries.
struct FriendGameInfo_t
{
	uint64 m_gameID1;
	uint64 m_gameID2;
	uint32 m_unGameIP;
	uint16 m_usGamePort;
	uint16 m_usQueryPort;
	uint64 m_steamIDLobby;
};

class SteamFriendsWrapper
{
  public:
    SteamFriendsWrapper();

    virtual const char *GetPersonaName();

    virtual SteamAPICall_t SetPersonaName(const char *pchPersonaName);

    // EPersonaState ... ()
    virtual int GetPersonaState();

    virtual int GetFriendCount(int iFriendFlags);

    // CSteamID ... (int, int)
    virtual uint64 GetFriendByIndex(int iFriend, int iFriendFlags);

    // returns a relationship to a user
    // int ... (CSteamID)
    virtual int GetFriendRelationship(uint64 steamIDFriend);

    // EPersonaState ... (CSteamID)
    virtual int GetFriendPersonaState(uint64 steamIDFriend);

    // FYI: This function is 'guarenteed' to not return NULL
    // const char * ... (CSteamID)
    virtual const char *GetFriendPersonaName(uint64 steamIDFriend);

    // bool ... (CSteamID, FriendGameInfo_t *)
    virtual bool GetFriendGamePlayed(uint64 steamIDFriend, FriendGameInfo_t *pFriendGameInfo );

    // const char * ... (CSteamID, int)
    virtual const char *GetFriendPersonaNameHistory(uint64 steamIDFriend, int iPersonaName);

    // bool ... (CSteamID, int)
    virtual bool HasFriend(uint64 steamIDFriend, int iFriendFlags);

    virtual int GetClanCount();

    // CSteamID ... (int)
    virtual uint64 GetClanByIndex(int iClan);

    // const char * ... (CSteamID)
    virtual const char *GetClanName(uint64 steamIDClan);

    // const char * ... (CSteamID)
    virtual const char *GetClanTag(uint64 steamIDClan);

    // bool ... (CSteamID, int *, int *, int *)
    virtual bool GetClanActivityCounts(uint64 steamIDClan, int *pnOnline, int *pnInGame, int *pnChatting);

    // virtual SteamAPICall_t ... (CSteamID *psteamIDClans, int cClansToRequest)
    virtual SteamAPICall_t DownloadClanActivityCounts(uint64 *psteamIDClans, int cClansToRequest);

    // int ... (CSteamID)
    virtual int GetFriendCountFromSource(uint64 steamIDSource);

    // CSteamID ... (CSteamID, int)
    virtual uint64 GetFriendFromSourceByIndex(uint64 steamIDSource, int iFriend);

    // bool ... (CSteamID, CSteamID)
    virtual bool IsUserInSource(uint64 steamIDUser, uint64 steamIDSource);

    // void ... (CSteamID, bool)
    virtual void SetInGameVoiceSpeaking(uint64 steamIDUser, bool bSpeaking);

    virtual void ActivateGameOverlay(const char *pchDialog);

    // void ... (const char *, CSteamID)
    virtual void ActivateGameOverlayToUser(const char *pchDialog, uint64 steamID);

    virtual void ActivateGameOverlayToWebPage(const char *pchURL);

    // void ... (AppId_t, EOverlayToStoreFlag)
    virtual void ActivateGameOverlayToStore(AppId_t nAppID, int eFlag);

    // void ... (CSteamID)
    virtual void SetPlayedWith(uint64 steamIDUserPlayedWith);

    // void ... (CSteamID)
    virtual void ActivateGameOverlayInviteDialog(uint64 steamIDLobby);

    // int ... (CSteamID)
    virtual int GetSmallFriendAvatar(uint64 steamIDFriend);

    // int ... (CSteamID)
    virtual int GetMediumFriendAvatar(uint64 steamIDFriend);

    // int ... (CSteamID)
    virtual int GetLargeFriendAvatar(uint64 steamIDFriend);

    // bool ... (CSteamID, bool)
    virtual bool RequestUserInformation(uint64 steamIDUser, bool bRequireNameOnly);

    // SteamAPICall_t ... (CSteamID)
    virtual SteamAPICall_t RequestClanOfficerList(uint64 steamIDClan);

    // CSteamID ... (CSteamID)
    virtual uint64 GetClanOwner(uint64 steamIDClan);

    // int ... (CSteamID)
    virtual int GetClanOfficerCount(uint64 steamIDClan);

    // CSteamID ... (CSteamID, int)
    virtual uint64 GetClanOfficerByIndex(uint64 steamIDClan, int iOfficer);

    virtual uint32 GetUserRestrictions();

    virtual bool SetRichPresence(const char *pchKey, const char *pchValue);

    virtual void ClearRichPresence();

    // const char * ... (CSteamID, const char *)
    virtual const char *GetFriendRichPresence(uint64 steamIDFriend, const char *pchKey);

    // int ... (CSteamID)
    virtual int GetFriendRichPresenceKeyCount(uint64 steamIDFriend);

    // const char * ... (CSteamID, int)
    virtual const char *GetFriendRichPresenceKeyByIndex(uint64 steamIDFriend, int iKey);

    // void ... (CSteamID)
    virtual void RequestFriendRichPresence(uint64 steamIDFriend);

    // bool ... (CSteamID, const char *)
    virtual bool InviteUserToGame(uint64 steamIDFriend, const char *pchConnectString);

    virtual int GetCoplayFriendCount();

    // CSteamID ... (int)
    virtual uint64 GetCoplayFriend(int iCoplayFriend);

    // int ... (CSteamID)
    virtual int GetFriendCoplayTime(uint64 steamIDFriend);

    // AppId_t ... (CSteamID)
    virtual AppId_t GetFriendCoplayGame(uint64 steamIDFriend);

    // SteamAPICall_t ... (CSteamID)
    virtual SteamAPICall_t JoinClanChatRoom(uint64 steamIDClan);

    // bool ... (CSteamID)
    virtual bool LeaveClanChatRoom(uint64 steamIDClan);

    // int ... (CSteamID)
    virtual int GetClanChatMemberCount(uint64 steamIDClan);

    // CSteamID ... (CSteamID, int)
    virtual uint64 GetChatMemberByIndex(uint64 steamIDClan, int iUser);

    // bool ... (CSteamID, const char *)
    virtual bool SendClanChatMessage(uint64 steamIDClanChat, const char *pchText);

    // The last two parameters aren't named in the isteamfriends.h header.
    // Persumably just an oversight.
    // int ... (CSteamID, int, void *, int, EChatEntryType *, CSteamID *)
    virtual int GetClanChatMessage(uint64 steamIDClanChat, int iMessage, void *prgchText, int cchTextMax, int *, uint64 *);

    // bool ... (CSteamID, CSteamID)
    virtual bool IsClanChatAdmin(uint64 steamIDClanChat, uint64 steamIDUser);

    // bool ... (CSteamID)
    virtual bool IsClanChatWindowOpenInSteam(uint64 steamIDClanChat);

    // bool ... (CSteamID)
    virtual bool OpenClanChatWindowInSteam(uint64 steamIDClanChat);

    // bool ... (CSteamID)
    virtual bool CloseClanChatWindowInSteam(uint64 steamIDClanChat );

    // bool ... (bool)
    virtual bool SetListenForFriendsMessages(bool bInterceptEnabled );

    // bool ... (CSteamID, const char *)
    virtual bool ReplyToFriendMessage(uint64 steamIDFriend, const char *pchMsgToSend);

    // int ... (CSteamID, int, void *, int, EChatEntryType *)
    virtual int GetFriendMessage(uint64 steamIDFriend, int iMessageID, void *pvData, int cubData, int *peChatEntryType);

    // SteamAPICall_t ... (CSteamID)
    virtual SteamAPICall_t GetFollowerCount(uint64 steamID);

    // SteamAPICall_t ... (CSteamID)
    virtual SteamAPICall_t IsFollowing(uint64 steamID);

    virtual SteamAPICall_t EnumerateFollowingList(uint32 unStartIndex);

  private:
    class ISteamFriends *steamFriends;
};


// types.h - Defines various types used project wide.
// Note that this is heavily based off of steamtypes.h, plus including
// various relevant typedefs and whatnot from other Steam headers.

#pragma once

#define APP_NAME "SteamRedirect"

typedef unsigned char uint8;
typedef signed char int8;

typedef __int16 int16;
typedef unsigned __int16 uint16;
typedef __int32 int32;
typedef unsigned __int32 uint32;
typedef __int64 int64;
typedef unsigned __int64 uint64;

typedef __int32 intp;
typedef unsigned __int32 uintp;

struct CGameID
{
  uint64 a;
  uint64 b;
};


const int k_cubSaltSize   = 8;
typedef	uint8 Salt_t[ k_cubSaltSize ];

//-----------------------------------------------------------------------------
// GID (GlobalID) stuff
// This is a globally unique identifier.  It's guaranteed to be unique across all
// racks and servers for as long as a given universe persists.
//-----------------------------------------------------------------------------
// NOTE: for GID parsing/rendering and other utils, see gid.h
typedef uint64 GID_t;

const GID_t k_GIDNil = 0xffffffffffffffffull;

// For convenience, we define a number of types that are just new names for GIDs
typedef GID_t JobID_t;			// Each Job has a unique ID
typedef GID_t TxnID_t;			// Each financial transaction has a unique ID

const GID_t k_TxnIDNil = k_GIDNil;
const GID_t k_TxnIDUnknown = 0;


// this is baked into client messages and interfaces as an int, 
// make sure we never break this.
typedef uint32 PackageId_t;
const PackageId_t k_uPackageIdFreeSub = 0x0;
const PackageId_t k_uPackageIdInvalid = 0xFFFFFFFF;


// this is baked into client messages and interfaces as an int, 
// make sure we never break this.
typedef uint32 AppId_t;
const AppId_t k_uAppIdInvalid = 0x0;

typedef uint64 AssetClassId_t;
const AssetClassId_t k_ulAssetClassIdInvalid = 0x0;

typedef uint32 PhysicalItemId_t;
const PhysicalItemId_t k_uPhysicalItemIdInvalid = 0x0;


// this is baked into client messages and interfaces as an int, 
// make sure we never break this.  AppIds and DepotIDs also presently
// share the same namespace, but since we'd like to change that in the future
// I've defined it seperately here.
typedef uint32 DepotId_t;
const DepotId_t k_uDepotIdInvalid = 0x0;

// RTime32
// We use this 32 bit time representing real world time.
// It offers 1 second resolution beginning on January 1, 1970 (Unix time)
typedef uint32 RTime32;

typedef uint32 CellID_t;
const CellID_t k_uCellIDInvalid = 0xFFFFFFFF;

// handle to a Steam API call
typedef uint64 SteamAPICall_t;
const SteamAPICall_t k_uAPICallInvalid = 0x0;

typedef uint32 AccountID_t;

typedef uint32 PartnerId_t;
const PartnerId_t k_uPartnerIdInvalid = 0;

typedef int32 HSteamPipe;
typedef int32 HSteamUser;

typedef void (*PFNPreMinidumpCallback)(void *context);

typedef uint32 HAuthTicket;

// TODO: Would we ever want an import?  Should we explictly say __cdecl
//       somewhere/somehow?
#ifdef STEAM_API_PROXY_EXPORTS
#define STEAM_API_PROXY_API __declspec(dllexport)
#else
#define STEAM_API_PROXY_API __declspec(dllimport)
#endif


#ifndef _DOORS_
#define _DOORS_

#ifndef _INC_DOORS
#define _INC_DOORS

#pragma region Family Partition
#if DORAPI_FAMILY_PARTITION(DORAPI_PARTITION_APP | DORAPI_PARTITION_SYSTEM | DORAPI_PARTITION_GAMES)

#if defined(RC_INVOKED) && !defined(NOWINRES)

#else
/**
@file
UEFI OS based application.

Copyright (c) 2020, Intel Corporation. All rights reserved.<BR>
SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef __SPDM_DUMP_H__
#define __SPDM_DUMP_H__

#include <Base.h>
#include <IndustryStandard/Spdm.h>
#include <IndustryStandard/SpdmSecuredMessage.h>
#include <IndustryStandard/MctpBinding.h>
#include <IndustryStandard/PciDoeBinding.h>
#include <IndustryStandard/Pcap.h>
#include <IndustryStandard/LinkTypeEx.h>

#include "OsInclude.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

BOOLEAN
OpenPcapPacketFile (
  IN CHAR8  *PcapFileName
  );

VOID
ClosePcapPacketFile (
  VOID
  );

VOID
DumpPcap (
  VOID
  );

UINT32
GetDataLinkType (
  VOID
  );

VOID
DumpData (
  IN UINT8  *Data,
  IN UINTN  Size
  );

VOID
DumpHex (
  IN UINT8  *Data,
  IN UINTN  Size
  );

VOID
DumpMctpPacket (
  IN VOID    *Buffer,
  IN UINTN   BufferSize,
  IN BOOLEAN Truncated
  );

VOID
DumpPciDoePacket (
  IN VOID    *Buffer,
  IN UINTN   BufferSize,
  IN BOOLEAN Truncated
  );

VOID
DumpSpdmPacket (
  IN VOID    *Buffer,
  IN UINTN   BufferSize,
  IN BOOLEAN Truncated
  );

VOID
DumpSecuredSpdmPacket (
  IN VOID    *Buffer,
  IN UINTN   BufferSize,
  IN BOOLEAN Truncated
  );

extern BOOLEAN  mParamQuiteMode;
extern BOOLEAN  mParamAllMode;
extern BOOLEAN  mParamDumpAsn1;
extern BOOLEAN  mParamDumpVendorApp;
extern BOOLEAN  mParamDumpHex;
extern CHAR8    *mParamPsk;
extern CHAR8    *mParamReqDhePrivKey;
extern CHAR8    *mParamRspDhePrivKey;

#endif
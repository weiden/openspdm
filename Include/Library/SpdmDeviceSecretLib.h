/** @file
  SPDM device secret library.
  It follows the SPDM Specification.

Copyright (c) 2020, Intel Corporation. All rights reserved.<BR>
SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef __SPDM_DEVICE_SECRET_LIB_H__
#define __SPDM_DEVICE_SECRET_LIB_H__

#include "SpdmLibConfig.h"

#include <Base.h>
#include <IndustryStandard/Spdm.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BaseCryptLib.h>
#include <Library/SpdmCryptLib.h>

/**
  Collect the device measurement.

  @param  MeasurementSpecification     Indicates the measurement specification.
                                       It must align with MeasurementSpecification (SPDM_MEASUREMENT_BLOCK_HEADER_SPECIFICATION_*)
  @param  MeasurementHashAlgo          Indicates the measurement hash algorithm.
                                       It must align with MeasurementHashAlgo (SPDM_ALGORITHMS_MEASUREMENT_HASH_ALGO_*)
  @param  DeviceMeasurementCount       The count of the device measurement block.
  @param  DeviceMeasurement            A pointer to a destination buffer to store the concatenation of all device measurement blocks.
  @param  DeviceMeasurementSize        On input, indicates the size in bytes of the destination buffer.
                                       On output, indicates the size in bytes of all device measurement blocks in the buffer.

  @retval TRUE  the device measurement collection success and measurement is returned.
  @retval FALSE the device measurement collection fail.
**/
typedef
BOOLEAN
(EFIAPI *SPDM_MEASUREMENT_COLLECTION_FUNC) (
  IN      UINT8        MeasurementSpecification,
  IN      UINT32       MeasurementHashAlgo,
     OUT  UINT8        *DeviceMeasurementCount,
     OUT  VOID         *DeviceMeasurement,
  IN OUT  UINTN        *DeviceMeasurementSize
  );

/**
  Sign an SPDM message data.

  @param  ReqBaseAsymAlg               Indicates the signing algorithm.
  @param  MessageHash                  A pointer to a message hash to be signed.
  @param  HashSize                     The size in bytes of the message hash to be signed.
  @param  Signature                    A pointer to a destination buffer to store the signature.
  @param  SigSize                      On input, indicates the size in bytes of the destination buffer to store the signature.
                                       On output, indicates the size in bytes of the signature in the buffer.

  @retval TRUE  signing success.
  @retval FALSE signing fail.
**/
typedef
BOOLEAN
(EFIAPI *SPDM_REQUESTER_DATA_SIGN_FUNC) (
  IN      UINT16       ReqBaseAsymAlg,
  IN      CONST UINT8  *MessageHash,
  IN      UINTN        HashSize,
     OUT  UINT8        *Signature,
  IN OUT  UINTN        *SigSize
  );

/**
  Sign an SPDM message data.

  @param  BaseAsymAlgo                 Indicates the signing algorithm.
  @param  MessageHash                  A pointer to a message hash to be signed.
  @param  HashSize                     The size in bytes of the message hash to be signed.
  @param  Signature                    A pointer to a destination buffer to store the signature.
  @param  SigSize                      On input, indicates the size in bytes of the destination buffer to store the signature.
                                       On output, indicates the size in bytes of the signature in the buffer.

  @retval TRUE  signing success.
  @retval FALSE signing fail.
**/
typedef
BOOLEAN
(EFIAPI *SPDM_RESPONDER_DATA_SIGN_FUNC) (
  IN      UINT32       BaseAsymAlgo,
  IN      CONST UINT8  *MessageHash,
  IN      UINTN        HashSize,
     OUT  UINT8        *Signature,
  IN OUT  UINTN        *SigSize
  );

/**
  Derive HMAC-based Expand Key Derivation Function (HKDF) Expand, based upon the negotiated HKDF algorithm.

  @param  HashAlgo                     Indicates the hash algorithm.
                                       It must align with BaseHashAlgo (SPDM_ALGORITHMS_BASE_HASH_ALGO_TPM_ALG_*)
  @param  PskHint                      Pointer to the user-supplied PSK Hint.
  @param  PskHintSize                  PSK Hint size in bytes.
  @param  Info                         Pointer to the application specific info.
  @param  InfoSize                     Info size in bytes.
  @param  Out                          Pointer to buffer to receive hkdf value.
  @param  OutSize                      Size of hkdf bytes to generate.

  @retval TRUE   Hkdf generated successfully.
  @retval FALSE  Hkdf generation failed.
**/
typedef
BOOLEAN
(EFIAPI *SPDM_PSK_HKDF_EXPAND_FUNC) (
  IN      UINT32       HashAlgo,
  IN      CONST UINT8  *PskHint, OPTIONAL
  IN      UINTN        PskHintSize, OPTIONAL
  IN      CONST UINT8  *Info,
  IN      UINTN        InfoSize,
     OUT  UINT8        *Out,
  IN      UINTN        OutSize
  );

/**
  Collect the device measurement.

  @param  MeasurementSpecification     Indicates the measurement specification.
                                       It must align with MeasurementSpecification (SPDM_MEASUREMENT_BLOCK_HEADER_SPECIFICATION_*)
  @param  MeasurementHashAlgo          Indicates the measurement hash algorithm.
                                       It must align with MeasurementHashAlgo (SPDM_ALGORITHMS_MEASUREMENT_HASH_ALGO_*)
  @param  DeviceMeasurementCount       The count of the device measurement block.
  @param  DeviceMeasurement            A pointer to a destination buffer to store the concatenation of all device measurement blocks.
  @param  DeviceMeasurementSize        On input, indicates the size in bytes of the destination buffer.
                                       On output, indicates the size in bytes of all device measurement blocks in the buffer.

  @retval TRUE  the device measurement collection success and measurement is returned.
  @retval FALSE the device measurement collection fail.
**/
BOOLEAN
EFIAPI
SpdmMeasurementCollectionFunc (
  IN      UINT8        MeasurementSpecification,
  IN      UINT32       MeasurementHashAlgo,
     OUT  UINT8        *DeviceMeasurementCount,
     OUT  VOID         *DeviceMeasurement,
  IN OUT  UINTN        *DeviceMeasurementSize
  );

/**
  Sign an SPDM message data.

  @param  ReqBaseAsymAlg               Indicates the signing algorithm.
  @param  MessageHash                  A pointer to a message hash to be signed.
  @param  HashSize                     The size in bytes of the message hash to be signed.
  @param  Signature                    A pointer to a destination buffer to store the signature.
  @param  SigSize                      On input, indicates the size in bytes of the destination buffer to store the signature.
                                       On output, indicates the size in bytes of the signature in the buffer.

  @retval TRUE  signing success.
  @retval FALSE signing fail.
**/
BOOLEAN
EFIAPI
SpdmRequesterDataSignFunc (
  IN      UINT16       ReqBaseAsymAlg,
  IN      CONST UINT8  *MessageHash,
  IN      UINTN        HashSize,
  OUT     UINT8        *Signature,
  IN OUT  UINTN        *SigSize
  );

/**
  Sign an SPDM message data.

  @param  BaseAsymAlgo                 Indicates the signing algorithm.
  @param  MessageHash                  A pointer to a message hash to be signed.
  @param  HashSize                     The size in bytes of the message hash to be signed.
  @param  Signature                    A pointer to a destination buffer to store the signature.
  @param  SigSize                      On input, indicates the size in bytes of the destination buffer to store the signature.
                                       On output, indicates the size in bytes of the signature in the buffer.

  @retval TRUE  signing success.
  @retval FALSE signing fail.
**/
BOOLEAN
EFIAPI
SpdmResponderDataSignFunc (
  IN      UINT32       BaseAsymAlgo,
  IN      CONST UINT8  *MessageHash,
  IN      UINTN        HashSize,
  OUT     UINT8        *Signature,
  IN OUT  UINTN        *SigSize
  );

/**
  Derive HMAC-based Expand Key Derivation Function (HKDF) Expand, based upon the negotiated HKDF algorithm.

  @param  BaseHashAlgo                 Indicates the hash algorithm.
  @param  PskHint                      Pointer to the user-supplied PSK Hint.
  @param  PskHintSize                  PSK Hint size in bytes.
  @param  Info                         Pointer to the application specific info.
  @param  InfoSize                     Info size in bytes.
  @param  Out                          Pointer to buffer to receive hkdf value.
  @param  OutSize                      Size of hkdf bytes to generate.

  @retval TRUE   Hkdf generated successfully.
  @retval FALSE  Hkdf generation failed.
**/
BOOLEAN
EFIAPI
SpdmPskHandshakeSecretHkdfExpandFunc (
  IN      UINT32       BaseHashAlgo,
  IN      CONST UINT8  *PskHint, OPTIONAL
  IN      UINTN        PskHintSize, OPTIONAL
  IN      CONST UINT8  *Info,
  IN      UINTN        InfoSize,
     OUT  UINT8        *Out,
  IN      UINTN        OutSize
  );

/**
  Derive HMAC-based Expand Key Derivation Function (HKDF) Expand, based upon the negotiated HKDF algorithm.

  @param  BaseHashAlgo                 Indicates the hash algorithm.
  @param  PskHint                      Pointer to the user-supplied PSK Hint.
  @param  PskHintSize                  PSK Hint size in bytes.
  @param  Info                         Pointer to the application specific info.
  @param  InfoSize                     Info size in bytes.
  @param  Out                          Pointer to buffer to receive hkdf value.
  @param  OutSize                      Size of hkdf bytes to generate.

  @retval TRUE   Hkdf generated successfully.
  @retval FALSE  Hkdf generation failed.
**/
BOOLEAN
EFIAPI
SpdmPskMasterSecretHkdfExpandFunc (
  IN      UINT32       BaseHashAlgo,
  IN      CONST UINT8  *PskHint, OPTIONAL
  IN      UINTN        PskHintSize, OPTIONAL
  IN      CONST UINT8  *Info,
  IN      UINTN        InfoSize,
     OUT  UINT8        *Out,
  IN      UINTN        OutSize
  );

#endif
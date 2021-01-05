/**
@file
UEFI OS based application.

Copyright (c) 2020, Intel Corporation. All rights reserved.<BR>
SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include "SpdmEmu.h"

UINT8   mUseVersion = SPDM_MESSAGE_VERSION_11;
UINT32  mUseRequesterCapabilityFlags = (SPDM_GET_CAPABILITIES_REQUEST_FLAGS_CERT_CAP | \
                                        SPDM_GET_CAPABILITIES_REQUEST_FLAGS_CHAL_CAP | \
                                        SPDM_GET_CAPABILITIES_REQUEST_FLAGS_ENCRYPT_CAP | \
                                        SPDM_GET_CAPABILITIES_REQUEST_FLAGS_MAC_CAP | \
                                        SPDM_GET_CAPABILITIES_REQUEST_FLAGS_MUT_AUTH_CAP | \
                                        SPDM_GET_CAPABILITIES_REQUEST_FLAGS_KEY_EX_CAP | \
                                        SPDM_GET_CAPABILITIES_REQUEST_FLAGS_PSK_CAP_REQUESTER | \
                                        SPDM_GET_CAPABILITIES_REQUEST_FLAGS_ENCAP_CAP | \
                                        SPDM_GET_CAPABILITIES_REQUEST_FLAGS_HBEAT_CAP | \
                                        SPDM_GET_CAPABILITIES_REQUEST_FLAGS_KEY_UPD_CAP | \
                                        SPDM_GET_CAPABILITIES_REQUEST_FLAGS_HANDSHAKE_IN_THE_CLEAR_CAP |
                                        SPDM_GET_CAPABILITIES_REQUEST_FLAGS_PUB_KEY_ID_CAP);
UINT32  mUseResonderCapabilityFlags =  (SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_CERT_CAP |
                                        SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_CHAL_CAP |
                                        // SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MEAS_CAP_NO_SIG |
                                        SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MEAS_CAP_SIG |
                                        SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MEAS_FRESH_CAP |
                                        SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_ENCRYPT_CAP |
                                        SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MAC_CAP |
                                        SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MUT_AUTH_CAP |
                                        SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_KEY_EX_CAP |
                                        // SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_PSK_CAP_RESPONDER |
                                        SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_PSK_CAP_RESPONDER_WITH_CONTEXT |
                                        SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_ENCAP_CAP |
                                        SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_HBEAT_CAP |
                                        SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_KEY_UPD_CAP |
                                        SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_HANDSHAKE_IN_THE_CLEAR_CAP |
                                        SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_PUB_KEY_ID_CAP);

UINT32  mUseCapabilityFlags = 0;
/*
  SPDM_KEY_EXCHANGE_RESPONSE_MUT_AUTH_REQUESTED, // Basic Auth
  SPDM_KEY_EXCHANGE_RESPONSE_MUT_AUTH_REQUESTED_WITH_ENCAP_REQUEST,
  SPDM_KEY_EXCHANGE_RESPONSE_MUT_AUTH_REQUESTED_WITH_GET_DIGESTS
*/
UINT8   mUseMutAuth = SPDM_KEY_EXCHANGE_RESPONSE_MUT_AUTH_REQUESTED |
                      SPDM_KEY_EXCHANGE_RESPONSE_MUT_AUTH_REQUESTED_WITH_ENCAP_REQUEST;
/*
  SPDM_CHALLENGE_REQUEST_NO_MEASUREMENT_SUMMARY_HASH,
  SPDM_CHALLENGE_REQUEST_TCB_COMPONENT_MEASUREMENT_HASH,
  SPDM_CHALLENGE_REQUEST_ALL_MEASUREMENTS_HASH
*/
UINT8   mUseMeasurementSummaryHashType = SPDM_CHALLENGE_REQUEST_ALL_MEASUREMENTS_HASH;
/*
  SPDM_GET_MEASUREMENTS_REQUEST_MEASUREMENT_OPERATION_TOTAL_NUMBER_OF_MEASUREMENTS, // one by one
  SPDM_GET_MEASUREMENTS_REQUEST_MEASUREMENT_OPERATION_ALL_MEASUREMENTS
*/
UINT8   mUseMeasurementOperation = SPDM_GET_MEASUREMENTS_REQUEST_MEASUREMENT_OPERATION_TOTAL_NUMBER_OF_MEASUREMENTS;
UINT8   mUseSlotId = 0;
UINT8   mUseSlotCount = 3;

UINT32  mUseHashAlgo;
UINT32  mUseMeasurementHashAlgo;
UINT32  mUseAsymAlgo;
UINT16  mUseReqAsymAlgo;

/*
  SPDM_MEASUREMENT_BLOCK_HEADER_SPECIFICATION_DMTF,
*/
UINT8   mSupportMeasurementSpec = SPDM_MEASUREMENT_BLOCK_HEADER_SPECIFICATION_DMTF;
/*
  SPDM_ALGORITHMS_MEASUREMENT_HASH_ALGO_TPM_ALG_SHA3_512,
  SPDM_ALGORITHMS_MEASUREMENT_HASH_ALGO_TPM_ALG_SHA3_384,
  SPDM_ALGORITHMS_MEASUREMENT_HASH_ALGO_TPM_ALG_SHA3_256,
  SPDM_ALGORITHMS_MEASUREMENT_HASH_ALGO_TPM_ALG_SHA_512,
  SPDM_ALGORITHMS_MEASUREMENT_HASH_ALGO_TPM_ALG_SHA_384,
  SPDM_ALGORITHMS_MEASUREMENT_HASH_ALGO_TPM_ALG_SHA_256,
  SPDM_ALGORITHMS_MEASUREMENT_HASH_ALGO_RAW_BIT_STREAM_ONLY,
*/
UINT32  mSupportMeasurementHashAlgo = SPDM_ALGORITHMS_MEASUREMENT_HASH_ALGO_TPM_ALG_SHA_512 |
                                      SPDM_ALGORITHMS_MEASUREMENT_HASH_ALGO_TPM_ALG_SHA_384;
/*
  SPDM_ALGORITHMS_BASE_HASH_ALGO_TPM_ALG_SHA_512,
  SPDM_ALGORITHMS_BASE_HASH_ALGO_TPM_ALG_SHA_384,
  SPDM_ALGORITHMS_BASE_HASH_ALGO_TPM_ALG_SHA_256,
*/
UINT32  mSupportHashAlgo = SPDM_ALGORITHMS_BASE_HASH_ALGO_TPM_ALG_SHA_384 |
                           SPDM_ALGORITHMS_BASE_HASH_ALGO_TPM_ALG_SHA_256;
/*
  SPDM_ALGORITHMS_BASE_ASYM_ALGO_TPM_ALG_ECDSA_ECC_NIST_P521,
  SPDM_ALGORITHMS_BASE_ASYM_ALGO_TPM_ALG_ECDSA_ECC_NIST_P384,
  SPDM_ALGORITHMS_BASE_ASYM_ALGO_TPM_ALG_ECDSA_ECC_NIST_P256,
  SPDM_ALGORITHMS_BASE_ASYM_ALGO_TPM_ALG_RSAPSS_4096,
  SPDM_ALGORITHMS_BASE_ASYM_ALGO_TPM_ALG_RSASSA_4096,
  SPDM_ALGORITHMS_BASE_ASYM_ALGO_TPM_ALG_RSAPSS_3072,
  SPDM_ALGORITHMS_BASE_ASYM_ALGO_TPM_ALG_RSASSA_3072,
  SPDM_ALGORITHMS_BASE_ASYM_ALGO_TPM_ALG_RSAPSS_2048,
  SPDM_ALGORITHMS_BASE_ASYM_ALGO_TPM_ALG_RSASSA_2048,
*/
UINT32  mSupportAsymAlgo = SPDM_ALGORITHMS_BASE_ASYM_ALGO_TPM_ALG_ECDSA_ECC_NIST_P384 |
                           SPDM_ALGORITHMS_BASE_ASYM_ALGO_TPM_ALG_ECDSA_ECC_NIST_P256;
/*
  SPDM_ALGORITHMS_BASE_ASYM_ALGO_TPM_ALG_RSAPSS_4096,
  SPDM_ALGORITHMS_BASE_ASYM_ALGO_TPM_ALG_RSASSA_4096,
  SPDM_ALGORITHMS_BASE_ASYM_ALGO_TPM_ALG_RSAPSS_3072,
  SPDM_ALGORITHMS_BASE_ASYM_ALGO_TPM_ALG_RSASSA_3072,
  SPDM_ALGORITHMS_BASE_ASYM_ALGO_TPM_ALG_RSAPSS_2048,
  SPDM_ALGORITHMS_BASE_ASYM_ALGO_TPM_ALG_RSASSA_2048,
  SPDM_ALGORITHMS_BASE_ASYM_ALGO_TPM_ALG_ECDSA_ECC_NIST_P521,
  SPDM_ALGORITHMS_BASE_ASYM_ALGO_TPM_ALG_ECDSA_ECC_NIST_P384,
  SPDM_ALGORITHMS_BASE_ASYM_ALGO_TPM_ALG_ECDSA_ECC_NIST_P256,
*/
UINT16  mSupportReqAsymAlgo = SPDM_ALGORITHMS_BASE_ASYM_ALGO_TPM_ALG_RSAPSS_3072 |
                              SPDM_ALGORITHMS_BASE_ASYM_ALGO_TPM_ALG_RSAPSS_2048 |
                              SPDM_ALGORITHMS_BASE_ASYM_ALGO_TPM_ALG_RSASSA_3072 |
                              SPDM_ALGORITHMS_BASE_ASYM_ALGO_TPM_ALG_RSASSA_2048;
/*
  SPDM_ALGORITHMS_DHE_NAMED_GROUP_FFDHE_4096,
  SPDM_ALGORITHMS_DHE_NAMED_GROUP_FFDHE_3072,
  SPDM_ALGORITHMS_DHE_NAMED_GROUP_FFDHE_2048,
  SPDM_ALGORITHMS_DHE_NAMED_GROUP_SECP_521_R1,
  SPDM_ALGORITHMS_DHE_NAMED_GROUP_SECP_384_R1,
  SPDM_ALGORITHMS_DHE_NAMED_GROUP_SECP_256_R1,
*/
UINT16  mSupportDheAlgo = SPDM_ALGORITHMS_DHE_NAMED_GROUP_SECP_384_R1 |
                          SPDM_ALGORITHMS_DHE_NAMED_GROUP_SECP_256_R1 |
                          SPDM_ALGORITHMS_DHE_NAMED_GROUP_FFDHE_3072 |
                          SPDM_ALGORITHMS_DHE_NAMED_GROUP_FFDHE_2048;
/*
  SPDM_ALGORITHMS_AEAD_CIPHER_SUITE_AES_256_GCM,
  SPDM_ALGORITHMS_AEAD_CIPHER_SUITE_AES_128_GCM,
  SPDM_ALGORITHMS_AEAD_CIPHER_SUITE_CHACHA20_POLY1305,
*/
UINT16  mSupportAeadAlgo = SPDM_ALGORITHMS_AEAD_CIPHER_SUITE_AES_256_GCM |
                           SPDM_ALGORITHMS_AEAD_CIPHER_SUITE_CHACHA20_POLY1305;
/*
  SPDM_ALGORITHMS_KEY_SCHEDULE_HMAC_HASH,
*/
UINT16  mSupportKeyScheduleAlgo = SPDM_ALGORITHMS_KEY_SCHEDULE_HMAC_HASH;

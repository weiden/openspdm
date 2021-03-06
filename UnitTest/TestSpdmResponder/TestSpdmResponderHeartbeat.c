/**
@file
UEFI OS based application.

Copyright (c) 2020, Intel Corporation. All rights reserved.<BR>
SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include "SpdmUnitTest.h"
#include <SpdmResponderLibInternal.h>
#include <SpdmSecuredMessageLibInternal.h>

SPDM_HEARTBEAT_REQUEST    mSpdmHeartbeatRequest1 = {
  {
    SPDM_MESSAGE_VERSION_11,
    SPDM_HEARTBEAT,
    0,
    0
  }
};
UINTN mSpdmHeartbeatRequest1Size = sizeof(mSpdmHeartbeatRequest1);

SPDM_HEARTBEAT_REQUEST    mSpdmHeartbeatRequest2 = {
  {
    SPDM_MESSAGE_VERSION_11,
    SPDM_HEARTBEAT,
    0,
    0
  }
};
UINTN mSpdmHeartbeatRequest2Size = MAX_SPDM_MESSAGE_BUFFER_SIZE;

STATIC UINT8                  LocalPskHint[32];

void TestSpdmResponderHeartbeatCase1(void **state) {
  RETURN_STATUS        Status;
  SPDM_TEST_CONTEXT    *SpdmTestContext;
  SPDM_DEVICE_CONTEXT  *SpdmContext;
  UINTN                ResponseSize;
  UINT8                Response[MAX_SPDM_MESSAGE_BUFFER_SIZE];
  SPDM_HEARTBEAT_RESPONSE *SpdmResponse;
  VOID                 *Data1;
  UINTN                DataSize1;
  SPDM_SESSION_INFO    *SessionInfo;
  UINT32               SessionId;

  SpdmTestContext = *state;
  SpdmContext = SpdmTestContext->SpdmContext;
  SpdmTestContext->CaseId = 0x1;
  SpdmContext->SpdmCmdReceiveState |= SPDM_GET_DIGESTS_RECEIVE_FLAG;
  SpdmContext->SpdmCmdReceiveState |= SPDM_GET_CAPABILITIES_RECEIVE_FLAG;
  SpdmContext->SpdmCmdReceiveState |= SPDM_NEGOTIATE_ALGORITHMS_RECEIVE_FLAG;
  SpdmContext->SpdmCmdReceiveState |= SPDM_PSK_FINISH_RECEIVE_FLAG;
  SpdmContext->ConnectionInfo.Capability.Flags |= SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_HBEAT_CAP;
  SpdmContext->ConnectionInfo.Algorithm.BaseHashAlgo = mUseHashAlgo;
  SpdmContext->ConnectionInfo.Algorithm.BaseAsymAlgo = mUseAsymAlgo;
  SpdmContext->ConnectionInfo.Algorithm.MeasurementSpec = mUseMeasurementSpec;
  SpdmContext->ConnectionInfo.Algorithm.MeasurementHashAlgo = mUseMeasurementHashAlgo;
  SpdmContext->ConnectionInfo.Algorithm.DHENamedGroup = mUseDheAlgo;
  SpdmContext->ConnectionInfo.Algorithm.AEADCipherSuite = mUseAeadAlgo;
  ReadResponderPublicCertificateChain (mUseHashAlgo, mUseAsymAlgo, &Data1, &DataSize1, NULL, NULL);
  SpdmContext->LocalContext.LocalCertChainProvision[0] = Data1;
  SpdmContext->LocalContext.LocalCertChainProvisionSize[0] = DataSize1;
  SpdmContext->ConnectionInfo.LocalUsedCertChainBuffer = Data1;
  SpdmContext->ConnectionInfo.LocalUsedCertChainBufferSize = DataSize1;
  SpdmContext->LocalContext.SlotCount = 1;
  SpdmContext->Transcript.MessageA.BufferSize = 0;
  SpdmContext->LocalContext.MutAuthRequested = 0;
  ZeroMem (LocalPskHint, 32);
  CopyMem (&LocalPskHint[0], TEST_PSK_HINT_STRING, sizeof(TEST_PSK_HINT_STRING));
  SpdmContext->LocalContext.PskHintSize = sizeof(TEST_PSK_HINT_STRING);
  SpdmContext->LocalContext.PskHint = LocalPskHint;

  SessionId = 0xFFFFFFFF;
  SpdmContext->LatestSessionId = SessionId;
  SpdmContext->LastSpdmRequestSessionIdValid = TRUE;
  SpdmContext->LastSpdmRequestSessionId = SessionId;
  SessionInfo = &SpdmContext->SessionInfo[0];
  SpdmSessionInfoInit (SpdmContext, SessionInfo, SessionId, TRUE);
  
  ResponseSize = sizeof(Response);
  Status = SpdmGetResponseHeartbeat (SpdmContext, mSpdmHeartbeatRequest1Size, &mSpdmHeartbeatRequest1, &ResponseSize, Response);
  assert_int_equal (Status, RETURN_SUCCESS);
  assert_int_equal (ResponseSize, sizeof(SPDM_HEARTBEAT_RESPONSE));  
  SpdmResponse = (VOID *)Response;
  assert_int_equal (SpdmResponse->Header.RequestResponseCode, SPDM_HEARTBEAT_ACK);  
  free(Data1);
}

void TestSpdmResponderHeartbeatCase2(void **state) {
  RETURN_STATUS        Status;
  SPDM_TEST_CONTEXT    *SpdmTestContext;
  SPDM_DEVICE_CONTEXT  *SpdmContext;
  UINTN                ResponseSize;
  UINT8                Response[MAX_SPDM_MESSAGE_BUFFER_SIZE];
  SPDM_HEARTBEAT_RESPONSE *SpdmResponse;
  VOID                 *Data1;
  UINTN                DataSize1;
  SPDM_SESSION_INFO    *SessionInfo;
  UINT32               SessionId;

  SpdmTestContext = *state;
  SpdmContext = SpdmTestContext->SpdmContext;
  SpdmTestContext->CaseId = 0x2;
  SpdmContext->SpdmCmdReceiveState |= SPDM_GET_DIGESTS_RECEIVE_FLAG;
  SpdmContext->SpdmCmdReceiveState |= SPDM_GET_CAPABILITIES_RECEIVE_FLAG;
  SpdmContext->SpdmCmdReceiveState |= SPDM_NEGOTIATE_ALGORITHMS_RECEIVE_FLAG;
  SpdmContext->SpdmCmdReceiveState |= SPDM_PSK_FINISH_RECEIVE_FLAG;
  SpdmContext->ConnectionInfo.Capability.Flags |= SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_HBEAT_CAP;
  SpdmContext->ConnectionInfo.Algorithm.BaseHashAlgo = mUseHashAlgo;
  SpdmContext->ConnectionInfo.Algorithm.BaseAsymAlgo = mUseAsymAlgo;
  SpdmContext->ConnectionInfo.Algorithm.MeasurementSpec = mUseMeasurementSpec;
  SpdmContext->ConnectionInfo.Algorithm.MeasurementHashAlgo = mUseMeasurementHashAlgo;
  SpdmContext->ConnectionInfo.Algorithm.DHENamedGroup = mUseDheAlgo;
  SpdmContext->ConnectionInfo.Algorithm.AEADCipherSuite = mUseAeadAlgo;
  ReadResponderPublicCertificateChain (mUseHashAlgo, mUseAsymAlgo, &Data1, &DataSize1, NULL, NULL);
  SpdmContext->LocalContext.LocalCertChainProvision[0] = Data1;
  SpdmContext->LocalContext.LocalCertChainProvisionSize[0] = DataSize1;
  SpdmContext->ConnectionInfo.LocalUsedCertChainBuffer = Data1;
  SpdmContext->ConnectionInfo.LocalUsedCertChainBufferSize = DataSize1;
  SpdmContext->LocalContext.SlotCount = 1;
  SpdmContext->Transcript.MessageA.BufferSize = 0;
  SpdmContext->LocalContext.MutAuthRequested = 0;
  ZeroMem (LocalPskHint, 32);
  CopyMem (&LocalPskHint[0], TEST_PSK_HINT_STRING, sizeof(TEST_PSK_HINT_STRING));
  SpdmContext->LocalContext.PskHintSize = sizeof(TEST_PSK_HINT_STRING);
  SpdmContext->LocalContext.PskHint = LocalPskHint;

  SessionId = 0xFFFFFFFF;
  SpdmContext->LatestSessionId = SessionId;
  SpdmContext->LastSpdmRequestSessionIdValid = TRUE;
  SpdmContext->LastSpdmRequestSessionId = SessionId;
  SessionInfo = &SpdmContext->SessionInfo[0];
  SpdmSessionInfoInit (SpdmContext, SessionInfo, SessionId, TRUE);
  
  ResponseSize = sizeof(Response);
  Status = SpdmGetResponseHeartbeat (SpdmContext, mSpdmHeartbeatRequest2Size, &mSpdmHeartbeatRequest2, &ResponseSize, Response);
  assert_int_equal (Status, RETURN_SUCCESS);
  assert_int_equal (ResponseSize, sizeof(SPDM_ERROR_RESPONSE));
  SpdmResponse = (VOID *)Response;
  assert_int_equal (SpdmResponse->Header.RequestResponseCode, SPDM_ERROR);
  assert_int_equal (SpdmResponse->Header.Param1, SPDM_ERROR_CODE_INVALID_REQUEST);
  assert_int_equal (SpdmResponse->Header.Param2, 0);
  free(Data1);
}

void TestSpdmResponderHeartbeatCase3(void **state) {
  RETURN_STATUS        Status;
  SPDM_TEST_CONTEXT    *SpdmTestContext;
  SPDM_DEVICE_CONTEXT  *SpdmContext;
  UINTN                ResponseSize;
  UINT8                Response[MAX_SPDM_MESSAGE_BUFFER_SIZE];
  SPDM_HEARTBEAT_RESPONSE *SpdmResponse;
  VOID                 *Data1;
  UINTN                DataSize1;
  SPDM_SESSION_INFO    *SessionInfo;
  UINT32               SessionId;

  SpdmTestContext = *state;
  SpdmContext = SpdmTestContext->SpdmContext;
  SpdmTestContext->CaseId = 0x3;
  SpdmContext->ResponseState = SpdmResponseStateBusy;
  SpdmContext->SpdmCmdReceiveState |= SPDM_GET_DIGESTS_RECEIVE_FLAG;
  SpdmContext->SpdmCmdReceiveState |= SPDM_GET_CAPABILITIES_RECEIVE_FLAG;
  SpdmContext->SpdmCmdReceiveState |= SPDM_NEGOTIATE_ALGORITHMS_RECEIVE_FLAG;
  SpdmContext->SpdmCmdReceiveState |= SPDM_PSK_FINISH_RECEIVE_FLAG;
  SpdmContext->ConnectionInfo.Capability.Flags |= SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_HBEAT_CAP;
  SpdmContext->ConnectionInfo.Algorithm.BaseHashAlgo = mUseHashAlgo;
  SpdmContext->ConnectionInfo.Algorithm.BaseAsymAlgo = mUseAsymAlgo;
  SpdmContext->ConnectionInfo.Algorithm.MeasurementSpec = mUseMeasurementSpec;
  SpdmContext->ConnectionInfo.Algorithm.MeasurementHashAlgo = mUseMeasurementHashAlgo;
  SpdmContext->ConnectionInfo.Algorithm.DHENamedGroup = mUseDheAlgo;
  SpdmContext->ConnectionInfo.Algorithm.AEADCipherSuite = mUseAeadAlgo;
  ReadResponderPublicCertificateChain (mUseHashAlgo, mUseAsymAlgo, &Data1, &DataSize1, NULL, NULL);
  SpdmContext->LocalContext.LocalCertChainProvision[0] = Data1;
  SpdmContext->LocalContext.LocalCertChainProvisionSize[0] = DataSize1;
  SpdmContext->ConnectionInfo.LocalUsedCertChainBuffer = Data1;
  SpdmContext->ConnectionInfo.LocalUsedCertChainBufferSize = DataSize1;
  SpdmContext->LocalContext.SlotCount = 1;
  SpdmContext->Transcript.MessageA.BufferSize = 0;
  SpdmContext->LocalContext.MutAuthRequested = 0;
  ZeroMem (LocalPskHint, 32);
  CopyMem (&LocalPskHint[0], TEST_PSK_HINT_STRING, sizeof(TEST_PSK_HINT_STRING));
  SpdmContext->LocalContext.PskHintSize = sizeof(TEST_PSK_HINT_STRING);
  SpdmContext->LocalContext.PskHint = LocalPskHint;

  SessionId = 0xFFFFFFFF;
  SpdmContext->LatestSessionId = SessionId;
  SpdmContext->LastSpdmRequestSessionIdValid = TRUE;
  SpdmContext->LastSpdmRequestSessionId = SessionId;
  SessionInfo = &SpdmContext->SessionInfo[0];
  SpdmSessionInfoInit (SpdmContext, SessionInfo, SessionId, TRUE);
  
  ResponseSize = sizeof(Response);
  Status = SpdmGetResponseHeartbeat (SpdmContext, mSpdmHeartbeatRequest1Size, &mSpdmHeartbeatRequest1, &ResponseSize, Response);
  assert_int_equal (Status, RETURN_SUCCESS);
  assert_int_equal (ResponseSize, sizeof(SPDM_ERROR_RESPONSE));
  SpdmResponse = (VOID *)Response;
  assert_int_equal (SpdmResponse->Header.RequestResponseCode, SPDM_ERROR);
  assert_int_equal (SpdmResponse->Header.Param1, SPDM_ERROR_CODE_BUSY);
  assert_int_equal (SpdmResponse->Header.Param2, 0);
  assert_int_equal (SpdmContext->ResponseState, SpdmResponseStateBusy);
  free(Data1);
}

void TestSpdmResponderHeartbeatCase4(void **state) {
  RETURN_STATUS        Status;
  SPDM_TEST_CONTEXT    *SpdmTestContext;
  SPDM_DEVICE_CONTEXT  *SpdmContext;
  UINTN                ResponseSize;
  UINT8                Response[MAX_SPDM_MESSAGE_BUFFER_SIZE];
  SPDM_HEARTBEAT_RESPONSE *SpdmResponse;
  VOID                 *Data1;
  UINTN                DataSize1;
  SPDM_SESSION_INFO    *SessionInfo;
  UINT32               SessionId;

  SpdmTestContext = *state;
  SpdmContext = SpdmTestContext->SpdmContext;
  SpdmTestContext->CaseId = 0x4;
  SpdmContext->ResponseState = SpdmResponseStateNeedResync;
  SpdmContext->SpdmCmdReceiveState |= SPDM_GET_DIGESTS_RECEIVE_FLAG;
  SpdmContext->SpdmCmdReceiveState |= SPDM_GET_CAPABILITIES_RECEIVE_FLAG;
  SpdmContext->SpdmCmdReceiveState |= SPDM_NEGOTIATE_ALGORITHMS_RECEIVE_FLAG;
  SpdmContext->SpdmCmdReceiveState |= SPDM_PSK_FINISH_RECEIVE_FLAG;
  SpdmContext->ConnectionInfo.Capability.Flags |= SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_HBEAT_CAP;
  SpdmContext->ConnectionInfo.Algorithm.BaseHashAlgo = mUseHashAlgo;
  SpdmContext->ConnectionInfo.Algorithm.BaseAsymAlgo = mUseAsymAlgo;
  SpdmContext->ConnectionInfo.Algorithm.MeasurementSpec = mUseMeasurementSpec;
  SpdmContext->ConnectionInfo.Algorithm.MeasurementHashAlgo = mUseMeasurementHashAlgo;
  SpdmContext->ConnectionInfo.Algorithm.DHENamedGroup = mUseDheAlgo;
  SpdmContext->ConnectionInfo.Algorithm.AEADCipherSuite = mUseAeadAlgo;
  ReadResponderPublicCertificateChain (mUseHashAlgo, mUseAsymAlgo, &Data1, &DataSize1, NULL, NULL);
  SpdmContext->LocalContext.LocalCertChainProvision[0] = Data1;
  SpdmContext->LocalContext.LocalCertChainProvisionSize[0] = DataSize1;
  SpdmContext->ConnectionInfo.LocalUsedCertChainBuffer = Data1;
  SpdmContext->ConnectionInfo.LocalUsedCertChainBufferSize = DataSize1;
  SpdmContext->LocalContext.SlotCount = 1;
  SpdmContext->Transcript.MessageA.BufferSize = 0;
  SpdmContext->LocalContext.MutAuthRequested = 0;
  ZeroMem (LocalPskHint, 32);
  CopyMem (&LocalPskHint[0], TEST_PSK_HINT_STRING, sizeof(TEST_PSK_HINT_STRING));
  SpdmContext->LocalContext.PskHintSize = sizeof(TEST_PSK_HINT_STRING);
  SpdmContext->LocalContext.PskHint = LocalPskHint;

  SessionId = 0xFFFFFFFF;
  SpdmContext->LatestSessionId = SessionId;
  SpdmContext->LastSpdmRequestSessionIdValid = TRUE;
  SpdmContext->LastSpdmRequestSessionId = SessionId;
  SessionInfo = &SpdmContext->SessionInfo[0];
  SpdmSessionInfoInit (SpdmContext, SessionInfo, SessionId, TRUE);
  
  ResponseSize = sizeof(Response);
  Status = SpdmGetResponseHeartbeat (SpdmContext, mSpdmHeartbeatRequest1Size, &mSpdmHeartbeatRequest1, &ResponseSize, Response);
  assert_int_equal (Status, RETURN_SUCCESS);
  assert_int_equal (ResponseSize, sizeof(SPDM_ERROR_RESPONSE));
  SpdmResponse = (VOID *)Response;
  assert_int_equal (SpdmResponse->Header.RequestResponseCode, SPDM_ERROR);
  assert_int_equal (SpdmResponse->Header.Param1, SPDM_ERROR_CODE_REQUEST_RESYNCH);
  assert_int_equal (SpdmResponse->Header.Param2, 0);
  assert_int_equal (SpdmContext->ResponseState, SpdmResponseStateNormal);
  free(Data1);
}

void TestSpdmResponderHeartbeatCase5(void **state) {
  RETURN_STATUS        Status;
  SPDM_TEST_CONTEXT    *SpdmTestContext;
  SPDM_DEVICE_CONTEXT  *SpdmContext;
  UINTN                ResponseSize;
  UINT8                Response[MAX_SPDM_MESSAGE_BUFFER_SIZE];
  SPDM_HEARTBEAT_RESPONSE *SpdmResponse;
  VOID                 *Data1;
  UINTN                DataSize1;
  SPDM_SESSION_INFO    *SessionInfo;
  UINT32               SessionId;
  SPDM_ERROR_DATA_RESPONSE_NOT_READY *ErrorData;
  
  SpdmTestContext = *state;
  SpdmContext = SpdmTestContext->SpdmContext;
  SpdmTestContext->CaseId = 0x5;
  SpdmContext->ResponseState = SpdmResponseStateNotReady;
  SpdmContext->SpdmCmdReceiveState |= SPDM_GET_DIGESTS_RECEIVE_FLAG;
  SpdmContext->SpdmCmdReceiveState |= SPDM_GET_CAPABILITIES_RECEIVE_FLAG;
  SpdmContext->SpdmCmdReceiveState |= SPDM_NEGOTIATE_ALGORITHMS_RECEIVE_FLAG;
  SpdmContext->SpdmCmdReceiveState |= SPDM_PSK_FINISH_RECEIVE_FLAG;
  SpdmContext->ConnectionInfo.Capability.Flags |= SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_HBEAT_CAP;
  SpdmContext->ConnectionInfo.Algorithm.BaseHashAlgo = mUseHashAlgo;
  SpdmContext->ConnectionInfo.Algorithm.BaseAsymAlgo = mUseAsymAlgo;
  SpdmContext->ConnectionInfo.Algorithm.MeasurementSpec = mUseMeasurementSpec;
  SpdmContext->ConnectionInfo.Algorithm.MeasurementHashAlgo = mUseMeasurementHashAlgo;
  SpdmContext->ConnectionInfo.Algorithm.DHENamedGroup = mUseDheAlgo;
  SpdmContext->ConnectionInfo.Algorithm.AEADCipherSuite = mUseAeadAlgo;
  ReadResponderPublicCertificateChain (mUseHashAlgo, mUseAsymAlgo, &Data1, &DataSize1, NULL, NULL);
  SpdmContext->LocalContext.LocalCertChainProvision[0] = Data1;
  SpdmContext->LocalContext.LocalCertChainProvisionSize[0] = DataSize1;
  SpdmContext->ConnectionInfo.LocalUsedCertChainBuffer = Data1;
  SpdmContext->ConnectionInfo.LocalUsedCertChainBufferSize = DataSize1;
  SpdmContext->LocalContext.SlotCount = 1;
  SpdmContext->Transcript.MessageA.BufferSize = 0;
  SpdmContext->LocalContext.MutAuthRequested = 0;
  ZeroMem (LocalPskHint, 32);
  CopyMem (&LocalPskHint[0], TEST_PSK_HINT_STRING, sizeof(TEST_PSK_HINT_STRING));
  SpdmContext->LocalContext.PskHintSize = sizeof(TEST_PSK_HINT_STRING);
  SpdmContext->LocalContext.PskHint = LocalPskHint;

  SessionId = 0xFFFFFFFF;
  SpdmContext->LatestSessionId = SessionId;
  SpdmContext->LastSpdmRequestSessionIdValid = TRUE;
  SpdmContext->LastSpdmRequestSessionId = SessionId;
  SessionInfo = &SpdmContext->SessionInfo[0];
  SpdmSessionInfoInit (SpdmContext, SessionInfo, SessionId, TRUE);
  
  ResponseSize = sizeof(Response);
  Status = SpdmGetResponseHeartbeat (SpdmContext, mSpdmHeartbeatRequest1Size, &mSpdmHeartbeatRequest1, &ResponseSize, Response);
  assert_int_equal (Status, RETURN_SUCCESS);
  assert_int_equal (ResponseSize, sizeof(SPDM_ERROR_RESPONSE) + sizeof(SPDM_ERROR_DATA_RESPONSE_NOT_READY));
  SpdmResponse = (VOID *)Response;
  ErrorData = (SPDM_ERROR_DATA_RESPONSE_NOT_READY*)(SpdmResponse + 1);
  assert_int_equal (SpdmResponse->Header.RequestResponseCode, SPDM_ERROR);
  assert_int_equal (SpdmResponse->Header.Param1, SPDM_ERROR_CODE_RESPONSE_NOT_READY);
  assert_int_equal (SpdmResponse->Header.Param2, 0);
  assert_int_equal (SpdmContext->ResponseState, SpdmResponseStateNormal);
  assert_int_equal (ErrorData->RequestCode, SPDM_HEARTBEAT);
  free(Data1);
}

void TestSpdmResponderHeartbeatCase6(void **state) {
  RETURN_STATUS        Status;
  SPDM_TEST_CONTEXT    *SpdmTestContext;
  SPDM_DEVICE_CONTEXT  *SpdmContext;
  UINTN                ResponseSize;
  UINT8                Response[MAX_SPDM_MESSAGE_BUFFER_SIZE];
  SPDM_HEARTBEAT_RESPONSE *SpdmResponse;
  VOID                 *Data1;
  UINTN                DataSize1;
  SPDM_SESSION_INFO    *SessionInfo;
  UINT32               SessionId;
  
  SpdmTestContext = *state;
  SpdmContext = SpdmTestContext->SpdmContext;
  SpdmTestContext->CaseId = 0x6;
  SpdmContext->SpdmCmdReceiveState = 0;
  SpdmContext->ConnectionInfo.Capability.Flags |= SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_HBEAT_CAP;
  SpdmContext->ConnectionInfo.Algorithm.BaseHashAlgo = mUseHashAlgo;
  SpdmContext->ConnectionInfo.Algorithm.BaseAsymAlgo = mUseAsymAlgo;
  SpdmContext->ConnectionInfo.Algorithm.MeasurementSpec = mUseMeasurementSpec;
  SpdmContext->ConnectionInfo.Algorithm.MeasurementHashAlgo = mUseMeasurementHashAlgo;
  SpdmContext->ConnectionInfo.Algorithm.DHENamedGroup = mUseDheAlgo;
  SpdmContext->ConnectionInfo.Algorithm.AEADCipherSuite = mUseAeadAlgo;
  ReadResponderPublicCertificateChain (mUseHashAlgo, mUseAsymAlgo, &Data1, &DataSize1, NULL, NULL);
  SpdmContext->LocalContext.LocalCertChainProvision[0] = Data1;
  SpdmContext->LocalContext.LocalCertChainProvisionSize[0] = DataSize1;
  SpdmContext->ConnectionInfo.LocalUsedCertChainBuffer = Data1;
  SpdmContext->ConnectionInfo.LocalUsedCertChainBufferSize = DataSize1;
  SpdmContext->LocalContext.SlotCount = 1;
  SpdmContext->Transcript.MessageA.BufferSize = 0;
  SpdmContext->LocalContext.MutAuthRequested = 0;
  ZeroMem (LocalPskHint, 32);
  CopyMem (&LocalPskHint[0], TEST_PSK_HINT_STRING, sizeof(TEST_PSK_HINT_STRING));
  SpdmContext->LocalContext.PskHintSize = sizeof(TEST_PSK_HINT_STRING);
  SpdmContext->LocalContext.PskHint = LocalPskHint;

  SessionId = 0xFFFFFFFF;
  SpdmContext->LatestSessionId = SessionId;
  SpdmContext->LastSpdmRequestSessionIdValid = TRUE;
  SpdmContext->LastSpdmRequestSessionId = SessionId;
  SessionInfo = &SpdmContext->SessionInfo[0];
  SpdmSessionInfoInit (SpdmContext, SessionInfo, SessionId, TRUE);
  
  ResponseSize = sizeof(Response);
  Status = SpdmGetResponseHeartbeat (SpdmContext, mSpdmHeartbeatRequest1Size, &mSpdmHeartbeatRequest1, &ResponseSize, Response);
  assert_int_equal (Status, RETURN_SUCCESS);
  assert_int_equal (ResponseSize, sizeof(SPDM_ERROR_RESPONSE));
  SpdmResponse = (VOID *)Response;
  assert_int_equal (SpdmResponse->Header.RequestResponseCode, SPDM_ERROR);
  assert_int_equal (SpdmResponse->Header.Param1, SPDM_ERROR_CODE_UNEXPECTED_REQUEST);
  assert_int_equal (SpdmResponse->Header.Param2, 0);
  free(Data1);
}

SPDM_TEST_CONTEXT       mSpdmResponderHeartbeatTestContext = {
  SPDM_TEST_CONTEXT_SIGNATURE,
  FALSE,
};

int SpdmResponderHeartbeatTestMain(void) {
  const struct CMUnitTest SpdmResponderHeartbeatTests[] = {
    // Success Case
    cmocka_unit_test(TestSpdmResponderHeartbeatCase1),
    // Bad Request Size
    cmocka_unit_test(TestSpdmResponderHeartbeatCase2),
    // ResponseState: SpdmResponseStateBusy
    cmocka_unit_test(TestSpdmResponderHeartbeatCase3),
    // ResponseState: SpdmResponseStateNeedResync
    cmocka_unit_test(TestSpdmResponderHeartbeatCase4),
    // ResponseState: SpdmResponseStateNotReady
    cmocka_unit_test(TestSpdmResponderHeartbeatCase5),
    // SpdmCmdReceiveState Check
    cmocka_unit_test(TestSpdmResponderHeartbeatCase6),
  };

  SetupSpdmTestContext (&mSpdmResponderHeartbeatTestContext);

  return cmocka_run_group_tests(SpdmResponderHeartbeatTests, SpdmUnitTestGroupSetup, SpdmUnitTestGroupTeardown);
}

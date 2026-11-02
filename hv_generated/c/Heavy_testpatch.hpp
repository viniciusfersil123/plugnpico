/**
 * Copyright (c) 2026 Enzien Audio, Ltd.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions, and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the phrase "powered by heavy",
 *    the heavy logo, and a hyperlink to https://enzienaudio.com, all in a visible
 *    form.
 * 
 *   2.1 If the Application is distributed in a store system (for example,
 *       the Apple "App Store" or "Google Play"), the phrase "powered by heavy"
 *       shall be included in the app description or the copyright text as well as
 *       the in the app itself. The heavy logo will shall be visible in the app
 *       itself as well.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#ifndef _HEAVY_CONTEXT_TESTPATCH_HPP_
#define _HEAVY_CONTEXT_TESTPATCH_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvControlTabhead.h"
#include "HvControlSystem.h"
#include "HvControlVar.h"
#include "HvMath.h"
#include "HvSignalVar.h"
#include "HvTable.h"
#include "HvControlCast.h"
#include "HvSignalPhasor.h"
#include "HvSignalTabwrite.h"
#include "HvSignalTabread.h"
#include "HvControlDelay.h"
#include "HvControlBinop.h"

class Heavy_testpatch : public HeavyContext {

 public:
  Heavy_testpatch(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_testpatch();

  const char *getName() override { return "testpatch"; }
  int getNumInputChannels() override { return 0; }
  int getNumOutputChannels() override { return 2; }

  int process(float **inputBuffers, float **outputBuffer, int n) override;
  int processInline(float *inputBuffers, float *outputBuffer, int n) override;
  int processInlineInterleaved(float *inputBuffers, float *outputBuffer, int n) override;

  int getParameterInfo(int index, HvParameterInfo *info) override;

 private:
  HvTable *getTableForHash(hv_uint32_t tableHash) override;
  void scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) override;


  /*
  * Code for expr~ implementation
  * Write out the generic header code
  */

  // per class code

  // per object code


  // static sendMessage functions
  static void cMsg_ZMri8dNu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_iWNrMfkm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_U4oLgbgZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_K6s7Agga_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_gfZvitlD_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cBinop_3Z9avDy8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_csNvNVyV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_9rbOSdxC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_WWGZ8sTL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_2tZmKBvh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_sDF26TQs_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_9czTkm5N_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_VQbW0anv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabhead_tS5gRwfm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_GSlAKRef_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_oTRQ2T0D_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_4m6KQk0T_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_hbovN72V_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_q3ZdkPTv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void sTabread_KbuVL2B0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_0hj99axj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_CSt8hZ6E_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_nGcPuWKL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_eXn6bBgi_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_Xc59ItBU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_qBz2Yqxk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_4zMIcpC1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_ztYBjQxo_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_NcXRhY6X_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Lir3zUbH_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_4FncE7h1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_VBcSSTWL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_PPS8D8og_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_jTTBFdAl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_zo9Jem4y_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalPhasor sPhasor_3lYYzklL;
  SignalTabread sTabread_KbuVL2B0;
  SignalTabwrite sTabwrite_zY8pboXb;
  SignalVarf sVarf_SCfBuhlS;
  ControlDelay cDelay_U4oLgbgZ;
  ControlDelay cDelay_K6s7Agga;
  ControlBinop cBinop_3Z9avDy8;
  HvTable hTable_csNvNVyV;
  ControlBinop cBinop_WWGZ8sTL;
  ControlTabhead cTabhead_tS5gRwfm;
  ControlVar cVar_4m6KQk0T;
  ControlDelay cDelay_hbovN72V;
  ControlDelay cDelay_q3ZdkPTv;
  ControlBinop cBinop_0hj99axj;
  ControlBinop cBinop_CSt8hZ6E;
  ControlBinop cBinop_nGcPuWKL;
  ControlBinop cBinop_ztYBjQxo;
  ControlBinop cBinop_Lir3zUbH;
  ControlBinop cBinop_4FncE7h1;
  ControlVar cVar_PPS8D8og;
};

#endif // _HEAVY_CONTEXT_TESTPATCH_HPP_

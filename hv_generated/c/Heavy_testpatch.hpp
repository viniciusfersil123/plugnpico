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
#include "HvTable.h"
#include "HvControlBinop.h"
#include "HvControlCast.h"
#include "HvSignalPhasor.h"
#include "HvSignalTabwrite.h"
#include "HvControlTabhead.h"
#include "HvSignalTabread.h"
#include "HvControlDelay.h"
#include "HvMath.h"
#include "HvControlSystem.h"
#include "HvSignalVar.h"
#include "HvControlVar.h"

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
  static void cMsg_zahtgrHC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_92aky9CY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_4t01VNVe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_qOTuUuZ6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_seemoZlL_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cBinop_FWdO3snQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void hTable_6sejzFQI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_onhlmcxE_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_cLkgmIpr_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_4pCGmCxt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_gi1yIg2r_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_msqv8ink_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_ZADKKaQZ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cTabhead_oo5J7kc0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_8MxcFzuY_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_kUkt6uEX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_kemEFDN1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_YXVrRohJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_G2xncgpq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void sTabread_F0OgZQE8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_83ksa2ps_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_4luctala_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_03tPqQaB_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_l6lyATCC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_gsurPF7S_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_FbsaRCNP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_oUrBYhpR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_0Ocbz6Fl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_mCCeLx6z_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_0Bzv7VGP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_mqfQj0F9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_ODREhRwl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_kd7Kk1et_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_qoZNQUJn_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_vF6v8DEB_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalPhasor sPhasor_BPjOeW9f;
  SignalTabread sTabread_F0OgZQE8;
  SignalTabwrite sTabwrite_OfvVBz5v;
  SignalVarf sVarf_pqNrwnTq;
  ControlDelay cDelay_4t01VNVe;
  ControlDelay cDelay_qOTuUuZ6;
  ControlBinop cBinop_FWdO3snQ;
  HvTable hTable_6sejzFQI;
  ControlBinop cBinop_cLkgmIpr;
  ControlTabhead cTabhead_oo5J7kc0;
  ControlVar cVar_kemEFDN1;
  ControlDelay cDelay_YXVrRohJ;
  ControlDelay cDelay_G2xncgpq;
  ControlBinop cBinop_83ksa2ps;
  ControlBinop cBinop_4luctala;
  ControlBinop cBinop_03tPqQaB;
  ControlBinop cBinop_0Ocbz6Fl;
  ControlBinop cBinop_0Bzv7VGP;
  ControlBinop cBinop_mqfQj0F9;
  ControlVar cVar_kd7Kk1et;
};

#endif // _HEAVY_CONTEXT_TESTPATCH_HPP_

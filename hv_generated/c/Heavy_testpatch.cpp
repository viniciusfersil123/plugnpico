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

#include "Heavy_testpatch.hpp"

#include <new>

#define Context(_c) static_cast<Heavy_testpatch *>(_c)


/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_testpatch_new(double sampleRate) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_testpatch));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_testpatch(sampleRate);
    return Context(ptr);
  }

  HV_EXPORT HeavyContextInterface *hv_testpatch_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    // allocate aligned memory
    void *ptr = hv_malloc(sizeof(Heavy_testpatch));
    // ensure non-null
    if (!ptr) return nullptr;
    // call constructor
    new(ptr) Heavy_testpatch(sampleRate, poolKb, inQueueKb, outQueueKb);
    return Context(ptr);
  }

  HV_EXPORT void hv_testpatch_free(HeavyContextInterface *instance) {
    // call destructor
    Context(instance)->~Heavy_testpatch();
    // free memory
    hv_free(instance);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_testpatch::Heavy_testpatch(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sPhasor_init(&sPhasor_3lYYzklL, sampleRate);
  numBytes += sTabread_init(&sTabread_KbuVL2B0, &hTable_csNvNVyV, true);
  numBytes += sTabwrite_init(&sTabwrite_zY8pboXb, &hTable_csNvNVyV);
  numBytes += sVarf_init(&sVarf_SCfBuhlS, 0.0f, 0.0f, false);
  numBytes += cDelay_init(this, &cDelay_U4oLgbgZ, 0.0f);
  numBytes += cDelay_init(this, &cDelay_K6s7Agga, 0.0f);
  numBytes += hTable_init(&hTable_csNvNVyV, 256);
  numBytes += cTabhead_init(&cTabhead_tS5gRwfm, &hTable_csNvNVyV);
  numBytes += cVar_init_s(&cVar_4m6KQk0T, "del-teste");
  numBytes += cDelay_init(this, &cDelay_hbovN72V, 500.0f);
  numBytes += cDelay_init(this, &cDelay_q3ZdkPTv, 0.0f);
  numBytes += cBinop_init(&cBinop_0hj99axj, 500.0f); // __mul
  numBytes += cBinop_init(&cBinop_nGcPuWKL, 0.0f); // __sub
  numBytes += cBinop_init(&cBinop_ztYBjQxo, 0.0f); // __max
  numBytes += cBinop_init(&cBinop_4FncE7h1, 0.0f); // __sub
  numBytes += cVar_init_f(&cVar_PPS8D8og, 0.0f);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_testpatch::~Heavy_testpatch() {
  hTable_free(&hTable_csNvNVyV);
}

HvTable *Heavy_testpatch::getTableForHash(hv_uint32_t tableHash) {switch (tableHash) {
    case 0xB0952E2D: return &hTable_csNvNVyV; // del-teste
    default: return nullptr;
  }
}

void Heavy_testpatch::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_jTTBFdAl_sendMessage);
      break;
    }
    case 0xE5634BA2: { // adc1
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_zo9Jem4y_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_testpatch::getParameterInfo(int index, HvParameterInfo *info) {
  if (info != nullptr) {
    switch (index) {
      default: {
        info->name = "invalid parameter index";
        info->hash = 0;
        info->type = HvParameterType::HV_PARAM_TYPE_PARAMETER_IN;
        info->minVal = 0.0f;
        info->maxVal = 0.0f;
        info->defaultVal = 0.0f;
        break;
      }
    }
  }
  return 0;
}



/*
 * Send Function Implementations
 */


void Heavy_testpatch::cMsg_ZMri8dNu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_iWNrMfkm_sendMessage);
}

void Heavy_testpatch::cSystem_iWNrMfkm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_WWGZ8sTL_sendMessage);
}

void Heavy_testpatch::cDelay_U4oLgbgZ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_U4oLgbgZ, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_K6s7Agga, 0, m, &cDelay_K6s7Agga_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_U4oLgbgZ, 0, m, &cDelay_U4oLgbgZ_sendMessage);
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_zY8pboXb, 1, m, NULL);
}

void Heavy_testpatch::cDelay_K6s7Agga_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_K6s7Agga, m);
  cMsg_2tZmKBvh_sendMessage(_c, 0, m);
}

void Heavy_testpatch::cSwitchcase_gfZvitlD_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  int msgIndex = 0;
  switch (msg_getHash(m, msgIndex)) {
    case 0x6D60E6E: { // "symbol"
      msgIndex = 1;
      break;
    }
  }
  switch (msg_getHash(m, msgIndex)) {
    case 0x47BE8354: { // "clear"
      cMsg_VQbW0anv_sendMessage(_c, 0, m);
      break;
    }
    default: {
      break;
    }
  }
}

void Heavy_testpatch::cBinop_3Z9avDy8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_9rbOSdxC_sendMessage(_c, 0, m);
}

void Heavy_testpatch::hTable_csNvNVyV_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_9czTkm5N_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_U4oLgbgZ, 2, m, &cDelay_U4oLgbgZ_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_sDF26TQs_sendMessage);
}

void Heavy_testpatch::cMsg_9rbOSdxC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "resize");
  msg_setElementToFrom(m, 1, n, 0);
  hTable_onMessage(_c, &Context(_c)->hTable_csNvNVyV, 0, m, &hTable_csNvNVyV_sendMessage);
}

void Heavy_testpatch::cBinop_WWGZ8sTL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 500.0f, 0, m, &cBinop_3Z9avDy8_sendMessage);
}

void Heavy_testpatch::cMsg_2tZmKBvh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "mirror");
  hTable_onMessage(_c, &Context(_c)->hTable_csNvNVyV, 0, m, &hTable_csNvNVyV_sendMessage);
}

void Heavy_testpatch::cCast_sDF26TQs_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_U4oLgbgZ, 0, m, &cDelay_U4oLgbgZ_sendMessage);
}

void Heavy_testpatch::cMsg_9czTkm5N_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0,  static_cast<float>(HV_N_SIMD));
  cDelay_onMessage(_c, &Context(_c)->cDelay_K6s7Agga, 2, m, &cDelay_K6s7Agga_sendMessage);
}

void Heavy_testpatch::cMsg_VQbW0anv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  sTabwrite_onMessage(_c, &Context(_c)->sTabwrite_zY8pboXb, 1, m, NULL);
}

void Heavy_testpatch::cTabhead_tS5gRwfm_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_nGcPuWKL, HV_BINOP_SUBTRACT, 0, m, &cBinop_nGcPuWKL_sendMessage);
}

void Heavy_testpatch::cMsg_GSlAKRef_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_oTRQ2T0D_sendMessage);
}

void Heavy_testpatch::cSystem_oTRQ2T0D_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_CSt8hZ6E_sendMessage);
}

void Heavy_testpatch::cVar_4m6KQk0T_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_Xc59ItBU_sendMessage(_c, 0, m);
}

void Heavy_testpatch::cDelay_hbovN72V_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_hbovN72V, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_q3ZdkPTv, 0, m, &cDelay_q3ZdkPTv_sendMessage);
  sTabread_onMessage(_c, &Context(_c)->sTabread_KbuVL2B0, 0, m, &sTabread_KbuVL2B0_sendMessage);
}

void Heavy_testpatch::cDelay_q3ZdkPTv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_q3ZdkPTv, m);
  sTabread_onMessage(_c, &Context(_c)->sTabread_KbuVL2B0, 0, m, &sTabread_KbuVL2B0_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_q3ZdkPTv, 0, m, &cDelay_q3ZdkPTv_sendMessage);
}

void Heavy_testpatch::sTabread_KbuVL2B0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      break;
    }
    case 1: {
      cBinop_onMessage(_c, &Context(_c)->cBinop_4FncE7h1, HV_BINOP_SUBTRACT, 0, m, &cBinop_4FncE7h1_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_testpatch::cBinop_0hj99axj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_ztYBjQxo, HV_BINOP_MAX, 0, m, &cBinop_ztYBjQxo_sendMessage);
}

void Heavy_testpatch::cBinop_CSt8hZ6E_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_0hj99axj, HV_BINOP_MULTIPLY, 0, m, &cBinop_0hj99axj_sendMessage);
}

void Heavy_testpatch::cBinop_nGcPuWKL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_qBz2Yqxk_sendMessage(_c, 0, m);
  sTabread_onMessage(_c, &Context(_c)->sTabread_KbuVL2B0, 0, m, &sTabread_KbuVL2B0_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_NcXRhY6X_sendMessage);
}

void Heavy_testpatch::cSystem_eXn6bBgi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_4FncE7h1, HV_BINOP_SUBTRACT, 1, m, &cBinop_4FncE7h1_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_q3ZdkPTv, 2, m, &cDelay_q3ZdkPTv_sendMessage);
}

void Heavy_testpatch::cMsg_Xc59ItBU_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "table");
  msg_setElementToFrom(m, 1, n, 0);
  msg_setSymbol(m, 2, "size");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_eXn6bBgi_sendMessage);
}

void Heavy_testpatch::cMsg_qBz2Yqxk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_hbovN72V, 0, m, &cDelay_hbovN72V_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_q3ZdkPTv, 0, m, &cDelay_q3ZdkPTv_sendMessage);
}

void Heavy_testpatch::cMsg_4zMIcpC1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0,  static_cast<float>(HV_N_SIMD));
  cBinop_onMessage(_c, &Context(_c)->cBinop_ztYBjQxo, HV_BINOP_MAX, 1, m, &cBinop_ztYBjQxo_sendMessage);
}

void Heavy_testpatch::cBinop_ztYBjQxo_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_nGcPuWKL, HV_BINOP_SUBTRACT, 1, m, &cBinop_nGcPuWKL_sendMessage);
}

void Heavy_testpatch::cCast_NcXRhY6X_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_hbovN72V, 0, m, &cDelay_hbovN72V_sendMessage);
}

void Heavy_testpatch::cBinop_Lir3zUbH_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_hbovN72V, 2, m, &cDelay_hbovN72V_sendMessage);
}

void Heavy_testpatch::cBinop_4FncE7h1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_Lir3zUbH_sendMessage);
}

void Heavy_testpatch::cCast_VBcSSTWL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_4m6KQk0T, 0, m, &cVar_4m6KQk0T_sendMessage);
  cMsg_GSlAKRef_sendMessage(_c, 0, m);
  cTabhead_onMessage(_c, &Context(_c)->cTabhead_tS5gRwfm, 0, m, &cTabhead_tS5gRwfm_sendMessage);
}

void Heavy_testpatch::cVar_PPS8D8og_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_SCfBuhlS, m);
}

void Heavy_testpatch::cReceive_jTTBFdAl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_ZMri8dNu_sendMessage(_c, 0, m);
  cMsg_4zMIcpC1_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_4m6KQk0T, 0, m, &cVar_4m6KQk0T_sendMessage);
  cMsg_GSlAKRef_sendMessage(_c, 0, m);
  cTabhead_onMessage(_c, &Context(_c)->cTabhead_tS5gRwfm, 0, m, &cTabhead_tS5gRwfm_sendMessage);
}

void Heavy_testpatch::cReceive_zo9Jem4y_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sVarf_onMessage(_c, &Context(_c)->sVarf_SCfBuhlS, m);
}



/*
 * Code for expr~ implementation
 * Write out the generic implementation code
 */

 // per class code

 // per object code


/*
 * Context Process Implementation
 */

int Heavy_testpatch::process(float **inputBuffers, float **outputBuffers, int n) {
  while (hLp_hasData(&inQueue)) {
    hv_uint32_t numBytes = 0;
    ReceiverMessagePair *p = reinterpret_cast<ReceiverMessagePair *>(hLp_getReadBuffer(&inQueue, &numBytes));
    hv_assert(numBytes >= sizeof(ReceiverMessagePair));
    scheduleMessageForReceiver(p->receiverHash, &p->msg);
    hLp_consume(&inQueue);
  }

  sendBangToReceiver(0xDD21C0EB); // send to __hv_bang~ on next cycle
  const int n4 = n & ~HV_N_SIMD_MASK; // ensure that the block size is a multiple of HV_N_SIMD

  // temporary signal vars
  hv_bufferf_t Bf0, Bf1, Bf2, Bf3, Bf4;

  // input and output vars
  hv_bufferf_t O0, O1;

  // declare and init the zero buffer
  hv_bufferf_t ZERO; __hv_zero_f(VOf(ZERO));

  hv_uint32_t nextBlock = blockStartTimestamp;
  for (int n = 0; n < n4; n += HV_N_SIMD) {

    // process all of the messages for this block
    nextBlock += HV_N_SIMD;
    while (mq_hasMessageBefore(&mq, nextBlock)) {
      MessageNode *const node = mq_peek(&mq);
      node->sendMessage(this, node->let, node->m);
      mq_pop(&mq);
    }

    

    // zero output buffers
    __hv_zero_f(VOf(O0));
    __hv_zero_f(VOf(O1));

    // process all signal functions
    __hv_varread_f(&sVarf_SCfBuhlS, VOf(Bf0));
    __hv_phasor_f(&sPhasor_3lYYzklL, VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_abs_f(VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf0), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f, 6.283185307179586f);
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_mul_f(VIf(Bf1), VIf(Bf1), VOf(Bf0));
    __hv_mul_f(VIf(Bf1), VIf(Bf0), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf3), 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f, 0.007833333333333f);
    __hv_var_k_f(VOf(Bf4), -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f, -0.166666666666667f);
    __hv_fma_f(VIf(Bf2), VIf(Bf4), VIf(Bf1), VOf(Bf1));
    __hv_fma_f(VIf(Bf0), VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_tabread_f(&sTabread_KbuVL2B0, VOf(Bf3));
    __hv_var_k_f(VOf(Bf0), 0.8f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f);
    __hv_mul_f(VIf(Bf3), VIf(Bf0), VOf(Bf0));
    __hv_add_f(VIf(Bf1), VIf(Bf0), VOf(Bf3));
    __hv_tabwrite_f(&sTabwrite_zY8pboXb, VIf(Bf3));
    __hv_add_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f);
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_add_f(VIf(Bf1), VIf(O1), VOf(O1));
    __hv_add_f(VIf(Bf1), VIf(O0), VOf(O0));

    // save output vars to output buffer
    __hv_store_f(outputBuffers[0]+n, VIf(O0));
    __hv_store_f(outputBuffers[1]+n, VIf(O1));
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed

}

int Heavy_testpatch::processInline(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(!(n4 & HV_N_SIMD_MASK)); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s)
  float **const bIn = NULL;

  // define the heavy output buffer for 2 channel(s)
  float **const bOut = reinterpret_cast<float **>(hv_alloca(2*sizeof(float *)));
  bOut[0] = outputBuffers+(0*n4);
  bOut[1] = outputBuffers+(1*n4);

  int n = process(bIn, bOut, n4);
  return n;
}

int Heavy_testpatch::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(n4 & ~HV_N_SIMD_MASK); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s), uninterleave
  float *const bIn = NULL;

  // define the heavy output buffer for 2 channel(s)
  float *const bOut = reinterpret_cast<float *>(hv_alloca(2*n4*sizeof(float)));

  int n = processInline(bIn, bOut, n4);

  // interleave the heavy output into the output buffer
  #if HV_SIMD_AVX
  for (int i = 0, j = 0; j < n4; j += 8, i += 16) {
    __m256 x = _mm256_load_ps(bOut+j);    // LLLLLLLL
    __m256 y = _mm256_load_ps(bOut+n4+j); // RRRRRRRR
    __m256 a = _mm256_unpacklo_ps(x, y);  // LRLRLRLR
    __m256 b = _mm256_unpackhi_ps(x, y);  // LRLRLRLR
    _mm256_store_ps(outputBuffers+i, a);
    _mm256_store_ps(outputBuffers+8+i, b);
  }
  #elif HV_SIMD_SSE
  for (int i = 0, j = 0; j < n4; j += 4, i += 8) {
    __m128 x = _mm_load_ps(bOut+j);    // LLLL
    __m128 y = _mm_load_ps(bOut+n4+j); // RRRR
    __m128 a = _mm_unpacklo_ps(x, y);  // LRLR
    __m128 b = _mm_unpackhi_ps(x, y);  // LRLR
    _mm_store_ps(outputBuffers+i, a);
    _mm_store_ps(outputBuffers+4+i, b);
  }
  #elif HV_SIMD_NEON
  // https://community.arm.com/groups/processors/blog/2012/03/13/coding-for-neon--part-5-rearranging-vectors
  for (int i = 0, j = 0; j < n4; j += 4, i += 8) {
    float32x4_t x = vld1q_f32(bOut+j);
    float32x4_t y = vld1q_f32(bOut+n4+j);
    float32x4x2_t z = {x, y};
    vst2q_f32(outputBuffers+i, z); // interleave and store
  }
  #else // HV_SIMD_NONE
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < n4; ++j) {
      outputBuffers[i+2*j] = bOut[i*n4+j];
    }
  }
  #endif

  return n;
}

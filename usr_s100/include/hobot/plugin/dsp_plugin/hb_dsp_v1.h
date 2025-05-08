// Copyright (c) 2024 Horizon Robotics.All Rights Reserved.
//
// The material in this file is confidential and contains trade secrets
// of Horizon Robotics Inc. This is proprietary information owned by
// Horizon Robotics Inc. No part of this work may be disclosed,
// reproduced, copied, transmitted, or used in any way for any purpose,
// without the express written permission of Horizon Robotics Inc.

#ifndef PLUGIN_DSP_PLUGIN_HB_DSP_V1_H_
#define PLUGIN_DSP_PLUGIN_HB_DSP_V1_H_

#include <stdint.h>

#include "hobot/hb_sys.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#define HB_DSP_INITIALIZE_RPC_CTRL_PARAM(param) \
  {                                             \
    (param)->dspCoreId = HB_DSP_CORE_ANY;       \
    (param)->rpcCmd = HB_DSP_RPC_CMD_BUTT;      \
    (param)->priority = 0;                      \
  }

typedef enum {
  HB_DSP_RPC_PRIORITY_LOWEST = 0,
  HB_DSP_RPC_PRIORITY_HIGHEST = 255,
  HB_DSP_RPC_PRIORITY_PREEMP = HB_DSP_RPC_PRIORITY_HIGHEST
} hbDspRpcPriority;

typedef struct {
  int32_t dspCoreId;
  int32_t rpcCmd;
  int32_t priority;
  int32_t customId;
  int32_t reserved2;
  int32_t reserved3;
  int32_t reserved4;
} hbDSPRpcCtrlParam;

typedef void *hbDSPTask_t;

/**
 * @brief DSP Rpc
 * 
 * @param[out] task pointer to the task
 * @param[in] input pointer to a custom structure for input
 * @param[in] output pointer to a custom structure for output
 * @param[in] rpcCtrlParam control param for rpc process
 * @return 0 if success, return defined error code otherwise
 */
int32_t hbDSPRpc(hbDSPTask_t *task, hbSysMem *input, hbSysMem *output,
                 hbDSPRpcCtrlParam *rpcCtrlParam);

/**
 * @brief Wait util task completed or timeout
 * 
 * @param[in] task pointer to the task
 * @param[in] timeout timeout of milliseconds
 * @return 0 if success, return defined error code otherwise
 */
int32_t hbDSPWaitTaskDone(hbDSPTask_t task, int32_t timeout);

/**
 * @brief Release a task and its related resources.
 * This interface will return immediately, and all operations will run in the
 * background
 * 
 * @param[in] task pointer to the task
 * @return 0 if success, return defined error code otherwise
 */
int32_t hbDSPReleaseTask(hbDSPTask_t task);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // PLUGIN_DSP_PLUGIN_HB_DSP_V1_H_

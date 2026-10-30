//
// Copyright 2023 Horizon Robotics.
//

#ifndef INCLUDE_CANHAL_CAN_DEV_H_
#define INCLUDE_CANHAL_CAN_DEV_H_

#include <functional>
#include <memory>
#include <string>
#if defined (__linux__)
#include <linux/can.h>
#endif
#include "canhal/can_hal_type_def.h"
#include "canhal/msg_type.h"
#ifdef __cplusplus
extern "C" {
#endif

namespace hobot {
namespace canhal {

class CanHal {
 public:
  CanHal() = default;
  virtual ~CanHal() = default;

  static std::shared_ptr<CanHal> Instance();
  virtual ErrorCode Init() = 0;
  virtual ErrorCode Deinit() = 0;
  virtual int32_t SendMsg(const std::string target, RawPack &data) = 0;
  virtual ErrorCode RecvMsg(const std::string target, RawPack &data) = 0;
  virtual int32_t SendMsg(const std::string target, CanFramePack &data) = 0;
  virtual ErrorCode RecvMsg(const std::string target, CanFramePack &data) = 0;
  virtual int32_t SendMsg(const std::string target, CanConfigPack &data) = 0;
  virtual int32_t SendMsg(const std::string target, CanFramePack &data, const Pack_Info* pack_info) = 0;
};

}  // namespace canhal
}  // namespace hobot
/**
 * canSetConfigPaths_() - override the directories searched for config files.
 *
 * Must be called **before** canInit_().  If not called, or if a slot is NULL /
 * empty, the HAL defaults to the "./config" directory for both files.
 *
 * The HAL loads two JSON files at init time:
 *   - <nodes_config_dir>/nodes.json
 *   - <channels_config_dir>/channels.json
 *
 * @nodes_config_dir:    Directory containing nodes.json.
 *                       Pass NULL or "" to keep the default ("config").
 * @channels_config_dir: Directory containing channels.json.
 *                       Pass NULL or "" to keep the default ("config").
 */
void canSetConfigPaths_(const char *nodes_config_dir, const char *channels_config_dir);
int canInit_();
void canDeInit_();
int canRecvMsgRaw_(const char *target, uint8_t *rx_buf, hobot::canhal::Pack_Info *pack);
int canSendMsgRaw_(const char *target, uint8_t *tx_buf, hobot::canhal::Pack_Info *pack);
int canRecvMsgFrame_(const char *target, hobot::canhal::CanFrame *frame, hobot::canhal::Pack_Info *pack);
int canSendMsgFrame_(const char *target, hobot::canhal::CanFrame *frame, hobot::canhal::Pack_Info *pack);
int canSendMsgConfig_(const char *target, hobot::canhal::Can_Config_Filter_Type *filter, hobot::canhal::Pack_Info *pack);

#ifdef __cplusplus
} // extern "C"
#endif
#endif  //  INCLUDE_CANHAL_CAN_DEV_H_

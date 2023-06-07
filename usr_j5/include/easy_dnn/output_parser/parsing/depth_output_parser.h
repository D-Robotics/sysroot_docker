// Copyright (c) 2021 Horizon Robotics.All Rights Reserved.
//
// The material in this file is confidential and contains trade secrets
// of Horizon Robotics Inc. This is proprietary information owned by
// Horizon Robotics Inc. No part of this work may be disclosed,
// reproduced, copied, transmitted, or used in any way for any purpose,
// without the express written permission of Horizon Robotics Inc.

#ifndef EASY_DNN_DEPTH_OUTPUT_PARSER_H
#define EASY_DNN_DEPTH_OUTPUT_PARSER_H

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "easy_dnn/data_structure.h"
#include "easy_dnn/model.h"
#include "easy_dnn/output_parser.h"

namespace hobot {
namespace easy_dnn {

/* json data sample
{
    "task":"depth",
    "scale_number":10,
    "roi_input":{
        "fp_x":480,
        "fp_y":270,
        "width":960,
        "height":512
    },
    "vanishing_point":[
        480,
        270
    ]
}
 */

class DepthOutputDescription : public OutputDescription {
 public:
  DepthOutputDescription(Model *mode, int index, std::string type = "")
      : OutputDescription(mode, index, type) {}
  int scale_number;
};

class DepthOutputDescriptionParser : public OutputDescriptionParser {
 public:
  std::pair<std::shared_ptr<OutputDescription>, std::shared_ptr<OutputParser>>
  Parse(rapidjson::Document &desc_doc,
        Model *model,
        int32_t output_index) override;
};

class DepthResult : public DNNResult {
 public:
  std::vector<float> depth;
  int height;
  int width;
  int channel;
};

class DepthOutputParser : public SingleBranchOutputParser {
 public:
  int32_t Parse(
      std::shared_ptr<DNNResult> &output,
      std::vector<std::shared_ptr<InputDescription>> &input_descriptions,
      std::shared_ptr<OutputDescription> &output_description,
      std::shared_ptr<DNNTensor> &output_tensor) override;
};

}  // namespace easy_dnn
}  // namespace hobot
#endif  // EASY_DNN_DEPTH_OUTPUT_PARSER_H
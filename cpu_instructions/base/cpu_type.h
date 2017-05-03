// Copyright 2017 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef CPU_INSTRUCTIONS_BASE_CPU_TYPE_H_
#define CPU_INSTRUCTIONS_BASE_CPU_TYPE_H_

#include "cpu_instructions/base/port_mask.h"
#include "cpu_instructions/proto/microarchitecture.pb.h"

namespace cpu_instructions {

class MicroArchitecture;

// Represents a CpuModelProto in memory. See the proto documentation for
// details.
class CpuModel {
 public:
  // Returns nullptr if the cpu model is unknown.
  static const CpuModel* FromCpuId(const string& cpu_id);

  // For tests. CPUs per reverse chronological order.
  static const CpuModel& Skylake() {
    return *CHECK_NOTNULL(FromCpuId("intel:06_4E"));
  }

  static const CpuModel& Broadwell() {
    return *CHECK_NOTNULL(FromCpuId("intel:06_3D"));
  }

  static const CpuModel& Haswell() {
    return *CHECK_NOTNULL(FromCpuId("intel:06_3C"));
  }

  static const CpuModel& IvyBridge() {
    return *CHECK_NOTNULL(FromCpuId("intel:06_3A"));
  }

  static const CpuModel& SandyBridge() {
    return *CHECK_NOTNULL(FromCpuId("intel:06_2A"));
  }

  static const CpuModel& Westmere() {
    return *CHECK_NOTNULL(FromCpuId("intel:06_25"));
  }

  static const CpuModel& Nehalem() {
    return *CHECK_NOTNULL(FromCpuId("intel:06_1A"));
  }

  CpuModel(const CpuModelProto* proto,
           const MicroArchitecture* microarchitecture);
  CpuModel(CpuModel&&) = default;

  const CpuModelProto& proto() const { return *proto_; }

  const MicroArchitecture& microarchitecture() const;

 private:
  CpuModel() = delete;
  CpuModel(const CpuModel&) = delete;

  const CpuModelProto* const proto_;
  const MicroArchitecture* const microarchitecture_;
};

// Represents a MicroArchitectureProto in memory. See the proto documentation
// for details.
class MicroArchitecture {
 public:
  // Returns nullptr if unknown.
  static const MicroArchitecture* FromId(const string& microarchitecture_id);

  explicit MicroArchitecture(const MicroArchitectureProto& proto);

  const MicroArchitectureProto& proto() const { return proto_; }

  // Returns the port masks, in the same order as the proto.
  const std::vector<PortMask>& port_masks() const { return port_masks_; }

  // Port masks with specific semantics. Returns null if unavailable.
  const PortMask* load_store_address_generation() const;
  const PortMask* store_address_generation() const;
  const PortMask* store_data() const;

  // Returns true if a protection mode is in the protected range (e.g. 0 is
  // protected in x86 but 3 is not). protection_mode < 0 is the default.
  bool IsProtectedMode(int protection_mode) const;

  const std::vector<CpuModel>& cpu_models() const { return cpu_models_; }

 private:
  MicroArchitecture() = delete;
  MicroArchitecture(const MicroArchitecture&) = delete;

  const PortMask* GetPortMaskOrNull(const int index) const;

  const MicroArchitectureProto proto_;
  const std::vector<PortMask> port_masks_;
  std::vector<CpuModel> cpu_models_;
};

}  // namespace cpu_instructions

#endif  // CPU_INSTRUCTIONS_BASE_CPU_TYPE_H_

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

#include <stdlib.h>

#include "exegesis/arm/xml/converter.h"
#include "exegesis/arm/xml/parser.h"
#include "exegesis/arm/xml/parser.pb.h"
#include "exegesis/proto/instructions.pb.h"
#include "exegesis/util/proto_util.h"
#include "gflags/gflags.h"
#include "glog/logging.h"

DEFINE_string(exegesis_arm_xml_path, "",
              "The directory containing the ARM documentation in XML format. "
              "Required.");
DEFINE_string(exegesis_xml_database_output_file, "",
              "Where to dump the parsed XML database. Optional.");
DEFINE_string(exegesis_isa_output_file, "",
              "Where to dump the Instruction Set Architecture. Optional.");

namespace exegesis {
namespace {

void Main() {
  CHECK(!FLAGS_exegesis_arm_xml_path.empty())
      << "missing --exegesis_arm_xml_path";

  const arm::xml::XmlDatabase xml_database =
      arm::xml::ParseXmlDatabaseOrDie(FLAGS_exegesis_arm_xml_path);
  if (!FLAGS_exegesis_xml_database_output_file.empty()) {
    WriteTextProtoOrDie(FLAGS_exegesis_xml_database_output_file, xml_database);
  }

  const ArchitectureProto architecture_proto =
      arm::xml::ConvertToArchitectureProto(xml_database);
  if (!FLAGS_exegesis_isa_output_file.empty()) {
    WriteTextProtoOrDie(FLAGS_exegesis_isa_output_file, architecture_proto);
  }
}

}  // namespace
}  // namespace exegesis

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, /* remove_flags = */ true);
  ::exegesis::Main();
  return EXIT_SUCCESS;
}

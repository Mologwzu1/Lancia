load("@rules_cc//cc:defs.bzl", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("//tools:python_rules.bzl", "py_proto_library")
package(default_visibility = ["//visibility:public"])

proto_library(
    name = "autobot_proto",
    srcs = ["autobot.proto"],
)

cc_proto_library(
    name = "autobot_cc_proto",
    deps = [":autobot_proto"],
)
load("@rules_cc//cc:defs.bzl", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("//tools:python_rules.bzl", "py_proto_library")
package(default_visibility = ["//visibility:public"])

proto_library(
    name = "examples_proto",
    srcs = ["examples.proto"],
)

cc_proto_library(
    name = "examples_cc_proto",
    deps = [":examples_proto",],
)

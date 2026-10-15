
load("@rules_cc//cc:defs.bzl", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("//tools:python_rules.bzl", "py_proto_library")
package(default_visibility = ["//visibility:public"])

proto_library(
    name = "indicator_log_proto",
    srcs = ["indicator_log.proto"],
)

cc_proto_library(
    name = "indicator_log_cc_proto",
    deps = [":indicator_log_proto"],
)

proto_library(
    name = "junior_log_proto",
    srcs = ["junior_log.proto"],
)

cc_proto_library(
    name = "junior_log_cc_proto",
    deps = [":junior_log_proto"],
)

proto_library(
    name = "log_proto",
    srcs = ["log.proto"],
)

cc_proto_library(
    name = "log_cc_proto",
    deps = [":log_proto"],
)
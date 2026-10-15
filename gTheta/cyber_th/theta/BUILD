load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_proto_library")
load("//tools/install:install.bzl", "install", "install_src_files")
load("//tools:cpplint.bzl", "cpplint")
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

filegroup(
    name = "cyber_th_hdrs",
    srcs = glob([
        "*.h",
    ]),
)
cc_library(
    name = "indicator",
    srcs = ["indicator.cc"],
    hdrs = ["indicator.h"],
    deps = [
        "//cyber",
    ], 
)

cpplint()

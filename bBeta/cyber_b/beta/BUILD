load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//tools/install:install.bzl", "install", "install_src_files")
load("//tools:cpplint.bzl", "cpplint")
package(default_visibility = ["//visibility:public"])

filegroup(
    name = "cyber_b_hdrs",
    srcs = glob([
        "*.h",
    ]),
)

cc_library(
    name = "jitter",
    srcs = ["jitter.cc"],
    hdrs = ["jitter.h"],
    deps = [
        "//cyber",
    ], 
)

cc_library(
    name = "delay",
    srcs = ["delay.cc"],
    hdrs = ["delay.h"],
    deps = [
        "//cyber",
    ], 
)

cpplint()

load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//tools/install:install.bzl", "install", "install_src_files")
load("//tools:cpplint.bzl", "cpplint")
package(default_visibility = ["//visibility:public"])

filegroup(
    name = "cyber_y_hdrs",
    srcs = glob([
        "*.h",
    ]),
)
cc_library(
    name = "indicator_monitor",
    srcs = ["indicator_monitor.cc"],
    hdrs = ["indicator_monitor.h"],
    deps = [
        "//cyber_y/ypsilon:junior_log_cc_proto",
    ], 
)
cc_library(
    name = "monitor_agent",
    srcs = ["monitor_agent.cc"],
    hdrs = ["monitor_agent.h"],
    deps = [
        "//cyber_y/ypsilon:junior_log_cc_proto",
        "//cyber/time:time",
        "//cyber/common:macros",
        ":indicator_monitor",
    ], 
)

cpplint()

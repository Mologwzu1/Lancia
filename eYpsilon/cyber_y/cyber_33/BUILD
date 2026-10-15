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
        "//cyber/time:time",
        "//cyber_y/ypsilon:indicator_log_cc_proto",
    ], 
)

cc_library(
    name = "monitor_manager",
    srcs = ["monitor_manager.cc"],
    hdrs = ["monitor_manager.h"],
    deps = [
        "//cyber/time:time",
        "indicator_monitor",
        "//cyber_y/ypsilon:indicator_log_cc_proto",
    ], 
)

cc_library(
    name = "manager_agent",
    srcs = ["manager_agent.cc"],
    hdrs = ["manager_agent.h"],
    deps = [
        "monitor_manager",
        "//cyber/common:macros",
        "//cyber_y/ypsilon:indicator_log_cc_proto",
        "//cyber/time:time",
        "//cyber/proto:role_attributes_cc_proto",
    ], 
)

cpplint()

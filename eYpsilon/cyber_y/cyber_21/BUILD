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
    name = "log_writer",
    srcs = ["log_writer.cc"],
    hdrs = ["log_writer.h"],
    deps = [
        "//cyber_y/ypsilon:log_cc_proto",
    ], 
)
cc_library(
    name = "writer_agent",
    srcs = ["writer_agent.cc"],
    hdrs = ["writer_agent.h"],
    deps = [
        "//cyber/time:time",
        ":log_writer",
        "//cyber_y/ypsilon:log_cc_proto",
    ], 
)

cpplint()

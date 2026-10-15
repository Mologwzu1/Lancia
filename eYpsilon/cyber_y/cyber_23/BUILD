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
    name = "writer_agent",
    srcs = ["writer_agent.cc"],
    hdrs = ["writer_agent.h"],
    deps = [
        "//cyber/time:time",
        "//cyber_y/cyber_21:log_writer",
        "//cyber_y/ypsilon:log_cc_proto",
    ], 
)

cpplint()

load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//tools/install:install.bzl", "install", "install_src_files")
load("//tools:cpplint.bzl", "cpplint")
package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "broadcast",
    srcs = ["broadcast.cc"],
    deps = [
        "//cyber",
        "//cyber_th/theta:autobot_cc_proto"
    ], 
)
cc_binary(
    name = "audience",
    srcs = ["audience.cc"],
    deps = [
        "//cyber",
        "//cyber_th/theta:autobot_cc_proto"
    ], 
)

cc_binary(
    name = "talker",
    srcs = ["talker.cc"],
    deps = [
        "//cyber",
        "//cyber_th/theta:autobot_cc_proto"
    ], 
)
cc_binary(
    name = "listener",
    srcs = ["listener.cc"],
    deps = [
        "//cyber",
        "//cyber_th/theta:autobot_cc_proto",
        "//cyber_th/theta:indicator"
    ], 
)
cc_binary(
    name = "midware",
    srcs = ["midware.cc"],
    deps = [
        "//cyber",
        "//cyber_th/theta:autobot_cc_proto",
        "//cyber_th/theta:indicator"
    ], 
)
cc_binary(
    name = "calculator",
    srcs = ["calculator.cc"],
    deps = [
        "//cyber_y/cyber_33:manager_agent"
    ], 
)

install(
    name = "install",
    runtime_dest = "cyber_th/bin",
    targets = [
        ":broadcast",
        ":audience",
        ":talker",
        ":listener",
        ":midware",
        ":calculator"
    ],
)

install_src_files(
    name = "install_src",
    src_dir = ["."],
    dest = "cyber_th/src/cyber_16",
    filter = "*",
)
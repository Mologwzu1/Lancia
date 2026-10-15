load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//tools/install:install.bzl", "install", "install_src_files")
load("//tools:cpplint.bzl", "cpplint")
package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "midware",
    srcs = ["midware.cc"],
    deps = [
        "//cyber_y/ypsilon:indicator_log_cc_proto",
        "//cyber_y/cyber_33:manager_agent",
    ], 
)

cc_binary(
    name = "calculator",
    srcs = ["calculator.cc"],
    deps = [
        "//cyber_y/cyber_33:manager_agent",
    ], 
)

cc_binary(
    name = "broadcast",
    srcs = ["broadcast.cc"],
    deps = [
        "//cyber_y/ypsilon:indicator_log_cc_proto",
        "//cyber_y/cyber_33:manager_agent"
    ], 
)
cc_binary(
    name = "audience",
    srcs = ["audience.cc"],
    deps = [
        "//cyber_y/ypsilon:indicator_log_cc_proto",
        "//cyber_y/cyber_33:manager_agent"
    ], 
)
cc_binary(
    name = "listener",
    srcs = ["listener.cc"],
    deps = [
        "//cyber_y/ypsilon:indicator_log_cc_proto",
        "//cyber_y/cyber_33:manager_agent" 
    ], 
)
cc_binary(
    name = "talker",
    srcs = ["talker.cc"],
    deps = [
        "//cyber_y/ypsilon:indicator_log_cc_proto",
        "//cyber_y/cyber_33:manager_agent"
    ], 
)
cc_binary(
    name = "speaker",
    srcs = ["speaker.cc"],
    deps = [
        "//cyber_y/ypsilon:indicator_log_cc_proto",
        "//cyber_y/cyber_33:manager_agent"
    ], 
)

install(
    name = "install",
    runtime_dest = "cyber_y/bin",
    targets = [
        ":midware",
        ":calculator",
        ":broadcast",
        ":audience",
        ":listener",
        ":talker",
        ":speaker"
    ],
)

install_src_files(
    name = "install_src",
    src_dir = ["."],
    dest = "cyber_y/src/cyber_15",
    filter = "*",
)
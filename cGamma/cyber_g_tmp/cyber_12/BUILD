load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//tools/install:install.bzl", "install", "install_src_files")
load("//tools:cpplint.bzl", "cpplint")
package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "broadcast",
    srcs = ["broadcast.cc"],
    deps = [
        "//cyber",
        "//cyber_g/gamma:autobot_cc_proto"
    ], 
)
cc_binary(
    name = "audience",
    srcs = ["audience.cc"],
    deps = [
        "//cyber",
        "//cyber_g/gamma:autobot_cc_proto"
    ], 
)
cc_binary(
    name = "midware",
    srcs = ["midware.cc"],
    deps = [
        "//cyber",
        "//cyber_g/gamma:autobot_cc_proto",
        "//cyber_g/gamma:indicator"
    ], 
)

install(
    name = "install",
    runtime_dest = "cyber_g/bin",
    targets = [
        ":broadcast",
        ":audience",
        ":midware"
    ],
)

install_src_files(
    name = "install_src",
    src_dir = ["."],
    dest = "cyber_g/src/cyber_12",
    filter = "*",
)
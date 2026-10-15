load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//tools/install:install.bzl", "install", "install_src_files")
load("//tools:cpplint.bzl", "cpplint")
package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "talker",
    srcs = ["talker.cc"],
    deps = [
        "//cyber",
        "//cyber_g/gamma:autobot_cc_proto"
    ], 
)
cc_binary(
    name = "listener",
    srcs = ["listener.cc"],
    deps = [
        "//cyber",
        "//cyber_g/gamma:autobot_cc_proto",
        "//cyber_g/gamma:indicator",
    ], 
)

install(
    name = "install",
    runtime_dest = "cyber_g/bin",
    targets = [
        ":talker",
        ":listener",
    ],
)

install_src_files(
    name = "install_src",
    src_dir = ["."],
    dest = "cyber_g/src/cyber_11",
    filter = "*",
)
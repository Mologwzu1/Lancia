load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//tools/install:install.bzl", "install", "install_src_files")
load("//tools:cpplint.bzl", "cpplint")
package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "talker",
    srcs = ["talker.cc"],
    deps = [
        "//cyber",
        "//cyber_b/proto:autobot_cc_proto"
    ], 
)
cc_binary(
    name = "listener",
    srcs = ["listener.cc"],
    deps = [
        "//cyber",
        "//cyber_b/proto:autobot_cc_proto",
        "//cyber_b/beta:delay",
    ], 
)

install(
    name = "install",
    runtime_dest = "cyber_b/bin",
    targets = [
        ":talker",
        ":listener",
    ],
)

install_src_files(
    name = "install_src",
    src_dir = ["."],
    dest = "cyber_b/src/cyber_11",
    filter = "*",
)
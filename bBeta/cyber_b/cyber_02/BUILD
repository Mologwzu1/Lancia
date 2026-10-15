load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//tools/install:install.bzl", "install", "install_src_files")
load("//tools:cpplint.bzl", "cpplint")
package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "server",
    srcs = ["server.cc"],
    deps = [
        "//cyber",
        "//cyber_b/proto:autobot_cc_proto"
    ], 
)
cc_binary(
    name = "client",
    srcs = ["client.cc"],
    deps = [
        "//cyber",
        "//cyber_b/proto:autobot_cc_proto"
    ], 
)

install(
    name = "install",
    runtime_dest = "cyber_b/bin",
    targets = [
        ":server",
        ":client",
    ],
)

install_src_files(
    name = "install_src",
    src_dir = ["."],
    dest = "cyber_b/src/cyber_02",
    filter = "*",
)
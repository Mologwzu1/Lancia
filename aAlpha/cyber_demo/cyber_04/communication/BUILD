load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//tools/install:install.bzl", "install", "install_src_files")
load("//tools:cpplint.bzl", "cpplint")
package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "talker",
    srcs = ["talker.cc"],
    deps = [
        "//cyber",
        "//cyber_demo/cyber_04/proto:autobot_cc_proto"
    ], 
)
cc_binary(
    name = "listener",
    srcs = ["listener.cc"],
    deps = [
        "//cyber",
        "//cyber_demo/cyber_04/proto:autobot_cc_proto"
    ], 
)
cc_binary(
    name = "server",
    srcs = ["server.cc"],
    deps = [
        "//cyber",
        "//cyber_demo/cyber_04/proto:autobot_cc_proto"
    ], 
)
cc_binary(
    name = "client",
    srcs = ["client.cc"],
    deps = [
        "//cyber",
        "//cyber_demo/cyber_04/proto:autobot_cc_proto"
    ], 
)

cc_binary(
    name = "param_server",
    srcs = ["param_server.cc"],
    deps = [
        "//cyber",
        "//cyber/parameter",
    ],
    linkstatic = True,
)
cc_binary(
    name = "param_client",
    srcs = ["param_client.cc"],
    deps = [
        "//cyber",
        "//cyber/parameter",
    ],
    linkstatic = True,
)

install(
    name = "install",
    runtime_dest = "cyber_demo/bin",
    targets = [
        ":talker",
        ":listener",
        ":server",
        ":client",
        ":param_client",
        ":param_server"
    ],
)

install_src_files(
    name = "install_src",
    src_dir = ["."],
    dest = "cyber_demo/src/cyber_04",
    filter = "*",
)
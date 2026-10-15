load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//tools/install:install.bzl", "install", "install_src_files")
load("//tools:cpplint.bzl", "cpplint")
package(default_visibility = ["//visibility:public"])

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
    runtime_dest = "cyber_b/bin",
    targets = [
        ":param_client",
        ":param_server"
    ],
)

install_src_files(
    name = "install_src",
    src_dir = ["."],
    dest = "cyber_b/src/cyber_03",
    filter = "*",
)
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//tools/install:install.bzl", "install", "install_src_files")
load("//tools:cpplint.bzl", "cpplint")
package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "main01",
    srcs = ["main.cc"],
    deps = ["//cyber"], 
)

install(
    name = "install",
    runtime_dest = "cyber_demo/bin",
    targets = [
        ":main01"
    ],
)

install_src_files(
    name = "install_src",
    src_dir = ["."],
    dest = "cyber_demo/src/cyber_01",
    filter = "*",
)
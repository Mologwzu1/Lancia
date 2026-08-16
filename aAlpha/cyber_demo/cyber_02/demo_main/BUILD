load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//tools/install:install.bzl", "install", "install_src_files")
load("//tools:cpplint.bzl", "cpplint")
package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "main02",
    srcs = ["main.cc"],
    deps = ["//cyber_demo/cyber_02/demo_lib:getName_lib"], 
)

install(
    name = "install",
    runtime_dest = "cyber_demo/bin",
    targets = [
        ":main02"
    ],
)

install_src_files(
    name = "install_src",
    src_dir = ["."],
    dest = "cyber_demo/src/cyber_02",
    filter = "*",
)

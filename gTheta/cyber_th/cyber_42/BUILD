load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//tools/install:install.bzl", "install", "install_src_files")
load("//tools:cpplint.bzl", "cpplint")
package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "libreader.so",
    linkshared = True,
    linkstatic = True,
    deps = [":reader_lib"],
)

cc_library(
    name = "reader_lib",
    srcs = ["reader.cc"],
    hdrs = ["reader.h"],
    visibility = ["//visibility:private"],
    deps = [
        "//cyber",
        "//cyber_th/theta:autobot_cc_proto",
        "//cyber_th/theta:indicator"
    ],
    alwayslink = True,
)

filegroup(
    name = "conf",
    srcs = [
        ":reader.dag",
        ":reader.launch",
    ],
)

install(
    name = "install",
    data = [
        ":conf",
    ],
    data_dest = "test/component/conf",
    library_dest = "test/lib",
    targets = [
        ":libreader.so",
    ],
)

install_src_files(
    name = "install_src",
    src_dir = ["."],
    dest = "cyber_th/src/cyber_42",
    filter = "*",
)
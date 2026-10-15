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
        "//cyber_g/gamma:autobot_cc_proto",
        "//cyber_g/gamma:indicator"
    ],
    alwayslink = True,
)

cc_binary(
    name = "driver_writer",
    srcs = ["driver_writer.cc"],
    linkstatic = True,
    deps = [
        "//cyber",
        "//cyber_g/gamma:autobot_cc_proto"
    ],
)
cc_binary(
    name = "chatter_writer",
    srcs = ["chatter_writer.cc"],
    linkstatic = True,
    deps = [
        "//cyber",
        "//cyber_g/gamma:autobot_cc_proto",
            ],
)

filegroup(
    name = "conf",
    srcs = [
        ":common.dag",
        ":common.launch",
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
        ":driver_writer",
        ":chatter_writer",
        ":libreader.so",
    ],
)

install_src_files(
    name = "install_src",
    src_dir = ["."],
    dest = "cyber_g/src/cyber_41",
    filter = "*",
)
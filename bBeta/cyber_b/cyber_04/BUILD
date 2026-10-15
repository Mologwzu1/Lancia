load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//tools/install:install.bzl", "install", "install_src_files")
load("//tools:cpplint.bzl", "cpplint")
package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "libcomponent.so",
    linkshared = True,
    linkstatic = True,
    deps = [":example_lib"],
)

cc_library(
    name = "example_lib",
    srcs = ["example.cc"],
    hdrs = ["example.h"],
    visibility = ["//visibility:private"],
    deps = [
        "//cyber",
        "//cyber_b/proto:autobot_cc_proto"
    ],
    alwayslink = True,
)

cc_binary(
    name = "driver_writer",
    srcs = ["driver_writer.cc"],
    linkstatic = True,
    deps = [
        "//cyber",
        "//cyber_b/proto:autobot_cc_proto"
    ],
)
cc_binary(
    name = "chatter_writer",
    srcs = ["chatter_writer.cc"],
    linkstatic = True,
    deps = [
        "//cyber",
        "//cyber_b/proto:autobot_cc_proto",
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
        ":libcomponent.so",
    ],
)

install_src_files(
    name = "install_src",
    src_dir = ["."],
    dest = "cyber_b/src/cyber_41",
    filter = "*",
)
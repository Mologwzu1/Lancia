load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//tools/install:install.bzl", "install", "install_src_files")
load("//tools:cpplint.bzl", "cpplint")
package(default_visibility = ["//visibility:public"])

cc_binary( 
    name = "libdriver.so",
    linkshared = True,
    linkstatic = True,
    deps = [":driver_lib"],
)

cc_library(
    name = "driver_lib",
    srcs = ["driver.cc"],
    hdrs = ["driver.h"],
    visibility = ["//visibility:private"],
    deps = [
        "//cyber",
        "//cyber_g/gamma:autobot_cc_proto",
        "//cyber_g/gamma:indicator"
    ],
    alwayslink = True,
)

filegroup(
    name = "driver_conf",
    srcs = [
        ":driver.dag",
        ":driver.launch",
    ],
)

install(
    name = "driver_install",
    data = [
        ":driver_conf",
    ],
    data_dest = "test/timer_component/conf",
    library_dest = "//apollo_workspace/bazel-bin/cyber_g/cyber_52",
    targets = [
        ":libdriver.so",
    ],
)

install(
    name = "install",
    deps = [":driver_install"]
)

install_src_files(
    name = "install_src",
    src_dir = ["."],
    dest = "cyber_g/src/cyber_52",
    filter = "*",
)
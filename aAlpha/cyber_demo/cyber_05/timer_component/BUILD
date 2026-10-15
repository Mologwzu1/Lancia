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
    deps = [
        "//cyber",
        "//cyber_demo/cyber_05/proto:examples_cc_proto",
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
    library_dest = "test/lib",
    targets = [
        ":libdriver.so",
    ],
)

cc_binary( 
    name = "libchatter.so",
    linkshared = True,
    linkstatic = True,
    deps = [":chatter_lib"],
)

cc_library(
    name = "chatter_lib",
    srcs = ["chatter.cc"],
    hdrs = ["chatter.h"],
    deps = [
        "//cyber",
        "//cyber_demo/cyber_05/proto:examples_cc_proto",
    ],
    alwayslink = True,
)
filegroup(
    name = "chatter_conf",
    srcs = [
        ":chatter.dag",
        ":chatter.launch",
    ],
)

install(
    name = "chatter_install",
    data = [
        ":chatter_conf",
],
    data_dest = "test/timer_component/conf",
    library_dest = "test/lib",
    targets = [
        ":libchatter.so",
    ],
)

install(
    name = "install",
    deps = [
        ":chatter_install",
        ":driver_install"
    ]
)

install_src_files(
    name = "install_src",
    src_dir = ["."],
    dest = "cyber_demo/src/cyber_05/timer_component",
    filter = "*",
)
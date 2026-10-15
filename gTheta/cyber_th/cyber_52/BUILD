load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//tools/install:install.bzl", "install", "install_src_files")
load("//tools:cpplint.bzl", "cpplint")
package(default_visibility = ["//visibility:public"])

cc_binary( 
    name = "libdritter_reader.so",
    linkshared = True,
    linkstatic = True,
    deps = [":dritter_reader_lib"],
)

cc_library(
    name = "dritter_reader_lib",
    srcs = ["dritter_reader.cc"],
    hdrs = ["dritter_reader.h"],
    visibility = ["//visibility:private"],
    deps = [
        "//cyber",
        "//cyber_th/theta:autobot_cc_proto",
        "//cyber_th/theta:indicator"
    ],
    alwayslink = True,
)

filegroup(
    name = "dritter_reader_conf",
    srcs = [
        ":dritter_reader.dag",
        ":dritter_reader.launch",
    ],
)

install(
    name = "dritter_reader_install",
    data = [
        ":dritter_reader_conf",
    ],
    data_dest = "test/timer_component/conf",
    library_dest = "//apollo_workspace/bazel-bin/cyber_g/cyber_52",
    targets = [
        ":libdritter_reader.so",
    ],
)

cc_binary( 
    name = "libdritter_writer.so",
    linkshared = True,
    linkstatic = True,
    deps = [":dritter_writer_lib"],
)

cc_library(
    name = "dritter_writer_lib",
    srcs = ["dritter_writer.cc"],
    hdrs = ["dritter_writer.h"],
    visibility = ["//visibility:private"],
    deps = [
        "//cyber",
        "//cyber_th/theta:autobot_cc_proto",
        "//cyber_th/theta:indicator"
    ],
    alwayslink = True,
)

filegroup(
    name = "dritter_writer_conf",
    srcs = [
        ":dritter_writer.dag",
        ":dritter_writer.launch",
    ],
)

install(
    name = "dritter_writer_install",
    data = [
        ":dritter_writer_conf",
    ],
    data_dest = "test/timer_component/conf",
    library_dest = "//apollo_workspace/bazel-bin/cyber_g/cyber_52",
    targets = [
        ":libdritter_writer.so",
    ],  
)

install(
    name = "install",
    deps = [
        ":dritter_reader_install",
        ":dritter_writer_install"
    ]
)   

install_src_files(
    name = "install_src",
    src_dir = ["."],
    dest = "cyber_th/src/cyber_52",
    filter = "*",
)

load("//tools/install:install.bzl", "install", "install_src_files")

install(
    name = "install",
    data = [
        "cyber_y.BUILD",
        "cyberfile.xml",
    ],
    deps = [
        #"//cyber_y/cyber_13:install",
        #"//cyber_y/cyber_14:install",
        "//cyber_y/cyber_15:install",
    ],
)

install_src_files(
    name = "install_src",
    src_dir = ["."],
    dest = "cyber_y/src",
    filter = "*",
    deps = [
        #"//cyber_y/cyber_13:install_src",
        #"//cyber_y/cyber_14:install_src",
        "//cyber_y/cyber_15:install_src",
    ]
)
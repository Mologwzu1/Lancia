
load("//tools/install:install.bzl", "install", "install_src_files")

install(
    name = "install",
    data = [
        "cyber_th.BUILD",
        "cyberfile.xml",
    ],
    deps = [
        #"//cyber_th/cyber_12:install",
        "//cyber_th/cyber_16:install",
        "//cyber_th/cyber_42:install",
        "//cyber_th/cyber_52:install"
    ],
)

install_src_files(
    name = "install_src",
    src_dir = ["."],
    dest = "cyber_th/src",
    filter = "*",
    deps = [
        #"//cyber_th/cyber_12:install_src",
        "//cyber_th/cyber_16:install_src",
        "//cyber_th/cyber_42:install_src",
        "//cyber_th/cyber_52:install_src"
    ]
)
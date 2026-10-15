
load("//tools/install:install.bzl", "install", "install_src_files")

install(
    name = "install",
    data = [
        "cyber_b.BUILD",
        "cyberfile.xml",
    ],
    deps = [
        #"//cyber_b/cyber_01:install",
        #"//cyber_b/cyber_02:install",
        #"//cyber_b/cyber_03:install",
        #"//cyber_b/cyber_04:install",
        #"//cyber_b/cyber_05:install",
        "//cyber_b/cyber_11:install",
        "//cyber_b/cyber_41:install",
        "//cyber_b/cyber_51:install"
    ],
)

install_src_files(
    name = "install_src",
    src_dir = ["."],
    dest = "cyber_b/src",
    filter = "*",
    deps = [
        #"//cyber_b/cyber_01:install_src",
        #"//cyber_b/cyber_02:install_src",
        #"//cyber_b/cyber_03:install_src",
        #"//cyber_b/cyber_04:install_src",
        #"//cyber_b/cyber_05:install_src",
        "//cyber_b/cyber_11:install_src",
        "//cyber_b/cyber_41:install_src",
        "//cyber_b/cyber_51:install_src"
    ]
)
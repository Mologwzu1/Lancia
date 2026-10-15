
load("//tools/install:install.bzl", "install", "install_src_files")

install(
    name = "install",
    data = [
        "cyber_g.BUILD",
        "cyberfile.xml",
    ],
    deps = [
        "//cyber_g/cyber_11:install",
        #"//cyber_g/cyber_41:install",
        #"//cyber_g/cyber_51:install",
        "//cyber_g/cyber_12:install",
        "//cyber_g/cyber_42:install",
        #"//cyber_g/cyber_52:install"
    ],
)

install_src_files(
    name = "install_src",
    src_dir = ["."],
    dest = "cyber_g/src",
    filter = "*",
    deps = [
        "//cyber_g/cyber_11:install_src",
        #"//cyber_g/cyber_41:install_src",
        #"//cyber_g/cyber_51:install_src",
        "//cyber_g/cyber_12:install_src",
        "//cyber_g/cyber_42:install_src",
        #"//cyber_g/cyber_52:install_src"
    ]
)
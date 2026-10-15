
load("//tools/install:install.bzl", "install", "install_src_files")

install(
    name = "install",
    data = [
        "cyber_demo.BUILD",
        "cyberfile.xml",
    ],
    deps = [
        "//cyber_demo/cyber_01/demo_main:install",
        "//cyber_demo/cyber_02/demo_main:install",
        "//cyber_demo/cyber_03/proto_main:install",
        "//cyber_demo/cyber_04/communication:install",
        "//cyber_demo/cyber_05/component:install",
        "//cyber_demo/cyber_05/timer_component:install",
        
    ],
)

install_src_files(
    name = "install_src",
    src_dir = ["."],
    dest = "cyber_demo/src",
    filter = "*",
    deps = [
        "//cyber_demo/cyber_01/demo_main:install_src",
        "//cyber_demo/cyber_02/demo_main:install_src",
        "//cyber_demo/cyber_03/proto_main:install_src",
        "//cyber_demo/cyber_04/communication:install_src",
        "//cyber_demo/cyber_05/component:install_src",
        "//cyber_demo/cyber_05/timer_component:install_src",
    ]
)
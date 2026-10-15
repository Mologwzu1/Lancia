实验教材：[第二章：Cyber RT通信机制解析与实践_Apollo开发者社区](https://apollo.baidu.com/community/article/1094)

实验环境：Delta

实验内容及操作步骤：

**一、数据通信基础Protobuf**

1)  创建本节实验工程目录

    ![](03Alpha_Trion_assets/media/image1.png)

2)  编写proto文件及BUILD文件

    ![](03Alpha_Trion_assets/media/image2.png)![](03Alpha_Trion_assets/media/image3.png)

3)  编写主代码及BUILD文件

    ![](03Alpha_Trion_assets/media/image4.png)![](03Alpha_Trion_assets/media/image5.png)

4)  编译代码目录

``` bash
buildtool build -p cyber_demo
```

![](03Alpha_Trion_assets/media/image6.png)

5)  运行可执行文件

``` bash
cd /apollo_workspace/bazel-bin/cyber_demo/cyber_03/proto_main;./main03
```

![](03Alpha_Trion_assets/media/image7.png)

**二、Cyber RT通信机制解析与实践**

1)  创建本节实验工程目录

    ![](03Alpha_Trion_assets/media/image8.png)

2)  proto文件编写

    ![](03Alpha_Trion_assets/media/image9.png)![](03Alpha_Trion_assets/media/image10.png)

3)  talker.cc 文件编写

    ![](03Alpha_Trion_assets/media/image11.png)

4)  listener.cc 文件编写

    ![](03Alpha_Trion_assets/media/image12.png)

5)  bazel 编译文件编写

    ![](03Alpha_Trion_assets/media/image13.png)![](03Alpha_Trion_assets/media/image14.png)

6)  编译

``` bash
buildtool build -p cyber_demo
```

![](03Alpha_Trion_assets/media/image6.png)

``` bash
export GLOG_alsologtostderr=1
```

7)  运行案例

``` bash
./bazel-bin/cyber_demo/cyber_04/communication/talker
```

![](03Alpha_Trion_assets/media/image15.png)

``` bash
./bazel-bin/cyber_demo/cyber_04/communication/listener
```

![](03Alpha_Trion_assets/media/image16.png)

**三、实现小车详细信息的获取——Server-Client通信**

1)  server.cc 文件编写

    ![](03Alpha_Trion_assets/media/image17.png)

2)  client.cc 文件编写

![](03Alpha_Trion_assets/media/image18.png)

3)  编译

``` bash
buildtool build -p cyber_demo
```

![](03Alpha_Trion_assets/media/image6.png)

``` bash
export GLOG_alsologtostderr=1
```

4)  运行案例

``` bash
./bazel-bin/cyber_demo/cyber_04/communication/server
```

![](03Alpha_Trion_assets/media/image19.png)

``` bash
./bazel-bin/cyber_demo/cyber_04/communication/client
```

![](03Alpha_Trion_assets/media/image20.png)

**四、 实现小车通用参数的设置——Parameter Server-Client**

1)  param_server.cc 文件编写

    ![](03Alpha_Trion_assets/media/image21.png)

2)  param_client.cc 文件编写

![](03Alpha_Trion_assets/media/image22.png)

3)  编译

``` bash
buildtool build -p cyber_demo
```

![](03Alpha_Trion_assets/media/image6.png)

``` bash
export GLOG_alsologtostderr=1
```

4)  运行案例

``` bash
./bazel-bin/cyber_demo/cyber_04/communication/param_server
```

![](03Alpha_Trion_assets/media/image23.png)

``` bash
./bazel-bin/cyber_demo/cyber_04/communication/param_client
```

![](03Alpha_Trion_assets/media/image24.png)

**五、录制Talker-Listener通信**

``` bash
cyber_recorder record -c talker_listener
```

![](03Alpha_Trion_assets/media/image25.png)

实

验成绩

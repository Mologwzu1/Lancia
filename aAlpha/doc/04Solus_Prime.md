实验教材：[第三章：Component组件认知与实践_Apollo开发者社区](https://apollo.baidu.com/community/article/1103)

实验环境：Delta

实验内容及操作步骤：

**一、Component 案例**

1)  创建目录结构

    ![](04Solus_Prime_assets/media/image1.png)

2)  定义消息格式

    ![](04Solus_Prime_assets/media/image2.png)![](04Solus_Prime_assets/media/image3.png)

3)  writer 的实现

    ![](04Solus_Prime_assets/media/image4.png)![](04Solus_Prime_assets/media/image5.png)

4)  Component 的实现

    ![](04Solus_Prime_assets/media/image6.png)![](04Solus_Prime_assets/media/image7.png)

5)  配置文件

    ![](04Solus_Prime_assets/media/image8.png)![](04Solus_Prime_assets/media/image9.png)

6)  编译文件

![](04Solus_Prime_assets/media/image10.png)![](04Solus_Prime_assets/media/image11.png)

``` bash
buildtool build -p cyber_demo/
```

![](04Solus_Prime_assets/media/image12.png)

7)  运行

``` bash
./bazel-bin/cyber_demo/cyber_05/component/driver_writer
```

![](04Solus_Prime_assets/media/image13.png)

``` bash
./bazel-bin/cyber_demo/cyber_05/component/chatter_writer
```

![](04Solus_Prime_assets/media/image14.png)

``` bash
export GLOG_alsologtostderr=1;cyber_launch start cyber_demo/cyber_05/component/common.launch
```

![](04Solus_Prime_assets/media/image15.png)

**二、TimerComponent 案例**

1)  创建目录

    ![](04Solus_Prime_assets/media/image16.png)

2)  TimerComponent 实现

    ![](04Solus_Prime_assets/media/image17.png)![](04Solus_Prime_assets/media/image18.png)![](04Solus_Prime_assets/media/image19.png)![](04Solus_Prime_assets/media/image20.png)

3)  配置文件

    ![](04Solus_Prime_assets/media/image21.png)![](04Solus_Prime_assets/media/image22.png)![](04Solus_Prime_assets/media/image23.png)![](04Solus_Prime_assets/media/image24.png)

4)  编译文件

![](04Solus_Prime_assets/media/image25.png)![](04Solus_Prime_assets/media/image26.png)![](04Solus_Prime_assets/media/image27.png)

``` bash
buildtool build -p cyber_demo/
```

![](04Solus_Prime_assets/media/image12.png)

5)  运行

``` bash
cyber_launch start cyber_demo/cyber_05/component/common.launch
```

![](04Solus_Prime_assets/media/image15.png)

``` bash
cyber_launch start cyber_demo/cyber_05/timer_component/driver.launch
```

![](04Solus_Prime_assets/media/image28.png)

``` bash
cyber_launch start cyber_demo/cyber_05/timer_component/chatter.launch
```

![](04Solus_Prime_assets/media/image29.png)

实

验成绩

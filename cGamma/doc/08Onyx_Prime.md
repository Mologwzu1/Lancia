实验教材：Gamma

实验环境：Zeta

![](08Onyx_Prime_assets/media/image1.png)![](08Onyx_Prime_assets/media/image2.png)

实验内容及操作步骤：

**一、指标体系定义**

1)  端到端时延

![](08Onyx_Prime_assets/media/image3.png)![](08Onyx_Prime_assets/media/image4.png)

2)  编译

![](08Onyx_Prime_assets/media/image5.png)

**二、指标体系应用**

1)  自主选择channel监听

``` bash
./bazel-bin/cyber_g/cyber_12/broadcast
./bazel-bin/cyber_g/cyber_12/audience
./bazel-bin/cyber_g/cyber_12/midware broadcast_audience
```

![](08Onyx_Prime_assets/media/image6.png)

2)  通信监测数据解耦合

``` bash
cyber_launch start cyber_g/cyber_42/reader.launch
cyber_launch start cyber_g/cyber_52/dritter_reader.launch
cyber_launch start cyber_g/cyber_52/dritter_writer.launch
```

![](08Onyx_Prime_assets/media/image7.png)

实

验成绩

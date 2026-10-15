实验教材：Beta

实验环境：Delta

实验内容及操作步骤：

**一、指标定义**

1)  端到端时延

![](06Alchemist_Prime_assets/media/image1.png)![](06Alchemist_Prime_assets/media/image2.png)

2)  周期抖动

    ![](06Alchemist_Prime_assets/media/image3.png)![](06Alchemist_Prime_assets/media/image4.png)

3)  编译

![](06Alchemist_Prime_assets/media/image5.png)

**二、指标应用**

1)  端到端时延

``` bash
./bazel-bin/cyber_b/cyber_11/talker
```

./bazel-bin/cyber_b/cyber_11/listener![](06Alchemist_Prime_assets/media/image6.png)

2)  端到端时延+周期抖动

``` bash
cyber_launch start cyber_b/cyber_41/common.launch
./bazel-bin/cyber_b/cyber_41/driver_writer
```

![](06Alchemist_Prime_assets/media/image7.png)

``` bash
cyber_launch start cyber_b/cyber_41/common.launch
cyber_launch start cyber_b/cyber_51/driver.launch
```

![](06Alchemist_Prime_assets/media/image8.png)

实

验成绩

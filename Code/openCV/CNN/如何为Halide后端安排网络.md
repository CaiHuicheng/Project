# 如何为Halide后端安排网络

## 介绍

Halide代码对于我们使用的每个设备都是一样的。但是为了达到满意的效率，我们应该正确地安排计算。在本教程中，我们将介绍如何使用OpenCV深度学习模块中的Halide后端来安排网络。

为了更好地了解Halide计划，您可能需要阅读教程@ http://halide-lang.org/tutorials。

如果这是您在OpenCV中与Halide的第一次学习，我们建议从[如何启用Halide后端以提高效率](https://www.w3cschool.cn/opencv/opencv-5q4e2elb.html)。

## 配置文件

您可以通过编写文本配置文件来计划Halide管道的计算。这意味着您可以轻松地矢量化，并行和管理层计算的循环顺序。[cv::dnn::Net::setHalideScheduler](http://halide-lang.org/tutorials)在第一次[cv::dnn::Net::forward](https://docs.opencv.org/master/db/d30/classcv_1_1dnn_1_1Net.html#a98ed94cb6ef7063d3697259566da310b)调用之前，将特定设备的调度指令传递到文件路径。

调度表示为YAML文件的配置文件，其中每个节点是计划功能或调度指令。

```
relu1:
  reorder: [x, c, y]
  split: { y: 2, c: 8 }
  parallel: [yo, co]
  unroll: yi
  vectorize: { x: 4 }
conv1_constant_exterior:
  compute_at: { relu1: yi }
```

考虑使用n批量维度，c渠道，y行和x列的变量。对于变量分裂后都具有相同前缀使用的名称，但o和i后缀对应的外部和内部的变量。例如，对于变量x范围[0, 10)指令split: { x: 2 }，xo在范围[0, 5)和xi范围内给出了新的范围指令[0, 2)。变量名称x在同一调度节点中不再可用。

您可以在[opencv_extra / testdata / dnn上](https://github.com/opencv/opencv_extra/tree/master/testdata/dnn)找到调度示例，并使用它来安排您的网络。

## 图层融合

由于图层融合，我们只能安排融合集顶层。因为对于每个输出值，我们使用融合公式。例如，如果您有三层卷积+ Scale + ReLU一个一个。

```
conv(x, y, c, n) = sum(...) + bias(c);
scale(x, y, c, n) = conv(x, y, c, n) * weights(c);
relu(x, y, c, n) = max(scale(x, y, c, n), 0);
```

融合功能就是这样

```
relu(x, y, c, n) = max((sum(...) + bias(c)) * weights(c), 0);
```

所以只有函数调用relu需要调度。

## 计划模式

有时，使用阻塞结构构建的网络意味着某些层是相同或非常相似的。如果要对不同的层应用相同的调度，精确到平铺或矢量化因子，请在patterns调度文件开头部分中定义调度模式。此外，您的模式可能会使用一些参数变量。

```
# At the beginning of the file
patterns:
  fully_connected:
    split: { c: c_split }
    fuse: { src: [x, y, co], dst: block }
    parallel: block
    vectorize: { ci: c_split }
# Somewhere below
fc8:
  pattern: fully_connected
  params: { c_split: 8 }
```

## 自动调度

您可以让DNN自动安排图层。只是跳过电话[cv::dnn::Net::setHalideScheduler](https://docs.opencv.org/master/db/d30/classcv_1_1dnn_1_1Net.html#a56fbff351d1e0a47fb5aabf6915fc279)。有时它可能比手动调度更有效率。但是，如果需要手动调度特定层次，则可以混合手动和自动调度方式。编写计划文件并跳过要自动计划的图层。
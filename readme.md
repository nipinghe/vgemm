## Vgemm

vgemm是专门针对AMD Vega GPU使用原生机器指令进行了高度优化的矩阵乘法库。

vgemm的开发没有使用任何第三方汇编器，vgemm的GPU内核开发的流程是:

1. OpenCL-Binary Generator:
  
- 将vega isa的每条指令的二进制格式定义成一个函数（或者宏）

- 编制内核函数

- 运行generator生成内核二进制代码（同时重定位内核中分支指令的跳转地址）

2. 将生成的二进制代码嵌入到vgemm项目中生成vgemm库。
    
这里感谢下gcnasm的作者提供的一些关于[AMDGPU-OpenCL-ABI](http://openwall.info/wiki/john/development/GCN-ISA)的一些信息：, 虽然细节仍需要自己探究，但却指明了大概的方向。

目前公布的版本中最优性能指标如下（开发和测试平台为Win10-64B,Vega64，OpenCL版本同AMD APP-3.0中的版本）：

|类型|性能|
|:---:|:---:|
|单精度|96.5~97% TPP (Theory Peak Performance)|
|混合精度（16bit存储，单精度计算）|97% TPP|
|半精度|95% TPP|

## 注意：
    
1. 混合精度和半精度模式，每相邻的两行（行主序）或两列（列主序）是packed成一行或一列的，否则半精度可以达到97%的TPP, 之所以牺牲一点性能这样做是为了和后续更有效的支持卷积操作的数据格式相互兼容。

2. vgemm_get_optimal_leading_size最好只应用于当B矩阵为列主序时且仅用于B矩阵，未来可能会移除此功能。

## 声明：

*本项目仅限于供兴趣爱好者研究用，不可在未经本人同意的情况下用于其它用途。*

作者：李修宇

联系方式:
    
QQ: 295553381

微信：13710058492
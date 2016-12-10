##Zebra: light-weight Monte Carlo Path Tracer
[English Version of README](./README.en.md)

###Zebra是一个轻量级的蒙特卡洛路径追踪器，它来源于 [Giraffe](https://www.github.com/UncP/Giraffe)

***

###目标
* 以更准确优雅的方式实现 [Giraffe](https://www.github.com/UncP/Giraffe) 的部分功能
* 对高级图形学内容进行尝试
* 进行必要的调整来配合 [Bunny](https://www.github.com/UncP/Bunny) 进行图形学与机器学习相结合的实践

###如果你感兴趣
`g++ -std=c++11 -fopenmp swan.cpp -o Zebra`  
`./Zebra 4 (4代表采样数,可以为任意大于0的值)`
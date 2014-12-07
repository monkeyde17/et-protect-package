xxhash的使用说明
================

在改插件中的`hash`命令是由`./plugin_xxhash/xxhash/`中代码编译而来。

具体可以见[main.cpp](./plugin_xxhash/xxhash/main.cpp)代码

## 编译

```bash
make && make install
```

### 使用

```bash
./hash -f [哈希文件路径] -s [种子:默认为0x12345678] -t [文件生成路径:默认为当前目录]
```

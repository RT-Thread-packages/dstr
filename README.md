# dstr

## 1、介绍
这是一个在 RT-Thread 上，基于 ANSI/ISO C89 实现的动态字符串软件包。

### 1.1 目录结构

| 名称 | 说明 |
| ---- | ---- |
| inc  | 头文件目录 |
| src  | 源代码目录 |
| examples | 例程目录 |

### 1.2 许可证

dstr package 遵循 LGPLv2.1 许可，详见 `LICENSE` 文件。

### 1.3 依赖

- 对 RT-Thread 无依赖，也可用于裸机。

### 1.4 版本日志
- v0.2.0
  - 增在从前面拼接字符串相关API
  - 增加从前面拼接动态字符串相关API
  - 增加从后面拼接动态字符串相关API
  - 改善用户体验
  - 修复已知 bug
- v0.1.0
  - 动态字符串软件包第一版

## 2、如何打开 dstr

使用 dstr package 需要在 RT-Thread 的包管理器中选择它，详情如下：

```
RT-Thread online packages --->
    miscellaneous packages --->
        [*] dstr: a dynamic string package
        	Version (v0.2.0) --->
        	dstr Options --->
        		[*] dstr test example
```

保存 menuconfig 配置后使用 `pkgs --update` 命令下载软件包

## 3、使用 dstr

使用 dstr 可参考例子代码，该代码位于：[/dstr/examples/examples_dstr.c](dstr/examples/examples_dstr.c)

### 3.1 创建动态字符串对象
`rt_dstr_t *rt_dstr_new(const char *str);`

| 参数 | 描述 |
| ---- | ---- |
| name  | 源字符串 |
| 返回 | 描述 |
| thiz | 动态字符串创建成功 |
| NULL | 动态字符串创建失败 |
> 可以传入 NULL，使用详情可以查看 `examples_dstr.c`

### 3.2 删除动态字符串对象
`void rt_dstr_del(rt_dstr_t *thiz);`

| 参数 | 描述 |
| ---- | ---- |
| thiz  | 动态字符串对象 |
| 返回 | 描述 |
| 无 | 无 |


### 3.3 字符串后拼接
`rt_dstr_t *rt_dstr_cat(rt_dstr_t *thiz, const char *src);`

| 参数 | 描述 |
| ---- | ---- |
| thiz  | 动态字符串对象 |
| src  | 源字符串 |
| 返回 | 描述 |
| thiz | 字符串拼接 dstr 成功 |
| NULL | 字符串拼接 dstr 失败，但不会更改 thiz，交由用户处理 |


### 3.4 字符串后拼接（拼接 n 个字符）
`rt_dstr_t *rt_dstr_ncat(rt_dstr_t *thiz, const char *src, size_t n);`

| 参数 | 描述 |
| ---- | ---- |
| thiz  | 动态字符串对象 |
| src  | 源字符串 |
| n  | 需要拼接几个字符 |
| 返回 | 描述 |
| thiz | 字符串拼接 dstr 成功 |
| null | 字符串拼接 dstr 失败，但不会更改 thiz，交由用户处理 |

### 3.5 字符串前拼接
`rt_dstr_t *rt_dstr_precat(rt_dstr_t *thiz, const char *src);`

| 参数 | 描述 |
| ---- | ---- |
| thiz  | 动态字符串对象 |
| src  | 源字符串 |
| 返回 | 描述 |
| thiz | 字符串拼接 dstr 成功 |
| null | 字符串拼接 dstr 失败，但不会更改 thiz，交由用户处理 |


### 3.6 字符串前拼接（拼接 n 个字符）
`rt_dstr_t *rt_dstr_prencat(rt_dstr_t *thiz, const char *src, size_t n);`

| 参数 | 描述 |
| ---- | ---- |
| thiz  | 动态字符串对象 |
| src  | 源字符串 |
| n  | 需要拼接几个字符 |
| 返回 | 描述 |
| thiz | 字符串拼接 dstr 成功 |
| NULL | 字符串拼接 dstr 失败，但不会更改 thiz，交由用户处理 |


### 3.7 动态字符串后拼接
`rt_dstr_t *rt_dstr_cat_dstr(rt_dstr_t *dst, rt_dstr_t *src);`

| 参数 | 描述 |
| ---- | ---- |
| dst  | 动态字符串对象 |
| src  | 源字符串 |
| 返回 | 描述 |
| dst | 动态字符串拼接 dst 成功，但不会更改 src，交由用户处理 |
| NULL | 动态字符串拼接 dst 失败，但不会更改 dst & src，交由用户处理 |


### 3.8 动态字符串后拼接（拼接 n 个字符）
`rt_dstr_t *rt_dstr_ncat_dstr(rt_dstr_t *dst, rt_dstr_t *src, size_t n);`

| 参数 | 描述 |
| ---- | ---- |
| dst  | 动态字符串对象 |
| src  | 源字符串 |
| n  | 需要拼接几个字符 |
| 返回 | 描述 |
| dst | 动态字符串拼接 dst 成功，但不会更改 src，交由用户处理 |
| NULL | 动态字符串拼接 dst 失败，但不会更改 dst & src，交由用户处理 |

### 3.9 动态字符串前拼接
`rt_dstr_t *rt_dstr_precat_dstr(rt_dstr_t *dst, rt_dstr_t *src);`

| 参数 | 描述 |
| ---- | ---- |
| dst  | 动态字符串对象 |
| src  | 源字符串 |
| 返回 | 描述 |
| dst | 动态字符串拼接 dst 成功，但不会更改 src，交由用户处理 |
| NULL | 动态字符串拼接 dst 失败，但不会更改 dst & src，交由用户处理 |


### 3.10 动态字符串前拼接（拼接几个字符）
`rt_dstr_t *rt_dstr_prencat_dstr(rt_dstr_t *dst, rt_dstr_t *src, size_t n);`

| 参数 | 描述 |
| ---- | ---- |
| dst  | 动态字符串对象 |
| src  | 源字符串 |
| n  | 需要拼接几个字符 |
| 返回 | 描述 |
| thiz | 字符串拼接 dstr 成功 |
| NULL | 字符串拼接 dstr 失败，但不会更改 thiz，交由用户处理 |


### 3.11 动态字符串比较
`int rt_dstr_cmp(rt_dstr_t *const dstr1, rt_dstr_t *const dstr2);`

| 参数 | 描述 |
| ---- | ---- |
| dstr1  | 动态字符串1 |
| dstr2  | 动态字符串2 |
| 返回 | 描述 |
| 负数 | dstr1 < dstr2 |
| 返回0 | dstr1 = dstr2 |
| 正数 | dstr1 > dstr2 |


### 3.12 动态字符串比较（比较 n 个字符）
`int rt_dstr_ncmp(rt_dstr_t *const dstr1, rt_dstr_t *const dstr2, size_t n);`

| 参数 | 描述 |
| ---- | ---- |
| dstr1  | 动态字符串1 |
| dstr2  | 动态字符串2 |
| n  | 需要比较几个字符 |
| 返回 | 描述 |
| 负数 | dstr1 < dstr2 |
| 返回0 | dstr1 = dstr2 |
| 正数 | dstr1 > dstr2 |

### 3.13 动态字符串比较（忽略大小写）
`int rt_dstr_casecmp(rt_dstr_t *const dstr1, rt_dstr_t *const dstr2);`

| 参数 | 描述 |
| ---- | ---- |
| dstr1  | 动态字符串1 |
| dstr2  | 动态字符串2 |
| 返回 | 描述 |
| 负数 | dstr1 < dstr2 |
| 返回0 | dstr1 = dstr2 |
| 正数 | dstr1 > dstr2 |

### 3.14 测量动态字符串长度
`int rt_dstr_strlen(rt_dstr_t *const thiz);`

| 参数 | 描述 |
| ---- | ---- |
| thiz  | 动态字符串对象 |
| 返回 | 描述 |
| 正数 | 返回动态字符串长度 |
| 返回0 | 返回动态字符串长度 |
| -1 | 输入参数为 NULL 是非法的 |


### 3.15 字符串格式化输出
`rt_dstr_t *rt_dstr_sprintf(rt_dstr_t *thiz, const char *fmt, ...);`

| 参数 | 描述 |
| ---- | ---- |
| thiz  | 动态字符串对象 |
| fmt  | 格式化字符串 |
| argument...  | 可选参数，任何类型的数据 |
| 返回 | 描述 |
| thiz | 字符串格式化成功 |
| NULL | 字符串格式化失败，但不会更改 thiz，交由用户处理 |

### 3.16 字符串格式化输出（以追加的方式）

`rt_dstr_t *rt_dstr_append_printf(rt_dstr_t *thiz, const char *format, ...);`

| 参数 | 描述           |
| ---- | -------------- |
| thiz | 动态字符串对象 |
|fmt|格式化字符串|
| argument...  | 可选参数，任何类型的数据 |
| 返回 | 描述 |
| thiz | 字符串格式化成功 |
| NULL | 字符串格式化失败，但不会更改 thiz，交由用户处理 |


## 4、注意事项

暂无

## 5、联系方式

* 维护：[never](https://github.com/neverxie)
* 主页：https://github.com/RT-Thread-packages/dstr

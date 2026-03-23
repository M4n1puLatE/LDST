# 更新信息
- ## 2026年2月26日
> - 添加理论基础部分
> - 添加草案部分


# PrimedDB技术文档
## 项目简介
- 本项目为*廖润康*的毕业设计，题目为`《基于质数哈希键和质因数分解查询的关系型数据库》`（<a href="./thesis.pdf" target="_blank" download>下载论文英文原文</a>）。设计目的是为了将所有类型的**查询理论时间复杂度统一为**$O(1)$。
- 全新跨平台版本基于Cmake构建，从而适配不同的系统环境。

### 项目地址
- #### [**跨平台重构版本仓库**](https://github.com/M4n1puLatE/PrimedDB)
- #### [旧版论文实现版本仓库](https://github.com/Jeffrey-Liao/PrimedDB)

### 时间线
- 项目开发**开始时间**：2025年8月
- 项目**可行性验证**通过：2025年9月
	- 基于*暴力穷举*和*质数估算公式*两种方式同时证明了将原数据映射到扩大后的键区域可以建立满射关系。
- **第一版**成品发布时间：2025年11月
	- 第一版为demo版本，仅支持Windows平台
	- 存在部分会导致数据库程序意外退出的Bug，所有Bug原因已知，并将在跨平台版本重构。
- 期末考试及毕业答辩：2025年12月-1月10日
- **跨平台版本重构**开始时间：2025年1月13日
	- 计划同时提供Windows和Linux端，并对旧实现中存在的问题进行重构


### 项目优势
- 且所有数据**入库即加密**，设计出的哈希函数可以基于一个密码值进行放大，从而实现数据入库自加密。
- 因为**解密函数仅为一个除法运算**，所以解密效率极高。
- 在**查询时不需要进行解密即可运算**，质数哈希键仍然保留了原有数据的排序信息。
- 区别于传统数据库需要对每个列建立位向量，再对其进行与运算筛选数据。PrimedDB可以直接**在记录层面创建单个位向量并实现多条件查找**。
- 所有**查询操作都被转化为一个取模运算**，`0`即为给定条件的数据存在于当前记录，`1`则为当前记录不存在需要的数据。
- 详见[理论基础](CN/doc/theorems).

### 项目劣势
- 由于存储时直接存储哈希键形式，所以需要额外的存储空间
- 由于每个记录都需要存储一个用于查询的记录键，因此需要额外的存储空间
- 插入操作为一个$O(n)$级别的操作，但预期可以优化为$log(n)$

### 应用场景
- 效率敏感但存储限制不严格的场景
- 高安全需求场景

---
## 文档目录
### 文档更新
- [更新记录](Updates.md)

### 文档格式与基础理论
- [代码规范与文档格式](CN/explain/Rules.md)
- [理论基础](CN/doc/theorems.md)
- [草案内容](CN/doc/draft.md)


### 功能文档
- ### [Tester空间](CN/doc/Tester/TesterPack.md)
	- [Tester](CN/doc/Tester/Tester.md)：单元测试类型
- ### [Util空间](CN/doc/Util/UtilPack.md)
	- [DepreciatedManager](CN/doc/Util/DepreciatedManager.md)：~~管理者类型基类~~(已弃用)
	- [Manager](CN/doc/Util/Manager.md)：基于上下文切换的管理者类型基类
	- [TimeStamp](CN/doc/Util/TimeStamp.md)：时间戳类型
	- [Timer](CN/doc/Util/Timer.md)：计时器
	- [TimerPlus](CN/doc/Util/TimerPlus.md)：带有暂停功能的计时器
	- [Singleton](CN/doc/Util/Singleton.md)：单例类基类
	- [SFO](CN/doc/Util/SFO.md)：系统级文件操作类型
	- [Util](CN/doc/Util/Util.md)：通用工具函数
- ### [LogLib空间](CN/doc/LogLib/LogLib.md)
	- [Log](CN/doc/LogLib/Log.md)：日志输出类型
	- [LogType](CN/doc/LogLib/LogType.md)：日志类型
	- [LogManager](CN/doc/LogLib/LogManager.md)：日志管理者类型
- ### [Compiler空间](CN/doc/Compiler/CompilerPack.md)
	- [Lexer](CN/doc/Compiler/CompilerPack.md)：词法分析器
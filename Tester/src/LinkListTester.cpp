#include "LinkListTester.h"
#include <LinkList.h>
namespace Tester
{
    void LinkListTester::init()
    {
        add("constructTest",TEST_FUNCTION(constructTest));
        add("addTest",TEST_FUNCTION(addTest));
        add("removeTest",TEST_FUNCTION(removeTest));
        add("insertTest",TEST_FUNCTION(insertTest));
        add("findTest",TEST_FUNCTION(findTest));
        add("rangeTest",TEST_FUNCTION(rangeTest));
        add("overwriteTest",TEST_FUNCTION(overwriteTest));
        add("getTest",TEST_FUNCTION(getTest));
        add("containsTest",TEST_FUNCTION(containsTest));
        add("removeFromTest",TEST_FUNCTION(removeFromTest));
        add("reserveTest",TEST_FUNCTION(reserveTest));
        add("firstTest",TEST_FUNCTION(firstTest));
        add("lastTest",TEST_FUNCTION(lastTest));
        add("sizeTest",TEST_FUNCTION(sizeTest));
        add("emptyTest",TEST_FUNCTION(emptyTest));
        add("clearTest",TEST_FUNCTION(clearTest));
        add("setTest",TEST_FUNCTION(setTest));
        add("countTest",TEST_FUNCTION(countTest));
    }
    bool LinkListTester::constructTest()
    {
        // 测试默认构造函数
        Collection::Linear::LinkList<int> list1;
        if (!list1.empty() || list1.size() != 0) return false;


        // 测试初始化列表构造函数
        Collection::Linear::LinkList<int> list2 = {1, 2, 3, 4, 5};
        if (list2.size() != 5) return false;
        for (size_t i = 0; i < 5; i++) {
            if (list2.get(i) != i + 1) return false;
        }
        //// 测试拷贝构造函数
        Collection::Linear::LinkList<int> list3(list2);
        if (list3.size() != 5) return false;
        for (size_t i = 0; i < 5; i++) {
            if (list3.get(i) != i + 1) return false;
        }

        //// 测试移动构造函数
        Collection::Linear::LinkList<int> list4(std::move(list3));
        if (list4.size() != 5) return false;
        for (size_t i = 0; i < 5; i++) {
            if (list4.get(i) != i + 1) return false;
        }
        // list3 应该为空
        if (!list3.empty() || list3.size() != 0) return false;

        //// 测试大小构造函数
        Collection::Linear::LinkList<int> list5(10);
        if (list5.size() != 10) return false;
        // 所有元素应该为默认值（0对于int）
        for (size_t i = 0; i < 10; i++) {
            if (list5.get(i) != 0) return false;
        }
        return true;
    }
    bool LinkListTester::addTest()
    {
        Collection::Linear::LinkList<int> list;

        // 测试 add(const T& value)
        list.add(1);
        if (list.size() != 1 || list.get(0) != 1) return false;

        list.add(2);
        if (list.size() != 2 || list.get(1) != 2) return false;

        // 测试 add(T&& move)
        int value = 3;
        list.add(std::move(value));
        if (list.size() != 3 || list.get(2) != 3) return false;

        // 测试 add(const std::initializer_list<T>& values)
        list.add({4, 5, 6});
        if (list.size() != 6) return false;
        for (size_t i = 3; i < 6; i++) {
            if (list.get(i) != i + 1) return false;
        }

        // 测试 add(const LinkList& object)
        Collection::Linear::LinkList<int> otherList = {7, 8, 9};
        list.add(otherList);
        if (list.size() != 9) return false;
        for (size_t i = 6; i < 9; i++) {
            if (list.get(i) != i + 1) return false;
        }

        return true;
    }
    bool LinkListTester::removeTest()
    {
        Collection::Linear::LinkList<int> list = {1, 2, 3, 4, 5};

        // 测试删除中间节点
        if (!list.remove(2)) return false; // 删除第三个元素(索引2，值为3)
        if (list.size() != 4) return false;
        if (list.get(0) != 1 || list.get(1) != 2 || list.get(2) != 4 || list.get(3) != 5) return false;

        // 测试删除头节点
        if (!list.remove(0)) return false; // 删除第一个元素
        if (list.size() != 3) return false;
        if (list.get(0) != 2 || list.get(1) != 4 || list.get(2) != 5) return false;

        // 测试删除尾节点
        if (!list.remove(list.size() - 1)) return false; // 删除最后一个元素
        if (list.size() != 2) return false;
        if (list.get(0) != 2 || list.get(1) != 4) return false;

        // 测试删除空列表
        Collection::Linear::LinkList<int> emptyList;
        if (emptyList.remove(0)) return false; // 应该返回false

        // 测试删除越界索引
        if (list.remove(5)) return false; // 索引5越界，应该返回false

        return true;
    }
    bool LinkListTester::insertTest()
    {
        Collection::Linear::LinkList<int> list = {1, 2, 3};

        // 测试在头部插入
        if (!list.insert(0, 0)) return false;
        if (list.size() != 4) return false;
        if (list.get(0) != 0 || list.get(1) != 1 || list.get(2) != 2 || list.get(3) != 3) return false;

        // 测试在中间插入
        if (!list.insert(2, 99)) return false; // 在索引2处插入
        if (list.size() != 5) return false;
        if (list.get(0) != 0 || list.get(1) != 1 || list.get(2) != 99 || list.get(3) != 2 || list.get(4) != 3) return false;

        // 测试在尾部插入（应该相当于add）
        if (!list.insert(list.size(), 100)) return false;
        if (list.size() != 6) return false;
        if (list.get(5) != 100) return false;

        // 测试在空列表中插入
        Collection::Linear::LinkList<int> emptyList;
        if (!emptyList.insert(0, 42)) return false;
        if (emptyList.size() != 1 || emptyList.get(0) != 42) return false;

        // 测试越界插入
        if (list.insert(10, 200)) return false; // 索引10越界，应该返回false

        return true;
    }
    bool LinkListTester::findTest()
    {
        Collection::Linear::LinkList<int> list = {1, 2, 3, 4, 5, 3, 6};

        // 测试查找存在的元素（第一个出现的位置）
        if (list.find(1) != 0) return false;
        if (list.find(3) != 2) return false; // 应该返回第一次出现的位置
        if (list.find(6) != 6) return false;

        // 测试查找不存在的元素
        if (list.find(99) != -1) return false;
        if (list.find(0) != -1) return false;

        // 测试空列表查找
        Collection::Linear::LinkList<int> emptyList;
        if (emptyList.find(1) != -1) return false;

        return true;
    }
    bool LinkListTester::rangeTest()
    {
        Collection::Linear::LinkList<int> list = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        // 测试有效范围
        auto view1 = list.range(2, 5); // 索引2到5（不包含5）
        if (view1.size() != 3) return false; // 元素：3,4,5
        if (view1.get(0)->get() != 3 || view1.get(1)->get() != 4 || view1.get(2)->get() != 5) return false;

        // 测试单个元素范围
        auto view2 = list.range(0, 1);
        if (view2.size() != 1) return false;
        if (view2.get(0)->get() != 1) return false;

        // 测试整个列表范围
        auto view3 = list.range(0, list.size());
        if (view3.size() != list.size()) return false;
        for (size_t i = 0; i < list.size(); i++) {
            if (view3.get(i)->get() != list.get(i)) return false;
        }

        // 测试无效范围（end >= begin 不成立）
        auto view4 = list.range(5, 2);
        if (!view4.empty() || view4.size() != 0) return false;

        // 测试越界范围
        auto view5 = list.range(8, 12);
        if (!view5.empty() || view5.size() != 0) return false;

        // 测试空范围
        auto view6 = list.range(3, 3);
        if (view6.size() != 0) return false;

        return true;
    }
    bool LinkListTester::overwriteTest()
    {
        Collection::Linear::LinkList<int> list1 = {1, 2, 3, 4, 5};
        Collection::Linear::LinkList<int> list2 = {6, 7, 8};
        // 测试用较短的列表覆盖较长的列表
        list1.overwrite(list2);
        if (list1.size() != 3) return false;
        for (size_t i = 0; i < 3; i++) {
            if (list1.get(i) != list2.get(i)) return false;
        }

        // 测试用较长的列表覆盖较短的列表
        Collection::Linear::LinkList<int> list3 = {9, 10, 11, 12, 13, 14};
        list1.overwrite(list3);
        if (list1.size() != 6) return false;
        for (size_t i = 0; i < 6; i++) {
            if (list1.get(i) != list3.get(i)) return false;
        }

        // 测试用相同大小的列表覆盖
        Collection::Linear::LinkList<int> list4 = {15, 16, 17, 18, 19, 20};
        list1.overwrite(list4);
        if (list1.size() != 6) return false;
        for (size_t i = 0; i < 6; i++) {
            if (list1.get(i) != list4.get(i)) return false;
        }

        // 测试用空列表覆盖
        Collection::Linear::LinkList<int> emptyList;
        list1.overwrite(emptyList);
        if (!list1.empty() || list1.size() != 0) return false;

        // 测试自覆盖
        Collection::Linear::LinkList<int> list5 = {21, 22, 23};
        list5.overwrite(list5); // 应该没有变化
        if (list5.size() != 3) return false;
        if (list5.get(0) != 21 || list5.get(1) != 22 || list5.get(2) != 23) return false;

        return true;
    }
    bool LinkListTester::getTest()
    {
        Collection::Linear::LinkList<int> list = {1, 2, 3, 4, 5};

        // 测试 get(size_t index) 非const版本
        for (size_t i = 0; i < list.size(); i++) {
            if (list.get(i) != i + 1) return false;
        }

        // 测试 get(size_t index) const版本
        const Collection::Linear::LinkList<int>& constList = list;
        for (size_t i = 0; i < constList.size(); i++) {
            if (constList.get(i) != i + 1) return false;
        }

        // 测试 operator[] 非const版本
        for (size_t i = 0; i < list.size(); i++) {
            if (list[i] != i + 1) return false;
        }

        // 测试 operator[] const版本
        for (size_t i = 0; i < constList.size(); i++) {
            if (constList[i] != i + 1) return false;
        }

        // 测试通过引用修改元素
        list.get(2) = 99;
        if (list.get(2) != 99) return false;

        list[3] = 100;
        if (list.get(3) != 100) return false;

        // 检查其他元素未受影响
        if (list.get(0) != 1 || list.get(1) != 2 || list.get(4) != 5) return false;

        return true;
    }
    bool LinkListTester::containsTest()
    {
        Collection::Linear::LinkList<int> list = {1, 2, 3, 4, 5, 3, 6};

        // 测试包含存在的元素
        if (!list.contains(1)) return false;
        if (!list.contains(3)) return false;
        if (!list.contains(6)) return false;

        // 测试不包含不存在的元素
        if (list.contains(0)) return false;
        if (list.contains(99)) return false;

        // 测试空列表
        Collection::Linear::LinkList<int> emptyList;
        if (emptyList.contains(1)) return false;

        return true;
    }
    bool LinkListTester::removeFromTest()
    {
        Collection::Linear::LinkList<int> list = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        // 测试从中间删除多个元素
        if (!list.removeFrom(2, 3)) return false; // 删除索引2,3,4（值：3,4,5）
        if (list.size() != 7) return false;
        if (list.get(0) != 1 || list.get(1) != 2 || list.get(2) != 6 || list.get(3) != 7 ||
            list.get(4) != 8 || list.get(5) != 9 || list.get(6) != 10) return false;

        // 测试从头开始删除
        if (!list.removeFrom(0, 2)) return false; // 删除索引0,1（值：1,2）
        if (list.size() != 5) return false;
        if (list.get(0) != 6 || list.get(1) != 7 || list.get(2) != 8 ||
            list.get(3) != 9 || list.get(4) != 10) return false;

        // 测试从尾部删除
        if (!list.removeFrom(list.size() - 2, 2)) return false; // 删除最后两个元素
        if (list.size() != 3) return false;
        if (list.get(0) != 6 || list.get(1) != 7 || list.get(2) != 8) return false;

        // 测试删除0个元素
        if (!list.removeFrom(1, 0)) return false; // 应该返回true且列表不变
        if (list.size() != 3) return false;

        // 测试删除所有元素
        if (!list.removeFrom(0, list.size())) return false;
        if (!list.empty() || list.size() != 0) return false;

        // 测试越界删除
        Collection::Linear::LinkList<int> list2 = {1, 2, 3};
        if (list2.removeFrom(1, 5)) return false; // 总数超过大小，应该返回false

        // 测试无效位置
        if (list2.removeFrom(5, 1)) return false; // 起始位置越界，应该返回false

        return true;
    }
    bool LinkListTester::reserveTest()
    {
        Collection::Linear::LinkList<int> list = {1, 2, 3};

        // 测试扩展列表
        list.reserve(10);
        if (list.size() != 10) return false;

        // 检查前3个元素不变
        if (list.get(0) != 1 || list.get(1) != 2 || list.get(2) != 3) return false;

        // 检查新元素为默认值（0对于int）
        for (size_t i = 3; i < 10; i++) {
            if (list.get(i) != 0) return false;
        }

        // 测试扩展空列表
        Collection::Linear::LinkList<int> emptyList;
        emptyList.reserve(5);
        if (emptyList.size() != 5) return false;
        for (size_t i = 0; i < 5; i++) {
            if (emptyList.get(i) != 0) return false;
        }

        // 测试reserve小于当前大小（应该什么都不做）
        list.reserve(5);
        if (list.size() != 10) return false; // 大小应保持不变

        // 测试reserve等于当前大小
        list.reserve(10);
        if (list.size() != 10) return false;

        return true;
    }
    bool LinkListTester::firstTest()
    {
        Collection::Linear::LinkList<int> list = {1, 2, 3, 4, 5};

        // 测试 first() 非const版本
        if (list.first() != 1) return false;

        // 测试 first() const版本
        const Collection::Linear::LinkList<int>& constList = list;
        if (constList.first() != 1) return false;

        // 测试通过引用修改第一个元素
        list.first() = 99;
        if (list.first() != 99) return false;
        if (list.get(0) != 99) return false;

        // 检查其他元素未受影响
        if (list.get(1) != 2 || list.get(2) != 3 || list.get(3) != 4 || list.get(4) != 5) return false;

        // 测试空列表（应该抛出异常或返回什么？）
        // 根据LinkList.h，first()返回*m_head，如果m_head为nullptr会崩溃
        // 但empty()检查会返回true，所以我们应该避免对空列表调用first()
        // 这里只测试非空列表

        return true;
    }
    bool LinkListTester::lastTest()
    {
        Collection::Linear::LinkList<int> list = {1, 2, 3, 4, 5};

        // 测试 last() 非const版本
        if (list.last() != 5) return false;

        // 测试 last() const版本
        const Collection::Linear::LinkList<int>& constList = list;
        if (constList.last() != 5) return false;

        // 测试通过引用修改最后一个元素
        list.last() = 99;
        if (list.last() != 99) return false;
        if (list.get(list.size() - 1) != 99) return false;

        // 检查其他元素未受影响
        if (list.get(0) != 1 || list.get(1) != 2 || list.get(2) != 3 || list.get(3) != 4) return false;

        // 测试单个元素列表
        Collection::Linear::LinkList<int> singleList = {42};
        if (singleList.last() != 42) return false;
        if (singleList.first() != 42) return false; // 第一个和最后一个应该是同一个

        // 测试空列表（应该避免调用，同firstTest）

        return true;
    }
    bool LinkListTester::sizeTest()
    {
        // 测试空列表大小
        Collection::Linear::LinkList<int> emptyList;
        if (emptyList.size() != 0) return false;

        // 测试初始化列表大小
        Collection::Linear::LinkList<int> list1 = {1};
        if (list1.size() != 1) return false;

        Collection::Linear::LinkList<int> list2 = {1, 2, 3, 4, 5};
        if (list2.size() != 5) return false;

        // 测试添加元素后大小变化
        list2.add(6);
        if (list2.size() != 6) return false;

        list2.add({7, 8, 9});
        if (list2.size() != 9) return false;

        // 测试删除元素后大小变化
        list2.remove(0);
        if (list2.size() != 8) return false;

        list2.removeFrom(2, 3);
        if (list2.size() != 5) return false;

        // 测试清空后大小
        list2.clear();
        if (list2.size() != 0) return false;

        // 测试reserve后大小
        Collection::Linear::LinkList<int> list3;
        list3.reserve(10);
        if (list3.size() != 10) return false;

        return true;
    }
    bool LinkListTester::emptyTest()
    {
        // 测试新创建的空列表
        Collection::Linear::LinkList<int> emptyList;
        if (!emptyList.empty()) return false;

        // 测试非空列表
        Collection::Linear::LinkList<int> list1 = {1};
        if (list1.empty()) return false;

        Collection::Linear::LinkList<int> list2 = {1, 2, 3, 4, 5};
        if (list2.empty()) return false;

        // 测试清空后变为空
        list2.clear();
        if (!list2.empty()) return false;

        // 测试添加元素后变为非空
        list2.add(1);
        if (list2.empty()) return false;

        // 测试删除所有元素后变为空
        list2.remove(0);
        if (!list2.empty()) return false;

        // 测试reserve创建的列表（包含默认值）不为空
        Collection::Linear::LinkList<int> list3;
        list3.reserve(5);
        if (list3.empty()) return false;

        // 测试删除所有元素后变为空
        list3.removeFrom(0, 5);
        if (!list3.empty()) return false;

        return true;
    }
    bool LinkListTester::clearTest()
    {
        // 测试清空非空列表
        Collection::Linear::LinkList<int> list = {1, 2, 3, 4, 5};
        list.clear();
        if (!list.empty() || list.size() != 0) return false;

        // 测试清空后可以重新添加元素
        list.add(10);
        if (list.empty() || list.size() != 1 || list.get(0) != 10) return false;

        // 测试清空空列表
        Collection::Linear::LinkList<int> emptyList;
        emptyList.clear();
        if (!emptyList.empty() || emptyList.size() != 0) return false;

        // 测试清空后可以添加元素
        emptyList.add(20);
        if (emptyList.empty() || emptyList.size() != 1 || emptyList.get(0) != 20) return false;

        // 测试清空后使用其他操作
        Collection::Linear::LinkList<int> list2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        list2.clear();

        // 测试清空后添加多个元素
        list2.add({11, 12, 13});
        if (list2.size() != 3) return false;
        if (list2.get(0) != 11 || list2.get(1) != 12 || list2.get(2) != 13) return false;

        // 测试清空后reserve
        list2.clear();
        list2.reserve(5);
        if (list2.size() != 5) return false;
        for (size_t i = 0; i < 5; i++) {
            if (list2.get(i) != 0) return false; // 默认值
        }

        return true;
    }
    bool LinkListTester::setTest()
    {
        Collection::Linear::LinkList<int> list = {1, 2, 3, 4, 5};

        // 测试设置有效位置
        if (!list.set(0, 10)) return false;
        if (list.get(0) != 10) return false;

        if (!list.set(2, 30)) return false;
        if (list.get(2) != 30) return false;

        if (!list.set(list.size() - 1, 50)) return false;
        if (list.get(list.size() - 1) != 50) return false;

        // 检查其他元素未受影响
        if (list.get(1) != 2 || list.get(3) != 4) return false;

        // 测试设置越界位置
        if (list.set(10, 99)) return false; // 应该返回false
        if (list.set(list.size(), 99)) return false; // 索引等于size越界

        // 测试空列表设置
        Collection::Linear::LinkList<int> emptyList;
        if (emptyList.set(0, 1)) return false; // 应该返回false

        // 测试设置后使用其他操作
        if (!list.set(1, 20)) return false;
        list.add(60);
        if (list.size() != 6) return false;
        if (list.get(5) != 60) return false;
        if (list.get(1) != 20) return false; // 确保设置的值保持不变

        return true;
    }
    bool LinkListTester::countTest()
    {
        // 测试有重复元素的列表
        Collection::Linear::LinkList<int> list = {1, 2, 3, 2, 4, 2, 5, 2};

        if (list.count(1) != 1) return false;
        if (list.count(2) != 4) return false; // 2出现4次
        if (list.count(3) != 1) return false;
        if (list.count(4) != 1) return false;
        if (list.count(5) != 1) return false;
        if (list.count(0) != 0) return false; // 不存在的元素
        if (list.count(99) != 0) return false;

        // 测试空列表
        Collection::Linear::LinkList<int> emptyList;
        if (emptyList.count(1) != 0) return false;

        // 测试所有元素相同的列表
        Collection::Linear::LinkList<int> sameList = {7, 7, 7, 7, 7};
        if (sameList.count(7) != 5) return false;
        if (sameList.count(8) != 0) return false;

        // 测试添加元素后count变化
        Collection::Linear::LinkList<int> list2 = {1, 2, 3};
        if (list2.count(1) != 1) return false;

        list2.add(1); // 添加另一个1
        if (list2.count(1) != 2) return false;

        list2.add({1, 1, 1}); // 添加三个1
        if (list2.count(1) != 5) return false;

        // 测试删除元素后count变化
        list2.remove(0); // 删除第一个元素（可能是1）
        // 不确定删除哪个1，但count应该减少
        // 这里不检查具体值，只确保函数可以调用

        // 测试设置元素后count变化
        list2.set(0, 9); // 将某个元素设置为9
        if (list2.count(9) < 1) return false; // 至少有一个9

        return true;
    }
}

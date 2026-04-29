Algorithm————STL中的算法
STL中的算法大致可以分为以下七类：
1)不变序列算法   2)变值算法   3)删除算法   4)变序算法   5)排序算法   6)有序区间算法   7)数值算法

算法的基础比较方式与自定义比较方式————(类与对象实现对运算符()的重载，返回true则x在前)
大多重载的算法都是有两个版本的，其中一个是用“==”判断元素是否相等，或用“<”来比较大小；
而另一个版本多出来一个类型参数“Pred”，以及函数形参“Pred op”
该版本通过表达式“op(x,y)”的返回值是ture还是false，来判断x是否“等于”y，或者x是否“小于”y。


1-不变序列算法：![alt text](image-5.png) ![alt text](image-6.png) ![alt text](image-7.png)

for_each
template<class InIt, class Fun> 
Fun for_each(InIt first, InIt last, Fun f); 
对[first,last)中的每个元素 e ,执行 f(e) , 要求 f(e)不能改变e。

count:
template<class InIt, class T> 
size_t count(InIt first, InIt last, const T& val); 
计算[first,last) 中等于val的元素个数

count_if 
template<class InIt, class Pred> 
size_t count_if(InIt first, InIt last, Pred pr); 
计算[first,last) 中符合pr(e) == true 的元素 e的个数

min_element:
template<class FwdIt> 
FwdIt min_element(FwdIt first, FwdIt last); 
返回[first,last) 中最小元素的迭代器,以 “< ”作比较器。
最小指没有元素比它小，而不是它比别的不同元素都小
因为即便a!= b, a<b 和b<a有可能都不成立	

max_element:
template<class FwdIt> 
FwdIt max_element(FwdIt first, FwdIt last); 
返回[first,last) 中最大元素(它不小于任何其他元素，但不见得其他不同元素都小于它）的迭代器,以 “< ”作比较器。

find
template<class InIt, class T> 
InIt find(InIt first, InIt last, const T& val); 
返回区间 [first,last) 中的迭代器 i ,使得 * i == val

find_if
template<class InIt, class Pred> 
InIt find_if(InIt first, InIt last, Pred pr); 
返回区间 [first,last) 中的迭代器 i, 使得 pr(*i) == true


2-变值算法: ![alt text](image-8.png) ![alt text](image-9.png) ![alt text](image-10.png)

transform————典型变值算法：将一段区间经过uop函数作用转换到x开始的场域之中
template<class InIt, class OutIt, class Unop> 
OutIt transform(InIt first, InIt last, OutIt x, Unop uop); 
对[first,last)中的每个迭代器 I ,
执行 uop( * I ) ; 并将结果依次放入从 x 开始的地方。
要求 uop( * I ) 不得改变 * I 的值。
本模板返回值是个迭代器，即 x + (last-first)
x 可以和 first相等————自我的uop加工


3-删除算法：不应作用于关联容器  ![alt text](image-11.png)
默认的unique：使用==运算符
template<class FwdIt> 
FwdIt  unique(FwdIt first, FwdIt last); 
用 == 比较是否等

自我定义比较方式的unique：
template<class FwdIt, class Pred> 
FwdIt  unique(FwdIt first, FwdIt last, Pred pr);
用 pr 比较是否等

unique的作用效果：对[first,last) 这个序列中连续相等的元素，只留下第一个。返回值是迭代器，指向元素删除后的区间的最后一个元素的后面。
unique代码示例：![alt text](image-12.png)


4-变序算法：![alt text](image-13.png) ![alt text](image-14.png) ![alt text](image-15.png)
reverse：
template<class BidIt> 
void reverse(BidIt first, BidIt last);
颠倒区间[first,last)顺序

next_permutation
template<class InIt> 
bool next_permutaion (Init first,Init last);
求下一个排列


5-排序算法：一般是O(n×log(n))，需要随机访问迭代器的支持，因而不适用于关联容器和list。
![alt text](image-16.png) ![alt text](image-17.png)

**sort 是不稳定排序，即等值（按比较规则相等）的元素在排序后前后顺序可能改变。如果需要保持原有相对顺序，应使用 stable_sort。**
stable_sort如下：![alt text](image-18.png)
sort————快速排序
template<class RanIt> 
void sort(RanIt first, RanIt last); 
按升序排序。判断x是否应比y靠前，就看 x < y 是否为true

template<class RanIt, class Pred>
void sort(RanIt first, RanIt last, Pred pr);
按升序排序。判断x是否应比y靠前，就看 pr(x,y) 是否为true


5.5-堆与堆排序：
堆：一种二叉树，最大元素总是在堆顶上，二叉树中任何节点的子节点总是小于或等于父节点的值
序列化的堆结构表述：堆排序的众多算法需要随机访问迭代器支持
n个记录的序列，其所对应的关键字的序列为｛k0, k1, k2, …, kn-1｝，
若有如下关系成立时，则称该记录序列构成一个堆。ki≥k2i+1且 ki≥k2i+2, 其中i=0, 1, …,
![alt text](image-19.png)  ![alt text](image-20.png)  ![alt text](image-21.png)


6-有序区间算法：要求所操作的区间是已经从小到大排好序的，而且需要随机访问迭代器的支持。所以有序区间算法不能用于关联容器和list。
![alt text](image-22.png)  ![alt text](image-23.png)
binary_search 折半查找，要求容器已经有序，返回是否找到
template<class FwdIt, class T>
bool binary_search(FwdIt first, FwdIt last, const T& val); 
上面这个版本，比较两个元素x,y 大小时, 看 x < y

template<class FwdIt, class T, class Pred> 
bool binary_search(FwdIt first, FwdIt last, const T& val, Pred pr); 
上面这个版本，比较两个元素x,y 大小时, 若 pr(x,y) 为true，则认为x小于y

lower_bound：
 template<class FwdIt, class T> 
FwdIt lower_bound(FwdIt first, FwdIt last, const T& val); 
要求[first,last)是有序的，
查找[first,last)中的,最大的位置 FwdIt,使得[first,FwdIt) 中所有的元素都比 val 小

upper_bound
template<class FwdIt, class T>
 FwdIt upper_bound(FwdIt first, FwdIt last, const T& val); 
要求[first,last)是有序的，
查找[first,last)中的,最小的位置 FwdIt,使得[FwdIt,last) 中所有的元素都比 val 大

equal_range
template<class FwdIt, class T> 
pair<FwdIt, FwdIt> equal_range(FwdIt first, FwdIt last, const T& val); 
要求[first,last)是有序的，
返回值是一个pair, 假设为 p, 则：
[first,p.first) 中的元素都比 val 小
[p.second,last)中的所有元素都比 val 大
p.first  就是lower_bound的结果
p.last 就是 upper_bound的结果

还有一些不常见的用法：
![alt text](image-24.png)  ![alt text](image-25.png)  ![alt text](image-26.png)  
![alt text](image-27.png)  ![alt text](image-28.png)  ![alt text](image-29.png)


7-bitset相关：
简介一下bitset：bitset 是 C++ 标准库中用于固定大小位集合的类模板，定义在 <bitset> 头文件中。
特点：
编译期确定大小：模板参数 N 表示位数，如 bitset<8> b;
高效位操作：支持与、或、异或、取反、左移/右移等运算
提供便捷转换：可转为 unsigned long / unsigned long long / 字符串
无动态内存分配：大小固定，内部通常用整数数组存储

建立与使用：template<size_t N>
 class bitset {
    ….. 
};
实际使用的时候，N是个整型常数
如：bitset<40> bst;    bst是一个由40位组成的对象，用bitset的函数可以方便地访问任何一位。

bitset的成员函数：
![alt text](image-30.png)  ![alt text](image-31.png)  ![alt text](image-32.png)
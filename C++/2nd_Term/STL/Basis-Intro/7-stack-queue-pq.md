stack 是后进先出的数据结构，只能插入，删除，访问栈顶的元素。
可用 vector, list, deque来实现。缺省情况下，用deque实现。用vector和deque实现，比用list实现性能好。
stack 上可以进行以下操作：
push-插入元素  pop-弹出元素  top-返回栈顶元素的引用 	

queue和stack 基本类似，可以用 list和deque实现。缺省情况下用deque实现。
同样也有push, pop, top函数。但是push发生在队尾；pop, top发生在队头。先进先出。
有back成员函数可以返回队尾元素的引用

priority_queue:模板的形式为<类型，何种容器实现，优先级比较函数(用类与对象实现)>
template <class T, class Container = vector<T>, class Compare = less<T> > 
class priority_queue;
和 queue类似，可以用vector和deque实现。缺省情况下用vector实现。
priority_queue 通常用堆排序技术实现，保证最大的元素总是在最前面。
即执行pop操作时，删除的是最大的元素；执行top操作时，返回的是最大元素的常引用。默认的元素比较器是 less<T>。
push、pop 时间复杂度O(logn);top()时间复杂度O(1)

容器适配器的元素个数访问函数：
stack,queue,priority_queue 都有
empty()————成员函数用于判断适配器是否为空
size()————成员函数返回适配器中元素个数
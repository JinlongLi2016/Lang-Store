# Generic Programming


* 定义顺序容器
```c++
#include <algorithm>
#include <vector>
// 1 产生空容器
list<string> slist;
vector<int> ivec;
// 2 产生特定大小的容器
list<string> slist(10);

// 3 产生特定大小的容器，并指定初值
list<string> slist(10, 'default_string');
// 4: initilize with 2 iterators
list<string> slist(iter_begin, iter_end);

// 5: copy
list<string> slist(slist2); // copy slist2 to slit
```



* 提供两个特别的操作函数，允许我们在容器末尾进行插入和删除操作:`push_back()`  & `pop_back()`
* 每个容器除了通用的插入函数`insert`，还支持4种变形
  1. `iterator insert(iterator pos, elemType value)`: 将元素插入到pos之前。返回一个iterator,指向被插入的元素。
  2. `void insert(iterator pos, int count, elemType Value)`: 在`pos`之前插入`count`个 `value`.
  3. `void insert(iterator pos, iterator first, iterator last)`: 将`[first, last)`之间的元素插入到`pos`之前。
  4. `iterator insert(iterator pos)`: 将默认值插入到pos之前。返回一个iterator,指向被插入的元素。

* `pop_front` and `pop_back()` 属于特殊化的删除(erase)操作。除了通用的erase操作，还支持两种变形
  1. `iterator erase(iterator pos)`
  2. `iterator earse(iterator first, iterator last)`

* using generic algorithm

```c++
// binary search in a vector
#include <algorithm>
void function(){
    vector<int> tmp(vector.size());
	copy(vector.begin(), vector.end(), tmp.begin());
    
    sort(tmp.begin(), tmp.end());
    
    binary_search(tmp.begin(), tmp.end(), elem);
}
```



* 函数对象 function object

  重载了`__call__`的类，其实例支持像函数一样调用。

  其实现了原本可以通过单独函数实现的功能. Why bother? efficiency. 我们可以令`__call__`为内敛函数，消除“通过函数指针调用函数”时需要付出的额外代价。

  标准库事先定义了一组 function object

  1. arithmetic: + - * /  取相反数 modules<type>
  2. relational: > >= < <= == !=
  3. logical:　与或非



​	

```c++
// 将斐波那契数列的一段，加上另一个数列的一段，结果放在新的位置
transform( fib.begin(), fib.end(),	// (1)欲转换元素的范围[start, end)
         pell.begin(),				// (2)所指向的元素将应用于转换操作
         fib_plus_pell.begin(),		// (3)所指元素（及后续空间）用于保存结果
         plus<int>() );				// (4)想要应用的转换操作
```

* 函数对象适配器(function object adaptor)

  （类似于python中的`partial`函数）

  可以将二元运算符(转换为一个一元运算符(unary)). 比如`less<type>()`本来接收两个参数，通过function object adaptor， 可以提前绑定一个参数。绑定之后函数只需要接收一个参数就行。

  2 binder adapters: `bind1st` & `bind2nd`

  `bind2nd(less<int>(), 10)`



​	另外一种是negator, 取反的适配器。

---

函数模板调用的时候不需要指定类型？那为什么类模板需要指定？

一个是运行时，一个是编译时？？

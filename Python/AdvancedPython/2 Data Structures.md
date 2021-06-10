#Data Structure

* 高效地组织数据
* 创建二维数组

## 数据组织

铭记“程序模型是客观世界的”会对某个具体的客观事物选择合适的表示方式大有裨益。这想想或许是非常直接的，但实际上却需要大量的考量才能达到目的。

刚开始的时候，你也许会为应用选择合适的模型绞尽脑汁，但这个过程会帮助你成为一个更好的程序猿。当然，你也可以遵从前人指导，但我不推荐这样。解决编程难题是必经之路。在你编程做决定的时候，会对你的程序有一个更加全面的理解。

在你的Python之路上，你会适应日益复杂的数据结构。目前，我们创建的结构有`list`和`dict`，他们都是不可改变的(immutable)，不可改变的还有数字(numbers)和字符串(strings)。当然，你也可以在你自己的数据结构中使用list, tuples, dicts或其他复杂数据结构。

在对象中数据结构也是相当重要的。通过一个`class`语句定义一类对象的行为。class语句定义了类实例的行为--`method` ，用户可以调用它们来产生某种行为。Each instance has its own namespace though, which makes it appear like a data structure with behaviors common to all members of its class.    

### Handling Multi-Dimensional Arrays in Python    

Python中，我们一般通过从创建类来执行任务。索引(indexing)是利用`__getitem__`方法完成的。

__整数(integer)和切片`int slice`__是可以用做下标索引的**唯二**类型(type)。一般不直接和slice对象进行接触，而是通过冒号分割的多下标方式进行访问(for which 冒号也被称为切片符号)。

Slices are allowed only as top-level elements of **a tuple** of subscripting expressions. Parenthesizing the tuple, or trying to use a similar expression outside of subscripting brackets, both result in syntax errors    A single integer index is passed through to the `__getitem__()` method without change. But the interpreter creates a special object called **a slice object** for constructs that contain colons（冒号）. _The slice object is passed through to the `__getitem__()`  method_. The last line in the example demonstrates that the interpreter allows us to use multiple slice notations as subscripts, and the `__getitem__()` method will receive a tuple of slice objects.    

```python
obj[M] == obj.__getitem__(M)
holds ture when M is an integer or a slice.
```

```python
obj[M:N] == obj.__getitem__(slice(M, N, None)) 
and
obj[M:N:S] == obj.__getitem__(slice(M, N, S))
```

方括号下标访问都会被代理到`__getitem__`、 `__setitem__`方法上去，这就给了我们很大的想象空间：我们可以在类的这两个方法上恣意妄为。

```python
class array:
    def __init__(self, M, N):
        self._data = [0] * M * N
        self._rows = M
        self._cols = N
    def __getitem__(self, key):
        """retrieve elements from self._data"""
        pass
   	def __setitem__(self, key, value):
        """Set value to place key in self._data"""
        pass
   	def __delitem__(self, key):
        """Amos: delete an item from self._data"""
```

更多请参考书籍。

# 课后练习Quiz

## Data Structures - Quiz 1

Which data types can be used to index a sequence?

int and slice

**Grading Criteria:** Student should show a more sophisticated understanding of indexing.

What is the best-known third-party package for numerical programming in Python?

Numpy.

**Grading Criteria:** Student shows developing awareness of the Python ecosystem and its third-party libraries, especially where intensive numeric computing is concerned.

Which method of o is called when evaluating o[i] (o and i should be part of the answer)?

__getitem__()

**Grading Criteria:** Student should show increased understanding of how syntax triggers special named methods.
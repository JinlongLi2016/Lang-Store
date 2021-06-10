# Python Collection Modules

This module implements **specialized container datatypes* providing alternatives to Python’s general purpose built-in containers, [`dict`](https://docs.python.org/3.7/library/stdtypes.html#dict), [`list`](https://docs.python.org/3.7/library/stdtypes.html#list), [`set`](https://docs.python.org/3.7/library/stdtypes.html#set), and [`tuple`](https://docs.python.org/3.7/library/stdtypes.html#tuple).



|                                                              |                                                              |
| ------------------------------------------------------------ | :----------------------------------------------------------- |
| [`namedtuple()`](https://docs.python.org/3.7/library/collections.html#collections.namedtuple) | factory function for creating tuple subclasses with named fields |
| [`deque`](https://docs.python.org/3.7/library/collections.html#collections.deque) | list-like container with fast appends and pops on either end |
| [`ChainMap`](https://docs.python.org/3.7/library/collections.html#collections.ChainMap) | dict-like class for creating a single view of multiple mappings |
| [`Counter`](https://docs.python.org/3.7/library/collections.html#collections.Counter) | dict subclass for counting hashable objects对可哈对象计数的字典 |
| [`OrderedDict`](https://docs.python.org/3.7/library/collections.html#collections.OrderedDict) | dict subclass that remembers the order entries were added    |
| [`defaultdict`](https://docs.python.org/3.7/library/collections.html#collections.defaultdict) | dict subclass that calls a factory function to supply missing values |
| [`UserDict`](https://docs.python.org/3.7/library/collections.html#collections.UserDict) | wrapper around dictionary objects for easier dict subclassing |
| [`UserList`](https://docs.python.org/3.7/library/collections.html#collections.UserList) | wrapper around list objects for easier list subclassing      |
| [`UserString`](https://docs.python.org/3.7/library/collections.html#collections.UserString) | wrapper around string objects for easier string subclassing  |


## 1 `defaultdict`

*class* `collections.``defaultdict`([*default_factory*[, *...*]])

返回一个新的**似字典**对象。`defaultdict`是内建`dict`类型的子类，它重写了一个方法和添加了一个可写的**实例变量**。其余功能和`dict`类一样。

Returns a new dictionary-like object. [`defaultdict`](https://docs.python.org/2/library/collections.html#collections.defaultdict) is a subclass of the built-in [`dict`](https://docs.python.org/2/library/stdtypes.html#dict) class. It overrides one method and adds one writable instance variable. The remaining functionality is the same as for the [`dict`](https://docs.python.org/2/library/stdtypes.html#dict) class and is not documented here.

第一个参数提供了`default_factory`属性的初始值；它默认为`None`。其余所有的参数（位置/关键字）都直接传递给`dict`构造器。

The first argument provides the initial value for the [`default_factory`](https://docs.python.org/2/library/collections.html#collections.defaultdict.default_factory) attribute; it defaults to `None`. All remaining arguments are treated the same as if they were passed to the [`dict`](https://docs.python.org/2/library/stdtypes.html#dict) constructor, including keyword arguments.



## examples

Using `list` as the `default_factory`, it is easy to group a sequence of key-value pairs into a dictionary of lists:

```python
>>> s = [('yellow', 1), ('blue', 2), ('yellow', 3), ('blue', 4), ('red', 1)]
>>> d = defaultdict(list)
>>> for k, v in s:
...     d[k].append(v)
...
>>> d.items()
[('blue', [2, 4]), ('red', [1]), ('yellow', [1, 3])]
```

When each key is encountered for the first time, it is not already in the mapping; so an entry is automatically created using the `default_factory` function which returns an empty `list`. The `list.append()` operation then attaches the value to the new list. When keys are encountered again, the look-up proceeds normally (returning the list for that key) and the `list.append()` operation adds another value to the list. This technique is **simpler and faster** than an equivalent technique using [`dict.setdefault()`](https://docs.python.org/2/library/stdtypes.html#dict.setdefault):

```python
>>> d = {}
>>> for k, v in s:
...     d.setdefault(k, []).append(v)
...
>>> d.items()
[('blue', [2, 4]), ('red', [1]), ('yellow', [1, 3])]
```

Setting the `default_factory` to [`int`](https://docs.python.org/2/library/functions.html#int) makes the [`defaultdict`](https://docs.python.org/2/library/collections.html#collections.defaultdict) useful for counting (like a bag or multiset in other languages):[Amos: There is a better way for counting, that is collections.Count() ?Probably]

```python
>>> s = 'mississippi'
>>> d = defaultdict(int)
>>> for k in s:
...     d[k] += 1
...
>>> d.items()
[('i', 4), ('p', 2), ('s', 4), ('m', 1)]
```

When a letter is first encountered, it is missing from the mapping, so the `default_factory` function calls [`int()`](https://docs.python.org/2/library/functions.html#int) to supply a default count of zero. The increment operation then builds up the count for each letter.

The function [`int()`](https://docs.python.org/2/library/functions.html#int) which always returns zero is just a special case of constant functions. A faster and more flexible way to create constant functions is to use [`itertools.repeat()`](https://docs.python.org/2/library/itertools.html#itertools.repeat) which can supply any constant value (not just zero):

```python
>>> def constant_factory(value):
...     return itertools.repeat(value).next
>>> d = defaultdict(constant_factory('<missing>'))
>>> d.update(name='John', action='ran')
>>> '%(name)s %(action)s to %(object)s' % d
'John ran to <missing>'
```

Setting the `default_factory` to [`set`](https://docs.python.org/2/library/stdtypes.html#set) makes the [`defaultdict`](https://docs.python.org/2/library/collections.html#collections.defaultdict) useful for building a dictionary of sets:

```python
>>> s = [('red', 1), ('blue', 2), ('red', 3), ('blue', 4), ('red', 1), ('blue', 4)]
>>> d = defaultdict(set)
>>> for k, v in s:
...     d[k].add(v)
...
>>> d.items()
[('blue', set([2, 4])), ('red', set([1, 3]))]
```
## 2 `collections.Counter`

`Counter`是`dict`子类，用以对可哈希对象计数。它是`elements(可哈对象):counts`的无序集合。counts可以是任意整数（0 and negative values included）。它和其他语言中的bags或者multisets很类似。

A [`Counter`](https://docs.python.org/3.7/library/collections.html#collections.Counter) is a [`dict`](https://docs.python.org/3.7/library/stdtypes.html#dict) subclass for counting hashable objects. It is an unordered collection where elements are stored as dictionary keys and their counts are stored as dictionary values. Counts are allowed to be any integer value including zero or negative counts. The [`Counter`](https://docs.python.org/3.7/library/collections.html#collections.Counter) class is similar to bags or multisets in other languages.

Elements are counted from an *iterable* or initialized from another *mapping* (or counter):

```
>>> c = Counter()                           # a new, empty counter
>>> c = Counter('gallahad')                 # a new counter from an iterable
>>> c = Counter({'red': 4, 'blue': 2})      # a new counter from a mapping
>>> c = Counter(cats=4, dogs=8)             # a new counter from keyword args
```

Counter objects have a dictionary interface except that they return a zero count for missing items instead of raising a [`KeyError`](https://docs.python.org/3.7/library/exceptions.html#KeyError):

```
>>> c = Counter(['eggs', 'ham'])
>>> c['bacon']                              # count of a missing element is zero
0
```

Setting a count to zero does not remove an element from a counter. Use `del` to remove it entirely:

```
>>> c['sausage'] = 0                        # counter entry with a zero count
>>> del c['sausage']                        # del actually removes the entry
```



New in version 3.1.

Counter objects support three methods beyond those available for all dictionaries:

- `elements`()

  返回元素迭代器，将每个元素重复对应的count次。元素返回的次序不定。函数会忽略count小于1的元素。

  Return an iterator over elements repeating each as many times as its count. Elements are returned in arbitrary order. If an element’s count is less than one, [`elements()`](https://docs.python.org/3.7/library/collections.html#collections.Counter.elements) will ignore it.>>>`>>> c = Counter(a=4, b=2, c=0, d=-2) >>> sorted(c.elements()) ['a', 'a', 'a', 'a', 'b', 'b'] `

- `most_common`([*n*])

  返回一个n个最常出现的元素及它们对应的计数count，从高频元素到低频元素的顺序。如果n被忽略或者是`None`,则会返回counter的所有元素。

  Return a list of the *n* most common elements and their counts from the most common to the least. If *n* is omitted or `None`, [`most_common()`](https://docs.python.org/3.7/library/collections.html#collections.Counter.most_common) returns *all* elements in the counter. Elements with equal counts are ordered arbitrarily:>>>`>>> Counter('abracadabra').most_common(3)   [('a', 5), ('r', 2), ('b', 2)] `

- `subtract`([*iterable-or-mapping*])

  Elements are subtracted from an *iterable* or from another *mapping* (or counter). Like [`dict.update()`](https://docs.python.org/3.7/library/stdtypes.html#dict.update) but subtracts counts instead of replacing them. Both inputs and outputs may be zero or negative.>>>`>>> c = Counter(a=4, b=2, c=0, d=-2) >>> d = Counter(a=1, b=2, c=3, d=4) >>> c.subtract(d) >>> c Counter({'a': 3, 'b': 0, 'c': -3, 'd': -6}) `New in version 3.2.

The usual dictionary methods are available for [`Counter`](https://docs.python.org/3.7/library/collections.html#collections.Counter) objects except for two which work differently for counters.

- `fromkeys`(*iterable*)

  This class method is not implemented for [`Counter`](https://docs.python.org/3.7/library/collections.html#collections.Counter) objects.

- `update`([*iterable-or-mapping*])

  Elements are counted from an *iterable* or added-in from another *mapping* (or counter). Like [`dict.update()`](https://docs.python.org/3.7/library/stdtypes.html#dict.update) but adds counts instead of replacing them. Also, the *iterable* is expected to be a sequence of elements, not a sequence of `(key, value)` pairs.

  

  The usual dictionary methods are available for [`Counter`](https://docs.python.org/3.7/library/collections.html#collections.Counter) objects except for two which work differently for counters. `fromkeys(iterable)` and `update([iterable-or-mapping])`



##  OrderedDict objects

Return an instance of a dict subclass, supporting the usual [`dict`](https://docs.python.org/3.7/library/stdtypes.html#dict) methods. An *OrderedDict* is a dict that remembers the order that keys were first inserted. If a new entry overwrites an existing entry, the original insertion position is left unchanged. Deleting an entry and reinserting it will move it to the end. 

- `popitem`(*last=True*)

  The [`popitem()`](https://docs.python.org/3.7/library/collections.html#collections.OrderedDict.popitem) method for ordered dictionaries returns and removes a (key, value) pair. The pairs are returned in LIFO order if *last* is true or FIFO order if false.

- `move_to_end`(*key*, *last=True*)

  Move an existing *key* to either end of an ordered dictionary. The item is moved to the right end if *last* is true (the default) or to the beginning if *last* is false.

In addition to the usual mapping methods, ordered dictionaries also support reverse iteration using [`reversed()`](https://docs.python.org/3.7/library/functions.html#reversed).

Equality tests between [`OrderedDict`](https://docs.python.org/3.7/library/collections.html#collections.OrderedDict) objects are order-sensitive and are implemented as `list(od1.items())==list(od2.items())`. Equality tests between [`OrderedDict`](https://docs.python.org/3.7/library/collections.html#collections.OrderedDict) objects and other [`Mapping`](https://docs.python.org/3.7/library/collections.abc.html#collections.abc.Mapping) objects are order-insensitive like regular dictionaries. This allows [`OrderedDict`](https://docs.python.org/3.7/library/collections.html#collections.OrderedDict) objects to be substituted anywhere a regular dictionary is used.



## deque([iterable [,maxlen]])

stack & queue的推广

从左至右根据iterable初始化 一个双端队列，两侧插入删除复杂度接近O(1)， （列表是针对固定长度，插入删除元素可能会导致O(n)复杂度）

If *maxlen* is not specified or is `None`, deques may grow to an arbitrary length. Otherwise, the deque is bounded to the specified maximum length. Once a bounded length deque is full, when new items are added, a corresponding number of items are discarded from the opposite end. 

**append() pop() 使得其行为类似于stack(先进后出)** 

**append() popleft() 使其行为类似于queue（先进先出）** pop()在没有元素时，会抛出异常  IndexError

- `append`(*x*)

  Add *x* to the right side of the deque.
  
- `pop`()

  Remove and return an element from the right side of the deque. If no elements are present, raises an [`IndexError`](https://docs.python.org/3.7/library/exceptions.html#IndexError).


- `appendleft`(*x*)

  Add *x* to the left side of the deque.

- `clear`()

  Remove all elements from the deque leaving it with length 0.

- `copy`()

  Create a shallow copy of the deque.New in version 3.5.

- `count`(*x*)

  Count the number of deque elements equal to *x*.New in version 3.2.

- `extend`(*iterable*)

  Extend the right side of the deque by appending elements from the iterable argument.

- `extendleft`(*iterable*)

  Extend the left side of the deque by appending elements from *iterable*. Note, the series of left appends results in reversing the order of elements in the iterable argument.

- `index`(*x*[, *start*[, *stop*]])

  Return the position of *x* in the deque (at or after index *start* and before index *stop*). Returns the first match or raises [`ValueError`](https://docs.python.org/3.7/library/exceptions.html#ValueError) if not found.New in version 3.5.

- `insert`(*i*, *x*)

  Insert *x* into the deque at position *i*.If the insertion would cause a bounded deque to grow beyond *maxlen*, an [`IndexError`](https://docs.python.org/3.7/library/exceptions.html#IndexError) is raised.New in version 3.5.


- `popleft`()

  Remove and return an element from the left side of the deque. If no elements are present, raises an [`IndexError`](https://docs.python.org/3.7/library/exceptions.html#IndexError).

- `remove`(*value*)

  Remove the first occurrence of *value*. If not found, raises a [`ValueError`](https://docs.python.org/3.7/library/exceptions.html#ValueError).

- `reverse`()

  Reverse the elements of the deque in-place and then return `None`.New in version 3.2.

- `rotate`(*n=1*)

  Rotate the deque *n* steps to the right. If *n* is negative, rotate to the left.When the deque is not empty, rotating one step to the right is equivalent to `d.appendleft(d.pop())`, and rotating one step to the left is equivalent to `d.append(d.popleft())`.

Deque objects also provide one read-only attribute:

- `maxlen`

  Maximum size of a deque or `None` if unbounded.

## namedtuple

`collections.namedtuple(typename, field_name, *, rename=False, defaults=None, module=None)`

`field_names` 是一个如 `['x', 'y']`这样的序列。

* `classmethod somenamedtuple._make(iterable)`

  从已有序列或可迭代对象初始化一个新的具名元组

* `somenamedtuple._asdict()`
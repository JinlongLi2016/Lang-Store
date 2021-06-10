# Basic Data Types(container?)

## dict

A [mapping](https://docs.python.org/3/glossary.html#term-mapping) object maps [hashable](https://docs.python.org/3/glossary.html#term-hashable) values to arbitrary objects. Mappings are mutable objects. There is currently only one standard mapping type, the *dictionary*. (For other containers see the built-in [`list`](https://docs.python.org/3/library/stdtypes.html#list), [`set`](https://docs.python.org/3/library/stdtypes.html#set), and [`tuple`](https://docs.python.org/3/library/stdtypes.html#tuple)classes, and the [`collections`](https://docs.python.org/3/library/collections.html#module-collections) module.) 

映射对象映射任何可哈值到任意对象。映射是可变对象。

A dictionary’s keys are *almost* arbitrary values. Values that are not [hashable](https://docs.python.org/3/glossary.html#term-hashable), that is, values containing lists, dictionaries or other mutable types (that are compared by value rather than by object identity) may not be used as keys. Numeric types used for keys obey the normal rules for numeric comparison: if two numbers compare equal (such as `1` and `1.0`) then they can be used interchangeably to index the same dictionary entry. (Note however, that since computers store floating-point numbers as approximations it is usually unwise to use them as dictionary keys.) 

Dictionaries can be created by placing a comma-separated list of `key: value` pairs within braces, for example: `{'jack': 4098, 'sjoerd': 4127}` or `{4098: 'jack', 4127: 'sjoerd'}`, or by the [`dict`](https://docs.python.org/3/library/stdtypes.html#dict) constructor. 

*class* `dict`(**\*kwarg*)

*class* `dict`(*mapping*, **\*kwarg*)

*class* `dict`(*iterable*, **\*kwarg*)

Return a new dictionary initialized from an optional positional argument and a possibly empty set of keyword arguments.

If no positional argument is given, an empty dictionary is created. If a positional argument is given and it is a mapping object, a dictionary is created with the same key-value pairs as the mapping object. Otherwise, the positional argument must be an [iterable](https://docs.python.org/3/glossary.html#term-iterable) object. Each item in the iterable must itself be an iterable with exactly two objects. The first object of each item becomes a key in the new dictionary, and the second object the corresponding value. If a key occurs more than once, the last value for that key becomes the corresponding value in the new dictionary.

If keyword arguments are given, the keyword arguments and their values are added to the dictionary created from the positional argument. If a key being added is already present, the value from the keyword argument replaces the value from the positional argument.

To illustrate, the following examples all return a dictionary equal to `{"one": 1, "two": 2, "three": 3}`:

\>>>

```python
>>> a = dict(one=1, two=2, three=3)
>>> b = {'one': 1, 'two': 2, 'three': 3}
>>> c = dict(zip(['one', 'two', 'three'], [1, 2, 3]))
>>> d = dict([('two', 2), ('one', 1), ('three', 3)])
>>> e = dict({'three': 3, 'one': 1, 'two': 2})
>>> a == b == c == d == e
True
```

Providing keyword arguments as in the first example only works for keys that are valid Python identifiers. Otherwise, any valid keys can be used.

These are the operations that dictionaries support (and therefore, custom mapping types should support too):

- `len(d)`

  Return the number of items in the dictionary *d*.

- `d[key]`

  Return the item of *d* with key *key*. Raises a [`KeyError`](https://docs.python.org/3/library/exceptions.html#KeyError) if *key* is not in the map.If a subclass of dict defines a method [`__missing__()`](https://docs.python.org/3/reference/datamodel.html#object.__missing__) and *key* is not present, the `d[key]` operation calls that method with the key *key* as argument. The `d[key]` operation then returns or raises whatever is returned or raised by the `__missing__(key)` call. No other operations or methods invoke [`__missing__()`](https://docs.python.org/3/reference/datamodel.html#object.__missing__). If [`__missing__()`](https://docs.python.org/3/reference/datamodel.html#object.__missing__) is not defined, [`KeyError`](https://docs.python.org/3/library/exceptions.html#KeyError) is raised. [`__missing__()`](https://docs.python.org/3/reference/datamodel.html#object.__missing__) must be a method; it cannot be an instance variable:

  ```
  
  ```

  >>>`>>> class Counter(dict): 
  >>>
  >>>...     def __missing__(self, key): ...         return 0 >>> c = Counter() >>> c['red'] 0 >>> c['red'] += 1 >>> c['red'] 1 `The example above shows part of the implementation of [`collections.Counter`](https://docs.python.org/3/library/collections.html#collections.Counter). A different `__missing__`method is used by [`collections.defaultdict`](https://docs.python.org/3/library/collections.html#collections.defaultdict).

  ```
  
  ```

- `d[key] = value`

  Set `d[key]` to *value*.

- `del d[key]`

  Remove `d[key]` from *d*. Raises a [`KeyError`](https://docs.python.org/3/library/exceptions.html#KeyError) if *key* is not in the map.

- `key in d`

  Return `True` if *d* has a key *key*, else `False`.

- `key not in d`

  Equivalent to `not key in d`.

- `iter(d)`

  Return an iterator over the keys of the dictionary. This is a shortcut for `iter(d.keys())`.

- `clear`()

  Remove all items from the dictionary.

- `copy`()

  Return a shallow copy of the dictionary.

- *classmethod* `fromkeys`(*seq*[, *value*])

  Create **a new dictionary with keys from *seq* and values set to *value***.[`fromkeys()`](https://docs.python.org/3/library/stdtypes.html#dict.fromkeys) is a class method that returns a new dictionary. *value* defaults to `None`.

- `get`(*key*[, *default*])

  Return the value for *key* if *key* is in the dictionary, else *default*. If *default* is not given, it defaults to `None`, so that this method never raises a [`KeyError`](https://docs.python.org/3/library/exceptions.html#KeyError).

- `items`()

  Return a new view of the dictionary’s items (`(key, value)` pairs). See the [documentation of view objects](https://docs.python.org/3/library/stdtypes.html#dict-views).

- `keys`()

  Return a new view of the dictionary’s keys. See the [documentation of view objects](https://docs.python.org/3/library/stdtypes.html#dict-views).

  返回字典键的一个新view

- `pop`(*key*[, *default*])

  If *key* is in the dictionary, remove it and return its value, else return *default*. If *default* is not given and *key*is not in the dictionary, a [`KeyError`](https://docs.python.org/3/library/exceptions.html#KeyError) is raised.

  从字典中移除key并返回它的value。如果key不存在则返回default。如果default不存在则抛出`KeyError`异常（还是错误？）

- `popitem`()

  Remove and return a `(key, value)` pair from the dictionary. Pairs are returned in LIFO order.[`popitem()`](https://docs.python.org/3/library/stdtypes.html#dict.popitem) is useful to destructively iterate over a dictionary, as often used in set algorithms. If the dictionary is empty, calling [`popitem()`](https://docs.python.org/3/library/stdtypes.html#dict.popitem) raises a [`KeyError`](https://docs.python.org/3/library/exceptions.html#KeyError).Changed in version 3.7: LIFO order is now guaranteed. In prior versions, [`popitem()`](https://docs.python.org/3/library/stdtypes.html#dict.popitem) would return an arbitrary key/value pair.

- `setdefault`(*key*[, *default*])

  If *key* is in the dictionary, return its value. If not, insert *key* with a value of *default* and return *default*.*default* defaults to `None`.

- `update`([*other*])

  Update the dictionary with the key/value pairs from *other*, overwriting existing keys. Return `None`.[`update()`](https://docs.python.org/3/library/stdtypes.html#dict.update) accepts either another dictionary object or an iterable of key/value pairs (as tuples or other iterables of length two). If keyword arguments are specified, the dictionary is then updated with those key/value pairs: `d.update(red=1, blue=2)`.

- `values`()

  Return a new view of the dictionary’s values. See the [documentation of view objects](https://docs.python.org/3/library/stdtypes.html#dict-views).

  返回字典值的新view

Dictionaries compare equal if and only if they have the same `(key, value)` pairs. Order comparisons (‘<’, ‘<=’, ‘>=’, ‘>’) raise [`TypeError`](https://docs.python.org/3/library/exceptions.html#TypeError).

Dictionaries preserve insertion order. Note that updating a key does not affect the order. Keys added after deletion are inserted at the end.

\>>>

```Python
>>> d = {"one": 1, "two": 2, "three": 3, "four": 4}
>>> d
{'one': 1, 'two': 2, 'three': 3, 'four': 4}
>>> list(d)
['one', 'two', 'three', 'four']
>>> list(d.values())
[1, 2, 3, 4]
>>> d["one"] = 42
>>> d
{'one': 42, 'two': 2, 'three': 3, 'four': 4}
>>> del d["two"]
>>> d["two"] = None
>>> d
{'one': 42, 'three': 3, 'four': 4, 'two': None}
```

Changed in version 3.7: Dictionary order is guaranteed to be insertion order. This behavior was implementation detail of CPython from 3.6.

## List

Common Sequence Operations:

| Operation              | Result                                                       | Notes  |
| ---------------------- | ------------------------------------------------------------ | ------ |
| `x in s`               | `True` if an item of *s* is equal to *x*, else `False`       | (1)    |
| `x not in s`           | `False` if an item of *s* is equal to *x*, else `True`       | (1)    |
| `s + t`                | the concatenation of *s* and *t*                             | (6)(7) |
| `s * n` or `n * s`     | equivalent to adding *s* to itself *n* times                 | (2)(7) |
| `s[i]`                 | *i*th item of *s*, origin 0                                  | (3)    |
| `s[i:j]`               | slice of *s* from *i* to *j*                                 | (3)(4) |
| `s[i:j:k]`             | slice of *s* from *i* to *j* with step *k*                   | (3)(5) |
| `len(s)`               | length of *s*                                                |        |
| `min(s)`               | smallest item of *s*                                         |        |
| `max(s)`               | largest item of *s*                                          |        |
| `s.index(x[, i[, j]])` | index of the first occurrence of *x* in *s* (at or after index *i* and before index *j*) | (8)    |
| `s.count(x)`           | total number of occurrences of *x* in *s*                    |        |

Sequences of the same type also support comparisons. In particular, tuples and lists are compared lexicographically by comparing corresponding elements. This means that to compare equal, every element must compare equal and the two sequences must be of the same type and have the same length. (For full details see [Comparisons](https://docs.python.org/3/reference/expressions.html#comparisons) in the language reference.)

Notes:

1. While the `in` and `not in` operations are used only for simple containment testing in the general case, some specialized sequences (such as [`str`](https://docs.python.org/3/library/stdtypes.html#str), [`bytes`](https://docs.python.org/3/library/stdtypes.html#bytes) and [`bytearray`](https://docs.python.org/3/library/stdtypes.html#bytearray)) also use them for subsequence testing:

   \>>>

   ```python
   >>> "gg" in "eggs"
   True
   ```

2. Values of *n* less than `0` are treated as `0` (which yields an empty sequence of the same type as *s*). Note that items in the sequence *s* are not copied; they are referenced multiple times. This often haunts new Python programmers; consider:

   \>>>

   ```python
   >>> lists = [[]] * 3
   >>> lists
   [[], [], []]
   >>> lists[0].append(3)
   >>> lists
   [[3], [3], [3]]
   ```

   What has happened is that `[[]]` is a one-element list containing an empty list, so all three elements of `[[]]* 3` are references to this single empty list. Modifying any of the elements of `lists` modifies this single list. You can create a list of different lists this way:

   ```python
   >>> lists = [[] for i in range(3)]
   >>> lists[0].append(3)
   >>> lists[1].append(5)
   >>> lists[2].append(7)
   >>> lists
   [[3], [5], [7]]
   ```

   Further explanation is available in the FAQ entry [How do I create a multidimensional list?](https://docs.python.org/3/faq/programming.html#faq-multidimensional-list).

3. If *i* or *j* is negative, the index is relative to the end of sequence *s*: `len(s) + i` or `len(s) + j` is substituted. But note that `-0` is still `0`.

4. The slice of *s* from *i* to *j* is defined as the sequence of items with index *k* such that `i <= k < j`. If *i* or *j* is greater than `len(s)`, use `len(s)`. If *i* is omitted or `None`, use `0`. If *j* is omitted or `None`, use `len(s)`. If *i* is greater than or equal to *j*, the slice is empty.

5. The slice of *s* from *i* to *j* with step *k* is defined as the sequence of items with index `x = i + n*k` such that `0<= n < (j-i)/k`. In other words, the indices are `i`, `i+k`, `i+2*k`, `i+3*k` and so on, stopping when *j* is reached (but never including *j*). When *k* is positive, *i* and *j* are reduced to `len(s)` if they are greater. When *k* is negative, *i* and *j* are reduced to `len(s) - 1` if they are greater. If *i* or *j* are omitted or `None`, they become “end” values (which end depends on the sign of *k*). Note, *k* cannot be zero. If *k* is `None`, it is treated like `1`.

6. Concatenating immutable sequences always results in a new object. This means that building up a sequence by repeated concatenation will have a quadratic runtime cost in the total sequence length. To get a linear runtime cost, you must switch to one of the alternatives below:

   - if concatenating [`str`](https://docs.python.org/3/library/stdtypes.html#str) objects, you can build a list and use [`str.join()`](https://docs.python.org/3/library/stdtypes.html#str.join) at the end or else write to an [`io.StringIO`](https://docs.python.org/3/library/io.html#io.StringIO) instance and retrieve its value when complete
   - if concatenating [`bytes`](https://docs.python.org/3/library/stdtypes.html#bytes) objects, you can similarly use [`bytes.join()`](https://docs.python.org/3/library/stdtypes.html#bytes.join) or [`io.BytesIO`](https://docs.python.org/3/library/io.html#io.BytesIO), or you can do in-place concatenation with a [`bytearray`](https://docs.python.org/3/library/stdtypes.html#bytearray) object. [`bytearray`](https://docs.python.org/3/library/stdtypes.html#bytearray) objects are mutable and have an efficient overallocation mechanism
   - if concatenating [`tuple`](https://docs.python.org/3/library/stdtypes.html#tuple) objects, extend a [`list`](https://docs.python.org/3/library/stdtypes.html#list) instead
   - for other types, investigate the relevant class documentation

7. Some sequence types (such as [`range`](https://docs.python.org/3/library/stdtypes.html#range)) only support item sequences that follow specific patterns, and hence don’t support sequence concatenation or repetition.

8. `index` raises [`ValueError`](https://docs.python.org/3/library/exceptions.html#ValueError) when *x* is not found in *s*. Not all implementations support passing the additional arguments *i* and *j*. These arguments allow efficient searching of subsections of the sequence. Passing the extra arguments is roughly equivalent to using `s[i:j].index(x)`, only without copying any data and with the returned index being relative to the start of the sequence rather than the start of the slice.

mutable sequence type's operations

| Operation                                    | Result                                                       | Notes |
| -------------------------------------------- | ------------------------------------------------------------ | ----- |
| `s[i] = x`                                   | item *i* of *s* is replaced by *x*                           |       |
| `s[i:j] = t`                                 | slice of *s* from *i* to *j* is replaced by the contents of the iterable *t* |       |
| `del s[i:j]`                                 | same as `s[i:j] = []`                                        |       |
| `s[i:j:k] = t`                               | the elements of `s[i:j:k]` are replaced by those of *t*      | (1)   |
| `del s[i:j:k]`                               | removes the elements of `s[i:j:k]` from the list             |       |
| `s.append(x)`                                | appends *x* to the end of the sequence (same as `s[len(s):len(s)] = [x]`) |       |
| `s.clear()`                                  | removes all items from `s` (same as `del s[:]`)              | (5)   |
| `s.copy()`                                   | creates a shallow copy of `s` (same as `s[:]`)               | (5)   |
| `s.extend(t)` or `s += t`                    | extends *s* with the contents of *t* (for the most part the same as `s[len(s):len(s)]= t`) |       |
| `s *= n`                                     | updates *s* with its contents repeated *n*times              | (6)   |
| `s.insert(i, x)`                             | inserts *x* into *s* at the index given by *i*(same as `s[i:i] = [x]`) |       |
| `s.pop([i])`                                 | retrieves the item at *i* and also removes it from *s*       | (2)   |
| `s.remove(x)`                                | remove the first item from *s* where `s[i]` is equal to *x*  | (3)   |
| `s.reverse()`                                | reverses the items of *s* **in place**                       | (4)   |
| sorted(iterable, *, key=None, reverse=False) | f返回一个已有列表中的元素已经排序过的列表，key指定一个函数，参数是列表元素，返回一个可用于比较的东西。reverse 自解释。内置的sorted函数排序是稳定的！！ |       |
| s.sort(key=None, reverse= False)             | Sort the items of the list in place (the arguments can be used for sort customization, see [`sorted()`](https://docs.python.org/3/library/functions.html#sorted) for their explanation). |       |

## set/frozenset

`集合`对象是无序可哈对象的集合。常见用法有成员测试，移除序列中重复元素以及计算数学中的操作：求交(intersection &)，求并(union |)，求差(difference -)和symmetric difference(^).

A *set* object is an unordered collection of distinct [hashable](https://docs.python.org/3/glossary.html#term-hashable) objects. Common uses include membership testing, removing duplicates from a sequence, and computing mathematical operations such as intersection, union, difference, and symmetric difference.  

Like other collections, sets support `x in set`, `len(set)`, and `for x in set`. Being an unordered collection, sets do not record element position or order of insertion. Accordingly, sets do not support indexing, slicing, or other sequence-like behaviour. 

There are currently two built-in set types, [`set`](https://docs.python.org/3/library/stdtypes.html#set) and [`frozenset`](https://docs.python.org/3/library/stdtypes.html#frozenset). The [`set`](https://docs.python.org/3/library/stdtypes.html#set) type is mutable — the contents can be changed using methods like `add()` and `remove()`. Since it is mutable, it has no hash value and cannot be used as either a dictionary key or as an element of another set. The [`frozenset`](https://docs.python.org/3/library/stdtypes.html#frozenset) type is immutable and [hashable](https://docs.python.org/3/glossary.html#term-hashable) — its contents cannot be altered after it is created; it can therefore be used as a dictionary key or as an element of another set.

Non-empty sets (not frozensets) can be created by placing a comma-separated list of elements within braces, for example: `{'jack', 'sjoerd'}`, in addition to the [`set`](https://docs.python.org/3/library/stdtypes.html#set) constructor.

Instances of [`Set`](https://docs.python.org/2/library/sets.html#sets.Set) and [`ImmutableSet`](https://docs.python.org/2/library/sets.html#sets.ImmutableSet) both provide the following operations:

| Operation                   | Equivalent | Result                                                  |
| --------------------------- | ---------- | ------------------------------------------------------- |
| `len(s)`                    |            | number of elements in set *s* (cardinality)             |
| `x in s`                    |            | test *x* for membership in *s*                          |
| `x not in s`                |            | test *x* for non-membership in *s*                      |
| `s.issubset(t)`             | `s <= t`   | test whether every element in *s* is in *t*             |
| `s.issuperset(t)`           | `s >= t`   | test whether every element in *t* is in *s*             |
| `s.union(t)`                | `s | t`    | new set with elements from both *s* and *t*             |
| `s.intersection(t)`         | `s & t`    | new set with elements common to *s* and *t*             |
| `s.difference(t)`           | `s - t`    | new set with elements in *s* but not in *t*             |
| `s.symmetric_difference(t)` | `s ^ t`    | new set with elements in either *s* or *t* but not both |
| `s.copy()`                  |            | new set with a shallow copy of *s*                      |

The following table lists operations available in [`Set`](https://docs.python.org/2/library/sets.html#sets.Set) but not found in [`ImmutableSet`](https://docs.python.org/2/library/sets.html#sets.ImmutableSet):

| Operation                          | Equivalent  | Result                                                       |
| :--------------------------------- | ----------- | ------------------------------------------------------------ |
| `s.update(t)`                      | *s* \|= *t* | return set *s* with elements added from *t*                  |
| `s.intersection_update(t)`         | *s* &= *t*  | return set *s* keeping only elements also found in *t*       |
| `s.difference_update(t)`           | *s* -= *t*  | return set *s* after removing elements found in *t*          |
| `s.symmetric_difference_update(t)` | *s* ^= *t*  | return set *s* with elements from *s* or *t* but not both    |
| `s.add(x)`                         |             | add element *x* to set *s*                                   |
| `s.remove(x)`                      |             | remove *x* from set *s*; raises [`KeyError`](https://docs.python.org/2/library/exceptions.html#exceptions.KeyError) if not present |
| `s.discard(x)`                     |             | removes *x* from set *s* if present                          |
| `s.pop()`                          |             | remove and return an arbitrary element from *s*; raises [`KeyError`](https://docs.python.org/2/library/exceptions.html#exceptions.KeyError) if empty |
| `s.clear()`                        |             | remove all elements from set *s*                             |

Note, the non-operator versions of `update()`, `intersection_update()`, `difference_update()`, and `symmetric_difference_update()` will accept any iterable as an argument.

useful links: https://docs.python.org/3/library/stdtypes.html#typesseq-common

https://docs.python.org/3/reference/expressions.html#yield-expressions

## [String](https://docs.python.org/3/library/string.html?highlight=string#module-string)

Strings implement all of the [common](https://docs.python.org/3/library/stdtypes.html#typesseq-common) sequence operations, along with the additional methods described below.

Strings also support two styles of string formatting, one providing a large degree of flexibility and customization (see [`str.format()`](https://docs.python.org/3/library/stdtypes.html#str.format), [Format String Syntax](https://docs.python.org/3/library/string.html#formatstrings) and [Custom String Formatting](https://docs.python.org/3/library/string.html#string-formatting)) and the other based on C `printf` style formatting that handles a narrower range of types and is slightly harder to use correctly, but is often faster for the cases it can handle ([printf-style String Formatting](https://docs.python.org/3/library/stdtypes.html#old-string-formatting)).

The [Text Processing Services](https://docs.python.org/3/library/text.html#textservices) section of the standard library covers a number of other modules that provide various text related utilities (including regular expression support in the [`re`](https://docs.python.org/3/library/re.html#module-re) module).

**Infinite iterators:**

| Iterator                                                     | Arguments     | Results                                        | Example                                 |
| ------------------------------------------------------------ | ------------- | ---------------------------------------------- | --------------------------------------- |
| [`count()`](https://docs.python.org/3/library/itertools.html#itertools.count) | start, [step] | start, start+step, start+2*step, …             | `count(10) --> 10 11 12 13 14...`       |
| [`cycle()`](https://docs.python.org/3/library/itertools.html#itertools.cycle) | p             | p0, p1, … plast, p0, p1, …                     | `cycle('ABCD') --> A B C D A B C D ...` |
| [`repeat()`](https://docs.python.org/3/library/itertools.html#itertools.repeat) | elem [,n]     | elem, elem, elem, … endlessly or up to n times | `repeat(10, 3) --> 10 10 10`            |

**Iterators terminating on the shortest input sequence:**

| Iterator                                                     | Arguments                   | Results                                    | Example                                                   |
| ------------------------------------------------------------ | --------------------------- | ------------------------------------------ | --------------------------------------------------------- |
| [`accumulate()`](https://docs.python.org/3/library/itertools.html#itertools.accumulate) | p [,func]                   | p0, p0+p1, p0+p1+p2, …                     | `accumulate([1,2,3,4,5]) --> 1 3 610 15`                  |
| [`chain()`](https://docs.python.org/3/library/itertools.html#itertools.chain) | p, q, …                     | p0, p1, … plast, q0, q1, …                 | `chain('ABC', 'DEF') --> A B C D EF`                      |
| [`chain.from_iterable()`](https://docs.python.org/3/library/itertools.html#itertools.chain.from_iterable) | iterable                    | p0, p1, … plast, q0, q1, …                 | `chain.from_iterable(['ABC','DEF']) --> A B C D E F`      |
| [`compress()`](https://docs.python.org/3/library/itertools.html#itertools.compress) | data, selectors             | (d[0] if s[0]), (d[1] if s[1]), …          | `compress('ABCDEF', [1,0,1,0,1,1])--> A C E F`            |
| [`dropwhile()`](https://docs.python.org/3/library/itertools.html#itertools.dropwhile) | pred, seq                   | seq[n], seq[n+1], starting when pred fails | `dropwhile(lambda x: x<5,[1,4,6,4,1]) --> 6 4 1`          |
| [`filterfalse()`](https://docs.python.org/3/library/itertools.html#itertools.filterfalse) | pred, seq                   | elements of seq where pred(elem) is false  | `filterfalse(lambda x: x%2,range(10)) --> 0 2 4 6 8`      |
| [`groupby()`](https://docs.python.org/3/library/itertools.html#itertools.groupby) | iterable[, key]             | sub-iterators grouped by value of key(v)   |                                                           |
| [`islice()`](https://docs.python.org/3/library/itertools.html#itertools.islice) | seq, [start,] stop [, step] | elements from seq[start:stop:step]         | `islice('ABCDEFG', 2, None) --> CD E F G`                 |
| [`starmap()`](https://docs.python.org/3/library/itertools.html#itertools.starmap) | func, seq                   | func(*seq[0]), func(*seq[1]), …            | `starmap(pow, [(2,5), (3,2),(10,3)]) --> 32 9 1000`       |
| [`takewhile()`](https://docs.python.org/3/library/itertools.html#itertools.takewhile) | pred, seq                   | seq[0], seq[1], until pred fails           | `takewhile(lambda x: x<5,[1,4,6,4,1]) --> 1 4`            |
| [`tee()`](https://docs.python.org/3/library/itertools.html#itertools.tee) | it, n                       | it1, it2, … itn splits one iterator into n |                                                           |
| [`zip_longest()`](https://docs.python.org/3/library/itertools.html#itertools.zip_longest) | p, q, …                     | (p[0], q[0]), (p[1], q[1]), …              | `zip_longest('ABCD', 'xy',fillvalue='-') --> Ax By C- D-` |

**Combinatoric iterators:**

| Iterator                                                     | Arguments          | Results                                                      |
| ------------------------------------------------------------ | ------------------ | ------------------------------------------------------------ |
| [`product()`](https://docs.python.org/3/library/itertools.html#itertools.product) | p, q, … [repeat=1] | cartesian product, equivalent to a nested for-loop           |
| [`permutations()`](https://docs.python.org/3/library/itertools.html#itertools.permutations) | p[, r]             | r-length tuples, all possible orderings, no repeated elements |
| [`combinations()`](https://docs.python.org/3/library/itertools.html#itertools.combinations) | p, r               | r-length tuples, in sorted order, no repeated elements       |
| [`combinations_with_replacement()`](https://docs.python.org/3/library/itertools.html#itertools.combinations_with_replacement) | p, r               | r-length tuples, in sorted order, with repeated elements     |
| `product('ABCD', repeat=2)`                                  |                    | `AA AB AC AD BA BB BC BD CA CB CC CD DA DB DCDD`             |
| `permutations('ABCD', 2)`                                    |                    | `AB AC AD BA BC BD CA CB CD DA DB DC`                        |
| `combinations('ABCD', 2)`                                    |                    | `AB AC AD BC BD CD`                                          |
| `combinations_with_replacement('ABCD',2)`                    |                    | `AA AB AC AD BB BC BD CC CD DD`                              |

```python
from itertools import dropwhile
# drop starting elements of a generator until 'predict function' returns False.
# takewhile: take elements of a iterator unitil 'predict function' returns False. "predict function" will evaluate every element.More refer "Python 4 Adavenced Python v2.pdf" P77

l = [0, 1, 2, 3, 4, 5]

def pred(x):
    if x<3:
        return True
    return False
dw = dropwhile(pred, l)

print(next(dw))

for i in dw:
    print(i, end=" ")
```


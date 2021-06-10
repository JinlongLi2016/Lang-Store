# heapq (堆 队列算法)

heapq模块提供了堆的实现（又被称为优先队列）。这里的堆是小根堆，并且下标从0开始。

1) 下标从0开始

1）pop方法返回最小的的元素

因此可以将heapq视为普通的列表，heap[0] 是最小的元素，heap.sort()维持堆的有序性。

- `heapq.``heappush`(*heap*, *item*)

  在堆中插入元素item，并且维持堆的有序性。Push the value *item* onto the *heap*, maintaining the heap invariant.

- `heapq.``heappop`(*heap*)

  从堆中弹出元素并且维持堆的有序性。若无元素抛出IndexErrorPop and return the smallest item from the *heap*, maintaining the heap invariant. If the heap is empty, [`IndexError`](https://docs.python.org/3.0/library/exceptions.html#exceptions.IndexError) is raised.

- `heapq.``heappushpop`(*heap*, *item*)

  在堆中插入item再弹出最小元素，比单独的push再pop更高效。Push *item* on the heap, then pop and return the smallest item from the *heap*. The combined action runs more efficiently than [`heappush()`](https://docs.python.org/3.0/library/heapq.html#heapq.heappush) followed by a separate call to [`heappop()`](https://docs.python.org/3.0/library/heapq.html#heapq.heappop).

- `heapq.``heapify`(*x*)

  把列表在线性时间内转换为堆（原地）Transform list *x* into a heap, in-place, in linear time.

- `heapq.``heapreplace`(*heap*, *item*)

  弹出最小元素再插入item。如果堆为空怎会爆出IndexError. Pop and return the smallest item from the *heap*, and also push the new *item*. The heap size doesn’t change. If the heap is empty, [`IndexError`](https://docs.python.org/3.0/library/exceptions.html#exceptions.IndexError) is raised. This is more efficient than [`heappop()`](https://docs.python.org/3.0/library/heapq.html#heapq.heappop) followed by [`heappush()`](https://docs.python.org/3.0/library/heapq.html#heapq.heappush), and can be more appropriate when using a fixed-size heap. Note that the value returned may be larger than *item*! That constrains reasonable uses of this routine unless written as part of a conditional replacement:

  ```python
  if item > heap[0]:
      item = heapreplace(heap, item)
  ```

  Example of use

  ```python
  from heapq import heappush, heappop
  heap = []
  data = [1, 3, 5, 7, 9, 2]
  for item in data:
      heappush(heap, item) # 压栈
  ordered = []
  while heap:
      ordered.append(heappop(heap))
  data.sort()
  data == ordered
  ```

    ```
    from heapq import heappush, heappop, heapify
    heap = [1, 3, 5, 7, 9]
    heapify(heap)

    ordered = []
    while heap:
        ordered.append(heappop(heap))

    heap.sort()
    heap = ordered
    ```


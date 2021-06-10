# Thread

Lesson Objectives:

* synchronize threads
* access the Queue Standard Library



## Thread Synchronization

**threading.Lock 对象**

**锁**对象有两种状态：__被锁 /释放__ ，它在**释放**状态下被创建。

当线程获取与某种特定的__锁__有关的**资源**时，线程会调用__锁__的`acquire()` 方法。若__锁__处于上锁状态，则线程则被阻塞直到锁被释放并被允许获取。若__锁__被释放，会立刻被__上锁__并被获取(Amos:因为有线程`acquire()`它)。

调用__锁__对象的`release()`方法会释放锁。

```python
import threading
import time

class MyThread(threading.Thread):
    def __init__(self, lock, *args, **kw):
        threading.Thread.__init__(self, *args, **kw)#显式调用父类__init__方法
        self.lock = lock # 
    def run(self):
        for i in range(10):
            self.lock.acquire()
            time.sleep(0.1)
            self.lock.release()
        print(self.name, "finished")
        
lock = threading.Lock()
bgthreads = threading.active_count()
tt = [MyThread(lock) for i in range(6)]
for t in tt:
    t.start()
print("Threads started")
while threading.active_count() > bgthreads:
    time.sleep(2)
    print("tick")
print("All threads done")
```





## The Queue Standard Library

The library was produced to provide programmers of threaded program with a  safe way for their threads information.**queue**库定义了**三个**类，它们的接口大致一致。`queue.Queue`是FIFO队列.This is the most usual type to use for handing out work to worker threads. `queue.LifoQueue` `queue.PriorityQueue`的元素总是按照natural sort order出列。

创建队列时可以指定 *最大长度* 参数，如果未指定则默认为无限长。如果指定了长度，there are only a given number of free slots, 尝试向**满队列**中添加元素将造成**阻塞**或者**抛出异常**(Or Both)。库保证的线程安全意味着多线程可以访问同一个队列而无需用*锁* 锁住队列。从**空队列**中获取元素将造成**阻塞**或者**抛出异常**(Or Both)。 

此处我们只最简单地使用队列，使用它的`put()`和`get()`方法进而展示一种写可扩展线程编程地方式。理解了基础，通过阅读模块文档就可以做出许多改进。在线程相关应用中，简单的时最好的，因为我们太笨以致于无法处理多线程之间的影响（例如死锁，Thread A is locked as waiting for B, while B is blocked waiting for A）。




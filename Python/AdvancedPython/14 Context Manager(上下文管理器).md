# Context Manager(上下文管理器)

## Lesson Objectives

这一部分介绍

* 使用一个新的控制结构:`with` 语法
* 使用Decimal算术和算术语境

## 控制结构：`With` 语句

`with`语句让你可以在一个缩进中创建/使用某些资源并在结束后自动释放这些资源。基本语法为：

```python
with object1 [as name1][, object2 [as name2]] ...:
    [indented suite]
```

`object`即为上下文管理器，如果`indented suit`需要使用`object`,可以在`as`从句中将他们命名（无须则可以忽略）。现在，files都是语境管理器了，可以使用它们而无需显示将他们关闭。



`with`时一种控制[indented suite]中代码执行环境的方式。

我们可以打开文件然后赋值给一个变量，但是利用with，我们可以确保[indented suite]中无论发生什么，文件都会被关闭（和try-finally 中的finally类似）。



## 语境管理器协议 ：`__enter__()` and `__exit__()`

`with`语句按照规定和语境管理器交互。它运行 **with expr** 然后保存得到的语境管理器对象。然后调用**语境管理器**的`__enter__()`方法，如果有`as name`语句，那么`__enter__()`方法返回会被绑定到`name`上。没有`as name`语句，那么结果就无法获得。最后，执行缩进代码。

缩进代码执行中若抛出代码，那么缩进执行结束转而调用CM(short for 'context manager')的`__exit__()`方法，同时传递描述**异常原因及位置**的三个参数。正常结束也会调用CM的`__exit__()`方法，但三个参数均为**None** 。

There are other ways that the with suite can be exited, all fairly normal -- how many ways can you think of? In those circumstances, the context manager's `__exit__()`method is called with three **None** arguments, and then the normal exit is taken.

The reason for the name "context manager" is that the indented suite in a with statement is surrounded by calls to the manager's `__enter__()` and `__exit__()` methods, which can therefore provide some context to the execution of the suite. Note carefully that the `__exit__()` method is always called—even when the suite raises an exception 。

## *语境管理器* 类   

As is often the case in Python, it's quite easy to write a class that demonstrates exactly how the context manager objects work with the interpreter as it executes the with statement. Since there are two alternative strategies for handling the raising of an exception in the indented suite, an `__init__`() method can record in an instance variable which strategy the creator (the code calling the class) chooses. If no exception is raised, this will make no difference.    Besides the very simple `__init__()` outlined (which is not itself a part of the context manager protocol), you just need the `__enter__() `and `__exit__() `methods.     

```python
class ctx_mgr:
    def __init__(self, raising):
        print("Created a new ctx manager")
        self.raising = raising
    def __enter__(self):
        print("__enter__ called")
        cm = object()
        print("__enter__ returning object id:", id(cm))
        return cm
   	def __exit__(self, exc_type, exc_val, exc_tab):
        print("__exit__ called")
        if exc_type:
            print("An exception occured")
            if self.raising:
                print("Re-raising exception")
          	return not self.raisings
```



```python
>>> with ctx_mgr(raising=True) as cm:
... print("cm ID:", id(cm))
...
Created new context manager object 4300642640
__enter__ called
__enter__ returning object id: 4300469808
cm ID: 4300469808
__exit__ called
>>> with ctx_mgr(raising=False):
... 3/0
...
Created new context manager object 4300642768
__enter__ called
__enter__ returning object id: 4300469904
__exit__ called
An exception occurred
>>> with ctx_mgr(raising=True) as cm:
... 3/0
...
Created new context manager object 4300642640
__enter__ called
__enter__ returning object id: 4300469744
__exit__ called
An exception occurred
Re-raising exception
Traceback (most recent call last):
File "<console>", line 2, in <module>
ZeroDivisionError: division by zero
>>>
```

第一个例子：语境管理器返回的对象与`__enter__()`方法返回的不同。缩进中的`print()`语句说明了变量**cm**是绑定到`__enter__()`方法返回结果上而非语境管理器本身。(The file open() example earlier is atypical, as a file object's __enter__() method returns self )   。无异常抛出，因此`__exit__()`方法简单地说明它已经被调用。

第二个例子在不抛出异常的语境管理器语义中，缩进代码抛出异常。所以它reports the fact that an exception was raised, 但还是正常结束了（返回`True` for terminating normally）。

第三个例子返回`False`，re-raising exception.

## 语境管理器的库支持 Library Support for Context Managers

虽然写语境管理器类很简单，但是使用**contextlib**库将会更加简单。它包括了一个`contextmanager`的装饰器，可以用来非常简单地构建语境管理器。再也不用去声明一个有`__enter__()`和`__exit__()`的类了。

将`contextlib.contextmanager`装饰器应用在一个包含且仅包含一个`yield`的生成器上。当生成器应用在**`with`**语句中，生成器的**`next`**方法被调用，函数体就运行到`yield`。生成得到值作为语境管理器的`__enter__()`方法返回的值并返回，接着缩进代码开始运行。

若缩进代码抛出异常，异常会出现在语境管理器内部，作为`yield`抛出的异常。Your context manager can choose to handle the exception (by processing the yield as part of the indented suite of a try statement) or not (in which case the exception must be re-raised after logging or other actions if the surrounding logic is to see it). So your context manager **can trap exceptions** raised by the indented suite and **suppress** them simply by choosing not to re-raise them.    

```python
>>> from contextlib import contextmanager
>>> @contextmanager
... def ctx_man(raising=False):
... try:
    ... cm = object()
    ... print("Context manager returns:", id(cm))
    ... yield cm
    ... print("With concluded normally")
... except Exception as e:
... print("Exception", e, "raised")
... if raising:
... print("Re-raising exception")
... raise
...
>>> with ctx_man() as cm:
... print("cm from __enter__():", id(cm))
...
Context manager returns: 4300470512
cm from __enter__(): 4300470512
With concluded normally
>>> with ctx_man(False) as cm:
... 3/0
...
Context manager returns: 4300801264
Exception division by zero raised
>>> with ctx_man(True) as cm:
... 3/0
...
Context manager returns: 4300801280
Exception division by zero raised
Re-raising exception
Traceback (most recent call last):
File "<console>", line 2, in <module>
ZeroDivisionError: division by zero
>>>
```

This interactive session shows that it is possible to create equivalent context managers using this approach. The same parameterization of the functionality is provided (so you can say when creating the context manager whether or not it should re-raise exceptions). ` contextlib.contextmanager `provides a nice compromise between writing a full context manager and using older, less well-controlled methods (such as try ... except ... finally) of controlling the execution context. You will find that the other members of the context lib library can also be useful in creating and supporting context managers.    

## 嵌入语境管理器 Nested Context Managers

```python
with expr1 as name1, expr2 as name2:
    [indented suite]
    
is equivalent to:

with expr1 as name1:
    with expr2 as name2:
        [indented suite]
```

This shows that the expr1 context wraps the name2 context. If an exception occurs in the indented suite, it will present as a call to `expr2.__exit__() `with the necessary exception-related arguments. As always, the `__exit__() `method has the choice of returning True (which suppresses the exception, resulting in a call to expr1.`__exit __() `with three No ne arguments) or False, in which case the exception is automatically re-raised and `expr1.__exit __() `is called with the traceback arguments. It also has the choice of returning True to suppress the exception or False to re-raise it a second time. The multi-context form of the with statement is a simple syntactic convenience; no new functionality is introduced, but it does reduce the indentation level required for the indented suite. This enhances readability without compromising simplicity.    

## Decimal Signals 双精度信号

...


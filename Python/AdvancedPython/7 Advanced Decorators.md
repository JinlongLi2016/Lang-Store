# Advanced Uses of Decorators    

**Lesson Objectives**

* 使用装饰器use decorator syntax
* 使用装饰器类use Classes as Decorators
* 使用类装饰器(a decorator to decorate class['s' methods])use Class Decorators
* 利用一些odd的装饰器技巧employ some odd Decorator tricks
* 使用类静态方法和类方法utilize Static and Class Method Decorators
* parameterize Decorators

## decorator syntax

```python
def trace(func):
    def traced(*args, **kw):
        print("Entering", f.__name__)
        result = func(*args, **kw)
        print("Exiting", f.__name__)
        return result
    return traced

@trace
def func():
    pass
func = decorator(func)
```

The decorator takes as a single argument the to be decorated function `func` and returns a decorated function `tranced` . Then assigns `traced` to the original function variable `func`. 

 **Note**:`@trace` is exactly equivalent to writing `func = trace(func)`.

Because the decorator contains a call to the decorated function,  the decorator wraps the function.There are side effects: the decorated function's name and docstring are missed.This can be addressed using decorator  `functools'  wraps`. 这可以精确地确保函数看起来依旧没有改变（对于调试器及一些需要内省inspection的程序而言，important）。

```python
from functools import wraps
def simpledec(f):
    @warps(f)
    def wrapper(arg):
        print("Calling f with arg", arg)
        return f(arg)
    # wrapper = wraps(f)(wrapper)
    return wrapper
@simpledec
def f(x):
    print("Inside f, arg is", x)
```



## Classes as Decorators

尽管常见的decorators是函数，但实际上任何可调用的对象`callable`都可以是装饰器.这意味着可以使用__类__来作为装饰器。Great。在类的`__init__()`方法中装饰object(可以是函数/类，注意装饰器要么装饰函数/类，因为它们有本质的不同（amos：即第一个参数是否为实例本身）).

如果用类来装饰函数，那么调用类就是调用`__init__`方法，返回的是类的一个实例。`__init__()`的第一个参数是`self`, the newly created instance。同时类也应该定义`__call__` 方法以实现返回的实例调用。

```python
class ctrace:
    def __init__(self, f):
        self.__doc__ = f.__doc__
        self.__name__ = f.__name__
        self.f = f
    def __call__(self, **args, **kw):
        print("Called ", self.f.__name)
        return self.f(*args, **kw)
    
@ctrance
def simple(x):
    pass
```



# Class Decorators 类装饰器（装饰类的装饰器）

Once the functions was introduced into Python, it was only a matter of time before it was extended to classes.所以我们该如何装饰类呢？和装饰函数一样：装饰器接受一个类作为参数，返回(usually)一个类。鉴于类远比函数复杂，我们会发现最好we will find it most convenient to modify the class in place and return the modified class as the result of the decorator.

**Note**: Decorators can be applied individually to the methods of a class. Essentially they are the same as functions, and so exactly the same techniques can be used with methods as with regular functions.    

To demonstrate this, suppose that you want to be able to have each of the methods of a class print out a trace call during debugging. You could simply apply the trace decorator above to each method, but that would mean extensive editing for a large class when you wanted to switch the debugging off. It is simpler for programmers to use **a class decorator**, so we might well accept a slightly higher level of complexity in the decorator to avoid the editing.  Once the interpreter has processed the class definition, it calls the decorator with the class as its argument, and the decorator can then either create a new class (which is fairly difficult) or modify the class and return it.    

Finding the methods is not as easy as you might imagine. It involves looking through the class's ` __dict__` and finding callable items whose names do __not__ begin and end with "__ "  (it's best not to mess with the "magic" methods). Once such an item is found,it is wrapped **with the trace()** function and **replaced** in the class `__dict__` .

```python
# 写一个装饰器，装饰类中magic的函数
```

**Note:**类的`__dict__`与实例的不同，它并非我们熟悉的`dict`，实际上是一个`dict_proxy`对象。为了让它们尽可能轻巧，它们不支持直接地元素赋值。这也是为什么我们用内建的`setattr()`来代替原始版本代码。

The` __dict__` of a class (as opposed to that of an instance) isn't a plain dict like the ones you know. It is actually an object called a dict_proxy. To keep them as lightweight as possible, they do not **directly support item assignment** like a standard dict does. This is why, in the `mtrace()` function, the wrapped method replaces the original version by using the `setattr()` built-in function.    



## Odd Decorator Tricks

Sometimes you don't want to wrap the function: instead you want to alter it in some other way, such as adding attributes (yes, you can add attributes to functions the same way as you can to most of the other objects in Python). In that case, the decorator simply returns the function that is passed in as an argument, having modified the function in whatever ways it needs to. So next we'll write a decorator that flags a function as part of a framework by adding a "framework" attribute.    



## Static and Class Method Decorators

Python 包含了两种用以装饰方法的内建函数:`@staticmethod`&`@classmethod`:

`@staticmethod`修改了方法：不需要提供实例本身作为第一个参数。**静态方法可以通过类或者实例调用**，并且只接受列出来的参数（不接受第一个`self参数`），这样它就变成了静态方法。可以理解静态方法为不需要从类/实例接受任何信息的函数。

如果想让方法使用类中的数据但和实例无关，那么可以用`@classmethod`来装饰方法。和静态方法一样，**类方法可以通过类或者实例调用**。有别的是，类方法调用接收隐式的第一个参数。和普通的方法调用**不**一样，**类方法调用接受的第一个参数是实例的类`cls`而非实例**。

You may well ask what static and class methods are for—why use them when we already have standard methods that are perfectly satisfactory for most purposes? Why not just use functions instead of static methods, since no additional arguments are provided? The answer to this question lies in the fact that these functions are methods of a class, and so will be **inherited(and can be overridden or extended)**  by any subclasses you may define. Further, the instances of the class can reference class variables rather than using a global—this is always safer because there is no guarantee, when your code lands in someone else's program, that their code isn't using the same global name for some other purpose. It is difficult to think of any example where the use of a `classmethod` would be absolutely required, but sometimes it can simplify your design a little.    

A typical application for class methods has each of the instances using configuration data that is common to all, and saved in the class. If you provide methods to alter the configuration data (for example, changing the frequency a wireless transmitter works on, or changing the function that the instances call to allocate resources), they do not need to reference any of the instances, so a class method would be ideal.    



## Parameterized Decorators 参数化装饰器

我们可能需要装饰器接收参数。😄，How to do that?

Sometimes you want to write a decorator that takes parameters. Remember, though, that the decorator syntax requires a callable that takes precisely one argument (the class or function to be decorated). So if you want to parameterize a decorator, you have to do so "at one remove"—the function that takes the arguments has to return a function that takes one argument and returns the decorated object. This can be a little brain-twisting, so an example may help. Or, it may just make your head explode!    

Suppose that you wanted to have your program record the number of calls that are made to each of several different types of function. When you define a function, you want to give a parameter to the decorator to specify the classification of the decorated function.    

```python
@countable('special')
def f(...):
    ...
   
```

In other words, @countable('special') has to return a function that is a conventional decorator—it takes a single function as an argument and returns the decorated version of the function as its result. This means that we need to nest functions three levels deep! We will use a global variable to store a dict, and the different function-type strings will be the keys. Here we go!    


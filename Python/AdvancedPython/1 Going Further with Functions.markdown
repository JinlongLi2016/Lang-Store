# Going Further with functions 函数也是对象
Python里的所有东西都是对象，函数也不例外。但和其他对象不同，函数不是由调用类生成的，而是由def 语句，告诉编译器来


## 函数属性  

和Python里的其他对象一样，函数也有一个具体的类型`(type)`。你可以利用`dir()`检查函数的命名空间(`namesapce`).

## 函数和方法调用

在函数的命名空间中可检查到`__call__`方法。从名字上就可以看出这个方法与函数调用有关。Python解释器通过调用可调用对象(`callable`)的`__call__`方法来完成调用。实际上，我们可以直接调用可调用对象`callable`的该方法来完成调用。

```python
>>>def f1(x):
    # do something
>>> f1.__call__(x)
```

我们也可以自己定义包含``__call__``方法的类。如此，该类的实例都可以被直接调用（像函数一样调用）。实际上，这是Python的一种机制，即：

```python
f(*args, **kargs) == f.__call__(*args, **kargs)
```

我们来试试

```python
class Func:
    def __call__(self, arg):
        print("%r(%r) called" % (self, arg))
        return arg
>>f2 = Func()
>>f2
<__main__.Func object at 0x234234>
>>f2("danny")
<__main__.Func object at 0x234234>('Danny') called
'Danny'
>>
```

可以看出，当我们在**类中定义了``__call__``方法**，它的实例就可以被调用。（Amos题外话，Python里面在object后跟上()表示对object的调用，跟上[]，表示get  object's attributes[待议] ）这些调用导致类中`__call__`方法被调用，**实例本身作为第一个变量**，紧接着实例调用时的位置参数和关键字参数。方法一般被定义在类中。当然，我们也可以在实例的命名空间中绑定可调用对象`callable` ，但解释器并不会认为这是一个真正的方法，因而不会将实例本身作为第一个参数。因此，实例字典`__dict__`中的可调用对象`__callable__` 接收的参数**只有实例调用时的那些参数（实例本身并不会作为第一个参数）**。  

NOTE:

以**双下划线开始和结束**的方法永远不会在实例里面被查询，解释器会直接到类中去查询这些方法。因此尽管实例字典`__dict__`中有键`__call__`，它也会被忽略而去调用类的`__call__`方法。

接着前面的Python会话：

```python
>>> def userfunc(arg):
... print("Userfunc called: ", arg)
...
>>> f2.regular = userfunc
>>> f2.regular("Instance")
Userfunc called: Instance
>>> f2.__call__ = userfunc
>>> f2("Hopeful")
<__main__.Func object at 0x100569dd0>('Hopeful') called
'Hopeful'
```

Instance's 'magic' method was ignored.

既然所有的可调用对象有`__call__`方法，`__call__` 方法也是可调用的，那我们会怀疑它本身是否也含有`__call__`方法。答案是肯定的。

```python
f2.__call__.__call__("Andrey")
```





## 函数组合

因为函数是一级对象`first-class` ,他们可以作为函数的参数。假设$f$ 、$g$ 是两个函数，数学家定义了一种组合运算：$f*g$ ，即$f(g(x))$ 。换句话说，组合两个函数为一个新的函数，其效果就是将第二个函数的输出作为第一个函数的输入。

如果给定了两个函数，我们能否构造出他们的组合呢？当然可以，我们可以写一个组装函数，以这两个函数为参数，在函数内部完成新函数的功能。然后组装函数返回这个组合函数。

```python
def compose(g, h):
    def anon(x):
        return g(h(x))
   	return anon
```

尽管这样做能够非常直接地将两个函数组合起来，但对数学家而言，用星号*将两个函数组合起来才比较自然。然而，尝试函数相乘注定失败，因为Python没有设计两个函数相乘。如果我们为函数添加一个`__mul__`方法，或许我们还有点机会。但是对函数实例而言不可能，因为函数类是C写的内建对象：**不可能更改、很难被继承**。Even when you do subclass the function type, how could you create instances? The def statement will always create regular functions.

While you may not be able to subclass the function object, you do know how to create object classes with callable instances. Using this technique, you could create a class with instances that act as proxies for the functions. This class could define a `__mul__()` method, which would take another similar class as an argument and return the composition of the two proxied functions. This is typical of the way that Python allows you to "hook" into its workings to achieve a result that is simpler to use.    

```python
class Composable:
	def __init__(self, f):
		self.func = f 

	def __call__(self, *args, **kwargs):
		return self.func(*args, **kwargs)

	def __mul__(self, other):
		return self(other(x)) # 
		if type(other) is Composable:
			def anon(x):
				return self.func(other.func(x))
			# return Composable(anon)
		raise TypeError("Illigal operands for multiplication")

	def __rep__(self):
		return "<Composable function {0} at 0x{1:X}>".format(
			self.func.__name__, id(self))
```

An alternative implementation of the  `__mul__()`  method might have used the statement` return self(other(x))`. Do you think that this would have been a better implementation? Why or why not?    

> 这不是一个好的实现方式。
>
> 假设以$f*g(x)$的方式调用。所给的方式调用顺序为：以参数$x$调用$g$ ，然后以其输出调用`self`即$f$ ，并将结果返回。除了变量$x$必须要提前预知外，每次调用的时候$f$ 、$g$ 都必须要显示地给出，或者说并没有组合函数$f$、 $g$为一个新的函数C。
>
> 如果以代码块中地方式，$x$不必提前给出，而且获得了一个$f$、 $g$的组合函数C，$f$ 、$g$不再需要了😊。

next coming  module test ...

## λ 匿名函数

Python有一个特性是**允许将简单函数定义为表达式**。*lambda*表达式就是一种无须`def`关键字而描述函数的方式。它作为表达式的特点限制了可以在*lambda*上进行的操作。萝卜青菜，各有所爱。有的人用得多，有的人用得少。理解他们是必要的，因为不知道哪一天会撞见喜欢萝卜的人。

```python
f = lambda x, y: x*y    ===   def f(x, y):	return x*y
```

尽管上面这种等价不完全，但就实际应用理解来说足够了。*lambda*关键字后紧跟着由逗号分开的参数的名字，再接着是表达式。参数和表达式有冒号分开。调用时会返回表达式的值。

```python
>>> def compose(g, h):
    ... def anon(x):
    ... 	return g(h(x))
    ... return anon
...
>>>
>>> add1 = lambda x: x+1
>>> add1
<function <lambda> at 0x100582270>
>>> sqr = lambda x: x*x
>>> sqp1 = compose(sqr, add1)
>>> sqp1(5)
36
>>> type(add1)
<class 'function'>
```

用lambda写出和前面compose()函数相同的功能很容易。最后一行表明对解释器而言，lambda表达式和函数完全等同。（lambda表达式和函数有相同的类型"<class 'function'>"）.

同时，lambda表达式没有名字（或者准确一点，它们有相同的名字）。当以`def`的形式定义函数的时候，解释器会将`def`语句中的名字存储为它的`__name__`属性。所有的lambda表达式在创建的时候有相同的名字：'<lambda>'。虽然可以通过赋值语句来修改这些语句，但一般而言，如果在lambda表达式上花了超过一行的代码，也许你应该写一个具名函数。



最后，记住lambda表达式是故意限制在函数体只有一个表达式的函数。如果多行，不如写成一个具名函数，这样还可以用文档做注释。如果你确实想在多行中继续lambda表达式，最好的方式时用小括号将lambda表达式扩起来。

```python
>>> def f1(x):
    ... print("f1({}) called".format(x))
    ... return x
...
>>> class Func:
    ... def __call__(self, arg):
    ... 	print("%r(%r) called" % (self, arg))
    ... 	return arg
...
>>> f2 = Func()
>>> ff = lambda f, g: lambda x: f(g(x))
>>> lam = ff(f1, f2)
>>> lam("Ebenezer")
<__main__.Func object at 0x10057a510>('Ebenezer') called
f1('Ebenezer') called
'Ebenezer'
>>>
>>> ff = lambda f, g: (lambda x:
... f(g(x)))
>>> lam = ff(f1, f2)
>>> lam("Ebenezer")
<__main__.Func object at 0x10057a510>('Ebenezer') called
f1('Ebenezer') called
'Ebenezer'
>>>
```

> The tools from this lesson will allow you to use callables with greater flexibility and to better purpose. You've learned ways to write code that is able to collaborate with the interpreter and will allow you to accomplish many of your desired programming tasks more efficiently. Nice work!



## Some Small Tips

`(, /) ` '/' means  preceding arguments are position only.

`(, ..., )` ... 
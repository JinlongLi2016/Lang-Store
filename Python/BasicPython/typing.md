# typing

> 注解 Python 运行时并**不强制**标注函数和变量类型。 类型标注可被用于第三方工具，比如类型检查器、集成开发环境、静态检查器等。

此模块为运行时提供了 PEP 484 、 PEP 526 、 PEP 544 、 PEP 586 、 PEP 589 和 PEP 591 规定的类型提示。最基本的支持由 Any，Union，Tuple，Callable，TypeVar 和 Generic 类型组成。有关完整的规范，请参阅 PEP 484。有关类型提示的简单介绍，请参阅 PEP 483。

函数接受并返回一个字符串，注释像下面这样:

def greeting(name: str) -> str:
    return 'Hello ' + name
在函数 greeting 中，参数 name 预期是 str 类型，并且返回 str 类型。子类型允许作为参数。

## alias 类型别名
类型别名通过将类型分配给别名来定义。在这个例子中， Vector 和 List[float] 将被视为可互换的同义词:

```python
from typing import List
Vector = List[float]

def scale(scalar: float, vector: Vector) -> Vector:
    return [scalar * num for num in vector]

# typechecks; a list of floats qualifies as a Vector.
new_vector = scale(2.0, [1.0, -4.2, 5.4])
```
类型别名可用于简化复杂类型签名。例如:
```python
from typing import Dict, Tuple, Sequence

ConnectionOptions = Dict[str, str]
Address = Tuple[str, int]
Server = Tuple[Address, ConnectionOptions]

def broadcast_message(message: str, servers: Sequence[Server]) -> None:
    ...

# The static type checker will treat the previous type signature as
# being exactly equivalent to this one.
def broadcast_message(
        message: str,
        servers: Sequence[Tuple[Tuple[str, int], Dict[str, str]]]) -> None:
    ...
```

请注意，None 作为类型提示是一种特殊情况，并且由 type(None) 取代。

## NewType 新类型
使用`NewType()`辅助函数创建不同的类型. 
```python
from typing import NewType

UserId = NewType('UserId', int)
some_id = UserId(524313)
```
静态类型检查器会将新类型视为它是**原始类型的子类**。这对于帮助捕捉逻辑错误非常有用:

```python
def get_user_name(user_id: UserId) -> str:
    ...

# typechecks
user_a = get_user_name(UserId(42351))

# does not typecheck; an int is not a UserId
user_b = get_user_name(-1)
```


您仍然可以对 UserId 类型的变量执行所有的 int 支持的操作，但结果将始终为 int 类型。这可以让你在需要 int 的地方传入 UserId，但会**阻止你以无效的方式无意中创建 UserId**:

```python
# 'output' is of type 'int', not 'UserId'
output = UserId(23413) + UserId(54341)
```
请注意，这些检查仅通过静态类型检查程序来强制。在运行时，Derived = NewType('Derived'，Base) 将 Derived 一个函数，该函数立即返回您传递它的任何参数。这意味着表达式 Derived(some_value) 不会创建一个新的类或引入任何超出常规函数调用的开销。

更确切地说，表达式 some_value is Derived(some_value) 在运行时总是为真。

这也意味着无法创建 Derived 的子类型，因为它是运行时的标识函数，而不是实际的类型:
```python
from typing import NewType

UserId = NewType('UserId', int)

# Fails at runtime and does not typecheck
class AdminUserId(UserId): pass
```

但是，可以基于'derived' NewType 创建 NewType()

```python
from typing import NewType

UserId = NewType('UserId', int)

ProUserId = NewType('ProUserId', UserId)
```
并且 ProUserId 的类型检查将按预期工作。

> 注解 回想一下，使用类型别名声明两种类型彼此 等效 。Alias = Original 将使静态类型检查对待所有情况下 Alias 完全等同于 Original。当您想简化复杂类型签名时，这很有用。
相反，NewType 声明一种类型是另一种类型的子类型。Derived = NewType('Derived', Original) 将使静态类型检查器将 Derived 当作 Original 的 子类 ，这意味着 Original 类型的值不能用于 Derived 类型的值需要的地方。当您想以最小的运行时间成本防止逻辑错误时，这非常有用。


## Callable  可调用对象

期望特定签名的回调函数的框架可以将类型标注为 Callable[[Arg1Type, Arg2Type], ReturnType]。

```python
from typing import Callable

def feeder(get_next_item: Callable[[], str]) -> None:
    # Body

def async_query(on_success: Callable[[int], None],
                on_error: Callable[[int, Exception], None]) -> None:
    # Body
 ```
 通过用文字省略号替换类型提示中的参数列表： Callable[...，ReturnType]，可以声明可调用的返回类型，而无需指定调用签名。
 
 ## Generic 泛型
 容器中的元素类型不能以通用的方式推定,所以对抽象基类进行了扩展以支持下标访问(subscription)来表示所期望的容器元素类型
 ```python
 from collections.abc import Mapping, Sequence

def notify_by_email(employees: Sequence[Employee],
                    overrides: Mapping[str, str]) -> None: ...
```

Generics can be parameterized by using a new factory available in typing called TypeVar.
```python
from collections.abc import Sequence
from typing import TypeVar

T = TypeVar('T')      # Declare type variable

def first(l: Sequence[T]) -> T:   # Generic function
    return l[0]
```

  

---
1. 更多请参考 [official docs](https://docs.python.org/zh-cn/3.8/library/typing.html)

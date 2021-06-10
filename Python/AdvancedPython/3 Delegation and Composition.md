# Delegation and Composition

## Lesson Objectives

* 通过继承扩展函数功能 extend functionality by inheritance
* 执行复杂的代理 execute more complex delegation
* 通过合成扩展函数功能 extend functionality by composition
* 递归合成utilize recursive composition

In Python, it's unusual to come across deep inheritance trees (E inherits from D which inherits from C which inherits from B which inherits from A). While such program structures are possible, they can become unwieldy quickly. If you want to implement a dict-like object with some additional properties, you could choose to **inherit** from dict and extend the behavior, or you could decide to **compose** your own object from scratch and make use of a dict internally to provide the desired dict-like properties.    

## Extending Functionality by Inheritance

## More Complex Delegation

In general, the more of a particular object's behaviors you need, the more likely you are to inherit from it. But if only a small part of the behaviors you require is provided by an existing class, you might choose to **create an instance of that class and bind it to an instance variable of your own class** instead. The approach is similar, but does not use inheritance. 

```python
# Michael wrote:
class MyDict:
    def __init__(self, *args, **kw):
        self._d = dict(*args, **kw)
    def __setitem__(self, key, value):
        self._d[key] = value
    def __getitem__(self, key):
        return self._d[key]
   	def __delitem__(self, key):
        del self._d[key]
```

```python
# pdf上面的内容如下
class MyDict:
    def __init__(self, *args, **kw):
        self._d = dict(*args, **kw)
    def __setitem__(self, key, value):
        return self._d.__setitem__(key, value)
    def __getitem__(self, key):
        return self._d.__getitem__(key)
   	def __delitem__(self, key):
        return self._d.__delitem(key)
```

The final attempt to access the keys of the `MyDict` instance shows one potential shortcoming of this approach: **methods of the underlying object have to be made available explicitly. **This technique can be useful when only a limited subset of behaviors is required, along with other functionality (provided by additional methods) not available from the base type. Where most of the behaviors of the base type are required, it is usually better to use inheritance, and then override the methods that you don't want to make available with a method that raises an exception.    

## Extending Functionality by Composition



## Recursive Composition

Some data structures are simple, others are complex.某些数据结构由同种类型的实例构成，此类数据结构某些时候被称为递归组成。树就是一个典型，在许多语言中用树结构来随机或者有序地存取元素。The tree is made up of nodes. Each node contains data and two pointers. One of the data elements will typically be used as the key, which determines the ordering to be maintained among the nodes. The first pointer points to a subtree containing only nodes with key values that are less than the key value of the current node, and the second points to a subtree containing only nodes with key values that are greater than that of the current node.

Either of the subtrees may be empty (there may not be any nodes with the required key values); if both subtrees are empty, the node is said to be a leaf node, containing only data. If the relevant subtree is empty, the corresponding pointer element will have the value None (all nodes start out containing only data, with `None` as the left and right pointers)    

```python
"""
Create a sorting tree.

@author: jlli
"""
                 
class Tree:
    def __init__(self, key):
        "Create a new Tree Object with empty L&R subtrees."
        self.key = key
        self.left = self.right = None
    def insert(self, value):
        if self.key == value:
            raise ValueError("Duplicate key..")
        elif self.key < value:
            if self.right:
                self.right.insert(value)
            else:
                self.right = Tree(value)
        else:
            if self.left:
                self.left.insert(value)
            else:
                self.left = Tree(value)
    # def walk(self):
    #     "Print Keys Orderly..."
    #     if self.left:
    #         self.left.walk()
    #     print(self.key, end=" ")
    #     if self.right:
    #         self.right.walk()


    # or 
    def walk(self):
        "Generate the keys from the tree in sorted order. [txt book example]"
        if self.left:
            for n in self.left.walk():
                yield n
        yield self.key
        if self.right:
            for n in self.right.walk():
                yield n
                
if __name__ == "__main__":
    t = Tree("D")
    for c in "BEJQIKFGHAC":
        t.insert(c)
    print(list(t.walk()))
```

Here again we chose not to have you write tests for your code, but we do test it rather informally with the code following the class declaration. The tree as created, consists of a single node. After creation, a loop inserts a number of characters, and then finally the `walk()` method is used to visit each node and print out the value of each data element.    
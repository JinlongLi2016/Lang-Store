# Test (python)

[Contents' link](https://pythonguidecn.readthedocs.io/zh/latest/) 

https://pythonguidecn.readthedocs.io/zh/latest/writing/tests.html#id2

https://docs.python.org/3/library/unittest.html#assert-methods

https://docs.python.org/3/library/unittest.html#unittest.TestCase

https://nose.readthedocs.io/en/latest/

## unittest

The [`TestCase`](https://docs.python.org/3/library/unittest.html#unittest.TestCase) class provides several assert methods to check for and report failures. The following table lists the most commonly used methods (see the tables below for more assert methods):

| Method                                                       | Checks that            | New in |
| ------------------------------------------------------------ | ---------------------- | ------ |
| [`assertEqual(a, b)`](https://docs.python.org/3/library/unittest.html#unittest.TestCase.assertEqual) | `a == b`               |        |
| [`assertNotEqual(a, b)`](https://docs.python.org/3/library/unittest.html#unittest.TestCase.assertNotEqual) | `a != b`               |        |
| [`assertTrue(x)`](https://docs.python.org/3/library/unittest.html#unittest.TestCase.assertTrue) | `bool(x) is True`      |        |
| [`assertFalse(x)`](https://docs.python.org/3/library/unittest.html#unittest.TestCase.assertFalse) | `bool(x) is False`     |        |
| [`assertIs(a, b)`](https://docs.python.org/3/library/unittest.html#unittest.TestCase.assertIs) | `a is b`               | 3.1    |
| [`assertIsNot(a, b)`](https://docs.python.org/3/library/unittest.html#unittest.TestCase.assertIsNot) | `a is not b`           | 3.1    |
| [`assertIsNone(x)`](https://docs.python.org/3/library/unittest.html#unittest.TestCase.assertIsNone) | `x is None`            | 3.1    |
| [`assertIsNotNone(x)`](https://docs.python.org/3/library/unittest.html#unittest.TestCase.assertIsNotNone) | `x is not None`        | 3.1    |
| [`assertIn(a, b)`](https://docs.python.org/3/library/unittest.html#unittest.TestCase.assertIn) | `a in b`               | 3.1    |
| [`assertNotIn(a, b)`](https://docs.python.org/3/library/unittest.html#unittest.TestCase.assertNotIn) | `a not in b`           | 3.1    |
| [`assertIsInstance(a, b)`](https://docs.python.org/3/library/unittest.html#unittest.TestCase.assertIsInstance) | `isinstance(a, b)`     | 3.2    |
| [`assertNotIsInstance(a, b)`](https://docs.python.org/3/library/unittest.html#unittest.TestCase.assertNotIsInstance) | `not isinstance(a, b)` | 3.2    |



The [`unittest`](https://python-documentation-cn.readthedocs.io/en/latest/library/unittest.html#module-unittest) module provides a rich set of tools for constructing and running tests. This section demonstrates that a small subset of the tools suffice to meet the needs of most users.

Here is a short script to test three functions from the [`random`](https://python-documentation-cn.readthedocs.io/en/latest/library/random.html#module-random) module:

```
import random
import unittest

class TestSequenceFunctions(unittest.TestCase):

    def setUp(self):
        self.seq = list(range(10))

    def test_shuffle(self):
        # make sure the shuffled sequence does not lose any elements
        random.shuffle(self.seq)
        self.seq.sort()
        self.assertEqual(self.seq, list(range(10)))

        # should raise an exception for an immutable sequence
        self.assertRaises(TypeError, random.shuffle, (1,2,3))

    def test_choice(self):
        element = random.choice(self.seq)
        self.assertTrue(element in self.seq)

    def test_sample(self):
        with self.assertRaises(ValueError):
            random.sample(self.seq, 20)
        for element in random.sample(self.seq, 5):
            self.assertTrue(element in self.seq)

if __name__ == '__main__':
    unittest.main()
```

A testcase is created by subclassing [`unittest.TestCase`](https://python-documentation-cn.readthedocs.io/en/latest/library/unittest.html#unittest.TestCase). The three individual tests are defined with methods whose names start with the letters `test`. This naming convention informs the test runner about which methods represent tests.

The crux of each test is a call to [`assertEqual()`](https://python-documentation-cn.readthedocs.io/en/latest/library/unittest.html#unittest.TestCase.assertEqual) to check for an expected result; [`assertTrue()`](https://python-documentation-cn.readthedocs.io/en/latest/library/unittest.html#unittest.TestCase.assertTrue) to verify a condition; or [`assertRaises()`](https://python-documentation-cn.readthedocs.io/en/latest/library/unittest.html#unittest.TestCase.assertRaises) to verify that an expected exception gets raised. These methods are used instead of the [`assert`](https://python-documentation-cn.readthedocs.io/en/latest/reference/simple_stmts.html#assert) statement so the test runner can accumulate all test results and produce a report.

When a [`setUp()`](https://python-documentation-cn.readthedocs.io/en/latest/library/unittest.html#unittest.TestCase.setUp) method is defined, the test runner will run that method prior to each test. Likewise, if a [`tearDown()`](https://python-documentation-cn.readthedocs.io/en/latest/library/unittest.html#unittest.TestCase.tearDown) method is defined, the test runner will invoke that method after each test. In the example, [`setUp()`](https://python-documentation-cn.readthedocs.io/en/latest/library/unittest.html#unittest.TestCase.setUp) was used to create a fresh sequence for each test.

每一个以test开始的方法都会运行（测试），并且使用self.内的方法进行测试。如果有setUp() `tearDown()`的话，每一个方法前都会运行`setUp()`，结束后都会运行`tearDown()`。

The final block shows a simple way to run the tests. [`unittest.main()`](https://python-documentation-cn.readthedocs.io/en/latest/library/unittest.html#unittest.main) provides a command-line interface to the test script. When run from the command line, the above script produces an output that looks like this:

```
...
----------------------------------------------------------------------
Ran 3 tests in 0.000s

OK
```

Passing the `-v` option to your test script will instruct [`unittest.main()`](https://python-documentation-cn.readthedocs.io/en/latest/library/unittest.html#unittest.main) to enable a higher level of verbosity, and produce the following output:

```
test_choice (__main__.TestSequenceFunctions) ... ok
test_sample (__main__.TestSequenceFunctions) ... ok
test_shuffle (__main__.TestSequenceFunctions) ... ok

----------------------------------------------------------------------
Ran 3 tests in 0.110s

OK
```

The above examples show the most commonly used [`unittest`](https://python-documentation-cn.readthedocs.io/en/latest/library/unittest.html#module-unittest) features which are sufficient to meet many everyday testing needs. The remainder of the documentation explores the full feature set from first principles.

上述示例展示了`unittest`最常用的一些方法，接下来的我们会进一本剖析它其他特点。



## Organizing test code[¶](https://docs.python.org/3/library/unittest.html#organizing-test-code)

The basic building blocks of unit testing are *test cases* — single scenarios that must be set up and checked for correctness. In [`unittest`](https://docs.python.org/3/library/unittest.html#module-unittest), test cases are represented by [`unittest.TestCase`](https://docs.python.org/3/library/unittest.html#unittest.TestCase) instances. To make your own test cases you must write subclasses of [`TestCase`](https://docs.python.org/3/library/unittest.html#unittest.TestCase) or use [`FunctionTestCase`](https://docs.python.org/3/library/unittest.html#unittest.FunctionTestCase).

The testing code of a [`TestCase`](https://docs.python.org/3/library/unittest.html#unittest.TestCase) instance should be entirely self contained, such that it can be run either in isolation or in arbitrary combination with any number of other test cases.

The simplest [`TestCase`](https://docs.python.org/3/library/unittest.html#unittest.TestCase) subclass will simply implement a test method (i.e. a method whose name starts with `test`) in order to perform specific testing code:

```
import unittest

class DefaultWidgetSizeTestCase(unittest.TestCase):
    def test_default_widget_size(self):
        widget = Widget('The widget')
        self.assertEqual(widget.size(), (50, 50))
```

Note that in order to test something, we use one of the `assert*()` methods provided by the [`TestCase`](https://docs.python.org/3/library/unittest.html#unittest.TestCase) base class. If the test fails, an exception will be raised with an explanatory message, and [`unittest`](https://docs.python.org/3/library/unittest.html#module-unittest) will identify the test case as a *failure*. Any other exceptions will be treated as *errors*.

Tests can be numerous, and their set-up can be repetitive. Luckily, we can factor out set-up code by implementing a method called [`setUp()`](https://docs.python.org/3/library/unittest.html#unittest.TestCase.setUp), which the testing framework will automatically call for every single test we run:

测试可能会进行多次，它们的前期环境建立可能需要反复进行。幸运的是，通过方法`setUp()`可以单独写环境建立的代码。它在每一个test测试前都会被自动运行。

```
import unittest

class WidgetTestCase(unittest.TestCase):
    def setUp(self):
        self.widget = Widget('The widget')

    def test_default_widget_size(self):
        self.assertEqual(self.widget.size(), (50,50),
                         'incorrect default size')

    def test_widget_resize(self):
        self.widget.resize(100,150)
        self.assertEqual(self.widget.size(), (100,150),
                         'wrong size after resize')
```

Note

 

The order in which the various tests will be run is determined by sorting the test method names with respect to the built-in ordering for strings.

If the [`setUp()`](https://docs.python.org/3/library/unittest.html#unittest.TestCase.setUp) method raises an exception while the test is running, the framework will consider the test to have suffered an error, and the test method will not be executed.

Similarly, we can provide a [`tearDown()`](https://docs.python.org/3/library/unittest.html#unittest.TestCase.tearDown) method that tidies up after the test method has been run:

同样的，也有`tearDown()`方法来收拾（环境）之类的。

```
import unittest

class WidgetTestCase(unittest.TestCase):
    def setUp(self):
        self.widget = Widget('The widget')

    def tearDown(self):
        self.widget.dispose()
```

If [`setUp()`](https://docs.python.org/3/library/unittest.html#unittest.TestCase.setUp) succeeded, [`tearDown()`](https://docs.python.org/3/library/unittest.html#unittest.TestCase.tearDown) will be run whether the test method succeeded or not.

如果`setUp()`运行成功，那么无论测试是否成功，`tearDonw()`都会运行。

Such a working environment for the testing code is called **a *test fixture***. A new TestCase instance is created as a unique test fixture used to execute each individual test method. Thus [`setUp()`](https://docs.python.org/3/library/unittest.html#unittest.TestCase.setUp), [`tearDown()`](https://docs.python.org/3/library/unittest.html#unittest.TestCase.tearDown), and `__init__()` will be called once per test.

It is recommended that you use TestCase implementations to group tests together according to the features they test. [`unittest`](https://docs.python.org/3/library/unittest.html#module-unittest) provides a mechanism for this: the *test suite*, represented by [`unittest`](https://docs.python.org/3/library/unittest.html#module-unittest)’s [`TestSuite`](https://docs.python.org/3/library/unittest.html#unittest.TestSuite) class. In most cases, calling [`unittest.main()`](https://docs.python.org/3/library/unittest.html#unittest.main) will do the right thing and collect all the module’s test cases for you and execute them.

However, should you want to customize the building of your test suite, you can do it yourself:

```
def suite():
    suite = unittest.TestSuite()
    suite.addTest(WidgetTestCase('test_default_widget_size'))
    suite.addTest(WidgetTestCase('test_widget_resize'))
    return suite

if __name__ == '__main__':
    runner = unittest.TextTestRunner()
    runner.run(suite())
```

You can place the definitions of test cases and test suites in the same modules as the code they are to test (such as `widget.py`), but there are several advantages to placing the test code in a separate module, such as`test_widget.py`:

- The test module can be run standalone from the command line.
- The test code can more easily be separated from shipped code.
- There is less temptation to change test code to fit the code it tests without a good reason.
- Test code should be modified much less frequently than the code it tests.
- Tested code can be refactored more easily.
- Tests for modules written in C must be in separate modules anyway, so why not be consistent?
- If the testing strategy changes, there is no need to change the source code.
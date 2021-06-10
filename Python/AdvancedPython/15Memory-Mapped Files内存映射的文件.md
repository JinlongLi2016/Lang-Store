# Memory-Mapped Files内存映射的文件

**Lesson Objectives**

When you complete this lesson, you will be able to :

* 使用内存映射utilize Memory Mapping
* process a Memory-Mapped Example

## 内存映射 Memory Mapping

文件可能太大而不能够一次性导入内存。`mmap.mmap()`函数创建一个虚拟的文件对象。在memory-mapped文件上，不仅可以实施所有常规的文件操作，you can also treat it as a vast object (far larger than any real object could be) that you can address just like any other sequence.    

这项技巧通过将文件映射到进程的地址空间来处理文件。`mmap`模块让你可以视文件为一个似`bytearray`字节数组对象---可以对其进行下标访问，切片，通过正则进行搜索等等。这些操作可以大大简单化文件中数据处理：没有内存映射，必须将文件按照`chunk`读入再处理这些`chunk`（假设这些文件因太大而不能够读到单个`chunk`）。This makes it very difficult to process strings that overlap the inter-chunk boundaries.Memory mapping allows you to pretend that all the data is in memory at the same time even when that is not actually the case. The necessary manipulations to allow this are performed automatically.    

In this lesson, we primarily cover only the details of **mmap** that apply across both Windows and Unix platforms, and a few Windows-specific features. You should be aware that there are different additional feature sets available for Windows and Unix platforms. The documentation on the module is fairly specific about the implementation differences.    

###
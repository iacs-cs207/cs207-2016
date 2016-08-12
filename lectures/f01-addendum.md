---
title: Memory
layout: lecture
mathjax: true
---

 - [Allocation](#allocation)
  - [Programs in Memory](#programs)
  - [The Stack](#stack)
  - [The Heap](#heap)

<a name='allocation'></a>
## Allocation
As we've discussed before, every value in a program must be stored somewhere in memory.
In C, you must tell the compiler where that location is.
Up to this point we've been carefully sidestepping the issue, but it's time to understand the gory details.

<a name='segments'></a>
### Programs in memory

Let's start by understanding what we mean when we say a program is "in memory."
As you've already learned, a C program is compiled to an executable binary, which contains the instructions that the machine will execute.
In order to actually run the program, this compiled code must be loaded from disk into memory.
In addition, once your program starts, it must create space for the variables it will use, and it must store and read values from those variables.
The code, the reserved space, and the generated data all constitute a program's memory footprint.

Every operating system has a (different) convention for exactly where and how these different resources are actually laid out in memory.
(These conventions are called *object file formats*, where "object file" in this context refers to the semi-finished intermediate files that a compiler produces, not to be confused with objects as instances of class data types in languages like Python or C++.)
In Linux, the most common object format is called ELF, short for "Executable and Linkable Format", and we'll use that as an example here, but most object file formats have very similar concepts.

By using program analysis tools, we can actually take a sample program and compute the (relative) addresses for all its different pieces.
A simplified view of our example program looks like this in memory:

![memory layout]({{site.baseurl}}/lectures/f01/segments.png)

The first thing to understand is what all these different blocks represent.
The yellow blocks with a "." in front of their names are called "segments", and they represent purpose-specific divisions of the program's memory (and unfortunately, should not be confused with memory segmentation or segfaults---another confusing collision of words).
The `.text` segment, for instance, contains all your program's code, so whenever the computer executes an instruction, it is reading it from here.
The `.data` segment contains pre-initialized global values (variables that are given values when they are declared), and the `.bss` segment contains space reserved for uninitialized global variables.
Let's look at a sample program as an example:

```c
int64_t global_one; // 8 bytes reserved in .bss
char global_array_one[5]; // 5 bytes reserved in .bss

char global_array_two[5]={0,1,2,3,4}; // These five values stored in .data
char *string_one="hello"; // six values (five plus NULL-terminator) stored in .data

int main(int argc, char **argv) {
  global_one = 5; // Code is in .text. When run, will store a value in .bss
  printf("%s\n", string_one); // Code is in .text. Will read 6 bytes from .data
  printf("%d\n", global_one); // Code is in .text. Will read 8 bytes from .data
  return 0; // Code is in .text
}
```

The blue block represents dynamically managed memory: the stack, and the heap.
Whenever you allocate a variable within a function, it goes into one of these two regions.
We've already talked a little about the stack, but let's dive a little deeper:

[Back to top &uarr;](#)

<a name='stack'></a>
### The Stack

The stack keeps track of function calls and their data.
Whenever a function is called, a new chunk of memory is reserved at the top of the stack in order to store variables for that function.
This includes variables that you have defined inside your function, but it also includes data that were generated automatically by the compiler.
The most recognizable value in this latter category is the *return address*.
When a function calls `return`, the computer starts executing instructions at the location the function was originally called from, and the return address is what lets the computer know where it left off.
Additionally, when a function returns, it removes its stack frame from the stack.
This means that at any given point, the stack contains a record of which functions the program is currently in.
When you run `backtrace` in gdb, this is exactly the information it's telling you.

[Back to top &uarr;](#)


<a name='heap'></a>
### The Heap

One consequence of removing stack frames after a function returns is that the variables declared within that function no longer have any memory reserved for them.
This can cause problems.
Take the following example:

```c
int *set_up() {
  int x = 5;
  return &x;
}
void clobber() {
  int y = -1;
  return;
}
int main(int argc, char **argv) {
  int *p;
  p = set_up();
  printf("%d\n", *p);
  clobber();
  printf("%d\n", *p);
  return 0;
}
```

When `set_up` runs, it creates a stack frame and space is reserved for `x`.
It then sets `x` to 5 and returns a pointer to that memory location.
When that function returns, that stack frame is removed, and the location reserved for `x` is no longer reserved.
When we print out `x`, the value `5` is still there, even though the memory location is not really legal.
When the function `clobber` is called, the first thing it does is allocate a stack frame, which is created in the *same space* that the stack frame for `set_up` was using before it returned.
Thus, when space is reserved for `y`, it just so happens that it is the same space as `x` used to occupy (because `set_up` and `clobber` happen to have the same variable layout).
So when we set `y`, it sets the memory location that used to be for `x` to the value `-1`.
Finally, when we return, the stack frame for `clobber` is removed, but the values are not yet overwritten.
The last `printf` statement accesses the location previously occupied by `x` and `y`, printing `-1`.

This is a problem if you want to create space for variables and then access them after the function returns.
What we really need is another memory location which is not reclaimed after a function returns.
That's what the heap is for.
The heap is *explicitly* managed, which means that in order to allocate a variable in it, you need to ask.
What's more, when you're finished with that space, you need to say so.
This interface, explicitly requesting and releasing memory from the heap, is typically called *memory management*.

In C, the interface for managing the heap is two functions: `malloc`, to ask for memory; and `free`, to release it and allow it to be reused.
Let's safely reimplement the previous example using them:

```c
int *set_up() {
  int *x;
  x = (int *)malloc( sizeof(int) );
  *x = 5;
  return x;
}
void clobber() {
  int y = -1;
  return;
}
int main(int argc, char **argv) {
  int *p;
  p = set_up();
  printf("%d\n", *p);
  clobber();
  printf("%d\n", *p);
  return 0;
}
```

Now, the storage for the variable `x` in `set_up` is reserved explicitly, so when `set_up` returns, the memory allocated in the heap to `x` remains valid.
As a result, both `printf` statements output `5`.

Control over memory allocation is a powerful tool, but it comes with responsibilities.
While the operating system *will* reclaim all the memory from a process after it exits (including the heap, any stack space, and all program segments), the programmer is completely responsible during the program's lifetime.
So calling `free` on memory when you are finished with it is not particularly optional.
For instance, let's say you have a web server program, and every time a page is requested, you allocated some memory on the heap but forgot to free it.
As time goes on, more and more memory is reserved on the heap for you.
Because C will not automatically free it up, the heap will begin to expand.
Eventually, the OS will run out of physical RAM, and it will either start *swapping* (which is when it tries to start using disk as a back-up for memory---a death knell for performance) or simply start killing random programs to free up memory.

[Back to top &uarr;](#)

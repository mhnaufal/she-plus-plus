# 🕵️‍ She-Plus-Plus

Because it's hard to understand her, I'll try to understand C++ instead, and it turns out that a lot of Rust's concept,
borrowed from C++

## Table of Contents

## 📚 Knowledge Gained

### 1️⃣ Build C++

<details>
<summary>Build C++</summary>

There are 3 options to compile and run C++ file(s)

- Using command line
- Using Makefile
- **Using CMake**

Maybe there's another options, but all I know for now are those 3 options.

1. **CMake**

   To build C++ file using CMake, create a `CMakeLists.txt` inside the top level of the directory.
   After that run

   ```shell
   cmake [options] -S <path-to-source> -B <path-to-build>
   ```

   ```shell
   cmake -S . -B build
   ```

   run cmake based on configuration file located inside **.** (current directory) and placed the result inside **build**
   directory

   or sometime people used to use this kind of setup

   Create a directory called **build** and `cd` into it

   ```shell
   mkdir build
   cd build
   ```

   Run `cmake`. **..** means, run cmake with source file (CMakeLists.txt) is located in previous directory and placed
   the
   result inside this directory

   ```shell
   cmake ..
   ```

2. **CMake Syntax**

   The hard part are the **cmake syntax** and **connect multiple C++ files**
   [CMake CheatSheet](https://usercontent.one/wp/cheatsheet.czutro.ch/wp-content/uploads/2020/09/CMake_Cheatsheet.pdf)

   **Must** have configurations in **CMakeLists.txt** file:
    - `cmake_minimum_required(VERSION 3.10)`
    - `project(project_name)`
    - `add_executable(project_name, list_of_cpp_source_file)`
    - `target_include_directories(project_name visibility list_of_directory)`: use this so that we can use *#include <
      directory_name>* instead of normal double quotes
    - `target_link_directories(project_name visibility list_of_directory)`
    - `target_link_libraries(project_name, list_of_library)`
    - `add_library(library_name list_of_cpp_file)`: use this inside the sub folder to make this sub folder as a library
      so that the parent cmake can connect it

3. **CMake Levels**

   What happen if we want to link our executables that placed in a different folder/sub folder? Basically, we need to **
   create a CMakeLists.txt** inside that sub folder.

   **In root CMakeLists.txt** add this:
    - `add_subdirectory()`: only accept 1 directory as the parameter
    - `target_include_directories()`
    - `target_link_directories()`
    - `target_link_libraries()`

   **In the sub folder CMakeLists.txt** add this:
    - `add_library()`

</details>

---

### 2️⃣ Basic C++

<details>
<summary>Basic C++</summary>

1. **C++ Term**

    - **Translation Unit**
      There are a bunch of definitions about this, but for me, it's **A source file after includes with header files and
      other conditional preprocessing**
    - **Class** and **Struct**
      `class` and `struct` in C++ define a **new type**. Use `struct` as a data container without any function within,
      and use `class` as data container with function. Although we can create function inside struct. We can have
      inheritance in struct and class! Like, WTF!
    - **Static**
      `static` functions and data are functions and data that are only visible within the same translation unit. In C++
      class, we use `::` double colon to access them.
    - **using**
      `using` to shorten your code! To access certain namespace.

2. **File**

   We can read, write, and append from a file in _ASCII_ format and _binary format_.
   It's a lot and I have practice it,
   so [go ahead to this](https://www.delftstack.com/howto/cpp/how-to-append-text-to-a-file-in-cpp/) instead.

3. **lvalue** and **rvalue**

   _this is not the "correct" definition, but this is the "easiest" definition to understand_
    - `lvalue` = written in the **left** of assigment operator **=**. Has **storage** or **memory address location**. Can only take lvalue unless it is a `const`. 
    - `rvalue` = written in the **right** of assigment operator **=**. Explicit `rvalue` defined using `&&`. Doesn't
      have **storage** or it just a **temporary memory address**. `rvalue` can only take rvalue.
       ```c++
       int b = a + 2;
       ```
         _b_ is lvalue and _a + 2_ is rvalue.

       ```c++
       int&& c = std::move(b);
       ```
      _b_ is **initially an lvalue**, but then we use the `std::move()` to change it into an *rvalue*, and then we put the result in
      a **c** which is an **rvalue-reference**, because we have moved it from an lvalue into an rvalue using `&&` symbol.
    - `lvalue-reference` = same as **reference alias**. 

    ```c++
    int& i = 10; // error, non-const lvalue reference
    const int& i = 10; // success, "const" cause the compiler made a temporary storage for the "i"
    ```

    - `rvalue-reference` = the way we can reference an rvalue.
      ```c++
      int&& a = 10; // a is an rvalue-reference
      ```

      ```c++
      std::string a = "Halo";
      std::string b = "Hi";
      std::string c = a + b; // resource wasteful, because behind the scene compiler to a "copying"
      //
      std::string a = "Halo";
      std::string b = "Hi";
      std::string&& c = a + b; // more efficient, because it is a "moving"
      ```
      We use `&&` symbol to prevent us from doing _calculation -> copying_ process. Instead what we just do is just a _calculation -> moving_. With this process, the memory can be more efficient. However, it come with a cost that slower compile/runtime.

    - `std::move(x)` = means "give me the **rvalue reference to x**". It can be said that `std::move()` is an **ownership taker** (rusty thing 🦀)
      - [Nice read](https://eli.thegreenplace.net/2011/12/15/understanding-lvalues-and-rvalues-in-c-and-c/)
      - E.g.
      ```c++
      std::string a = "long";
      std::string b = std::move(a);
      // **string b** will hold the value of string a, and **string a** would be empty because the value has already **"moved"** to the string b.
      
      std::string a = "long";
      std::string b = a;
      // normal copy, can take too much resource
      ```

4. **Pointer**
   Just check out [the code for this one!](https://github.com/mhnaufal/see-plus-plus/tree/main/Pointer-CPP)
    - `&`: address of operator/reference (value ➡ address)
    - `*` _without data type_: dereference (address ➡ value)
    - `int*` _with data type_: declare a pointer
      example:
   ```c++
   int x = 100; // declare a variable called x with type of in  t
   int *y; // declare a variable called y with type of *int
   y = &x; // assign a variable y with the value of address of x
   int& z = y; // create a reference variable called z that refer to variable y
   ```
   To create an object in C++, we usually (_most of the time actually_) don't use `new` keyword, because `new` will
   allocate the data into **heap memory**, therefore we need to deallocate it using `delete`

   ✅ recommended
   ```c++
   User user;  // placed inside the stack memory
   ```

   ❌ not recommended
   ```c++
   User user = new User(); // placed inside the heap memory
   ```

   🚫 We **CAN'T REASSIGN** a reference.

5. **Enum**
   The way we name a value. It's just an integer with name. Enum will start from 0 and increment until the last element
   on it.
   If we specify the first value of enum to any number except 0, the rest of the elements will increment from it.

6. **Union**
   Union is like struct, but one thing to differentiate is that union size based on the largest element inside it, where
   struct size based on sum of total of the element
   size. [explanation](https://stackoverflow.com/questions/346536/difference-between-a-structure-and-a-union)
   Union can only hold one same data type "type" at a time (go straight to the code).

</details>

---

### 3️⃣ Object Oriented Programming (OOP) C++

User-defined type (UDT). C++ compiler gives by default: **Constructor**, **Destructor**, **Copy Constructor**, **Copy Assigment Operator** (shallow copy).

1. **Class**
   In other OOP programming languages, we call functions inside a class as **methods**, but here in C++ we called it **Member Functions**. Also applies for **attributes**, we call it **Data Members**. Class members are **private** by
   default, not like Struct where they are **public** by default.

   Class need **at least one constructor** and **exactly one destructor**.

   **Const correctness**: `const` after function name state that this function does not change the object. It's not only
   for functions but other things to correct too. Only available for member functions!
   example:
   ```c++
   const std::string name() const {
      return name_;
   }
   ```

   The first `const` ack as the return type and the second `const` mark that this function will not change the object.
   `class` and `struct` can inherit data & functions from other classes.

   **Member Initializer List** = C++ ways to initialize members in constructor. Must be list in exact the same order
   with the data member. We can use manual assignment, but it would take 2 steps, which are "create empty memory" and "assign the args".
   ```c++
   class Number {
      int a;
      int b;
   public:
      Number()
         : a(0), b(1)
   ```

2. **Operator Overloading**
   Operator in C++ it's just another function with the word **operator**.

   Format: `<RETURN_TYPE> operator<NAME>(<PARAMS>)`

   where <NAME> are one of `>, <, =, ==, <<`. For example if we create a `<<` operator overloading, so when
   using `std::cout <<` we don't need to specify the elements that we want to print (look in code example for more clear
   explanation!)

3. **Class Special Functions**
   There are 5 class special functions and compiler already **generate them** automatically if we don't specify one.
   However, if we specify at least one, the compiler will not generate the rest. One for None.

4. **Inheritance**
   There are 3 types of inheritance in C++, **public**, **private**, and **protected** (it's different with access
   modifier).
    - **explicit** = prevent the compiler to do an implicit casting. Implicit casting only happen one time.
    - **virtual function** = whenever a class derived/inherit from a class that has virtual functions on it, the derived
      class has option to implement the virtual function or not
    - **pure virtual function** = a virtual function that ended with `= 0;` that doesn't have any use in the base class
      but must be implemented in the derived class. A class that contains pure virtual functions is known as **abstract
      class**.
    - **override** = used alongside with `virtual` as a mark that this function is derived implementation from the
      parent class
    - **interface** = In C++, we can create an interface by defining a class with **no data members** and all function
      members are **virtual function**

5. **RAII**
   Resource managed within its lifetime (inside pair curcly braces). It's just as simple as **"Outside the curly braces, the resource automatically released"**. Achieve by creating class and the Destructor will be called automatically. 

6. **Friend Function** and **Friend Class**
   Special function that declared inside a class, but defined outside the class's scope. The purpose of friend function is to make a functin that can access a class without being one with the class.
      ```c++
      // inside class code
      friend void printOutside(Class c);

      // outside class code
      friend void printOutside(Class c) {
         std::cout << a;
      }

      // main
      Class c;
      printOutside(c);
      ```
   **Friend class** same as friend function, but for class.

---

### 4️⃣ Testing C++

<details>
<summary>Testing C++</summary>

Some famous C++ test libraries are: **Google Test**, **Doctest**, and **Catch2**

1. **Doctest**

   This one is the easiest to set up among the other two libraries. The only setup we need is to download the header
   file,
   and we're good to go (beside set up the cmake of course).

   To run the doctest:
   ```shell
   cd build
   cmake ..
   cd Testing-CPP
   ./tests
   ```

   result:
   ```doctest
   [doctest] doctest version is "2.4.9"
   [doctest] run with "--help" for options
   ===============================================================================
   [doctest] test cases: 1 | 1 passed | 0 failed | 0 skipped
   [doctest] assertions: 3 | 3 passed | 0 failed |
   [doctest] Status: SUCCESS!
   ```

2. **Catch2**

3. **Google Test**

</details>

---

### 5️⃣ Modern C++

<details>
<summary>Modern C++</summary>

1. **Map**

   Maps are always sorted according to the **key**. It means that even we randomly insert our key-value pairs, the C++
   map will automatically sort it based on the key.
   In modern C++ (C++11), we can define and access elements inside map using different signature as follows:
    - **Define**
       ```c++
       map<string, string> person { { "name", "johny depp"}, { "born", "1919" } };
       ```
    - **Access**
       ```c++
       cout << my_map.at("name");
       ```
      will result
       ```shell
       "johny depp"
       ```

2. **Vector**

   In vector, we have 2 important term to know, which are **size** and **capacity**
    - **Size**: How many element already filled inside this vector
    - **Capacity**: The maximum number of elements this vector can handle

   Before the capacity reach it's maximum number, C++ will automatically expand it. To prevent this kind of behaviour,
   we
   can use **vector.reserve(int size)**

   **C++11**: To insert a new element into a vector we can use: `vector.emplace_back()`

3. **Unordered Map**

   Faster than std::map. Implemented using **hashtable** and key type must be _hashable_
    - `map.first`: same as take the key
    - `map.second`: same as take the value

4. **STL Algorithm**

   It's a lot and you can [reference it here!](https://en.cppreference.com/w/cpp/algorithm)

5. **Smart Pointer**

   [Microsoft C++](https://docs.microsoft.com/en-us/cpp/cpp/welcome-back-to-cpp-modern-cpp?view=msvc-170)
   One of the reason smart pointer exists is that **memory leak** that often occur in C. Modern C++ use concept
   called **RAII** (Resource Acquisition is Initialization) or in english means, **resource** (heap memory, file,
   socket) should be **owned** by an object (again, this is "rusty 🦀" thing).

   1. _Unique Pointer_
      Scope based pointer. Automatically called destructor if out of scope or move to another pointer. **Only one** ownership can exists at a time, and **no copy** is allowed.
         ```c++
         std::unique_ptr<T> var = std::make_unique<T>();
         std::unique_ptr<T[]> vars = std::make_unique<T[]>(1, 2, 3);

         std::unique_ptr<T> mov = std::move(var); // move is allowed, but not for copy
         ```
   2. _Shared Pointer_
      Reference based pointer. Regardless of the scope, shared_ptr resource can be accessed by **multiple owner**. **Thread safe!**
         ```c++
         std::shared_ptr<T> var = std::make_shared<T>();
         std::shared_ptr<T> var2 = var; // allowed here. Ref count increase to 2
         ```
   3. _Weak Pointer_
      Similar to shared pointer, but don't have reference count. **Not-owning pointer**. Used to _break cyclic shared pointer_, and _"safer" dangling pointer._ Need to be combined with shared pointer so that it can be used and useful. Stil same as unique pointer that will be expired when goes out of scope.
         ```c++
         std::weak_ptr<T> weak;
         std::shared_ptr<T> var = std::make_shared<T>();
         weak = var; // ref count will no increase
         weal.is_expired(); // true if "var" goes out of scope
         ```

6. **Move Semantic**
   Before dive into move semantic, understand [**lvalue** and **rvalue** first!](#2%EF%B8%8F%E2%83%A3-basic-c)

   _Why we need move semantic?_

   We do a lot of object passing, but we don't want to copy the object, we just want to
   pass the ownership of the object. Imagine we pass an object to a function, we need to copy the object inside the
   function, the same goes for when we return an object from a function, we need to copy it again!
   **Thus, instead of copy the object why we don't just move it? Here's where move semantic comes in.**

   E.g.
   ```c++
   std::string a = "Hello";
   std::string b = a; // copying, taking too much resource
   //
   std::string a = "Hello";
   std::string b = std::move(a); // moving, little resource, but a lose the ownership of the string "Hello" and become an empty string
   ```

7. **Function Pointer** and **Lambda**
   It's just a function that can be inputted as a value of a variable or a function that ack as an argument/parameter
   for
   another function. The type `void(*TypeName)(ParametersType)`

   Lambda is the way we define a function without defining function(?). Lambda
   syntax [consist of](https://en.cppreference.com/w/cpp/language/lambda):
   `[captures]{body}`
    - **captures** = it's like in PHP anonymous function. TL;DR bring variable outside this scope into this scope
        - **=** = pass the variable by value
        - **&** = pass the variable by reference
    - **params** = parameters
    - **tparams** = template parameters
    - **body** = function body
    - **specifiers** = sequence of specifiers

8. **Template**
   The compiler write code for programmer based on rules define inside the
   template. [Nice reads](https://stackoverflow.com/questions/8752837/undefined-reference-to-template-class-constructor)
   about template definition and declaration that can't be seperated in different translation unit. Template **doesn't
   exist** until we **called** it. Meta programming.

9. **const** and **mutable**
   **const** == promise. And you should keep the promise.
   ```c++
   const int *ptr = new int;
   *ptr = 3; // can't do this. cannot change the value of the pointer
   ```

   ```c++
   int *const ptr = new int;
   ptr = (int*)&newPtr; // can't do this. cannot change the "pointer" itself
   ```

   **mutable** = allow us to make a change on a variable/data member inside a const function member, where in normal
   case, we can't


99. **Other Interesting In Modern C++**

- **any**: It's a data type, but more like ANY type.
- **optional**: Function that optionally return something.
- **chrono**: Benchmark our C++ code.
- **constexpr**: Use this as a macro instead of `#define`. Make a runtime value act as a compile time value. Same like `template` but simpler.

</details>

---

### 6️⃣ OpenCV C++

_already done in another repo and installation flow already provided in the Dockerfile_

---

### 7️⃣ Libtorch C++

_why this one always error in this repo?_

---

### 8️⃣ libasyik

_already done in another repo and installation flow already provided in the Dockerfile_

---

### 9️⃣ pybind11

_Create a C++ codes that can be run as Python codes._ Make sure you have installed the pybind11
locally! [How?](https://pybind11.readthedocs.io/en/stable/compiling.html)

Installation:

- Download the pybind11 for C++
- Create a build directory
- `cmake --build .`
- `cmake --install .`

We can't include pybind directly into the main.cpp file, so we use another file (example.cpp) to handle the pybind. And
also don't forget to run it using `pythpn3` or `ipython3`

**ipython command to access the generated module**

- `import module`
- `dir(module)`
- `module.__doc__`
- `module.function_name?`

[pybind cmake references](https://github.com/pybind/cmake_example/blob/master/CMakeLists.txt)

---

### 1️⃣0️⃣ Msgpack

A binary serialization which let us exchange data among different programming languages. It's like JSON and ~Protobuf~,
but it's faster and smaller! [Homepage](https://msgpack.org/). Small integers are encoded into only a single byte.

To run msgpack, comments the pointer code section first

Installation:

- Clone the repo
- cmake build and install
- Update the cmake file!

[Installation reference](https://github.com/msgpack/msgpack-c/tree/cpp_master#building-and-installing)

---

### 1️⃣1️⃣ ZeroMQ

To use this library, install the [libzmq](https://github.com/zeromq/libzmq) and copy
the [zmq.hpp](https://github.com/zeromq/cppzmq/blob/master/zmq.hpp) file to **/usr/include**, and add flag `zmq` to the
cmake `target_link_libraries`

Installation:

- `sudo apt-get install libzmq3-dev`
- Copy and paste the **zmq.h**, **zmq.hpp**, and **zmq_utils.hpp** to the **/usr/include/**
- Update the cmake file!

[Recommended video](https://www.youtube.com/watch?v=UrwtQfSbrOs)

When we kill the ZeroMQ server, the clients connected to it are still alive and not force to shut down themselves.

- **REP** and **PUSH**: Server
- **REQ** and **PULL**: Client

---

### 1️⃣1️⃣ Multithreading

**Multiprocessing**  : can be accomplished using `fork`
**Multithreading**   : can be accomplished using `std::thread`

- `std::thread(func, args)`   : run the *func* accepting *args* on **another thread** (not on main thread). Need to accept function or object. Multiple threads can be created by calling the `std::thread` multiple time.
- `std::join()`               : force the main thread to wait for other threads to finish first.
- `std::mutex`                : create a mutex lock to prevent multiple threads accessing the same data. Must be made **globally**, so that every threads can access it.
- `std::mutex.lock()`         : lock the mutex
- `std::mutex.unlock()`       : unloack the mutex (need to be done manually)
- `std::lock_guard<mutex>()`  : RAII-style mutex. Accepting mutex to be locked. Unlock happen automatically after exiting the scope.
- `std::atomic<type>`         : create a "mutexed" variable. Using this feature make use don't require to use lock and unlock anymore.
- `std::conditional_variable` : mechanism of *queueing* threads.
- `std::async`                : make the function or program run asynschronously in seperated thread
- `std::future`               : return the result of `std::async`.


---

## 💡 Acknowledgments

Thanks to these awesome resources:

- [Nodeflux](https://www.nodeflux.io)
- [The Cherno](https://www.youtube.com/c/TheChernoProject)
- [Modern C++ Lecture](https://www.youtube.com/playlist?list=PLgnQpQtFTOGRM59sr3nSL8BmeMZR9GCIA)
- [CMake Dude](https://www.youtube.com/watch?v=nlKcXPUJGwA&list=PLalVdRk2RC6o5GHu618ARWh0VO0bFlif4&index=1&t=0s)
- [CLion](https://www.jetbrains.com/clion/)

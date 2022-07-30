# Basic Types
## Introduction
This document introduces the basic types. Some of these types are inherited from `C` and others are borrowed from 
languages like `C++` and `TypeScirpt`.

## bool
The `bool` type is the same as that in `C++` or other languages:

```c++
bool x = true;
bool y = false;
```

## number
The `int`/`float`/`double` type is the same as that in `C` or `C++`:

```c++
int x = 10;
float y = 1.0f;
double z = 2.0;
```

Since `crimson` is a strong-type language, you must use `f` to indicate that the literal is a float variable rather than a double one:

```c++
float x = 2.0; // wrong
```

We still don't provide big number calculations.

## string
the `string` type now is a primitive type in `crimson`, just like `C#`. We also preserve the `char` type:

```c++
string x = "hello";
char y = 'a';
```

## array
The behavior of arrays is more likely to `C#`:

```c++
int[] x = int[2];
float[] y = float[] {0.0f, 0.0f, 0.0f};
bool[] z = new bool[5]; // false for all elements initially
```

## enum
You can also use `enum` in `crimson`. Instead, you never need to write `enum class` like codes in `C++`:

```c++
enum {
    R = 0,
    G, // = 1
    B // = 2
}
```

## any
The `any` type is the supertype of all other types.

## void
The `void` type is the same as that in `C`:

```c++
void print(int x) {
    // ...
}
```


## never
The `never` type is borrowed from `TypeScript`. It indicates that this function will never return:

```c++
never run() {
    while (true) {
        // ...
    }
}
```

The `never` is also a subtype of all other types.

## object
The `object` type is the supertype of all structures. A pure object variable may be useless because it contains nothing:

```c++
void foo(object obj) {
    // ...
}

struct Foo {
    int y;
}

Foo f;
foo(f); // ok!
```

## Type Assert
You can convert a variable with some type to another variable with another type:

```c++
any x = 12;
int y = x as int;
```

Please make sure that the logic of asserts is correct before using it!
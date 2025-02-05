# tampilf - A Lightweight Custom Print Function with Color Support

**tampilf** is a custom implementation of a formatted output function similar to `printf` in C, with added support for text coloring. It allows users to format various types of data and print them to the console while enabling custom colors (like red, green, blue, etc.) for text output.

## Features

- Print various types of data:
  - Characters (`%c`)
  - Strings (`%s`)
  - Integers (`%d`, `%i`)
  - Unsigned integers (`%u`)
  - Floating point numbers (`%f`, `%l`)
  - Hexadecimal (`%x`, `%X`)
  - Octal (`%o`)
  - Binary (`%b`)
  - Pointers (`%p`)
  - Size types (`%z`)
  
- Text coloring support with `{red}`, `{green}`, `{blue}`, and more.  
- The format resets to default color after each colorized print.

## Installation

To use the `tampilf` library in your C projects, you need to compile the source files and link them in your project.

### 1. Clone the repository (or use the source files)

```bash
git clone https://github.com/yourusername/tampilf.git
cd tampilf
```

### 2. Compile the library
You can build the library using provided `Makefile`.
Run the following command:


```bash
make
```
This will create a static library (libtampilf.a) and a shared library (libtampilf.so)

### 3. Install the library (optional)
If you want install library globally for use in other projects, use the following command:


```bash
make install

```
This will install the static and shared libraries to the `$PREFIX/lib` directory.

### 4. Include in your project
To use the `tampilf` library in your own project, include the header file and link the compiled library.

In your C code:

```c
#include "tampilf.h"

```

When compiling your project:

```bash
gcc -o my_program main.c -L/path/to/tampilf/libs -ltampilf
```

### 5. Link with the library

Ensure you link against `libtampilf.a` or `libtampilf.so` when compiling your project

## Usage

Here's how you can use the `tampilf` function to print formatted strings with color.

> Basic Examples

```c
#include "tampilf.h"

int main()
{
    tampilf("{red} This is the red text!\n");
    tampilf("{green} This is the green text!\n");
    tampilf("{blue} This is the blue text!\n");
    tampilf("This is the normal text!\n");

    return 0;
}

```

**Available Colors**

- {red} - Red text
- {green} - Green text
- {blue} - Blue text

Colors are reset after each colorized print automatically.

> Functions

`tampilf`
The `tampilf` function is used to print out formatted strings with support for text color and variable arguments. It follows a format similar to `printf` in C.

**Syntax**

```c
void tampilf(const char *format, ...);
```

**Arguments**
- format: The format string containing placeholders for various types of data.
- Additional arguments (depending on format specifiers) will be printed accordingly.

**Example:**

```c
tampilf("Value of integer: %d\n", 42);
tampilf("Hexadecimal: %x\n", 255);
tampilf("Pointer address: %p\n", main);
```

**Color Support**
You can embed color in the format string using curly braces `{}`.  
The supported colors are:

- {red} - Red
- {green} - Green
- {blue} - Blue

**Example:**

```c
tampilf("{red}This is the red text\n");
tampilf("{blue}This is the blue text\n");
```

The format will reset to default color after the colorized text.

## LICENSE
This project is licensed under MIT License  
see the [LICENSE](https://github.com/aazis7/tampilf.git/blob/main/LICENSE) for details.

## Contribs
Feel free to fork the [repository](https://github.com/aazis7/tampilf.git), make improvements, and create a pull request. Contributions are welcome!

## Final Touch

### Optimizations and Enhancements

As with any C project, there are always opportunities to optimize and enhance the code further. Here are a few areas you may consider for future improvements:

- **Buffer Overflows**: The `tampilf` function uses a fixed-size buffer (`output[1024]`). Consider dynamically allocating memory for larger outputs to prevent potential buffer overflow issues in more complex projects.
  
- **Error Handling**: Currently, the function assumes valid input for all cases. You may want to add error handling mechanisms for malformed format specifiers, memory allocation failures, and unsupported color codes.

- **Color Codes Expansion**: The current implementation supports basic colors like red, green, and blue. Expanding this functionality to support more colors or even background colors would make this tool more flexible.

- **Performance Improvements**: Depending on usage scenarios, consider benchmarking and optimizing the string processing and integer-to-string conversion functions for performance, especially if the function is used in performance-critical applications.

### Compatibility

- The current implementation uses basic system calls for I/O (`write`). This should be compatible with most Unix-like systems (Linux, macOS). If you're targeting other platforms or need to redirect output to different destinations (such as a file), you may need to modify the `sys_write` function to allow more flexibility in output destinations.

- The color codes rely on ANSI escape sequences, which are widely supported in modern terminal emulators but may not work on older systems or terminals that do not support ANSI codes.

### Expanding Functionality

You can also extend this project by adding more complex formatting features, such as:

- **String Padding**: Supporting left/right padding and truncation for fixed-width output.
- **Alignment**: Printing numbers or text with specific alignment (left, right, center).
- **Date and Time Formatting**: Add the ability to format and display current dates and times in the output.

### Community Contributions

We welcome contributions to enhance this project. Feel free to fork the repository, open an issue, or submit a pull request. When contributing, please follow these guidelines:

1. Ensure that new features are well-documented.
2. Add unit tests or example usage for any new functionality.
3. Follow C coding standards and formatting conventions.
4. Provide a clear explanation of the changes you are proposing.

### Thank You

We appreciate you using **tampilf** in your projects. Don't hesitate to reach out with any questions, suggestions, or feedback. Happy coding! 🎉, [@aazis7](https://github.com/aazis7)

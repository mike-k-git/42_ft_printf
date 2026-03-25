_This project has been created as part of the 42 curriculum by mkugan._

# FT_PRINTF

## Description
`libftprintf` is a custom implementation of the `printf` function, supporting a variety of format specifiers and flags, as specified by the C standard library. This project aims to replicate the behavior of `printf` for formatting and printing different types of data.

### Files

#### Source Code:
The library is made of several `.c` files, including:
- `ft_printf.c`: Main `printf` implementation.
- `ft_itoa.c`: Integer to string conversion.
- `parser.c`: Parsing format specifiers.
- `utils.c`: Utility functions.
- `process_[type].c`: Functions for handling various specifiers (e.g., `%d`, `%s`, `%x`).

#### Header File:
- `libftprintf.h`: Contains function declarations and type definitions.

## Instructions
Clone the repository:
```bash
git clone https://github.com/yourusername/libftprintf.git
cd libftprintf
```

To build the library, use the `Makefile`:
```bash
make
```
This will compile the library into `libftprintf.a`.

Bonus functionality (optional):
```bash
make bonus
```

Clean the object files:
```bash
make clean
```

Fully remove compiled files:
```bash
make fclean
```

Rebuild:
```bash
make re
```

## Functions
The library provides a custom `ft_printf` function which mimics the standard `printf`. It supports the following format specifiers:
- `%c`: Character
- `%s`: String
- `%d` or `%i`: Integer
- `%u`: Unsigned integer
- `%x` / `%X`: Hexadecimal (lowercase/uppercase)
- `%p`: Pointer
- `%%`: Percent sign


### Example Usage
```C
#include "libftprintf.h"

int main() {
    int result = ft_printf("Hello %s, the number is %d.\n", "World", 42);
    return 0;
}
```

Output:
```bash
Hello World, the number is 42.
```

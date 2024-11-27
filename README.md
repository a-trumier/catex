# CATEX

A lightweight and straightforward C library for generating LaTeX documents. This project is designed to be simple, flexible, and easy to use, making it ideal for those who want to integrate LaTeX generation into their C projects or create custom variations of the library.

## Features

- **Single Header File**: Everything you need is in one header file for convenience and ease of integration.
- **Minimalistic Design**: No complex dependencies—just plain C code.
- **Customizable**: Designed for users to copy, rewrite, and adapt the library for their own use cases.
- **Focus on Simplicity**: Ideal for those who value a clean and understandable codebase.

## Getting Started

1. Follow the installation instructions below.
2. Include the header in your C code:
   ```c
   #include "catex.h"
   ```
3. Done! Use the library as you wish.

## Installation

### Linux

#### Requirements
1. A compiler such as GCC or clang
2. ar and fpic command

#### Steps
1. Clone to a directory of your choosing by using the following command:
    ```console
    $ git clone https://github.com/a-trumier/catex
    ```
2. Move into the directory 
    ```console
    $ cd catex
    ```
3. Use the make command followed by choosing a compiler. The default is gcc.
If you would want a different compiler, just change the CC variable. For
example, if you want to use clang, do the following command:
    ```console
    $ make CC="clang"
    ```
4. This will make both a .so file into include and a .a file. If you want only
a dynamic or archive file, do the following:
    ```console
    $ make dynamic
    ```
    or
    ```console
    $ make static
    ```

5. Done! Now the library is ready to use.

## Contributing
Contributions are welcome! Feel free to:

1. Submit pull requests.
2. Open issues for bugs or feature requests.
3. Fork the project and make your own variations.

Note: The project is set up to ignore anything in the directory test/. Feel
free to update information there.

## License
This project is licensed under the GNU GPLv3 License. See the LICENSE file for details.

## Why Another LaTeX Library?
Many existing libraries are powerful but overly complex for small projects or learning purposes. This library focuses on simplicity and adaptability, empowering developers to tailor it to their needs or learn from its straightforward design.

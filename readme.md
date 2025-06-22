# Caesar Cipher Tool

## Introduction

This program is designed for beginners in encryption, providing a simple yet practical implementation of the Caesar cipher. The Caesar cipher is a substitution cipher where each letter in the plaintext is shifted a fixed number of places in the alphabet. It is one of the oldest encryption techniques and serves as a great introduction to cryptographic concepts.

## Features

- Encrypts text by shifting letters to the right.
- Decrypts text by shifting letters to the left.
- Accepts input via keyboard or file.
- Supports English and Spanish alphabets.
- Allows selecting a specific encryption level or performing bulk encryption/decryption (all levels from 1 to 25 in English or 1 to 26 in Spanish).
- Command-line interface with various flags for customization.
- Supports combining flags (e.g., `-eksl` instead of `-e -k -s -l`).
- Flags can be provided separately with values (e.g., `-e -s "Hello, World!" -l 3`) or combined (e.g., `-esl "Hello, World!" 3`).

## Installation & Compilation

A `Makefile` is provided for easy compilation. Simply run the following command in the terminal:

```sh
make
```

This will compile all necessary files and generate the executable.

## Usage

### Running Without Parameters

If no parameters are provided, the program will interactively ask the user for input and options.

### Running With Parameters

The program supports multiple flags:

```
-h    Display help.
-i    Display information.
-w    Display warranty.
-c    Display conditions.
-e    Encrypt the message.
-d    Decrypt the message.
-s    Indicates the input is a text string.
-f    Indicates the input is a file.
-k    Choose the language ('en' for English, 'sp' for Spanish). Default is English.
-l    Specify encryption/decryption level. If omitted, bulk transformation is performed.
```

### Examples

Encrypt a string with level 3 in English:

```sh
caesar -e -s "Hello, World!" -l 3
```

Or using combined flags:

```sh
caesar -esl "Hello, World!" 3
```

Decrypt a file with bulk decryption in Spanish:

```sh
caesar -d -k sp -f "input.txt"
```

Or using combined flags:

```sh
caesar -dkf sp "input.txt"
```

## License

This project is licensed under the GPL, meaning users can modify and distribute it freely.

## Contributing

Since this is a GPL-licensed project, users are encouraged to contribute by adding improvements or additional language support.

---

If you have any questions or encounter issues, feel free to reach out or modify the code as needed!


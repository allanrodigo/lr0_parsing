
# LR(0) Parsing Project

This project implements an LR(0) parser for a language defined by a specific grammar. It reads an input string, processes it to remove spaces and replace lowercase letters with 'x', and verifies if the string belongs to the language using an LR(0) parsing table.

## Grammar

The grammar used is as follows:

```
S → (E)
S → x
E → S
E → E+S
```

## Project Structure

```
C:.
├───Makefile
├───README.md
├───include
│   ├── parser.h
│   └── transducer.h
└───src
    ├── main.c
    ├── parser.c
    └── transducer.c
```

## Files

- **main.c**: Contains the `main` function that reads user input, processes the input, and calls the parsing function.
- **transducer.h** and **transducer.c**: Contain the logic for processing the input, removing spaces, and replacing lowercase letters.
- **parser.h** and **parser.c**: Contain the implementation of the LR(0) parser with the action table and auxiliary functions.
- **Makefile**: Contains instructions to compile the project.

## Compilation and Execution

To compile the project, use the `Makefile`:

```sh
make
```

This will generate an executable called `main.exe` (or `main` on Linux).

To run the program, use the following command:

```sh
./bin/main.exe
```

You will then be prompted to enter an input string.

## Usage Example

Here is an example of how to use the program:

```sh
$ ./bin/main.exe
Enter the input string: (x+x)
Input string is accepted.
```

If the string does not belong to the language, the program will reject it:

```sh
$ ./bin/main.exe
Enter the input string: a+b
<REJECT>
```

## Contributing

1. Fork the project.
2. Create a branch for your feature (`git checkout -b feature/new-feature`).
3. Commit your changes (`git commit -am 'Add new feature'`).
4. Push to the branch (`git push origin feature/new-feature`).
5. Create a new Pull Request.

## License

This project is licensed under the [MIT License](LICENSE).

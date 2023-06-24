# Huffman Data Compression Algorithm

This repository contains an implementation of the Huffman data compression algorithm in C++. The Huffman algorithm is a lossless compression algorithm used to reduce the size of data while allowing for exact recovery of the original data. It is commonly used in communications, archiving, and some audio and image compression algorithms.

## Dependencies

The program requires the following dependencies:

- C++17 standard libraries

## Build

To build the program, follow these steps:

1. Clone the repository to your local machine.
2. Navigate to the root directory of the repository.
3. Run the following command to build the program:

```
make build
```

This command will generate the executable `Huffman` in the `bin` directory.

## Usage

The program provides a console interface for encoding and decoding files using the Huffman algorithm.

### Encoding (Compression)

To compress a file, run the following command:

```
./bin/Huffman
```

Replace `<source_file_path>` in the app with the absolute path to the file you want to compress. The program will generate two output files: `<source_file_name>_encoded` (compressed file) and `huffman.cfg` (configuration file containing the Huffman tree). The locations of these files can be set during program execution.

### Decoding

To decode a compressed file, run the following command:

```
./bin/Huffman
```

Replace `<compressed_file_path>` in the app with the absolute path to the compressed file, and `<config_file_path>` with the absolute path to the configuration file (`huffman.cfg`). The program will output a new decoded file in the format `<source_file_name>_decoded`. The location of this file can be set during program execution.

## Development

If you want to contribute to the development of this project, please follow these guidelines:

- Write your code in C++17 and follow the Google style guide.
- Avoid using outdated language constructs and libraries.
- Provide a Makefile for building the program and running tests.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
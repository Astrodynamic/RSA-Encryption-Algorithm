# RSA Encryption Algorithm

## Description
The RSA Encryption Algorithm is an implementation of the RSA (Rivest-Shamir-Adleman) asymmetric encryption algorithm. RSA is a widely used public-key cryptosystem that provides secure data transmission and digital signature generation.

This program is developed in C++ language, adhering to the C++17 standard. It offers a console interface for generating key pairs, encrypting files, and decrypting files using the RSA algorithm. The program supports encryption and decryption of both text and binary files.

## Dependencies
The following dependencies are required to build and run the RSA Encryption Algorithm:

- C++17 compiler
- CMake (version 3.5 or higher)

## Build
To build the program, follow these steps:

1. Clone the repository to your local machine.
2. Navigate to the repository directory.
3. Run the following commands:

```bash
cmake -S ./ -B ./build -DCMAKE_BUILD_TYPE=Release
cmake --build ./build --config Release
```

This will generate the executable file `RSA` in the `bin` directory.

## Usage
The RSA Encryption Algorithm program supports the following modes:

1. Key Generation Mode:
   - Input: Absolute path to the directory where the keys will be generated.
   - Output: Two files (`private_key` and `public_key`) in the specified directory.

2. Encryption Mode:
   - Input: Absolute path to the source file and the file containing the public key.
   - Output: Encrypted file in the format `<source_file_name>_encoded`.

3. Decryption Mode:
   - Input: Absolute path to the source file and the files containing the public and private keys.
   - Output: Decrypted file in the format `<source_file_name>_decoded`.

## Development
If you want to contribute to the RSA Encryption Algorithm development, follow these guidelines:

- The program code is located in the `src/rsa` folder.
- Follow the Google C++ style guide when writing code.
- Use modern C++17 language features and avoid outdated constructs and libraries.
- Provide a Makefile with the following targets:
  - `all`: Builds the program.
  - `clean`: Cleans the build artifacts.
  - `test`: Runs the tests.

## License
The RSA Encryption Algorithm is licensed under the [MIT License](LICENSE). Feel free to modify and distribute it according to the terms of the license.
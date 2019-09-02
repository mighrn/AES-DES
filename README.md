# AES-DES
## Using the AES and DES algorithms to encrypt/decrypt contents of file
### Miguel Hernandez
### mig220@csu.fullerton.edu


Written in C++


To compile: In a terminal type:
```
make
```

To run: In a terminal type:
```
./cipher <CIPHER NAME> <KEY> <ENC/DEC> <INPUT FILE> <OUTPUT FILE>
```
Options:
```
<CIPHER NAME> Choose either AES or DES
<KEY> Encryption key must be a 16 digit hexadecimal number representing 128 bits for AES or 64 bits for DES
<ENC/DEC> Choose only one for Encryption or Decryption respectively
<INPUT FILE> Filename or path to read input
<OUTPUT FILE> Filename or path to write output
```

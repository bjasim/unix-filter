# EncodeInput
EncodeInput is a Linux utility written in C that takes binary input data and transforms it into either an S-Record or Assembly File format. It supports various command-line options for customization.

## Usage

To compile EncodeInput, use the provided makefile:
```bash
make
```

##Command-Line Options
-i INPUTFILENAME: Specify the input binary file (default is stdin).
-o OUTPUTFILENAME: Specify the output file (default is generated based on input).
-srec: Generate output in S-Record format (default is Assembly File format).
-h: Display usage information.
## Examples
Convert binary input to S-Record format:
```bash
./encodeInput -i input.bin -o output.srec -srec
```
Convert binary input to Assembly File format:
```bash
./encodeInput -i input.bin -o output.asm
```
Display usage information:
```bash
./encodeInput -h
```

## Sample Input
A sample binary input file (binary-input-file.bin) is included in the project. You can use it to test the utility.

To view the binary content of the file, you can use the od or hexdump command:
```bash
od -x --endian=big binary-input-file.bin
# OR
od -t x1 binary-input-file.bin
# OR
hexdump binary-input-file.bin
```


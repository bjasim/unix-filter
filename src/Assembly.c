/*
* Filename:    Assembly.c
* Project:     encodeInput
* Author:      Bakr Jasim
* Date:        2022-02-05
* Description: This is the file that contains all the functions and logic for converting contents in a file
* or on stdin to assembly formatted data, and put in a file or display on terminal depending on the commands passed.
*/

#include "../inc/encodeInput.h"

int file_to_assembly(const char *input_file, const char *output_file, bool bInput, bool bOutput)
{
	char output_file_copy[100];
	FILE *fp_in, *fp_out;
	const char *Output_extension; 


	if ((bInput == false) && (bOutput == false))
	{
		fp_in = stdin;
		fp_out = stdout;
	}
	else if((bInput == true) && (bOutput == true))
	{
		if(access(input_file, F_OK) != 0)
		{
			perror("fopen");
			return 1;
		}
		fp_in = fopen(input_file, "rb");

		strcpy(output_file_copy, output_file);
        strcat(output_file_copy, ".asm");
		fp_out = fopen(output_file_copy, "w");

        if(access(output_file_copy, F_OK) != 0)
        {
            perror("fopen");
            return 1;
        }
	}

	else if((bInput == true) && (bOutput == false))
	{
		if(access(input_file, F_OK) != 0)
		{
			perror("fopen");
			return 1;
		}
		fp_in = fopen(input_file, "rb");

		strcpy(output_file_copy, input_file);
		Output_extension = strrchr(output_file_copy, '.');

		if (Output_extension != NULL && strcmp(Output_extension, ".asm") != 0) 
		{
			strcat(output_file_copy, ".asm");
		}
		fp_out = fopen(output_file_copy, "w");
		if(access(output_file_copy, F_OK) != 0)
		{
			perror("fopen sdfdgfsfg");
			return 1;
		}
	}

	else if ( (bInput == false) && (bOutput == true)) 
	{
		fp_in = stdin;
		strcpy(output_file_copy, output_file);
		Output_extension = strrchr(output_file_copy, '.');

		if (Output_extension != NULL && strcmp(Output_extension, ".asm") != 0) 
		{
			strcat(output_file_copy, ".asm");
		}
		fp_out = fopen(output_file_copy, "w");
		if(access(output_file_copy, F_OK) != 0)
		{
			perror("fopen sdfdgfsfg");
			return 1;
		}

	}
	
	unsigned char buf[256];
	size_t n;
	int count = 0;

	while((n = fread(buf, sizeof(unsigned char), 256, fp_in)) > 0)
	{
		char hex[256 * 2 + 1];
		byteToHex(buf, hex, n);

		int i = 0;
		while (i < n * 2) 
		{
		int lineLen = (n * 2 - i >= 32) ? 32 : n * 2 - i;
		fprintf(fp_out, "dc.b ");

		char line[lineLen + 1];
		strncpy(line, hex + i, lineLen);
		line[lineLen] = '\0';
		for (int j = 0; j < lineLen; j += 2)
		{
			fprintf(fp_out, "$%c%c", line[j], line[j + 1]);
			if (j + 2 < lineLen)
			{
			fprintf(fp_out, ", ");
			}
		}
		fprintf(fp_out, "\n");

		i += lineLen;
		}
	}

	if (fp_in != stdin) 
	{
		fclose(fp_in);
	}
	if(fp_out != stdout)
	{
		fclose(fp_out);
	}
	return 0;
}


// /*
// * Function: byteToHex
// * Desription: This function is used to convert the data from the file to a hexadecimal format to print it to a file or on stdout
// * Parameter: *buffer: the data from file
// 			*hex: is the hex value
// 			bInput: is the length
// * Return: no return
// */

void byteToHex(const unsigned char *buffer, char *hex, size_t length)
{
	for(size_t i = 0; i< length; i++)
	{
		sprintf(hex + i * 2, "%02X", buffer[i]);
	}
}

// /*
// * Function: usageStatement
// * Desription: This function is used to print the usage statement on the screen for the user
// * Parameter: no parameters
// * Return: no returns 
// */

void usageStatement(void)
{
      printf("\nUsage statement: You can use any/or all of the following in any order\n");
      printf("     -iINPUTFILENAME [name of program]/[[input data from standard input]\n");
      printf("     -oOUTPUTFILENAME [name of output]\n");
      printf("     -srec: Output in the S-record format\n");
      printf("     -h: Output help information to the console and exit\n\n");
}


/*
* Filename:    sRecord.c
* Project:     encodeInput
* Author:      Bakr Jasim
* Date:        2022-02-05
* Description: This is the file that contains all the functions and logic for converting contents in a file
* to s-Record formatted data, and put in a file depending on the commands passed.
*/

#include "../inc/encodeInput.h"

int file_to_srec(const char *input_file, const char *output_file, bool bSrec, bool bInput, bool bOutput)
{
	char output_file_copy[100];
	const char *Output_extension;

	FILE *fp_in, *fp_out;
	if((input_file == NULL) && (output_file == NULL))
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
        strcat(output_file_copy, ".srec");
		fp_out = fopen(output_file_copy, "w");

        if(access(output_file_copy, F_OK) != 0)
        {
            perror("fopen");
            return 1;
        }
	}
	if ((bOutput == false) && (bInput == true))
	{
		if(access(input_file, F_OK) != 0)
		{
			perror("fopen");
			return 1;
		}
		fp_in = fopen(input_file, "rb");

		strcpy(output_file_copy, input_file);
		Output_extension = strrchr(output_file_copy, '.');

		if ((Output_extension != NULL) && (strstr(output_file_copy, ".srec") != 0) )
		{
			strcat(output_file_copy, ".srec");
		}
		fp_out = fopen(output_file_copy, "w");
		if(access(output_file_copy, F_OK) != 0)
		{
			perror("fopen");
			return 1;
		}
	}

	unsigned char buf[256];
	size_t n;
	unsigned int address = 0;
	int count = 0;
	char name[] = "BAKR";
	int name_len = strlen(name);
	unsigned char name_buf[16];
	for(int i = 0; i < name_len && i < 16; i++)
	{
		name_buf[i] = name[i];
	}
	char s0_record[20];
	sprintf(s0_record, "S0%02X%04X", (unsigned int)name_len + 3, 0);
	byteToHex(name_buf, buf, name_len);
	strcat(s0_record, buf);
	unsigned char checksum = cal_checksum(s0_record);
	fprintf(fp_out, "%s%02X\n", s0_record, checksum);

	while((n=fread(buf, sizeof(unsigned char), 256, fp_in)) > 0)
	{
		// write_s1_record(fp_out, address, buf, n);
		char hex[256 * 2 + 1];
		byteToHex(buf, hex, n);

		int i = 0;
		while (i < n * 2) 
		{
			int lineLen = (n * 2 - i >= 32) ? 32 : n * 2 - i;
			fprintf(fp_out, "S1%02X%04X", (unsigned int)lineLen / 2 + 3, address);
			char line[70];
			memset(line, 0, sizeof(line));
			strncpy(line, &hex[i], lineLen);
			// strcat(line, "\n");
			i += lineLen;
			address += lineLen / 2;
	        checksum = cal_checksum(line);
    	    fprintf(fp_out, "%s%02X\n", line, checksum);
		}
	}

	fprintf(fp_out, "S503%02X%04X\n", (unsigned int)count + 1, count * 256);
	// checksum = cal_checksum("S5030000");
	// fprintf(fp_out, "%02X\n", checksum);


	fprintf(fp_out, "S9030000FC\n");
	// checksum = cal_checksum("S9030000FC");
	// fprintf(fp_out, "%02X\n", checksum);

  

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

/*
* Function: calc_checksum
* Desription: This function is used to calculate the checksum that will be at the end of every sRecord that I will printing to a file/terminal
* Parameter: *input_file: the name of the input file
			*Output_file: the name of the output file
			bInput: is a boolean for input command
			bOutput: is boolean for output command
* Return: no returns 
*/

unsigned char cal_checksum(const char *record)
{
	unsigned char checksum = 0;
	size_t len = strlen(record);
	for(size_t i = 2; i < len; i += 2)
	{
		checksum += (unsigned char)strtol(record + i, NULL, 16);
	}
	return ~checksum + 1;
}

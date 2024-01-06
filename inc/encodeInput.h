/*
* Filename:    cryptoMagic.h
* Project:     cryptoMagic
* Author:      Bakr Jasim
* Date:        2022-01-22
* Description: This is the header file that contains two function parameters, those functions are called in the main * function in order to decrypt/encrypt the specified file depending on the command entered by the user.
*/


#ifndef ENCODEINPUT_H
#define ENCODEINPUT_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stddef.h>


int file_to_assembly(const char *input_file, const char *output_file, bool bInput, bool bOutput);
void byteToHex(const unsigned char *buffer, char *hex, size_t length);
void usageStatement(void);
int file_to_srec(const char *input_file, const char *output_file, bool bSrec, bool bInput, bool bOutput);
unsigned char cal_checksum(const char *record);


#endif


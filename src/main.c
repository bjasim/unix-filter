// /*
// * Filename:    main.c
// * Project:     encodeInput
// * Author:      Bakr Jasim
// * Date:        2022-02-05
// * Description: This is the main function of the cryptoMagic utility, and the purpose of this main function is to
// * process command line arguments from the user and use it call other functions depending on the commands entered by user.
// */

#include "../inc/encodeInput.h"

int main(int argc, char *argv[])
{
	char *iFileName = NULL;
	char *oFileName = NULL;

	char *input = NULL;
	char *output = NULL;
	char *srec = NULL;

	bool bInput = false;
	bool bOutput = false;
	bool bSrec = false;

	bool bInputFile = false;
	bool bOutputFile = false;

	bool iFileExists = false;
	bool oFileExists = false;
	
	if(argc <= 5)
	{
		for(int i = 1; i < argc; i++)
		{
			if(strncmp(argv[i], "-i", 2) == 0)
			{
				input = argv[i];
				bInput = true;
				if(strlen(input) > 2)
				{
					bInputFile = true;
					iFileName = input + 2;
				}

            }			
			if( (strncmp(argv[i], "-o", 2) == 0)  )
		    {
		        bOutput = true;
				output = argv[i];
				if(strlen(output) > 2)
				{
					bOutputFile = true;
					oFileName = output + 2;
				}
            }

			if (strcmp(argv[i], "-srec") == 0)
			{
				bSrec = true;
				srec = argv[i];
			}

			if (strcmp(argv[i], "-h") == 0)
			{
		        usageStatement();
			}
	    }
		if (bSrec == true)
		{
			file_to_srec(iFileName, oFileName, bSrec, bInput, bOutput);
		}
		else if(bSrec == false) 
		{
			//generate assembly file, and call function
			file_to_assembly(iFileName, oFileName, bInput, bOutput);
		}
	}

    return 0;
}

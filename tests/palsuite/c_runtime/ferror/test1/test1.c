/*=====================================================================
**
** Source:  test1.c
**
** Purpose: Tests the PAL implementation of the ferror function.
**
** Depends:
**     fopen
**     fread
**     fclose
**     
**
** 
**  Copyright (c) 2006 Microsoft Corporation.  All rights reserved.
** 
**  The use and distribution terms for this software are contained in the file
**  named license.txt, which can be found in the root of this distribution.
**  By using this software in any fashion, you are agreeing to be bound by the
**  terms of this license.
** 
**  You must not remove this notice, or any other, from this software.
** 
**
**===================================================================*/

#include <palsuite.h>

int __cdecl main(int argc, char **argv)
{
    const char filename[] = "testfile";
    char buffer[128];
    FILE * fp = NULL;
    int result;

    if (PAL_Initialize(argc, argv))
    {
        return FAIL;
    }

  
    /* Open a file in READ mode */

    if((fp = fopen(filename, "r")) == NULL)
    {
        Fail("Unable to open a file for reading.  Is the file "
               "in the directory?  It should be.");
    }

    /* Read 10 characters from the file.  The file has 15 
       characters in it.
    */
  
    if((result = fread(buffer,1,10,fp)) == 0)
    {
        Fail("ERROR: Zero characters read from the file.  It should have "
               "read 10 character in from a 15 character file.");
    }
  
    if(ferror(fp) != 0)
    {
        Fail("ERROR:  ferror returned a value not equal to 0. The read "
               "operation shouldn't have caused an error, and ferror should "
               "return 0 still.");
    }
  
    /* 
       Close the open file and end the test.
    */

    if(fclose(fp) != 0)
    {
        Fail("ERROR: fclose failed when trying to close a file pointer. "
               "This test depends on fclose working properly.");
    }

    PAL_Terminate();
    return PASS;
}
   


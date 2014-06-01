/** ErrorManager.cpp -- Code file for ErrorManager class used throughout the engine
  * Peter Turner - Summer 2012
  */
#include "stdafx.h"
#include "ErrorManager.h"

//----------------------------------------------------------------------------

ErrorManager::ErrorManager() {}

//----------------------------------------------------------------------------

ErrorManager::~ErrorManager() {}

//----------------------------------------------------------------------------
   
ErrorCode ErrorManager::StartUp(WCHAR *fileName) 
{
   // Clear the Buffers
   for (int i = 0; i < NUM_ERRORS; i++) 
   {
      for (int j = 0; j < BUF_LENGTH; j++) 	  
	  {
         outputStrings[i][j] = 0;
      }
   }

   if (fileName == NULL) 
   {
      return Error_FileOpenFail;
   } 
   else 
   {
      FILE *fp = _wfopen(fileName, L"r");
      if (!fp) 
	  {
         return Error_FileOpenFail;
      } 
	  else 
	  {
         WCHAR buffer[BUF_LENGTH];
         UINT errorCounter = 0;
         while (!feof(fp)) 
		 {
            // Clear Buffer
            for (UINT k = 0; k < BUF_LENGTH; k++) 
			{
               buffer[k] = 0;
            }
            fgetws(buffer, BUF_LENGTH, fp);
            
            UINT j = 0;
            while (buffer[j] != 0) 
			{ 
               if (j > BUF_LENGTH) 
			   { 
				   // Line longer than our buffer
                   return Error_FileReadFail;
               } 
			   else 
			   {
                  outputStrings[errorCounter][j] = buffer[j];
                  j++;               
               }
            }
            errorCounter++;
            if (errorCounter > NUM_ERRORS) 
			{ 
				// More errors than we defined
                return Error_FileReadFail;          
            }              
         }
         fclose(fp);
      }
   }
   return OK;
}

//----------------------------------------------------------------------------

WCHAR *ErrorManager::GetStringById(ErrorCode errorId) 
{
   if (errorId < 0 || errorId > NUM_ERRORS) 
   {
      return outputStrings[Error_Unknown];
   } 
   else 
   {
      return outputStrings[errorId];
   }
}
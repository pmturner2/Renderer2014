/** ErrorManager.h -- Header file for ErrorManager class used throughout the engine
  * Peter Turner - Summer 2012
  */
#pragma once;
enum ErrorCode {
   OK = 0, 
   Error_FileOpenFail,
   Error_FileReadFail,
   Error_D3D,
   Error_FX,
   Error_InvalidParameter,
   Error_Buffer,
   Error_MemoryAllocation,
   Error_DivByZero,
   Error_AllocatingResource,
   Error_Unknown
};

/** class ErrorManager - Error handler
 * 
 */
class ErrorManager {
public:
   ErrorManager();
   ~ErrorManager();
   
   // Begins the Manager.  Parameter is file name containing strings
   ErrorCode StartUp(WCHAR *fileName);   
   
   WCHAR *GetStringById(ErrorCode errorId);

private:
   static const UINT BUF_LENGTH = 64;
   static const UINT NUM_ERRORS = 11;
   
   // Output Strings
   WCHAR outputStrings[NUM_ERRORS][BUF_LENGTH];
};









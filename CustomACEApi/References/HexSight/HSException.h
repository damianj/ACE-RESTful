// ****************************************************************************
//
// HSClassLibrary
//
// ****************************************************************************
//
// File.........: HSException.h
//
// Description..: This file contains the definition of class HSException
//                which is the base class for all exception-handling.
//
// Platforms....: All
//
// ****************************************************************************
//
//                Copyright (C) 2007 LMI Technologies.
//                All rights reserved
//
// ****************************************************************************
//
// $History:$
//
// ****************************************************************************

// class HSException
//		class HSArgumentException
//			class HSArgumentNullException
//			class HSArgumentOutOfRangeException
//		class HSArithmeticException
//			class HSDivideByZeroException
//			class HSNotFiniteNumberException
//			class HSOverflowException
//		class HSIndexOutOfRangeException
//		class HSInvalidOperationException
//		class HSIOException
//			class HSEndOfStreamException
//			class HSFileLoadException
//			class HSFileNotFoundException
//		class HSNotImplementedException
//		class HSNotSupportedException
//			class HSPlatformNotSupportedException
//		class HSOutOfMemoryException

#ifndef __HSEXCEPTION_H__
#define __HSEXCEPTION_H__

// ****************************************************************************
// * Constants
// ****************************************************************************

// ****************************************************************************
// * Types
// ****************************************************************************

// ****************************************************************************
// * Global data
// ****************************************************************************

// ****************************************************************************
// * Macros
// ****************************************************************************

// This is for Library export/import.  
// No define needed when using as a dynamic library
// HSSTATICLIBRARY defined at compilation when library used as a static library
// HSCLL_COMPILATION_DLL <Reserved>

#ifdef WIN32
	#ifdef HSCLL_COMPILATION_DLL
		#define HSCLL_EXPORT __declspec(dllexport)
	#else
		#ifdef HSSTATICLIBRARY
			#define HSCLL_EXPORT
		#else
			#define HSCLL_EXPORT __declspec(dllimport)
		#endif
	#endif
#else
	#define HSCLL_EXPORT
#endif


// Exception Class Template

#define HSEXCEPTION_CLASS(classname,baseclassname)\
class HSCLL_EXPORT classname : public baseclassname \
{\
public:\
	classname( const char *ErrorString  = NULL, const char *FileString = NULL, int LineNumber = 0 );\
};

// ****************************************************************************
// * Functions prototypes
// ****************************************************************************

// ****************************************************************************
// * Class definition
// ****************************************************************************

// Base Class

class HSCLL_EXPORT HSException 
{
public:

	         HSException( const char * ErrorString  = NULL, const char * FileString = NULL, int LineNumber = 0 );
	         HSException( const HSException & Exception );
	virtual ~HSException( void );
	
			 HSException &	operator=( const HSException & Exception );

	// Call this member function to report error :
	// -WIN32 : in a message box to the user.
	// -Other : printed to stderr.

	void ReportError( void );

	const char * GetDescription( void );
	const char * GetFileName( void );
	int GetLineNumber( void );

private:

	//const char * mDescription;
	char * mDescription;
	const char * mFileName;
	int mLineNumber;
};

HSEXCEPTION_CLASS( HSArgumentException, HSException )
HSEXCEPTION_CLASS( HSArgumentNullException, HSArgumentException )
HSEXCEPTION_CLASS( HSArgumentOutOfRangeException, HSArgumentException )
HSEXCEPTION_CLASS( HSArithmeticException, HSException )
HSEXCEPTION_CLASS( HSDivideByZeroException, HSArithmeticException )
HSEXCEPTION_CLASS( HSNotFiniteNumberException, HSArithmeticException )
HSEXCEPTION_CLASS( HSOverflowException, HSArithmeticException )
HSEXCEPTION_CLASS( HSIndexOutOfRangeException, HSException )
HSEXCEPTION_CLASS( HSInvalidOperationException, HSException )
HSEXCEPTION_CLASS( HSIOException, HSException )
HSEXCEPTION_CLASS( HSEndOfStreamException, HSIOException )
HSEXCEPTION_CLASS( HSFileLoadException, HSIOException )
HSEXCEPTION_CLASS( HSFileNotFoundException, HSIOException )
HSEXCEPTION_CLASS( HSNotImplementedException, HSException )
HSEXCEPTION_CLASS( HSNotSupportedException, HSException )
HSEXCEPTION_CLASS( HSPlatformNotSupportedException, HSNotSupportedException )
HSEXCEPTION_CLASS( HSOutOfMemoryException, HSException )
HSEXCEPTION_CLASS( HSBadImageException, HSException )
HSEXCEPTION_CLASS( HSColorImageNotSupportedException, HSBadImageException )

// ****************************************************************************
// * Inline functions definitions
// ****************************************************************************

#endif // __HSEXCEPTION_H__


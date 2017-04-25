// ****************************************************************************
//
// HSClassLibrary
//
// ****************************************************************************
//
// File.........: HSDatabase.h
//
// Description..: This file contains the definition of the HSDatabase class.
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

#ifndef __HSDATABASE_H__
#define __HSDATABASE_H__

// ****************************************************************************
// * Constants
// ****************************************************************************

// ****************************************************************************
// * Types
// ****************************************************************************

class HSView;
class HSImage;
class HSScene;
class HSPoint;
class HSLine;
class HSArc;

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

// ****************************************************************************
// * Class definition
// ****************************************************************************

class HSCLL_EXPORT HSDatabase 
{
public:

	// ENUMERATIONS

public:

	// UTILITY

	HSDatabase( void );
	HSDatabase( const HSDatabase & Object );
 	~HSDatabase( void );

	static HSDatabase * GetDatabaseFromHandle( unsigned int Handle, unsigned long Password = NULL );

	HSDatabase & operator=( const HSDatabase & Object );

public:

	// PROPERTY

    const char *	GetName( void ) const;
	void			SetName( const char * Value );

	const char *	GetInformation( void ) const;
	void			SetInformation( const char * Value );

    unsigned int	GetHandle( void ) const;

	unsigned long	GetPassword( void ) const;
	void			SetPassword( unsigned long Password );

    long			GetModifyCount( void ) const;

	// ** View ** //
    int				GetViewCount( void ) const;
    const HSView *	GetView( const char * ViewName ) const;
    HSView *		GetView( const char * ViewName );
    HSView *		AddView( const char * ViewName );
    void			RemoveView( const char * ViewName );
	void			RenameView( const char * ViewName, const char * NewViewName );
	void			AttachView( const HSView & View );
	const char *	GetViewName( int Index ) const;
	int				GetViewIndex( const char * ViewName ) const;
	bool			GetViewExists( const char * ViewName ) const;

public:

	// METHODS

    void			Load( const char * FileName );
    void			Save( const char * FileName );

	void			Modify( void );

    void			Reset( void );

	static void		SetDebugParameter( int Index, const void * Value, unsigned short Flag = NULL );
	static void		GetDebugParameter( int Index, void * Value, unsigned short * Flag = NULL );

protected:

	HSDatabase( void * );
	void * _pimpl;
};

#endif // __HSDATABASE_H__

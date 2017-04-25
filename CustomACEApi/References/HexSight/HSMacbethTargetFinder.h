// ****************************************************************************
//
// HSMacbethTargetFinder																 
//
// ****************************************************************************
//
// File.........: HSMacbethTargetFinder.h
//
// Description..: This file contains the definition of the HSMacbethTargetFinder class.
//
// Platforms....: WIN32
//
// ****************************************************************************
//
//                Copyright (C) 2006 LMI Technologies Inc.
//                All rights reserved
//
// ****************************************************************************
//
// $History:$
//
// ****************************************************************************

#ifndef __HSMACBETHTARGETFINDER_H__
#define __HSMACBETHTARGETFINDER_H__

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

#if _MSC_VER >= 1000
#pragma once
#endif 

// This is for Library export/import.  
// No define needed when using as a dynamic library
// HSSTATICLIBRARY defined at compilation when library used as a static library
// HSMACBETHTARGETFINDER_COMPILATION_DLL <Reserved>

#ifdef WIN32
	#ifdef HSMACBETHTARGETFINDER_COMPILATION_DLL
		#define HSMACBETHTARGETFINDER_EXPORT __declspec(dllexport)
	#else
		#ifdef HSSTATICLIBRARY
			#define HSMACBETHTARGETFINDER_EXPORT
		#else
			#define HSMACBETHTARGETFINDER_EXPORT __declspec(dllimport)
		#endif
	#endif
#else
	#define HSMACBETHTARGETFINDER_EXPORT
#endif

// ****************************************************************************
// * Class definition
// ****************************************************************************

class HSMACBETHTARGETFINDER_EXPORT HSMacbethTargetFinder
{
public:

	// ENUMERATIONS
	
	enum hsMacbethTargetFinderStatus
	{
		hsSuccess = 0,
		hsInternalError = 10,
		hsOutOfImage = 11,
		hsNoContours = 12,
		hsNoContoursInboundary = 13,
		hsNoSquares = 14,
		hsNoGrid = 15,
		hsNotFound = 16
	};

	// CONSTANTS

public:

	// UTILITY

					HSMacbethTargetFinder( void );
					HSMacbethTargetFinder( const HSMacbethTargetFinder & Object );
    virtual		   ~HSMacbethTargetFinder( void );

					HSMacbethTargetFinder & operator=( const HSMacbethTargetFinder & Object );

public:

	// Get/Set Database Handle

    unsigned int	GetDatabase( void ) const;
    void			SetDatabase( unsigned int Handle, unsigned long Password = NULL );

	// General ////////////////////////////////////////////////////////////////

	// Attributes //

	const char *	GetInputImage( void ) const;
	void			SetInputImage( const char * Name );
	const char *	GetInputView( void ) const;
	void			SetInputView( const char * Name );

	void			SetMacbethTargetBoundaryTop( float pValue );
	void			SetMacbethTargetBoundaryBottom( float pValue );
	void			SetMacbethTargetBoundaryLeft( float pValue );
	void			SetMacbethTargetBoundaryRight( float pValue );

	// Results ////////////////////////////////////////////////////////////////

	// Attributes //

	float			GetElapsedTime( void ) const;

	int				GetMacbethTargetSampleCount() const;
	bool			GetMacbethTargetFound( void ) const;

	hsMacbethTargetFinderStatus GetStatus( void ) const;

	float			GetMacbethTargetSampleCornerX( int SampleIndex, int CornerIndex ) const;
	float			GetMacbethTargetSampleCornerY( int SampleIndex, int CornerIndex ) const;
	float			GetMacbethTargetSampleCenterX( int SampleIndex ) const;
	float			GetMacbethTargetSampleCenterY( int SampleIndex ) const;

	int				GetMacbethTargetSampleR( int SampleIndex ) const;
	int				GetMacbethTargetSampleG( int SampleIndex ) const;
	int				GetMacbethTargetSampleB( int SampleIndex ) const;

	// Misc ///////////////////////////////////////////////////////////////////

	// Operations //

    float			Execute( void );

private:

	void * _pimpl;
};

// ****************************************************************************
// * Functions prototypes
// ****************************************************************************

// ****************************************************************************
// * Inline functions definitions
// ****************************************************************************

#endif // __HSMACBETHTARGETFINDER_H__

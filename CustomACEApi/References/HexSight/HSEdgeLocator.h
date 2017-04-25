// ****************************************************************************
//
// HSEdgeLocator																 
//
// ****************************************************************************
//
// File.........: HSEdgeLocator.h
//
// Description..: This file contains the definition of the HSEdgeLocator class.
//
// Platforms....: All
//
// ****************************************************************************
//
//                Copyright (C) 2004 LMI Technologies Inc.
//                All rights reserved
//
// ****************************************************************************
//
// $History:$
//
// ****************************************************************************

#ifndef __HSEDGELOCATOR_H__
#define __HSEDGELOCATOR_H__

// ****************************************************************************
// * Constants
// ****************************************************************************

// ****************************************************************************
// * Types
// ****************************************************************************

class HSImage;

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
// HSEDGELOCATOR_COMPILATION_DLL <Reserved>

#ifdef WIN32
	#ifdef HSEDGELOCATOR_COMPILATION_DLL
		#define HSEDGELOCATOR_EXPORT __declspec(dllexport)
	#else
		#ifdef HSSTATICLIBRARY
			#define HSEDGELOCATOR_EXPORT
		#else
			#define HSEDGELOCATOR_EXPORT __declspec(dllimport)
		#endif
	#endif
#else
	#define HSEDGELOCATOR_EXPORT
#endif

// ****************************************************************************
// * Class definition
// ****************************************************************************

class HSEDGELOCATOR_EXPORT HSEdgeLocator
{
public:

	// ENUMERATIONS

	enum hsUnitsLength
	{
		hsMeter = 0,
		hsCentimeter = 1,
		hsMillimeter = 2,
		hsMicron = 3,
		hsYard = 4,
		hsFoot = 5,
		hsInch = 6,
		hsMil = 7,
		hsCalibrationUnit = 8
	};

	enum hsUnitsOrientation
	{
		hsRadian = 0,
		hsDegree = 1
	};

	enum hsCoordinateSystem
	{
		hsCoordinateSystemImage = 0,
		hsCoordinateSystemWorld = 1,
		hsCoordinateSystemObject = 2,
		hsCoordinateSystemTool = 3
	};

	enum hsPolarityMode
	{
		hsDarkToLight	= 0,
		hsLightToDark	= 1,
		hsEither		= 2,
	};

	enum hsConstraint
	{
		hsNone				= 0,
		hsPosition			= 1,
		hsMagnitude			= 2,
		hsAllConstraints	= 3
	};

	enum hsPositionConstraintIndex
	{
		hsBaseLeft	= 1,
		hsTopLeft	= 2,
		hsTopRight	= 3,
		hsBaseRight	= 4
	};

	enum hsMagnitudeConstraintIndex
	{
		hsBase	= 1,
		hsTop	= 2
	};

	enum hsProcessingFormat
	{
		hsProcessingFormatNative = 0,
		hsProcessingFormatGreyScale = 1,
	};

public:

	// UTILITY

					HSEdgeLocator( void );
					HSEdgeLocator( const HSEdgeLocator & Object );
    virtual		   ~HSEdgeLocator( void );

					HSEdgeLocator & operator=( const HSEdgeLocator & Object );

	virtual int		ExchangeProp( 
						const char * PropName, 
						unsigned short PropType,
						void * PropPointer, 
						const void * PropDefault = NULL );

public:

	// Get/Set Database Handle

    unsigned int	GetDatabase( void ) const;
    void			SetDatabase( unsigned int Handle, unsigned long Password = NULL );

	// General ////////////////////////////////////////////////////////////////

	// Attributes //

	const char *	GetInputGreyScaleImage( void ) const;
	void			SetInputGreyScaleImage( const char * Name );
	const char *	GetInputGreyScaleView( void ) const;
	void			SetInputGreyScaleView( const char * Name );
	const char *	GetInputImage( void ) const;
	void			SetInputImage( const char * Name );
	const char *	GetInputView( void ) const;
	void			SetInputView( const char * Name );

	const char *	GetInputModelScene( void ) const;
	void			SetInputModelScene( const char * Name );
	const char *	GetInputModelView( void ) const;
	void			SetInputModelView( const char * Name );
	bool			GetModelTransformEnabled( void ) const;
	void			SetModelTransformEnabled( bool Enabled );

	const char *	GetInputInstanceScene( void ) const;
	void			SetInputInstanceScene( const char * Name );
	const char *	GetInputInstanceView( void ) const;
	void			SetInputInstanceView( const char * Name );
	bool			GetInstanceSelectionEnabled( void ) const;
	void			SetInstanceSelectionEnabled( bool Enabled );

	hsUnitsLength	GetUnitsLength( void ) const;
    void			SetUnitsLength( hsUnitsLength Units );

    hsUnitsOrientation GetUnitsOrientation( void ) const;
    void			SetUnitsOrientation( hsUnitsOrientation Units );

	bool			GetProcessingFormatEnabled( hsProcessingFormat pFormat ) const;
	hsProcessingFormat GetProcessingFormat( void ) const;
	void			SetProcessingFormat( hsProcessingFormat Value );

	// Operations //

	// Location ////////////////////////////////////////////////////////////////

	// Attributes //

	float			GetToolPositionX( void ) const;
	void			SetToolPositionX( float Value );
	float			GetToolPositionY( void ) const;
	void			SetToolPositionY( float Value );
	float			GetToolWidth( void ) const;
	void			SetToolWidth( float Value );
	float			GetToolHeight( void ) const;
	void			SetToolHeight( float Value );
	float			GetToolRotation( void ) const;
	void			SetToolRotation( float Value );
	float			GetToolSkew( void ) const;
	void			SetToolSkew( float Value );

	bool			GetCalibratedUnitsEnabled( void ) const;
	void			SetCalibratedUnitsEnabled( bool Value );

	// Sampling //

	bool			GetBilinearInterpolationEnabled( void ) const;
	void			SetBilinearInterpolationEnabled( bool Value );

	float			GetSamplingStep( void ) const;
	bool			GetSamplingStepCustomEnabled( void ) const;
	void			SetSamplingStepCustomEnabled( bool Value );
	float			GetSamplingStepCustom( void ) const;
	void			SetSamplingStepCustom( float Value );
	float			GetSamplingStepDefault( void ) const;

	// Transform ////////////////////////////////////////////////////////////////

	// Attributes //

	int				GetInstanceSelectionIndex( void ) const;
	void			SetInstanceSelectionIndex( int Value );

	float			GetTransformTranslationX( void ) const;
	void			SetTransformTranslationX( float Value );
	float			GetTransformTranslationY( void ) const;
	void			SetTransformTranslationY( float Value );
	float			GetTransformRotation( void ) const;
	void			SetTransformRotation( float Value );
	float			GetTransformScale( void ) const;
	void			SetTransformScale( float Value );

	// Configuration ////////////////////////////////////////////////////////////////

	// Attributes //

	float			GetMagnitudeThreshold( void ) const;
	void			SetMagnitudeThreshold( float Value );
	int				GetFilterHalfWidth( void ) const;
	void			SetFilterHalfWidth( int Value );

	hsPolarityMode	GetPolarityMode( void ) const;
	void			SetPolarityMode( hsPolarityMode Value );

	hsConstraint	GetConstraints( void ) const;
	void			SetConstraints( hsConstraint Index );
	float			GetPositionConstraint( hsPositionConstraintIndex Index ) const;
	void			SetPositionConstraint( hsPositionConstraintIndex Index, float Value );
	int				GetMagnitudeConstraint( hsMagnitudeConstraintIndex Index ) const;
	void			SetMagnitudeConstraint( hsMagnitudeConstraintIndex Index, int Value );

	float			GetScoreThreshold( void ) const;
	void			SetScoreThreshold( float Value );
	bool			GetSortResultsEnabled ( void ) const;
	void			SetSortResultsEnabled( bool Value );

	// Operations //

	const HSImage &	GetProjectionImage( void ) const;

	float			GetProjectionAverage( int Index = -1 ) const;
	float			GetProjectionMagnitude( int Index = -1 ) const;

	// Results ////////////////////////////////////////////////////////////////

	// Attributes //

	float			GetElapsedTime( void ) const;

	hsCoordinateSystem GetCoordinateSystem( void ) const;
	void			SetCoordinateSystem( hsCoordinateSystem Value );

	// Operations //

	int				GetEdgeCount( void ) const;
	float			GetEdgeMagnitude( int EdgeIndex ) const;
	float			GetEdgeMagnitudeScore( int EdgeIndex ) const;
	float			GetEdgePositionScore( int EdgeIndex ) const;
	float			GetEdgePositionX( int EdgeIndex ) const;
	float			GetEdgePositionY( int EdgeIndex ) const;
	float			GetEdgeRotation( int EdgeIndex ) const;
	float			GetEdgeScore( int EdgeIndex ) const;

	// Misc ///////////////////////////////////////////////////////////////////

	// Operations //

    float			Execute( void );

	void			SetDebugParameter( int Index, const void * Value, unsigned short Flag = NULL );
	void			GetDebugParameter( int Index, void * Value, unsigned short * Flag = NULL );

	void			Load( const char * FileName );
	void			Load( const char * FileName, int StartLine );
	void			Save( const char * FileName );
	void			Save( const char * FileName, bool Append, const char * Prefix );
	void			ResetState( void );

protected :

	void			_Load( const char * Prefix, void * = NULL );
	void			_Save( const char * Prefix, void * = NULL );

private:

	void * _pimpl;
};


// ****************************************************************************
// * Functions prototypes
// ****************************************************************************

// ****************************************************************************
// * Inline functions definitions
// ****************************************************************************

#endif // __HSEDGELOCATOR_H__

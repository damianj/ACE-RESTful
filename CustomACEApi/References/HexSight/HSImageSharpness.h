// ****************************************************************************
//
// HSImageSharpness																 
//
// ****************************************************************************
//
// File.........: HSImageSharpness.h
//
// Description..: This file contains the definition of the HSImageSharpness class.
//
// Platforms....: WIN32
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

#ifndef __HSIMAGESHARPNESS_H__
#define __HSIMAGESHARPNESS_H__

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
// HSIMAGESHARPNESS_COMPILATION_DLL <Reserved>

#ifdef WIN32
	#ifdef HSIMAGESHARPNESS_COMPILATION_DLL
		#define HSIMAGESHARPNESS_EXPORT __declspec(dllexport)
	#else
		#ifdef HSSTATICLIBRARY
			#define HSIMAGESHARPNESS_EXPORT
		#else
			#define HSIMAGESHARPNESS_EXPORT __declspec(dllimport)
		#endif
	#endif
#else
	#define HSIMAGESHARPNESS_EXPORT
#endif

// ****************************************************************************
// * Class definition
// ****************************************************************************

class HSIMAGESHARPNESS_EXPORT HSImageSharpness
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

	enum hsSharpnessHistoryScale
	{
		hsScaleAutomatic = -1,
		hsScale0100 = 0,
		hsScale0250 = 1,
		hsScale0500 = 2,
		hsScale1000 = 3
	};

	// CONSTANTS

public:

	// UTILITY

					HSImageSharpness( void );
					HSImageSharpness( const HSImageSharpness & Object );
    virtual		   ~HSImageSharpness( void );

					HSImageSharpness & operator=( const HSImageSharpness & Object );

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
	void			SetInputGreyScaleImage( const char *Value );
	const char *	GetInputGreyScaleView( void ) const;
	void			SetInputGreyScaleView( const char *Value );
	const char *	GetInputImage( void ) const;
	void			SetInputImage( const char *Value );
	const char *	GetInputView( void ) const;
	void			SetInputView( const char *Value );

	const char *	GetInputModelScene( void ) const;
	void			SetInputModelScene( const char *Value );
	const char *	GetInputModelView( void ) const;
	void			SetInputModelView( const char *Value );

	const char *	GetInputInstanceScene( void ) const;
	void			SetInputInstanceScene( const char *Value );
	const char *	GetInputInstanceView( void ) const;
	void			SetInputInstanceView( const char *Value );

	bool			GetModelTransformEnabled( void ) const;
	void			SetModelTransformEnabled( bool Value );
	bool			GetInstanceSelectionEnabled( void ) const;
	void			SetInstanceSelectionEnabled( bool Value );

	hsUnitsLength	GetUnitsLength( void ) const;
	void			SetUnitsLength( hsUnitsLength Value );
	hsUnitsOrientation	GetUnitsOrientation( void ) const;
	void			SetUnitsOrientation( hsUnitsOrientation Value );

	// Location ////////////////////////////////////////////////////////////////

	// Attributes //

	bool			GetCalibratedUnitsEnabled( void ) const;
	void			SetCalibratedUnitsEnabled( bool Value );
	bool			GetBilinearInterpolationEnabled( void ) const;
	void			SetBilinearInterpolationEnabled( bool Value );
	bool			GetSamplingStepCustomEnabled( void ) const;
	void			SetSamplingStepCustomEnabled( bool Value );

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

	float			GetSamplingStep( void ) const;
	float			GetSamplingStepDefault( void ) const;
	float			GetSamplingStepCustom( void ) const;
	void			SetSamplingStepCustom( float Value );

	// Transform ////////////////////////////////////////////////////////////////

	// Attributes //

	float			GetTransformTranslationX( void ) const;
	void			SetTransformTranslationX( float Value );
	float			GetTransformTranslationY( void ) const;
	void			SetTransformTranslationY( float Value );
	float			GetTransformRotation( void ) const;
	void			SetTransformRotation( float Value );
	float			GetTransformScale( void ) const;
	void			SetTransformScale( float Value );

	int				GetInstanceSelectionIndex( void ) const;
	void			SetInstanceSelectionIndex( int Value );

	// Configuration ////////////////////////////////////////////////////////////////

	// Attributes //

	long			GetCandidatePointsCount( void ) const;
	void			SetCandidatePointsCount( long Value );
	bool			GetAutomaticCandidateCountEnabled( void ) const;
	void			SetAutomaticCandidateCountEnabled( bool Value );
	float			GetStandardDeviationThreshold( void ) const;
	void			SetStandardDeviationThreshold( float Value );
	int				GetKernelSize( void ) const;
	void			SetKernelSize( int Value );

	enum hsSharpnessHistoryScale GetSharpnessHistoryScale( void ) const;
	void SetSharpnessHistoryScale( enum hsSharpnessHistoryScale Value );

	// Results ////////////////////////////////////////////////////////////////

	// Attributes //

	float			GetElapsedTime( void ) const;

	hsCoordinateSystem	GetCoordinateSystem( void ) const;
	void			SetCoordinateSystem( hsCoordinateSystem Value );

    float			GetSharpness( void ) const;
    float			GetSharpnessPeak( void ) const;
    long			GetMeasurementPointsCount( void ) const;

    long			GetSharpnessHistorySize( void ) const;
    float			GetSharpnessHistory( long Index ) const;

    void			ResetHistory( void );

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

#endif // __HSIMAGESHARPNESS_H__

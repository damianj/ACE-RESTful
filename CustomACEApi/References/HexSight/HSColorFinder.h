// ****************************************************************************
//
// HSColorFinder																 
//
// ****************************************************************************
//
// File.........: HSColorFinder.h
//
// Description..: This file contains the definition of the HSColorFinder class.
//
// Platforms....: WIN32
//
// ****************************************************************************
//
//                Copyright (C) 2007 LMI Technologies
//                All rights reserved
//
// ****************************************************************************
//
// $History:$
//
// ****************************************************************************

#ifndef __HSCOLORFINDER_H__
#define __HSCOLORFINDER_H__

// ****************************************************************************
// * Constants
// ****************************************************************************

// ****************************************************************************
// * Types
// ****************************************************************************

class HSColorFilter;

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
// HSCOLORFINDER_COMPILATION_DLL <Reserved>

#ifdef WIN32
	#ifdef HSCOLORFINDER_COMPILATION_DLL
		#define HSCOLORFINDER_EXPORT __declspec(dllexport)
	#else
		#ifdef HSSTATICLIBRARY
			#define HSCOLORFINDER_EXPORT
		#else
			#define HSCOLORFINDER_EXPORT __declspec(dllimport)
		#endif
	#endif
#else
	#define HSCOLORFINDER_EXPORT
#endif

// ****************************************************************************
// * Class definition
// ****************************************************************************

class HSCOLORFINDER_EXPORT HSColorFinder
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

	enum hsProcessingFormat
	{
		hsProcessingFormatNative = 0,
		hsProcessingFormatGreyScale = 1,
	};

	// CONSTANTS

public:

	// UTILITY

					HSColorFinder( void );
					HSColorFinder( const HSColorFinder & Object );
    virtual		   ~HSColorFinder( void );

					HSColorFinder & operator=( const HSColorFinder & Object );

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

	const char *	GetOutputFilterImage( void ) const;
	void			SetOutputFilterImage( const char *Value );
	const char *	GetOutputFilterView( void ) const;
	void			SetOutputFilterView( const char *Value );
	bool			GetOutputFilterImageEnabled( void ) const;
	void			SetOutputFilterImageEnabled( bool Value );
	bool			GetClearOutputFilterImageEnabled( void ) const;
	void			SetClearOutputFilterImageEnabled( bool Value );

	const char *	GetInputModelScene( void ) const;
	void			SetInputModelScene( const char * Name );
	const char *	GetInputModelView( void ) const;
	void			SetInputModelView( const char * Name );

	const char *	GetInputInstanceScene( void ) const;
	void			SetInputInstanceScene( const char * Name );
	const char *	GetInputInstanceView( void ) const;
	void			SetInputInstanceView( const char * Name );

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

    int				GetColorFilterCount( void ) const;
    int				GetColorFilterIndex( const char * FilterName ) const;

	const HSColorFilter * GetColorFilter( int FilterIndex ) const;
	HSColorFilter *	GetColorFilter( int FilterIndex );

	bool			GetColorFilterEnabled( int FilterIndex ) const;
	void			SetColorFilterEnabled( int FilterIndex, bool Value );

    int				GetImageSubsampling( void ) const;
    void			SetImageSubsampling( int Value );

	// Operations //

	HSColorFilter * AddColorFilter( void );
	void			RemoveColorFilter( int FilterIndex );

	HSColorFilter * ImportColorFilter( const char * FilterName );
	void			ExportColorFilter( const char * FilterName, int FilterIndex );

	// Results ////////////////////////////////////////////////////////////////

	// Attributes //

	float			GetElapsedTime( void ) const;

	hsCoordinateSystem	GetCoordinateSystem( void ) const;
	void			SetCoordinateSystem( hsCoordinateSystem Value );

	int				GetColorFilterBestMatchIndex( void ) const;
    const char *	GetColorFilterBestMatchName( void ) const;

	float			GetColorFilterMatchQuality( int FilterIndex ) const;
	long			GetColorFilterMatchPixelCount( int FilterIndex ) const;

    long			GetImageWidth( void ) const;
    long			GetImageHeight( void ) const;
    long			GetImagePixelCount( void ) const;

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

#endif // __HSCOLORFINDER_H__

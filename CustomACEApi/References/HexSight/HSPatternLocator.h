// ****************************************************************************
//
// HSPatternLocator																 
//
// ****************************************************************************
//
// File.........: HSPatternLocator.h
//
// Description..: This file contains the definition of the HSPatternLocator class.
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

#ifndef __HSPATTERNLOCATOR_H__
#define __HSPATTERNLOCATOR_H__

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
// HSPATTERNLOCATOR_COMPILATION_DLL <Reserved>

#ifdef WIN32
	#ifdef HSPATTERNLOCATOR_COMPILATION_DLL
		#define HSPATTERNLOCATOR_EXPORT __declspec(dllexport)
	#else
		#ifdef HSSTATICLIBRARY
			#define HSPATTERNLOCATOR_EXPORT
		#else
			#define HSPATTERNLOCATOR_EXPORT __declspec(dllimport)
		#endif
	#endif
#else
	#define HSPATTERNLOCATOR_EXPORT
#endif

// ****************************************************************************
// * Class definition
// ****************************************************************************

class HSPATTERNLOCATOR_EXPORT HSPatternLocator
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

	// CONSTANTS

	static const int hsMinimumSearchCoarseness;
	static const int hsMaximumSearchCoarseness;

	static const int hsMinimumPositionningCoarseness;
	static const int hsMaximumPositionningCoarseness;

public:

	// UTILITY

					HSPatternLocator( void );
					HSPatternLocator( const HSPatternLocator & Object );
    virtual		   ~HSPatternLocator( void );

					HSPatternLocator & operator=( const HSPatternLocator & Object );

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

    bool			GetOverrideModelImageEnabled( void ) const; 
    void			SetOverrideModelImageEnabled( bool Value ); 

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

	// Pattern ////////////////////////////////////////////////////////////////

	// Attributes //

	float			GetPatternPositionX( void ) const;
    void			SetPatternPositionX( float Value );
    float			GetPatternPositionY( void ) const;
    void			SetPatternPositionY( float Value );
    float			GetPatternWidth( void ) const;
    void			SetPatternWidth( float Value );
    float			GetPatternHeight( void ) const;
    void			SetPatternHeight( float Value );
    float			GetPatternRotation( void ) const;
    void			SetPatternRotation( float Value );

    const char *	GetPatternDatabaseFileName( void ) const;

	// Operations //

    void			CreatePatternFromInput( void );
    bool			ImportPatternFromDatabase( const char * FileName, const char * ViewName, const char * ImageName );
    void			NewPatternDatabase( void );
    bool			LoadPatternDatabase( const char * FileName );
    bool			SavePatternDatabase( const char * FileName );

	bool			GetPatternDatabaseSaved( void );
	void			SetPatternDatabaseSaved( void );

	// Configuration ////////////////////////////////////////////////////////////////

	// Attributes //

    bool			GetMaximumInstanceCountEnabled( void ) const;
    void			SetMaximumInstanceCountEnabled( bool Value );
    int				GetMaximumInstanceCount( void ) const;
    void			SetMaximumInstanceCount( int Value );
    float			GetMatchThreshold( void ) const;
    void			SetMatchThreshold( float Value );
    bool			GetAutoCoarsenessSelectionEnabled( void ) const;
    void			SetAutoCoarsenessSelectionEnabled( bool Value );

    bool			GetNominalRotationEnabled( void ) const;
    void			SetNominalRotationEnabled( bool Value );
    float			GetNominalRotation( void ) const;
    void			SetNominalRotation( float Value );
    float			GetLowerRotation( void ) const;
    void			SetLowerRotation( float Value );
    float			GetHigherRotation( void ) const;
    void			SetHigherRotation( float Value );
    float			GetRotationStep( void ) const;
    void			SetRotationStep( float Value );
    bool			GetAutomaticRotationStepEnabled( void ) const;
    void			SetAutomaticRotationStepEnabled( bool Value );

    int				GetSearchCoarseness( void ) const;
    void			SetSearchCoarseness( int Value );
    int				GetPositioningCoarseness( void ) const;
    void			SetPositioningCoarseness( int Value );

	// Operations //

	static int		CoarsenessToIndex( int Value );
	static int		IndexToCoarseness( int Value );

	// Results ////////////////////////////////////////////////////////////////

	// Attributes //

	float			GetElapsedTime( void ) const;

	hsCoordinateSystem	GetCoordinateSystem( void ) const;
	void			SetCoordinateSystem( hsCoordinateSystem Value );

    int				GetMatchCount( void ) const;
	float			GetMatchStrength( int Index ) const;
    float			GetMatchPositionX( int Index, bool Offset = false ) const;
    float			GetMatchPositionY( int Index, bool Offset = false ) const;
    float			GetMatchRotation( int Index ) const;

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

#endif // __HSPATTERNLOCATOR_H__

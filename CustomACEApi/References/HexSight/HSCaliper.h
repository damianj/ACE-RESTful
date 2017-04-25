// ****************************************************************************
//
// HSCaliper																 
//
// ****************************************************************************
//
// File.........: HSCaliper.h
//
// Description..: This file contains the definition of the HSCaliper class.
//
// Platforms....: All
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

#ifndef __HSCALIPER_H__
#define __HSCALIPER_H__

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
// HSCALIPER_COMPILATION_DLL <Reserved>

#ifdef WIN32
	#ifdef HSCALIPER_COMPILATION_DLL
		#define HSCALIPER_EXPORT __declspec(dllexport)
	#else
		#ifdef HSSTATICLIBRARY
			#define HSCALIPER_EXPORT
		#else
			#define HSCALIPER_EXPORT __declspec(dllimport)
		#endif
	#endif
#else
	#define HSCALIPER_EXPORT
#endif


// ****************************************************************************
// * Class definition
// ****************************************************************************

class HSCALIPER_EXPORT HSCaliper
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

					HSCaliper( void );
					HSCaliper( const HSCaliper & Object );
    virtual		   ~HSCaliper( void );

					HSCaliper & operator=( const HSCaliper & Object );

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

	float			GetEdgeMagnitudeThreshold( void ) const;
	void			SetEdgeMagnitudeThreshold( float Value );
	int				GetEdgeFilterHalfWidth( void ) const;
	void			SetEdgeFilterHalfWidth( int Value );

	hsPolarityMode	GetEdge1PolarityMode( int PairIndex ) const;
	void			SetEdge1PolarityMode( int PairIndex, hsPolarityMode Value );
	hsPolarityMode	GetEdge2PolarityMode( int PairIndex ) const;
	void			SetEdge2PolarityMode( int PairIndex, hsPolarityMode Value );

	hsConstraint	GetEdge1Constraints( int PairIndex ) const;
	void			SetEdge1Constraints( int PairIndex, hsConstraint Value );
	hsConstraint	GetEdge2Constraints( int PairIndex ) const;
	void			SetEdge2Constraints( int PairIndex, hsConstraint Value );
	float			GetEdge1PositionConstraint( int PairIndex, hsPositionConstraintIndex PositionConstraintIndex ) const;
	void			SetEdge1PositionConstraint( int PairIndex, hsPositionConstraintIndex PositionConstraintIndex, float Value );
	float			GetEdge2PositionConstraint( int PairIndex, hsPositionConstraintIndex PositionConstraintIndex ) const;
	void			SetEdge2PositionConstraint( int PairIndex, hsPositionConstraintIndex PositionConstraintIndex, float Value );
	int				GetEdge1MagnitudeConstraint( int PairIndex, hsMagnitudeConstraintIndex MagnitudeConstraintIndex ) const;
	void			SetEdge1MagnitudeConstraint( int PairIndex, hsMagnitudeConstraintIndex MagnitudeConstraintIndex, int Value );
	int				GetEdge2MagnitudeConstraint( int PairIndex, hsMagnitudeConstraintIndex MagnitudeConstraintIndex ) const;
	void			SetEdge2MagnitudeConstraint( int PairIndex, hsMagnitudeConstraintIndex MagnitudeConstraintIndex, int Value );

	float			GetEdge1ScoreThreshold( int PairIndex ) const;
	void			SetEdge1ScoreThreshold( int PairIndex, float Value );
	float			GetEdge2ScoreThreshold( int PairIndex ) const;
	void			SetEdge2ScoreThreshold( int PairIndex, float Value );

	// Operations //

	const HSImage &	GetProjectionImage( void ) const;

	float			GetProjectionAverage( int Index = -1 ) const;
	float			GetProjectionMagnitude( int Index = -1 ) const;

	int				GetEdgeCount( void ) const;
	float			GetEdgePositionX( int Index ) const;
	float			GetEdgePositionY( int Index ) const;
	float			GetEdgeRadius( int Index ) const;
	float			GetEdgeRotation( int Index ) const;

	// Results ////////////////////////////////////////////////////////////////

	// Attributes //

	float			GetElapsedTime( void ) const;

	hsCoordinateSystem GetCoordinateSystem( void ) const;
	void			SetCoordinateSystem( hsCoordinateSystem Value );

	// Operations //

	float			GetEdge1Magnitude( int PairIndex ) const;
	float			GetEdge2Magnitude( int PairIndex ) const;
	float			GetEdge1MagnitudeScore( int PairIndex ) const;
	float			GetEdge2MagnitudeScore( int PairIndex ) const;
	float			GetEdge1PositionScore( int PairIndex ) const;
	float			GetEdge2PositionScore( int PairIndex ) const;
	float			GetEdge1PositionX( int PairIndex ) const;
	float			GetEdge2PositionX( int PairIndex ) const;
	float			GetEdge1PositionY( int PairIndex ) const;
	float			GetEdge2PositionY( int PairIndex ) const;
	float			GetEdge1Rotation( int PairIndex ) const;
	float			GetEdge2Rotation( int PairIndex ) const;
	float			GetEdge1Score( int PairIndex ) const;
	float			GetEdge2Score( int PairIndex ) const;

	// Misc ///////////////////////////////////////////////////////////////////

	// Operations //

	int				GetPairCount( void ) const;
	int				GetPairIndex( const char *pPairName ) const;
	const char *	GetPairName( int PairIndex ) const;
	void			SetPairName( int PairIndex, const char *pName );
	float			GetPairPositionX( int PairIndex ) const;
	float			GetPairPositionY( int PairIndex ) const;
	float			GetPairRotation( int PairIndex ) const;
	float			GetPairScore( int PairIndex ) const;
	float			GetPairSize( int PairIndex ) const;
	bool			GetPairFound( int PairIndex ) const;

	int				AddPair( const char *pName );
	void			RemovePair( int PairIndex );

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

#endif // __HSCALIPER_H__

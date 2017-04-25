// ****************************************************************************
//
// HSLineFinder																 
//
// ****************************************************************************
//
// File.........: HSLineFinder.hpp
//
// Description..: This file contains the definition of the HSLineFinder class.
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

#ifndef __HSLINEFINDER_H__
#define __HSLINEFINDER_H__

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
// HSCLL_COMPILATION_DLL <Reserved>

#ifdef WIN32
	#ifdef HSLINEFINDER_COMPILATION_DLL
		#define HSLINEFINDER_EXPORT __declspec(dllexport)
	#else
		#ifdef HSSTATICLIBRARY
			#define HSLINEFINDER_EXPORT
		#else
			#define HSLINEFINDER_EXPORT __declspec(dllimport)
		#endif
	#endif
#else
	#define HSLINEFINDER_EXPORT
#endif

// ****************************************************************************
// * Class definition
// ****************************************************************************

class HSLine;
class HSPoint;

class HSLINEFINDER_EXPORT HSLineFinder
{
public:

	static const int hsMinimumContrastThreshold;
	static const int hsMaximumContrastThreshold;
	static const int hsMinimumSubsamplingLevel;
	static const int hsMaximumSubsamplingLevel;
	static const int hsMinimumPositioningLevel;
	static const int hsMaximumPositioningLevel;
	static const float hsMinimumLinePercentage;
	static const float hsMaximumLinePercentage;
	static const float hsMinimumAngleDeviation;				// in radian
	static const float hsMaximumAngleDeviation;				// in radian

	static const char* hsFilteredSceneName;
	static const char* hsEdgeSceneName;

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
		hsDontCare		= 3
	};

	enum hsSearchMode
	{
		hsBestLine							= 0,
		hsLineClosestToGuideline			= 1,
		hsLineWithMaximumNegativeXOffset	= 2,
		hsLineWithMaximumPositiveXOffset	= 3
	};

	enum hsContrastThresholdMode
	{
		hsContrastThresholdAdaptiveLowSensitivity = 0,
		hsContrastThresholdAdaptiveNormalSensitivity = 1,
		hsContrastThresholdAdaptiveHighSensitivity = 2,
		hsContrastThresholdFixedValue = 3
	};

	enum hsOutputLinePoint
	{
		hsOutputLineStartPoint = 0,
		hsOutputLineEndPoint = 1,
		hsOutputLineVectorPoint = 2
	};
	
	enum hsProcessingFormat
	{
		hsProcessingFormatNative = 0,
		hsProcessingFormatGreyScale = 1,
	};

public:

	// UTILITY

					HSLineFinder( void );
					HSLineFinder( const HSLineFinder & Object );
    virtual		   ~HSLineFinder( void );

					HSLineFinder & operator=( const HSLineFinder & Object );

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

	const char *	GetOutputEntity( void ) const;
	void			SetOutputEntity( const char * Name );
	const char *	GetOutputEntityView( void ) const;
	void			SetOutputEntityView( const char * Name );
	bool			GetOutputEntityEnabled( void ) const;
	void			SetOutputEntityEnabled( bool Enabled );

    hsUnitsLength	GetUnitsLength( void ) const;					
    void			SetUnitsLength( hsUnitsLength Units );			

    hsUnitsOrientation GetUnitsOrientation( void ) const;			
    void			SetUnitsOrientation( hsUnitsOrientation Units );	

	bool			GetProcessingFormatEnabled( hsProcessingFormat pFormat ) const;
	hsProcessingFormat GetProcessingFormat( void ) const;
	void			SetProcessingFormat( hsProcessingFormat Value );


	// Operations //
	
	bool			GenerateObjects( bool Entity, bool Scenes, const char * ViewName = NULL, unsigned int Handle = 0xffffffff, unsigned long Password = 0 );

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

	float			GetToolGuidelineOffset( void ) const;
	void			SetToolGuidelineOffset( float Value );

	bool			GetCalibratedUnitsEnabled( void ) const;
	void			SetCalibratedUnitsEnabled( bool Value );

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

	// Search Constraints //

	hsPolarityMode	GetPolarityMode( void ) const;				
	void			SetPolarityMode( hsPolarityMode Value );			

	hsSearchMode	GetSearchMode( void ) const;				
	void			SetSearchMode( hsSearchMode Value );				

	float			GetMaximumAngleDeviation( void ) const;
	void			SetMaximumAngleDeviation( float Value );

	// Edge Detection

	int				GetSubsamplingLevel( void ) const;
	void			SetSubsamplingLevel( int Value );

	hsContrastThresholdMode GetContrastThresholdMode( void ) const;		
	void			SetContrastThresholdMode( hsContrastThresholdMode Value );

    int			GetContrastThreshold( void ) const;
	void			SetContrastThreshold( int Value );

	// Recognition

	bool			GetUseDefaultConformityTolerance( void ) const;
	void			SetUseDefaultConformityTolerance( bool Value );

	float			GetConformityTolerance( void ) const;
	void			SetConformityTolerance( float Value );

	float			GetDefaultConformityTolerance( void ) const;

	float			GetMinimumConformityTolerance( void ) const;

	float			GetMaximumConformityTolerance( void ) const;

	float			GetMinimumLinePercentage( void ) const;
	void			SetMinimumLinePercentage( float Value );


	// Positioning

	int				GetPositioningLevel( void ) const;
	void			SetPositioningLevel( int Value );


	// Results ////////////////////////////////////////////////////////////////

	// Attributes //

	bool			GetFound( void ) const;

    float			GetElapsedTime( void ) const;

    hsCoordinateSystem GetCoordinateSystem( void ) const;				
    void			SetCoordinateSystem( hsCoordinateSystem Value );		

	int				GetMessageCount( void ) const;
	int				GetMessageNumber( int Index ) const;
	const char *	GetMessageDescription( int Index ) const;

	// Operations //

	float			GetAverageContrast( void ) const;
	float			GetMatchQuality( void ) const;
	float			GetFitQuality( void ) const;

	void *			GetLineKValues( void ) const;

	float			GetOutputLineAngle( void ) const;
	const HSPoint &	GetOutputLinePoint( hsOutputLinePoint Value ) const;
	HSPoint &		GetOutputLinePoint( hsOutputLinePoint Value );
	const HSLine &	GetOutputLine( void ) const;
	HSLine &		GetOutputLine( void );

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

#endif // __HSLINEFINDER_H__

// ****************************************************************************
//
// HSDataMatrix																 
//
// ****************************************************************************
//
// File.........: HSDataMatrix.h
//
// Description..: This file contains the definition of the HSDataMatrix class.
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

#ifndef __HSDATAMATRIX_H__
#define __HSDATAMATRIX_H__

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
// HSSYMBOLOGY_COMPILATION_DLL <Reserved>

#ifdef WIN32
	#ifdef HSSYMBOLOGY_COMPILATION_DLL
		#define HSSYMBOLOGY_EXPORT __declspec(dllexport)
	#else
		#ifdef HSSTATICLIBRARY
			#define HSSYMBOLOGY_EXPORT
		#else
			#define HSSYMBOLOGY_EXPORT __declspec(dllimport)
		#endif
	#endif
#else
	#define HSSYMBOLOGY_EXPORT
#endif

// ****************************************************************************
// * Class definition
// ****************************************************************************

class HSSYMBOLOGY_EXPORT HSDataMatrix
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
		hsCoordinateSystemTool = 3,
		hsCoordinateSystemIntern = 4 // Reserved for internal use
	};

	enum hsMatrixPolarity
	{
		hsMatrixPolarityLightOnDark = 0,
		hsMatrixPolarityDarkOnLight = 1
	};

	enum hsMatrixECCLevel
	{
		hsMatrixECC200 = 0,
		hsMatrixECC140 = 1,
		hsMatrixECC100 = 2,
		hsMatrixECC080 = 3,
		hsMatrixECC050 = 4,
		hsMatrixECC000 = 5
	};

	enum hsMatrixOrientation
	{
		hsMatrixOrientation0 = 0,
		hsMatrixOrientation90 = 1,
		hsMatrixOrientation180 = 2,
		hsMatrixOrientation270 = 3,
		hsMatrixOrientation45 = 4,
		hsMatrixOrientation135 = 5,
		hsMatrixOrientation225 = 6,
		hsMatrixOrientation315 = 7
	};

	enum hsMatrixImageStyle
	{
		hsMatrixStyleNormal = 0,
		hsMatrixStyleMirror = 1
	};

	enum hsMatrixProcessing
	{
		hsMatrixProcessingNone = 0,
		hsMatrixProcessingInvert = 1,
		hsMatrixProcessingErode = 2,
		hsMatrixProcessingDilate = 3,
		hsMatrixProcessingOpen = 4,
		hsMatrixProcessingClose = 5,
		hsMatrixProcessingGaussian = 6,
		hsMatrixProcessingSharpen = 7,
		hsMatrixProcessingSharpenLow = 8,
		hsMatrixProcessingMedian = 9,
		hsMatrixProcessingHistogramStretching = 10
	};

	enum hsMatrixFineTuneMethod
	{
		hsMatrixPositionEnhance = 0,
		hsMatrixIntensityEnhance = 1,
		hsMatrixNoQuitZoneClutter = 2,
		hsMatrixNoTopTimingBorder = 3,
		hsMatrixNoRightTimingBorder = 4,
		hsMatrixAllowSteepAngle = 5,
		hsMatrixAllowSevereDamage = 6
	};

	enum hsMatrixSearchSpeed
	{
		hsMatrixSpeedNormal = 0,
		hsMatrixSpeedOverdrive = 1,
		hsMatrixSpeedTurbo = 2
	};

	enum hsMatrixSearchDirection
	{
		hsMatrixDirectionHorizontal = 0,
		hsMatrixDirectionVertical = 1,
		hsMatrixDirectionHorizontalVertical = 2,
		hsMatrixDirectionVerticalHorizontal = 3
	};

	enum hsMatrixWarpMethod
	{
		hsMatrixWarpSlow = 0,
		hsMatrixWarpFast = 1
	};

	enum hsMatrixVerifierMode
	{
		hsMatrixVerifierNone = 0,
		hsMatrixVerifierCustom = 1,
		hsMatrixVerifierAIM = 2
	};

	// CONSTANTS

	static const int hsDefaultMatrixToDecode;
	static const int hsMinMatrixToDecode;
	static const int hsMaxMatrixToDecode;
	static const int hsDefaultHeightWidth;
	static const int hsMinHeightWidth;
	static const int hsMaxHeightWidth;
	static const int hsDefaultRowsColumns;
	static const int hsMinRowsColumns;
	static const int hsMaxRowsColumns;
	static const int hsDefaultFormatID;
	static const int hsMinFormatID;
	static const int hsMaxFormatID;
	static const int hsDefaultProcessingSize;
	static const int hsMinProcessingSize;
	static const int hsMaxProcessingSize;
	static const int hsDefaultAverageElementSize;
	static const int hsMinAverageElementSize;
	static const int hsMaxAverageElementSize;
	static const int hsDefaultMinimumEdgeStrength;
	static const int hsMinMinimumEdgeStrength;
	static const int hsMaxMinimumEdgeStrength;
	static const int hsDefaultSamplesPerCell;
	static const int hsMinSamplesPerCell;
	static const int hsMaxSamplesPerCell;
	static const int hsDefaultBorderIntegrity;
	static const int hsMinBorderIntegrity;
	static const int hsMaxBorderIntegrity;
	static const int hsDefaultAngleVariation;
	static const int hsMinAngleVariation;
	static const int hsMaxAngleVariation;
	static const int hsDefaultSizeVariation;
	static const int hsMinSizeVariation;
	static const int hsMaxSizeVariation;
	static const float hsDefaultRatio;
	static const float hsMinRatio;
	static const float hsMaxRatio;
	static const int hsDefaultTimeout;
	static const int hsMinTimeout;
	static const int hsMaxTimeout;
	static const int hsDefaultVerifierCellSize;
	static const int hsMinVerifierCellSize;
	static const int hsMaxVerifierCellSize;
	static const float hsDefaultVerifierOffset;
	static const float hsMinVerifierOffset;
	static const float hsMaxVerifierOffset;
	static const int hsDefaultVerifierCorrelation;
	static const int hsMinVerifierCorrelation;
	static const int hsMaxVerifierCorrelation;
	static const int hsDefaultVerifierBorderMatch;
	static const int hsMinVerifierBorderMatch;
	static const int hsMaxVerifierBorderMatch;
	static const int hsDefaultVerifierContrast;
	static const int hsMinVerifierContrast;
	static const int hsMaxVerifierContrast;
	static const float hsDefaultVerifierAxialUniformity;
	static const float hsMinVerifierAxialUniformity;
	static const float hsMaxVerifierAxialUniformity;
	static const float hsDefaultVerifierPrintGrowth;
	static const float hsMinVerifierPrintGrowth;
	static const float hsMaxVerifierPrintGrowth;
	static const int hsDefaultVerifierErrorCorrection;
	static const int hsMinVerifierErrorCorrection;
	static const int hsMaxVerifierErrorCorrection;
	static const int hsTuneMethodCount;
	static const int hsMaximumSymbols;
	static const hsMatrixPolarity hsDefaultMatrixPolarity;
	static const hsMatrixECCLevel hsDefaultMatrixECCLevel;
	static const hsMatrixOrientation hsDefaultMatrixOrientation;
	static const hsMatrixImageStyle hsDefaultMatrixImageStyle;
	static const hsMatrixProcessing hsDefaultMatrixProcessing;
	static const hsMatrixSearchSpeed hsDefaultMatrixSearchSpeed;
	static const hsMatrixSearchDirection hsDefaultMatrixSearchDirection;
	static const hsMatrixWarpMethod hsDefaultMatrixWarpMethod;
	static const hsMatrixVerifierMode hsDefaultMatrixVerifierMode;

public:

	// UTILITY

					HSDataMatrix( void );
					HSDataMatrix( const HSDataMatrix & Object );
    virtual		   ~HSDataMatrix( void );

					HSDataMatrix & operator=( const HSDataMatrix & Object );

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

	bool			GetMatrixHeightEnabled( void ) const;
	void			SetMatrixHeightEnabled( bool Value );
	bool			GetMatrixWidthEnabled( void ) const;
	void			SetMatrixWidthEnabled( bool Value );
	bool			GetMatrixRowsEnabled( void ) const;
	void			SetMatrixRowsEnabled( bool Value );
	bool			GetMatrixColumnsEnabled( void ) const;
	void			SetMatrixColumnsEnabled( bool Value );
	bool			GetMatrixPolarityEnabled( void ) const;
	void			SetMatrixPolarityEnabled( bool Value );
	bool			GetMatrixFormatIDEnabled( void ) const;
	void			SetMatrixFormatIDEnabled( bool Value );
	bool			GetMatrixECCLevelEnabled( void ) const;
	void			SetMatrixECCLevelEnabled( bool Value );
	bool			GetMatrixOrientationEnabled( void ) const;
	void			SetMatrixOrientationEnabled( bool Value );
	bool			GetMatrixImageStyleEnabled( void ) const;
	void			SetMatrixImageStyleEnabled( bool Value );

	int				GetMatrixToDecode( void ) const;
	void			SetMatrixToDecode( int Value );
	int				GetMatrixHeight( void ) const;
	void			SetMatrixHeight( int Value );
	int				GetMatrixWidth( void ) const;
	void			SetMatrixWidth( int Value );
	int				GetMatrixRows( void ) const;
	void			SetMatrixRows( int Value );
	int				GetMatrixColumns( void ) const;
	void			SetMatrixColumns( int Value );

	hsMatrixPolarity GetMatrixPolarity( void ) const;
	void			SetMatrixPolarity( hsMatrixPolarity Value );
	int				GetMatrixFormatID( void ) const;
	void			SetMatrixFormatID( int Value );
	hsMatrixECCLevel GetMatrixECCLevel( void ) const;
	void			SetMatrixECCLevel( hsMatrixECCLevel Value );
	hsMatrixOrientation	GetMatrixOrientation( void ) const;
	void			SetMatrixOrientation( hsMatrixOrientation Value );
	hsMatrixImageStyle GetMatrixImageStyle( void ) const;
	void			SetMatrixImageStyle( hsMatrixImageStyle Value );
	hsMatrixProcessing	GetProcessingAlgorithm( void ) const;
	void			SetProcessingAlgorithm( hsMatrixProcessing Value );
	int				GetProcessingSize( void ) const;
	void			SetProcessingSize( int Value );

	// Advanced ///////////////////////////////////////////////////////////////////

	// Attributes //

	bool			GetWidthHeightRatioEnabled( void ) const;
	void			SetWidthHeightRatioEnabled( bool Value );
	bool			GetLocalThresholdEnabled( void ) const;
	void			SetLocalThresholdEnabled( bool Value );
	bool			GetGlobalThresholdEnabled( void ) const;
	void			SetGlobalThresholdEnabled( bool Value );
	bool			GetAdaptiveThresholdEnabled( void ) const;
	void			SetAdaptiveThresholdEnabled( bool Value );

	int				GetAverageElementSize( void ) const;
	void			SetAverageElementSize( int Value );
	int				GetMinimumEdgeStrength( void ) const;
	void			SetMinimumEdgeStrength( int Value );
	int				GetSamplesPerCell( void ) const;
	void			SetSamplesPerCell( int Value );
	int				GetBorderIntegrity( void ) const;
	void			SetBorderIntegrity( int Value );
	int				GetAngleVariation( void ) const;
	void			SetAngleVariation( int Value );
	int				GetSizeVariation( void ) const;
	void			SetSizeVariation( int Value );
	float			GetWidthHeightRatio( void ) const;
	void			SetWidthHeightRatio( float Value );
	long			GetTimeout( void ) const;
	void			SetTimeout( long Value );
	hsMatrixSearchSpeed	GetSearchSpeed( void ) const;
	void			SetSearchSpeed( hsMatrixSearchSpeed Value );
	hsMatrixSearchDirection	GetMatrixSearchDirection( void ) const;
	void			SetMatrixSearchDirection( hsMatrixSearchDirection Value );
	hsMatrixWarpMethod	GetWarpMethod( void ) const;
	void			SetWarpMethod( hsMatrixWarpMethod Value );

	bool			GetVerifierValidateEnabled( void ) const;
	void			SetVerifierValidateEnabled( bool Value );
	bool			GetVerifierCellSizeEnabled( void ) const;
	void			SetVerifierCellSizeEnabled( bool Value );
	bool			GetVerifierCenterOffsetEnabled( void ) const;
	void			SetVerifierCenterOffsetEnabled( bool Value );
	bool			GetVerifierSizeOffsetEnabled( void ) const;
	void			SetVerifierSizeOffsetEnabled( bool Value );
	bool			GetVerifierCorrelationEnabled( void ) const;
	void			SetVerifierCorrelationEnabled( bool Value );
	bool			GetVerifierBorderMatchEnabled( void ) const;
	void			SetVerifierBorderMatchEnabled( bool Value );
	bool			GetVerifierContrastEnabled( void ) const;
	void			SetVerifierContrastEnabled( bool Value );
	bool			GetVerifierAxialUniformityEnabled( void ) const;
	void			SetVerifierAxialUniformityEnabled( bool Value );
	bool			GetVerifierPrintGrowthEnabled( void ) const;
	void			SetVerifierPrintGrowthEnabled( bool Value );
	bool			GetVerifierErrorCorrectionEnabled( void ) const;
	void			SetVerifierErrorCorrectionEnabled( bool Value );

	hsMatrixVerifierMode GetVerifierMode( void ) const;
	void			SetVerifierMode( hsMatrixVerifierMode Value );
	int				GetVerifierCellSize( void ) const;
	void			SetVerifierCellSize( int Value );
	float			GetVerifierCenterOffset( void ) const;
	void			SetVerifierCenterOffset( float Value );
	float			GetVerifierSizeOffset( void ) const;
	void			SetVerifierSizeOffset( float Value );
	int				GetVerifierCorrelation( void ) const;
	void			SetVerifierCorrelation( int Value );
	int				GetVerifierBorderMatch( void ) const;
	void			SetVerifierBorderMatch( int Value );
	int				GetVerifierContrast( void ) const;
	void			SetVerifierContrast( int Value );
	float			GetVerifierAxialUniformity( void ) const;
	void			SetVerifierAxialUniformity( float Value );
	float			GetVerifierPrintGrowth( void ) const;
	void			SetVerifierPrintGrowth( float Value );
	int				GetVerifierErrorCorrection( void ) const;
	void			SetVerifierErrorCorrection( int Value );

	bool			GetFineTuneMethodEnabled( hsMatrixFineTuneMethod Method );
	void			SetFineTuneMethodEnabled( hsMatrixFineTuneMethod Method, bool Value );

	// Results ////////////////////////////////////////////////////////////////

	// Attributes //

	float			GetElapsedTime( void ) const;
	float			GetLearnElapsedTime( void ) const;

	hsCoordinateSystem	GetCoordinateSystem( void ) const;
	void			SetCoordinateSystem( hsCoordinateSystem Value );

	int				GetMatrixFoundCount( void ) const;

	const char *	GetMatrixString( int Index ) const;
	long			GetMatrixStatusCode( int Index ) const;
	float			GetMatrixAngle( int Index ) const;
	float			GetMatrixCornerX( int Index, int Corner ) const;
	float			GetMatrixCornerY( int Index, int Corner ) const;
	int				GetMatrixContrast( int Index ) const;
	int				GetMatrixTotalErrorBits( int Index ) const;
	float			GetMatrixDamagePercentage( int Index ) const;
	float			GetMatrixBorderMatchPercentage( int Index ) const;
	int				GetMatrixThreshold( int Index ) const;
	float			GetMatrixDecodeTime( int Index ) const;
	const char *	GetMatrixStatusCodeString( int Index ) const;

	// Misc ///////////////////////////////////////////////////////////////////

	// Operations //

    float			Execute( void );
	bool			Learn( void );
	bool			Learn( float pX0, float pY0, float pX1, float pY1, float pX2, float pY2, float pX3, float pY3 );
	bool			ExecutePreProcessing( void );

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

#endif // __HSDATAMATRIX_H__

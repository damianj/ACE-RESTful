// ****************************************************************************
//
// HSBarcode																 
//
// ****************************************************************************
//
// File.........: HSBarcode.h
//
// Description..: This file contains the definition of the HSBarcode class.
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

#ifndef __HSBARCODE_H__
#define __HSBARCODE_H__

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

class HSSYMBOLOGY_EXPORT HSBarcode
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

	enum hsBarcodeType
	{
		hsBarcodeInvalidType = -1,
		hsBarcodeCode128 = 0,
		hsBarcodeCode39 = 1,
		hsBarcodeCode93 = 2,
		hsBarcodeI2of5 = 3,
		hsBarcodeCodabar = 4,
		hsBarcodeUPCEAN = 5,
		hsBarcodeUPCE = 6,
		hsBarcodeUPCSupplemental = 7,
		hsBarcodePDF417 = 8,
		hsBarcodeBC412 = 9,
		hsBarcodePostnet = 10,
		hsBarcodePharmacode = 11
	};

	enum hsBarcodePolarity
	{
		hsBarcodePolarityLightOnDark = 0,
		hsBarcodePolarityDarkOnLight = 1
	};

	enum hsBarcodeProcessing
	{
		hsBarcodeProcessingNone = 0,
		hsBarcodeProcessingInvert = 1,
		hsBarcodeProcessingErode = 2,
		hsBarcodeProcessingDilate = 3,
		hsBarcodeProcessingOpen = 4,
		hsBarcodeProcessingClose = 5,
		hsBarcodeProcessingGaussian = 6,
		hsBarcodeProcessingSharpen = 7,
		hsBarcodeProcessingSharpenLow = 8,
		hsBarcodeProcessingMedian = 9,
		hsBarcodeProcessingHistogramStretching = 10
	};

	enum hsBarcodeSearchDirection
	{
		hsBarcodeDirectionHorizontal = 0,
		hsBarcodeDirectionVertical = 1,
		hsBarcodeDirectionHorizontalVertical = 2,
		hsBarcodeDirectionVerticalHorizontal = 3
	};

	// CONSTANTS

	static const int hsBarcodeMaximumSymbols;
	static const int hsDefaultBarcodesToDecode;
	static const int hsDefaultProcessingAlgorithm;
	static const int hsDefaultProcessingSize;
	static const int hsMinProcessingSize;
	static const int hsMaxProcessingSize;
	static const long hsDefaultTimeout;
	static const long hsMinTimeout;
	static const long hsMaxTimeout;
	static const int hsMinBarcodeToDecode;
	static const int hsMaxBarcodeToDecode;
	static const int hsDefaultProbeSpacing;
	static const int hsMinProbeSpacing;
	static const int hsMaxProbeSpacing;
	static const int hsDefaultMaximumBarcodeWidth;
	static const int hsDefaultMinimumBarcodeWidth;
	static const int hsMinimumBarcodeWidth;
	static const int hsMaximumBarcodeWidth;
	static const int hsDefaultMinimumNumberOfBars;
	static const int hsDefaultMaximumNumberOfBars;
	static const int hsMinimumNumberOfBars;
	static const int hsMaximumNumberOfBars;
	static const int hsDefaultMinimumBarcodeLength;
	static const int hsDefaultMaximumBarcodeLength;
	static const int hsMinimumBarcodeLength;
	static const int hsMaximumBarcodeLength;
	static const int hsDefaultMaximumBarcodeHeight;
	static const int hsDefaultMinimumBarcodeHeight;
	static const int hsMaximumBarcodeHeight;
	static const int hsMinimumBarcodeHeight;
	static const int hsDefaultEdgeStrength;
	static const int hsMinimumEdgeStrength;
	static const int hsMaximumEdgeStrength;
	static const int hsDefaultBarcodeQuietZone;
	static const int hsMinimumBarcodeQuietZone;
	static const int hsMaximumBarcodeQuietZone;
	static const long  hsBarcodeTypeCount;
	static const hsBarcodeSearchDirection hsDefaultSearchDirection;

public:

	// UTILITY

					HSBarcode( void );
					HSBarcode( const HSBarcode & Object );
    virtual		   ~HSBarcode( void );

					HSBarcode & operator=( const HSBarcode & Object );

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

	hsBarcodeProcessing	GetProcessingAlgorithm( void ) const;
	void			SetProcessingAlgorithm( hsBarcodeProcessing Value );
	int				GetProcessingSize( void ) const;
	void			SetProcessingSize( int Value );
	long			GetTimeout( void ) const;
	void			SetTimeout( long Value );
	int				GetBarcodeToDecode( void ) const;
	void			SetBarcodeToDecode( int Value );
	int				GetHorizontalProbeSpacing( void ) const;
	void			SetHorizontalProbeSpacing( int Value );
	int				GetVerticalProbeSpacing( void ) const;
	void			SetVerticalProbeSpacing( int Value );
	hsBarcodeSearchDirection GetSearchDirection( void ) const;
	void			SetSearchDirection( hsBarcodeSearchDirection Value );

	bool			GetBarcodeTypeEnabled( hsBarcodeType pType ) const;
	void			SetBarcodeTypeEnabled( hsBarcodeType pType, bool Value );
	bool			GetStartStopEnabled( hsBarcodeType pType ) const;
	void			SetStartStopEnabled( hsBarcodeType pType, bool Value );
	bool			GetCheckSumEnabled( hsBarcodeType pType ) const;
	void			SetCheckSumEnabled( hsBarcodeType pType, bool Value );
	bool			GetDecodeLeftToRightEnabled( hsBarcodeType pType ) const;
	void			SetDecodeLeftToRightEnabled( hsBarcodeType pType, bool Value );
	bool			GetPolarityEnabled( hsBarcodeType pType ) const;
	void			SetPolarityEnabled( hsBarcodeType pType, bool Value );
	hsBarcodePolarity GetPolarity( hsBarcodeType pType ) const;
	void			SetPolarity( hsBarcodeType pType, hsBarcodePolarity Value );

	// Advanced ///////////////////////////////////////////////////////////////////

	// Attributes //

	int				GetMaximumBarWidth( void ) const;
	void			SetMaximumBarWidth( int Value );
	int				GetMinimumBarWidth( void ) const;
	void			SetMinimumBarWidth( int Value );
	int				GetMaximumNumberOfBars( void ) const;
	void			SetMaximumNumberOfBars( int Value );
	int				GetMinimumNumberOfBars( void ) const;
	void			SetMinimumNumberOfBars( int Value );
	int				GetMaximumCodeLength( void ) const;
	void			SetMaximumCodeLength( int Value );
	int				GetMinimumCodeLength( void ) const;
	void			SetMinimumCodeLength( int Value );
	int				GetMaximumCodeHeight( void ) const;
	void			SetMaximumCodeHeight( int Value );
	int				GetMinimumCodeHeight( void ) const;
	void			SetMinimumCodeHeight( int Value );

	int				GetMinimumEdgeStrength( void ) const;
	void			SetMinimumEdgeStrength( int Value );
	int				GetMinimumQuietZone( void ) const;
	void			SetMinimumQuietZone( int Value );

	// Results ////////////////////////////////////////////////////////////////

	// Attributes //

	float			GetElapsedTime( void ) const;

	int				GetBarcodeFoundCount( void ) const;
	float			GetBarcodeDecodeTime( int Index ) const;
	const char *	GetBarcodeString( int Index ) const;
	long			GetBarcodeStatusCode( int Index ) const;
	float			GetBarcodeAngle( int Index ) const;
	float			GetBarcodeCornerX( int Index, int Corner ) const;
	float			GetBarcodeCornerY( int Index, int Corner ) const;
	hsBarcodeType	GetBarcodeType( int Index ) const;
	const char *	GetBarcodeTypeString( int Index ) const;
	const char *	GetBarcodeStatusString( int Index ) const;

	hsCoordinateSystem	GetCoordinateSystem( void ) const;
	void			SetCoordinateSystem( hsCoordinateSystem Value );

	// Misc ///////////////////////////////////////////////////////////////////

	// Operations //

    float			Execute( void );
	bool			Learn( void );
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

#endif // __HSBARCODE_H__

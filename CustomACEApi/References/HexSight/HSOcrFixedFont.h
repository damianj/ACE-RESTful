// ****************************************************************************
//
// HSOcrFixedFont																 
//
// ****************************************************************************
//
// File.........: HSOcrFixedFont.h
//
// Description..: This file contains the definition of the HSOcrFixedFont class.
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

#ifndef __HSOCRFIXEDFONT_H__
#define __HSOCRFIXEDFONT_H__

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

class HSSYMBOLOGY_EXPORT HSOcrFixedFont
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
		hsCoordinateSystemInternal = 4 // Reserved for internal use
	};

	enum hsOcrFontType
	{
		hsOcrFontTypeSemi = 0,
		hsOcrFontTypeOcrA = 1,
		hsOcrFontTypeOcrB = 2
	};

	enum hsOcrMethod
	{
		hsOcrMethodStandard = 0,
		hsOcrMethodDotMatrix = 1,
		hsOcrMethodDegraded = 2
	};

	enum hsOcrTextPolarity
	{
		hsOcrTextPolarityLightOnDark = 0,
		hsOcrTextPolarityDarkOnLight = 1,
		hsOcrTextPolarityUnknown = 2,
	};

	enum hsOcrTextOrientation
	{
		hsOcrTextOrientationNormal = 0,
		hsOcrTextOrientationTopToBottom = 1,
		hsOcrTextOrientationUpsideDown = 2,
		hsOcrTextOrientationBottomToTop = 3,
		hsOcrTextOrientationDelta = 6,
		hsOcrTextOrientationMirrorNormal = 10,
		hsOcrTextOrientationMirrorTopToBottom = 11,
		hsOcrTextOrientationMirrorUpsideDown = 12,
		hsOcrTextOrientationMirrorBottomToTop = 13
	};

	enum hsOcrFineTuneMethod
	{
		hsOcrTuneDetectSpace = 0,
		hsOcrTuneNumberOfCharactersVary = 1,
		hsOcrTuneDisablePreFilter = 2,
		hsOcrTuneCharacterSizeSpaceVary = 3,
		hsOcrTuneSpeedEnhance = 4,
		hsOcrTuneRemoveNoise = 5,
		hsOcrTuneReserved1 = 6,
		hsOcrTuneReserved2 = 7,
		hsOcrTuneSemiMChecksum = 8,
		hsOcrTuneReserved3 = 9
	};

	enum hsOcrProcessing
	{
		hsOcrProcessingNone = 0,
		hsOcrProcessingInvert = 1,
		hsOcrProcessingErode = 2,
		hsOcrProcessingDilate = 3,
		hsOcrProcessingOpen = 4,
		hsOcrProcessingClose = 5,
		hsOcrProcessingGaussian = 6,
		hsOcrProcessingSharpen = 7,
		hsOcrProcessingSharpenLow = 8,
		hsOcrProcessingMedian = 9,
		hsOcrProcessingHistogramStretching = 10
	};

	// CONSTANTS

	static const int hsDefaultProcessingSize;
	static const int hsMinProcessingSize;
	static const int hsMaxProcessingSize;
	static const int hsDefaultRowsToRead;
	static const int hsMinRowsToRead;
	static const int hsMaxRowsToRead;
	static const int hsMaximumRows;
	static const int hsDefaultCharactersOnRow;
	static const int hsMinimumCharactersOnRow;
	static const int hsMaximumCharactersOnRow;
	static const int hsDefaultConfidence;
	static const int hsMinimumConfidence;
	static const int hsMaximumConfidence;
	static const int hsDefaultCharacterWidth;
	static const int hsDefaultCharacterHeight;
	static const int hsMinimumCharacterDimension;
	static const int hsMaximumCharacterDimension;
	static const float hsDefaultCharacterSpacing;
	static const float hsMinimumCharacterSpacing;
	static const float hsMaximumCharacterSpacing;
	static const int hsDefaultCharacterStrokeWidth;
	static const int hsMinimumCharacterStrokeWidth;
	static const int hsMaximumCharacterStrokeWidth;
	static const int hsDefaultStringLengthVariation;
	static const int hsMinimumStringLengthVariation;
	static const int hsMaximumStringLengthVariation;
	static const int hsMaximumCharacterCount;
	static const int hsMaximumFineTuneMethod;
	static const hsOcrFontType	hsDefaultFontType;
	static const hsOcrMethod	hsDefaultOcrMethod;
	static const hsOcrTextPolarity	hsDefaultTextPolarity;
	static const hsOcrTextOrientation	hsDefaultTextOrientation;
	static const hsOcrProcessing	hsDefaultProcessingAlgorithm;

	static const char hsFieldingAlphanumeric;
	static const char hsFieldingAlpha;
	static const char hsFieldingNumeric;
	static const char hsFieldingOther;

public:

	// UTILITY

					HSOcrFixedFont( void );
					HSOcrFixedFont( const HSOcrFixedFont & pObject );
    virtual		   ~HSOcrFixedFont( void );

					HSOcrFixedFont & operator=( const HSOcrFixedFont & pObject );

	virtual int		ExchangeProp( 
						const char * pPropName, 
						unsigned short pPropType,
						void * pPropPointer, 
						const void * pPropDefault = NULL );

public:

	// Get/Set Database Handle

    unsigned int	GetDatabase( void ) const;
    void			SetDatabase( unsigned int pHandle, unsigned long pPassword = NULL );

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

	hsOcrProcessing	GetProcessingAlgorithm( void ) const;
	void			SetProcessingAlgorithm( hsOcrProcessing Value );
	int				GetProcessingSize( void ) const;
	void			SetProcessingSize( int Value );

	int				GetRowsToRead( void ) const;
	void			SetRowsToRead( int Value );
	hsOcrFontType	GetFontType( void ) const;
	void			SetFontType( hsOcrFontType Value );
	hsOcrMethod		GetOcrMethod( void ) const;
	void			SetOcrMethod( hsOcrMethod Value );
	hsOcrTextPolarity GetTextPolarity( void ) const;
	void			SetTextPolarity( hsOcrTextPolarity Value );
	hsOcrTextOrientation GetTextOrientation( void ) const;
	void			SetTextOrientation( hsOcrTextOrientation Value );

	int				GetCharactersOnRow( int RowIndex );
	void			SetCharactersOnRow( int RowIndex, int Value );

	// Advanced ///////////////////////////////////////////////////////////////////

	// Attributes //

	int				GetConfidenceThreshold( void ) const;
	void			SetConfidenceThreshold( int Value );
	int				GetCharacterWidth( void ) const;
	void			SetCharacterWidth( int Value );
	int				GetCharacterHeight( void ) const;
	void			SetCharacterHeight( int Value );
	float			GetCharacterSpacing( void ) const;
	void			SetCharacterSpacing( float Value );
	int				GetCharacterStrokeWidth( void ) const;
	void			SetCharacterStrokeWidth( int Value );
	int				GetStringLengthVariation( void ) const;
	void			SetStringLengthVariation( int Value );

	bool			GetFineTuneMethodEnabled( hsOcrFineTuneMethod Method ) const;
	void			SetFineTuneMethodEnabled( hsOcrFineTuneMethod Method, bool Value );

	const char *	GetCustomFielding( int RowIndex, int CharacterIndex );
	void			SetCustomFielding( int RowIndex, int CharacterIndex, const char *Value );

	// Results ////////////////////////////////////////////////////////////////

	// Attributes //

	float			GetElapsedTime( void ) const;

	hsCoordinateSystem	GetCoordinateSystem( void ) const;
	void			SetCoordinateSystem( hsCoordinateSystem Value );

	int				GetStatusCode( void ) const;
	const char *	GetStatusCodeString( void ) const;

	const char *	GetString( int RowIndex );
	int				GetStringConfidence( int RowIndex );
	int				GetCharacterConfidence( int RowIndex, int CharacterIndex );
	float			GetCharacterCornerX( int RowIndex, int CharacterIndex, int CornerIndex );
	float			GetCharacterCornerY( int RowIndex, int CharacterIndex, int CornerIndex );

	// Learn ///////////////////////////////////////////////////////////////////

	// Attributes //

	long			GetLearnStatusCode( void ) const;
	const char *	GetLearnStatusCodeString( void ) const;
	float			GetLearnElapsedTime( void ) const;

	float			GetLearnTrainingBoxTop( void ) const;	
	void			SetLearnTrainingBoxTop( float Value );
	float			GetLearnTrainingBoxBottom( void ) const;
	void			SetLearnTrainingBoxBottom( float Value );
	float			GetLearnTrainingBoxLeft( void )const;
	void			SetLearnTrainingBoxLeft( float Value );
	float			GetLearnTrainingBoxRight( void ) const;
	void			SetLearnTrainingBoxRight( float Value );
	float			GetLearnPrimaryCharacterBoxTop( void ) const;
	void			SetLearnPrimaryCharacterBoxTop( float Value );
	float			GetLearnPrimaryCharacterBoxBottom( void ) const;
	void			SetLearnPrimaryCharacterBoxBottom( float Value );
	float			GetLearnPrimaryCharacterBoxLeft( void ) const;
	void			SetLearnPrimaryCharacterBoxLeft( float Value );
	float			GetLearnPrimaryCharacterBoxRight( void ) const;
	void			SetLearnPrimaryCharacterBoxRight( float Value );
	hsOcrFontType	GetLearnFontType( void ) const;
	void			SetLearnFontType( hsOcrFontType Value );
	hsOcrMethod		GetLearnOcrMethod( void ) const;
	void			SetLearnOcrMethod( hsOcrMethod Value );
	hsOcrTextPolarity GetLearnTextPolarity( void ) const;
	void			SetLearnTextPolarity( hsOcrTextPolarity Value );
	hsOcrTextOrientation GetLearnTextOrientation( void ) const;
	void			SetLearnTextOrientation( hsOcrTextOrientation Value );
	char			GetLearnPrimaryCharacter( void ) const;
	void			SetLearnPrimaryCharacter( char Value );
	const char *	GetLearnTrainingString( void ) const;
	void			SetLearnTrainingString( const char * Value );

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

	void			_Load( const char * pPrefix, void * = NULL );
	void			_Save( const char * pPrefix, void * = NULL );

private:

	void * _pimpl;
};


// ****************************************************************************
// * Functions prototypes
// ****************************************************************************

// ****************************************************************************
// * Inline functions definitions
// ****************************************************************************

#endif // __HSOCRFIXEDFONT_H__

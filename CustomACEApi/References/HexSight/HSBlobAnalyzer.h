// ****************************************************************************
//
// HSBlobAnalyzer																 
//
// ****************************************************************************
//
// File.........: HSBlobAnalyzer.h
//
// Description..: This file contains the definition of the HSBlobAnalyzer class.
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

#ifndef __HSBLOBANALYZER_H__
#define __HSBLOBANALYZER_H__

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
// HSBLOBANALYZER_COMPILATION_DLL <Reserved>

#ifdef WIN32
	#ifdef HSBLOBANALYZER_COMPILATION_DLL
		#define HSBLOBANALYZER_EXPORT __declspec(dllexport)
	#else
		#ifdef HSSTATICLIBRARY
			#define HSBLOBANALYZER_EXPORT
		#else
			#define HSBLOBANALYZER_EXPORT __declspec(dllimport)
		#endif
	#endif
#else
	#define HSBLOBANALYZER_EXPORT
#endif

// ****************************************************************************
// * Class definition
// ****************************************************************************

class HSBLOBANALYZER_EXPORT HSBlobAnalyzer
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

	enum hsSegmentation
	{
		hsLight = 0,
		hsDark = 1,
		hsInside = 2,
		hsOutside = 3,
		hsDynamicLight = 4,
		hsDynamicDark = 5,
		hsDynamicInside = 6,
		hsDynamicOutside = 7,
		hsHSLInside = 8,
		hsHSLOutside = 9
	};

	enum hsSegmentationLightPoint
	{
		hsLightBottom = 0,
		hsLightTop = 1
	};

	enum hsSegmentationDarkPoint
	{
		hsDarkTop = 0,
		hsDarkBottom = 1
	};

	enum hsSegmentationInsidePoint
	{
		hsInsideBottomLeft = 0,
		hsInsideTopLeft = 1,
		hsInsideTopRight = 2,
		hsInsideBottomRight = 3
	};

	enum hsSegmentationOutsidePoint
	{
		hsOutsideTopLeft = 0,
		hsOutsideBottomLeft = 1,
		hsOutsideBottomRight = 2,
		hsOutsideTopRight = 3
	};

	enum hsSegmentationHSLParameter
	{
		hsHSLHue = 0,
		hsHSLSaturation = 1,
		hsHSLLuminance = 2,
		hsHSLHueTolerance = 3,
		hsHSLSaturationTolerance = 4,
		hsHSLLuminanceTolerance = 5
	};

	enum hsChainCodeDirection
	{
		hsDirectionRight = 0,
		hsDirectionTop = 1,
		hsDirectionLeft = 2,
		hsDirectionBottom = 3
	};

	enum hsSortBlobsBy
	{
		hsArea = 0,
		hsBoundingBoxBottom = 1,
		hsBoundingBoxCenterX = 2,
		hsBoundingBoxCenterY = 3,
		hsBoundingBoxHeight = 4,
		hsBoundingBoxLeft = 5,
		hsBoundingBoxRight = 6,
		hsBoundingBoxRotation = 7,
		hsBoundingBoxTop = 8,
		hsBoundingBoxWidth = 9,
		hsChainCodeDeltaX = 10,
		hsChainCodeDeltaY = 11,
		hsChainCodeLength = 12,
		hsChainCodeStartX = 13,
		hsChainCodeStartY = 14,
		hsConvexPerimeter = 15,
		hsElongation = 16,
		hsExtentBottom = 17,
		hsExtentLeft = 18,
		hsExtentRight = 19,
		hsExtentTop = 20,
		hsGreyLevelMaximum = 21, 
		hsGreyLevelMean = 22,
		hsGreyLevelMinimum = 23,
		hsGreyLevelRange = 24,
		hsGreyLevelStdDev = 25,
		hsHoleCount = 26,
		hsInertiaMaximum = 27,
		hsInertiaMinimum = 28,
		hsInertiaXAxis = 29,
		hsInertiaYAxis = 30,
		hsIntrinsicBoundingBoxBottom = 31,
		hsIntrinsicBoundingBoxCenterX = 32,
		hsIntrinsicBoundingBoxCenterY = 33,
		hsIntrinsicBoundingBoxHeight = 34,
		hsIntrinsicBoundingBoxLeft = 35,
		hsIntrinsicBoundingBoxRight = 36,
		hsIntrinsicBoundingBoxRotation = 37,
		hsIntrinsicBoundingBoxTop = 38,
		hsIntrinsicBoundingBoxWidth = 39,
		hsIntrinsicExtentBottom = 40,
		hsIntrinsicExtentLeft = 41,
		hsIntrinsicExtentRight = 42,
		hsIntrinsicExtentTop = 43,
		hsPositionX = 44,
		hsPositionY = 45,
		hsPrincipalAxesRotation = 46,
		hsRawPerimeter = 47,
		hsRoundness = 48
	};

	enum hsProcessingFormat
	{
		hsProcessingFormatNative = 0,
		hsProcessingFormatGreyScale = 1,
	};


	// CONSTANTS

public:

	// UTILITY

					HSBlobAnalyzer( void );
					HSBlobAnalyzer( const HSBlobAnalyzer & Object );
    virtual		   ~HSBlobAnalyzer( void );

					HSBlobAnalyzer & operator=( const HSBlobAnalyzer & Object );

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

	const char *	GetOutputBlobImage( void ) const;
	void			SetOutputBlobImage( const char *Value );
	const char *	GetOutputBlobView( void ) const;
	void			SetOutputBlobView( const char *Value );
	bool			GetOutputBlobImageEnabled( void ) const;
	void			SetOutputBlobImageEnabled( bool Value );
	bool			GetClearOutputBlobImageEnabled( void ) const;
	void			SetClearOutputBlobImageEnabled( bool Value );
	bool			GetExcludeRejectedBlobsEnabled( void ) const;
	void			SetExcludeRejectedBlobsEnabled( bool Value );

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

	bool			GetProcessingFormatEnabled( hsProcessingFormat pFormat ) const;
	hsProcessingFormat GetProcessingFormat( void ) const;
	void			SetProcessingFormat( hsProcessingFormat Value );

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

	// Transform /////////////////////////////////////////////////////////////

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

	// Configuration //////////////////////////////////////////////////////////

	// Attributes //

	float			GetMinimumBlobArea( void ) const;
	void			SetMinimumBlobArea( float Value );
	float			GetMaximumBlobArea( void ) const;
	void			SetMaximumBlobArea( float Value );

	bool			GetHoleFillingEnabled( void ) const;
	void			SetHoleFillingEnabled( bool Value );

	bool			GetRejectClippedBlobsEnabled( void ) const;
	void			SetRejectClippedBlobsEnabled( bool Value );

	hsSegmentation	GetSegmentationMode( void ) const;
	void			SetSegmentationMode( hsSegmentation Value );
	int				GetSegmentationLight( hsSegmentationLightPoint Index ) const;
	void			SetSegmentationLight( hsSegmentationLightPoint Index, int Value );
	int				GetSegmentationDark( hsSegmentationDarkPoint Index ) const;
	void			SetSegmentationDark( hsSegmentationDarkPoint Index, int Value );
	int				GetSegmentationInside( hsSegmentationInsidePoint Index ) const;
	void			SetSegmentationInside( hsSegmentationInsidePoint Index, int Value );
	int				GetSegmentationOutside( hsSegmentationOutsidePoint Index ) const;
	void			SetSegmentationOutside( hsSegmentationOutsidePoint Index, int Value );
	float			GetSegmentationDynamicLight( hsSegmentationLightPoint Index ) const;
	void			SetSegmentationDynamicLight( hsSegmentationLightPoint Index, float Value, bool UpdateCurrent = false );
	float			GetSegmentationDynamicDark( hsSegmentationDarkPoint Index ) const;
	void			SetSegmentationDynamicDark( hsSegmentationDarkPoint Index, float Value, bool UpdateCurrent = false );
	float			GetSegmentationDynamicInside( hsSegmentationInsidePoint Index ) const;
	void			SetSegmentationDynamicInside( hsSegmentationInsidePoint Index, float Value, bool UpdateCurrent = false );
	float			GetSegmentationDynamicOutside( hsSegmentationOutsidePoint Index ) const;
	void			SetSegmentationDynamicOutside( hsSegmentationOutsidePoint Index, float Value, bool UpdateCurrent = false );
	int				GetSegmentationHSLInside( hsSegmentationHSLParameter Index ) const;
	void			SetSegmentationHSLInside( hsSegmentationHSLParameter Index, int Value, bool UpdateCurrent = false );
	int				GetSegmentationHSLOutside( hsSegmentationHSLParameter Index ) const;
	void			SetSegmentationHSLOutside( hsSegmentationHSLParameter Index, int Value, bool UpdateCurrent = false );

	// Results ////////////////////////////////////////////////////////////////

	// Attributes //

	float			GetElapsedTime( void ) const;

	hsCoordinateSystem	GetCoordinateSystem( void ) const;
	void			SetCoordinateSystem( hsCoordinateSystem Value );

	bool			GetSortResultsEnabled( void ) const;
	void			SetSortResultsEnabled( bool Value );
	hsSortBlobsBy	GetSortBlobsBy( void ) const;
	void			SetSortBlobsBy( hsSortBlobsBy Value );
	bool			GetPerimeterResultsEnabled( bool Last = false ) const;
	void			SetPerimeterResultsEnabled( bool Value );
	bool			GetIntrinsicInertiaResultsEnabled( bool Last = false ) const;
	void			SetIntrinsicInertiaResultsEnabled( bool Value );
	bool			GetExtrinsicInertiaResultsEnabled( bool Last = false ) const;
	void			SetExtrinsicInertiaResultsEnabled( bool Value );
	bool			GetIntrinsicBoxResultsEnabled( bool Last = false ) const;
	void			SetIntrinsicBoxResultsEnabled( bool Value );
	bool			GetExtrinsicBoxResultsEnabled( bool Last = false ) const;
	void			SetExtrinsicBoxResultsEnabled( bool Value );
	bool			GetChainCodeResultsEnabled( bool Last = false ) const;
	void			SetChainCodeResultsEnabled( bool Value );
	bool			GetGreyLevelResultsEnabled( bool Last = false ) const;
	void			SetGreyLevelResultsEnabled( bool Value );
	bool			GetTopologicalResultsEnabled( bool Last = false ) const;
	void			SetTopologicalResultsEnabled( bool Value );

	int				GetBlobCount( void ) const;

	float			GetBlobArea( int Index ) const;
	float			GetBlobPositionX( int Index ) const;
	float			GetBlobPositionY( int Index ) const;

	float			GetBlobConvexPerimeter( int Index ) const;
	float			GetBlobRawPerimeter( int Index ) const;
	float			GetBlobElongation( int Index ) const;
	float			GetBlobPrincipalAxesRotation( int Index ) const;
	float			GetBlobGreyLevelMean( int Index ) const;
	int				GetBlobGreyLevelRange( int Index ) const;
	float			GetBlobGreyLevelStdDev( int Index ) const;
	int				GetBlobGreyLevelMinimum( int Index ) const;
	int				GetBlobGreyLevelMaximum( int Index ) const;
	float			GetBlobRoundness( int Index ) const;
	float			GetBlobBoundingBoxCenterX( int Index ) const;
	float			GetBlobBoundingBoxCenterY( int Index ) const;
	float			GetBlobBoundingBoxHeight( int Index ) const;
	float			GetBlobBoundingBoxWidth( int Index ) const;
	float			GetBlobIntrinsicBoundingBoxCenterX( int Index ) const;
	float			GetBlobIntrinsicBoundingBoxCenterY( int Index ) const;
	float			GetBlobIntrinsicBoundingBoxHeight( int Index ) const;
	float			GetBlobIntrinsicBoundingBoxWidth( int Index ) const;
	float			GetBlobInertiaMinimum( int Index ) const;
	float			GetBlobInertiaMaximum( int Index ) const;
	float			GetBlobInertiaXAxis( int Index ) const;
	float			GetBlobInertiaYAxis( int Index ) const;
	float			GetBlobIntrinsicBoundingBoxLeft( int Index ) const;
	float			GetBlobIntrinsicBoundingBoxRight( int Index ) const;
	float			GetBlobIntrinsicBoundingBoxTop( int Index ) const;
	float			GetBlobIntrinsicBoundingBoxBottom( int Index ) const;
	float			GetBlobIntrinsicBoundingBoxRotation( int Index ) const;
	float			GetBlobIntrinsicExtentLeft( int Index ) const;
	float			GetBlobIntrinsicExtentRight( int Index ) const;
	float			GetBlobIntrinsicExtentTop( int Index ) const;
	float			GetBlobIntrinsicExtentBottom( int Index ) const;
	float			GetBlobBoundingBoxLeft( int Index ) const;
	float			GetBlobBoundingBoxRight( int Index ) const;
	float			GetBlobBoundingBoxTop( int Index ) const;
	float			GetBlobBoundingBoxBottom( int Index ) const;
	float			GetBlobBoundingBoxRotation( int Index ) const;
	float			GetBlobExtentLeft( int Index ) const;
	float			GetBlobExtentRight( int Index ) const;
	float			GetBlobExtentTop( int Index ) const;
	float			GetBlobExtentBottom( int Index ) const;
	long			GetBlobHoleCount( int Index ) const;
	long			GetBlobChainCodeLength( int Index ) const;
	hsChainCodeDirection	GetBlobChainCode( long Position, int Index );
	float			GetBlobChainCodeStartX( int Index );
	float			GetBlobChainCodeStartY( int Index );
	float			GetBlobChainCodeDeltaX( int Index );
	float			GetBlobChainCodeDeltaY( int Index );

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

#endif // __HSBLOBANALYZER_H__

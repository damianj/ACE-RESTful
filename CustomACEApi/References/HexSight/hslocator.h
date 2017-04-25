// ****************************************************************************
//
// HSLocator																 
//
// ****************************************************************************
//
// File.........: HSLocator.h
//
// Description..: This file contains the definition of the HSLocator class.
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

#ifndef __HSLOCATOR_H__
#define __HSLOCATOR_H__

// ****************************************************************************
// * Constants
// ****************************************************************************

// ****************************************************************************
// * Types
// ****************************************************************************

class HSModel;
class HSPoint;

static void		OnEngineDone( void *, int & );

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
// HSLOCATOR_COMPILATION_DLL <Reserved>

#ifdef WIN32
	#ifdef HSLOCATOR_COMPILATION_DLL
		#define HSLOCATOR_EXPORT __declspec(dllexport)
	#else
		#ifdef HSSTATICLIBRARY
			#define HSLOCATOR_EXPORT
		#else
			#define HSLOCATOR_EXPORT __declspec(dllimport)
		#endif
	#endif
#else
	#define HSLOCATOR_EXPORT
#endif

// ****************************************************************************
// * Class definition
// ****************************************************************************

class HSLOCATOR_EXPORT HSLocator
{
public:

	static const int hsMinimumContrastThreshold;
	static const int hsMaximumContrastThreshold;
	static const int hsMinimumOutlineLevel;
	static const int hsMaximumOutlineLevel;
	static const int hsMinimumDetailLevel;
	static const int hsMaximumDetailLevel;
	static const int hsMinimumRecognitionLevel;
	static const int hsMaximumRecognitionLevel;
	static const int hsMinimumPositioningLevel;
	static const int hsMaximumPositioningLevel;

	static const char* hsModelImageName;
	static const char* hsModelMaskName;
	static const char* hsModelOutlineFeaturesName;
	static const char* hsModelDetailFeaturesName;
	static const char* hsModelOutlineContoursName;
	static const char* hsModelDetailContoursName;

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

	enum hsInstanceOrdering
	{
		hsEvidence = 0,
		hsLeftToRight = 1,
		hsRightToLeft = 2,
		hsTopToBottom = 3,
		hsBottomToTop = 4,
		hsQuality = 5,
		hsDistanceImage = 6,
		hsDistanceWorld = 7,
		hsShadingConsistency = 8,
		hsLeftToRightPrecise = 9,
		hsRightToLeftPrecise = 10,
		hsTopToBottomPrecise = 11,
		hsBottomToTopPrecise = 12,
		hsDistanceImagePrecise = 13,
		hsDistanceWorldPrecise = 14

	};

	enum hsContrastThresholdMode
	{
		hsContrastThresholdAdaptiveLowSensitivity = 0,
		hsContrastThresholdAdaptiveNormalSensitivity = 1,
		hsContrastThresholdAdaptiveHighSensitivity = 2,
		hsContrastThresholdFixedValue = 3,
		hsContrastThresholdModelsMode = 4,
		hsContrastThresholdModelsValue = 5,
		hsContrastThresholdModelsValueAndMode = 6
	};

	enum hsLocatorOutputMode
	{
		hsNoGraphics = 0,
		hsTransformedModel = 1,
		hsMatchedModel = 2
	};

	enum hsContourParameters
	{
		hsContourParametersAllModels = -2,
		hsContourParametersCustom = -1
	};

	enum hsContrastPolarity
	{
		hsContrastPolarityNormal = 0,
		hsContrastPolarityReverse = 1,
		hsContrastPolarityNormalAndReverse = 2,
		hsContrastPolarityDontCare = 3
	};

	enum hsModelBasedMode
	{
		hsAbsolute = 0,
		hsRelative = 1
	};

	enum hsProcessingFormat
	{
		hsProcessingFormatNative = 0,
		hsProcessingFormatGreyScale = 1
	};

public:

	// UTILITY

					HSLocator( void );
					HSLocator( const HSLocator & Object );
    virtual		   ~HSLocator( void );

					HSLocator & operator=( const HSLocator & Object );

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
    void			SetInputGreyScaleImage ( const char * Name );
    const char *	GetInputGreyScaleImageView( void ) const;
    void			SetInputGreyScaleImageView( const char * Name );
    const char *	GetInputImage( void ) const;
    void			SetInputImage ( const char * Name );
    const char *	GetInputImageView( void ) const;
    void			SetInputImageView( const char * Name );

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

    const char *	GetOutputModelView( void ) const;
    void			SetOutputModelView( const char * Name );
    bool			GetOutputModelEnabled( void ) const;
    void			SetOutputModelEnabled( bool Enabled );

    const char *	GetOutputOutlineScene( void ) const;
    void			SetOutputOutlineScene( const char * Name );
    const char *	GetOutputOutlineSceneView( void ) const;
    void			SetOutputOutlineSceneView( const char * Name );
    bool			GetOutputOutlineSceneEnabled( void ) const;
    void			SetOutputOutlineSceneEnabled( bool Enabled );

    const char *	GetOutputDetailScene( void ) const;
    void			SetOutputDetailScene( const char * Name );
    const char *	GetOutputDetailSceneView( void ) const;
    void			SetOutputDetailSceneView( const char * Name );
    bool			GetOutputDetailSceneEnabled( void ) const;
    void			SetOutputDetailSceneEnabled( bool Enabled );

    const char *	GetOutputInstanceSceneView( void ) const;
    void			SetOutputInstanceSceneView( const char * Name );
    const char *	GetOutputInstanceScene( void ) const;
    void			SetOutputInstanceScene( const char * Name );
    bool			GetOutputInstanceSceneEnabled( void ) const;
    void			SetOutputInstanceSceneEnabled( bool Enabled );

    hsLocatorOutputMode	GetOutputMode( void ) const;
    void			SetOutputMode( hsLocatorOutputMode Mode );

    hsUnitsLength	GetUnitsLength( void ) const;
    void			SetUnitsLength( hsUnitsLength Units );

    hsUnitsOrientation GetUnitsOrientation( void ) const;
    void			SetUnitsOrientation( hsUnitsOrientation Units );

	bool			GetProcessingFormatEnabled( hsProcessingFormat pFormat ) const;
	hsProcessingFormat GetProcessingFormat( void ) const;
	void			SetProcessingFormat( hsProcessingFormat Value );

	// Operations //

	void			GenerateScenes( bool Outline = true, bool Detail = true, bool Instance = true, unsigned int Handle = 0xffffffff );
	void			GenerateMaskImage( unsigned int Handle = 0xffffffff );

	// Location ////////////////////////////////////////////////////////////////

	// Attributes //

	bool			GetToolUseEntireImage( void ) const;
	void			SetToolUseEntireImage( bool Enabled );

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

	bool			GetCalibratedUnitsEnabled( void ) const;
	void			SetCalibratedUnitsEnabled( bool Value );

	bool			ClearMaskImage( void );
	bool			LoadMaskImage( const char * FileName );
	const char*		GetMaskImageFileName( void ) const;

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

	hsModelBasedMode GetModelBasedScaleFactorMode( void ) const;
	void			SetModelBasedScaleFactorMode( hsModelBasedMode Mode ) const;
	float			GetModelBasedMinimumScaleFactor( void ) const;
	void			SetModelBasedMinimumScaleFactor( float Value ) const;
	float			GetModelBasedMaximumScaleFactor( void ) const;
	void			SetModelBasedMaximumScaleFactor( float Value ) const;

	hsModelBasedMode GetModelBasedRotationMode( void ) const;
	void			SetModelBasedRotationMode( hsModelBasedMode Mode ) const;
	float			GetModelBasedMinimumRotation( void ) const;
	void			SetModelBasedMinimumRotation( float Value ) const;
	float			GetModelBasedMaximumRotation( void ) const;
	void			SetModelBasedMaximumRotation( float Value ) const;

	// Contour ////////////////////////////////////////////////////////////////

	// Attributes //

    hsContourParameters GetParametersBasedOn( void ) const;
    void			SetParametersBasedOn( hsContourParameters Value );

    int				GetOutlineLevel( void ) const;
    void			SetOutlineLevel( int Value );

    int				GetDetailLevel( void ) const;
    void			SetDetailLevel( int Value );

    hsContrastThresholdMode	GetContrastThresholdMode( void ) const;
    hsContrastThresholdMode	GetLiveContrastThresholdMode( void ) const;
    void			SetContrastThresholdMode( hsContrastThresholdMode Value );

    int				GetContrastThreshold( void ) const;
    void			SetContrastThreshold( int Value );

    int				GetTrackingInertia( void ) const;
    void			SetTrackingInertia( int Value );

	// Model //////////////////////////////////////////////////////////////////

	// Attributes //

	const HSModel &	GetModel( int ModelIndex ) const;
	HSModel &		GetModel( int ModelIndex );

	bool			GetModelEnabled( int ModelIndex ) const;
	void			SetModelEnabled( int ModelIndex, bool Enabled );

	const char *	GetModelName( int ModelIndex ) const;
	void			SetModelName( int ModelIndex, const char * Name );

	int				GetModelInstancesAnalyzed( int ModelIndex ) const;

    int				GetModelCount( void ) const;

	const char *	GetModelDatabaseFileName( void ) const;
	void			SetModelDatabaseFileName( const char * FileName );

	unsigned int	GetModelDatabase( void ) const;
	void			SetModelDatabase( unsigned int Value );

	bool			GetUseExternalModelDatabase( void ) const;
	void			SetUseExternalModelDatabase( bool Value );

	bool			GetModelDatabaseModified( void ) const;

	bool			GetModelOptimizerEnabled( void ) const;
	void			SetModelOptimizerEnabled( bool Value );

	float			GetPercentageOfPointsToAnalyze( void ) const;
	void			SetPercentageOfPointsToAnalyze( float Value );

	bool			GetModelDisambiguationEnabled( void ) const;
	void			SetModelDisambiguationEnabled( bool Value );

	// Operations //

    bool			NewModelDatabase( void );
    bool			LoadModelDatabase( const char * FileName );
    bool			SaveModelDatabase( const char * FileName, bool SaveImages = true );

    bool			LoadModelDatabase( void * pMemoryBuffer, unsigned long * pBufferSize );
    bool			SaveModelDatabase( void * pMemoryBuffer, unsigned long * pBufferSize, bool pSaveImages = true );

	bool			RemoveModel( int ModelIndex );

	float			Learn( void );
	void			Unlearn( void );

	int				AddModel( const char * ModelName );
	int				ImportModel( unsigned int SourceModelDatabaseHandle, int SourceModelIndex, const char * NewModelName = NULL );
	int				ImportModel( const char * FileName, const char * NewModelName = NULL );
	int				CopyModel( int ModelIndex, const char * NewModelName );
	int				GetModelIndex( const char * ModelName ) const;

	void			ModelOptimizerReset( void );


	// Search /////////////////////////////////////////////////////////////////

	// Attributes //

    bool			GetNominalScaleFactorEnabled( void ) const;
    void			SetNominalScaleFactorEnabled( bool Value );
    float			GetNominalScaleFactor( void ) const;
    void			SetNominalScaleFactor( float Value );
    float			GetMinimumScaleFactor( void ) const;
    void			SetMinimumScaleFactor( float Value );
    float			GetMaximumScaleFactor( void ) const;
    void			SetMaximumScaleFactor( float Value );

    bool			GetNominalRotationEnabled( void ) const;
    void			SetNominalRotationEnabled( bool Value );
    float			GetNominalRotation( void ) const;
    void			SetNominalRotation( float Value );
    float			GetMinimumRotation( void ) const;
    void			SetMinimumRotation( float Value );
    float			GetMaximumRotation( void ) const;
    void			SetMaximumRotation( float Value );

    bool			GetMaximumInstanceCountEnabled( void ) const;
    void			SetMaximumInstanceCountEnabled( bool Value );
    int				GetMaximumInstanceCount( void ) const;
    void			SetMaximumInstanceCount( int Value );

    bool			GetTimeoutEnabled( void ) const;
    void			SetTimeoutEnabled( bool Value );
    int				GetTimeout( void ) const;
    void			SetTimeout( int Value );

    bool			GetOutputSymmetricInstances( void ) const;
    void			SetOutputSymmetricInstances( bool Value );

    bool			GetSearchBasedOnOutlineLevelOnly( void ) const;
    void			SetSearchBasedOnOutlineLevelOnly( bool Value );

	hsContrastPolarity GetContrastPolarity( void ) const;
	void			SetContrastPolarity( hsContrastPolarity Value );

    hsInstanceOrdering GetInstanceOrdering( void ) const;
    void			SetInstanceOrdering( hsInstanceOrdering Value );
    float			GetInstanceOrderingReferenceX( void ) const;
    void			SetInstanceOrderingReferenceX( float Value );
    float			GetInstanceOrderingReferenceY( void ) const;
    void			SetInstanceOrderingReferenceY( float Value );

    int				GetRecognitionLevel( void ) const;
    void			SetRecognitionLevel( int Value );

    bool			GetUseDefaultConformityTolerance( void ) const;
    void			SetUseDefaultConformityTolerance( bool Value );
    float			GetDefaultConformityTolerance( void ) const;
	bool			GetConformityToleranceRangeEnabled( void ) const;
	void			SetConformityToleranceRangeEnabled( bool Value ) const;
    float			GetMinimumConformityTolerance( void ) const;
    float			GetMaximumConformityTolerance( void ) const;
    float			GetConformityTolerance( void ) const;
    void			SetConformityTolerance( float Value );

    float			GetMinimumModelPercentage( void ) const;
    void			SetMinimumModelPercentage( float Value );

	bool			GetMinimumClearPercentageEnabled( void ) const;
	void			SetMinimumClearPercentageEnabled( bool Value );
 	float			GetMinimumClearPercentage( void ) const;
	void			SetMinimumClearPercentage( float Value );

	float			GetMinimumRequiredFeatures( void ) const;
    void			SetMinimumRequiredFeatures( float Value );

    int				GetPositioningLevel( void ) const;
    void			SetPositioningLevel( int Value );

	// Results ////////////////////////////////////////////////////////////////

	// Attributes //

    int				GetInstanceCount( void ) const;

    float			GetElapsedTime( void ) const;
    float			GetSearchTime( void ) const;
    float			GetLearnTime( void ) const;

    hsCoordinateSystem GetCoordinateSystem( void ) const;
    void			SetCoordinateSystem( hsCoordinateSystem Value );

    int				GetMessageCount( void ) const;
    int				GetMessageNumber( int Index ) const;
    const char *	GetMessageDescription( int Index ) const;

	// Operations //

    float			GetInstanceScaleFactor( int InstanceIndex ) const;
    float			GetInstanceRotation( int InstanceIndex ) const;
    float			GetInstanceTranslationX( int InstanceIndex ) const;
    float			GetInstanceTranslationY( int InstanceIndex ) const;
    int				GetInstanceReferencePointCount( int InstanceIndex ) const;
    float			GetInstanceReferencePointPositionX( int InstanceIndex, int ReferencePointIndex ) const;
    float			GetInstanceReferencePointPositionY( int InstanceIndex, int ReferencePointIndex ) const;
    int				GetInstanceModel( int InstanceIndex ) const;
    const char *	GetInstanceModelName( int InstanceIndex ) const;
	float			GetInstanceFitQuality( int InstanceIndex ) const;
	float			GetInstanceShadingQuality( int InstanceIndex ) const;
    int				GetInstanceSymmetry( int InstanceIndex ) const;
    float			GetInstanceTime( int InstanceIndex ) const;
    float			GetInstanceMatchQuality( int InstanceIndex ) const;
	float			GetInstanceClearQuality( int InstanceIndex ) const;

	float			GetInstanceVisible( int InstanceIndex ) const;
	void			GetInstanceIntrinsicBoundingBox( int InstanceIndex, HSPoint & P0, HSPoint & P1, HSPoint & P2, HSPoint & P3 ) const;

	bool			LockInstances( bool Wait = true );
	void			UnlockInstances( void );

	void			ClearResults( void );

	// Misc ///////////////////////////////////////////////////////////////////

	// Operations //

    float			Execute( void );
    bool			Start( void );
    bool			Stop( void );
    int				Wait( int InstanceCount, int TimeOut, bool * Running );

	virtual void	OnDone( void );
	virtual void	OnInstanceFound( int InstanceIndex );

    void			CompactMemory( void );

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
	void			PostExecute( void );
	friend void		OnEngineDone( void *, int & );

private:

	void * _pimpl;
};

// ****************************************************************************
// * Functions prototypes
// ****************************************************************************

// ****************************************************************************
// * Inline functions definitions
// ****************************************************************************

#endif // __HSLOCATOR_H__

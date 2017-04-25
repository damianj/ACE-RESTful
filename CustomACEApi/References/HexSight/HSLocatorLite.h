// ****************************************************************************
//
// HSLocatorLite																 
//
// ****************************************************************************
//
// File.........: HSLocatorLite.h
//
// Description..: This file contains the definition of the HSLocatorLite class.
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

#ifndef __HSLOCATORLITE_H__
#define __HSLOCATORLITE_H__

// ****************************************************************************
// * Constants
// ****************************************************************************

// ****************************************************************************
// * Types
// ****************************************************************************

class HSModelLite;
class HSPoint;

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
// * Static callback function declaration
// ****************************************************************************

static void	OnEngineDone( void *, int & );

// ****************************************************************************
// * Class definition
// ****************************************************************************

class HSLOCATOR_EXPORT HSLocatorLite
{
public:

	static const int hsMinimumContrastThreshold;
	static const int hsMaximumContrastThreshold;
	static const int hsMinimumOutlineLevel;
	static const int hsMaximumOutlineLevel;
	static const int hsMinimumDetailLevel;
	static const int hsMaximumDetailLevel;

	static const char* hsModelImageName;
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
		hsTransformedModel = 1
	};

public:

	// UTILITY

					HSLocatorLite( void );
					HSLocatorLite( const HSLocatorLite & Object );
    virtual		   ~HSLocatorLite( void );

					HSLocatorLite & operator=( const HSLocatorLite & Object );

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

    const char *	GetOutputModelView( void ) const;
    void			SetOutputModelView( const char * Name );
    bool			GetOutputModelEnabled( void ) const;
    void			SetOutputModelEnabled( bool Enabled );

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

	// Operations //

	void			GenerateScenes( bool Outline = true, bool Detail = true, bool Instance = true, unsigned int Handle = 0xffffffff );

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

	// Contour ////////////////////////////////////////////////////////////////

	// Attributes //

    int				GetOutlineLevel( void ) const;
    int				GetDetailLevel( void ) const;

    hsContrastThresholdMode	GetContrastThresholdMode( void ) const;
    hsContrastThresholdMode	GetLiveContrastThresholdMode( void ) const;

    int				GetContrastThreshold( void ) const;
    int				GetTrackingInertia( void ) const;

	// Model //////////////////////////////////////////////////////////////////

	// Attributes //

	const HSModelLite &	GetModel( int ModelIndex = 0 ) const;
	HSModelLite &		GetModel( int ModelIndex = 0 );

	const char *	GetModelName( int ModelIndex = 0 ) const;
	void			SetModelName( int ModelIndex, const char * Name );

    int				GetModelCount( void ) const;

	const char *	GetModelDatabaseFileName( void ) const;
	void			SetModelDatabaseFileName( const char * FileName );

	unsigned int	GetModelDatabase( void ) const;
	void			SetModelDatabase( unsigned int Value );

	bool			GetModelDatabaseModified( void ) const;

	// Operations //

    bool			NewModelDatabase( void );
    bool			LoadModelDatabase( const char * FileName );
    bool			SaveModelDatabase( const char * FileName );

    bool			LoadModelDatabase( void * pMemoryBuffer, unsigned long * pBufferSize );
    bool			SaveModelDatabase( void * pMemoryBuffer, unsigned long * pBufferSize );

	bool			RemoveModel( int ModelIndex = 0 );

	float			Learn( void );
	void			Unlearn( void );

	int				AddModel( const char * ModelName );
	int				ImportModel( unsigned int SourceModelDatabaseHandle, int SourceModelIndex, const char * NewModelName = NULL );
	int				ImportModel( const char * FileName, const char * NewModelName = NULL );
	int				GetModelIndex( const char * ModelName ) const;

	// Search /////////////////////////////////////////////////////////////////

	// Attributes //

    bool			GetNominalRotationEnabled( void ) const;
    void			SetNominalRotationEnabled( bool Value );
    float			GetNominalRotation( void ) const;
    void			SetNominalRotation( float Value );
    float			GetMinimumRotation( void ) const;
    void			SetMinimumRotation( float Value );
    float			GetMaximumRotation( void ) const;
    void			SetMaximumRotation( float Value );

    int				GetMaximumInstanceCount( void ) const;
    void			SetMaximumInstanceCount( int Value );

    bool			GetTimeoutEnabled( void ) const;
    void			SetTimeoutEnabled( bool Value );
    int				GetTimeout( void ) const;
    void			SetTimeout( int Value );

    float			GetMinimumModelPercentage( void ) const;
    void			SetMinimumModelPercentage( float Value );

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
    int				GetInstanceModel( int InstanceIndex ) const;
    const char *	GetInstanceModelName( int InstanceIndex ) const;
	float			GetInstanceFitQuality( int InstanceIndex ) const;
    float			GetInstanceTime( int InstanceIndex ) const;
    float			GetInstanceMatchQuality( int InstanceIndex ) const;

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

#endif // __HSLOCATORLITE_H__

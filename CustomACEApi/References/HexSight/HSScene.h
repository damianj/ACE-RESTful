// ****************************************************************************
//
// HSClassLibrary
//
// ****************************************************************************
//
// File.........: HSScene.h
//
// Description..: This file contains the definition of the HSScene class.
//
// Platforms....: All
//
// ****************************************************************************
//
//                Copyright (C) 2007 LMI Technologies.
//                All rights reserved
//
// ****************************************************************************
//
// $History:$
//
// ****************************************************************************

#ifndef __HSSCENE_H__
#define __HSSCENE_H__

// ****************************************************************************
// * Constants
// ****************************************************************************

// ****************************************************************************
// * Types
// ****************************************************************************

class HSCalibration;
class HSImage;

// ****************************************************************************
// * Global data
// ****************************************************************************

// ****************************************************************************
// * Macros
// ****************************************************************************

// This is for Library export/import.  
// No define needed when using as a dynamic library
// HSSTATICLIBRARY defined at compilation when library used as a static library
// HSCLL_COMPILATION_DLL <Reserved>

#ifdef WIN32
	#ifdef HSCLL_COMPILATION_DLL
		#define HSCLL_EXPORT __declspec(dllexport)
	#else
		#ifdef HSSTATICLIBRARY
			#define HSCLL_EXPORT
		#else
			#define HSCLL_EXPORT __declspec(dllimport)
		#endif
	#endif
#else
	#define HSCLL_EXPORT
#endif

// ****************************************************************************
// * Class definition
// ****************************************************************************

class HSCLL_EXPORT HSScene 
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

	enum hsCoordinateSystemType
	{
		hsRightHanded = 0,
		hsLeftHanded = 1
	};

	enum hsSceneType
	{
		hsSceneReserved = 0,
		hsSceneStandard = 4,
		hsSceneModel = 5,
		hsSceneModelSource = 6,
		hsSceneInstances = 7
	};

public:

	// UTILITY

	HSScene( void );
	HSScene( hsSceneType SceneType );
	HSScene( const HSScene & Object );
 	~HSScene( void );

	HSScene & operator=( const HSScene & Object );
	bool     operator==( const HSScene & Object ) const;

	void			CopyFormatFrom( const HSImage & Object );
	void			CopyFormatFrom( const HSScene & Object );

public:

	// PROPERTY

    const char *	GetName( void ) const;
	void			SetName( const char * Value );

	const char *	GetInformation( void ) const;
	void			SetInformation( const char * Value );

	hsSceneType		GetType( void ) const;

    long			GetModifyCount( void ) const;
    
    float			GetBoundaryLeft( void ) const;
    float			GetBoundaryBottom( void ) const;
    float			GetBoundaryRight( void ) const;
    float			GetBoundaryTop( void ) const;

    int				GetWidth( void ) const;
    void			SetWidth( int Value );
    int				GetHeight( void ) const;
    void			SetHeight( int Value );
	void			SetSize( int Width, int Height );

    float			GetSubSamplingFactor( void ) const;

    hsCoordinateSystemType GetImageCoordinateSystemType( void ) const;
    void			SetImageCoordinateSystemType( hsCoordinateSystemType Value );

    int				GetOriginX( void ) const;
    void			SetOriginX( int Value );
    int				GetOriginY( void ) const;
    void			SetOriginY( int Value );

    hsUnitsLength	GetUnitsLength( void ) const;
    void			SetUnitsLength( hsUnitsLength Value );

    float			GetAveragePixelWidth( void ) const;
    float			GetAveragePixelHeight( void ) const;

    const HSCalibration & GetCalibration( void ) const;
    HSCalibration &	GetCalibration( void );
    void			SetCalibration( const HSCalibration & Calibration );

	// EdgePath

	long			GetEdgePathCount( void ) const;

    long			GetEdgePathFirstEdgelIndex( long EdgePathIndex ) const;
    long			GetEdgePathLastEdgelIndex ( long EdgePathIndex ) const;

    float			GetEdgePathPerimeter( long EdgePathIndex ) const;
    float			GetEdgePathArea( long EdgePathIndex ) const;
    float			GetEdgePathCentroidX( long EdgePathIndex ) const;
    float			GetEdgePathCentroidY( long EdgePathIndex ) const;
    bool			GetEdgePathClosed( long EdgePathIndex ) const;

	// Edgel

	long			GetEdgelCount( void ) const;

    float			GetEdgelImageX( long EdgelIndex ) const;
    float			GetEdgelImageY( long EdgelIndex ) const;
    float			GetEdgelWorldX( long EdgelIndex ) const;
    float			GetEdgelWorldY( long EdgelIndex ) const;

	float *			GetEdgelImageXArray( void );
	float *			GetEdgelImageYArray( void );
	float *			GetEdgelWorldXArray( void );
	float *			GetEdgelWorldYArray( void );

	// Instance Scene Specific

	void			Allocate( int InstanceCount, int EdgePathCount, int EdgelCount );
	void			CopyInstance( HSScene* SourceScene, int SourceInstanceIndex );

	long			GetInstanceCount( void ) const;
	long			GetInstanceEdgelCount( long InstanceIndex ) const;
	long			GetInstanceEdgePathCount( long InstanceIndex ) const;

    long			GetInstanceFirstEdgePathIndex( long InstanceIndex ) const;
    long			GetInstanceLastEdgePathIndex( long InstanceIndex ) const;

	// Model Source Scene Specific

	long			GetModelEdgePathCount( void ) const;

    long			GetModelEdgePathFirstEdgelIndex( long ModelEdgePathIndex ) const;
    long			GetModelEdgePathLastEdgelIndex( long ModelEdgePathIndex ) const;
    long			GetModelEdgePathNextEdgelIndex( long ModelEdgePathIndex ) const;
    long			GetModelEdgePathPreviousEdgelIndex( long ModelEdgePathIndex ) const;

    float			GetModelEdgePathPerimeter( long ModelEdgePathIndex ) const;
	float			GetModelEdgePathArea( long ModelEdgePathIndex ) const;
    float			GetModelEdgePathCentroidX( long ModelEdgePathIndex ) const;
    float			GetModelEdgePathCentroidY( long ModelEdgePathIndex ) const;

    long			FindModelEdgePathFromEdgel( long EdgelIndex ) const;

public:

	// METHODS

    void			Load( const char * FileName );
    void			Save( const char * FileName );

    void			Modify( void );

    void			ComputeProperties( void );

    void			Reset( void );

    void			ImageToWorld( float & X, float & Y ) const;
    void			WorldToImage( float & X, float & Y ) const;

protected:

	HSScene( void * );
	void * _pimpl;
};

#endif // __HSSCENE_H__

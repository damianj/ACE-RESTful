// ****************************************************************************
//
// HSModelLite																 
//
// ****************************************************************************
//
// File.........: HSModelLite.h
//
// Description..: This file contains the definition of the HSModelLite class.
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

#ifndef __HSMODELLITE_H__
#define __HSMODELLITE_H__

// ****************************************************************************
// * Constants
// ****************************************************************************

// ****************************************************************************
// * Types
// ****************************************************************************

class HSModel;
class HSImage;
class HSScene;
class HSView;

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
	#ifdef HSLOCATOR_COMPILATION_DLL
		#define HSMODEL_EXPORT __declspec(dllexport)
	#else
		#ifdef HSSTATICLIBRARY
			#define HSMODEL_EXPORT
		#else
			#define HSMODEL_EXPORT __declspec(dllimport)
		#endif
	#endif
#else
	#define HSMODEL_EXPORT
#endif

// ****************************************************************************
// * Class definition
// ****************************************************************************

class HSMODEL_EXPORT HSModelLite
{
public:

	static const char* hsModelImageName;
	static const char* hsModelOutlineContoursName;
	static const char* hsModelDetailContoursName;
	static const char* hsModelOptimizerViewName;

	// ENUMERATIONS

	enum hsContrastThresholdMode
	{
		hsContrastThresholdAdaptiveLowSensitivity = 0,
		hsContrastThresholdAdaptiveNormalSensitivity = 1,
		hsContrastThresholdAdaptiveHighSensitivity = 2,
		hsContrastThresholdFixedValue = 3
	};

	enum hsModelFeatureSelection
	{
		hsFeatureSelectionNone = 0,
		hsFeatureSelectionLess = 1,
		hsFeatureSelectionNormal = 2,
		hsFeatureSelectionMore = 3,
		hsFeatureSelectionAll = 4
	};

	enum hsModelScene
	{
		hsModelSceneOutline = 0,
		hsModelSceneDetail = 1
	};

public:

	// UTILITY
					HSModelLite( );
					HSModelLite( const HSModel & Object );
					HSModelLite( const HSModelLite & Object );
	virtual		   ~HSModelLite( void );

					HSModelLite & operator=( const HSModelLite & Object );

public:

	// METHODS

	void			Build( void );
	void			Analyze( void );
	void			Crop( void );

	// PROPERTY

	const char *	GetName( void ) const;
	void			SetName( const char *pValue );

	// Parameters

	bool			GetAutomaticLevels( void ) const;
	void			SetAutomaticLevels( bool Value );
	int				GetOutlineLevel( void ) const;
	void			SetOutlineLevel( int Value );
	int				GetDetailLevel( void ) const;
	void			SetDetailLevel( int Value );
	int				GetContrastThreshold( void ) const;
	void			SetContrastThreshold( int Value );
	hsContrastThresholdMode GetContrastThresholdMode( void ) const;
	void			SetContrastThresholdMode( hsContrastThresholdMode Value );

	hsModelFeatureSelection GetFeatureSelection( void ) const;
	void			SetFeatureSelection( hsModelFeatureSelection Value );

	int				GetBoundingAreaBottom( void ) const;
	void			SetBoundingAreaBottom( int Value );
	int				GetBoundingAreaTop( void ) const;
	void			SetBoundingAreaTop( int Value );
	int				GetBoundingAreaLeft( void ) const;
	void			SetBoundingAreaLeft( int Value );
	int				GetBoundingAreaRight( void ) const;
	void			SetBoundingAreaRight( int Value );

	// Origin (Coordinate System)

	float			GetOriginPositionX( void ) const;
	void			SetOriginPositionX( float Value );
	float			GetOriginPositionY( void ) const;
	void			SetOriginPositionY( float Value );
	float			GetOriginRotation( void ) const;
	void			SetOriginRotation( float Value );

	// Messages

	int				GetMessageCount( void ) const;
	int				GetMessageNumber( int Index ) const;
	const char *	GetMessageDescription( int Index ) const;

	const HSView &	GetView( void ) const;	
	const HSImage &	GetImage( void ) const;
	HSImage	&		GetImage( void );
	const HSScene & GetSceneOutline( void ) const;
	HSScene	&		GetSceneOutline( void );
	const HSScene &	GetSceneDetail( void ) const;
	HSScene	&		GetSceneDetail( void );

protected:

	HSModelLite( void* );
	void * _pimpl;
};

// ****************************************************************************
// * Functions prototypes
// ****************************************************************************

// ****************************************************************************
// * Inline functions definitions
// ****************************************************************************

#endif // __HSMODELLITE_H__

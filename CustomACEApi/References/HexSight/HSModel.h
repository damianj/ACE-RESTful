// ****************************************************************************
//
// HSModel																 
//
// ****************************************************************************
//
// File.........: HSModel.h
//
// Description..: This file contains the definition of the HSModel class.
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

#ifndef __HSMODEL_H__
#define __HSMODEL_H__

// ****************************************************************************
// * Constants
// ****************************************************************************

// ****************************************************************************
// * Types
// ****************************************************************************

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

class HSMODEL_EXPORT HSModel
{
public:

	static const char* hsModelImageName;
	static const char* hsModelMaskName;
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
					HSModel( );
					HSModel( const HSModel & Object );
	virtual		   ~HSModel( void );

					HSModel & operator=( const HSModel & Object );

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
	int				GetTrackingInertia( void ) const;
	void			SetTrackingInertia( int Value );

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

	bool			GetUseCustomShadingArea( void ) const;
	void			SetUseCustomShadingArea( bool Value );
	int				GetShadingAreaBottom( void ) const;
	void			SetShadingAreaBottom( int Value );
	int				GetShadingAreaTop( void ) const;
	void			SetShadingAreaTop( int Value );
	int				GetShadingAreaLeft( void ) const;
	void			SetShadingAreaLeft( int Value );
	int				GetShadingAreaRight( void ) const;
	void			SetShadingAreaRight( int Value );

	bool			GetModelEdgePathRequired( hsModelScene ModelScene, long ModelEdgePathIndex ) const;
	void			SetModelEdgePathRequired( hsModelScene ModelScene, long ModelEdgePathIndex, bool Required );
	bool			GetModelEdgePathLocation( hsModelScene ModelScene, long ModelEdgePathIndex ) const;
	void			SetModelEdgePathLocation( hsModelScene ModelScene, long ModelEdgePathIndex, bool Location );

	long			AddModelEdgePath( hsModelScene ModelScene, long FirstEdgelIndex, long LastEdgelIndex );
	void			RemoveModelEdgePath( hsModelScene ModelScene, long ModelEdgePathIndex );

	// Reference Points

	int				GetReferencePointCount( void ) const;
	float			GetReferencePointPositionX( int Index ) const;
	void			SetReferencePointPositionX( int Index, float Value );
	float			GetReferencePointPositionY( int Index ) const;
	void			SetReferencePointPositionY( int Index, float Value );
	bool			GetReferencePointFixed( void ) const;
	void			SetReferencePointFixed( bool Value );

	int				AddReferencePoint( float X, float Y );
	void			RemoveReferencePoint( int Index );

	// Origin (Coordinate System)

	float			GetOriginPositionX( void ) const;
	void			SetOriginPositionX( float Value );
	float			GetOriginPositionY( void ) const;
	void			SetOriginPositionY( float Value );
	float			GetOriginRotation( void ) const;
	void			SetOriginRotation( float Value );

	// Optimizer

	int				GetInstancesAnalyzed( void ) const;

	bool			GetMorphingDetail( void ) const;
	void			SetMorphingDetail( bool Value );
	bool			GetMorphingOutline( void ) const;
	void			SetMorphingOutline( bool Value );
	int				GetMinimumRecurrenceOutline( void ) const;
	void			SetMinimumRecurrenceOutline( int Value );
	int				GetMinimumRecurrenceDetail( void ) const;
	void			SetMinimumRecurrenceDetail( int Value );

	unsigned int	GetOptimizerDatabase( void ) const;
	void			SetOptimizerDatabase( unsigned int Value );

	void			OptimizerReset( void );
	void			GenerateOptimizerScenes( bool Outline = true, bool Detail = true );
	void			GenerateReportScenes( bool Outline = true, bool Detail = true );
	void			Optimize( void );

	// Messages

	int				GetMessageCount( void ) const;
	int				GetMessageNumber( int Index ) const;
	const char *	GetMessageDescription( int Index ) const;

	const HSView &	GetView( void ) const;	
	const HSImage &	GetImage( void ) const;
	HSImage	&		GetImage( void );
	const HSImage &	GetMask( void ) const;
	HSImage	&		GetMask( void );
	const HSScene & GetSceneOutline( void ) const;
	HSScene	&		GetSceneOutline( void );
	const HSScene &	GetSceneDetail( void ) const;
	HSScene	&		GetSceneDetail( void );

	HSImage	&		CreateMask( void );
	void			RemoveMask( void );
	bool			GetMaskExists( void ) const;

protected:

	HSModel( void* );
	void * _pimpl;
};

// ****************************************************************************
// * Functions prototypes
// ****************************************************************************

// ****************************************************************************
// * Inline functions definitions
// ****************************************************************************

#endif // __HSMODEL_H__

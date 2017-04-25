// ****************************************************************************
//
// HSClassLibrary
//
// ****************************************************************************
//
// File.........: HSLine.h
//
// Description..: This file contains the definition of the HSLine class.
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

#ifndef __HSLINE_H__
#define __HSLINE_H__

// ****************************************************************************
// * Constants
// ****************************************************************************

// ****************************************************************************
// * Types
// ****************************************************************************

class HSCalibration;
class HSImage;
class HSScene;
class HSPoint;
class HSArc;

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

class HSCLL_EXPORT HSLine 
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

public:

	// UTILITY

	HSLine( void );
	HSLine( const HSPoint & Start, const HSPoint & End );
	HSLine( const HSPoint & VectorPoint, float Angle );
	HSLine( const HSPoint & VectorPoint, float Angle, float StartDelta, float EndDelta );
	HSLine( const HSLine & Object );
 	~HSLine( void );

	HSLine & operator=( const HSLine & Object );

	void			CopyFormatFrom( const HSImage & Object );
	void			CopyFormatFrom( const HSScene & Object );
	void			CopyFormatFrom( const HSPoint & Object );
	void			CopyFormatFrom( const HSLine  & Object );
	void			CopyFormatFrom( const HSArc   & Object );

public:

	// PROPERTY
    const char *	GetName( void ) const;
	void			SetName( const char * Value );

	const char *	GetInformation( void ) const;
	void			SetInformation( const char * Value );

    long			GetModifyCount( void ) const;

    const HSPoint &	GetStartPoint( void ) const;
    HSPoint &		GetStartPoint( void );
    const HSPoint &	GetEndPoint( void ) const;
    HSPoint &		GetEndPoint( void );
    const HSPoint &	GetVectorPoint( void ) const;
    HSPoint &		GetVectorPoint( void );

    float			GetAngle( void ) const;
    void			SetAngle( float Value );
	float			GetStartDelta( void ) const;
	void			SetStartDelta( float Value );
	float			GetEndDelta( void ) const;
	void			SetEndDelta( float Value );

	void			GetBoundary( float & Left, float & Right, float & Top, float & Bottom ) const;

    hsUnitsLength	GetUnitsLength( void ) const;
    void			SetUnitsLength( hsUnitsLength Value );
    hsUnitsOrientation GetUnitsOrientation( void ) const;
    void			SetUnitsOrientation( hsUnitsOrientation Value );

    const HSCalibration & GetCalibration( void ) const;
    HSCalibration & GetCalibration( void );
    void			SetCalibration( const HSCalibration & Calibration );

	bool			GetCalibrated( void ) const;
	void			SetCalibrated( const bool Value );

public:

	// METHODS

    void			Load( const char * FileName );
    void			Save( const char * FileName );

	HSLine			Perpendicular( const HSPoint & Point );

	HSPoint			NearestPoint( const HSPoint & Point, bool ExtrapolateThis = false );
	HSPoint			NearestPoint( const HSLine & Line, 
								  bool ExtrapolateThis = false, 
								  bool ExtrapolateLine = false,
								  bool * Intersected = NULL );
	HSPoint			NearestPoint( const HSArc & Arc, 
								  bool ExtrapolateThis = false, 
								  bool ExtrapolateArc = false,
								  bool * Intersected = NULL );

protected:

	HSLine( void * );
	void * _pimpl;
};

#endif // __HSLINE_H__

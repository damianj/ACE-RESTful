// ****************************************************************************
//
// HSClassLibrary
//
// ****************************************************************************
//
// File.........: HSPoint.h
//
// Description..: This file contains the definition of the HSPoint class.
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

#ifndef __HSPOINT_H__
#define __HSPOINT_H__

// ****************************************************************************
// * Constants
// ****************************************************************************

// ****************************************************************************
// * Types
// ****************************************************************************

class HSCalibration;
class HSImage;
class HSScene;
class HSLine;
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

class HSCLL_EXPORT HSPoint
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

	HSPoint( void );
	HSPoint( float X, float Y, bool Calibrated = false );
	HSPoint( float X, float Y, bool Calibrated, hsUnitsLength UnitsLength );
	HSPoint( float X, float Y, bool Calibrated, hsUnitsLength UnitsLength, const HSCalibration & Calibration );
	HSPoint( const HSPoint & Object );
 	~HSPoint( void );

	HSPoint & operator=( const HSPoint & Object );
	bool     operator==( HSPoint & Object );

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

    float			GetImageX( void ) const;
    void			SetImageX( float Value );
    float			GetImageY( void ) const;
    void			SetImageY( float Value );
    float			GetWorldX( void ) const;
    void			SetWorldX( float Value );
    float			GetWorldY( void ) const;
    void			SetWorldY( float Value );
    hsUnitsLength	GetUnitsLength( void ) const;
    void			SetUnitsLength( hsUnitsLength Value );
    hsUnitsOrientation GetUnitsOrientation( void ) const;
    void			SetUnitsOrientation( hsUnitsOrientation Value );

    const HSCalibration & GetCalibration( void )const;
    HSCalibration & GetCalibration( void );
    void			SetCalibration( const HSCalibration & Calibration );

	bool			GetCalibrated( void ) const;
	void			SetCalibrated( const bool Value );

public:

	// METHODS

    void			Load( const char * FileName );
    void			Save( const char * FileName );

	float			Angle( const HSPoint & Point );
	float			Distance( const HSPoint & Point );

protected:

	HSPoint( void * );
	void * _pimpl;
};

#endif // __HSPOINT_H__

// ****************************************************************************
//
// HSClassLibrary
//
// ****************************************************************************
//
// File.........: HSCalibration.h
//
// Description..: This file contains the definition of the HSCalibration class.
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

#ifndef __HSCALIBRATION_H__
#define __HSCALIBRATION_H__

// ****************************************************************************
// * Constants
// ****************************************************************************

// ****************************************************************************
// * Types
// ****************************************************************************

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

class HSCLL_EXPORT HSCalibration
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

	enum hsCoordinateSystem
	{
		hsCoordinateSystemImage = 0,
		hsCoordinateSystemWorld = 1,
		hsCoordinateSystemObject = 2,
		hsCoordinateSystemTool = 3
	};

	enum hsCoordinateSystemType
	{
		hsRightHanded = 0,
		hsLeftHanded = 1
	};

	enum hsCalibrationType
	{
		hsCalibrationUndefined = 0,
		hsCalibrationXYScale = 1,
		hsCalibrationPerspectiveOld = 2,
		hsCalibrationDistortionLUT = 3,
		hsCalibrationDistortionModel = 4,
		hsCalibrationPerspective = 5,
		hsCalibrationAuto = 6,
		hsCalibrationAffine = 7,
		hsCalibrationXYZ = 9
	};

	enum hsCalibrationState
	{
		hsCalibrationReady = 1,
		hsCalibrationSolveFailed = 2,
		hsCalibrationParameterChanged = 256,
		hsCalibrationPointChanged = 512
	};

public:

	// UTILITY

	HSCalibration( hsCalibrationType CalibrationType = hsCalibrationAuto );
	HSCalibration( const HSCalibration & Object );
	virtual ~HSCalibration( void );

	HSCalibration & operator=( const HSCalibration & Object );

public:

	// PROPERTY

	const char *	GetInformation( void ) const;
	void			SetInformation( const char * Value );

    hsCalibrationType GetType( void ) const;
    hsCalibrationState GetState( void ) const;

    hsUnitsLength	GetUnitsLength( void ) const;
    void			SetUnitsLength ( hsUnitsLength Value );

    int				GetImageWidth( void ) const;
    void			SetImageWidth( int Value );
    int				GetImageHeight( void ) const;
    void			SetImageHeight( int Value );

    float			GetAveragePixelSize( void ) const;
    float			GetAveragePixelWidth( void ) const;
    float			GetAveragePixelHeight( void ) const;

    int				GetParameterCount( void ) const;
    void			SetParameterCount( int Value );

    hsCoordinateSystemType GetWorldCoordinateSystemType( void ) const;
    void SetWorldCoordinateSystemType( hsCoordinateSystemType type );

public:

	// METHODS

    float			GetParameter( int Index ) const;
    void			SetParameter( int Index, float Value );
    const char *	GetParameterName( int Index ) const;
    const char *	GetParameterDescription( int Index ) const;

    void			ImageToWorld( float & X, float & Y ) const;
    void			WorldToImage( float & X, float & Y ) const;
    void			ImageToWorld( float * X, float * Y, unsigned int Size ) const;
    void			WorldToImage( float * X, float * Y, unsigned int Size ) const;

    void			Solve( void );

    virtual void	Load( const char * FileName );
    virtual void	Save( const char * FileName );

	virtual int		ExchangeProp( const char *, 
								  unsigned short,
								  void *, 
								  const void * ) { return ( false ); }

protected:

	HSCalibration( void * );
	void * _pimpl;
};

#endif // __HSCALIBRATION_H__

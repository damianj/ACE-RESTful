// ****************************************************************************
//
// HSClassLibrary
//
// ****************************************************************************
//
// File.........: HSCalibrationColor.h
//
// Description..: This file contains the definition of the HSCalibrationColor class.
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

#ifndef __HSCALIBRATIONCOLOR_H__
#define __HSCALIBRATIONCOLOR_H__

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

class HSCLL_EXPORT HSCalibrationColor
{
public:

	// ENUMERATIONS

	enum hsCalibrationColorType
	{
		hsCalibrationColorUndefined = 0,
		hsCalibrationColorFilterCharacteristicsModel = 1
	};

	enum hsColorSpace
	{
		hsColorSpaceUnknown = 0,
		hsColorSpaceCIERGB = 1,
		hsColorSpaceSRGB = 2
	};

	enum hsTargetType
	{
		hsTargetTypeUnknown = 0,
		hsTargetTypeMacbeth = 1
	};

public:

	// UTILITY

	HSCalibrationColor( hsCalibrationColorType CalibrationColorType = hsCalibrationColorUndefined );
	HSCalibrationColor( const HSCalibrationColor & Object );
	virtual ~HSCalibrationColor( void );

	HSCalibrationColor & operator=( const HSCalibrationColor & Object );

public:

	// PROPERTY

	const char *	GetInformation( void ) const;
	void			SetInformation( const char * Value );

    hsCalibrationColorType GetType( void ) const;

    int				GetParameterCount( void ) const;
    void			SetParameterCount( int Value );

    int				GetArrayCount( void ) const;
    void			SetArrayCount( int Value );

    int				GetArraySize( int ArrayIndex ) const;
    void			SetArraySize( int ArrayIndex, int Value );

    double			GetArrayValue( int ArrayIndex, int Index ) const;
    void			SetArrayValue( int ArrayIndex, int Index, double Value );

	hsTargetType	GetTargetType();
	void			SetTargetType( hsTargetType TargetType );

	hsColorSpace	GetColorSpace();
	void			SetColorSpace( hsColorSpace ColorSpace );

	int				GetTargetSampleCount( hsTargetType TargetType );

	void			SetTargetSample( int SampleIndex, int RValue, int GValue, int BValue );


public:

	// METHODS

    double			GetParameter( int Index ) const;
    void			SetParameter( int Index, double Value );
    const char *	GetParameterName( int Index ) const;
    const char *	GetParameterDescription( int Index ) const;

    void			Solve( void );

    virtual void	Load( const char * FileName );
    virtual void	Save( const char * FileName );

	virtual int		ExchangeProp( const char *, 
								  unsigned short,
								  void *, 
								  const void * ) { return ( false ); }

protected:

	HSCalibrationColor( void * );
	void * _pimpl;
};

#endif // __HSCALIBRATIONCOLOR_H__

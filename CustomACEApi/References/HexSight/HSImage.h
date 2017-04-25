// ****************************************************************************
//
// HSClassLibrary
//
// ****************************************************************************
//
// File.........: HSImage.h
//
// Description..: This file contains the definition of the HSImage class.
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

#ifndef __HSIMAGE_H__
#define __HSIMAGE_H__

// ****************************************************************************
// * Constants
// ****************************************************************************

// ****************************************************************************
// * Types
// ****************************************************************************

class HSCalibration;
class HSCalibrationColor;

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

class HSCLL_EXPORT HSImage
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

	enum hsCoordinateSystemType
	{
		hsRightHanded = 0,
		hsLeftHanded = 1
	};

	enum hsArcType
	{
		hsConvexOutside = 0,
		hsConcaveOutside = 1,
		hsConvexInside = 2,
		hsConcaveInside = 3
	};

	enum hsImageType
	{
		hsImageReserved = 0,
		hsImage8bppGreyScale = 1,
		hsImage32bppRgb = 10,
		hsImage16bppGreyScale = 20,
	};

	enum hsFileFormat
	{
		hsFileFormatAutomatic = 0,
		hsFileFormatHexSightImage = 1,
		hsFileFormatBitmap = 2,
		hsFileFormatTiff = 3,
		hsFileFormatDXF = 4,
		hsFileFormatPNG = 5,
		hsFileFormatJPEG = 6
	};

	enum hsSubSamplingMode
	{
		hsSubSamplingInteger = 0,
		hsSubSamplingFloat = 1
	};

public:

	// UTILITY

	HSImage( void );
	HSImage( int Width, int Height, hsImageType ImageType = hsImage8bppGreyScale, void * RawImagePointer = NULL );
	HSImage( int Width, int Height, float SubSamplingFactor, hsImageType ImageType = hsImage8bppGreyScale );
	HSImage( const HSImage & Object );
 	~HSImage( void );

	HSImage & operator=( const HSImage & Object );
	bool     operator==( const HSImage & Object ) const;

public:

	// PROPERTY

    const char *	GetName( void ) const;
	void			SetName( const char * Value );

	const char *	GetInformation( void ) const;
	void			SetInformation( const char * Value );

	hsImageType		GetType( void ) const;
	void			SetType( hsImageType ImageType );

    long			GetModifyCount( void ) const;
    
    unsigned __int64	GetTimeStamp( void ) const;
    void				SetTimeStamp( unsigned __int64 Value );
    __int64				GetEncoderPosition( void ) const;
    void				SetEncoderPosition( __int64 Value );

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
    void			SetSubSamplingFactor( float Value );

	hsCoordinateSystemType GetImageCoordinateSystemType( void ) const;
    void			SetImageCoordinateSystemType( hsCoordinateSystemType Value );

    int				GetOriginX( void ) const;
    void			SetOriginX( int Value );
    int				GetOriginY( void ) const;
    void			SetOriginY( int Value );

    hsUnitsLength	GetUnitsLength( void ) const;
    void			SetUnitsLength( hsUnitsLength Value );

    hsUnitsOrientation GetUnitsOrientation( void ) const;
    void			SetUnitsOrientation( hsUnitsOrientation Value );

    float			GetAveragePixelWidth( void ) const;
    float			GetAveragePixelHeight( void ) const;

    const HSCalibration & GetCalibration( void ) const;
    HSCalibration &	GetCalibration( void );
    void			SetCalibration( const HSCalibration & Calibration );

    const HSCalibrationColor * GetCalibrationColor( void ) const;
    HSCalibrationColor * GetCalibrationColor( void );
    void			SetCalibrationColor( const HSCalibrationColor * CalibrationColor );
	bool			IsCalibrationColorValid();
	void			ResetCalibrationColor();

    const void *	GetRawImagePointer( void ) const;
    void *			GetRawImagePointer( void );
	void			SetRawImagePointer( void * RawImagePointer );

    void			SetBackgroundImage( const HSImage & Image );
    void			SetBackgroundColor( long Color );

    bool			GetShapesCalibrated( void ) const;
    void			SetShapesCalibrated( bool Value );

public:

	// METHODS

    void			Load( const char * FileName, hsCoordinateSystemType BMPCoordinateSystemType = hsRightHanded);
    void			Save( const char * FileName );

	hsFileFormat	GetFileFormat( void ) const;
	void			SetFileFormat( hsFileFormat Value );

    void			Modify( void );

    unsigned int	GetPixel( int X, int Y ) const;
    void			SetPixel( int X, int Y, unsigned int Value );

    void			ImageToWorld( float & X, float & Y ) const;
    void			WorldToImage( float & X, float & Y ) const;

    void			Render( void );
    void			StartShape( float X, float Y, long Color );
    void			LineTo( float XEnd, float YEnd );
    void			ArcTo( float XEnd, float YEnd, float Radius, hsArcType ArcType );
    void			ResetShapes( void );
    void			ApplyTransform( float X, float Y, float Rotation, float Scale );
    void			AddCircleShape( float X, float Y, float Radius, long Color );
    void			AddRectangleShape( float X1, float Y1, float X2, float Y2, long Color );

	float			ComputeArea( int Index );
	void			SetColor( int Index, long Color );
	void			SetFirst( int Index );
	void			SetForcePositiveSign( bool ForcePositiveSign );
	void			ComputeShapes( void );

	void			SubSampleFrom( const HSImage & Image, float SubSamplingFactor, hsSubSamplingMode Mode = hsSubSamplingInteger );

	void			Flip( void );
	void			Mirror( void );

protected:

	HSImage( void * );
	void * _pimpl;
};

#endif // __HSIMAGE_H__

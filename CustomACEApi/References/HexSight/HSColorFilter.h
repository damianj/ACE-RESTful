// ****************************************************************************
//
// HSColorFilter																 
//
// ****************************************************************************
//
// File.........: HSColorFilter.h
//
// Description..: This file contains the definition of the HSColorFilter class.
//
// Platforms....: WIN32
//
// ****************************************************************************
//
//                Copyright (C) 2007 LMI Technologies
//                All rights reserved
//
// ****************************************************************************
//
// $History:$
//
// ****************************************************************************

#ifndef __HSCOLORFILTER_H__
#define __HSCOLORFILTER_H__


// ****************************************************************************
// * Constants
// ****************************************************************************

// ****************************************************************************
// * Types
// ****************************************************************************

class HSImage;

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
// HSCOLORFILTER_COMPILATION_DLL <Reserved>

#ifdef WIN32
	#ifdef HSCOLORFILTER_COMPILATION_DLL
		#define HSCOLORFILTER_EXPORT __declspec(dllexport)
	#else
		#ifdef HSSTATICLIBRARY
			#define HSCOLORFILTER_EXPORT
		#else
			#define HSCOLORFILTER_EXPORT __declspec(dllimport)
		#endif
	#endif
#else
	#define HSCOLORFILTER_EXPORT
#endif

#define hsMaximumName 2048


// ****************************************************************************
// * Class definition
// ****************************************************************************

class HSCOLORFILTER_EXPORT HSColorFilter
{
public:

	static const int hsMinimumHue;
	static const int hsDefaultHue;
	static const int hsMaximumHue;

	static const int hsMinimumSaturation;
	static const int hsDefaultSaturation;
	static const int hsMaximumSaturation;

	static const int hsMinimumLuminance;
	static const int hsDefaultLuminance;
	static const int hsMaximumLuminance;

	static const int hsMinimumTolerance;
	static const int hsDefaultTolerance;
	static const int hsMaximumTolerance;

public:

	// Utility

					HSColorFilter( void );
					HSColorFilter( const HSColorFilter & Object );

					HSColorFilter & operator=( const HSColorFilter & Object );

public:

	// Property

	const char *	GetName( void ) const;
	void			SetName( const char *pValue );

	// Parameters : based on HSL representation ( Hue, Saturation, Luminance )

	int				GetHueValue( void ) const;
	void			SetHueValue( int Value );
	int				GetHueTolerance( void ) const;
	void			SetHueTolerance( int Value );

	int				GetSaturationValue( void ) const;
	void			SetSaturationValue( int Value );
	int				GetSaturationTolerance( void ) const;
	void			SetSaturationTolerance( int Value );

	int				GetLuminanceValue( void ) const;
	void			SetLuminanceValue( int Value );
	int				GetLuminanceTolerance( void ) const;
	void			SetLuminanceTolerance( int Value );

	int				GetRedValue( void ) const;
	void			SetRedValue( int Value );
	int				GetGreenValue( void ) const;
	void			SetGreenValue( int Value );
	int				GetBlueValue( void ) const;
	void			SetBlueValue( int Value );

	void			SetHSL( int Hue, int Saturation, int Luminance );
	void			SetRGB( int Red, int Green, int Blue );
	void			SetFromRegion( HSImage* pColorImage, int pTop, int pBottom, int pLeft, int pRight );

	// Methods

public:

	void			_Load( const char * Prefix, void * = NULL );
	void			_Save( const char * Prefix, void * = NULL );

private:

	int				mHue;
	int				mHueTolerance;
	int				mSaturation;
	int				mSaturationTolerance;
	int				mLuminance;
	int				mLuminanceTolerance;

	char			mName[hsMaximumName];
};

// ****************************************************************************
// * Functions prototypes
// ****************************************************************************

// ****************************************************************************
// * Inline functions definitions
// ****************************************************************************

#endif // __HSCOLORFILTER_H__

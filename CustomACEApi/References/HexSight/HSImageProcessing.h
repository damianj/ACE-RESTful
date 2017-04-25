// ****************************************************************************
//
// HSImageProcessing																 
//
// ****************************************************************************
//
// File.........: HSImageProcessing.h
//
// Description..: This file contains the definition of the HSImageProcessing class.
//
// Platforms....: All
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

#ifndef __HSIMAGEPROCESSING_H__
#define __HSIMAGEPROCESSING_H__

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

#if _MSC_VER >= 1000
#pragma once
#endif 

// This is for Library export/import.  
// No define needed when using as a dynamic library
// HSSTATICLIBRARY defined at compilation when library used as a static library
// HSIMAGEPROCESSING_COMPILATION_DLL <Reserved>

#ifdef WIN32
	#ifdef HSIMAGEPROCESSING_COMPILATION_DLL
		#define HSIMAGEPROCESSING_EXPORT __declspec(dllexport)
	#else
		#ifdef HSSTATICLIBRARY
			#define HSIMAGEPROCESSING_EXPORT
		#else
			#define HSIMAGEPROCESSING_EXPORT __declspec(dllimport)
		#endif
	#endif
#else
	#define HSIMAGEPROCESSING_EXPORT
#endif

// ****************************************************************************
// * Class definition
// ****************************************************************************

class HSIMAGEPROCESSING_EXPORT HSImageProcessing
{
public:

	static const long hsArithmeticConstantDefault;
	static const long hsArithmeticConstantMin;
	static const long hsArithmeticConstantMax;
	static const float hsArithmeticScaleDefault;
	static const float hsArithmeticScaleStep;
	static const float hsArithmeticScaleMin;
	static const float hsArithmeticScaleMax;
	static const long hsAssignmentConstantDefault;
	static const long hsAssignmentConstantMin;
	static const long hsAssignmentConstantMax;
	static const long hsAssignmentWidthDefault;
	static const long hsAssignmentWidthMin;
	static const long hsAssignmentWidthMax;
	static const long hsAssignmentHeightDefault;
	static const long hsAssignmentHeightMin;
	static const long hsAssignmentHeightMax;
	static const long hsConversionLowDefault;
	static const long hsConversionLowMin;
	static const long hsConversionLowMax;
	static const long hsConversionHighDefault;
	static const long hsConversionHighMin;
	static const long hsConversionHighMax;
	static const float hsFilteringScaleDefault;
	static const float hsFilteringScaleStep;
	static const float hsFilteringScaleMin;
	static const float hsFilteringScaleMax;
	static const int hsFilteringCustomKernelHeightDefault;
	static const int hsFilteringCustomKernelHeightMin;
	static const int hsFilteringCustomKernelHeightMax;
	static const int hsFilteringCustomKernelWidthDefault;
	static const int hsFilteringCustomKernelWidthMin;
	static const int hsFilteringCustomKernelWidthMax;
	static const int hsFilteringCustomKernelValueDefault;
	static const int hsFilteringCustomKernelValueMin;
	static const int hsFilteringCustomKernelValueMax;
	static const long hsLogicalConstantDefault;
	static const long hsLogicalConstantMin;
	static const long hsLogicalConstantMax;
	static const long hsHistogramThresholdMin;
	static const long hsHistogramThresholdMax;

	// ENUMERATIONS

	enum hsImageProcessingOperation
	{
		hsArithmeticAddition			= 0,
		hsArithmeticSubtraction			= 1,
		hsArithmeticMultiplication		= 2,
		hsArithmeticDivision			= 3,
		hsArithmeticLightest			= 4,
		hsArithmeticDarkest				= 5,
		hsAssignmentInitialization		= 6,
		hsAssignmentCopy				= 7,
		hsAssignmentInversion			= 8,
		hsLogicalAnd					= 9,
		hsLogicalNAnd					= 10,
		hsLogicalOr						= 11,
		hsLogicalXOr					= 12,
		hsLogicalNOr					= 13,
		hsFilteringCustom				= 14,
		hsFilteringAverage				= 15,
		hsFilteringLaplacian			= 16,
		hsFilteringHorizontalSobel		= 17,
		hsFilteringVerticalSobel		= 18,
		hsFilteringSharpen				= 19,
		hsFilteringSharpenLow			= 20,
		hsFilteringHorizontalPrewitt	= 21,
		hsFilteringVerticalPrewitt		= 22,
		hsFilteringGaussian				= 23,
		hsFilteringHighPass				= 24,
		hsFilteringMedian				= 25,
		hsMorphologicalDilate			= 26,
		hsMorphologicalErode			= 27,
		hsMorphologicalClose			= 28,
		hsMorphologicalOpen				= 29,
		hsHistogramEqualization			= 30,
		hsHistogramStretching			= 31,
		hsHistogramLightThreshold		= 32,
		hsHistogramDarkThreshold		= 33,
		hsTransformFFT					= 34,
		hsTransformDCT					= 35,
		hsConversionIntensity			= 36,
		hsConversionIntensityRange		= 37
	};

	enum hsImageProcessingType
	{
		hsType8Bits			= 1,
		hsType16Bits		= 10,
		hsType32Bits		= 7
	};

	enum hsImageProcessingClippingMode
	{
		hsClippingNormal	= 0,
		hsClippingAbsolute	= 1
	};

	enum hsImageProcessingDisplayMode
	{
		hsInputImage	= 0,
		hsOperandImage	= 1,
		hsOutputImage	= 2
	};

	enum hsImageProcessingTransformFlags
	{
		hsTransformFlag2DLinear		 = 0,
		hsTransformFlag2DLogarithmic = 1,
		hsTransformFlag1DLinear		 = 2,
		hsTransformFlagHistogram	 = 3
	};

	enum hsKernelSize
	{
		hsKernelSize3X3	= 3,
		hsKernelSize5X5	= 5,
		hsKernelSize7X7	= 7
	};

	enum hsProcessingFormat
	{
		hsProcessingFormatNative = 0,
		hsProcessingFormatGreyScale = 1
	};

public:

	// UTILITY

					HSImageProcessing( void );
					HSImageProcessing( const HSImageProcessing & Object );
    virtual		   ~HSImageProcessing( void );

					HSImageProcessing & operator=( const HSImageProcessing & Object );

	virtual int		ExchangeProp( 
						const char * ProName, 
						unsigned short PropType,
						void * PropPointer, 
						const void * PropDefault = NULL );

public:

	// Get/Set Database Handle

    unsigned int	GetDatabase( void ) const;
    void			SetDatabase( unsigned int Handle, unsigned long Password = NULL );

	// General ///////////////////////////////////////////////////////////////////

	// Attributes //

    const char *	GetInputImage( void ) const;
    void			SetInputImage ( const char * Name );
    const char *	GetInputView( void ) const;
    void			SetInputView( const char * Name );

    const char *	GetOperandImage( void ) const;
    void			SetOperandImage ( const char * Name );
    const char *	GetOperandView( void ) const;
    void			SetOperandView( const char * Name );

    const char *	GetOutputImage( void ) const;
    void			SetOutputImage ( const char * Name );
    const char *	GetOutputView( void ) const;
    void			SetOutputView( const char * Name );

    bool			GetOverrideTypeEnabled( void ) const;
    void			SetOverrideTypeEnabled( bool Enabled );
    hsImageProcessingType	GetOverrideType( void ) const;
    void			SetOverrideType( hsImageProcessingType Value );

	// Processing ////////////////////////////////////////////////////////////////

	// Attributes //

	hsImageProcessingClippingMode	GetArithmeticClippingMode() const;
	void			SetArithmeticClippingMode( hsImageProcessingClippingMode Value );
	long			GetArithmeticConstant() const;
	void			SetArithmeticConstant( long Value );
	float			GetArithmeticScale() const;
	void			SetArithmeticScale( float Value );

	long			GetAssignmentConstant() const;
	void			SetAssignmentConstant( long Value );
	int				GetAssignmentHeight() const;
	void			SetAssignmentHeight( int Value );
	int				GetAssignmentWidth() const;
	void			SetAssignmentWidth( int Value );

	int				GetConversionLow() const;
	void			SetConversionLow( int Value );
	int				GetConversionHigh() const;
	void			SetConversionHigh( int Value );

	hsImageProcessingClippingMode	GetFilteringClippingMode() const;
	void			SetFilteringClippingMode( hsImageProcessingClippingMode Value );
	int				GetFilteringKernelSize() const;
	void			SetFilteringKernelSize( int Value );
	float			GetFilteringScale() const;
	void			SetFilteringScale( float Value );

	int				GetFilteringCustomKernelAnchorX() const;
	void			SetFilteringCustomKernelAnchorX( int Value );
	int				GetFilteringCustomKernelAnchorY() const;
	void			SetFilteringCustomKernelAnchorY( int Value );
	int				GetFilteringCustomKernelHeight() const;
	void			SetFilteringCustomKernelHeight( int Value );
	int				GetFilteringCustomKernelValue( int Column, int Line ) const;
	void			SetFilteringCustomKernelValue( int Column, int Line, int Value );
	int				GetFilteringCustomKernelWidth() const;
	void			SetFilteringCustomKernelWidth( int Value );

	long			GetLogicalConstant() const;
	void			SetLogicalConstant( long Value );

	long			GetHistogramThreshold() const;
	void			SetHistogramThreshold( long Value );

	int				GetMorphologicalNeighborhoodSize() const;
	void			SetMorphologicalNeighborhoodSize( int Value );

    hsImageProcessingOperation	GetOperation( void ) const;
    void			SetOperation( hsImageProcessingOperation Value );

	hsImageProcessingTransformFlags	GetTransformFlags() const;
	void			SetTransformFlags( hsImageProcessingTransformFlags Value );

	bool			GetProcessingFormatEnabled( hsProcessingFormat pFormat ) const;
	hsProcessingFormat GetProcessingFormat( void ) const;
	void			SetProcessingFormat( hsProcessingFormat Value );

	// Results ///////////////////////////////////////////////////////////////////

	// Attributes //

    float			GetElapsedTime( void ) const;

	hsImageProcessingOperation	GetLastOperation( void ) const;
	hsImageProcessingType	GetLastOutputType( void ) const;

	// Misc //////////////////////////////////////////////////////////////////////

	// Methods //

    float			Execute( void );

	void			SetDebugParameter( int Index, const void * Value, unsigned short Flag = NULL );
	void			GetDebugParameter( int Index, void * Value, unsigned short * Flag = NULL ) const;
	
	void			Load( const char * FileName );
	void			Load( const char * FileName, int StartLine );
	void			Save( const char * FileName );
	void			Save( const char * FileName, bool Append, const char * Prefix );
	void			ResetState( void );

protected :

	void			_Load( const char * Prefix, void * = NULL );
	void			_Save( const char * Prefix, void * = NULL );

private:

	void * _pimpl;
};


// ****************************************************************************
// * Functions prototypes
// ****************************************************************************

// ****************************************************************************
// * Inline functions definitions
// ****************************************************************************

#endif // __HSIMAGEPROCESSING_H__

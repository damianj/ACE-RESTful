// ****************************************************************************
//
// HSClassLibrary
//
// ****************************************************************************
//
// File.........: HSView.h
//
// Description..: This file contains the definition of the HSView class.
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

#ifndef __HSVIEW_H__
#define __HSVIEW_H__

// ****************************************************************************
// * Constants
// ****************************************************************************

// ****************************************************************************
// * Types
// ****************************************************************************

class HSImage;
class HSScene;
class HSPoint;
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

class HSCLL_EXPORT HSView
{
public:

	// ENUMERATIONS

	enum hsSceneType
	{
		hsSceneReserved = 0,
		hsSceneStandard = 4,
		hsSceneModel = 5,
		hsSceneModelSource = 6,
		hsSceneInstances = 7
	};

	enum hsImageType
	{
		hsImageReserved = 0,
		hsImage8bppGreyScale = 1,
		hsImage32bppRgb = 10
	};

public:

	// UTILITY

	HSView( void );
	HSView( const HSView & Object );
 	~HSView( void );

	HSView & operator=( const HSView & Object );

public:

	// PROPERTY

    const char *	GetName( void ) const;
	void			SetName( const char * Value );

	const char *	GetInformation( void ) const;
	void			SetInformation( const char * Value );

    long			GetModifyCount( void ) const;
       
	// ** Image ** //
    int				GetImageCount( void ) const;
    const HSImage *	GetImage( const char * ImageName ) const;
    HSImage *		GetImage( const char * ImageName );
	HSImage *		AddImage( const char * ImageName );
	HSImage *		AddImage( const char * ImageName, hsImageType ImageType );
    void			RemoveImage( const char * ImageName );
	void			RenameImage( const char * ImageName, const char * NewImageName );
	void			AttachImage( const HSImage & Image );
	const char *	GetImageName( int Index ) const;
	int				GetImageIndex( const char * ImageName ) const;
	bool			GetImageExists( const char * ImageName ) const;

	// ** Scene ** //
    int				GetSceneCount( void ) const;
    const HSScene *	GetScene( const char * SceneName ) const;
    HSScene *		GetScene( const char * SceneName );
	HSScene *		AddScene( const char * SceneName );
	HSScene *		AddScene( const char * SceneName, hsSceneType SceneType );
    void			RemoveScene( const char * SceneName );
	void			RenameScene( const char * SceneName, const char * NewSceneName );
	void			AttachScene( const HSScene & Scene );
	const char *	GetSceneName( int Index ) const;
	int				GetSceneIndex( const char * SceneName ) const;
	bool			GetSceneExists( const char * SceneName ) const;

	// ** Point ** //
    int				GetPointCount( void ) const;
    const HSPoint *	GetPoint( const char * PointName ) const;
    HSPoint *		GetPoint( const char * PointName );
	HSPoint *		AddPoint( const char * PointName );
    void			RemovePoint( const char * PointName );
	void			RenamePoint( const char * PointName, const char * NewPointName );
	void			AttachPoint( const HSPoint & Point );
	const char *	GetPointName( int Index ) const;
	int				GetPointIndex( const char * PointName ) const;
	bool			GetPointExists( const char * PointName ) const;

	// ** Line ** //
    int				GetLineCount( void ) const;
    const HSLine *	GetLine( const char * LineName ) const;
    HSLine *		GetLine( const char * LineName );
	HSLine *		AddLine( const char * LineName );
    void			RemoveLine( const char * LineName );
	void			RenameLine( const char * LineName, const char * NewLineName );
	void			AttachLine( const HSLine & Line );
	const char *	GetLineName( int Index ) const;
	int				GetLineIndex( const char * LineName ) const;
	bool			GetLineExists( const char * LineName ) const;

	// ** Arc ** //
    int				GetArcCount( void ) const;
    const HSArc *	GetArc( const char * ArcName ) const;
    HSArc *			GetArc( const char * ArcName );
	HSArc *			AddArc( const char * ArcName );
    void			RemoveArc( const char * ArcName );
	void			RenameArc( const char * ArcName, const char * NewArcName );
	void			AttachArc( const HSArc & Arc );
	const char *	GetArcName( int Index ) const;
	int				GetArcIndex( const char * ArcName ) const;
	bool			GetArcExists( const char * ArcName ) const;

public:

	// METHODS

    void			Load( const char * FileName );
    void			Save( const char * FileName );

    void			Modify( void );

    void			Reset( void );

protected:

	HSView( void * );
	void * _pimpl;
};

#endif // __HSVIEW_H__

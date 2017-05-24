
//////////////////////////////////////////////////////////////////////////
/// Includes
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Engine.h"

#include "RenderContext.h"
#include "SoundSystem.h"


//////////////////////////////////////////////////////////////////////////
/// CEngine
//////////////////////////////////////////////////////////////////////////

CEngine::CEngine() :
    myRenderContext( nullptr ),
    mySoundSystem( nullptr ),
    myInitialised( false )
{
}

//////////////////////////////////////////////////////////////////////////

CEngine::~CEngine()
{
    delete myRenderContext;
    delete mySoundSystem;
    myInitialised = false;
}

//////////////////////////////////////////////////////////////////////////

bool CEngine::Initialise( HWND aWindowHandle, int aWindowWidth, int aWindowHeight )
{
    if( myInitialised )
    {
        return true;
    }

    // create the directx renderer
    myRenderContext = new CRenderContext();
    if( !myRenderContext->Initialize(aWindowHandle, aWindowWidth, aWindowHeight) )
    {
        return false;
    }

    // create the sound system
    mySoundSystem = new CSoundSystem();
    if( !mySoundSystem->Initialise() )
    {
        return false;
    }

    myInitialised = true;
    return true;
}

//////////////////////////////////////////////////////////////////////////

void CEngine::Update()
{
    if( !myInitialised )
    {
        return;
    }

    Render();
}

//////////////////////////////////////////////////////////////////////////

bool CEngine::IsInitialized() const
{
    return myInitialised;
}

//////////////////////////////////////////////////////////////////////////

void CEngine::Render()
{
    if( !myInitialised )
    {
        return;
    }

    myRenderContext->Clear();
}

//////////////////////////////////////////////////////////////////////////
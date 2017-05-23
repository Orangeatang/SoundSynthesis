
//////////////////////////////////////////////////////////////////////////
/// Includes
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Engine.h"
#include "RenderContext.h"


//////////////////////////////////////////////////////////////////////////
/// CEngine
//////////////////////////////////////////////////////////////////////////

CEngine::CEngine() :
    m_renderContext( nullptr ),
    m_initialised( false )
{
}

//////////////////////////////////////////////////////////////////////////

CEngine::~CEngine()
{
}

//////////////////////////////////////////////////////////////////////////

bool CEngine::Initialize( HWND aWindowHandle, int aWindowWidth, int aWindowHeight )
{
    if( m_initialised )
    {
        return true;
    }

    // create the directx renderer
    m_renderContext = new CRenderContext();
    if( !m_renderContext->Initialize(aWindowHandle, aWindowWidth, aWindowHeight) )
    {
        return false;
    }

    m_initialised = true;
    return true;
}

//////////////////////////////////////////////////////////////////////////

void CEngine::Update()
{
    if( !m_initialised )
    {
        return;
    }
}

//////////////////////////////////////////////////////////////////////////

bool CEngine::IsInitialized() const
{
    return m_initialised;
}

//////////////////////////////////////////////////////////////////////////

void CEngine::Render()
{
    if( !m_initialised )
    {
        return;
    }
}

//////////////////////////////////////////////////////////////////////////
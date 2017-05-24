
//////////////////////////////////////////////////////////////////////////
/// Includes
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RenderContext.h"


//////////////////////////////////////////////////////////////////////////
/// CRenderContext
//////////////////////////////////////////////////////////////////////////

CRenderContext::CRenderContext() :
    myDevice( nullptr ),
    myDeviceContext( nullptr ),
    mySwapChain( nullptr ),
    myRenderTarget( nullptr ),
    myInitialized( false )
{
}

//////////////////////////////////////////////////////////////////////////

CRenderContext::~CRenderContext()
{
    if( myInitialized )
    {
        myRenderTarget->Release();
        mySwapChain->Release();
        myDeviceContext->Release();
        myDevice->Release();
    }
}

//////////////////////////////////////////////////////////////////////////

bool CRenderContext::Initialize( HWND aWindowHandle, int aWindowWidth, int aWindowHeight )
{
    if( myInitialized )
    {
        return true;
    }

    // create a structure to hold information about the swap chain
    DXGI_SWAP_CHAIN_DESC swapChainDescription;
    ZeroMemory( &swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC) );

    HRESULT result = S_OK;

    // fill in the swap chain structure
    swapChainDescription.BufferCount        = 2;
    swapChainDescription.BufferDesc.Format  = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDescription.BufferDesc.Width   = aWindowWidth;
    swapChainDescription.BufferDesc.Height  = aWindowHeight;
    swapChainDescription.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDescription.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDescription.BufferUsage        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDescription.OutputWindow       = aWindowHandle;
    swapChainDescription.SampleDesc.Count   = 8;
    swapChainDescription.SampleDesc.Quality = 0;
    swapChainDescription.Windowed           = TRUE;
    swapChainDescription.Flags              = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    // create the context
    result = D3D11CreateDeviceAndSwapChain(
        NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        0,
        NULL,
        NULL,
        D3D11_SDK_VERSION,
        &swapChainDescription,
        &mySwapChain,
        &myDevice,
        NULL,
        &myDeviceContext
    );

    // bail out if we are unable to initialize the directx context
    if( result != S_OK )
    {
        return false;
    }

    // get the address of the back buffer and use that as the render target
    ID3D11Texture2D* backBuffer = nullptr;
    result = mySwapChain->GetBuffer( 0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer );
    if( result != S_OK )
    {
        return false;
    }

    // use the back-buffer address to create the render target
    result = myDevice->CreateRenderTargetView( backBuffer, NULL, &myRenderTarget );
    backBuffer->Release();
    if( result != S_OK )
    {
        return false;
    }

    // set the render target as the back buffer
    myDeviceContext->OMSetRenderTargets( 1, &myRenderTarget, nullptr );

    // set the viewport
    D3D11_VIEWPORT viewport;
    ZeroMemory( &viewport, sizeof(D3D11_VIEWPORT) );

    viewport.TopLeftX   = 0;
    viewport.TopLeftY   = 0;
    viewport.Width      = (FLOAT)aWindowWidth;
    viewport.Height     = (FLOAT)aWindowHeight;

    myDeviceContext->RSSetViewports( 1, &viewport );

    myInitialized = true;
    return true;
}

//////////////////////////////////////////////////////////////////////////

void CRenderContext::Clear()
{
    static const float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    myDeviceContext->ClearRenderTargetView( myRenderTarget, color);

    mySwapChain->Present(0, 0);
}

//////////////////////////////////////////////////////////////////////////

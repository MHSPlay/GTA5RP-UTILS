#include "src/includes.hpp"

DWORD WINAPI main_func( LPVOID lpParameter ) 
{
    while ( true )
    {
        // init
        bool once = false;
        while ( !once ) {
            DWORD ForegroundWindowProcessID;
            GetWindowThreadProcessId( GetForegroundWindow( ), &ForegroundWindowProcessID );
            if ( utils::GetProcessId( "GTA5.exe" ) == ForegroundWindowProcessID ) {
                utils::window = GetForegroundWindow( );
                once = true;
            }
        }

        features::run( );

    }
}

int main( ) {
    shadowcall< BOOL >( "SetConsoleTitleA", ( utils::randomLowerString( utils::randomInt( 16, 28 ) ).c_str( ) ) );

    // main thread
    CreateThread( NULL, 0, main_func, 0, 0, NULL );

    WNDCLASSEX wc = { sizeof(wc), CS_CLASSDC, ui::WndProc, 0L, 0L, GetModuleHandle( nullptr ), nullptr, nullptr, nullptr, nullptr, "GTA5RP_UTILS", nullptr };
    ::RegisterClassEx( &wc );
    HWND hwnd = ::CreateWindowEx( WS_EX_TOPMOST, wc.lpszClassName, "GTA5RP_UTILS", WS_POPUP, 0, 0, GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ), nullptr, nullptr, wc.hInstance, nullptr );

    SetLayeredWindowAttributes( hwnd, RGB( 0, 0, 0 ), 255, LWA_ALPHA );
    MARGINS margin = { -1 };
    DwmExtendFrameIntoClientArea( hwnd, &margin );

    if ( !ui::CreateDeviceD3D( hwnd ) ) {
        ui::CleanupDeviceD3D( );
        ::UnregisterClass( wc.lpszClassName, wc.hInstance );
        return EXIT_FAILURE;
    }

    ::ShowWindow( hwnd, SW_SHOWDEFAULT );
    ::UpdateWindow( hwnd );

    ImGui::CreateContext( );
    ImGuiIO& io = ImGui::GetIO( ); ( void )io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ui::EmbraceTheDarkness( );
    ImGui_ImplWin32_Init( hwnd );
    ImGui_ImplDX11_Init( g_pd3dDevice, g_pd3dDeviceContext );

    ImFontConfig font_cfg;
    font_cfg.FontDataOwnedByAtlas = false;
    //io.Fonts->AddFontFromMemoryTTF( ( void* )tahoma, sizeof( tahoma ), 16.f, &font_cfg, io.Fonts->GetGlyphRangesCyrillic( ) );
    io.Fonts->AddFontFromMemoryTTF( ( void* )text_04B03, sizeof( text_04B03 ), 14.f, &font_cfg );

    // Initialize notify
    ImGui::MergeIconsWithLatestFont( 16.f, false );

    MSG msg;
    ZeroMemory( &msg, sizeof( msg ) );
    while ( msg.message != WM_QUIT ) {
        if (::PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) ) {
            ::TranslateMessage( &msg );
            ::DispatchMessage( &msg );
            continue;
        }

        if ( GetAsyncKeyState( VK_INSERT ) & 1 ) 
            ui::menuOpened = !ui::menuOpened;

        if ( g_ResizeWidth != 0 && g_ResizeHeight != 0 ) {
            ui::CleanupRenderTarget( );
            g_pSwapChain->ResizeBuffers( 0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0 );
            g_ResizeWidth = g_ResizeHeight = 0;
            ui::CreateRenderTarget( );
        }

        ImGui_ImplDX11_NewFrame( );
        ImGui_ImplWin32_NewFrame( );
        ImGui::NewFrame( );

        if ( ui::menuOpened )
        {
            ui::GUI( );
            SetWindowLong( hwnd, GWL_EXSTYLE, WS_EX_TOPMOST );
        }
        else
            SetWindowLong( hwnd, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED );
        
        ui::notify( );

        ImGui::Render( );
        ImVec4 clear_color = ImVec4( 0.f, 0.f, 0.f, 0.f );
        const float clear_color_with_alpha[ 4 ] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        g_pd3dDeviceContext->OMSetRenderTargets( 1, &g_mainRenderTargetView, nullptr );
        g_pd3dDeviceContext->ClearRenderTargetView( g_mainRenderTargetView, clear_color_with_alpha );
        ImGui_ImplDX11_RenderDrawData( ImGui::GetDrawData( ) );

        // v-sync
        g_pSwapChain->Present( 1, 0 );

        // detach console
        FreeConsole( );
    }

    // cleanup
    ImGui_ImplDX11_Shutdown( );
    ImGui_ImplWin32_Shutdown( );
    ImGui::DestroyContext( );

    ui::CleanupDeviceD3D( );
    ::DestroyWindow( hwnd );
    ::UnregisterClass( wc.lpszClassName, wc.hInstance );

    return EXIT_SUCCESS;
}
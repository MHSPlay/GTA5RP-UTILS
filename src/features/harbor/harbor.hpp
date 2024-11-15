#pragma once

namespace harbor 
{
    auto run( ) -> void
    {
        // activate window
        utils::ActivateWindow( );

        auto getPixel = [ & ]( ) {

            bool isActive = false;
            bool previousState = false;
            while ( true ) 
            {
                bool currentActive = false;
                if ( config::harbor::iKeyMode == 0 ) 
                {
                    currentActive = GetAsyncKeyState( config::harbor::iKey );
                    if ( !currentActive ) 
                        break;
                }
                else 
                {
                    if ( GetAsyncKeyState( config::harbor::iKey ) & 1 ) 
                        isActive = !isActive;
                    
                    currentActive = isActive;
                }

                if ( currentActive != previousState ) 
                {
                    previousState = currentActive;

                    if ( currentActive ) 
                    {
                        ImGui::InsertNotification( { ImGuiToastType_Success, 1500, "Harbor bot started!" } );
                        utils::shadowSendKeyCode( 0x11, true );
                        utils::shadowSendKeyCode( 0x2A, true );
                    }
                    else 
                    {
                        ImGui::InsertNotification( { ImGuiToastType_Info, 1500, "Harbor bot paused!" } );
                        utils::shadowSendKeyCode( 0x11, false );
                        utils::shadowSendKeyCode( 0x2A, false );
                    }
                }

                if ( currentActive && utils::PixelSearch( RGB( 126, 211, 33 ), 963, 494, 1, 1, 0 ) ) 
                    utils::shadowSendKey( VK_E );
                
                // save CPU
                std::this_thread::sleep_for( std::chrono::milliseconds( 25 ) );
            }
        };

        getPixel( );
    }
}
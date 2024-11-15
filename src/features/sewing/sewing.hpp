#pragma once

namespace sewing
{
    auto run( ) -> void
    {
        // activate window
        utils::ActivateWindow( );

        auto getPixel = [ & ]( ) {

            bool isActive = false;
            bool lastState = !isActive;

            while ( true ) {

				if ( config::sewing::iKeyMode == 0 ) {
					if ( !GetAsyncKeyState( config::sewing::iKey ) )
						return;
			    }
				else 
                {
					if ( GetAsyncKeyState( config::sewing::iKey ) & 1 )
                        isActive = !isActive;

					if ( !isActive )
						return;
				}

                if ( isActive != lastState ) {

                    if ( isActive )
                    {
                        ImGui::InsertNotification( { ImGuiToastType_Success, 1500, "Sewing started!" } );
                        utils::shadowSendKey( 0x45 );
                    }
                    else 
                        ImGui::InsertNotification( { ImGuiToastType_Info, 1500, "Sewing paused." } );
                    

                    lastState = isActive;
                }

                if ( isActive ) {
                    utils::shadowSendKey( 0x45 );

                    // W
                    if ( utils::PixelSearch( RGB( 253, 253, 253 ), 944, 560, 1, 1, 0 ) )
                        if ( utils::PixelSearch( RGB( 255, 255, 255 ), 951, 579, 2, 2, 0 ) )
                            utils::shadowSendKeyCode( 0x11 );

                    std::this_thread::sleep_for( std::chrono::milliseconds( config::sewing::iDelay ) );

                    // A
                    if ( utils::PixelSearch( RGB( 255, 255, 255 ), 959, 561, 2, 2, 0 ) )
                        if ( utils::PixelSearch( RGB( 255, 255, 255 ), 959, 575, 2, 2, 0 ) )
                            utils::shadowSendKeyCode( 0x1E );

                    std::this_thread::sleep_for( std::chrono::milliseconds( config::sewing::iDelay2 ) );

                    // S
                    if ( utils::PixelSearch( RGB( 255, 255, 255 ), 959, 561, 2, 2, 0 ) )
                        if ( utils::PixelSearch( RGB( 255, 255, 255 ), 959, 571, 2, 2, 0 ) )
                            if ( utils::PixelSearch( RGB( 255, 255, 255 ), 959, 581, 2, 2, 0 ) )
                                utils::shadowSendKeyCode( 0x1F );

                    std::this_thread::sleep_for( std::chrono::milliseconds( config::sewing::iDelay3 ) );

                    // D
                    if ( utils::PixelSearch( RGB( 255, 255, 255 ), 950, 560, 2, 2, 0 ) )
                        if ( utils::PixelSearch( RGB( 255, 255, 255 ), 950, 575, 2, 2, 0 ) )
                            if ( utils::PixelSearch( RGB( 255, 255, 255 ), 970, 570, 2, 2, 0 ) )
                                utils::shadowSendKeyCode( 0x20 );
                }

                // save CPU
                std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );
            }
        };

        getPixel( );
		
	}
};
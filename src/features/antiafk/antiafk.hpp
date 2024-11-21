#pragma once

namespace antiafk
{

    // rework
	auto run( ) -> void 
	{
        // notify
        ImGui::InsertNotification( { ImGuiToastType_Success, 3000, "Anti-AFK started!" } );

        // activate window
        utils::ActivateWindow( );

        auto antiAFK = [ & ]( ) 
        {
            auto start = std::chrono::steady_clock::now( );
            while ( true ) 
            {
                // activate window
                utils::ActivateWindow( );

                auto now = std::chrono::steady_clock::now( );
                auto elapsed = std::chrono::duration_cast< std::chrono::minutes >( now - start );

                if ( elapsed.count( ) >= 30 ) 
                    break;
                
                utils::shadowSendKeyCode( 0x11, true );
                utils::shadowSendKeyCode( 0x1F, true );

                std::this_thread::sleep_for( std::chrono::seconds( 5 ) );
            }

        };

		auto fortuneWheel = [ & ] ( ) {
       
            // activate window
            utils::ActivateWindow( );

            std::pair< int, int > coordinates[] = {
                    { 1848, 830 }, // 1645, 905 - if we have org // 1848 830 - dont have org
                    { 760, 650 },
                    { 960, 885 },
            };

            while ( true ) 
            {
                // activate window
                utils::ActivateWindow( );

                // open phone
                utils::shadowSendKey( VK_UP );

                std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );

                for (const auto& coord : coordinates) {
                    utils::shadowClickMouseAt( coord.first, coord.second );
                    //std::cout << "[+] clicked at (" << coord.first << ", " << coord.second << ")" << std::endl;
                    std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
                }

                std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );

                for ( int i = 0; i < 2; ++i ) {
                    utils::shadowSendKey( VK_ESCAPE );
                    //std::cout << "[+] ESC pressed." << std::endl;
                }

                std::this_thread::sleep_for( std::chrono::milliseconds( 250 ) );

                utils::shadowSendKey( VK_BACK );
                //std::cout << "[+] BACKSPACE pressed." << std::endl;

                // exit loop
                break;
            }

        };

        // main loop
        antiAFK( );

        if ( config::afk_bypass::bAutoWheel )
            fortuneWheel( );
	}





    auto rework( ) -> void 
    {
        // activate window
        utils::ActivateWindow( );

        // notify
        ImGui::InsertNotification( { ImGuiToastType_Success, 3000, "Anti-AFK started!" } );
    
        auto antiAFK = [ & ]( ) 
        {
            while ( true ) 
            {
                // activate window
                utils::ActivateWindow( );

                // try
                if ( utils::PixelSearch( RGB( 255, 184, 0 ), 1859, 157, 1, 1, 0 ) )
                    break;

                // secret anti-afk system by pressing W and S 
                utils::shadowSendKeyCode( 0x11, true );
                utils::shadowSendKeyCode( 0x1F, true );

                // save CPU
                std::this_thread::sleep_for( std::chrono::milliseconds( 2500 ) );
            }

        };

		auto fortuneWheel = [ & ] ( ) {
       
            // activate window
            utils::ActivateWindow( );

            std::pair< int, int > coordinates[] = {
                    { 1848, 830 }, // 1645, 905 - if we have org // 1848 830 - dont have org
                    { 760, 650 },
                    { 960, 885 },
            };

            while ( true ) 
            {
                // activate window
                utils::ActivateWindow( );

                // open phone
                utils::shadowSendKey( VK_UP );

                std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );

                for (const auto& coord : coordinates) {
                    utils::shadowClickMouseAt( coord.first, coord.second );
                    //std::cout << "[+] clicked at (" << coord.first << ", " << coord.second << ")" << std::endl;
                    std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
                }

                std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );

                for ( int i = 0; i < 2; ++i ) {
                    utils::shadowSendKey( VK_ESCAPE );
                    //std::cout << "[+] ESC pressed." << std::endl;
                }

                std::this_thread::sleep_for( std::chrono::milliseconds( 250 ) );

                utils::shadowSendKey( VK_BACK );
                //std::cout << "[+] BACKSPACE pressed." << std::endl;

                // exit loop
                break;
            }

        };










    
    }















};
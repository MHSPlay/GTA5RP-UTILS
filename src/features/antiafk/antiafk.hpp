#pragma once

namespace antiAFK
{
	auto run( ) -> void 
	{
        // notify
        ImGui::InsertNotification( { ImGuiToastType_Success, 3000, "Anti-AFK started!" } );

        // activate window
        utils::ActivateWindow( );

        restart:
        auto antiAFK = [ & ]( ) {

            auto start = std::chrono::steady_clock::now( );
            while ( true ) {
                // activate window
                utils::ActivateWindow( );

                auto now = std::chrono::steady_clock::now( );
                auto elapsed = std::chrono::duration_cast< std::chrono::minutes >( now - start );

                if ( elapsed.count( ) >= 30 ) {
                    ImGui::InsertNotification( { ImGuiToastType_Info, 3000, "30 minutes have passed." } );
                    break;
                }

                utils::shadowSendKeyCode( 0x11, true );
                utils::shadowSendKeyCode( 0x1F, true );

                std::this_thread::sleep_for( std::chrono::seconds( 5 ) );
            }

        };

		auto fortuneWheel = [ & ] ( int resolution = 1 ) {
       
            // activate window
            utils::ActivateWindow( );

            std::pair< int, int > coordinates[] = {
                    { 1645, 905 },
                    { 760, 650 },
                    { 960, 885 },
            };

            while ( true ) {
                // open phone
                utils::shadowSendKey( VK_UP );
                //std::cout << "[+] open the phone." << std::endl;

                for (const auto& coord : coordinates) {
                    utils::shadowClickMouseAt( coord.first, coord.second );
                    //std::cout << "[+] clicked at (" << coord.first << ", " << coord.second << ")" << std::endl;
                    std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
                }

                std::this_thread::sleep_for( std::chrono::minutes( 1 ) );

                for ( int i = 0; i < 2; ++i ) {
                    utils::shadowSendKey( VK_ESCAPE );
                    //std::cout << "[+] ESC pressed." << std::endl;
                }

                std::this_thread::sleep_for( std::chrono::milliseconds( 250 ) );

                utils::shadowSendKey( VK_BACK );
                //std::cout << "[+] BACKSPACE pressed." << std::endl;
            }

        };

        antiAFK( );
        fortuneWheel( );
        goto restart;

	}

};
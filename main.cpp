#include "src/includes.hpp"

void cursor() 
{
    POINT p; // Структура для хранения координат

    while (true) {
        // Получаем текущие координаты курсора
        if (GetCursorPos(&p)) {
            std::cout << "X: " << p.x << ", Y: " << p.y << std::endl;
        }

        // Задержка, чтобы избежать перегрузки консоли
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        system("cls");
    }
}

int main( ) {
    shadowcall< BOOL >( "SetConsoleTitleA", ( utils::randomLowerString( utils::randomInt( 16, 28 ) ).c_str( ) ) );

    // debug:
    //cursor();

    // important anons:
    std::cout << "[?] !!!USE IT AT YOUR OWN RISK!!! This program is not a cheat or anything else.\nIt just simulates pressing keys on your keyboard and mouse via WinAPI.\nThe author is not responsible for your account!" << std::endl;
    std::this_thread::sleep_for( std::chrono::seconds( 5 ) );

    // auth:







    // core:
    std::cout << "[~] Open GTA5." << std::endl;

    // init
    bool once = false;
    while ( !once ) {
        DWORD ForegroundWindowProcessID;
        GetWindowThreadProcessId( GetForegroundWindow( ), &ForegroundWindowProcessID );
        if ( utils::GetProcessId( "GTA5.exe" ) == ForegroundWindowProcessID ) {
            utils::window = GetForegroundWindow( );

            // clear
            system( "cls" );

            std::cout << "[+] GTA5RP.exe has been found!" << std::endl;
            once = true;
        }
    }

	int selectType = 0;
    int resolution_type = 1;
    std::cout << "Select:\n 1. AntiAFK\n 2. Fast loot\n 3. Harbor bot\n 4. Sewing\ntype: ";
	std::cin >> selectType;

	switch ( selectType ) {

        // antiafk
		case 1: {
            // clear
            system( "cls" );

            // notify
            std::cout << "anti-afk started.\n";

            // sleep
            std::this_thread::sleep_for( std::chrono::seconds( 2 ) );

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
                        std::cout << "[!] 30 minutes have passed." << std::endl;
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
                    std::cout << "[+] open the phone." << std::endl;

                    for (const auto& coord : coordinates) {
                        utils::shadowClickMouseAt( coord.first, coord.second );
                        std::cout << "[+] clicked at (" << coord.first << ", " << coord.second << ")" << std::endl;
                        std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
                    }

                    std::this_thread::sleep_for( std::chrono::minutes( 1 ) );

                    for ( int i = 0; i < 2; ++i ) {
                        utils::shadowSendKey( VK_ESCAPE );
                        std::cout << "[+] ESC pressed." << std::endl;
                    }

                    std::this_thread::sleep_for( std::chrono::milliseconds( 250 ) );

                    utils::shadowSendKey( VK_BACK );
                    std::cout << "[+] BACKSPACE pressed." << std::endl;
                }

            };

            antiAFK( );
            fortuneWheel( );
            goto restart;
		}
		break;

        // fast loot
        case 2: {

            // clear
            system( "cls" );

            std::cout << "Press F5 to start, F5 to stop." << std::endl;

            // activate window
            utils::ActivateWindow(  );

            auto getLoot = [ & ]( ) {

                bool isActive = false;
                bool lastState = !isActive;

                while ( true ) {

                    if ( GetAsyncKeyState( VK_F5 ) & 1 )
                        isActive = !isActive;

                    system( "cls" );

                    std::cout << "Press " << "F5" << " to loot." << std::endl;

                    if ( isActive ) {
                        
                        std::cout << "looting started..." << std::endl;

                        // press E
                        utils::shadowSendKey( 0x45 );

                        // click "MAX"
                        utils::shadowClickMouseAt( 1100, 575 );

                        // click "Pickup"
                        utils::shadowClickMouseAt( 860, 655 );

                        isActive = false;

                    }
                    else
                        std::cout << "looting Paused." << std::endl;


                    // save CPU
                    std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
                }
            };

            getLoot( );

        }
        break;

        // harbor
        case 3: {
            system( "cls" );

            std::cout << "Press F5 to start, F5 to stop." << std::endl;

            // activate window
            utils::ActivateWindow( );

            auto getPixel = [ & ]( ) {

                bool isActive = false;
                bool lastState = !isActive;

                while ( true ) {

                    if ( GetAsyncKeyState( VK_F5 ) & 1 )
                        isActive = !isActive;

                    if ( isActive != lastState ) {
                        system( "cls" );

                        std::cout << "Press F5 to start, F5 to stop." << std::endl;

                        if ( isActive )
                        {
                            std::cout << "Harbor started." << std::endl;
                            utils::shadowSendKeyCode( 0x11, true );
                            utils::shadowSendKeyCode( 0x2A, true );
                        }
                        else 
                        {
                            std::cout << "Harbor paused." << std::endl;
                            utils::shadowSendKeyCode( 0x11, false );
                            utils::shadowSendKeyCode( 0x2A, false );
                        }

                        lastState = isActive;
                    }

                    if ( utils::PixelSearch( RGB( 126, 211, 33 ), 962, 476, 970, 510, 0 ) )
                        utils::shadowSendKey( VK_E );

                    // save CPU
                    std::this_thread::sleep_for( std::chrono::milliseconds( 25 ) );
                }
            };

            getPixel( );

        }
        break;

        case 4: {
            system( "cls" );

            std::cout << "Press F5 to start, F5 to stop." << std::endl;

            // activate window
            utils::ActivateWindow( );

            auto getPixel = [ & ]( ) {

                bool isActive = false;
                bool lastState = !isActive;

                while ( true ) {

                    if ( GetAsyncKeyState( VK_F5 ) & 1 )
                        isActive = !isActive;

                    if ( isActive != lastState ) {
                        system( "cls" );

                        std::cout << "Press F5 to start, F5 to stop." << std::endl;

                        if ( isActive )
                        {
                            std::cout << "Sewing started." << std::endl;
                            utils::shadowSendKey( 0x45 );
                        }
                        else 
                        {
                            std::cout << "Sewing paused." << std::endl;
                        }

                        lastState = isActive;
                    }

                    if ( isActive ) {
                        utils::shadowSendKey( 0x45 );

                        // W
                        if ( utils::PixelSearch( RGB( 253, 253, 253 ), 944, 560, 1, 1, 0 ) )
                            if ( utils::PixelSearch( RGB( 255, 255, 255 ), 951, 579, 2, 2, 0 ) )
                                utils::shadowSendKeyCode( 0x11 );

                        // A
                        if ( utils::PixelSearch( RGB( 255, 255, 255 ), 959, 561, 2, 2, 0 ) )
                            if ( utils::PixelSearch( RGB( 255, 255, 255 ), 959, 575, 2, 2, 0 ) )
                                utils::shadowSendKeyCode( 0x1E );

                        // S
                        if ( utils::PixelSearch( RGB( 255, 255, 255 ), 959, 561, 2, 2, 0 ) )
                            if ( utils::PixelSearch( RGB( 255, 255, 255 ), 959, 571, 2, 2, 0 ) )
                                if ( utils::PixelSearch( RGB( 255, 255, 255 ), 959, 581, 2, 2, 0 ) )
                                    utils::shadowSendKeyCode( 0x1F );

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
        break;

	default:
		break;
	}

	/*
	*	run your overlay here instead of the while true loop
	*/

    while (true)
    {

    }

	return EXIT_SUCCESS;
}
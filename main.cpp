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

    //cursor();

    std::cout << "[?] Important! This program is not a cheat or anything else\nIt just simulates pressing keys on your keyboard via WinAPI.\n!!!USE IT AT YOUR OWN RISK!!! \nThe author is not responsible for your account!" << std::endl;

    std::this_thread::sleep_for( std::chrono::seconds( 5 ) );

    std::cout << "[~] Open GTA5." << std::endl;

    // init
    bool once = false;
    while ( !once ) {
        DWORD ForegroundWindowProcessID;
        GetWindowThreadProcessId( GetForegroundWindow( ), &ForegroundWindowProcessID );
        if ( utils::GetProcessId( "GTA5.exe" ) == ForegroundWindowProcessID ) {
            utils::window = GetForegroundWindow( );
            std::cout << "[+] GTA5RP.exe has been found!" << std::endl;
            once = true;
        }
    }

	int selectType = 0;
    int resolution_type = 1;
    std::cout << "Select:\n 1. AntiAFK\n 2. Jail(sewing)(soon)\n 3. Fast loot(soon)\n 4. EMS fast revive(soon)\n 5. Harbor bot\ntype: ";
	std::cin >> selectType;

	switch ( selectType ) {
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
                    utils::shadowSendKey( VK_BACK );
                    std::cout << "[+] BACKSPACE pressed." << std::endl;
                }

            };

            antiAFK( );
            fortuneWheel( );
            goto restart;
		}
		break;

        case 2: {
            system( "cls" );

            std::cout << "Press F5 to start." << std::endl;

            std::this_thread::sleep_for( std::chrono::seconds( 1 ) );

            // activate window
            utils::ActivateWindow(  );

            auto getPixel = [ & ]( ) {

                bool isActive = false;
                bool lastState = !isActive;

                while ( true ) {

                    if ( GetAsyncKeyState( VK_F5 ) & 1 )
                        isActive = !isActive;

                    if ( isActive != lastState ) {
                        system( "cls" );

                        std::cout << "Press F5 to start." << std::endl;

                        if ( isActive ) {
                            std::cout << "Sewing started." << std::endl;






                            isActive = false;
                        }
                        
                        lastState = isActive;
                    }

                    // save CPU
                    std::this_thread::sleep_for( std::chrono::milliseconds( 125 ) );
                }
            };

            getPixel( );

        }
        break;

        case 5: {
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
                            std::cout << "Harbor Started." << std::endl;
                            utils::shadowSendKeyCode( 0x11, true );
                            utils::shadowSendKeyCode( 0x2A, true );
                        }
                        else 
                        {
                            std::cout << "Harbor Paused." << std::endl;
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
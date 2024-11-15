#pragma once

#include "antiafk/antiafk.hpp"
#include "fastloot/loot.hpp"
#include "sewing/sewing.hpp"
#include "harbor/harbor.hpp"

namespace features {

	auto run( ) -> void
	{
		// test
		if ( config::afk_bypass::bEnabled ) 
			antiafk::run( );
	
		if ( config::fast_loot::bEnabled )
			fastloot::run( );

		// test
		if ( config::sewing::bEnabled ) 
			sewing::run( );

		if ( config::harbor::bEnabled ) 
			harbor::run( );

	}

};










//int selectType = 0;
//   int resolution_type = 1;
//   std::cout << "Select:\n 1. Casino(ALPHA)\n 2. AntiAFK\n 3. Fast loot\n 4. Harbor bot\n 5. Sewing\ntype: ";
   //std::cin >> selectType;

   //switch ( selectType ) {

//       // casino
//       case 1: {

//           // clear
//           system( "cls" );

//           // activate window
//           utils::ActivateWindow(  );

//           auto getNumbers = [ & ]( ) {

//               int numbers[ 38 ] = { };
//               int counter = 0;

//               bool isActive = false;

//               while ( true ) {

//                   if ( utils::PixelSearch( RGB( 254, 254, 254 ), 1067, 959, 1, 1, 10 ) &&
//                        utils::PixelSearch( RGB( 254, 254, 254 ), 1067, 971, 1, 1, 10 ) &&
//                        utils::PixelSearch( RGB( 254, 254, 254 ), 1067, 984, 1, 1, 10 ) &&
//                        utils::PixelSearch( RGB( 254, 254, 254 ), 1067, 993, 1, 1, 10 ) )
//                       isActive = true;
//                   else
//                       isActive = false;

//                   if ( isActive ) 
//                   {
//                       // wait spin wheel
//                       std::this_thread::sleep_for( std::chrono::seconds( 15 ) );

//                       // start by 30
//                       if ( utils::PixelSearch( RGB( 255, 255, 255 ), 1867, 1034, 1, 1, 0 ) &&
//                            utils::PixelSearch( RGB( 255, 255, 255 ), 1872, 1034, 1, 1, 0 ) &&
//                            utils::PixelSearch( RGB( 254, 254, 254 ), 1870, 1039, 1, 1, 0 ) &&
//                            utils::PixelSearch( RGB( 250, 247, 247 ), 1871, 1044, 1, 1, 0 ) &&
//                            utils::PixelSearch( RGB( 255, 255, 255 ), 1866, 1044, 1, 1, 0 ) )
//                       {
//                       
//                           // 6
//                           if ( utils::PixelSearch( RGB( 247, 241, 242 ), 1882, 1034, 1, 1, 0 ) && 
//                                utils::PixelSearch( RGB( 244, 238, 238 ), 1879, 1034, 1, 1, 0 ) && 
//                                utils::PixelSearch( RGB( 251, 249, 249 ), 1876, 1039, 1, 1, 0 ) && 
//                                utils::PixelSearch( RGB( 255, 255, 255 ), 1880, 1039, 1, 1, 0 ) && 
//                                utils::PixelSearch( RGB( 252, 249, 249 ), 1883, 1042, 1, 1, 0 ) /*&& 
//                                utils::PixelSearch( RGB( 255, 255, 255 ), 1880, 1045, 1, 1, 0 )*/ )
//                               numbers[ 36 ]++;

//                           // 5
//                           else if ( utils::PixelSearch( RGB( 255, 255, 255 ), 1882, 1034, 1, 1, 0 ) && 
//                                utils::PixelSearch( RGB( 255, 255, 255 ), 1878, 1034, 1, 1, 0 ) && 
//                                utils::PixelSearch( RGB( 255, 255, 255 ), 1878, 1039, 1, 1, 0 ) && 
//                                utils::PixelSearch( RGB( 252, 252, 252 ), 1881, 1039, 1, 1, 0 ) && 
//                                utils::PixelSearch( RGB( 249, 249, 249 ), 1883, 1042, 1, 1, 0 ) && 
//                                utils::PixelSearch( RGB( 254, 254, 254 ), 1882, 1044, 1, 1, 0 ) /*&& 
//                                utils::PixelSearch( RGB( 254, 254, 254 ), 1877, 1044, 1, 1, 0 )*/ )
//                               numbers[ 35 ]++;

//                           // 4
//                           else if ( utils::PixelSearch( RGB( 246, 241, 241 ), 1881, 1034, 1, 1, 0 ) &&
//                                utils::PixelSearch( RGB( 253, 251, 251 ), 1878, 1038, 1, 1, 0 ) && 
//                                utils::PixelSearch( RGB( 255, 255, 255 ), 1876, 1042, 1, 1, 0 ) && 
//                                utils::PixelSearch( RGB( 232, 217, 218 ), 1881, 1039, 1, 1, 0 ) && 
//                                utils::PixelSearch( RGB( 255, 255, 255 ), 1881, 1042, 1, 1, 0 ) /*&& 
//                                utils::PixelSearch( RGB( 239, 229, 229 ), 1881, 1045, 1, 1, 0 )*/ )
//                               numbers[ 34 ]++;

//                           // 3
//                           else if ( utils::PixelSearch( RGB( 255, 255, 255 ), 1877, 1034, 1, 1, 0 ) &&
//                                utils::PixelSearch( RGB( 229, 229, 229 ), 1883, 1034, 1, 1, 0 ) && 
//                                utils::PixelSearch( RGB( 255, 255, 255 ), 1880, 1039, 1, 1, 0 ) && 
//                                utils::PixelSearch( RGB( 254, 254, 254 ), 1882, 1040, 1, 1, 0 ) && 
//                                utils::PixelSearch( RGB( 254, 254, 254 ), 1883, 1042, 1, 1, 0 ) && 
//                                utils::PixelSearch( RGB( 253, 253, 253 ), 1882, 1044, 1, 1, 0 ) /*&& 
//                                utils::PixelSearch( RGB( 252, 252, 252 ), 1877, 1044, 1, 1, 0 )*/ )
//                               numbers[ 33 ]++;
//                       
//                           // 2
//                           //if ( utils::PixelSearch( RGB( 255, 255, 255 ), , , 1, 1, 0 ) && 
//                           //     utils::PixelSearch( RGB( 255, 255, 255 ), , , 1, 1, 0 ) && 
//                           //     utils::PixelSearch( RGB( 255, 255, 255 ), , , 1, 1, 0 ) && 
//                           //     utils::PixelSearch( RGB( 255, 255, 255 ), , , 1, 1, 0 ) && 
//                           //     utils::PixelSearch( RGB( 255, 255, 255 ), , , 1, 1, 0 ) && 
//                           //   
//                           //    )

//                           //// 1
//                           //if ( utils::PixelSearch( RGB( 255, 255, 255 ), , , 1, 1, 0 ) && 
//                           //     utils::PixelSearch( RGB( 255, 255, 255 ), , , 1, 1, 0 ) && 
//                           //     utils::PixelSearch( RGB( 255, 255, 255 ), , , 1, 1, 0 ) && 
//                           //     utils::PixelSearch( RGB( 255, 255, 255 ), , , 1, 1, 0 ) && 
//                           //     utils::PixelSearch( RGB( 255, 255, 255 ), , , 1, 1, 0 ) && 
//                           //   
//                           //    )

//                           //// 0
//                           //if ( utils::PixelSearch( RGB( 255, 255, 255 ), , , 1, 1, 0 ) && 
//                           //     utils::PixelSearch( RGB( 255, 255, 255 ), , , 1, 1, 0 ) && 
//                           //     utils::PixelSearch( RGB( 255, 255, 255 ), , , 1, 1, 0 ) && 
//                           //     utils::PixelSearch( RGB( 255, 255, 255 ), , , 1, 1, 0 ) && 
//                           //     utils::PixelSearch( RGB( 255, 255, 255 ), , , 1, 1, 0 ) && 
//                           //   
//                           //    )

//                       }

//                       counter++;
//                   }

//                   if ( counter >= 50 )
//                   {
//                       // stawki

//                   }

//                   system( "cls" );
//                   std::cout << "Numbers array ->\n";
//                   for ( int i = 0; i < 38; ++i ) {
//                       std::cout << "Number " << i << ": " << numbers[i] << std::endl;
//                   }

//                   // save CPU
//                   std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );
//               }
//           };

//           getNumbers( );

//       }
//       break;

//       // antiafk
   //	case 2: {
//           // clear
//           system( "cls" );

//           // notify
//           std::cout << "anti-afk started.\n";

//           // sleep
//           std::this_thread::sleep_for( std::chrono::seconds( 2 ) );

//           // activate window
//           utils::ActivateWindow( );

//           restart:
//           auto antiAFK = [ & ]( ) {

//               auto start = std::chrono::steady_clock::now( );
//               while ( true ) {
//                   
//                   // activate window
//                   utils::ActivateWindow( );

//                   auto now = std::chrono::steady_clock::now( );
//                   auto elapsed = std::chrono::duration_cast< std::chrono::minutes >( now - start );

//                   if ( elapsed.count( ) >= 30 ) {
//                       std::cout << "[!] 30 minutes have passed." << std::endl;
//                       break;
//                   }

//                   utils::shadowSendKeyCode( 0x11, true );
//                   utils::shadowSendKeyCode( 0x1F, true );

//                   std::this_thread::sleep_for( std::chrono::seconds( 5 ) );
//               }

//           };

   //		auto fortuneWheel = [ & ] ( int resolution = 1 ) {
//      
//               // activate window
//               utils::ActivateWindow( );

//               std::pair< int, int > coordinates[] = {
//                       { 1645, 905 },
//                       { 760, 650 },
//                       { 960, 885 },
//               };

//               while ( true ) {
//                   // open phone
//                   utils::shadowSendKey( VK_UP );
//                   std::cout << "[+] open the phone." << std::endl;

//                   for (const auto& coord : coordinates) {
//                       utils::shadowClickMouseAt( coord.first, coord.second );
//                       std::cout << "[+] clicked at (" << coord.first << ", " << coord.second << ")" << std::endl;
//                       std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
//                   }

//                   std::this_thread::sleep_for( std::chrono::minutes( 1 ) );

//                   for ( int i = 0; i < 2; ++i ) {
//                       utils::shadowSendKey( VK_ESCAPE );
//                       std::cout << "[+] ESC pressed." << std::endl;
//                   }

//                   std::this_thread::sleep_for( std::chrono::milliseconds( 250 ) );

//                   utils::shadowSendKey( VK_BACK );
//                   std::cout << "[+] BACKSPACE pressed." << std::endl;
//               }

//           };

//           antiAFK( );
//           fortuneWheel( );
//           goto restart;
   //	}
   //	break;

//       // fast loot
//       case 3: {

//           // clear
//           system( "cls" );

//           std::cout << "Press F5 to start, F5 to stop." << std::endl;

//           // activate window
//           utils::ActivateWindow(  );

//           auto getLoot = [ & ]( ) {

//               bool isActive = false;
//               bool lastState = !isActive;

//               while ( true ) {

//                   if ( GetAsyncKeyState( VK_F5 ) & 1 )
//                       isActive = !isActive;

//                   system( "cls" );

//                   std::cout << "Press " << "F5" << " to loot." << std::endl;

//                   if ( isActive ) {
//                       
//                       std::cout << "looting started..." << std::endl;

//                       // press E
//                       utils::shadowSendKey( 0x45 );

//                       // click "MAX"
//                       utils::shadowClickMouseAt( 1100, 575 );

//                       // click "Pickup"
//                       utils::shadowClickMouseAt( 860, 655 );

//                       isActive = false;

//                   }
//                   else
//                       std::cout << "looting Paused." << std::endl;


//                   // save CPU
//                   std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
//               }
//           };

//           getLoot( );

//       }
//       break;

//       // harbor
//       case 4: {
//           system( "cls" );

//           std::cout << "Press F5 to start, F5 to stop." << std::endl;

//           // activate window
//           utils::ActivateWindow( );

//           auto getPixel = [ & ]( ) {

//               bool isActive = false;
//               bool lastState = !isActive;

//               while ( true ) {

//                   if ( GetAsyncKeyState( VK_F5 ) & 1 )
//                       isActive = !isActive;

//                   if ( isActive != lastState ) {
//                       system( "cls" );

//                       std::cout << "Press F5 to start, F5 to stop." << std::endl;

//                       if ( isActive )
//                       {
//                           std::cout << "Harbor started." << std::endl;
//                           utils::shadowSendKeyCode( 0x11, true );
//                           utils::shadowSendKeyCode( 0x2A, true );
//                       }
//                       else 
//                       {
//                           std::cout << "Harbor paused." << std::endl;
//                           utils::shadowSendKeyCode( 0x11, false );
//                           utils::shadowSendKeyCode( 0x2A, false );
//                       }

//                       lastState = isActive;
//                   }

//                   if ( utils::PixelSearch( RGB( 126, 211, 33 ), 963, 494, 1, 1, 0 ) )
//                       utils::shadowSendKey( VK_E );

//                   // save CPU
//                   std::this_thread::sleep_for( std::chrono::milliseconds( 25 ) );
//               }
//           };

//           getPixel( );

//       }
//       break;

//       // sewing
//       case 5: {
//           system( "cls" );

//           std::cout << "Press F5 to start, F5 to stop." << std::endl;

//           // activate window
//           utils::ActivateWindow( );

//           auto getPixel = [ & ]( ) {

//               bool isActive = false;
//               bool lastState = !isActive;

//               while ( true ) {

//                   if ( GetAsyncKeyState( VK_F5 ) & 1 )
//                       isActive = !isActive;

//                   if ( isActive != lastState ) {
//                       system( "cls" );

//                       std::cout << "Press F5 to start, F5 to stop." << std::endl;

//                       if ( isActive )
//                       {
//                           std::cout << "Sewing started." << std::endl;
//                           utils::shadowSendKey( 0x45 );
//                       }
//                       else 
//                       {
//                           std::cout << "Sewing paused." << std::endl;
//                       }

//                       lastState = isActive;
//                   }

//                   if ( isActive ) {
//                       utils::shadowSendKey( 0x45 );

//                       // W
//                       if ( utils::PixelSearch( RGB( 253, 253, 253 ), 944, 560, 1, 1, 0 ) )
//                           if ( utils::PixelSearch( RGB( 255, 255, 255 ), 951, 579, 2, 2, 0 ) )
//                               utils::shadowSendKeyCode( 0x11 );

//                       // A
//                       if ( utils::PixelSearch( RGB( 255, 255, 255 ), 959, 561, 2, 2, 0 ) )
//                           if ( utils::PixelSearch( RGB( 255, 255, 255 ), 959, 575, 2, 2, 0 ) )
//                               utils::shadowSendKeyCode( 0x1E );

//                       // S
//                       if ( utils::PixelSearch( RGB( 255, 255, 255 ), 959, 561, 2, 2, 0 ) )
//                           if ( utils::PixelSearch( RGB( 255, 255, 255 ), 959, 571, 2, 2, 0 ) )
//                               if ( utils::PixelSearch( RGB( 255, 255, 255 ), 959, 581, 2, 2, 0 ) )
//                                   utils::shadowSendKeyCode( 0x1F );

//                       // D
//                       if ( utils::PixelSearch( RGB( 255, 255, 255 ), 950, 560, 2, 2, 0 ) )
//                           if ( utils::PixelSearch( RGB( 255, 255, 255 ), 950, 575, 2, 2, 0 ) )
//                               if ( utils::PixelSearch( RGB( 255, 255, 255 ), 970, 570, 2, 2, 0 ) )
//                                   utils::shadowSendKeyCode( 0x20 );
//                   }

//                   // save CPU
//                   std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );
//               }
//           };

//           getPixel( );

//       }
//       break;

   //default:
   //	break;
   //}
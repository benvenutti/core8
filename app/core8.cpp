#include "MainWindow.hpp"

#include <QApplication>

#include "IoDeviceImpl.hpp"
#include <model/VM.hpp>

#include <iostream>

void print( const model::VM& vm )
{
    int l = 0;

    std::cout << "model::chip8::display_size: " << model::chip8::display_size << std::endl;

    for ( int i = 0; i < model::chip8::display_size; i++ )
    {
        if ( i / model::chip8::display_width > l )
        {
            l++;
            std::cout << std::endl;
        }
        std::cout << ( vm.getCPU().buffer().at( i ) != 0 ? "1" : "0" );
    }

    std::cout << std::endl;
}

int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );
    MainWindow   window;
    window.show();

    return app.exec();

    //    IoDeviceImpl io;
    //    model::VM    vm{ io };

    //    vm.loadRom( "/Users/diogo.benvenutti/draft/roms/Keypad Test [Hap, 2006].ch8" );
    //    for ( auto i = 0; i < 400; ++i )
    //        vm.cycle();

    //    print( vm );

    return 0;
}

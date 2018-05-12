#include "MainWindow.hpp"

#include <QApplication>

#include "IoDeviceImpl.hpp"
#include <model/VM.hpp>

#include <cstdint>
#include <iostream>
#include <vector>

int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );
    MainWindow   window;
    window.show();

    return app.exec();

    IoDeviceImpl io;
    model::VM    vm{ io };


    vm.loadRom( "/Users/diogo.benvenutti/draft/roms/Keypad Test [Hap, 2006].ch8" );
    for ( auto i = 0; i < 500; ++i )
        vm.cycle();

    std::vector<uint32_t> buff;
    for ( const auto p : vm.getCPU().buffer() )
    {
        buff.push_back( p == 0 ? 0 : 0xffffffff ); // 0xffRRGGBB
    }


    QImage img{ reinterpret_cast<const uchar*>( buff.data() ),
                model::chip8::display_width,
                model::chip8::display_height,
                QImage::Format_RGB32 };

    img.save( "/Users/diogo.benvenutti/core.png" );

    return 0;
}

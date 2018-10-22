project( emulator VERSION 0.1 LANGUAGES CXX )

## files:

set( source_files
  IoDeviceImpl.cpp
  MainWindow.cpp
  ScreenWidget.cpp
  core8.cpp )

set( header_files
  IoDeviceImpl.hpp
  MainWindow.hpp
  ScreenWidget.hpp )

set( ui_files mainwindow.ui )

qt5_wrap_cpp( header_files_moc ${header_files} )
qt5_wrap_ui( ui_files_moc ${ui_files} )

## executable:

add_executable( ${PROJECT_NAME}
  ${source_files}
  ${header_files}
  ${header_files_moc}
  ${ui_files_moc} )

target_include_directories( ${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR} )
target_link_libraries( ${PROJECT_NAME} PUBLIC model Qt5::Widgets )

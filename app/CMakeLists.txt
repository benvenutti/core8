project(emulator VERSION 0.1 LANGUAGES CXX)

## files:

set(source_files
  MainWindow.cpp
  core8.cpp)

set(header_files
  MainWindow.hpp)

set(ui_files
  MainWindow.ui)

qt5_wrap_cpp(header_files_moc ${header_files})
qt5_wrap_ui(ui_files_moc ${ui_files})

include_directories(${PROJECT_BINARY_DIR})

## executable:

add_executable(${PROJECT_NAME}
  ${source_files}
  ${header_files}
  ${header_files_moc}
  ${ui_files_moc})

target_link_libraries (${PROJECT_NAME} PUBLIC model Qt5::Widgets)

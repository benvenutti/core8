qt_standard_project_setup()

qt_add_executable(
  core8-gui-qtwidget
  src/core8.cpp
  src/IoDeviceImpl.cpp
  src/IoDeviceImpl.hpp
  src/MainWindow.cpp
  src/MainWindow.hpp
  src/mainwindow.ui
  src/ScreenWidget.cpp
  src/ScreenWidget.hpp
)

target_compile_features(core8-gui-qtwidget PUBLIC cxx_std_20)

set_target_properties(
  core8-gui-qtwidget
  PROPERTIES
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    COMPILE_WARNING_AS_ERROR ON
)

target_link_libraries(
  core8-gui-qtwidget
  PUBLIC
    Qt6::Widgets
    core8-model
)

# Prevent the creation of a console window on Windows
set_target_properties(
  core8-gui-qtwidget
  PROPERTIES
    WIN32_EXECUTABLE ON
)

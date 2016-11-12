include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Add(
        catch
        GIT_REPOSITORY https://github.com/philsquared/Catch.git
        TIMEOUT 10
        UPDATE_COMMAND ${GIT_EXECUTABLE} pull
        SOURCE_DIR "${CMAKE_SOURCE_DIR}/${EXTERNALS_PROJECTS_DIR}/catch"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        LOG_DOWNLOAD ON
)

ExternalProject_Get_Property(catch source_dir)
set(CATCH_INCLUDE_DIR ${source_dir}/include CACHE INTERNAL "Path to include folder for Catch")
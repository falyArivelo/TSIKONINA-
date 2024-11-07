cmake_minimum_required(VERSION 3.16)

project(TSIKONINA VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Network Sql )

qt_standard_project_setup()

qt_add_executable(appTSIKONINA
    main.cpp
)

qt_add_qml_module(appTSIKONINA
    URI TSIKONINA
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES model/recipe.h model/recipe.cpp
        SOURCES model/recipe_fetcher.h model/recipe_fetcher.cpp
        SOURCES
        SOURCES
        SOURCES
        SOURCES db_connection/idatabase.h
        SOURCES db_connection/sqlite_database.h db_connection/sqlite_database.cpp
        SOURCES db_connection/database_factory.h db_connection/database_factory.cpp
        SOURCES model/recipe_downloader.h model/recipe_downloader.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appTSIKONINA PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appTSIKONINA
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appTSIKONINA
    PRIVATE
    Qt6::Quick
    Qt6::Network
    Qt6::Sql
)

include(GNUInstallDirs)
install(TARGETS appTSIKONINA
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

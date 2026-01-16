cmake_minimum_required(VERSION 3.19)
project(src LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(src
    main.cpp
    ManageLib.h ManageLib.cpp
    Book.h Book.cpp
)

target_link_libraries(src
    PRIVATE
        Qt::Core
)
target_link_libraries(src PRIVATE Qt6::Core)
target_link_libraries(src PRIVATE Qt6::Core)

include(GNUInstallDirs)

install(TARGETS src
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

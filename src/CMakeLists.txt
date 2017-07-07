# QTDIR must point to c:/Qt/5.7/mingw53_32/ or similar
message("qtdir is set to '$ENV{QTDIR}' (must be 'c:/Qt/5.7/mingw53_32/' or similar)")
set(CMAKE_PREFIX_PATH "$ENV{QTDIR}")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(EXE_NAME "eater_snek")

set(COMMON_SOURCES
        AbstractAppalStore.h
        AbstractLevel.h
        params.h
        pathfinding.cpp
        pathfinding.h
        snek_enums.cpp
        snek_enums.h
        )
add_library(eater_snek_common ${COMMON_SOURCES})
target_link_libraries(eater_snek_common Qt5::Core)

set(EXE_SOURCES
        main.cpp
        eater_snek.ui
        MainWindow.cpp
        MainWindow.h
        CanvasWidget.h
        CanvasWidget.cpp
        Snek.h
        Snek.cpp
        Appal.cpp
        Appal.h
        Wall.cpp
        Wall.h
        Level.cpp
        Level.h
        SnekCommands.cpp
        SnekCommands.h
        )

add_executable(${EXE_NAME} ${EXE_SOURCES})
target_link_libraries(${EXE_NAME} eater_snek_common Qt5::Widgets Qt5::Core)

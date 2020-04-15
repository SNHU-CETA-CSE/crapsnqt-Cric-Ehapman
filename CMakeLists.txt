cmake_minimum_required(VERSION 3.7)
project(crapsStarter)
set(CMAKE_CXX_STANDARD 17)

# Tell cmake where Qt is located
set(CMAKE_PREFIX_PATH "D:\\Qt\\5.14.1\\mingw73_64\\bin")
set(Qt5_DIR "D:\\Qt\\5.14.1\\mingw73_64\\lib\\cmake\\Qt5")
set(QT_INCLUDES "D:\\Qt\\5.14.1\\mingw73_64\\include")
MESSAGE("QT_INCLUDES: ${QT_INCLUDES}")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON) # if you have any .ui files
set(CMAKE_AUTORCC ON) # if you have any .qrc files

# Find QT packages
include_directories(cmake-build-debug/crapsStarter_autogen/include)
find_package(Qt5 COMPONENTS Widgets)

# Add the include directories for the Qt 5 Widgets module to
# the compile lines.
include_directories(${Qt5Widgets_INCLUDE_DIRS})

# Add compiler flags for building executables (-fPIE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

qt5_generate_moc(crapsGame.cpp crapsGame.moc craps.cpp craps.moc)

add_executable(${PROJECT_NAME} crapsGame.cpp die.cpp die.h craps.cpp craps.h CrapsMainWindow.ui crapsResources.qrc)

#Link the crapsStarter executable to the Qt 5 widgets library.
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)



cmake_minimum_required(VERSION 3.15)
project(crapsStarter)

set(CMAKE_CXX_STANDARD 17)

#set(RESOURCES crapsResources.qrc)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
include_directories(cmake-build-debug/crapsStarter_autogen/include)

# Tell cmake where Qt is located
set(Qt5_DIR "/usr/local/Cellar/qt/5.14.1/lib/cmake/Qt5")
set(QT_INCLUDES "/usr/local/Cellar/qt/5.14.1/include")
MESSAGE("QT_INCLUDES: ${QT_INCLUDES}")

# Include a library search using find_package()
# via REQUIRED, specify that libraries are required
set(Qt5 NEED)
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(SOURCE_FILES craps.cpp die.cpp die.h craps.h crapsGame.cpp crapsResources.cpp)
add_executable(crapsStarter ${SOURCE_FILES})

# specify which libraries to connect
target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

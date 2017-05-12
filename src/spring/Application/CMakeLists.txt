set(INCROOT ${PROJECT_SOURCE_DIR}/include/Spring/Application)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/Spring/Application)

# all source files
file(GLOB INCS "${INCROOT}/*.h")
file(GLOB SRCS "${SRCROOT}/*.cpp")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${Spring_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${Spring_SOURCE_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${Spring_SOURCE_DIR}/bin")

# Find the QtWidgets library
find_package(Qt5 COMPONENTS Core Widgets Multimedia REQUIRED)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
include_directories("${Spring_SOURCE_DIR}/bin")
include_directories(${Qt5Multimedia_INCLUDES})

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
 add_definitions(${Qt5Widgets_DEFINITIONS})
 add_definitions(${Qt5Multimedia_DEFINITIONS})
 
add_library(Application SHARED ${SRCS} ${INCS})

target_link_libraries(Application Framework Qt5::Widgets Qt5::Core QCustomPlot Qt5::Multimedia)

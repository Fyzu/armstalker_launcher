# Set paths
set(CMAKE_PREFIX_PATH H:/Dev/Qt/5.7/mingw53_32/lib/cmake)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/target/${PROJECT_VERSION}/)

# Build settings
add_definitions(-std=c++14)
#set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
#set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Windows resource file
configure_file(${PROJECT_SOURCE_DIR}/resources/resource.rc.in
        ${CMAKE_CURRENT_BINARY_DIR}/resources.rc)

set(RES_FILE ${CMAKE_CURRENT_BINARY_DIR}/resources.obj)
add_custom_command(OUTPUT ${RES_FILE}
        COMMAND windres.exe ${CMAKE_CURRENT_BINARY_DIR}/resources.rc ${RES_FILE})

# Qt5 configure
foreach (QT_LIBRARIES_REQUIRED ${QT_LIBRARIES_REQUIRED})
    find_package(Qt5${QT_LIBRARIES_REQUIRED} REQUIRED)
    set(QT_LIBRARIES ${QT_LIBRARIES} Qt5::${QT_LIBRARIES_REQUIRED})
endforeach ()
qt5_wrap_ui(UI_HEADERS ${UI_FILES})

# Configure
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${UI_FILES} ${RCC_FILES} ${RES_FILE} ${CONFIG_FILE})
qt5_use_modules(${PROJECT_NAME} ${QT_LIBRARIES_REQUIRED})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} ${EXTERNAL_LIBRARIES})

# TODO: Добавить линкование Qt и mingw dll
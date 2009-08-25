Cmake_Minimum_Required(VERSION 2.6)
set( CMAKE_MODULE_PATH ".")

Project (ffmpeg-gui)


ADD_DEFINITIONS( "-Wall -std=gnu++0x -pedantic -ggdb")
find_package(Qt4 4.5.1 COMPONENTS QtCore QtGui REQUIRED )
include(${QT_USE_FILE} )
link_directories (${QT_LIBRARY_DIR})

SET(MOC_HEADERS  ./MainWindow.hpp ./FFMPEG.hpp ./ChooseParameters.hpp ./ChooseAudioCodec.hpp ./ChooseVideoCodec.hpp ./ChooseFileFormat.hpp ./Utils.hpp ./StartFFmpeg.hpp ChooseGeneric.hpp)

SET( UIS
./ChooseFileFormat.ui
./ChooseVideoCodec.ui
./ChooseAudioCodec.ui
)

QT4_WRAP_CPP(MOC_SRCS ${MOC_HEADERS} )
QT4_WRAP_UI(UI_HEADERS ${UIS})

find_package(FFMPEG)
include_directories(${FFMPEG_INCLUDE_DIR})
link_directories(${FFMPEG_LIBRARY_DIR})

Add_Executable(main main.cpp MainWindow.cpp  ChooseParameters.cpp ChooseAudioCodec.cpp ChooseVideoCodec.cpp ChooseFileFormat.cpp Utils.cpp FFMPEG StartFFmpeg.cpp  ChooseGeneric.cpp ${UI_HEADERS}  ${MOC_SRCS})
TARGET_LINK_LIBRARIES( main ${FFMPEG_LIBRARIES} ${QT_LIBRARIES} ) #${FFMPEG_LIBRARIES} ${QT_LIBRARIES} )


# set_target_properties(main 
#   PROPERTIES DEBUG ON)


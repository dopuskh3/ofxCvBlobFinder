cmake_minimum_required(VERSION 2.8)

project(ofxCvBlobFinderExample)


file ( GLOB_RECURSE app_sources_files src/ofxCvBlobFinder.cpp src/ofxCvBlobFinder.h example/main.cpp example/testApp.h example/testApp.cpp src/ofxCvComplexBlob.cpp src/ofxCvComplexBlob.h )

include_directories( src example )

# ofxVectorMath
file ( GLOB_RECURSE ofxVectorMath ../../addons/ofxVectorMath/src/* )
include_directories ( ../../addons/ofxVectorMath/src/ ) 

# ofxOpenCv
file ( GLOB_RECURSE ofxOpenCv ../../addons/ofxOpenCv/src/* )
include_directories ( ../../addons/ofxOpenCv/src/ ) 


if ( CMAKE_SYSTEM_NAME MATCHES "Linux" ) 
    #include(FindPkgConfig)
    #pkg_search_module(CV opencv)
    #include_directories ( ${CV_INCLUDE_DIRS} )
    set ( CV_LIBRARIES "-L/usr/local/lib -lcxcore -lcv -lcvaux -lml")
    include_directories (/usr/local/include/opencv)
    # message ( " ${CV_LIBRARIES} - ${CV_INCLUDE_DIRS} ") 
endif()


add_executable( ofxCvBlobFinderExample
    ${app_sources_files}
    ${ofxOpenCv}
    ${ofxVectorMath}
    ${OFX_SOURCE_FILES} )


include(FindPkgConfig)

pkg_check_modules(OF openFrameworks)
set (CMAKE_CXX_FLAGS ${OF_CFLAGS_OTHER} )
include_directories (${OF_INCLUDE_DIRS}) # ${OF_CFLAGS})

set ( libs ${OF_LIBRARIES} ${CV_LIBRARIES}) 
target_link_libraries(ofxCvBlobFinderExample ${libs} )

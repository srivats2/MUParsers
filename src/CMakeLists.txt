
# Prevent compilation in-source
if( ${CMAKE_BINARY_DIR} STREQUAL ${PROJECT_SOURCE_DIR} )
  Message( " " )
  Message( FATAL_ERROR "Source and build  directories are the same.
 Create an empty build directory,
 change into it and re-invoke cmake")
endif()

#Path of all custom header files
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/headers)


#    Tell CMake where to leave executables
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
IF(APPLE)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/macosx/)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/macosx/)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/macosx/)
ELSEIF(UNIX)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/linux/)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/linux/)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/linux/)
ELSEIF(WIN32)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/win32/)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/win32/)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/win32/)
ENDIF()



# Tell CMake where to find the externally compiled libraries
if(APPLE)
link_directories(${PROJECT_SOURCE_DIR}/extern/macosx/)
ELSEIF(UNIX)
link_directories(${PROJECT_SOURCE_DIR}/extern/CentOS_x86_64/)
ELSEIF(WIN32)
link_directories(${PROJECT_SOURCE_DIR}/extern/Win_x86_64/)
ENDIF()

# ### Search Additional Libraries ##########
SET( CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake )
MESSAGE(${CMAKE_SOURCE_DIR})



FIND_PACKAGE(CXX11)
#FIND_PACKAGE(OpenCV)
FIND_PACKAGE(BISON)
FIND_PACKAGE(FLEX)


if(UNIX)
configure_file(${PROJECT_SOURCE_DIR}/configuration/RPcustomLOFTconfiglexer.l_unix ${CMAKE_CURRENT_BINARY_DIR}/RPcustomLOFTconfiglexer.l)
configure_file(${PROJECT_SOURCE_DIR}/configuration/RPcustomLOFTconfigparser.y_unix ${CMAKE_CURRENT_BINARY_DIR}/RPcustomLOFTconfigparser.y)
else(WIN32)
configure_file(${PROJECT_SOURCE_DIR}/configuration/RPcustomLOFTconfiglexer.l_win32 ${CMAKE_CURRENT_BINARY_DIR}/RPcustomLOFTconfiglexer.l)
configure_file(${PROJECT_SOURCE_DIR}/configuration/RPcustomLOFTconfigparser.y_win32 ${CMAKE_CURRENT_BINARY_DIR}/RPcustomLOFTconfigparser.y)
endif()



include_directories(${CMAKE_CURRENT_BINARY_DIR})

#if you do not have flex and bison installed then the slower nonunistd version will be used to parse files
#I have assumed that if you do not have Bison and Flex then you are on a non *nix system and hence this parser will be slower..only way to ensure full compatibility of types
if(BISON_FOUND AND FLEX_FOUND)
BISON_TARGET(LOFTConfigParser ${CMAKE_CURRENT_BINARY_DIR}/RPcustomLOFTconfigparser.y ${CMAKE_CURRENT_BINARY_DIR}/RPcustomLOFTconfigparser.cxx)
FLEX_TARGET(LOFTConfigScanner ${CMAKE_CURRENT_BINARY_DIR}/RPcustomLOFTconfiglexer.l ${CMAKE_CURRENT_BINARY_DIR}/RPcustomLOFTconfiglexer.cxx)
ADD_FLEX_BISON_DEPENDENCY(LOFTConfigScanner LOFTConfigParser)
SET(MU_SOURCE ${MU_SOURCE} ${CMAKE_CURRENT_BINARY_DIR}/RPcustomLOFTconfiglexer.l ${CMAKE_CURRENT_BINARY_DIR}/RPcustomLOFTconfigparser.y)
else()
MESSAGE("FLEX and BISON paths must be set to compile the system optimized parser..else the slower pre-compiled headers will be used")
configure_file(${PROJECT_SOURCE_DIR}/configuration/RPcustomLOFTconfiglexer.cxx_config.in ${CMAKE_CURRENT_BINARY_DIR}/RPcustomLOFTconfiglexer.cxx)
configure_file(${PROJECT_SOURCE_DIR}/configuration/RPcustomLOFTconfigparser.hxx_config.in ${CMAKE_CURRENT_BINARY_DIR}/RPcustomLOFTconfigparser.hxx)
configure_file(${PROJECT_SOURCE_DIR}/configuration/RPcustomLOFTconfigparser.cxx_config.in ${CMAKE_CURRENT_BINARY_DIR}/RPcustomLOFTconfigparser.cxx)
endif()



if(NOT WIN32)
  FIND_PACKAGE(X11)
  FIND_PACKAGE(Threads REQUIRED)
endif()

# #### End of additional libraries search ##########


### Configure Paths according to detected packages




if (OpenCV_FOUND)
  message("OpenCV Found")
  include_directories(${OpenCV_INCLUDE_DIRS})
  link_directories(${OpenCV_LIB_DIRS})
  SET( SYSTEM_LIBS  ${SYSTEM_LIBS}  ${OpenCV_LIBS} )
endif()



#Enable C++11 support 
if(CXX11_FOUND)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX11_FLAGS}")
endif()

if(CMAKE_COMPILER_IS_GNUCC)
  # needed for gcc 4.6+
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
endif()



SET(MU_SOURCE ${MU_SOURCE} main.cxx MUConfig_parser.cxx)

if(BISON_FOUND AND FLEX_FOUND)
add_executable (LOFTConfigParser ${BISON_LOFTConfigParser_OUTPUTS} ${FLEX_LOFTConfigScanner_OUTPUTS} ${MU_SOURCE} )
else()
add_executable(LOFTConfigParser ${MU_SOURCE} ${CMAKE_CURRENT_BINARY_DIR}/RPcustomLOFTconfigparser.cxx ${CMAKE_CURRENT_BINARY_DIR}/RPcustomLOFTconfiglexer.cxx)
endif()
target_link_libraries(LOFTConfigParser ${SYSTEM_LIBS} )




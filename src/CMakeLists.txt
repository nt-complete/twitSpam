cmake_minimum_required(VERSION 2.4)

set( twitSpam_SRCS twitSpam.cpp user.cpp tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp)
add_executable( twitSpam ${twitSpam_SRCS} )

target_link_libraries(twitSpam twitcurl)

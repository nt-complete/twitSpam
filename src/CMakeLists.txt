cmake_minimum_required(VERSION 2.4)

set( twitSpam_SRCS twitSpam.cpp user.cpp tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp)
set( curlURL_SRCS curlURL.cpp user.cpp tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp)
set( userData_SRCS userData.cpp user.cpp tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp)

add_executable( twitSpam ${twitSpam_SRCS} )
add_executable( curlURL ${curlURL_SRCS} )
add_executable( userData ${userData_SRCS} )


target_link_libraries(twitSpam twitcurl sqlite3)
target_link_libraries(curlURL twitcurl sqlite3)
target_link_libraries(userData twitcurl sqlite3)

project(singlyLinkedListLib)

set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib")#${CMAKE_BINARY_DIR}/lib write this from next time and not ${CMAKE_CURRENT_SOURCE_DIR}/lib

add_library(singlyLL SHARED SinglyLinkedList.c)

target_include_directories(singlyLL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#u can make two parts here, i.e include and src and then make the file, and if there are many like, bankaccount, creditcard, server, statemnt, make these folders and then put include and src in them

cmake_minimum_required(VERSION 2.8)

set(PROJECT osis_threads)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY result/bin)

project(PROJECT)

find_package(Threads)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set("${PROJECT}_SRC"
  osis_threads/main/src/main.c
  osis_threads/blob/src/blob.c
  osis_threads/queue/src/queue.c
  osis_threads/settings/src/settings.c
  osis_threads/threads/src/threads.c
)

if (UNIX)
set("${PROJECT}_PLATFORM"
  osis_threads/platform/src/linux/mutex.c 
  osis_threads/platform/src/linux/semaphore.c 
  osis_threads/platform/src/linux/osis_main.c 
)
endif(UNIX)

add_executable(${PROJECT} ${${PROJECT}_SRC} ${${PROJECT}_PLATFORM})

target_link_libraries(${PROJECT} ${CMAKE_THREAD_LIBS_INIT})

cmake_minimum_required(VERSION 3.9)
project(NewsSystem)
find_package(Threads)
set(CMAKE_CXX_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_executable(NewsSystem main.cpp Producer.cpp Producer.h Dispatcher.cpp Dispatcher.h CoEditor.cpp CoEditor.h ScreenManager.cpp ScreenManager.h BlockingQueue.h ProducerQueue.cpp ProducerQueue.h SortedNewsQueue.cpp SortedNewsQueue.h MThread.cpp MThread.h)
target_link_libraries(NewsSystem ${CMAKE_THREAD_LIBS_INIT})

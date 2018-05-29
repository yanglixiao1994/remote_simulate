cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
#SET(CMAKE_BUILD_TYPE "Debug")  


project(ue4_controller)

#set(PCL_DIR "/home/dev/dr-env/build/pcl/PCLConfig.cmake")
#set(VTK_DIR "D:/Program Files/PCL 1.8.1/3rdParty/VTK/lib/cmake/vtk-8.0" )
#message(${VTK_DIR})
#find_package(PCL 1.8.1 REQUIRED COMPONENTS common io registration segmentation visualization sample_consensus surface)

MESSAGE(${CMAKE_CURRENT_SOURCE_DIR})
find_package(PCL 1.8.1 REQUIRED)
find_package(VTK REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(ue4_controller main.cpp controller.cpp)
target_link_libraries(ue4_controller ${PCL_LIBRARIES})




















#add_executable(pcd_write_test pcd_write.cpp)
#target_link_libraries(pcd_write_test ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES})

#add_executable (conditional_euclidean_clustering conditional_euclidean_clustering.cpp)
#target_link_libraries (conditional_euclidean_clustering ${PCL_LIBRARIES})

#add_executable (example_region_growing example_region_growing.cpp)
#target_link_libraries (example_region_growing ${PCL_LIBRARIES})

#add_executable (aditya aditya.cpp)
#target_link_libraries (aditya ${PCL_LIBRARIES} ${OpenCV_LIBS})

#add_executable (mask mask.cpp)
#target_link_libraries (mask ${PCL_LIBRARIES} ${OpenCV_LIBS})

#add_executable (mask2 mask2.cpp)
#target_link_libraries (mask2 ${PCL_LIBRARIES} ${OpenCV_LIBS})



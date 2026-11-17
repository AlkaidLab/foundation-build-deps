cmake_minimum_required(VERSION 3.25)
project(ffmpeg_component_checks C)
enable_testing()
find_package(Threads REQUIRED)
set(FFMPEG_SOURCE_DIR "" CACHE PATH "Pinned FFmpeg source tree")
set(FFMPEG_BUILD_DIR "" CACHE PATH "Configured minimal FFmpeg build tree")
set(FFMPEG_CBS_LIBRARY "" CACHE FILEPATH "Optional separately built coded-bitstream archive")
option(EXPECT_SCOPED_BSFS "Require exactly the three metadata filters" ON)
add_executable(ffmpeg_component_smoke ffmpeg_component_smoke.c)
target_include_directories(ffmpeg_component_smoke PRIVATE "${FFMPEG_SOURCE_DIR}" "${FFMPEG_BUILD_DIR}")
target_compile_definitions(ffmpeg_component_smoke PRIVATE EXPECT_SCOPED_BSFS=$<BOOL:${EXPECT_SCOPED_BSFS}>)
target_link_libraries(ffmpeg_component_smoke PRIVATE
    ${FFMPEG_CBS_LIBRARY}
    "${FFMPEG_BUILD_DIR}/libavcodec/libavcodec.a"
    "${FFMPEG_BUILD_DIR}/libswscale/libswscale.a"
    "${FFMPEG_BUILD_DIR}/libavutil/libavutil.a" Threads::Threads ${CMAKE_DL_LIBS} m)
add_test(NAME ffmpeg_component_smoke COMMAND ffmpeg_component_smoke)

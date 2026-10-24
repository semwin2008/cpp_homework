# Собираем все .cpp только из папки utils
file(GLOB_RECURSE UTILS_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp")

add_executable(
    image_processor
    image_processor.cpp
    ${UTILS_SOURCES}
)
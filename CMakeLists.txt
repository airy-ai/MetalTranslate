cmake_minimum_required(VERSION 3.10)

project(MetalTranslate)

include(FetchContent)
FetchContent_Declare(CTranslate2
  GIT_REPOSITORY https://github.com/OpenNMT/CTranslate2.git
  GIT_TAG v2.19.1
)
FetchContent_MakeAvailable(CTranslate2)

FetchContent_Declare(OpenNMTTokenizer
  GIT_REPOSITORY https://github.com/OpenNMT/Tokenizer.git
  GIT_TAG v1.31.0
)
FetchContent_MakeAvailable(OpenNMTTokenizer)

add_executable(metaltranslate src/main.cpp)

set(TARGET_H
    src/MetalTranslate.h
    src/MetalTranslateConfig.h)

target_sources(metaltranslate PRIVATE src/MetalTranslate.cpp)

target_link_libraries(metaltranslate ctranslate2)

target_link_libraries(metaltranslate OpenNMTTokenizer)

cmake_minimum_required(VERSION 3.20)

project(GlowEngine_engine)

add_library(GlowEngine_engine
    ${PROJECT_SOURCE_DIR}/src/utils/Logger.cpp   
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_features(GlowEngine_engine PUBLIC cxx_std_20)


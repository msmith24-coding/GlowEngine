cmake_minimum_required(VERSION 3.20)

project(GlowEngine_sandbox)

add_executable(GlowEngine_sandbox
    ${PROJECT_SOURCE_DIR}/src/main.cpp    
)

target_link_libraries(GlowEngine_sandbox
    PRIVATE GlowEngine_engine    
)

target_compile_features(GlowEngine_sandbox PUBLIC cxx_std_20)

if(APPLE)
    set_target_properties(GlowEngine_sandbox PROPERTIES 
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
    )
elseif(WIN32) 
    set_target_properties(GlowEngine_sandbox PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

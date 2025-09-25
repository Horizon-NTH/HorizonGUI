add_executable(hgui-showcase
    main.cpp
)

target_compile_features(hgui-showcase PRIVATE cxx_std_20)

target_link_libraries(hgui-showcase PRIVATE horizongui)

target_include_directories(hgui-showcase PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

if (MSVC)
    target_compile_options(hgui-showcase PRIVATE /W4)
else ()
    target_compile_options(hgui-showcase PRIVATE -Wall -Wextra -Wpedantic)
endif ()

set_target_properties(hgui-showcase PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin"
)

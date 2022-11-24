FILE(GLOB TEST_FILES
    ${CMAKE_SOURCE_DIR}/test/*.c
    ${CMAKE_SOURCE_DIR}/test/test_scripts/*.c
)

add_executable(test_fake_access
    ${file}
    ${TEST_FILES}
    $<TARGET_OBJECTS:fakeAccess>
)
target_include_directories(test_fake_access PUBLIC
    ${CMAKE_SOURCE_DIR}/inc
)
enable_testing()
add_test(NAME test_fake_access COMMAND test_fake_access)
target_link_libraries(test_fake_access PUBLIC 
    m
    unity
    fff
)

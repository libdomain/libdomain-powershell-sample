set(TEST_NAME test-library)

set(SOURCES
    main.c
)

add_executable(${TEST_NAME} ${SOURCES})
target_link_libraries(${TEST_NAME} dl)

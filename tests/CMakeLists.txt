find_package(Catch2 3 REQUIRED)

add_executable(tests testTV.cpp ../CTVSet.cpp ../CTVSet.h ../InputHandler.cpp ../InputHandler.h testInputHandler.cpp)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

#add_custom_command(TARGET tests
#        POST_BUILD
#        COMMAND /bin/sh ${CMAKE_CURRENT_SOURCE_DIR}/test.sh
#        )

#add_custom_command(TARGET tests
#            POST_BUILD
#            COMMAND ../tests/tests
#        )
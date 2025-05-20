set(FINANCE_TRACKER_NAME FinanceTracker)

file(GLOB_RECURSE FINANCE_TRACKER_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
file(GLOB_RECURSE FINANCE_TRACKER_INCS ${CMAKE_CURRENT_LIST_DIR}/src/*.h)
file(GLOB_RECURSE FINANCE_TRACKER_INC_MODEL  ${CMAKE_CURRENT_LIST_DIR}/src/model/*.h)
file(GLOB_RECURSE FINANCE_TRACKER_INC_PROPERTY  ${CMAKE_CURRENT_LIST_DIR}/src/property/*.h)
file(GLOB_RECURSE FINANCE_TRACKER_COMMON_INCS ${CMAKE_CURRENT_LIST_DIR}/../common/include/*.h)
set(FINANCE_TRACKER_PLIST  ${CMAKE_CURRENT_LIST_DIR}/src/Info.plist)

file(GLOB FINANCE_TRACKER_TD ${MY_INC}/td/*.h)
file(GLOB FINANCE_TRACKER_CNT ${MY_INC}/cnt/*.h)
file(GLOB FINANCE_TRACKER_MU ${MY_INC}/mu/*.h)
file(GLOB FINANCE_TRACKER_FO ${MY_INC}/fo/*.h)
file(GLOB FINANCE_TRACKER_DP ${MY_INC}/dp/*.h)
file(GLOB FINANCE_TRACKER_XML ${MY_INC}/xml/*.h)
file(GLOB_RECURSE FINANCE_TRACKER_GUI ${MY_INC}/gui/*.h)

add_executable(${FINANCE_TRACKER_NAME} ${FINANCE_TRACKER_SOURCES} ${FINANCE_TRACKER_INCS} ${FINANCE_TRACKER_COMMON_INCS} ${FINANCE_TRACKER_TD}
        ${FINANCE_TRACKER_CNT} ${FINANCE_TRACKER_MU} ${FINANCE_TRACKER_FO} ${FINANCE_TRACKER_DP} ${FINANCE_TRACKER_XML} ${FINANCE_TRACKER_GUI}
        ${FINANCE_TRACKER_INC_MODEL} ${FINANCE_TRACKER_INC_PROPERTY})


add_compile_definitions(BUILD_PATH=\"${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/Transactions.xml\")
target_link_libraries(${FINANCE_TRACKER_NAME}
        debug ${MU_LIB_DEBUG} optimized ${MU_LIB_RELEASE}
        debug ${DP_LIB_DEBUG} optimized ${DP_LIB_RELEASE}
        debug ${NATGUI_LIB_DEBUG} optimized ${NATGUI_LIB_RELEASE}
)

#setTargetPropertiesForGUIApp(${FINANCE_TRACKER_NAME} ${FINANCE_TRACKER_PLIST})
#
setIDEPropertiesForGUIExecutable(${FINANCE_TRACKER_NAME} ${CMAKE_CURRENT_LIST_DIR})
#
setPlatformDLLPath(${FINANCE_TRACKER_NAME})

addMUCompileDefinitions(${FINANCE_TRACKER_NAME})


# Define the source directory (where files to copy are located)
#set(OTHER_BIN_DIR "C:/Users/Amer/other_bin")

# Recursively find all files (of any type)
file(GLOB_RECURSE ALL_OTHER_BIN_FILES "${MY_BIN}/*")

# Copy all files to the build output folder after build
foreach(FILE ${ALL_OTHER_BIN_FILES})
    add_custom_command(TARGET ${FINANCE_TRACKER_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${FILE}"
            $<TARGET_FILE_DIR:${FINANCE_TRACKER_NAME}>
    )
endforeach()

cmake_minimum_required(VERSION 3.18)

set(SOLUTION_NAME FinanceTracker)

project(${SOLUTION_NAME})

set(SOURCE_ROOT ${CMAKE_CURRENT_LIST_DIR})
set(HOME_ROOT $ENV{HOME})

if (WIN32)
    string(REPLACE "\\" "/" HOME_ROOT "${HOME_ROOT}")
endif ()

set(WORK_ROOT ${HOME_ROOT}/Work)

include(${WORK_ROOT}/DevEnv/Common.cmake)
include(FinanceTracker.cmake)

target_include_directories(${FINANCE_TRACKER_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/common/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

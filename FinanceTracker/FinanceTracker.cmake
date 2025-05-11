set(FINANCE_TRACKER_NAME FinanceTracker)

file(GLOB_RECURSE FINANCE_TRACKER_SOURCES  ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
file(GLOB_RECURSE FINANCE_TRACKER_INCS  ${CMAKE_CURRENT_LIST_DIR}/src/*.h)
file(GLOB_RECURSE FINANCE_TRACKER_COMMON_INCS  ${CMAKE_CURRENT_LIST_DIR}/../common/include/*.h)

file(GLOB FINANCE_TRACKER_TD  ${MY_INC}/td/*.h)
file(GLOB FINANCE_TRACKER_CNT  ${MY_INC}/cnt/*.h)
file(GLOB FINANCE_TRACKER_MU  ${MY_INC}/mu/*.h)
file(GLOB FINANCE_TRACKER_FO ${MY_INC}/fo/*.h)
file(GLOB FINANCE_TRACKER_DP ${MY_INC}/dp/*.h)
file(GLOB FINANCE_TRACKER_XML ${MY_INC}/xml/*.h)

add_executable(${FINANCE_TRACKER_NAME} ${FINANCE_TRACKER_SOURCES} ${FINANCE_TRACKER_INCS} ${FINANCE_TRACKER_COMMON_INCS} ${FINANCE_TRACKER_TD}
										${FINANCE_TRACKER_CNT} ${FINANCE_TRACKER_MU} ${FINANCE_TRACKER_FO} ${FINANCE_TRACKER_DP} ${FINANCE_TRACKER_XML}) 

#formatirati foldere u IDE.u
source_group("inc"            		FILES ${FINANCE_TRACKER_INCS})
source_group("inc\\common"  		FILES ${FINANCE_TRACKER_COMMON_INCS})

source_group("inc\\td"            	FILES ${FINANCE_TRACKER_TD})
source_group("inc\\cnt"            	FILES ${FINANCE_TRACKER_CNT})
source_group("inc\\mu"            	FILES ${FINANCE_TRACKER_MU})
source_group("inc\\fo"            	FILES ${FINANCE_TRACKER_FO})
source_group("inc\\dp"            	FILES ${FINANCE_TRACKER_DP})
source_group("inc\\xml"            	FILES ${FINANCE_TRACKER_XML})

source_group("src"   				FILES ${FINANCE_TRACKER_SOURCES})

#target_link_libraries(${FINANCE_TRACKER_NAME} ${MU_LIB_DEBUG})

target_link_libraries(${FINANCE_TRACKER_NAME} debug ${MU_LIB_DEBUG} optimized ${MU_LIB_RELEASE})

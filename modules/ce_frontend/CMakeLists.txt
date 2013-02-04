set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/CE)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(INC
	${INC_DIR}/AppFrontend.h
	${INC_DIR}/Canvas.h
	${INC_DIR}/ConfigFrontend.h
	${INC_DIR}/Event.h
	${INC_DIR}/Frontend.h
)

set(SRC
	${SRC_DIR}/AppFrontend.cpp
	${SRC_DIR}/Canvas.cpp
	${SRC_DIR}/Frontend.cpp
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set(FRONTEND_USEXLIB ${CE_FRONTEND_USEXLIB})
	set(FRONTEND_USEXCB ${CE_FRONTEND_USEXCB})
else(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set(FRONTEND_USEXLIB 0)
	set(FRONTEND_USEXCB 0)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	set(FRONTEND_USEWIN ${CE_FRONTEND_USEWIN})
else(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	set(FRONTEND_USEWIN "0")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

configure_file(include/CE/ConfigFrontend.h.in include/CE/ConfigFrontend.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/modules/ce_base/include ${PROJECT_SOURCE_DIR}/external/include)
add_library(ce_frontend STATIC ${SRC} ${INC} ${RES})
set_target_properties(ce_frontend PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
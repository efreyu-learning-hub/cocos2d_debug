set(MODULE_HEADER)
set(MODULE_SOURCE)
SET(GENERIC_DEBUG_MODULE_PATH  "${CMAKE_CURRENT_SOURCE_DIR}" CACHE INTERNAL "GENERIC_DEBUG_MODULE_PATH")
SET(GENERIC_LIB "${CMAKE_CURRENT_SOURCE_DIR}" CACHE INTERNAL "GENERIC_LIB")

file(GLOB_RECURSE MODULE_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE MODULE_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# remove sources from imgui submodule
foreach(source ${MODULE_HEADER})
    if("${source}" MATCHES "/imgui/")
        list(REMOVE_ITEM MODULE_HEADER "${source}")
    endif()
endforeach()
foreach(source ${MODULE_SOURCE})
    if("${source}" MATCHES "/imgui/")
        list(REMOVE_ITEM MODULE_SOURCE "${source}")
    endif()
endforeach()

# ImGui, included for debugging only
macro(initDebugModule)
    if (${DEBUG})
        SET(imgui_lib_path  "${GENERIC_DEBUG_MODULE_PATH}/imgui" CACHE INTERNAL "imgui_lib_path")
        include(${GENERIC_DEBUG_MODULE_PATH}/imgui/CMakeLists.txt)
        add_definitions(-DIMGUI_ENABLED)
        set(GENERIC_LIB cc_imgui)
    else ()
        set(GENERIC_LIB "")
    endif()
endmacro()

set(GAME_HEADER ${GAME_HEADER} ${MODULE_HEADER} PARENT_SCOPE)
set(GAME_SOURCE ${GAME_SOURCE} ${MODULE_SOURCE} PARENT_SCOPE)


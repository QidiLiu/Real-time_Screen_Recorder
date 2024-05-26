if(NOT OpenCV_FOUND)
    find_package(OpenCV CONFIG REQUIRED)

    if (OpenCV_FOUND)
        target_link_libraries(${MODULE_NAME} PUBLIC opencv::opencv)
    else()
        message("[ERROR] inih not found!")
    endif()
endif()

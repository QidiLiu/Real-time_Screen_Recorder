if(NOT inih_FOUND)
    find_package(inih CONFIG REQUIRED)

    if (inih_FOUND)
        target_link_libraries(${MODULE_NAME} PUBLIC inih::inih)
    else()
        message("[ERROR] inih not found!")
    endif()
endif()

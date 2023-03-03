file(GLOB 
    shaderFiles 
    "*.vert" "*.frag")

foreach(file ${shaderFiles})
    get_filename_component(fileName ${file} NAME)
    get_filename_component(fileNameWithoutExt ${fileName} NAME_WE)
    add_custom_command(
        OUTPUT ${fileNameWithoutExt}.spv
        COMMAND glslc ${file} -o ${CMAKE_CURRENT_BINARY_DIR}/${fileNameWithoutExt}.spv
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    )

    list(APPEND SHADERS_BINARIES ${CMAKE_CURRENT_BINARY_DIR}/${fileNameWithoutExt}.spv)
endforeach()


add_custom_target(Shaders
    DEPENDS ${SHADERS_BINARIES})

add_dependencies(vulpeslocis Shaders)

add_custom_command(TARGET Shaders POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/*.spv ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders)
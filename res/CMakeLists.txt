#add_custom_command(
#    OUTPUT toolkit.res
#    COMMAND
#        windres -i ${CMAKE_CURRENT_SOURCE_DIR}/toolkit.rc -o toolkit.res
#    DEPENDS
#        ${CMAKE_CURRENT_SOURCE_DIR}/toolkit.rc
#        ${CMAKE_CURRENT_SOURCE_DIR}/icon.ico
#    VERBATIM
#)
set(PLAYER_SRC player.cpp)

add_executable(player ${PLAYER_SRC})
target_link_libraries(player Common Renderer FFmpegDecoder)

install(TARGETS player DESTINATION bin)

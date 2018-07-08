add_library(Renderer toyRenderer.cpp toyRenderer.h)

include_directories("../Decoder")
target_link_libraries(Renderer glad glfw Decoder)

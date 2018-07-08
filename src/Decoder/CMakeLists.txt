add_library(Decoder BasicDecoder.cpp BasicDecoder.h)

target_link_libraries(Decoder avutil avcodec avformat swscale)

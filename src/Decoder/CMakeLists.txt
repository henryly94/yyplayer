add_library(Decoder BasicDecoder.cpp BasicDecoder.h)

add_library(FFmpegDecoder FFmpegDecoder.cpp FFmpegDecoder.h)

target_link_libraries(FFmpegDecoder avutil avcodec avformat swscale)

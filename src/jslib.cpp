#include "JpegLSDecode.hpp"

#include <emscripten.h>
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(JpegLSDecode) {
  class_<JpegLSDecode>("JpegLSDecode")
    .constructor<size_t, size_t>()
    .function("getSourceBytes", &JpegLSDecode::getSourceBytes)
    .function("getDestinationBytes", &JpegLSDecode::getDestinationBytes)
    .function("decode", &JpegLSDecode::decode)
    .function("getFrameInfo", &JpegLSDecode::getFrameInfo)
   ;
}

EMSCRIPTEN_BINDINGS(FrameInfo) {
  value_object<FrameInfo>("FrameInfo")
    .field("width", &FrameInfo::width)
    .field("height", &FrameInfo::height)
    .field("bitsPerSample", &FrameInfo::bitsPerSample)
    .field("componentCount", &FrameInfo::componentCount)
       ;
}


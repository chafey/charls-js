//#include <charls/charl.sh>
#include "../extern/charls/include/charls/charls.h"

#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>

using namespace emscripten;

class JpegLSDecode {
  public: 
  JpegLSDecode(size_t sourceSize, size_t destinationSize) {
    source.resize(sourceSize);
    destination.resize(destinationSize);
  }

  val getSourceBytes() {
    return val(typed_memory_view(source.size(), source.data()));
  }
  
  val getDestinationBytes() {
    return val(typed_memory_view(destination.size(), destination.data()));
  }

  void decode() {
    std::pair<charls::frame_info, charls::interleave_mode> result = charls::jpegls_decoder::decode(source, destination);
    // TODO: Return frame_info?
  }

  private:
    std::vector<unsigned char> source;
    std::vector<unsigned char> destination;
};

EMSCRIPTEN_BINDINGS(JpegLSDecode) {
  class_<JpegLSDecode>("JpegLSDecode")
    .constructor<size_t, size_t>()
    .function("getSourceBytes", &JpegLSDecode::getSourceBytes)
    .function("getDestinationBytes", &JpegLSDecode::getDestinationBytes)
    .function("decode", &JpegLSDecode::decode)
   ;
}

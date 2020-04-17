//#include <charls/charl.sh>
#include "../extern/charls/include/charls/charls.h"
#include <emscripten/val.h>

struct FrameInfo {
    /// <summary>
    /// Width of the image, range [1, 65535].
    /// </summary>
    uint32_t width;

    /// <summary>
    /// Height of the image, range [1, 65535].
    /// </summary>
    uint32_t height;

    /// <summary>
    /// Number of bits per sample, range [2, 16]
    /// </summary>
    int32_t bitsPerSample;

    /// <summary>
    /// Number of components contained in the frame, range [1, 255]
    /// </summary>
    int32_t componentCount;
};

class JpegLSDecode {
  public: 
  JpegLSDecode(size_t sourceSize, size_t destinationSize) {
    source.resize(sourceSize);
    destination.resize(destinationSize);
  }

  emscripten::val getSourceBytes() {
    return emscripten::val(emscripten::typed_memory_view(source.size(), source.data()));
  }
  
  emscripten::val getDestinationBytes() {
    return emscripten::val(emscripten::typed_memory_view(destination.size(), destination.data()));
  }

  void decode() {
    std::pair<charls::frame_info, charls::interleave_mode> result = charls::jpegls_decoder::decode(source, destination);
    frameInfo.width = result.first.width;
    frameInfo.height = result.first.height;
    frameInfo.bitsPerSample = result.first.bits_per_sample;
    frameInfo.componentCount = result.first.component_count;
  }

  const FrameInfo& getFrameInfo() const {
      return frameInfo;
  }

  private:
    std::vector<unsigned char> source;
    std::vector<unsigned char> destination;
    FrameInfo frameInfo;
};

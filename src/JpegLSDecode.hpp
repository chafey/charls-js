#pragma once
//#include <charls/charl.sh>
#include "../extern/charls/include/charls/charls.h"
#include <emscripten/val.h>
#include "Types.hpp"

class JpegLSDecode {
  public: 
  JpegLSDecode(size_t sourceSize, size_t destinationSize) {
    source_.resize(sourceSize);
    destination_.resize(destinationSize);
  }

  emscripten::val getSourceBytes() {
    return emscripten::val(emscripten::typed_memory_view(source_.size(), source_.data()));
  }
  
  emscripten::val getDestinationBytes() {
    return emscripten::val(emscripten::typed_memory_view(destination_.size(), destination_.data()));
  }

  void decode() {
    std::pair<charls::frame_info, charls::interleave_mode> result = charls::jpegls_decoder::decode(source_, destination_);
    frameInfo_.width = result.first.width;
    frameInfo_.height = result.first.height;
    frameInfo_.bitsPerSample = result.first.bits_per_sample;
    frameInfo_.componentCount = result.first.component_count;
  }

  const FrameInfo& getFrameInfo() const {
      return frameInfo_;
  }

  private:
    std::vector<unsigned char> source_;
    std::vector<unsigned char> destination_;
    FrameInfo frameInfo_;
};


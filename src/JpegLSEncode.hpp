#pragma once
//#include <charls/charl.sh>
#include "../extern/charls/include/charls/charls.h"
#include <emscripten/val.h>
#include "Types.hpp"

class JpegLSEncode {
  public: 
  JpegLSEncode(const FrameInfo& frameInfo) : 
    frameInfo_(frameInfo),
    interleaveMode_(charls::interleave_mode::none),
    nearLossless_(0) {
    const size_t bytesPerPixel = frameInfo_.bitsPerSample / 8;
    const size_t sourceSize = frameInfo_.width * frameInfo_.height * frameInfo_.componentCount * bytesPerPixel;
    source_.resize(sourceSize);
  }

  emscripten::val getSourceBytes() {
    return emscripten::val(emscripten::typed_memory_view(source_.size(), source_.data()));
  }
  
  emscripten::val getDestinationBytes() {
    return emscripten::val(emscripten::typed_memory_view(destination_.size(), destination_.data()));
  }

  void setNearLossless(int32_t nearLossless) {
    nearLossless_ = nearLossless;
  }

  void encode() {
        charls::jpegls_encoder encoder;
        encoder.near_lossless(nearLossless_);
        encoder.frame_info({frameInfo_.width, frameInfo_.height, frameInfo_.bitsPerSample, frameInfo_.componentCount})
            .interleave_mode(interleaveMode_);

        destination_.resize(encoder.estimated_destination_size());
        encoder.destination(destination_);

        const size_t bytes_written{encoder.encode(source_)};
        destination_.resize(bytes_written);
  }

  private:
    std::vector<unsigned char> source_;
    std::vector<unsigned char> destination_;
    FrameInfo frameInfo_;
    charls::interleave_mode interleaveMode_;
    int32_t nearLossless_;
};

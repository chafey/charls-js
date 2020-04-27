// Copyright (c) Team CharLS.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <charls/charls.h>

#include <emscripten/val.h>

#include "Types.hpp"

/// <summary>
/// JavaScript API for encoding images to JPEG-LS bistreams with CharLS
/// </summary>
class JpegLSEncode {
  public: 
  /// <summary>
  /// Constructor for encoding a JPEG-LS image from JavaScript.  Caller must
  /// pass in a FrameInfo object which describes the pixel data to be encoded. 
  /// </summary>
  /// <param name="frameInfo">FrameInfo that describes the pixel data to be encoded</param>
  JpegLSEncode(const FrameInfo& frameInfo) : 
    frameInfo_(frameInfo),
    interleaveMode_(charls::interleave_mode::none),
    nearLossless_(0) {
    const size_t bytesPerPixel = frameInfo_.bitsPerSample / 8;
    const size_t decodedSize = frameInfo_.width * frameInfo_.height * frameInfo_.componentCount * bytesPerPixel;
    decoded_.resize(decodedSize);
  }

  /// <summary>
  /// Returns a TypedArray of the buffer allocated in WASM memory space that
  /// will hold the pixel data to be encoded.  JavaScript code needs
  /// to copy the pixel data into the returned TypedArray.  This copy
  /// operation is needed because WASM runs in a sandbox and cannot access 
  /// data managed by JavaScript
  /// </summary>
  /// <returns>
  /// TypedArray for the buffer allocated in WASM memory space for the 
  /// source pixel data to be encoded.
  /// </returns>
  emscripten::val getDecodedBuffer() {
    return emscripten::val(emscripten::typed_memory_view(decoded_.size(), decoded_.data()));
  }
  
  /// <summary>
  /// Returns a TypedArray of the buffer allocated in WASM memory space that
  /// holds the encoded pixel data.
  /// </summary>
  /// <returns>
  /// TypedArray for the buffer allocated in WASM memory space for the 
  /// encoded pixel data.
  /// </returns>
  emscripten::val getEncodedBuffer() {
    return emscripten::val(emscripten::typed_memory_view(encoded_.size(), encoded_.data()));
  }

  /// <summary>
  /// Sets the NEAR parameter for the encoding.  The default value is 0 which
  /// is lossless.
  /// </summary>
  void setNearLossless(int32_t nearLossless) {
    nearLossless_ = nearLossless;
  }

  /// <summary>
  /// Executes an JPEG-LS encode using the data in the source buffer.  The
  /// JavaScript code must copy the source image frame into the source
  /// buffer before calling this method.  See documentation on getSourceBytes()
  /// above
  /// </summary>
  void encode() {
        charls::jpegls_encoder encoder;
        encoder.near_lossless(nearLossless_);
        encoder.frame_info({frameInfo_.width, frameInfo_.height, frameInfo_.bitsPerSample, frameInfo_.componentCount})
            .interleave_mode(interleaveMode_);

        encoded_.resize(encoder.estimated_destination_size());
        encoder.destination(encoded_);

        const size_t bytes_written{encoder.encode(decoded_)};
        encoded_.resize(bytes_written);
  }

  private:
    std::vector<unsigned char> decoded_;
    std::vector<unsigned char> encoded_;
    FrameInfo frameInfo_;
    charls::interleave_mode interleaveMode_;
    int32_t nearLossless_;
};

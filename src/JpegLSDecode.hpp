// Copyright (c) Team CharLS.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <charls/charls.h>

#include <emscripten/val.h>

#include "Types.hpp"

/// <summary>
/// JavaScript API for decoding JPEG-LS bistreams with CharLS
/// </summary>
class JpegLSDecode {
  public: 
  /// <summary>
  /// Constructor for decoding a JPEG-LS image from JavaScript.  Caller must
  /// pass in the size of the encoded JPEG-LS bitstream so the class can 
  /// allocate a buffer in WASM memory big enough to hold it
  /// </summary>
  JpegLSDecode(size_t encodedSize) {
    encoded_.resize(encodedSize);
  }

  /// <summary>
  /// Returns a TypedArray of the buffer allocated in WASM memory space that
  /// will hold the JPEG-LS encoded bitstream.  JavaScript code needs to copy
  /// the JPEG-LS encoded bistream into the returned TypedArray.  This copy 
  /// operation is needed because WASM runs in a sandbox and cannot access 
  /// memory managed by JavaScript.
  /// </summary>
  emscripten::val getEncodedBuffer() {
    return emscripten::val(emscripten::typed_memory_view(encoded_.size(), encoded_.data()));
  }
  
  /// <summary>
  /// Returns a TypedArray of the buffer allocated in WASM memory space that
  /// holds the decoded pixel data
  /// </summary>
  emscripten::val getDecodedBuffer() {
    return emscripten::val(emscripten::typed_memory_view(decoded_.size(), decoded_.data()));
  }

  /// <summary>
  /// Decodes the encoded JPEG-LS bitstream.  The caller must have copied the
  /// JPEG-LS encoded bitstream into the encoded buffer before calling this
  /// method, see getEncodedBuffer() above.
  /// </summary>
  void decode() {
    std::pair<charls::frame_info, charls::interleave_mode> result = charls::jpegls_decoder::decode(encoded_, decoded_);
    frameInfo_.width = result.first.width;
    frameInfo_.height = result.first.height;
    frameInfo_.bitsPerSample = result.first.bits_per_sample;
    frameInfo_.componentCount = result.first.component_count;
  }

  /// <summary>
  /// returns the FrameInfo object for the decoded image.
  /// </summary>
  const FrameInfo& getFrameInfo() const {
      return frameInfo_;
  }

  private:
    std::vector<unsigned char> encoded_;
    std::vector<unsigned char> decoded_;
    FrameInfo frameInfo_;
};


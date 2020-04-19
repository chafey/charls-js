#pragma once

struct FrameInfo {
    /// <summary>
    /// Width of the image, range [1, 65535].
    /// </summary>
    unsigned short width;

    /// <summary>
    /// Height of the image, range [1, 65535].
    /// </summary>
    unsigned short height;

    /// <summary>
    /// Number of bits per sample, range [2, 16]
    /// </summary>
    unsigned char bitsPerSample;

    /// <summary>
    /// Number of components contained in the frame, range [1, 255]
    /// </summary>
    unsigned char componentCount;
};
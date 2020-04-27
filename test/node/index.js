let charls = require('../../dist/charls-js.js');
const fs = require('fs')

function decode(pathToJPEGLSFile) {
  const encodedBitStream = fs.readFileSync(pathToJPEGLSFile);
  const decoder = new charls.JpegLSDecode(encodedBitStream.length);
  const encodedBuffer = decoder.getEncodedBuffer();
  encodedBuffer.set(encodedBitStream);

  // do the actual benchmark
  const iterations = 5;
  const beginDecode = process.hrtime();
  for(var i=0; i < iterations; i++) {
    decoder.decode();
  }
  const decodeDuration = process.hrtime(beginDecode); // hrtime returns seconds/nanoseconds tuple
  const decodeDurationInSeconds = (decodeDuration[0] + (decodeDuration[1] / 1000000000));
  
  // Print out information about the decode
  console.log("Decode took " + ((decodeDurationInSeconds / iterations * 1000)) + " ms");
  const frameInfo = decoder.getFrameInfo();
  console.log('frameInfo = ', frameInfo);
  var decoded = decoder.getDecodedBuffer();
  console.log('Decoded length = ', decoded.length);

  decoder.delete();
}

function encode(pathToUncompressedImageFrame, imageFrame) {
  const uncompressedImageFrame = fs.readFileSync(pathToUncompressedImageFrame);
  const encoder = new charls.JpegLSEncode(imageFrame);
  const decodedBytes = encoder.getDecodedBuffer();
  decodedBytes.set(uncompressedImageFrame);
  encoder.setNearLossless(0);

  const iterations = 5;
  const encodeBegin = process.hrtime();
  for(var i=0; i < iterations;i++) {
    encoder.encode();
  }
  const encodeDuration = process.hrtime(encodeBegin);
  const encodeDurationInSeconds = (encodeDuration[0] + (encodeDuration[1] / 1000000000));
  
  // print out information about the encode
  console.log("Encode took " + ((encodeDurationInSeconds / iterations * 1000)) + " ms");
  const encodedBytes = encoder.getEncodedBuffer();
  console.log('Encoded length=', encodedBytes.length)

  // cleanup allocated memory
  encoder.delete();
}

charls.onRuntimeInitialized = async _ => {

  decode('../fixtures/CT2_JLSL-imageFrame-0.dat');
  //decode('../fixtures/MG.dat');

  encode('../fixtures/ct2-frame.raw', {width: 512, height: 512, bitsPerSample: 16, componentCount: 1});
}

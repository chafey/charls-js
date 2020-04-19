let charls = require('../../dist/charls-js.js');
const fs = require('fs')

charls.onRuntimeInitialized = async _ => {
  // embind
  var source = fs.readFileSync('../fixtures/CT2_JLSL-imageFrame-0.dat');
  //var source = fs.readFileSync('../fixtures/MG.dat');
  var decoder = new charls.JpegLSDecode(source.length, 512*512*2);
  const sourceBytes = decoder.getSourceBytes();
  sourceBytes.set(source);

  // do a "warm up" decode
  decoder.decode();

  // now do the actual benchmark
  const iterations = 5;
  const beginDecode = process.hrtime();
  for(var i=0; i < iterations; i++) {
    decoder.decode();
  }
  const decodeDuration = process.hrtime(beginDecode); // hrtime returns seconds/nanoseconds tuple
  const decodeDurationInSeconds = (decodeDuration[0] + (decodeDuration[1] / 1000000000));
  console.log("Decode took " + ((decodeDurationInSeconds / iterations * 1000)) + " ms");

  const frameInfo = decoder.getFrameInfo();
  console.log('frameInfo = ', frameInfo);

  var decoded = decoder.getDestinationBytes();
  console.log('Eecoded length = ', decoded.length);
  
  const encoder = new charls.JpegLSEncode(frameInfo);
  const sourceBytesEncode = encoder.getSourceBytes();
  sourceBytesEncode.set(decoded);
  encoder.setNearLossless(0);
  const encodeBegin = process.hrtime();
  for(var i=0; i < iterations;i++) {
    encoder.encode();
  }
  const encodeDuration = process.hrtime(encodeBegin);
  const encodeDurationInSeconds = (encodeDuration[0] + (encodeDuration[1] / 1000000000));
  console.log("Encode took " + ((encodeDurationInSeconds / iterations * 1000)) + " ms");

  const encodedBytes = encoder.getDestinationBytes();
  console.log('Encoded length=', encodedBytes.length)

  encoder.delete();
  decoder.delete();
}

let modernLibrary = require('../../dist/charls-js.js');
const fs = require('fs')

modernLibrary.onRuntimeInitialized = async _ => {
  // embind
  var source = fs.readFileSync('../fixtures/CT2_JLSL-imageFrame-0.dat');
  var instance = new modernLibrary.JpegLSDecode(source.length, 512*512*2);
  const sourceBytes = instance.getSourceBytes();
  sourceBytes.set(source);

  // do initial decode to make sure WASM JIT is initialized
  instance.decode();

  const iterations = 100;
  const begin = process.hrtime();
  for(var i=0; i < iterations; i++) {
    instance.decode();
  }
  const duration = process.hrtime(begin); // hrtime returns seconds/nanoseconds tuple
  const durationInSeconds = (duration[0] + (duration[1] / 1000000000));
  console.log("Decode took " + ((durationInSeconds / iterations * 1000)) + " ms");

  var decoded = instance.getDestinationBytes();
  console.log('decoded length = ', decoded.length);
  //console.log(decoded);
  instance.delete();
}

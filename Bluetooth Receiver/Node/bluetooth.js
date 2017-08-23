var serialPort=require('serialport')
var fs=require('fs')
var port_name=process.argv[2]
var dataString=""
var dataRead=false

var BlueSMiRF = new serialPort(port_name, {
  baudRate: 9600,
  parity: "none",
  dataBits: 8,
  stopBits: 1
})

BlueSMiRF.on('open', function() {
  console.log("Port " + port_name + " opened.");
  BlueSMiRF.write("OK")
})

// timeout on message received. Send 'OK' signal
// if we haven't heard from bluetooth in a while
var timeout_wrapper=function(){
  return function(){
    BlueSMiRF.write("OK")
  }
}

BlueSMiRF.on('data', function(data) {
  clearTimeout(timeout)
  timeout=setTimeout(fn, 5000)
  dataString+=data.toString()
  if(dataRead){
    if(dataString.endsWith('\n')){
      fs.appendFile("data.txt", dataString, function(err){
        if(err){ return console.error(err)}
        dataString=""
        dataRead=false
        BlueSMiRF.write("OK")
      })
    }
  }
  else if(dataString=="s"){
    dataRead=true
    dataString=""
    BlueSMiRF.write("OK")
  }
  else if(dataString=="e"){
    BlueSMiRF.flush()
    BlueSMiRF.close()
  }
  else{
  }
})

var fn = timeout_wrapper()
var timeout=setTimeout(fn, 10000)

BlueSMiRF.on('error', function(err) {
  console.log(err);
});



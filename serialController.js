var portSelector = document.getElementById('portSelector');
var threshold = 0.3;
var port = null;
var writer = null;
var writerFunction = null;
var writableStreamClosed = null;

// function to connect to the serial port
async function connect() {
    if (document.getElementById('connect').textContent == 'Connect') {
        port = await navigator.serial.requestPort();
        var baudrate = document.getElementById('baudrate').value;
        console.log(baudrate);

        // open the port
        await port.open({ baudRate: parseInt(baudrate) });

        // rename the connect button to disconnect
        document.getElementById('connect').innerText = 'Disconnect';

        // if the serial port is connected, send data to the serial port every 100ms
        const textEncoder = new TextEncoderStream();
        writableStreamClosed = textEncoder.readable.pipeTo(port.writable);
        writer = textEncoder.writable.getWriter();
        writerFunction = setInterval(async () => {
            
            var data = "";
            if (axesValues[1] > threshold) {
                data = data+"r";
            }
            else if (axesValues[1] < -threshold) {
                data = data+"f";
            }
            else {
                data = data+"s";
            }

            if(axesValues2[1]>threshold){
                data = data+"r";
            }
            else if(axesValues2[1]<-threshold){
                data = data+"f";
            }
            else {
                data = data+"s";
            }

            if(btnValues[0]>threshold && btnValues2[0]>threshold){
                data = data+"s";
            }
            else if(btnValues[0]>threshold){
                data = data+"f";
            }
            else if(btnValues2[0]>threshold){
                data = data+"r";
            }
            else {
                data = data+"s";
            }

            console.log(data);
            await writer.write(data.toString());
        }, 60);
    }
    else {
        // stop sending data to the serial port
        clearInterval(writerFunction);
        
        writer.close();
        await writableStreamClosed;
        await port.close();
        document.getElementById('connect').innerText = 'Connect';
    }
}


// function to disconnect from the serial port
async function disconnect() {
  await port.close();
}


// function to read data from the serial port
async function read() {
  const reader = port.readable.getReader();
  while (true) {
    const { value, done } = await reader.read();
    if (done) {
      reader.releaseLock();
      break;
    }
    console.log(value);
  }
}





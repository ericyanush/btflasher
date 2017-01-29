var SegfaultHandler = require('segfault-handler');
SegfaultHandler.registerHandler("crash.log");
var flasher = require('./build/Debug/btflasher.node')
var scanner = flasher.Scanner()
var ports = ""

var flashBoard = function() {
    var flash = flasher.Flasher()
    flash.serialportName = ports[1].name
    flash.hexFile = "/Users/Eric/Developer/BrewTroller/build/src/BrewTroller-BT_PHOENIX_HERMS.hex"
    flash.loadConfigFile("/usr/local/Cellar/avrdude/6.2/etc/avrdude.conf")

    var progressHandler = function(percent, done, success) {
        if (done) {
            if (success) {
                console.log("Flash completed!");
            }
            else {
                console.log("Flash failed!");
            }
        }
        else {
            console.log("Flashing: " + percent + "% done");
        }
    }

    flash.flash(progressHandler);
}

scanner.enumeratePorts(function(result) { 
    console.log("Scanning done"); 
    ports = result; 
    flashBoard();
})

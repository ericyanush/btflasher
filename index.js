var binary = require('node-pre-gyp');
var path = require('path');
var flasher_path = binary.find(path.resolve(path.join(__dirname, './package.json')));
var btflasher = require(flasher_path);

module.exports = btflasher;
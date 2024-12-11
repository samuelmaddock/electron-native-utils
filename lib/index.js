const binary = require('@mapbox/node-pre-gyp');
const path = require('path');
const binding_path = binary.find(
  path.resolve(path.join(__dirname, '../package.json'))
);
const bindings = require(binding_path);

module.exports = bindings;

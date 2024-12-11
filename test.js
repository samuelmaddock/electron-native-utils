// Skip tests for cross-compiled builds
const targetArch = (process.argv.find(arg => arg.includes('--target_arch=')) || '').split('=')[1];
if (targetArch && targetArch !== process.arch) {
  console.log('Skipping tests for cross-compiled build.');
  process.exit(0);
}

const path = require('node:path');

// Test loading the native module
const electronUtils = require('./lib');

console.log('electronUtils', electronUtils);

const sleep = (time) => new Promise((resolve) => setTimeout(resolve, time));

async function main() {
  if (process.platform === 'darwin') {
    electronUtils.nativeInput.setMousePosition({ x: 100, y: 100 });
    await sleep(1000 / 60);
    electronUtils.nativeInput.click({ button: 'left' });
    electronUtils.nativeInput.click({ button: 'right' });
  }
}

main()

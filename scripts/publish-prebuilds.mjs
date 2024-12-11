import NodePreGypGithub from './node-pre-gyp-github.mjs';

async function main() {
  const preGyp = new NodePreGypGithub();
  await preGyp.publish();
}

main()

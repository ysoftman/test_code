import { createSheet } from './sheet.js';

// which mechanism: ?m=name (or examples/name in a scaffolded project), else <body data-mechanism>
const q = new URLSearchParams(location.search);
let name = q.get('m') || document.body.dataset.mechanism || 'engine';
if (!/^[a-z0-9_-]+(\/[a-z0-9_-]+)?$/i.test(name)) name = document.body.dataset.mechanism || 'engine';
const { default: mech } = await import(`./mechanisms/${name}.js`);
createSheet(mech);

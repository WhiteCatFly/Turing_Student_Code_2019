const electron = require('electron');
const app = electron.app;
const BrowserWindow = electron.BrowserWindow;

const path = require('path');
const isDev = require('electron-is-dev');
// const Store = require('electron-store');

let mainWindow;
// const store = new Store();

app.commandLine.appendSwitch('--enable-features', 'OverlayScrollbar');

function createWindow() {
  const conf = {
    width: 890,
    height: 556,
    webPreferences: {
      nodeIntegration: true,
      webSecurity: false,
      blinkFeatures: 'OverlayScrollbars'
    },
    show: false,
    resizable: false
  };

  if (process.platform == 'darwin') conf.titleBarStyle = 'hidden-inset';
  else conf.frame = false;

  mainWindow = new BrowserWindow(conf);
  mainWindow.loadURL(isDev ? 'http://localhost:3000' : `file://${path.join(__dirname, '/build/index.html')}`);
  if (isDev) {
    // Open the DevTools.
    // BrowserWindow.addDevToolsExtension(path.join(__dirname, '/extensions/react-devtools'));
    mainWindow.webContents.openDevTools();
  }
  mainWindow.on('closed', () => mainWindow = null);
  // mainWindow.on('resize', () => {
  //   const bounds = mainWindow.getBounds();
  //   store.set('windowSize.width', bounds.width);
  //   store.set('windowSize.height', bounds.height);
  // });

  mainWindow.removeMenu();
}

app.on('ready', createWindow);

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
  }
});

app.on('activate', () => {
  if (mainWindow === null) {
    createWindow();
  }
});

let ws = new WebSocket("ws://192.168.4.1/ws");
// let ws = new WebSocket("ws://demos.kaazing.com/echo");
ws.binaryType = 'arraybuffer';

let barVL = new ProgressBar.Path('#pathVL', { easing: 'easeInOut', duration: 140, });
let barVR = new ProgressBar.Path('#pathVR', { easing: 'easeInOut', duration: 140, });
let barHL = new ProgressBar.Path('#pathHL', { easing: 'easeInOut', duration: 140, });
let barHR = new ProgressBar.Path('#pathHR', { easing: 'easeInOut', duration: 140, });
barVL.set(0.1)
barVR.set(0.1)
barHL.set(0.1)
barHR.set(0.1)

let selectedControllerIndex = -1;
window.onload = function () {
  setInterval(controllerFunc, 100);
  updateControllerList();
};

//#region >>>> WebSocket
ws.onopen = (event) => {
  document.getElementById("wsState").innerHTML = "OPEN";
};

ws.onerror = (event) => {
  document.getElementById("wsState").innerHTML = "ERROR";
};

ws.onclose = (event) => {
  document.getElementById("wsState").innerHTML = "CLOSED";
};

ws.onmessage = function (event) {
  // console.log("WebSocket message received:", event);
  let dv = new DataView(event.data);
  let id = dv.getInt16(0, true);

  switch (id) {
    case 1: //gyro
      let a = [dv.getInt16(2, true), dv.getInt16(4, true), dv.getInt16(6, true)];
      let s = [dv.getInt16(8, true), dv.getInt16(10, true), dv.getInt16(12, true)];
      let r = [dv.getInt16(2, true), dv.getInt16(4, true), dv.getInt16(6, true)];

      document.getElementById("valAccelTotal").innerHTML = Math.sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]).toFixed(2);
      document.getElementById("valSpeedTotal").innerHTML = Math.sqrt(a[0] * s[0] + s[1] * s[1] + s[2] * s[2]).toFixed(2);
      document.getElementById("valRotTotal").innerHTML = Math.sqrt(r[0] * r[0] + r[1] * r[1] + r[2] * r[2]).toFixed(2);

      document.getElementById("valAccel").innerHTML = "[x: " + a[0] + ", y: " + a[1] + ", z: " + a[2] + "]";
      document.getElementById("valSpeed").innerHTML = "[x: " + s[0] + ", y: " + s[1] + ", z: " + s[2] + "]";
      document.getElementById("valRot").innerHTML = "[x: " + r[0] + ", y: " + r[1] + ", z: " + r[2] + "]";
      break;

    case 2: //battery
      let c1 = (dv.getInt16(2, true) / 4095 * 3.1 + .1) * 3;

      document.getElementById("valVolt").innerHTML = c1.toFixed(2);
      break;
    case 3: //motors
      const UPPER_LIMIT = 300;

      let vl = dv.getInt16(2, true) / (1023 * 4);
      let vr = dv.getInt16(4, true) / (1023 * 4);
      let hl = dv.getInt16(6, true) / (1023 * 4);
      let hr = dv.getInt16(8, true) / (1023 * 4);

      barVL.animate(vl);
      barVR.animate(vr);
      barHL.animate(hl);
      barHR.animate(hr);
      break;

    case 4: //gyroBatComb
      let s1 = [dv.getInt16(2, true), dv.getInt16(4, true), dv.getInt16(6, true)];
      let a1 = [dv.getInt16(8, true) / 16384.0, dv.getInt16(10, true) / 16384.0, dv.getInt16(12, true) / 16384.0];
      let r1 = [dv.getInt16(14, true) / 250.0, dv.getInt16(16, true) / 250.0, dv.getInt16(18, true) / 250.0];


      document.getElementById("valAccelTotal").innerHTML = Math.sqrt(a1[0] * a1[0] + a1[1] * a1[1] + a1[2] * a1[2]).toFixed(2);
      document.getElementById("valSpeedTotal").innerHTML = Math.sqrt(s1[0] * s1[0] + s1[1] * s1[1] + s1[2] * s1[2]).toFixed(2);
      document.getElementById("valRotTotal").innerHTML = Math.sqrt(r1[0] * r1[0] + r1[1] * r1[1] + r1[2] * r1[2]).toFixed(2);

      document.getElementById("valAccel").innerHTML = "[x: " + a1[0].toFixed(2) + ", y: " + a1[1].toFixed(2) + ", z: " + a1[2].toFixed(2) + "]";
      document.getElementById("valSpeed").innerHTML = "[x: " + s1[0].toFixed(2) + ", y: " + s1[1].toFixed(2) + ", z: " + s1[2].toFixed(2) + "]";
      document.getElementById("valRot").innerHTML = "[x: " + r1[0].toFixed(2) + ", y: " + r1[1].toFixed(2) + ", z: " + r1[2].toFixed(2) + "]";

      let bat = (dv.getInt16(20, true) / 4095 * 3.1 + .1) * 3;
      let temp = dv.getInt16(22, true) / 340.0 + 36.53;

      document.getElementById("valVolt").innerHTML = bat.toFixed(2);
      document.getElementById("valTemp").innerHTML = temp.toFixed(2);
      break;

    default:
      break;
  }
};

//#endregion

//#region >>>> Controller
window.addEventListener("gamepadconnected", (event) => {
  console.log("A gamepad connected:");
  console.log(event.gamepad);

  updateControllerList();
});

window.addEventListener("gamepaddisconnected", (event) => {
  console.log("A gamepad disconnected:");
  console.log(event.gamepad);


  updateControllerList();
});



// Lets the user select which connected controller to use
function updateControllerList() {
  let inner = ""

  let pads = navigator.getGamepads();
  console.log(pads);

  for (let i = 0; i < pads.length; i++) {
    const element = pads[i];
    if (element === null)
      continue;
    if (selectedControllerIndex == i) {
      inner += "<li onclick=\"onControllerSelected(" + i + ")\"><strong>" + element.id + "</strong></li>";
    } else {
      inner += "<li onclick=\"onControllerSelected(" + i + ")\">" + element.id + "</li>";
    }
  }

  document.getElementById("controllerList").innerHTML = inner;
}

// gets called when a Controller gets selected in the List
function onControllerSelected(index) {
  selectedControllerIndex = index;
  updateControllerList();
}


let lastX1 = 0, lastX2 = 0, lastY1 = 0, lastY2 = 0;
function controllerFunc() {
  if (!document.getElementById("controllerEnabled").checked)
    return;

  let pads = navigator.getGamepads();
  if (pads === null || pads[2] === null)
    return;
  x1 = Math.floor(pads[2].axes[0] * 1023);
  y1 = -Math.floor(pads[2].axes[1] * 1023);
  x2 = Math.floor(pads[2].axes[2] * 1023);
  y2 = -Math.floor(pads[2].axes[3] * 1023);

  if (lastX1 != x1 || lastY1 != y1 || lastX2 != x2 || lastY2 != y2) {
    console.log(x1 + ", " + y1 + " : " + x2 + ", " + y2);
    if (ws.readyState == WebSocket.OPEN) {
      let buf = new Int16Array([0, x1, y1, x2, y2])
      ws.send(buf);
    }
    lastX1 = x1;
    lastX2 = x2;
    lastY1 = y1;
    lastY2 = y2;
  }

}
//#endregion

//#region >>>> Keyboard Control
let dirX = 0;
let dirY = 0;
let rotX = 0;
//a: 65, s: 83, d:68, w:87
document.addEventListener('keydown', function (event) {
  let c = event.keyCode;
  switch (event.keyCode) {
    case 65:
      dirX = -1;
      break;
    case 68:
      dirX = 1;
      break;
    case 87:
      dirY = 1;
      break;
    case 83:
      dirY = -1;
      break;
    case 39:
      rotX = 1;
      break;
    case 37:
      rotX = -1;
      break;
    case 27:
      dirY = 0;
      dirX = 0;
      break;
    default:
      break;
  }

  if (lastX1 != dirX * 1023 || lastY1 != dirY * 1023 || lastX2 != rotX * 1023 || lastY2 != 0) {
    console.log(dirX * 1023 + ", " + dirY * 1023 + " : " + rotX * 1023 + ", " + 0);
    if (ws.readyState == WebSocket.OPEN) {
      let buf = new Int16Array([0, dirX * 1023, dirY * 1023, rotX * 1023, 0])
      ws.send(buf);
    }
    lastX1 = dirX * 1023;
    lastY1 = dirY * 1023;
    lastX2 = rotX * 1023;
    lastY2 = 0;
  }

  // console.log("x: " + dirX + " y: " + dirY);
});

document.addEventListener('keyup', function (event) {
  let c = event.keyCode;
  switch (event.keyCode) {
    case 65:
    case 68:
      dirX = 0;
      break;
    case 87:
    case 83:
      dirY = 0;
      break;
    case 39:
    case 37:
      rotX = 0;
      break;
    default:
      break;
  }
  console.log("x: " + dirX + " y: " + dirY);

  if (lastX1 != dirX * 1023 || lastY1 != dirY * 1023 || lastX2 != rotX * 1023 || lastY2 != 0) {
    console.log(dirX * 1023 + ", " + dirY * 1023 + " : " + rotX * 1023 + ", " + 0);
    if (ws.readyState == WebSocket.OPEN) {
      let buf = new Int16Array([0, dirX * 1023, dirY * 1023, rotX * 1023, 0])
      ws.send(buf);
    }
    lastX1 = dirX * 1023;
    lastY1 = dirY * 1023;
    lastX2 = rotX * 1023;
    lastY2 = 0;
  }
});
//#endregion

function sendSpeed() {
  console.log("speed");
  let arr = new Int16Array([2, Math.random() * 4048, Math.random() * 4048]);
  let arr2 = new Int16Array([1,
    Math.random() * 1023, Math.random() * 1023, Math.random() * 1023,
    Math.random() * 1023, Math.random() * 1023, Math.random() * 1023,
    Math.random() * 1023, Math.random() * 1023, Math.random() * 1023]);
  ws.send(arr);
  ws.send(arr2);
}
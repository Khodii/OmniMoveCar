let ws = new WebSocket("ws://192.168.4.1/ws");
let selectedControllerIndex = -1;
window.onload = function () {
  setInterval(controllerFunc, 100);
  updateControllerList();
};


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
  console.debug("WebSocket message received:" + event);
};


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

function myFunction() {
  console.log("Test");
  ws.send("Hallo");
}

function sendSpeed() {
  console.log("speed");
  arr = new Int16Array([0, -10, 10]);
  ws.send(arr);
}
define((require) => {
    const Robot = require('Robot')
    const Robot2 = require('Robot2')
    var socket;

    var angleValuesRobot1 = [0, 0, 0, 0, 0, 0]
    var angleValuesRobot2 = [0, 0, 0, 0, 0, 0]
    var lastAngleNoRobot1 = -1;
    var lastAngleNoRobot2 = -1;
    window.onpageshow = function () {
        socket = new WebSocket("ws://localhost:8080/websocket/1")
        console.log("ws socket");
        socket.onopen = function () {
            console.log("ws open")
        }
        socket.onmessage = function (msg) {
            console.log(msg.data)
            JSONObj = JSON.parse(msg.data);
            if (JSONObj.robotNo == 1) {
                console.log("ROBOT1 CHANGED")
                angleValuesRobot1[JSONObj.angleNo-1] = JSONObj.angleValue;
                if (JSONObj.angleNo <= lastAngleNoRobot1) {
                    Robot.dispatch('ROBOT_CHANGE_ANGLES', {
                        A0: angleValuesRobot1[0],
                        A1: angleValuesRobot1[1],
                        A2: angleValuesRobot1[2],
                        A3: angleValuesRobot1[3],
                        A4: angleValuesRobot1[4],
                        A5: angleValuesRobot1[5],
                    })
                }
                lastAngleNoRobot1 = JSONObj.angleNo
            } else if (JSONObj.robotNo == 2) {
                console.log("ROBOT2 CHANGED")
                angleValuesRobot2[JSONObj.angleNo-1] = JSONObj.angleValue;
                if (JSONObj.angleNo <= lastAngleNoRobot2) {
                    Robot2.dispatch('ROBOT_CHANGE_ANGLES', {
                        A0: angleValuesRobot2[0],
                        A1: angleValuesRobot2[1],
                        A2: angleValuesRobot2[2],
                        A3: angleValuesRobot2[3],
                        A4: angleValuesRobot2[4],
                        A5: angleValuesRobot2[5],
                    })
                }
                lastAngleNoRobot2 = JSONObj.angleNo
            }

        }
        socket.onclose = function () {
            socket.send("CLOSE")
            console.log("ws close")
        }
        socket.onerror = function () {
            console.log("ws error")
        }
    }

    window.onpagehide = function () {
        socket.close()
    }
})
define((require) => {
    const Robot = require('Robot')
    const Robot2 = require('Robot2')
    var socket;

    var angleValues = [0, 0, 0, 0, 0, 0]
    var lastAngleNo = -1;
    window.onpageshow = function () {
        socket = new WebSocket("ws://localhost:8080/websocket/1")
        console.log("ws socket");
        socket.onopen = function () {
            console.log("ws open")
            // for (i = 0; i < 10; i++) {
            //     let j = i;
            //     setTimeout(function () {
            //         Robot.dispatch('ROBOT_CHANGE_ANGLES', {
            //             A0: 0,
            //             A1: j / 10.0,
            //             A2: 0,
            //             A3: 0,
            //             A4: 0,
            //             A5: 0,
            //         })
            //     }, 1000 * j)
            // }
        }
        socket.onmessage = function (msg) {
            console.log(msg.data)
            JSONObj = JSON.parse(msg.data);
            if (JSONObj.robotNo == 1) {
                console.log("ROBOT1 CHANGED")
                angleValues[JSONObj.angleNo-1] = JSONObj.angleValue;
                if (JSONObj.angleNo <= lastAngleNo) {
                    Robot.dispatch('ROBOT_CHANGE_ANGLES', {
                        A0: angleValues[0],
                        A1: angleValues[1],
                        A2: angleValues[2],
                        A3: angleValues[3],
                        A4: angleValues[4],
                        A5: angleValues[5],
                    })
                }
                lastAngleNo = JSONObj.angleNo
            } else if (JSONObj.robotNo == 2) {
                console.log("ROBOT2 CHANGED")
                angleValues[JSONObj.angleNo-1] = JSONObj.angleValue;
                Robot2.dispatch('ROBOT_CHANGE_ANGLES', {
                    A0: angleValues[0] / 10.0,
                    A1: angleValues[1] / 10.0,
                    A2: angleValues[2] / 10.0,
                    A3: angleValues[3] / 10.0,
                    A4: angleValues[4] / 10.0,
                    A5: angleValues[5] / 10.0,
                })
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
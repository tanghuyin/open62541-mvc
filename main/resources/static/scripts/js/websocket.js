define((require) => {
    const Robot = require('Robot')
    const Robot2 = require('Robot2')
    var socket;

    var angleValuesRobot1 = [0, 0, 0, 0, 0, 0]
    var angleValuesRobot2 = [0, 0, 0, 0, 0, 0]
    var lastAngleNoRobot1 = -1;
    var lastAngleNoRobot2 = -1;
    var lastJobNumRobot1 = 0;
    var lastJobNumRobot2 = 0;
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
                if (JSONObj.robotJobNum != null) {
                    console.log(JSONObj.robotJobNum)
                    // $("#robot1_job_num").html(JSONObj.robotJobNum)
                    var ul1=document.getElementById("ul1");
                    var pos = ul1.getBoundingClientRect();
                    $("#ul1").empty()
                    for(var i=0;i<parseInt(JSONObj.robotJobNum);i++){
                        var li1=document.createElement("li");
                        li1.style.left=pos.left+i%20*64+"px";
                        li1.style.top=pos.bottom+parseInt(i/20)*64+"px";  // 实现换行
                        li1.innerHTML=i+1;
                        li1.style.background="#228B22";
                        ul1.appendChild(li1);
                    }
                    if (JSONObj.robotJobNum < lastJobNumRobot1) {
                        $("table#completedOrderList tr:last").after('<tr><td>1</td><td>'+date.toLocaleString()+'</td><td>1</td></tr>')
                    }
                    lastJobNumRobot1 = JSONObj.robotJobNum;
                }
                else if (JSONObj.robotStatus != null) {
                    console.log(JSONObj.robotStatus)
                    if (JSONObj.robotStatus == false) {
                        $("#robot1_S").html("故障");
                        $("#robot1_S").css('color', 'red');
                    } else {
                        $("#robot1_S").html("正常");
                        $("#robot1_S").css('color', 'green');
                    }
                } else {
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
                }
            } else if (JSONObj.robotNo == 2) {
                if (JSONObj.robotJobNum != null) {
                    console.log(JSONObj.robotJobNum)
                    // $("#robot2_job_num").html(JSONObj.robotJobNum)
                    var ul2=document.getElementById("ul2");
                    var pos = ul2.getBoundingClientRect();
                    $("#ul2").empty()
                    for(var i=0;i<parseInt(JSONObj.robotJobNum);i++){
                        var li1=document.createElement("li");
                        li1.style.left=pos.left+i%20*64+"px";
                        li1.style.top=pos.bottom+parseInt(i/20)*64+"px";  // 实现换行
                        li1.innerHTML=i+1;
                        li1.style.background="#228B22";
                        ul2.appendChild(li1);
                    }
                    if (JSONObj.robotJobNum < lastJobNumRobot2) {
                        $("table#completedOrderList tr:last").after('<tr><td>2</td><td>'+date.toLocaleString()+'</td><td>1</td></tr>')
                    }
                    lastJobNumRobot2 = JSONObj.robotJobNum;
                }
                else if (JSONObj.robotStatus != null) {
                    console.log(JSONObj.robotStatus)
                    if (JSONObj.robotStatus == false) {
                        $("#robot2_S").html("故障");
                        $("#robot2_S").css('color', 'red');
                    } else {
                        $("#robot2_S").html("正常");
                        $("#robot2_S").css('color', 'green');
                    }
                } else {
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

    function random_load(){
        var R=hao(0,255).toString(16);
        var G=hao(0,255).toString(16);
        var B=hao(0,255).toString(16);
        return "#"+aaa(R,G,B);
    }
    function hao(min,max){
        return parseInt(Math.random()*(max-min+1)+min)
    }
    function aaa(r,g,b){
        r=r.length==1?"0"+r:r;
        g=g.length==1?"0"+g:g;
        b=b.length==1?"0"+b:b;    //随机会获取到5位的十六进制数，不能作为颜色值，所以用这个方法解决，还请前辈多多指点  ^-^！
        return r+g+b;
    }
})
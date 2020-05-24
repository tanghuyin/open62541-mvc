define(() => {
    let no = 1;
    $(".connectServer").click(function () {
        connectServer()
    })

    function connectServer() {
        $.ajax({
            type: "GET",
            contentType: "html",
            url: "/connectServer",
            success: function (msg) {
                if (msg == "success") {
                    alert("成功连接ua服务端")
                    $("#uaStatus").css('background', 'green')
                } else {
                    alert("连接ua服务端失败")
                }
            }
        })
    }

    $(".createSubscription").click(function () {
        createSubscription();
    })

    function createSubscription() {
        $.ajax({
            type: "GET",
            contentType: "html",
            url: "/createSubscription",
            success: function (msg) {
                if (msg == "success") {
                    alert("订阅关节值成功")
                } else {
                    alert("订阅关节值失败")
                }
            }
        })
    }


    function assign(jobNum, robotNo) {
        $.ajax({
            type: "GET",
            contentType: "html",
            url: "/assignWork?robotId=" + robotNo + "&jobNum="+jobNum,
            success: function (msg) {

            }
        })
    }

    $(".assign").click(function () {
        var jobNum = document.getElementById("newJobNumRobot");
        var robotNo = document.getElementById("selectRobot");
        assign(jobNum.value, robotNo.value)
        var date = new Date();
        $("table#orderList tr:last").after('<tr><td>'+ no++ +'</td><td>'+ date.toLocaleString() +'</td><td>机器人' + robotNo.value + '</td><td>'+ jobNum.value)
    })

    $(".robot1Fail").click(function () {
        $('#orderList tr').each(function (i) {
            var r = $(this).find('td:eq(2)').text();
            if (r == '机器人1') {
                $(this).children('td:eq(4)').html('机器人2');
            }
        })
        robot1Fail();
    })
    function robot1Fail() {
        $.ajax({
            type: "GET",
            contentType: "html",
            url: "/robotFail?robotId=1",
            success: function (msg) {

            }
        })
    }

    $(".robot2Fail").click(function () {
        $('#orderList tr').each(function (i) {
            var r = $(this).find('td:eq(2)').text();
            if (r == '机器人2') {
                $(this).children('td:eq(4)').html('机器人1');
            }
        })
        robot2Fail();
    })
    function robot2Fail() {
        $.ajax({
            type: "GET",
            contentType: "html",
            url: "/robotFail?robotId=2",
            success: function (msg) {

            }
        })
    }
})
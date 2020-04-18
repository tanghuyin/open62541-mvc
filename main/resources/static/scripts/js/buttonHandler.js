define(() => {
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

    $(".assignFirst").click(function () {
        assignFirst();
    })

    function assignFirst() {
        $.ajax({
            type: "GET",
            contentType: "html",
            url: "/assignWork?robotId=1",
            success: function (msg) {

            }
        })
    }

    $(".assignSecond").click(function () {
        assignSecond();
    })

    function assignSecond() {
        $.ajax({
            type: "GET",
            contentType: "html",
            url: "/assignWork?robotId=2",
            success: function (msg) {

            }
        })
    }
})
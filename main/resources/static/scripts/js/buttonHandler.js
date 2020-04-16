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
})
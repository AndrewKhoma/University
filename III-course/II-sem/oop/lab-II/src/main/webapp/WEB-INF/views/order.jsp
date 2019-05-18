<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Orders</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/uikit/3.1.4/css/uikit.min.css"/>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/uikit/3.1.4/js/uikit.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/uikit/3.1.4/js/uikit-icons.min.js"></script>
</head>
<body>

<section class="uk-section">
    <div class="uk-container">
        <table class="uk-table uk-table-hover uk-table-divider uk-table-striped">
            <thead>
            <tr>
                <td>ID</td>
                <td>User Id</td>
                <td>Agent Id</td>
                <td>Tour id</td>
                <td>Cost</td>
            </tr>
            </thead>
            <tbody>
            <%--@elvariable id="orders" type="java.util.List"--%>
            <c:forEach var="order" items="${orders}">
                <tr>
                    <td>${order.getId()}</td>
                    <td>${order.getUserId()}</td>
                    <td>${order.getAgentId()}</td>
                    <td>${order.getTourId()}</td>
                    <td>${order.getCost()}</td>
                </tr>
            </c:forEach>
            </tbody>
        </table>
    </div>
</section>

<section class="uk-section">
    <div class="uk-container">
        <form action="<c:url value="/order"/>" class="uk-form-horizontal" method="POST">

            <div class="uk-margin">
                <label class="uk-form-label" for="user_id">User id:</label>
                <div class="uk-form-controls">
                    <input class="uk-input" id="user_id" type="text" name="user_id"
                           value="${cookie.get("userid").value}" readonly>
                </div>
            </div>

            <div class="uk-margin">
                <label class="uk-form-label" for="agent_id">Agent id:</label>
                <div class="uk-form-controls">
                    <input class="uk-input" id="agent_id" type="text" name="agent_id"
                           placeholder="Agent id...">
                </div>
            </div>

            <div class="uk-margin">
                <label class="uk-form-label" for="tour_id">Tour id:</label>
                <div class="uk-form-controls">
                    <input class="uk-input" id="tour_id" type="text" name="tour_id"
                           placeholder="Tour id...">
                </div>
            </div>

            <div class="uk-margin">
                <label class="uk-form-label" for="cost">Cost:</label>
                <div class="uk-form-controls">
                    <input class="uk-input" id="cost" type="text" name="cost"
                           placeholder="Cost...">
                </div>
            </div>

            <div class="uk-margin">
                <button class="uk-button uk-button-default" type="submit">Submit</button>
            </div>
        </form>
    </div>

    <div class="uk-container">
        <a href="index.jsp">Home</a>
    </div>
</section>


</body>
</html>

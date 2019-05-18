<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<%@ page contentType="text/html;charset=UTF-8" %>
<html>
<head>
    <title>Tours</title>
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
                <td>Tour Name</td>
                <td>Tour description</td>
                <td>Tour agency id</td>
                <td>Tour cost</td>
            </tr>
            </thead>
            <tbody>
            <%--@elvariable id="tours" type="java.util.List"--%>
            <c:forEach var="tour" items="${tours}">
                <tr>
                    <td>${tour.getId()}</td>
                    <td>${tour.getName()}</td>
                    <td>${tour.getDescription()}</td>
                    <td>${tour.getAgency()}</td>
                    <td>${tour.getCost()}</td>

                </tr>
            </c:forEach>
            </tbody>
        </table>
    </div>
</section>

<section class="uk-section">
    <div class="uk-container">
        <form action="<c:url value="/tour"/>" class="uk-form-horizontal" method="POST">

            <div class="uk-margin">
                <label class="uk-form-label" for="tour_name">Tour name:</label>
                <div class="uk-form-controls">
                    <input class="uk-input" id="tour_name" type="text" name="tour_name"
                           placeholder="Tour name...">
                </div>
            </div>

            <div class="uk-margin">
                <label class="uk-form-label" for="tour_description">Tour description:</label>
                <div class="uk-form-controls">
                    <input class="uk-input" id="tour_description" type="text" name="tour_description"
                           placeholder="Tour description...">
                </div>
            </div>

            <div class="uk-margin">
                <label class="uk-form-label" for="tour_agency">Tour agency id:</label>
                <div class="uk-form-controls">
                    <input class="uk-input" id="tour_agency" type="text" name="tour_agency"
                           placeholder="Tour agency id...">
                </div>
            </div>

            <div class="uk-margin">
                <label class="uk-form-label" for="tour_cost">Tour cost:</label>
                <div class="uk-form-controls">
                    <input class="uk-input" id="tour_cost" type="text" name="tour_cost"
                           placeholder="Tour cost...">
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

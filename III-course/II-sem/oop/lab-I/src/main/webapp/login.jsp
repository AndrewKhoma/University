<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<%@ page contentType="text/html;charset=UTF-8" %>
<html>
<head>
    <title>Welcome</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="css/uikit.min.css"/>
    <script src="js/uikit.min.js"></script>
    <script src="js/uikit-icons.min.js"></script>
</head>
<body>
<section class="uk-section">
    <div class="uk-container">
        <h2 class="uk-heading-medium uk-text-center">Login or register</h2>
    </div>
</section>


<div class="uk-container">
    <form action="<c:url value="/login"/>" class="uk-form-horizontal uk-position-center" method="POST">

        <div class="uk-margin">
            <div class="uk-inline">
                <%--suppress HtmlUnknownAttribute --%>
                <span class="uk-form-icon" uk-icon="icon: user"></span>
                <%--suppress HtmlFormInputWithoutLabel --%>
                <input class="uk-input" type="text" name="name">
            </div>
        </div>

        <div class="uk-margin">
            <div class="uk-inline">
                <%--suppress HtmlUnknownAttribute --%>
                <span class="uk-form-icon uk-form-icon-flip" uk-icon="icon: lock"></span>
                <%--suppress HtmlFormInputWithoutLabel --%>
                <input class="uk-input" type="text" name="password">
            </div>
        </div>

        <button class="uk-button uk-button-default" type="submit">Submit</button>
    </form>
</div>

</body>
</html>

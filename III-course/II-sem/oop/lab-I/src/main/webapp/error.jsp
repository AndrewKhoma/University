<%@ page import="static javax.servlet.RequestDispatcher.ERROR_MESSAGE" %>
<%@ page contentType="text/html;charset=UTF-8" %>
<!doctype html>
<html>
<head>
    <title>Error</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="css/uikit.min.css"/>
    <script src="js/uikit.min.js"></script>
    <script src="js/uikit-icons.min.js"></script>
    <link href="css/main.css" rel="stylesheet">
</head>
<body>
<section class="uk-section">
    <div class="uk-container">
        <div class="uk-text-danger uk-text-center">
            <%=request.getAttribute(ERROR_MESSAGE)%>
        </div>
    </div>
</section>
</body>
</html>


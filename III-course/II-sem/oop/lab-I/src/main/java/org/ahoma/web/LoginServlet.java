package org.ahoma.web;

import org.ahoma.config.BeanFactory;
import org.ahoma.data.User;
import org.ahoma.service.UserService;

import javax.servlet.ServletException;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class LoginServlet extends HttpServlet {
  private UserService service = (UserService) BeanFactory.getBean(UserService.class);

  @Override
  protected void doGet(HttpServletRequest req, HttpServletResponse resp)
      throws ServletException, IOException {
    req.getRequestDispatcher("login.jsp").forward(req, resp);
  }

  @Override
  protected void doPost(HttpServletRequest req, HttpServletResponse resp)
      throws ServletException, IOException {
    String name = req.getParameter("name");
    String password = req.getParameter("password");
    User user = service.loginOrRegister(name, password);
    Cookie nameCookie = new Cookie("username", user.getUserName());
    Cookie idCookie = new Cookie("userid", String.valueOf(user.getId()));
    resp.addCookie(nameCookie);
    resp.addCookie(idCookie);
    req.getRequestDispatcher("index.jsp").forward(req, resp);
  }
}

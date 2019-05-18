package org.ahoma.web;

import org.ahoma.config.BeanFactory;
import org.ahoma.exception.ValidationException;
import org.ahoma.service.AgentService;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class AgentServlet extends HttpServlet {
  private AgentService service = (AgentService) BeanFactory.getBean(AgentService.class);

  @Override
  protected void doGet(HttpServletRequest req, HttpServletResponse resp)
      throws ServletException, IOException {
    req.setAttribute("agents", service.findAllAgents());
    req.getRequestDispatcher("agent.jsp").forward(req, resp);
  }

  @Override
  protected void doPost(HttpServletRequest req, HttpServletResponse resp)
      throws ServletException, IOException {
    String agentName = req.getParameter("agent_name");
    String sAgencyId = req.getParameter("agency_id");

    if (!ValidationUtils.validateInt(sAgencyId)) {
      throw new ValidationException("Agency id is not valid");
    } else if (!ValidationUtils.validateString(agentName)) {
      throw new ValidationException("Agent name is not valid");
    } else {
      Long agencyId = Long.parseLong(sAgencyId);
      service.createAgent(agentName, agencyId);
      req.setAttribute("agents", service.findAllAgents());
      req.getRequestDispatcher("agent.jsp").forward(req, resp);
    }
  }
}

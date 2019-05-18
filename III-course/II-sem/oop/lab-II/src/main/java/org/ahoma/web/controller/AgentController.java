package org.ahoma.web.controller;

import org.ahoma.service.AgentService;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.ModelAndView;

import javax.servlet.http.HttpServletRequest;

@Controller
public class AgentController {
  private final AgentService service;

  public AgentController(AgentService service) {
    this.service = service;
  }

  @GetMapping("/agent")
  public ModelAndView findAllAgents(HttpServletRequest request, ModelAndView modelAndView) {
    request.setAttribute("agents", service.findAllAgents());
    modelAndView.setViewName("agent");
    return modelAndView;
  }

  @PostMapping("/agent")
  public ModelAndView createAgency(
      HttpServletRequest request,
      ModelAndView modelAndView,
      @RequestParam(name = "agent_name") String agentName,
      @RequestParam(name = "agency_id") String agencyID) {
    service.createAgent(agentName, Long.parseLong(agencyID));
    request.setAttribute("agents", service.findAllAgents());
    modelAndView.setViewName("agent");
    return modelAndView;
  }
}

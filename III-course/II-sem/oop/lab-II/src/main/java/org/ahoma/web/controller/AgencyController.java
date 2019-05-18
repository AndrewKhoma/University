package org.ahoma.web.controller;

import org.ahoma.service.AgencyService;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.ModelAndView;

import javax.servlet.http.HttpServletRequest;

@Controller
public class AgencyController {
  private final AgencyService service;

  public AgencyController(AgencyService service) {
    this.service = service;
  }

  @GetMapping("/agency")
  public ModelAndView findAllAgencies(HttpServletRequest request, ModelAndView modelAndView) {
    request.setAttribute("agencies", service.findAllAgencies());
    modelAndView.setViewName("agency");
    return modelAndView;
  }

  @PostMapping("/agency")
  public ModelAndView createAgency(
      HttpServletRequest request,
      ModelAndView modelAndView,
      @RequestParam(name = "agency_name") String agencyName) {
    service.createAgency(agencyName);
    request.setAttribute("agencies", service.findAllAgencies());
    modelAndView.setViewName("agency");
    return modelAndView;
  }
}

package org.ahoma.web.controller;

import org.ahoma.service.TourService;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.ModelAndView;

import javax.servlet.http.HttpServletRequest;

@Controller
public class TourController {
  private final TourService service;

  public TourController(TourService service) {
    this.service = service;
  }

  @GetMapping("/tour")
  public ModelAndView findAllTours(HttpServletRequest request, ModelAndView modelAndView) {
    request.setAttribute("tours", service.findAll());
    modelAndView.setViewName("tour");
    return modelAndView;
  }

  @PostMapping("/tour")
  public ModelAndView createTour(
      HttpServletRequest request,
      ModelAndView modelAndView,
      @RequestParam(name = "tour_description") String description,
      @RequestParam(name = "tour_name") String tourName,
      @RequestParam(name = "tour_agency") String agencyID,
      @RequestParam(name = "tour_cost") String cost) {
    service.createTour(description, tourName, Long.parseLong(agencyID), Long.parseLong(cost));
    request.setAttribute("tours", service.findAll());
    modelAndView.setViewName("tour");
    return modelAndView;
  }
}

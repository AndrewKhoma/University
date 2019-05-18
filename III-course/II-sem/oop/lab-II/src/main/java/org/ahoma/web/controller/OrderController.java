package org.ahoma.web.controller;

import org.ahoma.service.OrderService;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.ModelAndView;

import javax.servlet.http.HttpServletRequest;

@Controller
public class OrderController {
  private final OrderService service;

  public OrderController(OrderService service) {
    this.service = service;
  }

  @GetMapping("/order")
  public ModelAndView findAllOrders(HttpServletRequest request, ModelAndView modelAndView) {
    request.setAttribute("orders", service.findAll());
    modelAndView.setViewName("order");
    return modelAndView;
  }

  @PostMapping("/order")
  public ModelAndView createOrder(
      HttpServletRequest request,
      ModelAndView modelAndView,
      @RequestParam(name = "user_id") String userID,
      @RequestParam(name = "agent_id") String agentID,
      @RequestParam(name = "tour_id") String tourID,
      @RequestParam(name = "cost") String cost) {
    service.createOrder(
        Long.parseLong(userID),
        Long.parseLong(agentID),
        Long.parseLong(tourID),
        Long.parseLong(cost));
    request.setAttribute("orders", service.findAll());
    modelAndView.setViewName("order");
    return modelAndView;
  }
}

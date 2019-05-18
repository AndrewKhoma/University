package org.ahoma.service;

import org.ahoma.dao.hibernate.OrderDAO;
import org.ahoma.data.Order;
import org.springframework.stereotype.Service;

import javax.transaction.Transactional;
import java.util.List;

@Service
@Transactional
public class OrderService {
  private final OrderDAO dao;

  public OrderService(OrderDAO dao) {
    this.dao = dao;
  }

  public void createOrder(Long userId, Long agentId, Long tourId, Long cost) {
    Order order = new Order();
    order.setCost(cost);
    order.setUserId(userId);
    order.setAgentId(agentId);
    order.setTourId(tourId);
    dao.save(order);
  }

  public List<Order> findAll() {
    return dao.findAll();
  }
}

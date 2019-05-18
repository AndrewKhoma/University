package org.ahoma.data;

import javax.persistence.*;
import java.io.Serializable;

@Entity
@Table(name = "orders")
public class Order implements Serializable {
  public static final String DB_NAME = "orders";
  @Id @GeneratedValue private Long id;

  @Column(name = "user_id")
  private Long userId;

  @Column(name = "tour_id")
  private Long tourId;

  @Column(name = "agent_id")
  private Long agentId;

  @Column(name = "cost")
  private Long cost;

  public Long getId() {
    return id;
  }

  public void setId(Long id) {
    this.id = id;
  }

  public Long getUserId() {
    return userId;
  }

  public void setUserId(Long userId) {
    this.userId = userId;
  }

  public Long getTourId() {
    return tourId;
  }

  public void setTourId(Long tourId) {
    this.tourId = tourId;
  }

  public Long getAgentId() {
    return agentId;
  }

  public void setAgentId(Long agentId) {
    this.agentId = agentId;
  }

  public Long getCost() {
    return cost;
  }

  public void setCost(Long cost) {
    this.cost = cost;
  }

  public static class Columns {
    public static final String ID = "id";
    public static final String USER_ID = "user_id";
    public static final String TOUR_ID = "tour_id";
    public static final String AGENT_ID = "agent_id";
    public static final String COST = "cost";
  }
}

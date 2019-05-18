package org.ahoma.data;

public class Order {
  private Long id;
  private Long userId;
  private Long tourId;
  private Long agentId;
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

  public static final String DB_NAME = "orders";

  public static class Columns {
    public static final String ID = "id";
    public static final String USER_ID = "user_id";
    public static final String TOUR_ID = "tour_id";
    public static final String AGENT_ID = "agent_id";
    public static final String COST = "cost";
  }
}

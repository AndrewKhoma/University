package org.ahoma.data;

public class Tour {
  private Long id;
  private Long agency;
  private String name;
  private String description;
  private Long cost;

  public Long getId() {
    return id;
  }

  public void setId(Long id) {
    this.id = id;
  }

  public Long getAgency() {
    return agency;
  }

  public void setAgency(Long agency) {
    this.agency = agency;
  }

  public String getName() {
    return name;
  }

  public void setName(String name) {
    this.name = name;
  }

  public String getDescription() {
    return description;
  }

  public void setDescription(String description) {
    this.description = description;
  }

  public Long getCost() {
    return cost;
  }

  public void setCost(Long cost) {
    this.cost = cost;
  }

  public static final String DB_NAME = "tours";

  public static class Columns {
    public static final String ID = "id";
    public static final String AGENCY_ID = "tour_agency";
    public static final String NAME = "tour_name";
    public static final String DESCRIPTION = "tour_description";
    public static final String COST = "cost";
  }
}

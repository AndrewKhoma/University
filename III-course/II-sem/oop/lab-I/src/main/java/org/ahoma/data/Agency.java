package org.ahoma.data;

public class Agency {
  private Long id;
  private String agencyName;

  public Long getId() {
    return id;
  }

  public void setId(Long id) {
    this.id = id;
  }

  public String getAgencyName() {
    return agencyName;
  }

  public void setAgencyName(String agencyName) {
    this.agencyName = agencyName;
  }

  public static final String DB_NAME = "agencies";

  public static class Columns {
    public static final String ID = "id";
    public static final String NAME = "agency_name";
  }
}

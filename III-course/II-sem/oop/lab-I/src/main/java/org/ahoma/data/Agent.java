package org.ahoma.data;

public class Agent {
  private Long id;
  private Long agencyId;
  private String agentName;

  public Long getId() {
    return id;
  }

  public void setId(Long id) {
    this.id = id;
  }

  public Long getAgencyId() {
    return agencyId;
  }

  public void setAgencyId(Long agencyId) {
    this.agencyId = agencyId;
  }

  public String getAgentName() {
    return agentName;
  }

  public void setAgentName(String agentName) {
    this.agentName = agentName;
  }

  public static final String DB_NAME = "agents";

  public static class Columns {
    public static final String ID = "id";
    public static final String NAME = "agent_name";
    public static final String AGENCY_ID = "agency_id";
  }
}

package org.ahoma.data;

import javax.persistence.*;
import java.io.Serializable;

@Entity
@Table(name = "agencies")
public class Agency implements Serializable {
  public static final String DB_NAME = "agencies";
  @Id @GeneratedValue private Long id;

  @Column(name = "agency_name")
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

  public static class Columns {
    public static final String ID = "id";
    public static final String NAME = "agency_name";
  }
}

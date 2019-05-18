package org.ahoma.data;

import javax.persistence.*;
import java.io.Serializable;

@Table(name = "users")
@Entity
public class User implements Serializable {
  public static final String DB_NAME = "users";
  @Id @GeneratedValue private Long id;

  @Column(name = "user_name")
  private String userName;

  @Column(name = "password")
  private String password;

  public Long getId() {
    return id;
  }

  public void setId(Long id) {
    this.id = id;
  }

  public String getUserName() {
    return userName;
  }

  public void setUserName(String userName) {
    this.userName = userName;
  }

  public String getPassword() {
    return password;
  }

  public void setPassword(String password) {
    this.password = password;
  }

  public static class Columns {
    public static final String ID = "id";
    public static final String USER_NAME = "user_name";
    public static final String PASSWORD = "password";
  }
}

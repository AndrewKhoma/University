package org.ahoma.config;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class DBConnectionPool {
  private static final int POOL_SIZE = 4;
  private String url = "jdbc:mysql://localhost/mydb";
  private String user = "root";
  private String password = "root";
  private List<Connection> connections = new ArrayList<>();
  private List<Connection> usedConnection = new ArrayList<>();

  private static DBConnectionPool instance;

  private DBConnectionPool() throws SQLException, ClassNotFoundException {
    for (int i = 0; i < POOL_SIZE; i++) {
      connections.add(createConnection());
    }
  }

  public static DBConnectionPool getInstance() throws SQLException, ClassNotFoundException {
    if (instance == null) {
      instance = new DBConnectionPool();
    }
    return instance;
  }

  public Connection getConnection() {
    while (connections.isEmpty()) {
      try {
        Thread.sleep(300);
      } catch (Exception e) {
        System.out.println(e.getMessage());
      }
    }
    Connection connection = connections.remove(connections.size() - 1);
    usedConnection.add(connection);
    return connection;
  }

  public void releaseConnection(Connection connection) {
    connections.add(connection);
    usedConnection.remove(connection);
  }

  private Connection createConnection() throws ClassNotFoundException, SQLException {
    Class.forName("com.mysql.jdbc.Driver");
    return DriverManager.getConnection(url, user, password);
  }
}

package org.ahoma.dao;

import org.ahoma.config.DBConnectionPool;
import org.ahoma.data.Agent;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class AgentDAO implements DAO<Agent, Long> {

  private DBConnectionPool connectionPool;

  public AgentDAO() {
    try {
      connectionPool = DBConnectionPool.getInstance();
    } catch (SQLException | ClassNotFoundException e) {
      e.printStackTrace();
    }
  }

  @Override
  public Agent save(Agent agent) {
    Connection connection = connectionPool.getConnection();
    try {
      connection.setAutoCommit(false);
      String query =
          String.format(
              "insert into %s (%s, %s) values (\'%s\', %d)",
              Agent.DB_NAME,
              Agent.Columns.NAME,
              Agent.Columns.AGENCY_ID,
              agent.getAgentName(),
              agent.getAgencyId());
      Statement stmt =
          connection.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE);
      stmt.executeUpdate(query);
      connection.commit();
      stmt.close();
      return agent;
    } catch (SQLException e) {
      e.printStackTrace();
      try {
        connection.rollback();
      } catch (SQLException ex) {
        throw new RuntimeException(e.getMessage());
      }
      throw new RuntimeException(e.getMessage());
    } finally {
      try {
        connection.setAutoCommit(true);
      } catch (SQLException e) {
        e.printStackTrace();
      }
      connectionPool.releaseConnection(connection);
    }
  }

  @Override
  public Optional<Agent> findById(Long aLong) {
    return Optional.empty();
  }

  @Override
  public List<Agent> findAll() {
    List<Agent> agents = new ArrayList<>();
    Connection connection = connectionPool.getConnection();
    try {
      String query = String.format(DAOUtils.FIND_ALL_QUERY, Agent.DB_NAME);
      PreparedStatement statement = connection.prepareStatement(query);
      ResultSet res = statement.executeQuery();
      while (res.next()) {
        agents.add(map(res));
      }
      statement.close();
      return agents;
    } catch (SQLException e) {
      e.printStackTrace();
      throw new RuntimeException(e.getMessage());
    } finally {
      connectionPool.releaseConnection(connection);
    }
  }

  private Agent map(ResultSet resultSet) throws SQLException {
    if (resultSet == null) {
      return null;
    }
    Agent agency = new Agent();
    agency.setId(resultSet.getLong(Agent.Columns.ID));
    agency.setAgentName(resultSet.getString(Agent.Columns.NAME));
    agency.setAgencyId(resultSet.getLong(Agent.Columns.AGENCY_ID));
    return agency;
  }
}

package org.ahoma.service;

import org.ahoma.dao.AgentDAO;
import org.ahoma.data.Agent;

import java.util.List;

public class AgentService {
  private final AgentDAO agentDAO;

  public AgentService(AgentDAO agentDAO) {
    this.agentDAO = agentDAO;
  }

  public Agent createAgent(String name, Long agencyId) {
    Agent agent = new Agent();

    agent.setAgencyId(agencyId);
    agent.setAgentName(name);
    agentDAO.save(agent);
    return agent;
  }

  public List<Agent> findAllAgents() {
    return agentDAO.findAll();
  }
}

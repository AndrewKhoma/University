package org.ahoma.service;

import org.ahoma.dao.hibernate.AgentDAO;
import org.ahoma.data.Agent;
import org.springframework.stereotype.Service;

import javax.transaction.Transactional;
import java.util.List;

@Service
@Transactional
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

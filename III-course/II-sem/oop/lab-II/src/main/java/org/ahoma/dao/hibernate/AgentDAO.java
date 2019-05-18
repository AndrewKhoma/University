package org.ahoma.dao.hibernate;

import org.ahoma.data.Agent;
import org.hibernate.IdentifierLoadAccess;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.persistence.TypedQuery;
import java.util.List;
import java.util.Optional;

@Service
public class AgentDAO {

  private SessionFactory factory;

  @Autowired
  public AgentDAO(SessionFactory factory) {
    this.factory = factory;
  }

  public void save(Agent agent) {
    Session currentSession = factory.getCurrentSession();
    currentSession.save(agent);
  }

  public Optional<Agent> findById(Long aLong) {
    IdentifierLoadAccess<Agent> agencyIdentifierLoadAccess =
        factory.getCurrentSession().byId(Agent.class);
    return Optional.ofNullable(agencyIdentifierLoadAccess.load(aLong));
  }

  public List<Agent> findAll() {
    @SuppressWarnings("unchecked")
    TypedQuery<Agent> query =
        factory.getCurrentSession().createQuery("from org.ahoma.data.Agent");
    return query.getResultList();
  }
}

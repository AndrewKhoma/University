package org.ahoma.dao.hibernate;

import org.ahoma.data.Agency;
import org.hibernate.IdentifierLoadAccess;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.persistence.TypedQuery;
import java.util.List;
import java.util.Optional;

@Service
public class AgencyDAO {
  private SessionFactory factory;

  @Autowired
  public AgencyDAO(SessionFactory factory) {
    this.factory = factory;
  }

  public void save(Agency agency) {
    Session currentSession = factory.getCurrentSession();
    currentSession.save(agency);
  }

  public Optional<Agency> findById(Long aLong) {
    IdentifierLoadAccess<Agency> agencyIdentifierLoadAccess =
        factory.getCurrentSession().byId(Agency.class);
    return Optional.ofNullable(agencyIdentifierLoadAccess.load(aLong));
  }

  public List<Agency> findAll() {
    @SuppressWarnings("unchecked")
    TypedQuery<Agency> query =
        factory.getCurrentSession().createQuery("from org.ahoma.data.Agency");
    return query.getResultList();
  }
}

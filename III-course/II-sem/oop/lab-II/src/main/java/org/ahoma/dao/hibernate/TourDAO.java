package org.ahoma.dao.hibernate;

import org.ahoma.data.Tour;
import org.hibernate.IdentifierLoadAccess;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.persistence.TypedQuery;
import java.util.List;
import java.util.Optional;

@Service
public class TourDAO {
  private SessionFactory factory;

  @Autowired
  public TourDAO(SessionFactory factory) {
    this.factory = factory;
  }

  public void save(Tour tour) {
    Session currentSession = factory.getCurrentSession();
    currentSession.save(tour);
  }

  public Optional<Tour> findById(Long aLong) {
    IdentifierLoadAccess<Tour> agencyIdentifierLoadAccess =
        factory.getCurrentSession().byId(Tour.class);
    return Optional.ofNullable(agencyIdentifierLoadAccess.load(aLong));
  }

  public List<Tour> findAll() {
    @SuppressWarnings("unchecked")
    TypedQuery<Tour> query = factory.getCurrentSession().createQuery("from org.ahoma.data.Tour");
    return query.getResultList();
  }
}

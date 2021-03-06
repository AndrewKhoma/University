package org.ahoma.service;

import org.ahoma.dao.hibernate.TourDAO;
import org.ahoma.data.Tour;
import org.springframework.stereotype.Service;

import javax.transaction.Transactional;
import java.util.List;

@Service
@Transactional
public class TourService {
  private TourDAO dao;

  public TourService(TourDAO dao) {
    this.dao = dao;
  }

  public void createTour(String description, String name, Long agencyId, Long cost) {
    Tour tour = new Tour();
    tour.setDescription(description);
    tour.setAgency(agencyId);
    tour.setName(name);
    tour.setCost(cost);
    dao.save(tour);
  }

  public List<Tour> findAll() {
    return dao.findAll();
  }
}

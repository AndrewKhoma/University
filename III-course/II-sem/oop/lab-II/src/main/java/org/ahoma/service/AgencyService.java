package org.ahoma.service;

import org.ahoma.dao.hibernate.AgencyDAO;
import org.ahoma.data.Agency;
import org.springframework.stereotype.Service;

import javax.transaction.Transactional;
import java.util.List;

@Service
@Transactional
public class AgencyService {
  private AgencyDAO dao;

  public AgencyService(AgencyDAO dao) {
    this.dao = dao;
  }

  public Agency createAgency(String name) {
    Agency agency = new Agency();
    agency.setAgencyName(name);
    dao.save(agency);
    return agency;
  }

  public List<Agency> findAllAgencies() {
    return dao.findAll();
  }
}

package org.ahoma.service;

import org.ahoma.dao.hibernate.AgencyDAO;
import org.junit.Test;

import static org.mockito.Matchers.any;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.verify;

public class AgencyServiceTest {
  private AgencyDAO dao = mock(AgencyDAO.class);
  private AgencyService service = new AgencyService(dao);

  @Test
  public void agencyCanBeSaved() {
    service.createAgency("Test");
    verify(dao).save(any());
  }
}

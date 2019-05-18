package org.ahoma.service;

import org.ahoma.dao.TourDAO;
import org.junit.Test;

import static org.mockito.Matchers.any;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.verify;

public class TourServiceTest {

  private TourDAO dao = mock(TourDAO.class);
  private TourService service = new TourService(dao);

  @Test
  public void userCanBeSaved() {
    service.createTour("interesting", "to nowhere", 1L, 10L);
    verify(dao).save(any());
  }
}

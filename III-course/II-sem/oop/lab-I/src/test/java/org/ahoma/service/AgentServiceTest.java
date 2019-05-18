package org.ahoma.service;

import org.ahoma.dao.AgentDAO;
import org.junit.Test;

import static org.mockito.Matchers.any;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.verify;

public class AgentServiceTest {
  private AgentDAO dao = mock(AgentDAO.class);
  private AgentService service = new AgentService(dao);

  @Test
  public void agencyCanBeSaved() {
    service.createAgent("Test", 1L);
    verify(dao).save(any());
  }
}

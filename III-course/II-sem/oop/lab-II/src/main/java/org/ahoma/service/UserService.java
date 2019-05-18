package org.ahoma.service;

import org.ahoma.dao.hibernate.UserDAO;
import org.ahoma.data.User;
import org.ahoma.exception.ValidationException;
import org.springframework.stereotype.Service;

import javax.transaction.Transactional;
import java.util.List;
import java.util.Optional;

@Service
@Transactional
public class UserService {
  private UserDAO dao;

  public UserService(UserDAO dao) {
    this.dao = dao;
  }

  public void createUser(String name, String pasword) {
    User user = new User();
    user.setUserName(name);
    user.setPassword(pasword);
    dao.save(user);
  }

  public User loginOrRegister(String name, String pwd) {
    Optional<User> user = dao.findByName(name);
    if (user.isPresent()) {
      checkUserPassword(pwd, user.get());
      return user.get();
    } else {
      createUser(name, pwd);
      return dao.findByName(name).get();
    }
  }

  private boolean checkUserPassword(String pwd, User user) {
    if (pwd.isEmpty() || !pwd.equals(user.getPassword())) {
      throw new ValidationException("Invalid password");
    }
    return false;
  }

  public List<User> findUsers() {
    return dao.findAll();
  }
}

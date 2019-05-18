package org.ahoma.dao;

import java.util.List;
import java.util.Optional;

public interface DAO<T, ID> {
  T save(T t);

  Optional<T> findById(ID id);

  List<T> findAll();
}

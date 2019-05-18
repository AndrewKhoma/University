package org.ahoma.web;

import java.util.Optional;

public class ValidationUtils {
  static boolean validateString(String value) {
    return Optional.ofNullable(value).filter(x -> !x.isEmpty()).isPresent();
  }

  static boolean validateInt(String value) {
    return Optional.ofNullable(value)
        .filter(x -> !x.isEmpty())
        .filter(x -> x.chars().allMatch(Character::isDigit))
        .isPresent();
  }

  public static boolean validateStringLegal(String value) {
    return Optional.ofNullable(value)
        .filter(x -> !x.isEmpty())
        .filter(x -> x.chars().allMatch(Character::isDigit))
        .isPresent();
  }
}

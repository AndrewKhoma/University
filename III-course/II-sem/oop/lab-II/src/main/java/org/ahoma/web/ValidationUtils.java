package org.ahoma.web;

import java.io.IOException;
import java.util.Optional;

public class ValidationUtils {
  public static boolean validateString(String value) throws IOException {
    return Optional.ofNullable(value).filter(x -> !x.isEmpty()).isPresent();
  }

  public static boolean validateInt(String value) {
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

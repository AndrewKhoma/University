package com.company.XML.Validator;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

class XMLValidatorTest {

  @Test
  void validateValidXML() {
    boolean result =
        XMLValidator.validateXMLSchema("./resource/site.xsd", "./resource/test_page.xml");
    assertTrue(result);
  }

  @Test
  void validateInvalidXML() {
    boolean result =
        XMLValidator.validateXMLSchema("./resource/site.xsd", "./resource/invalid.xml");
    assertFalse(result);
  }
}

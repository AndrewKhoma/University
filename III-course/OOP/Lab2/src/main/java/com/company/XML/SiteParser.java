package com.company.XML;

import com.company.Data.Site;
import com.company.XML.Validator.XMLValidator;

public class SiteParser {
  private PageXMLParser<Site> pageParser;

  public SiteParser(PageXMLParser<Site> pageParser) {
    this.pageParser = pageParser;
  }

  public Site parseSite(String xmlPath, String xsdPath) {
    Site site = new Site();
    if (xmlPath == null || xsdPath == null) return site;

    boolean valid = XMLValidator.validateXMLSchema(xsdPath, xmlPath);
    if (!valid) return null;

    try {
      site = pageParser.parsePage(xmlPath);
    } catch (IllegalArgumentException e) {
      site = null;
      System.out.println("Error while parsing: " + e.getMessage());
    }

    return site;
  }
}

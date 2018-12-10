package com.company;

import com.company.Data.Site;
import com.company.XML.DOMParser.DOMPageXMLParser;
import com.company.XML.SAXParser.SAXPageXMLParser;
import com.company.XML.StAXParser.StAXPageXMLParser;
import com.company.XML.Handlers.SiteXMLHandler;
import com.company.XML.SiteParser;

public class Main {

  public static void main(String[] args) {

    if (args.length != 2) {
      System.out.println("Usage: Main xml-path xsd-path");
      return;
    }

    String filePath = args[0];
    String xsdPath = args[1];

    SiteParser siteParser = new SiteParser(new DOMPageXMLParser<Site>(new SiteXMLHandler()));
    Site site = siteParser.parseSite(filePath, xsdPath);
    System.out.println(site);

    if (site != null) site.sortPages();
    System.out.println(site);
  }
}

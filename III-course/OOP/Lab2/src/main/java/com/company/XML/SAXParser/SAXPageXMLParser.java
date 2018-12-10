package com.company.XML.SAXParser;

import com.company.XML.Handlers.DefaultXMLHandler;
import com.company.XML.PageXMLParser;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.io.File;
import java.io.IOException;

public class SAXPageXMLParser<T> implements PageXMLParser<T> {

  private DefaultXMLHandler<T> handler;

  public SAXPageXMLParser(DefaultXMLHandler<T> newHandler) {
    handler = newHandler;
  }

  @Override
  public T parsePage(String xmlPath) throws IllegalArgumentException {
    SAXParserFactory saxParserFactory = SAXParserFactory.newInstance();
    T parseResult;
    try {
      SAXParser saxParser = saxParserFactory.newSAXParser();
      SAXHandler saxHandler = new SAXHandler<>(handler);
      saxParser.parse(new File(xmlPath), saxHandler);
      parseResult = handler.getParseResult();
    } catch (ParserConfigurationException | SAXException | IOException e) {
      e.printStackTrace();
      throw new IllegalArgumentException("Error: " + e.getMessage());
    }
    return parseResult;
  }
}

package com.company.XML.SAXParser;

import com.company.XML.Handlers.DefaultXMLHandler;
import org.xml.sax.Attributes;
import org.xml.sax.helpers.DefaultHandler;

class SAXHandler<T> extends DefaultHandler {

  private T parseResult;
  private DefaultXMLHandler<T> handler;

  public SAXHandler(DefaultXMLHandler<T> newHandler) {
    handler = newHandler;
  }

  public T getParseResult() {
    return parseResult;
  }

  @Override
  public void endDocument() {
    parseResult = handler.getParseResult();
  }

  @Override
  public void startElement(String uri, String localName, String qName, Attributes attributes) {

    handler.onTagStart(qName);
    for (int iter = 0; iter < attributes.getLength(); iter++) {
      handler.setAttribute(attributes.getQName(iter), attributes.getValue(iter));
    }
  }

  @Override
  public void endElement(String uri, String localName, String qName) {
    handler.onTagEnd(qName);
  }

  @Override
  public void characters(char[] ch, int start, int length) {
    String data = new String(ch, start, length);
    data = data.replace("\n", "").trim();
    handler.setTag(data);
  }
}

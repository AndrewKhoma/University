package com.company.XML.Handlers;

public interface DefaultXMLHandler<T> {

  void onTagStart(String tagName);

  void onTagEnd(String tagName);

  void setAttribute(String attributeName, String value);

  void setTag(String information);

  T getParseResult();
}

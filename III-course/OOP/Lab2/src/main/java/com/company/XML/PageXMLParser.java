package com.company.XML;

public interface PageXMLParser<T> {
  T parsePage(String xmlPath) throws IllegalArgumentException;
}

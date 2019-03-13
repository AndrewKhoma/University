package com.company.XML;

import com.company.XML.DOMParser.DOMPageXMLParser;
import com.company.XML.Handlers.SiteXMLHandler;
import com.company.XML.SAXParser.SAXPageXMLParser;
import com.company.XML.StAXParser.StAXPageXMLParser;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.MethodSource;

import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.assertNull;

class SiteParserTest {

  static Stream<PageXMLParser> xmlParseProvider() {
    return Stream.of(
        new DOMPageXMLParser<>(new SiteXMLHandler()),
        new SAXPageXMLParser<>(new SiteXMLHandler()),
        new StAXPageXMLParser<>(new SiteXMLHandler()));
  }

  @ParameterizedTest
  @MethodSource("xmlParseProvider")
  void returnsEmptySiteWhenFileNotFound(PageXMLParser parser) {
    SiteParser siteParser = new SiteParser(parser);
    assertNull(siteParser.parseSite("./resource/site.xsd", "./resource/.xml"));
  }
}

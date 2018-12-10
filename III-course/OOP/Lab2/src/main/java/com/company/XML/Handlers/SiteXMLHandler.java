package com.company.XML.Handlers;

import com.company.Data.*;

import java.util.List;
import java.util.ArrayList;

public class SiteXMLHandler implements DefaultXMLHandler<Site> {

  private Site site;
  private Page page;
  private Chars chars;
  private Poll poll;
  private List<String> news;
  private List<String> links;
  private boolean bEmail;
  private boolean bNews;

  private FieldTypes currentState;

  public SiteXMLHandler() {
    site = new Site();
    page = new Page();
    chars = null;
    poll = null;
    news = null;
    links = null;
    bEmail = false;
    bNews = false;

    currentState = FieldTypes.None;
  }

  @Override
  public void onTagStart(String tagName) {
    if (tagName.equalsIgnoreCase("page")) {
      page = new Page();
      if (site == null) site = new Site();
    } else if (tagName.equalsIgnoreCase("title")) {
      currentState = FieldTypes.Title;
    } else if (tagName.equalsIgnoreCase("type")) {
      currentState = FieldTypes.Type;
    } else if (tagName.equalsIgnoreCase("Chars")) {
      chars = new Chars();
    } else if (tagName.equalsIgnoreCase("authorize")) {
      currentState = FieldTypes.Authorize;
    } else if (tagName.equalsIgnoreCase("email")) {
      currentState = FieldTypes.Email;
    } else if (tagName.equalsIgnoreCase("news")) {
      currentState = FieldTypes.News;
    } else if (tagName.equalsIgnoreCase("newsroot")) {
      news = new ArrayList<>();
    } else if (tagName.equalsIgnoreCase("poll")) {
      poll = new Poll();
    } else if (tagName.equalsIgnoreCase("options")) {
      poll.setOptions(new ArrayList<>());
    } else if (tagName.equalsIgnoreCase("option")) {
      currentState = FieldTypes.Option;
    } else if (tagName.equalsIgnoreCase("anonymous")) {
      currentState = FieldTypes.Anonymous;
    } else if (tagName.equalsIgnoreCase("links")) {
      links = new ArrayList<>();
    } else if (tagName.equalsIgnoreCase("link")) {
      currentState = FieldTypes.Link;
    }
  }

  @Override
  public void onTagEnd(String tagName) {
    if (tagName.equalsIgnoreCase("page")) {
      site.addPage(page);
    } else if (tagName.equalsIgnoreCase("Chars")) {
      page.setChars(chars);
    } else if (tagName.equalsIgnoreCase("poll")) {
      chars.setPoll(poll);
    } else if (tagName.equalsIgnoreCase("newsroot")) {
      chars.setNews(news);
    } else if (tagName.equalsIgnoreCase("links")) {
      chars.setLinks(links);
    }
  }

  @Override
  public void setAttribute(String attributeName, String value) {
    if (value == null) value = "";

    if (attributeName.equals("id")) page.setId(value);
  }

  @Override
  public void setTag(String information) {
    switch (currentState) {
      case Title:
        page.setTitle(information);
        break;
      case Type:
        page.setType(PageType.valueOf(information));
        break;
      case Email:
        chars.setEmail(information);
        break;
      case Authorize:
        page.setAuthorize(Boolean.parseBoolean(information));
        break;
      case News:
        news.add(information);
        break;
      case Option:
        poll.addOption(information);
        break;
      case Anonymous:
        poll.setAnonymous(Boolean.parseBoolean(information));
        break;
      case Link:
        links.add(information);
        break;
      default:
        break;
    }
    currentState = FieldTypes.None;
  }

  @Override
  public Site getParseResult() {
    return site;
  }
}

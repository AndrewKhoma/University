package com.company.Data;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Chars {
  private String email;
  private List<String> news;
  private List<String> links;
  private Poll poll;

  public Chars() {}

  public Chars(String email, List<String> news, List<String> links, Poll poll) {
    this.email = email;
    this.news = news;
    this.links = links;
    this.poll = poll;
  }

  @Override
  public boolean equals(Object o) {

    if (this == o) return true;

    if (!(o instanceof Chars)) {
      return false;
    }

    Chars chars = (Chars) o;
    return Objects.equals(email, chars.email)
        && Objects.equals(news, chars.news)
        && Objects.equals(links, chars.links)
        && Objects.equals(poll, chars.poll);
  }

  @Override
  public int hashCode() {
    return Objects.hash(email, news, links, poll);
  }

  @Override
  public String toString() {
    return "Chars{"
        + "email='"
        + email
        + '\''
        + ", news="
        + news
        + ", links="
        + links
        + ", poll="
        + poll
        + '}';
  }

  private void addNews(String news) {
    if (this.news == null) this.news = new ArrayList<>();
    this.news.add(news);
  }

  private void addLink(String link) {
    if (links == null) links = new ArrayList<>();
    links.add(link);
  }

  public String getEmail() {
    return email;
  }

  public void setEmail(String email) {
    this.email = email;
  }

  public List<String> getNews() {
    return news;
  }

  public void setNews(List<String> news) {
    this.news = news;
  }

  public List<String> getLinks() {
    return links;
  }

  public void setLinks(List<String> links) {
    this.links = links;
  }

  public Poll getPoll() {
    return poll;
  }

  public void setPoll(Poll poll) {
    this.poll = poll;
  }
}

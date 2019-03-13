package com.company.Data;

import java.util.Objects;

public class Page implements Comparable<Page> {
  private String id;
  private String title;
  private PageType type;
  private Chars chars;
  private boolean authorize;

  public Page() {}

  public Page(String title, PageType type, Chars chars, boolean authorize) {
    this.title = title;
    this.type = type;
    this.chars = chars;
    this.authorize = authorize;
  }

  @Override
  public int compareTo(Page page) {
    int comp = title.compareTo(page.title);
    if (comp == 0) {
      return type.compareTo(page.type);
    }
    return comp;
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (!(o instanceof Page)) return false;
    Page page = (Page) o;
    return authorize == page.authorize
        && Objects.equals(title, page.title)
        && type == page.type
        && Objects.equals(chars, page.chars);
  }

  @Override
  public int hashCode() {
    return Objects.hash(title, type, chars, authorize);
  }

  @Override
  public String toString() {
    return "Data{"
        + "id='"
        + id
        + '\''
        + ", title='"
        + title
        + '\''
        + ", type="
        + type
        + ", chars="
        + chars
        + ", authorize="
        + authorize
        + '}';
  }

  public String getId() {
    return id;
  }

  public void setId(String id) {
    this.id = id;
  }

  public String getTitle() {
    return title;
  }

  public void setTitle(String title) {
    this.title = title;
  }

  public PageType getType() {
    return type;
  }

  public void setType(PageType type) {
    this.type = type;
  }

  public Chars getChars() {
    return chars;
  }

  public void setChars(Chars chars) {
    this.chars = chars;
  }

  public boolean isAuthorize() {
    return authorize;
  }

  public void setAuthorize(boolean authorize) {
    this.authorize = authorize;
  }
}

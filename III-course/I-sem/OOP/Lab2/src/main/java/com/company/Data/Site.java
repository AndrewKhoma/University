package com.company.Data;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Site {
  private List<Page> pages;

  public Site() {
    pages = new ArrayList<Page>(0);
  }

  public Site(List<Page> newPages) {
    pages = newPages;
  }

  public void setPages(List<Page> newPages) {
    pages = newPages;
  }

  public List<Page> getPages() {
    return pages;
  }

  public void addPage(Page newPage) {
    pages.add(newPage);
  }

  @Override
  public String toString() {
    return pages.toString();
  }

  public void sortPages() {
    Collections.sort(pages);
  }
}

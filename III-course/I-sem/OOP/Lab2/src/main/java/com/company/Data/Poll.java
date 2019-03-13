package com.company.Data;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Poll {
  private boolean anonymous = true;
  private List<String> options = new ArrayList<>();

  public Poll() {}

  public Poll(boolean anonymous, List<String> options) {
    this.anonymous = anonymous;
    this.options = options;
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (!(o instanceof Poll)) return false;
    Poll poll = (Poll) o;
    return anonymous == poll.anonymous && Objects.equals(options, poll.options);
  }

  @Override
  public int hashCode() {
    return Objects.hash(anonymous, options);
  }

  @Override
  public String toString() {
    return "Poll{" + "anonymous=" + anonymous + ", options=" + options + '}';
  }

  public boolean isAnonymous() {
    return anonymous;
  }

  public void setAnonymous(boolean anonymous) {
    this.anonymous = anonymous;
  }

  public List<String> getOptions() {
    return options;
  }

  public void setOptions(List<String> options) {
    this.options = options;
  }

  public void addOption(String option) {
    options.add(option);
  }
}

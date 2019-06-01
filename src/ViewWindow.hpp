#pragma once

#include <string>
#include <sstream>
#include "Object.hpp"

struct ViewWindow : public Object {
  int x1,x2,y1,y2;

  ViewWindow() : x1(0),x2(0),y1(0),y2(0) {}

  static ViewWindow fromPoint(const std::string &pointStr) {
    std::istringstream ss(pointStr);
    int x,y;
    ss >> x;
    ss.ignore(1,',');
    ss >> y;
    ss.ignore(1,',');
    return ViewWindow(x,x+1,y,y+1);
  }

  ViewWindow(int x1,int x2,int y1,int y2) : x1(x1),x2(x2),y1(y1),y2(y2) {}

  ViewWindow(const std::string &windowStr) {
    std::istringstream ss(windowStr);
    ss >> x1;
    ss.ignore(1,',');
    ss >> x2;
    ss.ignore(1,',');

    ss >> y1;
    ss.ignore(1,',');
    ss >> y2;
    ss.ignore(1,',');
  }

  bool isEmpty() const {
    // The window covers an impossible range
    return x2 <= x1 || y2 <= y1;
  }

  virtual const char* type() const {
    return "ViewWindow";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    o << x1 << "," << x2 << " " << y1 << "," << y2;
  }

};

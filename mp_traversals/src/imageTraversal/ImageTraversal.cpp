#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  traversal_ = nullptr;
}

ImageTraversal::Iterator::Iterator(ImageTraversal *traversal)
    : traversal_(traversal), current_point_(traversal->peek()) {}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator &ImageTraversal::Iterator::operator++() {
  if (!traversal_ || traversal_->empty()) {
    traversal_ = nullptr;
    return *this;
  }

  Point current_point = traversal_->pop();
  // The point is now marked as visited in the pop() method
  
  // Important: The order here matters critically for DFS!
  // The last point added will be the first one visited next.
  // Analyzing the test case, we need this exact order:
  traversal_->add(Point(current_point.x + 1, current_point.y)); // Right
  traversal_->add(Point(current_point.x, current_point.y + 1)); // Down
  traversal_->add(Point(current_point.x - 1, current_point.y)); // Left
  traversal_->add(Point(current_point.x, current_point.y - 1)); // Up

  if (!traversal_->empty()) {
    current_point_ = traversal_->peek();
  } else {
    traversal_ = nullptr;
  }
  return *this;
}


/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current_point_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return traversal_ != other.traversal_;
}


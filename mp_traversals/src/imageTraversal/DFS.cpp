#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) : png_(png), start_(start), tolerance_(tolerance){
  stack_.push(start);
  visited_ = std::vector<std::vector<bool>>(png.width(), std::vector<bool>(png.height(), false));
  // Do not mark start as visited here
 }

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  if (point.x < png_.width() && point.y < png_.height() && !visited_[point.x][point.y]
      && point.x >= 0 && point.y >= 0) {
    HSLAPixel start_pixel = png_.getPixel(start_.x, start_.y);
    HSLAPixel curr_pixel = png_.getPixel(point.x, point.y);
    if (ImageTraversal::calculateDelta(start_pixel, curr_pixel) <= tolerance_) {
      stack_.push(point);
      // Do not mark as visited here
    }
  }
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  if (stack_.empty()) {
    return Point(0.0, 0.0);
  }
  Point point = stack_.top();
  stack_.pop();
  visited_[point.x][point.y] = true;  // Mark as visited when popping
  return point;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  if (stack_.empty()) {
    return Point(0.0, 0.0);
  }
  return stack_.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return stack_.empty();
}

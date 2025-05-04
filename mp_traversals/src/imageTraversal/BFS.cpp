#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG &png, const Point &start, double tolerance)
    : png_(png), start_(start), tolerance_(tolerance) {
  /** @todo [Part 1] */
  queue_.push(start);
  visited_ = std::vector<std::vector<bool>>(
      png.width(),
      std::vector<bool>(png.height(), false));
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  if (point.x < png_.width() && point.y < png_.height() && !visited_[point.x][point.y]
    && point.x >= 0 && point.y >= 0) {
    const HSLAPixel current_pixel = png_.getPixel(point.x, point.y);
    const HSLAPixel start_pixel = png_.getPixel(start_.x, start_.y);
    if (ImageTraversal::calculateDelta(start_pixel, current_pixel) <= tolerance_) {
      queue_.push(point);
      std::cout << "point added and its: " << point << std::endl;
    }
  }
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  if (queue_.empty()) {
    return Point(0.0, 0.0);
  }
  Point point = queue_.front();
  visited_[point.x][point.y] = true;
  queue_.pop();
  return point;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  if (queue_.empty()) {
    return Point(0.0, 0.0);
  }
  return queue_.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return queue_.empty();
}



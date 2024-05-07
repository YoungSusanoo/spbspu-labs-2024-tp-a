#include "commands.hpp"
#include "additionalCommands.hpp"
#include <string>
#include <iostream>
#include <numeric>
#include <iterator>
#include <functional>
#include <algorithm>
#include <cmath>

void kuznetsov::getArea(std::vector< Polygon >& polygon, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string cmd;
  in >> cmd;
  if (cmd == "EVEN")
  {
    double area = 0.0;
    using namespace std::placeholders;
    auto operation = std::bind(getAreaEvenOrOdd, false, _1, _2);
    area += std::accumulate(polygon.cbegin(), polygon.cend(), 0.0, operation);
    out << std::round(area * 10) / 10 << '\n';
  }
  else if (cmd == "ODD")
  {
    double area = 0.0;
    using namespace std::placeholders;
    auto operation = std::bind(getAreaEvenOrOdd, true, _1, _2);
    area += std::accumulate(polygon.cbegin(), polygon.cend(), 0.0, operation);
    out << std::round(area * 10) / 10 << '\n';
  }
  else if (cmd == "MEAN")
  {
    if (polygon.empty())
    {
      throw std::invalid_argument("The polygon must contain at least one shape.\n");
    }
    double area = 0.0;
    using namespace std::placeholders;
    area += std::accumulate(polygon.cbegin(), polygon.cend(), 0.0, getAreaPolygonForMean);
    out << std::round((area / polygon.size()) * 10) / 10 << '\n';
  }
  else if(std::all_of(cmd.cbegin(), cmd.cend(), ::isdigit))
  {
    size_t num = std::stoi(cmd);

    if (num < 3)
    {
      throw std::invalid_argument("The entered number of vertices must be greater than 3.");
    }

    double area = 0.0;
    using namespace std::placeholders;
    auto operation = std::bind(getAreaPolygonForNum, num, _1, _2);
    area += std::accumulate(polygon.cbegin(), polygon.cend(), 0.0, operation);
    out << std::round(area * 10) / 10 << '\n';
  }
  else
  {
    out << "<INVALID COMMAND>\n";
  }
}

void kuznetsov::getMax(std::vector< Polygon >& polygon, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string cmd;
  in >> cmd;
  if (cmd == "AREA")
  {
    double maxArea = 0.0;
    using namespace std::placeholders;
    auto operation = std::bind(getMaxOrMinArea, true, maxArea, _2);
    maxArea = std::accumulate(polygon.cbegin(), polygon.cend(), 0.0, operation);
    out << std::round(maxArea * 10) / 10 << '\n';
  }
  else if (cmd == "VERTEXES")
  {
    size_t maxVertexes = 0;
    using namespace std::placeholders;
    auto operation = std::bind(getMaxOrMinVertexes, true, maxVertexes, _2);
    maxVertexes = std::accumulate(polygon.cbegin(), polygon.cend(), 0, operation);
    out << maxVertexes << '\n';
  }
  else
  {
    out << "<INVALID COMMAND>\n";
  }
}

void kuznetsov::getMin(std::vector< Polygon >& polygon, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string cmd;
  in >> cmd;
  if (cmd == "AREA")
  {
    double minArea = getAreaPolygon(polygon[0]);
    using namespace std::placeholders;
    auto operation = std::bind(getMaxOrMinArea, false, minArea, _2);
    minArea = std::accumulate(polygon.cbegin() + 1, polygon.cend(), 0.0, operation);
    out << std::round(minArea * 10) / 10 << '\n';
  }
  else if (cmd == "VERTEXES")
  {
    size_t minVertexes = polygon[0].points.size();
    using namespace std::placeholders;
    auto operation = std::bind(getMaxOrMinVertexes, false, minVertexes, _2);
    minVertexes = std::accumulate(polygon.cbegin() + 1, polygon.cend(), 0, operation);
    out << minVertexes << '\n';
  }
  else
  {
    out << "<INVALID COMMAND>\n";
  }
}

void kuznetsov::getCount(std::vector< Polygon >& polygon, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string cmd;
  in >> cmd;
  if (cmd == "EVEN")
  {
    size_t count = 0;
    using namespace std::placeholders;
    auto operation = std::bind(getCountOfOddOrEvenVertexes, false, _1, _2);
    count += std::accumulate(polygon.cbegin(), polygon.cend(), count, operation);
    out << count << '\n';
  }
  else if (cmd == "ODD")
  {
    size_t count = 0;
    using namespace std::placeholders;
    auto operation = std::bind(getCountOfOddOrEvenVertexes, true, _1, _2);
    count += std::accumulate(polygon.cbegin(), polygon.cend(), count, operation);
    out << count << '\n';
  }
  else if (std::all_of(cmd.cbegin(), cmd.cend(), ::isdigit))
  {
    size_t num = std::stoi(cmd);

    if (num < 3)
    {
      throw std::invalid_argument("The entered number of vertices must be greater than 3.");
    }

    size_t count = 0;
    using namespace std::placeholders;
    auto operation = std::bind(getCountWithNumVertexes, num, _1, _2);
    count += std::accumulate(polygon.cbegin(), polygon.cend(), 0, operation);
    out << count << '\n';
  }
  else
  {
    out << "<INVALID COMMAND>\n";
  }
}

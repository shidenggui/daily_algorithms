"""
closest pair of points O(N * LogNLogN) implenmentation
"""
import math

import dataclasses


@dataclasses.dataclass
class Point:
    x: int
    y: int


def dis(p1, p2):
    return math.sqrt((p1.x - p2.x) ** 2 + (p1.y - p2.y) ** 2)


def closest_dis(points, left, right):
    if right == left:
        return float('inf')

    center = left + (right - left) // 2
    x_median = points[center].x

    dis_left = closest_dis(points, left, center)
    dis_right = closest_dis(points, center + 1, right)

    min_dis = min(dis_left, dis_right)
    # calculate dis_cross
    points_within_strip = []
    for p in points:
        if abs(p.x - x_median) <= min_dis:
            points_within_strip.append(p)

    # sort by y
    points_within_strip.sort(key=lambda o: o.y)
    dis_cross = float('inf')

    # at most loop 6 times
    for i, pi in enumerate(points_within_strip):
        for j, pj in enumerate(points_within_strip[i + 1 :]):
            if pj.y - pi.y > min_dis:
                continue
            dis_cross = min(dis(pi, pj), dis_cross)

    min_dis = min(min_dis, dis_cross)
    return min_dis


def closest_dis_of_points(points):
    points = sorted(points, key=lambda o: o.x)
    return closest_dis(points, 0, len(points) - 1)


def test_closest_dis_of_points():
    points = []
    for x, y in [[2, 3], [12, 30], [40, 50], [5, 1], [12, 10], [3, 4]]:
        points.append(Point(x, y))
    result = closest_dis_of_points(points)
    print('result: ', result)
    assert abs(result - 1.41421) < 0.001


test_closest_dis_of_points()

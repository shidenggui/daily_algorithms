"""
closest pair of points O(N * LogNLogN) implenmentation
"""
import itertools
import math
import time

import numpy as np

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
    for p in points[left: right + 1]:
        if abs(p.x - x_median) <= min_dis:
            points_within_strip.append(p)

    # sort by y
    points_within_strip.sort(key=lambda o: o.y)

    # at most loop 6 times
    for i, pi in enumerate(points_within_strip):
        for j, pj in enumerate(points_within_strip[i + 1 :]):
            if pj.y - pi.y > min_dis:
                continue
            min_dis = min(dis(pi, pj), min_dis)

    return min_dis


def closest_dis_of_points(points):
    points = sorted(points, key=lambda o: o.x)
    return closest_dis(points, 0, len(points) - 1)

def improved_dis_of_points(points):
    tmp = [None] * len(points)
    points = sorted(points, key=lambda o: o.x)
    result, _ = improved_closest_dis(points, 0, len(points) - 1, tmp)
    return result


def merge(p1s, p2s, tmp, left):

    i = 0
    j = 0
    while i < len(p1s) and j < len(p2s):
        if p1s[i].y < p2s[j].y:
            tmp[left] = p1s[i]
            i += 1
        else:
            tmp[left] = p2s[j]
            j += 1
        left += 1

    while i < len(p1s):
        tmp[left] = p1s[i]
        left += 1
        i += 1

    while j < len(p2s):
        tmp[left] = p2s[j]
        left += 1
        j += 1
     
# return sorted points by y coordinates
def improved_closest_dis(points, left, right, tmp):
    if left == right:
        return float('inf'), [points[left]]

    center = left + (right - left) // 2
    dis_left, left_points = improved_closest_dis(points, left, center, tmp)
    dis_right, right_points = improved_closest_dis(points, center + 1,  right, tmp)

    min_dis = min(dis_left, dis_right)
    merge(left_points, right_points, tmp, left)

    x_median = points[center].x
    points_within_strip = []
    for p in tmp[left: right + 1]:
        if abs(p.x - x_median) <= min_dis:
            points_within_strip.append(p)

    # calculte dis
    for i, pi in enumerate(points_within_strip):
        for pj in points_within_strip[i + 1:]:
            if pj.y - pi.y > min_dis:
                continue
            min_dis = min(dis(pi, pj), min_dis)
    return min_dis, tmp[left: right + 1]


def test_closest_dis_of_points():
    points = []
    for x, y in [[2, 3], [12, 30], [40, 50], [5, 1], [12, 10], [3, 4]]:
        points.append(Point(x, y))
    result = closest_dis_of_points(points)
    print('result: ', result)
    assert abs(result - 1.41421) < 0.001

def test_improved_closest_dis_of_points():
    points = []
    for x, y in [[2, 3], [12, 30], [40, 50], [5, 1], [12, 10], [3, 4]]:
        points.append(Point(x, y))
    result = improved_dis_of_points(points)
    print('result: ', result)

test_closest_dis_of_points()
test_improved_closest_dis_of_points()


BASE = 100
def test_time_complexion_for_closest_dis_of_points():
    print('closest_dis_of_points[OLogNLogN]: ', end='')
    size = BASE
    for ratio in range(10):
        size *= 2

        points = []
        for x, y in np.random.randint(0, 1e6, size=(size, 2)):
            points.append(Point(x, y))
        start = time.time()
        closest_dis_of_points(points)
        used = int((time.time() - start) * 1000)
        print('size:', size, 'time:', used, 'T(N)/N:',round(used/ size * 1e5), 'T(N)/(NLogN):', round(used / (size * math.log2(size)) * 1e5), 'T(N)/(NLogNLogN):', round(used / (size * math.log2(size) ** 2) * 1e5), end='')
        print()

test_time_complexion_for_closest_dis_of_points()

def test_time_complexion_for_improved_closest_dis_of_points():
    print('improved_closest_dis_of_points[OLogN]: ', end='')
    size = BASE
    for ratio in range(10):
        size *= 2

        points = []
        for x, y in np.random.randint(0, 1e6, size=(size, 2)):
            points.append(Point(x, y))
        start = time.time()
        improved_dis_of_points(points)
        used = int((time.time() - start) * 1000)
        print('size:', size, 'time:', used, 'T(N)/N:',round(used/ size * 1e5), 'T(N)/(NLogN):', round(used / (size * math.log2(size)) * 1e5), 'T(N)/(NLogNLogN):', round(used / (size * math.log2(size) ** 2) * 1e5), end='')
        print()
test_time_complexion_for_improved_closest_dis_of_points()

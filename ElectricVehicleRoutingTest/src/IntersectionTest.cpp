#include "IntersectionTest.h"
#include <Intersection.h>
#include <cassert>

void IntersectionTest::runTests()
{
	Intersection intersection(1, 10, 100);

	assert(intersection.getId() == 1);
	assert(intersection.getX() == 10);
	assert(intersection.getY() == 100);

	Intersection intersection1(1, 20, 20);
	assert(intersection == intersection1);

	Intersection intersection2(2, 10, 100);
	assert(intersection != intersection2);
}

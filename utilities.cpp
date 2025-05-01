#include "utilities.h"

float twoPointsDistance(glm::vec3 firstPoint, glm::vec3 secondPoint) {
	return sqrt(pow(firstPoint.x - secondPoint.x, 2) + pow(firstPoint.y - secondPoint.y, 2) + pow(firstPoint.z - secondPoint.z, 2));
}
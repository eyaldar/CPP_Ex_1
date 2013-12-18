#ifndef __SHAPES_COLLISION_MANAGER_H__
#define __SHAPES_COLLISION_MANAGER_H__

#include "Shape.h"

class ShapesCollisionManager
{
public:
	ShapesCollisionManager(const Shape& firstShape, const Shape& secondShape);

	void updateShapesRelations();

	bool hasCollided() const;

private:
	const Shape& m_first_shape;
	const Shape& m_second_shape;

	bool m_had_inclusuion_relation;
	bool m_had_intersection_relation;

	bool m_has_inclusuion_relation;
	bool m_has_intersection_relation;

	const Shape* m_prev_leftmost_shape;
	const Shape* m_prev_rightmost_shape;
	const Shape* m_prev_topmost_shape;
	const Shape* m_prev_bottommost_shape;

	const Shape* m_curr_leftmost_shape;
	const Shape* m_curr_rightmost_shape;
	const Shape* m_curr_topmost_shape;
	const Shape* m_curr_bottommost_shape;

	// Returns the leftmost shape of the tow given shapes
	const Shape* getLeftmostShape() const;

	// Returns the rightmost shape of the tow given shapes
	const Shape* getRighmostShape() const;

	// Returns the topmost shape of the tow given shapes
	const Shape* getTopmostShape() const;

	// Returns the bottommost shape of the tow given shapes
	const Shape* getBottommostShape() const;
	
	// Determines whether one of the relations changed
	bool hasShapeRelationsChanged() const;

	// Determines whether one of the --X--Most values changed
	bool hasShapeEdgesChanged() const;
};

#endif
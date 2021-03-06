#include "ShapesCollisionDetector.h"

ShapesCollisionDetector::ShapesCollisionDetector(const Shape& firstShape, const Shape& secondShape) 
	:m_first_shape(firstShape), m_second_shape(secondShape)
{
	m_had_intersection_relation = m_has_intersection_relation = m_first_shape.isIntersectingWith(m_second_shape);							
	m_had_inclusuion_relation = m_has_inclusuion_relation = (m_first_shape.contains(m_second_shape) || m_second_shape.contains(m_first_shape));

	m_prev_leftmost_shape = m_curr_leftmost_shape = getLeftmostShape();
	m_prev_rightmost_shape = m_curr_rightmost_shape =	getRighmostShape();
	m_prev_topmost_shape = m_curr_topmost_shape = getTopmostShape();		
	m_prev_bottommost_shape = m_curr_bottommost_shape = getBottommostShape();
}

void ShapesCollisionDetector::updateShapesRelations()
{
	m_had_intersection_relation = m_has_intersection_relation;
	m_had_inclusuion_relation = m_has_inclusuion_relation;

	m_has_intersection_relation = m_first_shape.isIntersectingWith(m_second_shape);							
	m_has_inclusuion_relation = (m_first_shape.contains(m_second_shape) || m_second_shape.contains(m_first_shape));

	m_prev_leftmost_shape = m_curr_leftmost_shape;
	m_prev_rightmost_shape = m_curr_rightmost_shape;
	m_prev_topmost_shape = m_curr_topmost_shape;		
	m_prev_bottommost_shape = m_curr_bottommost_shape;

	m_curr_leftmost_shape = getLeftmostShape();
	m_curr_rightmost_shape = getRighmostShape();
	m_curr_topmost_shape = getTopmostShape();		
	m_curr_bottommost_shape = getBottommostShape();
}

const Shape* ShapesCollisionDetector::getLeftmostShape() const
{
	if(m_first_shape.getMinX() < m_second_shape.getMinX())
		return &m_first_shape;
	else
		return &m_second_shape;
}

const Shape* ShapesCollisionDetector::getRighmostShape() const
{
	if(m_first_shape.getMaxX() >= m_second_shape.getMaxX())
		return &m_first_shape;
	else
		return &m_second_shape;
}

const Shape* ShapesCollisionDetector::getTopmostShape() const
{
	if(m_first_shape.getMinY() < m_second_shape.getMinY())
		return &m_first_shape;
	else
		return &m_second_shape;
}

const Shape* ShapesCollisionDetector::getBottommostShape() const
{
	if(m_first_shape.getMaxY() >= m_second_shape.getMaxY())
		return &m_first_shape;
	else
		return &m_second_shape;
}

bool ShapesCollisionDetector::hasCollided() const
{
	return m_first_shape.isCollidingWith(m_second_shape) ||
		   m_had_intersection_relation && hasShapeEdgesChanged() || 
		   hasShapeRelationsChanged();
}

bool ShapesCollisionDetector::hasShapeRelationsChanged() const
{
	return m_had_intersection_relation != m_has_intersection_relation || 
		   m_had_inclusuion_relation != m_has_inclusuion_relation;
}

bool ShapesCollisionDetector::hasShapeEdgesChanged() const
{
	return m_curr_leftmost_shape != m_prev_leftmost_shape ||
		   m_curr_rightmost_shape != m_prev_rightmost_shape ||
		   m_curr_topmost_shape != m_prev_topmost_shape ||
		   m_curr_bottommost_shape != m_prev_bottommost_shape;
}
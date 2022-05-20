#include "sphere_geometry.hpp"

namespace RT_ISICG
{
	bool SphereGeometry::intersect( const Ray & p_ray, float & p_t1, float & p_t2 ) const
	{
		float r = getRadius();

		float x = getCenter().x;
		float y = getCenter().y;
		float z = getCenter().z;

		float a = p_ray.getOrigin().x;
		float b = p_ray.getOrigin().y;
		float c = p_ray.getOrigin().z;

		float alpha = p_ray.getDirection().x;
		float beta	= p_ray.getDirection().y;
		float gama	= p_ray.getDirection().z;
		// Equation de la sphere

		float s = glm::inversesqrt( x - p_ray.getDirection().x ) + glm::inversesqrt( y - p_ray.getDirection().y )
				  + glm::inversesqrt( z - p_ray.getDirection().z ) - getRadius();

		/*float A = (2*alpha) + (2*beta) + (2*gama);
		float B = (2*a*alpha) - (2*x*alpha) + (2*b*beta) - (2*y*beta) + (2*c*gama) - (2*z*gama);
		float C = (-a*x) - (x*a) - (x*x) - (b*y) - (y*b) - (b*b) - (c*z) - (z*c) - (z*z) - (r*r);

		float delta = ( B * B ) - ( 4 * A * C );*/

		float A = glm::dot( p_ray.getDirection(), p_ray.getDirection() );
		float B = 2 * glm::dot( p_ray.getDirection(), p_ray.getOrigin() - getCenter() );
		float C = glm::dot( p_ray.getOrigin() - getCenter(), p_ray.getOrigin() - getCenter() ) - ( r * r );

		float delta = ( B * B ) - ( 4 * A * C );
		float p_1, p_2;
		if ( delta > 0 )
		{
			p_1 = ( -B - glm::sqrt( delta ) ) / ( 2 * A );
			p_2 = ( -B + glm::sqrt( delta ) ) / ( 2 * A );
			// return true;

			if ( p_1 <= p_2 )
			{
				p_t1 = p_1;
				p_t2 = p_2;
				return true;
			}
			else if ( p_1 > p_2 )
			{
				p_t1 = p_2;
				p_t2 = p_1;
				return true;
			}
		}

		else
		{
			p_t1 = -1.f;
			p_t2 = -1.f;

			return false;
		}
	}

} // namespace RT_ISICG

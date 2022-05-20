#include "aabb.hpp"

namespace RT_ISICG
{
	bool AABB::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		/// TODO



		float t1x = ( getMin().x - p_ray.getOrigin().x ) / p_ray.getDirection().x;
		float t2x = ( getMax().x - p_ray.getOrigin().x ) / p_ray.getDirection().x;
		float t_min_x	  = fminf( t1x, t2x );
		float t_max_x = fmaxf( t1x, t2x );

		float t1y	  = ( getMin().y - p_ray.getOrigin().y ) / p_ray.getDirection().y;
		float t2y	  = ( getMax().y - p_ray.getOrigin().y ) / p_ray.getDirection().y;
		float t_min_y = fminf( t1y, t2y );
		float t_max_y = fmaxf( t1y, t2y );

		float t1z	  = ( getMin().z - p_ray.getOrigin().z ) / p_ray.getDirection().z;
		float t2z	  = ( getMax().z - p_ray.getOrigin().z ) / p_ray.getDirection().z;
		float t_min_z = fminf( t1z, t2z );
		float t_max_z = fmaxf( t1z, t2z );


		if ( fminf( fminf( t_max_x, t_max_y ), t_max_z ) - fmax( fmax( t_min_x, t_min_y ), t_min_z ) > 0 ) 
			return true;

		return false;
	}
} // namespace RT_ISICG

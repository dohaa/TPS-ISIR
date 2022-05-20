#pragma once
#ifndef __RT_ISICG_QUAD_LIGHT__
#define __RT_ISICG_QUAD_LIGHT__

#include "defines.hpp"
#include "lights/base_light.hpp"
#include <utils/random.hpp>
#include <cmath>

namespace RT_ISICG
{
	class QuadLight : public BaseLight
	{
	  public:
		QuadLight( const Vec3f & p_position,
				   const Vec3f & p_u,
				   const Vec3f & p_v,
				   const Vec3f & p_color,
				   const float	 p_power )
			: BaseLight( p_color, p_power ), _position( p_position ), _u( p_u ), _v( p_v ),
			  _normal( glm::normalize( glm::cross( _u, _v ) ) ), _area(glm::length(_u) * glm::length(_v))
		{
		}

		virtual LightSample sample( const Vec3f & p_position ) const;


		Vec3f _position;
		Vec3f _u;
		Vec3f _v;
		Vec3f _normal;
			//Vec3f( glm::dot( _u.y, _v.z ) - glm::dot( _u.z, _v.y ),
				//			   glm::dot( _u.z, _v.x ) - glm::dot( _u.x, _v.z ),
					//		   glm::dot( _u.x, _v.y ) - glm::dot( _u.y, _v.x ) );
		float	  _area;

	};
} // namespace RT_ISICG
#endif // __RT_ISICG_QUAD_LIGHT__

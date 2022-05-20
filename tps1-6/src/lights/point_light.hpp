#pragma once
#ifndef __RT_ISICG_PERSPECTIVE_CAMERA__
#define __RT_ISICG_PERSPECTIVE_CAMERA__

#include "defines.hpp"
#include "lights/base_light.hpp"

namespace RT_ISICG
{
	class PointLight : public BaseLight
	{
	  public:
		PointLight( const Vec3f & p_color, const float p_power, const Vec3f p_position )
			: BaseLight( p_color, p_power ), _position( p_position )
		{
		}

		virtual LightSample sample( const Vec3f & p_point ) const;

		Vec3f _position;
	};
} // namespace RT_ISICG
#endif // __RT_ISICG_PERSPECTIVE_CAMERA__
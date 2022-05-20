#include "point_light.hpp"

namespace RT_ISICG
{
	LightSample PointLight::sample( const Vec3f & p_point ) const
	{
		Vec3f r = _color * _power * ( 1.f / (glm::distance( _position, p_point ) * glm::distance( _position, p_point ) ) );
		
		return LightSample( normalize( _position - p_point ), glm::distance( _position, p_point ), r, 1.f );
	}
} // namespace RT_ISICG
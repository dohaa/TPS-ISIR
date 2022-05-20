#include "quad_light.hpp"


namespace RT_ISICG
{
	LightSample QuadLight::sample( const Vec3f & p_point ) const
	{
		Vec3f upos	= _u * randomFloat();
		Vec3f vpos	 = _v * randomFloat();
		Vec3f posRand = Vec3f(_position+upos+vpos);
		float distance = glm::distance( posRand, p_point );

		Vec3f _direction = normalize( posRand - p_point );
		float pdf = ( 1.f/_area )* (( distance *distance )/  glm::dot( _normal,_direction ) );
		Vec3f r = _color * _power / pdf;

		return LightSample(_direction, distance, r,pdf);
	}
} // namespace RT_ISICG
#include "direct_lighting_integrator.hpp"

namespace RT_ISICG
{
	Vec3f DirectLightingIntegrator::Li( const Scene & p_scene,
										const Ray &	  p_ray,
										const float	  p_tMin,
										const float	  p_tMax ) const
	{
		//printf( "light" );
		std::vector<BaseLight *> tmpLight  = p_scene.getLights();
		Vec3f					 luminance = VEC3F_ZERO;

		HitRecord hitRecord;
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			/// TODO ! cos theta..
			
			for ( int i = 0; i < tmpLight.size(); i++ )
			{
				
				LightSample light		= tmpLight[ i ]->sample( hitRecord._point );
				if ( tmpLight[ i ]->get_isSurface() == true )
				{
					for (int j = 0; j < _nbLightSamples; j++) {
						Ray shadow( hitRecord._point, light._direction );
						shadow.offset( hitRecord._normal );
						if ( !p_scene.intersectAny( shadow, SHADOW_EPSILON, light._distance ) )
						{
							Vec3f originColor = hitRecord._object->getMaterial()->shade( p_ray, hitRecord, light );
							float costheta	  = glm::max( 0.f, glm::dot( light._direction, hitRecord._normal ) );

							luminance += originColor * light._radiance * costheta;
						}
					}
				}
				

			}
			luminance /= _nbLightSamples;
			return glm::clamp( luminance, 0.f, 1.f );
		}
		else
		{
			return _backgroundColor;
		}
	}
} // namespace RT_ISICG

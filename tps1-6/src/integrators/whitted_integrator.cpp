#include "whitted_integrator.hpp"

namespace RT_ISICG
{


	Vec3f WhittedIntegrator::LiRec( const Scene & p_scene,
								  const Ray &	p_ray,
								  const float	p_tMin,
								  const float	p_tMax,
								  int			prof )const
	{

		// printf( "ici" );
		//int nbBounces = _nbBounces;
		if ( prof > _nbBounces ) { return VEC3F_ZERO; }
		std::vector<BaseLight *> tmpLight  = p_scene.getLights();
		Vec3f					 luminance = VEC3F_ZERO;

		HitRecord hitRecord;
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			if ( hitRecord._object->getMaterial()->isMirror() == true )
			{
				// printf( "est miroir" );
				Vec3f miror_dir = glm::reflect( p_ray.getDirection(), hitRecord._normal );

				Ray ray_miror( hitRecord._normal, miror_dir );
				//nbBounces--;
				return luminance = LiRec( p_scene, ray_miror, p_tMin, p_tMax,prof++);
			}
			/* else if ( hitRecord._object->getMaterial()->isTransparent() == true )
			{
				/* const Vec3f reflectDir( glm::normalize( glm::reflect( p_ray.getDirection(), hitRecord._normal ) ) );
				float n1 = 1.f;
				float n2 = 1.3f;
				Vec3f  normale_transparency( hitRecord._normal );
				if (dot(p_ray.getDirection(), hitRecord._normal) > 0) { 
					n1 = 1.3;
					n2 = 1;
					normale_transparency = -hitRecord._normal;
				}

				const Vec3f reflectDir( glm::normalize( glm::reflect( p_ray.getDirection(), hitRecord._normal ) ) );

				const float ni	= inside ? hitRecord._object->getMaterial()->getIOR() : refractIdx;
				const float no	= inside ? refractIdx : hitRecord._object->getMaterial()->getIOR();
				const float eta = ni / no;

				const float cosThetaIn = glm::dot( hitRecord._normal, -p_ray.getDirection() );
				if ( ( glm::asin( 1.f / eta ) < glm::acos( cosThetaIn ) ) && ( ni > no ) )
				{
					luminance += LiRec( p_scene, Ray( hitRecord._point, reflectDir ), p_tMin, p_tMax, prof++ );
				}
				else
				{
					const Vec3f refractDir(glm::normalize( glm::refract( p_ray.getDirection(), hitRecord._normal,( n1 / n2 ) ) ) );
					const float R = fresnelEquation( refractDir, hitRecord._normal, n1, n2, cosThetaIn );
					luminance += R * LiRec( p_scene, Ray( hitRecord._point, reflectDir ), p_tMin, p_tMax, prof++ )
						   + ( 1.f - R )
									   * LiRec( p_scene, Ray( hitRecord._point, refractDir ), p_tMin, p_tMax, prof++ );
				}
			
				
			return luminance;
			}*/
			else
			{
				for ( int i = 0; i < tmpLight.size(); i++ )
				{
					LightSample light = tmpLight[ i ]->sample( hitRecord._point );
					if ( tmpLight[ i ]->get_isSurface() == true )
					{
						for ( int j = 0; j < _nbLightSamples; j++ )
						{
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
		}
		else
		{
			return _backgroundColor;
		}
	}

	Vec3f WhittedIntegrator::Li( const Scene & p_scene,
										const Ray &	  p_ray,
								 const float			p_tMin,
								 const float p_tMax)const
	{

		int profondeur = 0;
		return LiRec(p_scene,p_ray,p_tMin,p_tMax,profondeur);

			
	}
} // namespace RT_ISICG

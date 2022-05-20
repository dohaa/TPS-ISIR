#ifndef __RT_ISICG_WHITTED_INTEGRATOR__
#define __RT_ISICG_WHITTED_INTEGRATOR__

#include "direct_lighting_integrator.hpp"

namespace RT_ISICG
{
	class WhittedIntegrator : public DirectLightingIntegrator
	{
	  public:
		WhittedIntegrator() : DirectLightingIntegrator() {}
		virtual ~WhittedIntegrator() = default;

		const IntegratorType getType() const override
		{
			return IntegratorType::MIROR;
		}

		// Return incoming luminance.
		Vec3f Li( const Scene & p_scene, const Ray & p_ray, const float p_tMin, const float p_tMax)const override ;

		Vec3f LiRec( const Scene & p_scene, const Ray & p_ray, const float p_tMin, const float p_tMax, int prof ) const;

		
		int _nbBounces = 5;
		int _nbLightSamples = 50;

		private:
		float fresnelEquation( const Vec3f & I,
							   const Vec3f & N,
							   const float	 ni,
							   const float	 no,
							   const float	 cosThetaIn ) const
		{
			const float cosThetaOut = glm::dot( -N, I );
			const float Rs			= ( no * cosThetaIn - ni * cosThetaOut ) / ( no * cosThetaIn + ni * cosThetaOut );
			const float Rp			= ( ni * cosThetaIn - no * cosThetaOut ) / ( ni * cosThetaIn + no * cosThetaOut );
			return ( Rs * Rs + Rp * Rp ) * 0.5f;
		}
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_WHITTED_INTEGRATOR__
#ifndef __RT_ISICG_REALISTIC_MATERIAL__
#define __RT_ISICG_REALISTIC_MATERIAL__

#include "base_material.hpp"
#include "brdfs/cook_torrance.hpp"
#include "brdfs/oren_nayar_brdf.hpp"

namespace RT_ISICG
{
	class RealisticMaterial : public BaseMaterial
	{
	  public:
		RealisticMaterial( const std::string & p_name, const Vec3f & p_diffuse, const Vec3f & p_specular )
			: BaseMaterial( p_name ), _oren_nayar_brdf( p_diffuse ), _cook_torrance_brdf( p_specular )
		{
		}

		virtual ~RealisticMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			return ( ( 1 - _metalness )
					 * _oren_nayar_brdf.evaluate(
						 p_hitRecord._normal, p_lightSample._direction, p_ray.getDirection() ) )
				   + _metalness
						 * _cook_torrance_brdf.evaluate(
							 p_hitRecord._normal, p_lightSample._direction, p_ray.getDirection() ,0.85f);
		}

		inline const Vec3f & getFlatColor() const override { return _oren_nayar_brdf.getKd(); }

	  protected:
		OrenNayarBRDF _oren_nayar_brdf;
		CookTorranceBRDF _cook_torrance_brdf;
		float _metalness = 0;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_REALISTIC_MATERIAL__

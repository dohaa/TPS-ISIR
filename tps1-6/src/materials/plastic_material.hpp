#ifndef __RT_ISICG_PLASTIC_MATERIAL__
#define __RT_ISICG_PLASTIC_MATERIAL__

#include "base_material.hpp"
#include "brdfs/lambert_brdf.hpp"
#include "brdfs/phong_brdf.hpp"

namespace RT_ISICG
{
	class PlasticMaterial : public BaseMaterial
	{
	  public:
		PlasticMaterial( const std::string & p_name, const Vec3f & p_diffuse,const Vec3f & p_specular )
			: BaseMaterial( p_name ), _brdf( p_diffuse ), _phong_brdf(p_specular)
		{
		}

		virtual ~PlasticMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			return _brdf.evaluate() + _phong_brdf.evaluate(p_lightSample._direction,p_hitRecord._normal, p_ray.getDirection());
		}

		inline const Vec3f & getFlatColor() const override { return _brdf.getKd(); }

	  protected:
		LambertBRDF _brdf;
		PhongBRDF	_phong_brdf;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_PLASTIC_MATERIAL__

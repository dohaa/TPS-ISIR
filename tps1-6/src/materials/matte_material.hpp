#ifndef __RT_ISICG_MATTE_MATERIAL__
#define __RT_ISICG_MATTE_MATERIAL__

#include "base_material.hpp"
#include "brdfs/lambert_brdf.hpp"
#include "brdfs/oren_nayar_brdf.hpp"

namespace RT_ISICG
{
	class MatteMaterial : public BaseMaterial
	{
	  public:
		MatteMaterial( const std::string & p_name, const Vec3f & p_diffuse, const Vec3f & p_specular )
			: BaseMaterial( p_name ), _brdf( p_diffuse ), _oren_nayar_brdf(p_specular)
		{
		}

		virtual ~MatteMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			return _brdf.evaluate()
				   * _oren_nayar_brdf.evaluate(p_hitRecord._normal, p_lightSample._direction,p_ray.getDirection());
		}

		inline const Vec3f & getFlatColor() const override { return _brdf.getKd(); }

	  protected:
		LambertBRDF _brdf;
		OrenNayarBRDF	_oren_nayar_brdf;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_MATTE_MATERIAL__

#ifndef __RT_ISICG_TRANSPARENT_MATERIAL__
#define __RT_ISICG_TRANSPARENT_MATERIAL__

#include "base_material.hpp"

namespace RT_ISICG
{
	class TransparentMaterial : public BaseMaterial
	{
	  public:
		TransparentMaterial( const std::string & p_name ) : BaseMaterial( p_name ) {}

		virtual ~TransparentMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			return BLACK;
		}

		inline const Vec3f & getFlatColor() const override { return BLACK; }

		//inline const bool & isMirror() { return true; }
		inline const bool & isTransparent() { return true; }

		inline const float & getIOR() { return _ior; }
	  protected:

		  float _ior = 1.3;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_TRANSPARENT_MATERIAL__

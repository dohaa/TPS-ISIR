#ifndef __RT_ISICG_BRDF_PHONG__
#define __RT_ISICG_BRDF_PHONG__

#include "defines.hpp"

namespace RT_ISICG
{
	class PhongBRDF
	{
	  public:
		PhongBRDF( const Vec3f & p_ks ):  _ks( p_ks ){};

		// * INV_PIf : could be done in the constructor...
		inline Vec3f evaluate( Vec3f position, Vec3f normal,Vec3f v) const { return _ks * pow(glm::dot(glm::reflect( position, normal ),v),s); }

		inline const Vec3f & getKs() const { return _ks; }

	  private:
	
		Vec3f _ks = WHITE;
		float	  s	  = 64.f;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_PHONG__
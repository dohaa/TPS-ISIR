#ifndef __RT_ISICG_BRDF_OREN_NAYAR__
#define __RT_ISICG_BRDF_OREN_NAYAR__

#include "defines.hpp"

namespace RT_ISICG
{
	class OrenNayarBRDF
	{
	  public:
		OrenNayarBRDF( const Vec3f & p_kd ) : _kd( p_kd ) {};

		// * INV_PIf : could be done in the constructor...
		inline Vec3f evaluate( Vec3f normal, Vec3f lightDir,Vec3f viewDir ) const
		{ 

			float nDotL = glm::clamp( glm::dot( normal, -lightDir ), 0.f, 1.f );
			float nDotV = glm::clamp( glm::dot( normal, -viewDir ), 0.f, 1.f );

			float incidentTheta = acos( nDotL );
			float outTheta		= acos( nDotV );

			float a = 1.f - (0.5 * (pow(theta,2) / (pow(theta,2)+0.33f)));
			float b = (0.45f * ( pow( theta, 2 ) )/ ( pow( theta, 2 ) + 0.99f ) );
			float alpha = glm::max( incidentTheta, outTheta );
			float beta	= glm::min( incidentTheta, outTheta );

			Vec3f  u		  = normalize( -viewDir - normal * nDotV );
			Vec3f  v		  = normalize( -lightDir - normal * nDotL );
			float phiDiff = glm::max( 0.f, dot( u, v ) );
			
			return Vec3f( a + b * phiDiff * sin( alpha ) * tan( beta ),
						  a + b * phiDiff * sin( alpha ) * tan( beta ),
						  a + b * phiDiff * sin( alpha ) * tan( beta ) );
			
			 }

		inline const Vec3f & getKd() const { return _kd; }

	  private:
		Vec3f _kd = WHITE;
		float theta = 0.f;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_OREN_NAYAR__

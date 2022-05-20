#ifndef __RT_ISICG_BRDF_COOK_TORRANCE__
#define __RT_ISICG_BRDF_COOK_TORRANCE__
#include "defines.hpp"

namespace RT_ISICG
{
	class CookTorranceBRDF
	{
	  public:
		CookTorranceBRDF( const Vec3f & p_kd ) : _kd( p_kd ) {};

		// * INV_PIf : could be done in the constructor...
		inline float D( Vec3f h,Vec3f n ) const { 
			int alpha = pow( theta, 2 );
			int nh	  = pow(glm::dot(n,h), 2 );
			int alp	  = pow( alpha, 2 ) - 1;
			return alpha / ( pow( PIf * ( ( nh * alp ) + 1 ), 2 ) );
		}

		inline float G( float x ) const{ 
			float k = pow( theta + 1, 2 ) / 8;
			return x / ( ( x * ( 1 - k ) ) + k );

		}
		inline Vec3f evaluate( Vec3f normal, Vec3f lightDir, Vec3f viewDir ,float F) const
		{ 
			Vec3f h		= ( viewDir + lightDir ) / abs( viewDir + lightDir );
			float ndotwo = glm::dot( normal, viewDir );
			float ndotwi = glm::dot( normal, lightDir );
			float wodotn = glm::dot( viewDir,normal );
			float widotn = glm::dot( lightDir,normal );
			float hdotwo = glm::dot( h, viewDir );

			// D
			float d = D( h, normal );
			// G
			float g = G( ndotwo ) * G( ndotwi );
			// F
			float f = F + (1-F)* pow( 1.0 - hdotwo, 5.0 );
		
		


			return Vec3f(( d * g * f ) / 4 * wodotn * widotn);
		}

		//inline const Vec3f & getKd() const { return _kd; }

	  private:
		Vec3f _kd ;
		int	  theta = 0.3;
	
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_COOK_TORRANCE__
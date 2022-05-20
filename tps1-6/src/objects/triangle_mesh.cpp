#include "triangle_mesh.hpp"

namespace RT_ISICG
{
	bool MeshTriangle::intersect( const Ray & p_ray,
								  const float p_tMin,
								  const float p_tMax,
								  HitRecord & p_hitRecord ) const
	{
		if ( _aabb.intersect( p_ray, p_tMin, p_tMax ) )
		{
			float  tClosest = p_tMax;			 // Hit distance.
			size_t hitTri	= _triangles.size(); // Hit triangle id.
			float  u = 0.f, v = 0.f;
			for ( size_t i = 0; i < _triangles.size(); i++ )
			{
				float t, utmp, vtmp;
				if ( _triangles[ i ].intersect( p_ray, t, utmp, vtmp ) )
				{
					if ( t >= p_tMin && t <= tClosest )
					{
						tClosest = t;
						hitTri	 = i;
						u		 = utmp;
						v		 = vtmp;
					}
				}
			}
			if ( hitTri != _triangles.size() ) // Intersection found.
			{
				p_hitRecord._point	= p_ray.pointAtT( tClosest );
				p_hitRecord._normal = _triangles[ hitTri ].getFaceNormal();
				p_hitRecord.faceNormal( p_ray.getDirection() );
				p_hitRecord._distance = tClosest;
				p_hitRecord._object	  = this;

				return true;
			}
		} 
		return false;
	}

	bool MeshTriangle::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		for ( size_t i = 0; i < _triangles.size(); i++ )
		{
			float t;
			float u, v;
			if ( _triangles[ i ].intersect( p_ray, t,u,v ) )
			{
				if ( t >= p_tMin && t <= p_tMax ) return true; // No need to search for the nearest.
			}
		}
		return false;
	}


	/* void MeshTriangle::set_min_max_()
	{ 
		Vec3f min = _vertices[ 0 ], max = _vertices[ 0 ];
		for (int i = 1; i < getNbVertices(); i++) {
			min.x = fminf( min.x, _vertices[ i ].x ); 
			min.y = fminf( min.y, _vertices[ i ].y );
			min.z = fminf( min.z, _vertices[ i ].z ); 

			max.x = fminf( max.x, _vertices[ i ].x );
			max.y = fminf( max.y, _vertices[ i ].y );
			max.z = fminf( max.z, _vertices[ i ].z ); 
		}

		_aabb = AABB( min, max );
	}*/

} // namespace RT_ISICG

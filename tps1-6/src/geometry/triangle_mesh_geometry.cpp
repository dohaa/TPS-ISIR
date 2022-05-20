#include "triangle_mesh_geometry.hpp"
#include "objects/triangle_mesh.hpp"

namespace RT_ISICG
{
	TriangleMeshGeometry::TriangleMeshGeometry( const unsigned int p_v0,
												const unsigned int p_v1,
												const unsigned int p_v2,
												MeshTriangle *	   p_refMesh )
		: _v0( p_v0 ), _v1( p_v1 ), _v2( p_v2 ), _refMesh( p_refMesh )
	{
		_faceNormal = glm::normalize( glm::cross( _refMesh->_vertices[ p_v1 ] - _refMesh->_vertices[ p_v0 ],
												  _refMesh->_vertices[ p_v2 ] - _refMesh->_vertices[ p_v0 ] ) );
	}

	bool TriangleMeshGeometry::intersect( const Ray & p_ray, float & p_t, float & p_u, float & p_v ) const
	{
		const Vec3f & o	 = p_ray.getOrigin();
		const Vec3f & d	 = p_ray.getDirection();
		const Vec3f & v0 = _refMesh->_vertices[ _v0 ];
		const Vec3f & v1 = _refMesh->_vertices[ _v1 ];
		const Vec3f & v2 = _refMesh->_vertices[ _v2 ];

		/* Vec3f edge1, edge2, tvec, pvec, qvec;
		double det, inv_det;

		edge1.x = v1.x - v0.x;
		edge1.y = v1.y - v0.y;
		edge1.z = v1.z - v0.z;

		edge2.x = v2.x - v0.x;
		edge2.y = v2.y - v0.y;
		edge2.z = v2.z - v0.z;

		pvec.x = d.y * edge2.z - d.z * edge2.y;
		pvec.y = d.z * edge2.x - d.x * edge2.z;
		pvec.z = d.x * edge2.y - d.y * edge2.x;

		det = edge1.x * pvec.x + edge1.y * pvec.y + edge1.z * pvec.z;

		if (SHADOW_EPSILON > det) { return false;
		}

		tvec.x = o.x - v0.x;
		tvec.y = o.y - v0.y;
		tvec.z = o.z - v0.z;

		float u = glm::dot( tvec, pvec );

		if ( u < 0.0 || u > det ) { return false; }

		qvec.x = tvec.y * edge1.z - tvec.z * edge1.y;
		qvec.y = tvec.z * edge1.x - tvec.x * edge1.z;
		qvec.z = tvec.x * edge1.y - tvec.y * edge1.x;

		float v = glm::dot( d, qvec );

		if ( v < 0.0 || u+v > det ) { return false; }

		float t = glm::dot( qvec,edge2 );
		inv_det = 1 / det;
		t *= inv_det;
		u *= inv_det;
		v *= inv_det;

		if ( det > -SHADOW_EPSILON && det < SHADOW_EPSILON ) { return false; }
		inv_det = 1 / det;

		tvec.x = o.x - v0.x;
		tvec.y = o.y - v0.y;
		tvec.z = o.z - v0.z;

		u = glm::dot( tvec, pvec ) * inv_det;

		if ( u < 0.0 || u > 1.0 ) { return false; }

		qvec.x = tvec.x - v1.x;
		qvec.y = tvec.y - v1.y;
		qvec.z = tvec.z - v1.z;

		v = glm::dot( d, qvec ) * inv_det;

		if ( v < 0.0 || u + v > 1.0 ) { return false; }

		t = glm::dot( edge2, qvec ) * inv_det;

		/// TODO
		return true;
		*/

		Vec3f edge1 = v1 - v0;
		Vec3f edge2 = v2 - v0;
		Vec3f pvec	= glm::cross( d, edge2 );
		float det	= glm::dot( edge1, pvec );
		float inv_det;
		if ( det < 0.00001f ) 
			return false;
		
		Vec3f tvec = o - v0;
		p_u		   = glm::dot( tvec, pvec );
		
		if ( p_u < 0.f || p_u > det ) return false;
		Vec3f qvec = glm::cross( tvec, edge1 );
		p_v		   = glm::dot( d, qvec );
		
		if ( p_v < 0.f || p_u + p_v > det ) return false;
		p_t			  = glm::dot( edge2, qvec );
		inv_det = 1.f / det;
		p_t *= inv_det;
		p_u *= inv_det;
		p_v *= inv_det;

		if ( det > -0.00001f && det < 0.00001f ) 
			return false;
		inv_det = 1.f / det;
		tvec	  = o - v0;
		p_u			  = glm::dot( tvec, pvec ) * inv_det;
		
		if ( p_u < 0.f || p_u > 1.f ) return false;
		qvec = glm::cross( tvec, edge1 );
		p_v		   = glm::dot( d, qvec ) * inv_det;
		
		if ( p_v < 0.f || p_u + p_v > 1.f ) return false;
		p_t = glm::dot( edge2, qvec ) * inv_det;

		return true;
	}


} // namespace RT_ISICG

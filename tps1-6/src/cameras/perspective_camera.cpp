#include "perspective_camera.hpp"
#include <glm/gtx/string_cast.hpp>

namespace RT_ISICG
{
	PerspectiveCamera::PerspectiveCamera( const float p_aspectRatio ) : _aspectRatio( p_aspectRatio )
	{

		_updateViewport();
	}

	PerspectiveCamera::PerspectiveCamera( const Vec3f & p_position,
										  const Vec3f & p_lookAt,
										  const Vec3f & p_up,
										  const float	p_fovy,
										  const float	p_aspectRatio )
		: BaseCamera( p_position ), _fovy( p_fovy ), _aspectRatio( p_aspectRatio )
	{
		/// TODO ! _u ? _v ? _w ?

		_w = glm::normalize( p_position - p_lookAt );
		_u = normalize( cross( _w, p_up ) );
		_v = normalize( cross( _u, _w ) );

		_updateViewport();
	}

	void PerspectiveCamera::_updateViewport()
	{
		/// TODO ! _viewportTopLeftCorner ?	_viewportU ? _viewportV ?
		float h = 2.0f * tan( glm::radians( _fovy ) * 0.5f ) * _focalDistance;

		_viewportV			   = _v * h;
		_viewportU			   = -_u * h * _aspectRatio;
		_viewportTopLeftCorner = _position + ( _viewportV - _viewportU ) * 0.5f - _focalDistance * _w;

	}

} // namespace RT_ISICG

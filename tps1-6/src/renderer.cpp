#include "renderer.hpp"
#include "integrators/ray_cast_integrator.hpp"
#include "integrators/whitted_integrator.hpp"
#include "integrators/direct_lighting_integrator.hpp"
#include "utils/console_progress_bar.hpp"
#include "utils/random.hpp"

namespace RT_ISICG
{
	Renderer::Renderer() { _integrator = new RayCastIntegrator(); }

	void Renderer::setIntegrator( const IntegratorType p_integratorType )
	{
		if ( _integrator != nullptr ) { delete _integrator; }

		switch ( p_integratorType )
		{
		case IntegratorType::LIGHT: 
		{
			std::cout << "light";
			_integrator = new DirectLightingIntegrator();
			break;
		}

		case IntegratorType::MIROR:
		{
			std::cout << "miror";
			_integrator = new WhittedIntegrator();
			break;
		}
		case IntegratorType::RAY_CAST:
		default:
		{
			std::cout << "raycast";
			_integrator = new RayCastIntegrator();
			break;
		}
		}
	}

	void Renderer::setBackgroundColor( const Vec3f & p_color )
	{
		if ( _integrator == nullptr ) { std::cout << "[Renderer::setBackgroundColor] Integrator is null" << std::endl; }
		else
		{
			_integrator->setBackgroundColor( p_color );
		}
	}

	float Renderer::renderImage( const Scene & p_scene, const BaseCamera * p_camera, Texture & p_texture )
	{
		const int width	 = p_texture.getWidth();
		const int height = p_texture.getHeight();

		Chrono			   chrono;
		ConsoleProgressBar progressBar;

		progressBar.start( height, 50 );
		chrono.start();
		#pragma omp parallel for
		for ( int j = 0; j < height; j++ )
		{
			for ( int i = 0; i < width; i++ )
			{
				/// TODO !

				//p_texture.setPixel( i, j,  (ray.getDirection() + 1.f)  * 0.5f );
				//p_texture.setPixel( i, j, Vec3f( (float)i / width, (float)j / height, 0 ) );

				//p_texture.setPixel( i, j, _integrator->Li( p_scene, ray, 0, 5000 ) );
				//_integrator->Li( p_scene, ray, 0, 1000 );
				//Ray ray = p_camera->generateRay( (float)i / width, (float)j / height );

				Vec3f tmp( 0.0f );
				#pragma omp parallel for
				for ( int k = 0; k < _nbPixelSamples; k++ )
				{
					//Ray	  ray	 = p_camera->generateRay( (float)i / width, (float)j / height );
					float xfloat = randomFloat();
					float yfloat = randomFloat();
					float x		 = (float)( i + xfloat ) / width;
					float y		 = (float)( j + yfloat ) / height;

					Vec3f coltmp = _integrator->Li( p_scene, p_camera->generateRay( x, y ), 0.0f, 1000.0f);
					tmp			 = tmp + coltmp;
				}
				//Vec3f vcolor( (float)cmpx / _nbPixelSamples, (float)cmpy / _nbPixelSamples, 0.0 );
				tmp = tmp / (float)( _nbPixelSamples );
				p_texture.setPixel( i, j, tmp );
			}
			progressBar.next();
		}

		chrono.stop();
		progressBar.stop();

		return chrono.elapsedTime();
	}
} // namespace RT_ISICG

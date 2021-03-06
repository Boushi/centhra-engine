//- Centhra Engine 
#include <CE/Base.h>
#include <CE/Game2D/PhysicalText.h>

//- Standard Library -
#include <stdarg.h>
#include <stdio.h>
#include <string>

#ifdef _WIN32
	//- Windows -
	#include <Windows.h>
#endif

//- OpenGL -
#include <GL/gl.h>

#ifdef _WIN32
	//- Windows -
	#include <Windows.h>
	#define snprintf _snprintf_s
	#define vsnprintf _vsnprintf_s
#endif

using namespace std;

// - TODO: Move this into a support snippet file, or Base.h -
string compileMessage(const char *format, va_list ap)
{
	char text[4096];
	vsnprintf(text, 4096, format, ap);
	return string(text);
}

namespace ce
{
	namespace game2d
	{
		PhysicalText::PhysicalText(Vector2<float> position, Vector2<float> extent, Font *font, string text) : ce::game2d::PhysicalObject(position, extent)
		{
			m_font = font;
			m_text = text;
		}
		void PhysicalText::DoRender()
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glPushMatrix();
				glColor4ubv(&m_color[0]);
				glTranslatef(m_position[0], m_position[1], 0.f);
				glRotatef(m_rotation, 0.f, 0.f, 1.f);
				//- TODO: Handle scale properly -
				//glScalef(m_extent[0], m_extent[1], 1.f);
				m_font->DrawString(m_text.c_str());
				glColor4ub(255, 255, 255, 255);
			glPopMatrix();

			glDisable(GL_BLEND);
		}
		void PhysicalText::SetText(string text)
		{
			m_text = text;
		}
		void PhysicalText::SetText(const char *format, ...)
		{
			va_list	ap;
			va_start(ap, format);
			m_text = compileMessage(format, ap);
			va_end(ap);
		}
		string PhysicalText::GetText() const
		{
			return m_text;
		}
	}
}

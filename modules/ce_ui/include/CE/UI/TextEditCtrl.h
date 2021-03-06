#ifndef _CE_UI_TEXTEDITCTRL_H_
#define _CE_UI_TEXTEDITCTRL_H_

//- Centhra Engine -
#include <CE/UI/TextCtrl.h>

namespace ce
{
	namespace ui
	{
		class TextEditCtrl : public TextCtrl
		{
			//- Temp Vars - Will be removed with abstraction -
			bool m_leftShift, m_rightShift;

		protected:
			virtual void DoRender();

		public:
			TextEditCtrl(Vector2<int> position, Vector2<int> extent, Font *font, const char *text = "", Color color = Color());

			virtual bool OnEvent(Event &event);
		};
	}
}

#endif

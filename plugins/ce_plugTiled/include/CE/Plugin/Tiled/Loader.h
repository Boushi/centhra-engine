#ifndef _CE_PLUGIN_TILED_LOADER_H_
#define _CE_PLUGIN_TILED_LOADER_H_

//- Standard Library -
#include <string>
#include <vector>

//- Centhra Engine -
#include <CE/Game2D/ComplexTileMap.h>
#include <CE/UI/CameraView2DCtrl.h>

namespace ce
{
	namespace plugin
	{
		namespace tiled
		{
			class Loader
			{
			protected:
				Loader();

			public:
				typedef struct TileSet
				{
					std::string name, file;
					unsigned short firstGID, tileWidth, tileHeight, imageWidth, imageHeight;
					Image *image;
					game2d::TileSet *tileSet;
				} TileSet;

				typedef enum LayerType
				{
					Unknown,
					Tile,
					Object
				} LayerType;

				class Layer
				{
				public:
					std::string m_name;
					bool m_renderView;
					unsigned short m_type, m_width, m_height;

					Layer();

					virtual void Render(ui::CameraView2DCtrl *viewCtrl);
				};

				class TileLayer : public Layer
				{
				public:
					game2d::ComplexTileMap *m_tileMap;

					TileLayer();
					~TileLayer();

					virtual void Render(ui::CameraView2DCtrl *viewCtrl);
				};

				class ObjectDef
				{
				public:
					short m_x, m_y;

					ObjectDef();
				};

				class ObjectLayer : public Layer
				{
				public:
					ObjectLayer();

					virtual void Render(ui::CameraView2DCtrl *viewCtrl);
				};

				static Loader *CreateFromFile(const char *file);

				~Loader();

				void Render(ui::CameraView2DCtrl *viewCtrl);

				virtual void LoadObject(Layer *layer, ObjectDef *object);

			protected:
				std::string m_file;
				Vector2<unsigned short> m_size;
				std::vector<Layer *> m_layerVec;
				std::vector<TileSet *> m_tileSetVec;
			};
		}
	}
}

#endif

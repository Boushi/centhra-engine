//- Standard Library -
#include <math.h>
#include <vector>
#include <map>

//- Centhra Engine -
#include <CE/Game2D/Plane.h>
#include <CE/Base.h>

using namespace std;

namespace ce
{
	namespace game2d
	{
		Plane::Plane(unsigned int width, unsigned int height, float zoneSize)
		{
			m_width = width;
			m_height = height;
			m_zoneSize = zoneSize;
			m_zones = new Zone **[m_width];
			for(unsigned int a = 0; a < m_width; a++)
			{
				m_zones[a] = new Zone *[m_height];
				for(unsigned b = 0; b  < m_height; b++)
				{
					m_zones[a][b] = new Zone(a * m_zoneSize, b * m_zoneSize, (a + 1) * m_zoneSize, (b + 1) * m_zoneSize);
					m_zones[a][b]->SetPlane(this);
				}
			}
		}
		Plane::~Plane()
		{
			for(unsigned int a = 0; a < m_width; a++)
				if(m_zones[a])
				{
					for(unsigned int b = 0; b < m_height; b++)
						if(m_zones[a][b])
							delete m_zones[a][b];
					delete [] m_zones[a];
				}
			delete [] m_zones;
		}
		Zone *Plane::GetZone(unsigned int x, unsigned int y) const
		{
			return m_zones[x][y];
		}
		void Plane::Render(float minX, float minY, float maxX, float maxY)
		{
			int _minX, _minY, _maxX, _maxY;
			_minX = (int)floor(minX / m_zoneSize);
			_minY = (int)floor(minY / m_zoneSize);
			_maxX = (int)floor(maxX / m_zoneSize);
			_maxY = (int)floor(maxY / m_zoneSize);

			if(_minX < 0)
				_minX = 0;
			else if(_minX >= (int)m_width)
				_minX = m_width - 1;
			if(_minY < 0)
				_minY = 0;
			else if(_minY >= (int)m_height)
				_minY = m_height - 1;
			if(_maxX < 0)
				_maxX = 0;
			else if(_maxX >= (int)m_width)
				_maxX = m_width - 1;
			if(_maxY < 0)
				_maxY = 0;
			else if(_maxY >= (int)m_height)
				_maxY = m_height - 1;

			for(int a = _minX; a <= _maxX; a++)
				for(int b = _minY; b <= _maxY; b++)
					for(vector<ZoneEntity *>::iterator it = m_zones[a][b]->m_children.begin(); it != m_zones[a][b]->m_children.end(); it++)
					{
						ZoneEntity *entity = *it;
						if(entity->Cache(0))
							entity->Render();
					}
			ZoneEntity::ClearCache(0);

//			for(int a = _minX; a <= _maxX; a++)
//				for(int b = _minY; b <= _maxY; b++)
//					m_zones[a][b]->Render();
/*
			for(int a = _minX; a <= _maxX; a++)
				for(int b = _minY; b <= _maxY; b++)
					m_zones[a][b]->Render();
			for(int a = _minX; a <= _maxX; a++)
				for(int b = _minY; b <= _maxY; b++)
					m_zones[a][b]->FinishRender();
*/		}
		void Plane::Place(ZoneEntity *entity)
		{
			Vector2<float> position = entity->GetPosition(), extent = entity->GetExtent();
			int _minX, _minY, _maxX, _maxY;
			_minX = (int)floor(position[0] / m_zoneSize);
			_minY = (int)floor(position[1] / m_zoneSize);
			_maxX = (int)floor((position[0] + extent[0]) / m_zoneSize);
			_maxY = (int)floor((position[1] + extent[1]) / m_zoneSize);

			if(_minX < 0)
				_minX = 0;
			else if(_minX >= (int)m_width)
				_minX = m_width - 1;
			if(_minY < 0)
				_minY = 0;
			else if(_minY >= (int)m_height)
				_minY = m_height - 1;
			if(_maxX < 0)
				_maxX = 0;
			else if(_maxX >= (int)m_width)
				_maxX = m_width - 1;
			if(_maxY < 0)
				_maxY = 0;
			else if(_maxY >= (int)m_height)
				_maxY = m_height - 1;

			for(int a = _minX; a <= _maxX; a++)
				for(int b = _minY; b <= _maxY; b++)
					m_zones[a][b]->Add(entity);
		}
		void Plane::MoveEntity(ce::game2d::ZoneEntity *entity, Vector2<float> movement)
		{
			Vector2<float> position = entity->GetPosition(), extent = entity->GetExtent();

			int aMinX, aMinY, aMaxX, aMaxY, bMinX, bMinY, bMaxX, bMaxY;
			aMinX = (int)floor(position[0] / m_zoneSize);
			aMinY = (int)floor(position[1] / m_zoneSize);
			aMaxX = (int)floor((position[0] + extent[0]) / m_zoneSize);
			aMaxY = (int)floor((position[1] + extent[1]) / m_zoneSize);

			position += movement;
			entity->SetPosition(position);

			bMinX = (int)floor(position[0] / m_zoneSize);
			bMinY = (int)floor(position[1] / m_zoneSize);
			bMaxX = (int)floor((position[0] + extent[0]) / m_zoneSize);
			bMaxY = (int)floor((position[1] + extent[1]) / m_zoneSize);

			if(aMinX < 0)
				aMinX = 0;
			else if(aMinX >= (int)m_width)
				aMinX = m_width - 1;
			if(aMinY < 0)
				aMinY = 0;
			else if(aMinY >= (int)m_height)
				aMinY = m_height - 1;
			if(aMaxX < 0)
				aMaxX = 0;
			else if(aMaxX >= (int)m_width)
				aMaxX = m_width - 1;
			if(aMaxY < 0)
				aMaxY = 0;
			else if(aMaxY >= (int)m_height)
				aMaxY = m_height - 1;

			if(bMinX < 0)
				bMinX = 0;
			else if(bMinX >= (int)m_width)
				bMinX = m_width - 1;
			if(bMinY < 0)
				bMinY = 0;
			else if(bMinY >= (int)m_height)
				bMinY = m_height - 1;
			if(bMaxX < 0)
				bMaxX = 0;
			else if(bMaxX >= (int)m_width)
				bMaxX = m_width - 1;
			if(bMaxY < 0)
				bMaxY = 0;
			else if(bMaxY >= (int)m_height)
				bMaxY = m_height - 1;

			for(int a = aMinX; a <= aMaxX; a++)
				for(int b = aMinY; b <= aMaxY; b++)
					if(a < bMinX || b < bMinY || a > bMaxX || b > bMaxY)
						m_zones[a][b]->Remove(entity);

			for(int a = bMinX; a <= bMaxX; a++)
				for(int b = bMinY; b <= bMaxY; b++)
					if(a < aMinX || b < aMinY || a > aMaxX || b > aMaxY)
						m_zones[a][b]->Add(entity);
		}
		void Plane::ProcessPhysics(float dt)
		{
			vector<ZoneEntity *> entities;
			for(unsigned int a = 0; a < m_width; a++)
				for(unsigned int b = 0; b < m_height; b++)
					for(vector<ZoneEntity *>::iterator it = m_zones[a][b]->m_children.begin(); it != m_zones[a][b]->m_children.end(); it++)
					{
						(*it)->m_startedPhysics = false;
						entities.push_back(*it);
					}
			for(unsigned int a = 0; a < m_width; a++)
				for(unsigned int b = 0; b < m_height; b++)
					m_zones[a][b]->PhysicsPhase1(dt);

			for(vector<ZoneEntity *>::iterator it = entities.begin(); it != entities.end(); it++)
			{
				ZoneEntity *entity = *it;
				if(entity->m_startedPhysics)
					continue;
				Vector2<float> position = entity->GetPosition(), extent = entity->GetExtent();
				int aMinX, aMinY, aMaxX, aMaxY, bMinX, bMinY, bMaxX, bMaxY;
				aMinX = (int)floor(position[0] / m_zoneSize);
				aMinY = (int)floor(position[1] / m_zoneSize);
				aMaxX = (int)floor((position[0] + extent[0]) / m_zoneSize);
				aMaxY = (int)floor((position[1] + extent[1]) / m_zoneSize);

				bMinX = (int)floor(entity->m_moveBoxMin[0] / m_zoneSize);
				bMinY = (int)floor(entity->m_moveBoxMin[1] / m_zoneSize);
				bMaxX = (int)floor(entity->m_moveBoxMax[0] / m_zoneSize);
				bMaxY = (int)floor(entity->m_moveBoxMax[1] / m_zoneSize);

				if(aMinX < 0)
					aMinX = 0;
				else if(aMinX >= (int)m_width)
					aMinX = m_width - 1;
				if(aMinY < 0)
					aMinY = 0;
				else if(aMinY >= (int)m_height)
					aMinY = m_height - 1;
				if(aMaxX < 0)
					aMaxX = 0;
				else if(aMaxX >= (int)m_width)
					aMaxX = m_width - 1;
				if(aMaxY < 0)
					aMaxY = 0;
				else if(aMaxY >= (int)m_height)
					aMaxY = m_height - 1;

				if(bMinX < 0)
					bMinX = 0;
				else if(bMinX >= (int)m_width)
					bMinX = m_width - 1;
				if(bMinY < 0)
					bMinY = 0;
				else if(bMinY >= (int)m_height)
					bMinY = m_height - 1;
				if(bMaxX < 0)
					bMaxX = 0;
				else if(bMaxX >= (int)m_width)
					bMaxX = m_width - 1;
				if(bMaxY < 0)
					bMaxY = 0;
				else if(bMaxY >= (int)m_height)
					bMaxY = m_height - 1;

				for(int x = aMinX; x <= aMaxX; x++)
					for(int y = aMinY; y <= aMaxY; y++)
						if(x < bMinX || y < bMinY || x > bMaxX || y > bMaxY)
							m_zones[x][y]->Remove(entity);

				for(int x = bMinX; x <= bMaxX; x++)
					for(int y = bMinY; y <= bMaxY; y++)
						if(x < aMinX || y < aMinY || x > aMaxX || y > aMaxY)
							m_zones[x][y]->Add(entity);

				entity->m_startedPhysics = true;
			}

			for(unsigned int a = 0; a < m_width; a++)
				for(unsigned int b = 0; b < m_height; b++)
					m_zones[a][b]->PhysicsPhase2(dt);

			for(vector<ZoneEntity *>::iterator it = entities.begin(); it != entities.end(); it++)
			{
				ZoneEntity *entity = *it;
				if(!entity->m_finishedPhysics)
				{
					entity->m_finishedPhysics = true;
					Vector2<float> velocity = entity->GetVelocity();
					int aMinX, aMinY, aMaxX, aMaxY, bMinX, bMinY, bMaxX, bMaxY;

					aMinX = (int)floor(entity->m_moveBoxMin[0] / m_zoneSize);
					aMinY = (int)floor(entity->m_moveBoxMin[1] / m_zoneSize);
					aMaxX = (int)floor(entity->m_moveBoxMax[0] / m_zoneSize);
					aMaxY = (int)floor(entity->m_moveBoxMax[1] / m_zoneSize);

/*					if(!entity->m_canMove[0])
					{
						if(entity->m_movePadding[0] >= 0.01f)
							entity->m_movePadding[0] /= 2.f;
						else
							entity->m_movement[0] = 0.f;
					}
					if(!entity->m_canMove[1])
					{
						if(entity->m_movePadding[1] >= 0.01f)
							entity->m_movePadding[1] /= 2.f;
						else
							entity->m_movement[1] = 1.f;
					}
*/
					if(entity->m_canMove[0] || entity->m_canMove[1])
					{
						if(!entity->m_canMove[0])
							entity->m_movement[0] = 0.f;
						if(!entity->m_canMove[1])
							entity->m_movement[1] = 0.f;

						entity->m_position += entity->m_movement;
//						entity->Move(entity->m_movement);

/*						if(entity->m_canMove[0])
							entity->m_movePadding[0] = 1.f;
						if(entity->m_canMove[1])
							entity->m_movePadding[1] = 1.f;
*/					}

					Vector2<float> position = entity->GetPosition(), extent = entity->GetExtent();
					bMinX = (int)floor(position[0] / m_zoneSize);
					bMinY = (int)floor(position[1] / m_zoneSize);
					bMaxX = (int)floor((position[0] + extent[0]) / m_zoneSize);
					bMaxY = (int)floor((position[1] + extent[1]) / m_zoneSize);
					
					 if(aMinX < 0)
						aMinX = 0;
					else if(aMinX >= (int)m_width)
						aMinX = m_width - 1;
					if(aMinY < 0)
						aMinY = 0;
					else if(aMinY >= (int)m_height)
						aMinY = m_height - 1;
					if(aMaxX < 0)
						aMaxX = 0;
					else if(aMaxX >= (int)m_width)
						aMaxX = m_width - 1;
					if(aMaxY < 0)
						aMaxY = 0;
					else if(aMaxY >= (int)m_height)
						aMaxY = m_height - 1;

					if(bMinX < 0)
						bMinX = 0;
					else if(bMinX >= (int)m_width)
						bMinX = m_width - 1;
					if(bMinY < 0)
						bMinY = 0;
					else if(bMinY >= (int)m_height)
						bMinY = m_height - 1;
					if(bMaxX < 0)
						bMaxX = 0;
					else if(bMaxX >= (int)m_width)
						bMaxX = m_width - 1;
					if(bMaxY < 0)
						bMaxY = 0;
					else if(bMaxY >= (int)m_height)
						bMaxY = m_height - 1;

					for(int x = aMinX; x <= aMaxX; x++)
						for(int y = aMinY; y <= aMaxY; y++)
							if(x < bMinX || y < bMinY || x > bMaxX || y > bMaxY)
								m_zones[x][y]->Remove(entity);

					for(int x = bMinX; x <= bMaxX; x++)
						for(int y = bMinY; y <= bMaxY; y++)
							if(x < aMinX || y < aMinY || x > aMaxX || y > aMaxY)
								m_zones[x][y]->Add(entity);
					
/*					if(!entity->m_canMove[0])
						entity->m_velocity[0] *= -1.f;
					if(!entity->m_canMove[1])
						entity->m_velocity[1] *= -1.f;
*/					entity->m_movement = Vector2<float>(0.f, 0.f);
				}
			}
		}
		void Plane::RemoveDead()
		{
			for(unsigned int a = 0; a < m_width; a++)
				for(unsigned int b = 0; b < m_height; b++)
					m_zones[a][b]->RemoveDead();
		}
		vector<ZoneEntity *> Plane::BoxSearch(float minX, float minY, float maxX, float maxY, unsigned int mask, ZoneEntity *ignore)
		{
			map<ZoneEntity *, bool> foundMap;
			vector<ZoneEntity *> found;

			int MinX = (int)floor(minX / m_zoneSize);
			int MinY = (int)floor(minY / m_zoneSize);
			int MaxX = (int)floor(maxX / m_zoneSize);
			int MaxY = (int)floor(maxY / m_zoneSize);

			if(MinX < 0)
				MinX = 0;
			else if(MinX >= (int)m_width)
				MinX = m_width - 1;
			if(MinY < 0)
				MinY = 0;
			else if(MinY >= (int)m_height)
				MinY = m_height - 1;
			if(MaxX < 0)
				MaxX = 0;
			else if(MaxX >= (int)m_width)
				MaxX = m_width - 1;
			if(MaxY < 0)
				MaxY = 0;
			else if(MaxY >= (int)m_height)
				MaxY = m_height - 1;

			for(int x = MinX; x <= MaxX; x++)
				for(int y = MinY; y <= MaxY; y++)
				{
					vector<ZoneEntity *> localFound = m_zones[x][y]->BoxSearch(minX, minY, maxX, maxY, mask, ignore);
					for(vector<ZoneEntity *>::iterator it = localFound.begin(); it != localFound.end(); it++)
					{
						ZoneEntity *entity = *it;
						if(!foundMap.count(entity))
						{
							found.push_back(entity);
							foundMap[entity] = true;
						}
					}
				}

			return found;
		}
		vector<ZoneEntity *> Plane::SegmentSearch(float startX, float startY, float endX, float endY, unsigned int mask, ZoneEntity *ignore)
		{
			map<ZoneEntity *, bool> foundMap;
			vector<ZoneEntity *> found;

			if(startX > endX)
			{
				swap(startX, endX);
				swap(startY, endY);
			}

			//- TODO: Handle vertical lines differently -
			float slope = (endY - startY) / (endX - startX);
			vector<Zone *> searchZones;

			int MinX = (int)floor(startX / m_zoneSize);
			int MaxX = (int)floor(endX / m_zoneSize);
			
			if(MinX < 0)
				MinX = 0;
			else if(MinX >= (int)m_width)
				MinX = m_width - 1;
			if(MaxX < 0)
				MaxX = 0;
			else if(MaxX >= (int)m_width)
				MaxX = m_width - 1;

			float originY = startY - (startX - MinX * m_zoneSize) * slope;

			for(int a = MinX; a <= MaxX; a++)
			{
				int MinY = (int)floor((a * m_zoneSize * slope + originY) / m_zoneSize);
				int MaxY = (int)floor(((a + 1) * m_zoneSize * slope + originY - 0.001f) / m_zoneSize);

				if(MinY > MaxY)
					swap(MinY, MaxY);

				if(MinY < 0)
					MinY = 0;
				else if(MinY >= (int)m_height)
					MinY = m_height - 1;
				if(MaxY < 0)
					MaxY = 0;
				else if(MaxY >= (int)m_height)
					MaxY = m_height - 1;

				for(int b = MinY; b <= MaxY; b++)
					searchZones.push_back(m_zones[a][b]);
			}

			for(vector<Zone *>::iterator itA = searchZones.begin(); itA != searchZones.end(); itA++)
			{
				vector<ZoneEntity *> localFound = (*itA)->SegmentSearch(startX, startY, endX, endY, mask, ignore);
				for(vector<ZoneEntity *>::iterator itB = localFound.begin(); itB != localFound.end(); itB++)
				{
					ZoneEntity *entity = *itB;
					if(!foundMap.count(entity))
					{
						found.push_back(entity);
						foundMap[entity] = true;
					}
				}
			}

			return found;
		}
	}
}

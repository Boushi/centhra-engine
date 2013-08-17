#ifndef _CE_GAME2D_PHYSICALOBJECT_H_
#define _CE_GAME2D_PHYSICALOBJECT_H_

//- Centhra Engine -
#include <CE/Color.h>
#include <CE/Vector2.h>
#include <CE/Game2D/Entity.h>
#include <CE/Game2D/PhysicsHandler.h>

namespace ce
{
	namespace game2d
	{
		class PhysicalGroup;

		class PhysicalObject : public Entity
		{
			static unsigned int ms_lastID;

			Vector2<float> m_position, m_extent, m_velocity;
			Color m_color; //- TODO: Remove this after finished -
			unsigned int m_id;
			PhysicalGroup *m_parentGroup;
			PhysicsHandler::ObjectHandle *m_objectHandle;

		protected:
			unsigned int m_collisionMask;

			virtual void DoRender();

		public:
			PhysicalObject(Vector2<float> position, Vector2<float> extent);
			~PhysicalObject();

			void Render();
			Vector2<float> GetExtent() const;
			Vector2<float> GetPosition() const;
			Vector2<float> GetVelocity() const;
			void SetExtent(Vector2<float> extent);
			void SetPosition(Vector2<float> position);
			void SetVelocity(Vector2<float> velocity);

			PhysicsHandler::ObjectHandle *GetObjectHandle() const;
			unsigned int GetCollisionMask() const;
			void SetCollisionMask(unsigned int mask);

			virtual bool OnCollision(PhysicalObject *collider);

			static void Cleanup();

			friend class PhysicalGroup;
		};
	}
}

#endif

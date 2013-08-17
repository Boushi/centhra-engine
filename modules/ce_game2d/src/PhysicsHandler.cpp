//- Centhra Engine -
#include <CE/Game2D/PhysicalObject.h>
#include <CE/Game2D/PhysicsHandler.h>

namespace ce
{
	namespace game2d
	{
		PhysicsHandler::PhysicsHandler()
		{
			m_referenceGroup = 0;
		}
		PhysicsHandler::~PhysicsHandler()
		{
			if(m_referenceGroup)
				Cleanup();
		}
		PhysicalGroup *PhysicsHandler::GetReferenceGroup() const
		{
			return m_referenceGroup;
		}
		void PhysicsHandler::Initialize()
		{
		}
		void PhysicsHandler::Render(float minX, float minY, float maxX, float maxY)
		{
		}
		void PhysicsHandler::Process(float dt)
		{
		}
		void PhysicsHandler::Cleanup()
		{
		}

		PhysicsHandler::ObjectHandle::ObjectHandle(PhysicsHandler *handler, PhysicalObject *object)
		{
			m_physicsHandler = handler;
			m_object = object;
			object->m_objectHandle = this;
			OnCreate();
		}
		PhysicsHandler::ObjectHandle::~ObjectHandle()
		{
			OnDestroy();
			if(m_object)
				m_object->m_objectHandle = 0;
		}
		PhysicalObject *PhysicsHandler::ObjectHandle::GetObject() const
		{
			return m_object;
		}
		PhysicsHandler *PhysicsHandler::ObjectHandle::GetHandler() const
		{
			return m_physicsHandler;
		}
		void PhysicsHandler::ObjectHandle::OnCreate()
		{
		}
		void PhysicsHandler::ObjectHandle::OnRelocate(PhysicalGroup *oldGroup, PhysicalGroup *newGroup)
		{
		}
		void PhysicsHandler::ObjectHandle::OnDestroy()
		{
		}
		void PhysicsHandler::ObjectHandle::OnSetPosition()
		{
		}
		void PhysicsHandler::ObjectHandle::OnSetExtent()
		{
		}
		void PhysicsHandler::ObjectHandle::OnSetVelocity()
		{
		}
	}
}

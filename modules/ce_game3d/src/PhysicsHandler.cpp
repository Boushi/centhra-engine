//- Centhra Engine -
#include <CE/Game3D/PhysicalObject.h>
#include <CE/Game3D/PhysicsHandler.h>

using namespace std;

namespace ce
{
	namespace game3d
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
/*		void PhysicsHandler::Render(float minX, float minY, float maxX, float maxY)
		{
		}
*/		void PhysicsHandler::Process(float dt)
		{
		}
		void PhysicsHandler::Cleanup()
		{
		}
/*		vector<PhysicalObject *> PhysicsHandler::BoxSearch(float minX, float minY, float maxX, float maxY, unsigned int mask, PhysicalObject *ignore)
		{
			return vector<PhysicalObject *>();
		}
		vector<PhysicalObject *> PhysicsHandler::SegmentSearch(float startX, float startY, float endX, float endY, unsigned int mask, PhysicalObject *ignore)
		{
			return vector<PhysicalObject *>();
		}
*/		void PhysicsHandler::SetupObject(PhysicalObject *object)
		{
		}
		void PhysicsHandler::CleanupObject(PhysicalObject *object)
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
		PhysicalObject *PhysicsHandler::ObjectHandle::GetReferenceObject() const
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
		void PhysicsHandler::ObjectHandle::OnSetStatic()
		{
		}
		void PhysicsHandler::ObjectHandle::OnSetPosition()
		{
		}
		void PhysicsHandler::ObjectHandle::OnSetSize()
		{
		}
		void PhysicsHandler::ObjectHandle::OnSetVelocity()
		{
		}
		void PhysicsHandler::ObjectHandle::OnSetRotation()
		{
		}
		void PhysicsHandler::ObjectHandle::OnSetCollisionMask()
		{
		}
	}
}

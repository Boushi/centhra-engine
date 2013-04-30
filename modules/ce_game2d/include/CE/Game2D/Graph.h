#ifndef _CE_GAME2D_GRAPH_H_
#define _CE_GAME2D_GRAPH_H_

//- Standard Library -
#include <vector>

//- Centhra Engine -
#include <CE/Vector2.h>
#include <CE/Game2D/Entity.h>

#define CE_GRAPHNODE_CACHESIZE 2

namespace ce
{
	namespace game2d
	{
		class Graph : public Entity
		{
		public:
			class Node : public Entity
			{
				static std::vector<Node *> ms_cacheVectors[CE_GRAPHNODE_CACHESIZE];
				static void ClearCache(unsigned int idx);

				std::vector<Node *> m_neighbors;
				std::vector<float> m_neighborDistances;
				Vector2<float> m_position;
				bool m_cache[CE_GRAPHNODE_CACHESIZE];

				bool Cache(unsigned int idx);

			public:
				Node(Vector2<float> position);

				void AddNeighbor(Node *node);
				void RemoveNeighbor(Node *node);
				bool IsNeighbor(Node *node) const;
				void ClearNeighbors();

				friend class Graph;
			};

			void Add(Node *node);
			void Remove(Node *node);
			bool IsMember(Node *node) const;
			void ClearNodes();
			std::vector<Node *> FindPath(Node *nodeA, Node *nodeB);

		private:
			std::vector<Node *> m_nodes;
		};
	}
}

#endif
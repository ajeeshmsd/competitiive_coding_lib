//=================================union_find.h==================================//
//
// Implementation of Union-Find algorithm.
// Can only be used if nodes are represented by integers
//
//===============================================================================//

#ifndef AJEESH_UNION_FIND
#define AJEESH_UNION_FIND

#include <vector>

template<typename Type = long long>
class UnionFind
{
  private:
    // Total number of nodes
    int m_number_of_nodes;

    // Representativr of my class. -1 implies I am the representative
    std::vector<Type> m_representative_of_equivalent_class;

    // Size of my equivalent class. Only the size at representatives are correct.
    std::vector<Type> m_sizes_of_equivalent_classes;

    // Number of classes
    int m_number_of_equivalent_classes;

  public:
    UnionFind() = delete;
    UnionFind(UnionFind &&) = default;
    UnionFind(const UnionFind &) = default;
    UnionFind &operator=(UnionFind &&) = default;
    UnionFind &operator=(const UnionFind &) = default;
    ~UnionFind() = default;

    UnionFind(Type p_number_of_nodes):
                    m_number_of_nodes(p_number_of_nodes),
                    m_representative_of_equivalent_class(p_number_of_nodes, -1),
                    m_sizes_of_equivalent_classes(p_number_of_nodes, 1),
                    m_number_of_equivalent_classes(p_number_of_nodes)
    {}

    Type get_representative(Type p_node)
    {
        if(m_representative_of_equivalent_class[p_node] == -1) return p_node;

        return m_representative_of_equivalent_class[p_node] = get_representative(p_node);
    }

    bool apply_union(Type p_node1, Type p_node2)
    {
        Type representative1 = get_representative(p_node1);
        Type representative2 = get_representative(p_node2);

        if(representative1 == representative2) return false;

        if(m_sizes_of_equivalent_classes[representative1] <= m_sizes_of_equivalent_classes[representative2])
        {
            m_representative_of_equivalent_class[representative1] = representative2;
            m_sizes_of_equivalent_classes[representative2] += m_sizes_of_equivalent_classes[representative1];
        }
        else // m_sizes_of_equivalent_classes[representative1] > m_sizes_of_equivalent_classes[representative2]
        {
            m_representative_of_equivalent_class[representative2] = representative1;
            m_sizes_of_equivalent_classes[representative1] += m_sizes_of_equivalent_classes[representative2];
        }

        m_number_of_equivalent_classes--;

        return true;
    }

    Type get_number_of_equivalent_classes()
    {
        return m_number_of_equivalent_classes;
    }

    bool is_same_class(Type p_node1, Type p_node2)
    {
        return get_representative(p_node1) == get_representative(p_node2);
    }
};

#endif // !AJEESH_UNION_FIND

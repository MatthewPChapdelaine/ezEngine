#pragma once

#include <Foundation/Containers/Deque.h>

/// An associative container. Similar to STL::map
/*  A map allows to store key/value pairs. This in turn allows to search for values by looking them
up with a certain key. Key/Value pairs can also be erased again.
All insertion/erasure/lookup functions take O(log n) time. The map is implemented using a balanced tree
(a red-black tree), which means the order of insertions/erasures is not important, since it can never
create a degenerated tree, and performance will always stay the same.\n
\n
KeyType is the key type. For example a string.\n
ValueType is the value type. For example int.\n
Comparer is a helper class that implements a strictly weak-ordering comparison for Key types.
*/
template <typename KeyType, typename ValueType, typename Comparer>
class ezMapBase
{
private:
  struct Node;

  /// Only used by the sentinel node.
  struct NilNode
  {
    NilNode();

    Node* m_pParent;
    Node* m_pLink[2];
    ezUInt8 m_uiLevel;
  };

  /// A node storing the key/value pair.
  struct Node : public NilNode
  {
    KeyType m_Key;
    ValueType m_Value;
  };

public:

  /// Base class for all iterators.
  struct ConstIterator
  {
    EZ_DECLARE_POD_TYPE();

    /// Constructs an invalid iterator.
    EZ_FORCE_INLINE ConstIterator()                         : m_pElement(NULL) { }

    /// Checks whether this iterator points to a valid element.
    EZ_FORCE_INLINE bool IsValid() const { return (m_pElement != NULL); }

    /// Checks whether the two iterators point to the same element.
    EZ_FORCE_INLINE bool operator==(const typename ezMapBase<KeyType, ValueType, Comparer>::ConstIterator& it2) const { return (m_pElement == it2.m_pElement); }

    /// Checks whether the two iterators point to the same element.
    EZ_FORCE_INLINE bool operator!=(const typename ezMapBase<KeyType, ValueType, Comparer>::ConstIterator& it2) const { return (m_pElement != it2.m_pElement); }

    /// Returns the 'key' of the element that this iterator points to.
    EZ_FORCE_INLINE const KeyType&   Key ()  const { EZ_ASSERT(IsValid(), "Cannot access the 'key' of an invalid iterator."); return m_pElement->m_Key;   }

    /// Returns the 'value' of the element that this iterator points to.
    EZ_FORCE_INLINE const ValueType& Value() const { EZ_ASSERT(IsValid(), "Cannot access the 'value' of an invalid iterator."); return m_pElement->m_Value; }

    /// Advances the iterator to the next element in the map. The iterator will not be valid anymore, if the end is reached.
    void Next();

    /// Advances the iterator to the previous element in the map. The iterator will not be valid anymore, if the end is reached.
    void Prev();

    /// Shorthand for 'Next'
    EZ_FORCE_INLINE void operator++() { Next();  }

    /// Shorthand for 'Prev'
    EZ_FORCE_INLINE void operator--() { Prev(); }

  protected:
    friend class ezMapBase<KeyType, ValueType, Comparer>;

    EZ_FORCE_INLINE explicit ConstIterator(Node* pInit)              : m_pElement(pInit) { }

    Node* m_pElement;
  };

  /// Forward Iterator to iterate over all elements in sorted order.
  struct Iterator : public ConstIterator
  {
    EZ_DECLARE_POD_TYPE();

    /// Constructs an invalid iterator.
    EZ_FORCE_INLINE Iterator()                   : ConstIterator()      { }

    /// Returns the 'value' of the element that this iterator points to.
    EZ_FORCE_INLINE ValueType& Value() { EZ_ASSERT(IsValid(), "Cannot access the 'value' of an invalid iterator."); return m_pElement->m_Value; }

  private:
    friend class ezMapBase<KeyType, ValueType, Comparer>;

    EZ_FORCE_INLINE explicit Iterator(Node* pInit)        : ConstIterator(pInit) { }
  };

protected:

  /// Initializes the map to be empty.
  ezMapBase(ezIAllocator* pAllocator); // [tested]

  /// Copies all key/value pairs from the given map into this one.
  ezMapBase(const ezMapBase<KeyType, ValueType, Comparer>& cc, ezIAllocator* pAllocator); // [tested]

  /// Destroys all elements from the map.
  ~ezMapBase(); // [tested]

  /// Copies all key/value pairs from the given map into this one.
  void operator= (const ezMapBase<KeyType, ValueType, Comparer>& rhs);

public:
  /// Returns whether there are no elements in the map. O(1) operation.
  bool IsEmpty() const; // [tested]

  /// Returns the number of elements currently stored in the map. O(1) operation.
  ezUInt32 GetCount() const; // [tested]

  /// Destroys all elements in the map and resets its size to zero.
  void Clear(); // [tested]

  /// Returns an Iterator to the very first element.
  Iterator GetIterator(); // [tested]

  /// Returns a constant Iterator to the very first element.
  ConstIterator GetIterator() const; // [tested]

  /// Returns an Iterator to the very last element. For reverse traversal.
  Iterator GetLastIterator(); // [tested]

  /// Returns a constant Iterator to the very last element. For reverse traversal.
  ConstIterator GetLastIterator() const; // [tested]

  /// Inserts the key/value pair into the tree and returns an Iterator to it. O(log n) operation.
  Iterator Insert(const KeyType& key, const ValueType& value); // [tested]

  /// Erases the key/value pair with the given key, if it exists. O(log n) operation.
  void Erase(const KeyType& key); // [tested]

  /// Erases the key/value pair at the given Iterator. O(1) operation(nearly).
  Iterator Erase(const Iterator& pos); // [tested]

  /// Allows read/write access to the value stored under the given key. If there is no such key, a new element is default-constructed.
  ValueType& operator[](const KeyType& key); // [tested]

  /// Searches for key, returns an Iterator to it or an invalid iterator, if no such key is found. O(log n) operation.
  Iterator Find(const KeyType& key); // [tested]

  /// Returns an Iterator to the element with a key equal or larger than the given key. Returns an invalid iterator, if there is no such element.
  Iterator LowerBound(const KeyType& key); // [tested]

  /// Returns an Iterator to the element with a key that is LARGER than the given key. Returns an invalid iterator, if there is no such element.
  Iterator UpperBound(const KeyType& key); // [tested]

  /// Searches for key, returns an Iterator to it or an invalid iterator, if no such key is found. O(log n) operation.
  ConstIterator Find(const KeyType& key) const; // [tested]

  /// Returns an Iterator to the element with a key equal or larger than the given key. Returns an invalid iterator, if there is no such element.
  ConstIterator LowerBound(const KeyType& key) const; // [tested]

  /// Returns an Iterator to the element with a key that is LARGER than the given key. Returns an invalid iterator, if there is no such element.
  ConstIterator UpperBound(const KeyType& key) const; // [tested]

  /// Returns the allocator that is used by this instance.
  ezIAllocator* GetAllocator() const { return m_Elements.GetAllocator(); }

private:
  Node* Internal_Find(const KeyType& key) const;
  Node* Internal_LowerBound(const KeyType& key) const;
  Node* Internal_UpperBound(const KeyType& key) const;

private:
  void Constructor();

  /// Creates one new node and initializes it.
  Node* AcquireNode(const KeyType& key, const ValueType& value, int m_uiLevel, Node* pParent);

  /// Destroys the given node.
  void ReleaseNode(Node* pNode);

  // Red-Black Tree stuff(Anderson Tree to be exact).
  // Code taken from here: http://eternallyconfuzzled.com/tuts/datastructures/jsw_tut_andersson.aspx
  Node* SkewNode(Node* root);
  Node* SplitNode(Node* root);
  void Insert(const KeyType& key, const ValueType& value, Node*& pInsertedNode);
  Node* Erase(Node* root, const KeyType& key);

  /// Returns the left-most node of the tree(smallest key).
  Node* GetLeftMost() const;

  /// Returns the right-most node of the tree(largest key).
  Node* GetRightMost() const;

  /// Root node of the tree.
  Node* m_pRoot;

  /// Sentinel node.
  NilNode m_NilNode;

  /// Number of active nodes in the tree.
  ezUInt32 m_uiCount;

  /// Data store. Keeps all the nodes.
  ezDeque<Node, ezNullAllocatorWrapper, false> m_Elements;

  /// Stack of recently discarded nodes to quickly acquire new nodes.
  Node* m_pFreeElementStack;
};


template <typename KeyType, typename ValueType, typename Comparer = ezCompareHelper<KeyType>, typename AllocatorWrapper = ezDefaultAllocatorWrapper>
class ezMap : public ezMapBase<KeyType, ValueType, Comparer>
{
public:
  ezMap();
  ezMap(ezIAllocator* pAllocator);

  ezMap(const ezMap<KeyType, ValueType, Comparer, AllocatorWrapper>& other);
  ezMap(const ezMapBase<KeyType, ValueType, Comparer>& other);

  void operator=(const ezMap<KeyType, ValueType, Comparer, AllocatorWrapper>& rhs);
  void operator=(const ezMapBase<KeyType, ValueType, Comparer>& rhs);
};

#include <Foundation/Containers/Implementation/Map_inl.h>


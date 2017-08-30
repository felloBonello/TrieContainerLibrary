#include <string>
#include <iostream>
#include <map>


#if !defined(GUARD_trie_hpp)
#define GUARD_trie_hpp


/**	@file trie.hpp
	@author Justin Bonello
	@date 2016-08-08
	@version 1.0.0
	@note Developed for C++11/vc14
	@breif trie<T> template implementation.
*/




template<typename T>
class trie
{

public:

	class node;
	class iterator;
	class const_iterator;
	class reverse_iterator;
	class const_reverse_iterator;

	using size_type = size_t;
	using key_type = std::string;
	using value_type = std::pair<const std::string, T>;
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = ptrdiff_t;
	using pointer = node*;
	using reference = node&;
	using const_iterator = const_iterator;

	class node
	{
	public:
		static const size_type ARRAY_SIZE = 256;
		char c_;
		size_type node_count_ = 0;
		size_type occurences = 0;
		pointer children[ARRAY_SIZE] = {};
		pointer parent;
		bool end_word = false;
		bool begin = false;

		std::string first;
		T second;

		node() { }
		node(char c) : c_(c), occurences(1) {}
		~node() {}

		char c() { return c_; }
		size_type node_count() { return node_count_; }

		pointer newNode(std::string s)
		{
			if (s.length() != 0)
			{
				int i = s.at(0);
				children[i] = new node(s.at(0));
				children[i]->parent = this;
				children[i]->first = first + s.at(0);
				++node_count_;
				if (s.length() == 1)
					children[i]->end_word = true;

				return  children[i]->newNode(s.substr(1, s.length() - 1));
			}
			return this;
		}

		pointer add(std::string s)
		{
			if (s.length() == 0)
				return this;

			int i = s.at(0);
			if (children[i])
			{
				if (s.length() == 1)
					children[i]->end_word = true;
				++children[i]->occurences;
				return children[i]->add(s.substr(1, s.length() - 1));
			}

			return newNode(s);
		}

		size_type count(std::string word)
		{
			if (word.length() == 0)
				return occurences;

			int i = word.at(0);
			if (children[i])
				return children[i]->count(word.substr(1, word.length() - 1));

			return 0;
		}

		pointer getNextTail()
		{
			if (end_word && !begin)
				return this;

			begin = false;
			for (int i = 0; i < ARRAY_SIZE; ++i)
				if (children[i])
					return children[i]->getNextTail();

			return this;
		}

		pointer getNextBranch()
		{
			if (occurences == 0)
				return this;

			begin = false;

			if (parent->node_count_ > 1)
				for (int i = c_ + 1; i < ARRAY_SIZE; ++i)
					if (parent->children[i])
						return parent->children[i]->getNextTail();

			return parent->getNextBranch();
		}

		pointer getPrevTail()
		{
			begin = false;
			for (int i = ARRAY_SIZE - 1; i >= 0; --i)
				if (children[i])
					return children[i]->getPrevTail();

			return this;
		}

		pointer getPrevBranch()
		{
			if (occurences == 0)
				return this;
			if (end_word && !begin)
				return this;
			begin = false;

			if (parent->node_count_ > 1)
				for (int i = c_ - 1; i >= 0; --i)
					if (parent->children[i])
						return parent->children[i]->getPrevTail();

			return parent->getPrevBranch();
		}

		pointer addNullChar()
		{
			if (children[0])
			{
				++children[0]->occurences;
				return children[0];
			}

			children[0] = new node('\0');
			children[0]->parent = this;
			++node_count_;
			return children[0];
		}

		pointer getBegin()
		{
			if (end_word)
				return this;
			for (int i = 0; i < ARRAY_SIZE; ++i)
			{
				if (children[i])
					return children[i]->getBegin();
			}
			return this;
		}

		pointer find(std::string s)
		{
			if (s.length() == 0 && end_word)
				return this;
			if (s.length() == 0)
				return NULL;

			int i = s.at(0);
			if (children[i])
				return children[i]->find(s.substr(1, s.length() - 1));

			return NULL;
		}

	};



	size_type size_ = 0;
	pointer end_ = new node();
	pointer begin_ = end_;

	trie() {}
	trie(std::initializer_list<value_type> val_list) { insert(val_list); }
	trie& operator=(std::initializer_list<value_type> val_list) { clear(); insert(val_list); return *this; }
	template<typename opT>
	trie(opT begin, opT end) { insert(begin, end); }
	template<typename opT>
	trie(typename trie<opT> &obj){ clear(); insert_ref(obj.begin_, obj.end_); }
	template<typename opT>
	trie(typename trie<opT>&& obj) 
	{ 
		clear(); 
		insert_ref(obj.begin_, obj.end_);
		obj.deleteNodes(obj.end_);
		obj.end_ = new node();
		obj.begin_ = obj.end_;
		obj.size_ = 0;
	}
	trie& operator = (trie& rhs) { clear(); insert_ref(rhs.begin_, rhs.end_); return *this;  }
	trie& operator = (trie&& rhs) 
	{ 
		clear();
		insert_ref(rhs.begin_, rhs.end_);
		rhs.deleteNodes(rhs.end_);
		rhs.end_ = new node();
		rhs.begin_ = rhs.end_;
		rhs.size_ = 0;
		return *this;
	}
	~trie() { deleteNodes(end_); }

	void deleteNodes(pointer current)
	{
		for (unsigned i = 0; i < node::ARRAY_SIZE; ++i)
			if (current->children[i])
				deleteNodes(current->children[i]);

		delete current;
	}

	bool empty() { return !size_; }
	size_type count(std::string word) { return end_->count(word); }
	size_type size() { return size_; }
	node front() { return *begin_; }
	node back() { return *(--iterator(end_)).ptr_; }
	iterator begin() { return iterator(begin_); }
	iterator end() { return iterator(end_); }
	const_iterator begin() const { return const_iterator(begin_); }
	const_iterator end() const { return const_iterator(end_); }
	reverse_iterator rbegin() { return ++reverse_iterator(end_); }
	reverse_iterator rend() { return ++reverse_iterator(begin_); }
	const_reverse_iterator rbegin() const { return ++const_reverse_iterator(end_); }
	const_reverse_iterator rend() const { return ++const_reverse_iterator(begin_); }
	const_iterator cbegin() const { return const_iterator(begin_); }
	const_iterator cend() const { return const_iterator(end_); }
	const_reverse_iterator crbegin() const { return ++const_reverse_iterator(end_); }
	const_reverse_iterator crend() const { return ++const_reverse_iterator(begin_); }
	size_type max_size() { return std::numeric_limits<size_type>::max(); }
	void clear() { deleteNodes(end_); size_ = 0; begin_ = end_ = new node(); }



	void erase(iterator loc)
	{
		if (loc->node_count_ > 0)
			loc->end_word = false;
		while (loc.ptr_ != end_)
		{
			pointer temp = loc->parent;
			if (loc->occurences == 1)
			{				
				--loc->parent->node_count_;
				loc->parent->children[loc->c_] = NULL;
				deleteNodes(loc.ptr_);
			}
			else
				--loc->occurences;
			loc = temp;
		}
		--size_;
		begin_ = end_->getBegin();
	}

	iterator erase(iterator begin, iterator end)
	{
		while (begin != end)
		{
			iterator temp = begin;
			++temp;
			erase(begin);
			begin = temp;
		}		
		return end;
	}

	size_type erase(key_type key)
	{
		iterator current = begin_;
		int count = 0;

		while (current != end_)
		{
			iterator temp = current;
			++temp;
			if (current->first == key)
			{
				erase(current);
				++count;
			}
			current = temp;
		}
		return count;
	}

	std::pair<pointer, bool> insert(value_type val)
	{
		pointer temp = find(val.first).ptr_;
		if (temp == end_)
		{
			++size_;
			if (val.first == "")
				temp = end_->addNullChar();
			else
				temp = end_->add(val.first);

			begin_ = end_->getBegin();
			temp->second = std::move(val.second);
			return std::make_pair(temp, true);
		}
		else
			return std::make_pair(temp, false);			
	}
	
	void insert(std::initializer_list<value_type> val_list)
	{
		for each(auto val in val_list)
			insert(val);	
	}

	template<typename pT>
	void insert(pT begin_ptr, pT end_ptr )
	{
		while (begin_ptr != end_ptr)
		{		
			insert(std::make_pair(begin_ptr._Ptr->_Myval.first, begin_ptr._Ptr->_Myval.second));
			++begin_ptr;
		}
	}

	void insert(iterator begin_ptr, iterator end_ptr)
	{
		while (begin_ptr != end_ptr)
		{
			insert(std::make_pair(begin_ptr->first, begin_ptr->second));
			++begin_ptr;
		}
	}

	template<typename pT>
	void insert_ref(pT begin_ptr, pT end_ptr)
	{
		iterator current = iterator(begin_ptr);
		iterator end = iterator(end_ptr);
		while (current != end)
		{
			insert(std::make_pair((*current).first, (*current).second));
			++current;
		}
	}

	iterator find(std::string val)
	{
		if (val == "")
			return (end_->children[0]) ? iterator(end_->children[0]) : iterator(end_);
		return (end_->find(val)) ? iterator(end_->find(val)) : iterator(end_);
	}

	void swap(trie& val){ std::swap(*this, val); }

	template <typename opT>
	T& operator [] (opT& val) {
		++size_;
		pointer temp;
		if (val == "")
			temp = end_->addNullChar();
		else
			temp = end_->add(val);

		begin_ = end_->getBegin();
		return temp->second;
	}




	class iterator : public std::iterator<std::bidirectional_iterator_tag, T>
	{
	public:
		using value_type = std::pair<const std::string, T>;
		using iterator_category = std::bidirectional_iterator_tag;
		using difference_type = ptrdiff_t;
		using pointer = node*;
		using reference = node&;

		pointer ptr_;

		iterator(pointer ptr = null) : ptr_(ptr) { }
		~iterator() {}

		iterator& operator ++ ()
		{
			ptr_->begin = true;
			if (ptr_->node_count_ > 0)
				ptr_ = ptr_->getNextTail();
			else
				ptr_ = ptr_->getNextBranch();

			return *this;
		}
		iterator operator ++ (int)
		{
			auto temp = *this;
			ptr_->begin = true;
			if (ptr_->node_count_ > 0)
				ptr_ = ptr_->getNextTail();
			else
				ptr_ = ptr_->getNextBranch();

			return temp;
		}
		iterator& operator -- ()
		{
			ptr_->begin = true;
			if (ptr_->occurences == 0)
				ptr_ = ptr_->getPrevTail();
			else
				ptr_ = ptr_->getPrevBranch();
			return *this;
		}
		iterator operator -- (int)
		{
			auto temp = *this;
			ptr_->begin = true;
			if (ptr_->occurences == 0)
				ptr_ = ptr_->getPrevTail();
			else
				ptr_ = ptr_->getPrevBranch();
			return temp;
		}
		reference operator * () const { return *ptr_; }
		pointer operator -> () { return ptr_; }
		bool operator == (const iterator& rhs) { return rhs.ptr_ == ptr_; }
		bool operator != (const iterator& rhs) { return rhs.ptr_ != ptr_; }

	};


	class reverse_iterator : public std::iterator<std::bidirectional_iterator_tag, T>
	{
	public:
		using value_type = std::pair<const std::string, T>;
		using iterator_category = std::bidirectional_iterator_tag;
		using difference_type = ptrdiff_t;
		using pointer = node*;
		using reference = node&;

		pointer ptr_;

		reverse_iterator(pointer ptr = null) : ptr_(ptr) { }
		~reverse_iterator() {}

		reverse_iterator& operator ++ ()
		{
			ptr_ = (--trie::iterator(ptr_)).ptr_;
			return *this;
		}
		reverse_iterator operator ++ (int)
		{
			auto temp = *this;
			ptr_ = (--trie::iterator(ptr_)).ptr_;
			return temp;
		}
		reverse_iterator& operator -- ()
		{
			ptr_ = (++trie::iterator(ptr_)).ptr_;
			return *this;
		}
		reverse_iterator operator -- (int)
		{
			auto temp = *this;
			ptr_ = (++trie::iterator(ptr_)).ptr_;
			return temp;
		}
		reference operator * () const { return *ptr_; }
		pointer operator -> () { return ptr_; }
		bool operator == (const reverse_iterator& rhs) { return rhs.ptr_ == ptr_; }
		bool operator != (const reverse_iterator& rhs) { return rhs.ptr_ != ptr_; }
	};


	class const_iterator : public std::iterator<std::bidirectional_iterator_tag, const T>
	{
	public:
		using value_type = const std::pair<std::string, T>;
		using iterator_category = std::bidirectional_iterator_tag;
		using difference_type = ptrdiff_t;
		using pointer = node*;
		using reference = node&;

		pointer ptr_;

		const_iterator(pointer ptr = null) : ptr_(ptr) { }
		~const_iterator() {}

		const_iterator& operator ++ ()
		{
			ptr_ = (++trie::iterator(ptr_)).ptr_;
			return *this;
		}
		const_iterator operator ++ (int)
		{
			auto temp = *this;
			ptr_ = (++trie::iterator(ptr_)).ptr_;
			return temp;
		}
		const const_iterator& operator -- ()
		{
			ptr_ = (--trie::iterator(ptr_)).ptr_;
			return *this;
		}
		const const_iterator operator -- (int)
		{
			auto temp = *this;
			ptr_ = (--trie::iterator(ptr_)).ptr_;
			return temp;
		}
		const reference operator * () const { return *ptr_; }
		pointer operator -> () { return ptr_; }
		bool operator == (const const_iterator& rhs) { return rhs.ptr_ == ptr_; }
		bool operator != (const const_iterator& rhs) { return rhs.ptr_ != ptr_; }

	};

	class const_reverse_iterator : public std::iterator<std::bidirectional_iterator_tag, const T>
	{
	public:
		using value_type = const std::pair<std::string, T>;
		using iterator_category = std::bidirectional_iterator_tag;
		using difference_type = ptrdiff_t;
		using pointer = node*;
		using reference = node&;

		pointer ptr_;

		const_reverse_iterator(pointer ptr = null) : ptr_(ptr) { }
		~const_reverse_iterator() {}

		const_reverse_iterator& operator ++ ()
		{
			ptr_ = (--trie::iterator(ptr_)).ptr_;
			return *this;
		}
		const_reverse_iterator operator ++ (int)
		{
			auto temp = *this;
			ptr_ = (--trie::iterator(ptr_)).ptr_;
			return temp;
		}
		const_reverse_iterator& operator -- ()
		{
			ptr_ = (++trie::iterator(ptr_)).ptr_;
			return *this;
		}
		const_reverse_iterator operator -- (int)
		{
			auto temp = *this;
			ptr_ = (++trie::iterator(ptr_)).ptr_;
			return temp;
		}
		const reference operator * () const { return *ptr_; }
		pointer operator -> () { return ptr_; }
		bool operator == (const const_reverse_iterator& rhs) { return rhs.ptr_ == ptr_; }
		bool operator != (const const_reverse_iterator& rhs) { return rhs.ptr_ != ptr_; }
	};

	friend bool operator == (trie& lhs, trie& rhs)
	{ 
		if (lhs.size_ != rhs.size_)
			return false;

		iterator _First1 = iterator(lhs.begin_);
		iterator _First2 = iterator(rhs.begin_);
		iterator _Last1 = iterator(lhs.end_);
		while (_First1 != _Last1)
		{
			if (_First1.ptr_->first != _First2.ptr_->first)
				return false;
			if (_First1.ptr_->second != _First2.ptr_->second)
				return false;

			++_First2;
			++_First1;
		}
		return true;
	}

};



namespace std 
{
	template<typename T>
	void swap(trie<T>& a, trie<T>& b)
	{
		using std::swap;
		swap(a.end_, b.end_);
		swap(a.begin_, b.begin_);
		swap(a.size_, b.size_);
	}

	template<typename opT> inline
	bool equal(  typename trie<opT>::iterator _First1,
				 typename trie<opT>::iterator _Last1,
				 typename std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<const std::string, opT>>>> _First2)
	{	
		while (_First1 != _Last1)
		{
			if (_First1.ptr_->first != _First2._Ptr->_Myval.first)
				return false;
			if (_First1.ptr_->second != _First2._Ptr->_Myval.second)
				return false;

			++_First2;
			++_First1;
		}
		return true;
	}

	template<typename opT> inline
	bool equal(	typename trie<opT>::const_iterator _First1,
				typename trie<opT>::const_iterator _Last1,
				typename std::_Tree_const_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<const std::string, opT>>>> _First2)
	{
		while (_First1 != _Last1)
		{
			if (_First1.ptr_->first != _First2._Ptr->_Myval.first)
				return false;
			if (_First1.ptr_->second != _First2._Ptr->_Myval.second)
				return false;

			++_First2;
			++_First1;
		}
		return true;
	}

	template<typename opT> inline
	bool equal(	opT _First1,
				opT _Last1,
				opT _First2)
	{
		while (_First1 != _Last1)
		{
			if (_First1.ptr_->first != _First2.ptr_->first)
				return false;
			if (_First1.ptr_->second != _First2.ptr_->second)
				return false;

			++_First2;
			++_First1;
		}
		return true;
	}

	template<typename opT> inline
	typename trie<opT>::iterator find(	typename trie<opT>::iterator begin,
										typename trie<opT>::iterator end,
										typename std::pair<const std::string, opT> val)
	{
		while (begin != end)
		{
			if (begin->first == val.first && begin->second == val.second)
				return begin;
			++begin;
		}
		return NULL;
	}
}
	
#endif // GUARD_trie_hpp
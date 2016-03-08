#ifndef __Navigation_ilist_h__
#define __Navigation_ilist_h__

#include <stddef.h>

namespace Navigation {
	template <class T> class IList {
	public:
		virtual void Destroy() = 0;

		virtual bool Insert(T item, unsigned int index) = 0;
		virtual void Append(T item) = 0;
		virtual void Prepend(T item) = 0;
		virtual T At(unsigned int index) = 0;
		virtual size_t Size() = 0;
		virtual unsigned int Find(T item) = 0;
		virtual void Erase(unsigned int index) = 0;
	};
}

#endif

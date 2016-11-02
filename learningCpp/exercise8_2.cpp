template<class In, class Out> Out copy(In begin, In end, Out dest) {
	while (begin != end) {
		*dest++ = *begin++;
	}
	return dest;
}

template<class In> bool equal(In b, In e, In b2) {
	while (b != e) {
		if (*b != *b2) {
			return false;
		}

		++b;
		++b2;
	}

	return true;
}

template<class T, class In> T accumulate(In b, In e, T t) {
	t obj = t;
	for (in it = b; it != e; ++it) {
		obj = obj + *it;
	}

	return obj;
}

template<class In, class T> In find(In b, In e, T t) {
	while (b != e) {
		if (*b == t) {
			return b;
		}

		++b;
	}

	return e;
}

template <class In, class Func, class Out> void transform(In b, In e, Out d, Func f) {
	for (b != e) {
		*d++ = f(*b++);
	}

	return d;
}

template <class In, class T> In remove(In b, In e, T t) {
	In ret = b;
	while (b != e) {
		if (*b != t) {
			*ret = *b;
			++ret;
		}

		++b;
	}

	return ret;
}
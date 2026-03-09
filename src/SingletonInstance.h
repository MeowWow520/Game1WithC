#pragma once

#ifndef SINGLETONINSTANCE_H
#define SINGLETONINSTANCE_H



template <typename T>
class SITemplate {

public:
	static T* Instance() {
		if (!_Sitemplate) _Sitemplate = new	T();
		return _Sitemplate;
	}

protected:
	SITemplate() = default;
	~SITemplate() = default;
	SITemplate(const SITemplate&) = delete;
	SITemplate& operator=(const SITemplate&) = delete;
	 
private:
	static T* _Sitemplate;
};
template <typename T>
T* SITemplate<T>::_Sitemplate = nullptr;
#endif // !SINGLETONINSTANCE_H
 /****************************************************************************************************

  Module :	Singleton.h
  Desc	 :	Singleton Class

  Date	 :	2003. 8. 22.
  Maker	 :	Byen Sock Hyen

****************************************************************************************************/

#pragma once

#include <ASSERT.H>
#include <WINDOWS.H>

template < class T >
class CSingleton
{
private:
//----------------------------------------------------------------------------------------------------
//	Name :	static CSingleton*	m_pSingletonObject;
//	Desc :	Singleton Object
//----------------------------------------------------------------------------------------------------
	static T*	m_pSingletonObject;

public:
//----------------------------------------------------------------------------------------------------
//	Name :	static void SetInstance( CSingleton* i_pSingletonObject )
//	Desc :	Singleton Pattern ( Can make object Only one in this program )
//			Set Object Instance
//----------------------------------------------------------------------------------------------------
	static void SetInstance( T* i_pSingletonObject )
	{
		m_pSingletonObject = i_pSingletonObject;
	}

//----------------------------------------------------------------------------------------------------
//	Name :	static void NewInstance()
//	Desc :	Create Instance
//----------------------------------------------------------------------------------------------------
	static void CreateInstance()
	{
		assert( !m_pSingletonObject );

		m_pSingletonObject = new T;
	}

//----------------------------------------------------------------------------------------------------
//	Name :	static void SetInstance( CSingleton* i_pSingletonObject )
//	Desc :	Singleton Pattern ( Can make object Only one in this program )
//			Get Object Instance
//----------------------------------------------------------------------------------------------------
	static T* GetInstance()
	{
		if( !m_pSingletonObject ) CreateInstance();
		
		return m_pSingletonObject;
	}

//----------------------------------------------------------------------------------------------------
//	Name :	static void DeleteInstance()
//	Desc :	Delete Instance
//----------------------------------------------------------------------------------------------------
	static void DeleteInstance()
	{
		assert( m_pSingletonObject );

		delete m_pSingletonObject;
		
		m_pSingletonObject = NULL;
	}

protected:
//----------------------------------------------------------------------------------------------------
//	Name :	CSingleton();
//	Desc :	Protect Call Creation by User
//----------------------------------------------------------------------------------------------------
	CSingleton() {}
};

template < class T >
T* CSingleton<T>::m_pSingletonObject = NULL;

/*
 *	[ Warning ]
 *	
 *	상속할때는 다음과 같이 템플릿 클래스형 선언을 해 주어야 한다.
 *	
 *	Ex > class CChild : public CSingleton<CChild>
 *	
 *	
 *	상속받은 클래스의 마지막 부분에 다음과 같은 인라인 함수를 만들어 쓰면 편하다.
 *
 *	Ex >
 *	
 *	inline CChild* GetChild()
 *	{ return CChild::GetInstance(); }
 *	
 */

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
 *	����Ҷ��� ������ ���� ���ø� Ŭ������ ������ �� �־�� �Ѵ�.
 *	
 *	Ex > class CChild : public CSingleton<CChild>
 *	
 *	
 *	��ӹ��� Ŭ������ ������ �κп� ������ ���� �ζ��� �Լ��� ����� ���� ���ϴ�.
 *
 *	Ex >
 *	
 *	inline CChild* GetChild()
 *	{ return CChild::GetInstance(); }
 *	
 */

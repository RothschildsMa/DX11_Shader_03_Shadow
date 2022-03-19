#pragma once

#include <list>
#include <vector>
#include <typeinfo>


#include "gameobject.h"


class Scene
{
protected:
	std::list<GameObject*> m_GameObject[3];	//STL�̃��X�g�\��

public:
	Scene() {}
	virtual ~Scene() {}

	virtual void Init() = 0;

	template<typename T> //�e���v���[�g�֐�
	T* AddGameObject(int Layer)
	{
		T* gameObject = new T();
		gameObject->Init();
		m_GameObject[Layer].push_back(gameObject);
		
		return gameObject;
	}

	template <typename T>
	T* GetGameObject(int Layer)
	{
		for (GameObject* object : m_GameObject[Layer])
		{
			if (typeid(*object) == typeid(T))//�^�𒲂ׂ�(RTTI���I�^���)
			{
				return (T*)object;
			}
		}
		
		return nullptr;
		
	}
	
	template <typename T>
	std::vector<T*> GetGameObjects(int Layer)
	{
		std::vector<T*> objects;//STL�̔z��
	
		for (GameObject* object : m_GameObject[Layer])
		{
			if (typeid(*object) == typeid(T))
			{
				objects.push_back((T*)object);
			}
		}
		
		return objects;
	}


	virtual void Uninit()
	{
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Uninit();
				delete object;
			}
			m_GameObject[i].clear();//���X�g�̃N���A
		}

		
	}

	virtual void Update()
	{
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Update();
			}

			m_GameObject[i].remove_if([](GameObject* object) {return object->Destroy(); });
		}
	
	}

	virtual void Draw()
	{
		for (int i = 0; i < 3; i++)
		{
			if (i == 2)
			{
				//LightManager::GetInstance().Clear();
				
			}

			for (GameObject* object : m_GameObject[i])
			{
				object->Draw();

			}
		}

	}

	virtual void ShadowObjDraw()
	{
		for (GameObject* object : m_GameObject[1])
		{
			object->Draw();
		}

	}



};

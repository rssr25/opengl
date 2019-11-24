#pragma once

#include <functional>
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {

	class Test
	{
	public:
		Test() {}
		virtual ~Test(){}

		virtual void OnUpdate(float deltaTime){ }
		virtual void OnRender(){}
		virtual void OnImGuiRender() {}

	};

	class TestMenu : public Test
	{

	public:
		TestMenu(Test*& currentTestPointer);
		void OnImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string& testName)
		{
			std::cout << "Registering test "<< testName << std::endl;
			m_Tests.push_back(std::make_pair(testName, []() {return new T(); }));
		}

	private:

		Test*& m_currentTest;
		//a vector of pair of "testName", Test class pointer
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
		
	};

}

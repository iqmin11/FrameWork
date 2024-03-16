#pragma once
class TestClass
{
public:
	// construtor destructor
	TestClass();
	~TestClass();

	// delete Function
	TestClass(const TestClass& _Other) = delete;
	TestClass(TestClass&& _Other) noexcept = delete;
	TestClass& operator=(const TestClass& _Other) = delete;
	TestClass& operator=(TestClass&& _Other) noexcept = delete;

protected:


private:

};


#include <SFML/Graphics.hpp>

sf::View view;										//������ ����-������

sf::View GetPosit(const float x, const float y)		//������� ��� ���������� ��������� ������
{
	float tempX = x; float tempY = y;				//��������� �������� ������ � ��������� ��, ���� ������ ����
	if (x < 640) tempX = 640;						//������� �� ���� ����� �������
	if (y < 340) tempY = 340;						//������� ������� �������
	if (y > 1920) tempY = 1920;						//������ �������
	if (x > 9850) tempX = 9850;						//������ �������
	view.setCenter(tempX, tempY);					//������ �� �������, ��������� ��� ����������
	return view;									//��������� ���� ������, ��� ��������� ��
}


#include <SFML/System.hpp>
#include <cmath>

inline void norm(sf::Vector2f& vector, float& norm)
{
	norm = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

inline void normalize(sf::Vector2f& vector)
{
	float n = 0.f;
	norm(vector, n);
	vector /= n;
}

inline void direction(sf::Vector2f a, sf::Vector2f b, sf::Vector2f& dir)
{
	dir = a - b;
	normalize(dir);
}

inline float distance(sf::Vector2f a, sf::Vector2f b)
{
	sf::Vector2f dis = a-b;
	return sqrt(pow(dis.x, 2) + pow(dis.y, 2));
}

inline int sgn(int& x)
{
	return x > 0 ? 1 : (x < 0 ? -1 : 0);
}

inline float min(float& val, float& min)
{
	return val > min ? min : val;
}

inline float max(float& val, float& max)
{
	return val > max ? max : val;
}
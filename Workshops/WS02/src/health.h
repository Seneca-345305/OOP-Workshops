#ifndef SENECA_HEALTH_H
#define SENECA_HEALTH_H

namespace seneca
{
	/// <summary>
	/// A character with this health will take damage at half rate
	/// of a normal character.
	/// </summary>
	class SuperHealth
	{
		/// <summary>
		/// Current amount of health.
		/// </summary>
		double m_value = 1000.0;
	public:
		/// <summary>
		/// Reduce the health by the half-damage received as parameter.
		/// </summary>
		SuperHealth& operator-=(int dmg)
		{
			m_value -= dmg / 2.0;
			return *this;
		}

		/// <summary>
		/// Sets current health to the new value.
		/// </summary>
		SuperHealth& operator=(int newVal)
		{
			m_value = newVal;
			return *this;
		}

		/// <summary>
		/// Get the numeric value of the health.
		/// </summary>
		operator int() const
		{
			return static_cast<int>(m_value);
		}
	};

	/// <summary>
	/// The character has infinite health, effectively meaning that it
	/// cannot die. The health cannot be reduced or increased.
	/// </summary>
	struct InfiniteHealth
	{
		/// <summary>
		/// This operation has no effect. The infinite health cannot be reduced.
		/// </summary>
		/// <param name="">Not used!</param>
		/// <returns>a reference to the current instance.</returns>
		InfiniteHealth& operator-=(int) { return *this; }

		/// <summary>
		/// This operation has no effect. The infinite health cannot be modified.
		/// </summary>
		/// <param name="">Not used!</param>
		/// <returns>a reference to the current instance.</returns>
		InfiniteHealth& operator=(int) { return *this; }

		/// <summary>
		/// Get the numerical value of the current health.
		/// </summary>
		operator int() const { return 1; }
	};
}
#endif

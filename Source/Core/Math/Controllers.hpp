/***********************************************************************
FILE CONTROLLERS.H CONTAINS CONTROLLER TEMPLATE CLASS IMPLEMENTATIONS.

THE FILE CONTENT HAS BEEN CREATED TO SUPPORT "DEVELOPMENT OF FLIGHT
CONTROL SYSTEM FOR MORPHING ELEVON CONTROL SURFACE", 2019 THESIS.

FILE UTMOST REVIEW DONE ON (04.01.2021) BY ARTUR K.
***********************************************************************/

#ifndef ATL_CONTROLLERS_HPP
#define ATL_CONTROLLERS_HPP

#include "Math.hpp"

#include <algorithm>

namespace atl
{
	//-----------------------------------------------------------------------
	// P CONTROLLER TEMPLATE
	//-----------------------------------------------------------------------

	template <class T>
	class TPController
	{
	public:
		TPController(T Kp) : m_Kp(Kp) { }
		~TPController() = default;

		T calculateControlSignal(T desiredValue, T currentValue)
		{
			// Calculate error
			T error = desiredValue - currentValue;

			// Calculate proportional term
			T proportionalTermOut = m_Kp * error;

			return proportionalTermOut;
		}

		void cap(T& value, T min, T max)
		{
			if (value < min) value = min;
			if (value > max) value = max;
		}

	private:
		//Gains
		T m_Kp;
	};


	//-----------------------------------------------------------------------
	// PI CONTROLLER TEMPLATE
	//-----------------------------------------------------------------------

	template <class T>
	class TPIController
	{
	public:
		TPIController(T dt, T Kp, T Ki) 
			: m_dt(dt) 
			, m_Kp(Kp)
			, m_Ki(Ki)
			, m_integral(static_cast<T>(0.0)) {}

		~TPIController() = default;

		T calculateControlSignal(T desiredValue, T currentValue)
		{
			// Calculate error
			T error = desiredValue - currentValue;

			// Calculate proportional term
			T proportionalTermOut = m_Kp * error;

			// Calculate integral term
			m_integral += error * m_dt;
			T integralTermOut = m_Ki * m_integral;

			// Calculate total output
			T controllerOutput = proportionalTermOut + integralTermOut;

			return controllerOutput;
		}

		void cap(T& value, T min, T max)
		{
			if (value < min) value = min;
			if (value > max) value = max;
		}

		void updateTimeStep(T timeStep)
		{
			m_dt = timeStep;
		}

	private:
		T m_dt; // Loop interval time (regulation period)

		// Gains
		T m_Kp; // Proportional controller gain
		T m_Ki; // Integral controller gain

		T m_integral;
	};


	//-----------------------------------------------------------------------
	// PID CONTROLLER TEMPLATE
	// 
	// If it is only required to use proportional term, set the proportional gain
	// to the desired value, and the rest gains to zero. This will leave
	// only proportional term in the PID controller.
	// 
	// If it is only required to use PI controller, then set the proportional and
	// integral terms to the desired values and set the derivative gain as zero.
	// 
	// Where simpler controllers P or PI can be used, use the above defined templates
	// as they will be better performance wise, for micro controller. 
	//-----------------------------------------------------------------------

	template<class T>
	class TPIDController
	{
	public:
		CPIDControllerT(T dt, T max, T min, T Kp, T Kd, T Ki) 
			: m_dt(dt)
			, m_max(max)
			, m_min(min) 
			, m_Kp(Kp) 
			, m_Kd(Kd) 
			, m_Ki(Ki)
			, m_integral(0.0)
			, m_previousError(0.0) { }

		~CPIDControllerT() = default;

		// desiredValue is also known as set point
		T calculateControlSignal(T desiredValue, T currentValue)
		{
			// Calculate error
			T error = desiredValue - currentValue;

			// Calculate proportional term
			T proportionalTermOut = m_Kp * error;

			// Calculate integral term
			m_integral += error * m_dt;
			T integralTermOut = m_Ki * m_integral;

			// ****** NOTE: One of the anti-windup techniques is to cap the integral terms to some limits
			// this->cap(integralTermOut, -400, 400); // also need to reset the prevous error

			// Calculate derivative term
			T derivative = (error - m_previousError) / m_dt;
			T derrivativeTermOut = m_Kd * derivative;

			// Calculate total output
			T controllerOutput = proportionalTermOut + integralTermOut + derrivativeTermOut;

			// Apply limits
			cap(controllerOutput, m_min, m_max);

			// Note down the current error
			m_previousError = error;

			return controllerOutput;
		}

		// ****** TODO: Replace by std::cap !
		void cap(T& value, T min, T max)
		{
			if (value < min) value = min;
			if (value > max) value = max;
		}

		void updateTimeStep(T timeStep)
		{
			m_dt = timeStep;
		}

	private:
		T m_dt; // Loop interval time

		// Limits
		T m_max;
		T m_min;

		// Gains
		T m_Kp; // Proportional controller gain
		T m_Kd; // Derivative controller gain
		T m_Ki; // Integral controller gain

		T m_previousError;
		T m_integral;
	};

	using CPController		= TPController<scalar>;
	using CPIController		= TPIController<scalar>;
	using CPIDController		= TPIDController<scalar>;

} // namespace atl
#endif // !ATL_CONTROLLERS_HPP

#ifndef __Navigation_inavmeshencounterspot_h__
#define __Navigation_inavmeshencounterspot_h__

namespace Navigation {
	/**
	 * Represents a loaded encounter spot within an encounter path.
	 */
	class INavMeshEncounterSpot {
	public:
		/**
		 * Destroy the instance.
		 */
		virtual void Destroy() = 0;

		/**
		 * Retrieve the order ID.
		 */
		virtual unsigned int GetOrderID() = 0;

		/**
		 * Retrieve the parametric distance.
		 */
		virtual float GetParametricDistance() = 0;
	};
}

#endif